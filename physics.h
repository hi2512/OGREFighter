#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include <Ogre.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <vector>
#include <map>

#include "DebugDraw.h"

using namespace Ogre;
using namespace std;

class GameObject;
struct BulletContactCallback;
struct CollisionContext;

enum CollisionType {
	COL_NOTHING = 0, COLLISIONBOX = 1, HITBOX = 2, HURTBOX_P1 = 4, HURTBOX_P2 = 8, WALL = 16
};

class Physics {
public:
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	std::vector<btCollisionShape *> collisionShapes;
	std::map<std::string, btRigidBody *> physicsAccessors;

	btPairCachingGhostObject* pairCachingGhostObject = NULL;

	CDebugDraw * dbd;

	void initObjects();

	btDiscreteDynamicsWorld* getWorld() {
		return dynamicsWorld;
	}

	int addObject(GameObject* obj);

	void stepSimulation(const Ogre::Real elapsedTime, int maxSubSteps,
			const Ogre::Real fixedTimestep);
};

class GameObject {
protected:
	String name;
	Ogre::SceneManager* sceneMgr;
	Ogre::SceneNode* rootNode;
	Ogre::Entity* geom;

	Physics* physics;
	btCollisionShape* shape;
	btRigidBody* body;
	btTransform tr;
	btVector3 inertia;

	btMotionState* motionState;

	btScalar mass;
	btScalar restitution;
	btScalar friction;
	bool kinematic;
	//bool needsUpdates;

	//CollisionContext* context;
	//BulletContactCallback* cCallBack;

public:

	GameObject(Ogre::SceneManager *, SceneNode * rootNode, String name,
			Entity *);

	GameObject(Ogre::SceneManager *, SceneNode * rootNode, String name,
			Entity *, Physics *, btCollisionShape *, btScalar mass,
			bool isKinematic, const Ogre::Vector3&,
			const btQuaternion& orientation, Real restitution, Real friction);

	GameObject(Ogre::SceneManager *, SceneNode * rootNode, String name,
			Entity *, Physics *, btCollisionShape *, btScalar mass,
			bool isKinematic, const Ogre::Vector3&,
			const btQuaternion& orientation, const btVector3& linearVelocity,
			const btVector3& angularVelocity, Real restitution, Real friction);

	void initPhys(Physics *, btCollisionShape *, btScalar mass,
			bool isKinematic, const Ogre::Vector3&,
			const btQuaternion& orientation, Real restitution, Real friction);
	void initPhys(Physics *, btCollisionShape *, btScalar mass,
			bool isKinematic, const Ogre::Vector3&,
			const btQuaternion& orientation, const btVector3& linearVelocity,
			const btVector3& angularVelocity, Real restitution, Real friction);

	btRigidBody * getRigidBody() {
		return this->body;
	}
	SceneNode * getRootNode() {
		return rootNode;
	}
	String getName() {
		return name;
	}
	virtual void animate(const FrameEvent &evt);
	const CollisionContext& getCollisionContext();
	const BulletContactCallback& getCallBack();
	void updateTransform();
	void addToSimulator();
};

struct CollisionContext {
	bool hit;
	const btCollisionObject* body;
	const btCollisionObject* lastBody;
	GameObject* theObject;
	float distance;
	float velNorm;
	btVector3 point;
	btVector3 normal;
	btVector3 velocity;

	CollisionContext() {
		reset();
	}

	void reset() {
		hit = false;
		body = NULL;
		theObject = NULL;
		distance = 0.0;
		velNorm = 0.0;
		point.setZero();
		normal.setZero();
		velocity.setZero();
	}

	SceneNode* getSceneNode() {
		const btRigidBody* body0 = btRigidBody::upcast(body);
		void *userPointer0 = body0->getUserPointer();
		GameObject *gameObject0 = static_cast<GameObject *>(userPointer0);
		return gameObject0->getRootNode();
	}

};

/*
 A struct to handle contactTest queries via the ContactResultCallback
 Based on this example code: http://www.bulletphysics.org/mediawiki-1.5.8/index.php?title=Collision_Callbacks_and_Triggers
 */
struct BulletContactCallback: public btCollisionWorld::ContactResultCallback {

	// Constructor, pass whatever context you want to have available when processing contacts
	/* You may also want to set m_collisionFilterGroup and m_collisionFilterMask
	 *  (supplied by the superclass) for needsCollision() */
	BulletContactCallback(btRigidBody& tgtBody,
			CollisionContext& context /*, ... */) :
			btCollisionWorld::ContactResultCallback(), body(tgtBody), ctxt(
					context) {
	}

	btRigidBody& body; // The body the sensor is monitoring
	CollisionContext& ctxt; // External information for contact processing

	virtual ~BulletContactCallback() {

	}

	// If you don't want to consider collisions where the bodies are joined by a constraint, override needsCollision:
	/* However, if you use a btCollisionObject for #body instead of a btRigidBody,
	 *  then this is unnecessary -- checkCollideWithOverride isn't available */
	virtual bool needsCollision(btBroadphaseProxy* proxy) const override {
		// superclass will check m_collisionFilterGroup and m_collisionFilterMask
		if (!btCollisionWorld::ContactResultCallback::needsCollision(proxy))
			return false;
		// if passed filters, may also want to avoid contacts between constraints
		return body.checkCollideWithOverride(
				static_cast<btCollisionObject*>(proxy->m_clientObject));
	}

	// Called with each contact for your own processing
	virtual btScalar addSingleResult(btManifoldPoint& cp,
			const btCollisionObjectWrapper* colObj00, int partId0, int index0,
			const btCollisionObjectWrapper* colObj11, int partId1, int index1)
					override {

		const btCollisionObject* colObj0 = colObj00->getCollisionObject();
		const btCollisionObject* colObj1 = colObj11->getCollisionObject();
		ctxt.hit = true;
		ctxt.lastBody = ctxt.body;
		if (colObj0 == &body) {
			ctxt.point = cp.m_localPointA;
			ctxt.body = colObj1;
		} else {
			assert(
					colObj1 == &body
							&& "body does not match either collision object");
			ctxt.point = cp.m_localPointB;
			ctxt.body = colObj0;
		}
		ctxt.theObject = static_cast<GameObject*>(ctxt.body->getUserPointer());
		ctxt.normal = cp.m_normalWorldOnB;
		ctxt.velocity = body.getLinearVelocity();
		ctxt.velNorm = ctxt.normal.dot(ctxt.velocity);

		return 0;
	}
};

#endif

