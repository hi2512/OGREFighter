#include "physics.h"
#include <string>
#include <iostream>

using namespace Ogre;
using namespace std;

Real maxSpeed = 300.0;

void myTickCallback(btDynamicsWorld *world, btScalar timeStep) {
	// from wiki

	for (int i = 0; i < world->getNumCollisionObjects(); i++) {
		btCollisionObject * obj = world->getCollisionObjectArray()[i];
		if (obj->getCollisionFlags()
				== CollisionType::HITBOX) {
			//LogManager::getSingleton().logMessage("ISGHOST");
			continue;
		}

		if (!obj->isKinematicObject()) {
			GameObject * go = (GameObject *) obj->getUserPointer();
			btVector3 velocity = go->getRigidBody()->getLinearVelocity();
			btScalar speed = velocity.length();
			if (speed > maxSpeed) {
				velocity *= maxSpeed / speed;
				go->getRigidBody()->setLinearVelocity(velocity);
			}
		}
	}

}



void Physics::initObjects() {
	collisionConfiguration = new btDefaultCollisionConfiguration();
	//dispatcher = new btCollisionDispatcher(collisionConfiguration);
	dispatcher = new myCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	//btVector3 worldMin(-1000, -1000, -1000);
	//btVector3 worldMax(1000, 1000, 1000);
	//overlappingPairCache = new btAxisSweep3(worldMin, worldMax);
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,
			overlappingPairCache, solver, collisionConfiguration);
	dynamicsWorld->setInternalTickCallback(myTickCallback);

	dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(
			new btGhostPairCallback());

}

int Physics::addObject(GameObject* obj) {
	dynamicsWorld->addRigidBody(obj->getRigidBody());
// should ideally return the index of this object in the dynamics world
	return 0;
}

void Physics::stepSimulation(const Ogre::Real elapsedTime, int maxSubSteps,
		const Ogre::Real fixedTimestep) {
//    for (int i = 0; i != objList.size(); i++) idList[i] = 0;
// dynamicsWorld->stepSimulation(elapsedTime, maxSubSteps, fixedTimestep);
// for (unsigned int i = 0; i < objList.size(); i++)
// 	if (objList[i].gObject->doUpdates()) objList[i].gObject->update(elapsedTime);
}

void GameObject::initPhys(Physics * phys, btCollisionShape * shape,
		btScalar mass, bool isKinematic, const Vector3& origin,
		const btQuaternion& orientation, const btVector3& linearVelocity,
		const btVector3& angularVelocity, Real restitution, Real friction) {
	this->shape = shape;
	this->physics = phys;
	this->kinematic = isKinematic;

	btTransform startTransform;
	startTransform.setIdentity();

	this->mass = mass;
	btVector3 localInertia(0, 0, 0);
	startTransform.setRotation(orientation);
	rootNode->setPosition(origin);
	Vector3 ogreOri = rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	btVector3 ori(ogreOri.x, ogreOri.y, ogreOri.z);

	if (mass != 0.0f)
		shape->calculateLocalInertia(mass, localInertia);
	startTransform.setOrigin(ori);

	motionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape,
			localInertia);
	body = new btRigidBody(rbInfo);
	if (isKinematic) {
		body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
		body->setActivationState(DISABLE_DEACTIVATION);
	}
	body->setLinearVelocity(linearVelocity);
	body->setAngularVelocity(angularVelocity);
	this->restitution = restitution;
	body->setRestitution(restitution);
	this->friction = friction;
	body->setUserPointer(this);
	int collidesWith = CollisionType::COLLISIONBOX | CollisionType::WALL;
	phys->dynamicsWorld->addRigidBody(body, CollisionType::COLLISIONBOX,
			collidesWith);
}

//use this and initphys to get ogre object before phys is created

void GameObject::initPhys(Physics * phys, btCollisionShape * shape,
		btScalar mass, bool isKinematic, const Vector3& origin,
		const btQuaternion& orientation, Real restitution, Real friction) {
	this->shape = shape;
	this->physics = phys;
	this->kinematic = isKinematic;

	btTransform startTransform;
	startTransform.setIdentity();

	this->mass = mass;
	btVector3 localInertia(0, 0, 0);
	startTransform.setRotation(orientation);
	rootNode->setPosition(origin);
	Vector3 ogreOri = rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	btVector3 ori(ogreOri.x, ogreOri.y, ogreOri.z);

	if (mass != 0.0f) {
		shape->calculateLocalInertia(mass, localInertia);
	}
	startTransform.setOrigin(ori);

	motionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape,
			localInertia);
	body = new btRigidBody(rbInfo);
	if (isKinematic) {
		body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
		body->setActivationState(DISABLE_DEACTIVATION);
	}
	this->restitution = restitution;
	body->setRestitution(restitution);
	this->friction = friction;
	body->setFriction(friction);
	body->setUserPointer(rootNode);
	int collidesWith = CollisionType::COLLISIONBOX | CollisionType::WALL;
	phys->dynamicsWorld->addRigidBody(body, CollisionType::COLLISIONBOX,
			collidesWith);
}

void GameObject::animate(const FrameEvent &evt) {
	btTransform trans;
	this->body->getMotionState()->getWorldTransform(trans);

	btQuaternion orientation = trans.getRotation();

	rootNode->setPosition(
			Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(),
					trans.getOrigin().getZ()));
	rootNode->setOrientation(
			Ogre::Quaternion(orientation.getW(), orientation.getX(),
					orientation.getY(), orientation.getZ()));
}

GameObject::GameObject(SceneManager * mgr, SceneNode * rootNode, String name,
		Entity * e) {
	this->sceneMgr = mgr;
	this->name = name;
	this->rootNode = rootNode;
	this->geom = e;
	rootNode->attachObject(e);
}

GameObject::GameObject(SceneManager * mgr, SceneNode * rootNode, String name,
		Entity * e, Physics * phys, btCollisionShape * btShape, btScalar mass,
		bool isKinematic, const Ogre::Vector3& origin,
		const btQuaternion& orientation, Real restitution, Real friction) {

	this->sceneMgr = mgr;
	this->name = name;
	this->rootNode = rootNode;
	this->geom = e;
	rootNode->attachObject(e);
	this->shape = btShape;
	this->physics = phys;
	this->kinematic = isKinematic;

	btTransform startTransform;
	startTransform.setIdentity();

	this->mass = mass;
	btVector3 localInertia(0, 0, 0);
	startTransform.setRotation(orientation);
	rootNode->setPosition(origin);
//Vector3 ogreOri = rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Vector3 ogreOri = rootNode->getPosition();
	btVector3 ori(ogreOri.x, ogreOri.y, ogreOri.z);

	if (mass != 0.0f)
		shape->calculateLocalInertia(mass, localInertia);
	startTransform.setOrigin(ori);

	motionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape,
			localInertia);
	body = new btRigidBody(rbInfo);
	if (isKinematic) {
		body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
		body->setActivationState(DISABLE_DEACTIVATION);
	}
	this->restitution = restitution;
	body->setRestitution(restitution);
	this->friction = friction;
	body->setFriction(friction);
	body->setUserPointer(this);
	int collidesWith = CollisionType::COLLISIONBOX | CollisionType::WALL;
	collidesWith = 0 - 1;
	phys->dynamicsWorld->addRigidBody(body, CollisionType::COLLISIONBOX,
			collidesWith);

}

GameObject::GameObject(SceneManager * mgr, SceneNode * rootNode, String name,
		Entity * e, Physics * phys, btCollisionShape * btShape, btScalar mass,
		bool isKinematic, const Ogre::Vector3& origin,
		const btQuaternion& orientation, const btVector3& linearVelocity,
		const btVector3& angularVelocity, Real restitution, Real friction) {

	this->sceneMgr = mgr;
	this->name = name;
	this->rootNode = rootNode;
	this->geom = e;
	rootNode->attachObject(e);
	this->shape = btShape;
	this->physics = phys;
	this->kinematic = isKinematic;
//rootNode->setPosition(origin);

	btTransform startTransform;
	startTransform.setIdentity();

	this->mass = mass;
	btVector3 localInertia(0, 0, 0);
	startTransform.setRotation(orientation);

//Vector3 ogreOri = rootNode->convertLocalToWorldPosition(Vector3::ZERO);
//Vector3 ogreOri = rootNode->getPosition();
//btVector3 ori(ogreOri.x, ogreOri.y, ogreOri.z);
	btVector3 ori(origin.x, origin.y, origin.z);

//if (mass != 0.0f)
	shape->calculateLocalInertia(mass, localInertia);
	startTransform.setOrigin(ori);

	motionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape,
			localInertia);
	body = new btRigidBody(rbInfo);
	if (isKinematic) {
		body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
		body->setActivationState(DISABLE_DEACTIVATION);
	} else {
		body->setLinearVelocity(linearVelocity);
		body->setAngularVelocity(angularVelocity);
	}
	this->restitution = restitution;
	body->setRestitution(restitution);
	this->friction = friction;
	body->setFriction(friction);
	body->setUserPointer(this);
	int collidesWith = CollisionType::COLLISIONBOX | CollisionType::WALL;
	collidesWith = 0 - 1;
	phys->dynamicsWorld->addRigidBody(body, CollisionType::COLLISIONBOX,
			collidesWith);
}

void GameObject::updateTransform() {

}

void GameObject::addToSimulator() {
//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	updateTransform();
//rigidbody is dynamic if and only if mass is non zero, otherwise static
	if (mass != 0.0f)
		shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape,
			inertia);
	rbInfo.m_restitution = restitution;
	rbInfo.m_friction = friction;
	body = new btRigidBody(rbInfo);
	body->setUserPointer(this);
	if (kinematic) {
		body->setCollisionFlags(
				body->getCollisionFlags()
						| btCollisionObject::CF_KINEMATIC_OBJECT);
		body->setActivationState(DISABLE_DEACTIVATION);
	}
	int simID = physics->addObject(this);
}
