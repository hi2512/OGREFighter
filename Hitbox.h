#ifndef HITBOX_H_
#define HITBOX_H_

#include <Ogre.h>
#include "physics.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <SDL2/SDL.h>
#include "Actor.h"

using namespace Ogre;
using namespace std;
class Hitbox: public GameObject {
protected:
	btCollisionObject * collisionGhost;
public:
	Hitbox(SceneManager * mgr, String name, Physics * phys, btCollisionObject * shape,
			const btVector3& origin, HitboxData hbd, CollisionType hitboxOwner) :
			GameObject(mgr, name) {
		this->collisionGhost = shape;
		this->physics = phys;
		this->myHbd = hbd;

		this->setCollisionType(hitboxOwner);

		btTransform trans;
		trans.setIdentity();
		trans.setOrigin(origin);
		this->collisionGhost->setWorldTransform(trans);
		this->collisionGhost->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
		physics->dynamicsWorld->addCollisionObject(collisionGhost);

		collisionGhost->setUserPointer(this);
		collisionGhost->setUserIndex(hitboxOwner);
	}

};

#endif /* HITBOX_H_ */
