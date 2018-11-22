#ifndef _BALL_H_
#define _BALL_H_

#include <Ogre.h>
#include "physics.h"

class Ball: public GameObject {
private:
	//ParticleSystem * ps;

public:
	Ball(Ogre::SceneManager * sceneMgr, SceneNode * rootNode, String name,
			Entity * e, Physics * phys, const Ogre::Vector3& origin,
			const btQuaternion& orientation, const btVector3& linearVelocity,
			const btVector3& angularVelocity) :
			GameObject(sceneMgr, rootNode, name, e, phys,
					new btSphereShape(e->getBoundingBox().getSize().x * 0.2),
					0.2, false, origin, orientation, linearVelocity,
					angularVelocity, 1.0, 0.0) {

		//ps = sceneMgr->createParticleSystem(name, "BallTrail");
		//rootNode->attachObject(ps);
	}

	void animate(const FrameEvent &evt) {
		GameObject::animate(evt);
		//printf("flags %d\n", this->body->getCollisionFlags());
		CollisionContext context;
		BulletContactCallback* thing = new BulletContactCallback(*body,
				context);
		this->physics->getWorld()->contactTest(body, *thing);
		if (context.hit) {
			playSound("../assets/hit.wav", SDL_MIX_MAXVOLUME);
		}

	}

};

#endif
