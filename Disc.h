#ifndef DISC_H_
#define DISC_H_

#include <Ogre.h>
#include "physics.h"
#include "Actor.h"

using namespace Ogre;
using namespace std;
class Disc: public GameObject {

protected:
	int activeTime;
	SceneNode * offsetNode;
	void createAnim();
	void animate(const FrameEvent& evt);
	Actor * owner;

public:
	Disc(SceneManager * sceneMgr, SceneNode * rootNode, String name, Entity * e, Physics * phys,
			btCollisionShape * shape, const Ogre::Vector3& origin, const btQuaternion& orientation,
			const btVector3& linearVelocity, const btVector3& angularVelocity, HitboxData hbd,
			Actor * owner) :
			GameObject(sceneMgr, rootNode, name, e, phys, shape, 2.0, false, origin,
					btQuaternion(1.0, 0.0, 0.0, 0.0), linearVelocity, btVector3(0, 0, 0), 1.0, 0.0) {
		this->owner = owner;
		myHbd.hitbox = this->getRigidBody();
		CollisionType myType = owner->isP1() ? CollisionType::HITBOX_P1 : CollisionType::HITBOX_P2;
		this->setCollisionType(myType);
		//body->setUserIndex2(128);
		//printf("collision FLAGS %d\n", this->getRigidBody()->getCollisionFlags());
		//this->physics->dynamicsWorld->removeRigidBody(body);
		//physics->dynamicsWorld->addRigidBody((btRigidBody *) myHbd.hitbox);
		//printf("collision FLAGS %d\n", this->getRigidBody()->getCollisionFlags());
		this->myHbd = hbd;
		offsetNode = rootNode->createChildSceneNode("Offset" + name);

		offsetNode->attachObject(rootNode->detachObject((unsigned short) 0));

		activeTime = 250;
		//printf("collision flags: %d\n", this->body->getCollisionFlags());
		//this->body->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
		this->createAnim();
	}

};

#endif /* DISC_H_ */
