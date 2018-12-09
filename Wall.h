#ifndef WALL_H_
#define WALL_H_

#include <Ogre.h>
#include "physics.h"

class Wall: public GameObject {

protected:

public:
	Wall(SceneManager * sceneMgr, SceneNode * rootNode, String name, Entity * e, Physics * phys,
			btCollisionShape * shape, const Ogre::Vector3& origin) :
			GameObject(sceneMgr, rootNode, name, e, phys, shape, 0., false, origin,
					btQuaternion(0.0, -0.707, 0.0, 0.707), 1.15, 0.0) {
		this->setCollisionType(CollisionType::WALL);
		//new btStaticPlaneShape(btVector3(0, 1, 0), 0)
		//printf("start orientation, w:%f, x:%f y:%f z:%f\n", orientation.getW(), orientation.getX(),
		//	orientation.getY(), orientation.getZ());

		/*
		//set body orientation
		btQuaternion p1orientation(0.0, -0.707, 0.0, 0.707);
		btTransform trans;
		this->body->getMotionState()->getWorldTransform(trans);

		trans.setRotation(p1orientation);
		this->body->getMotionState()->setWorldTransform(trans);
		btQuaternion btori = trans.getRotation();
		Quaternion ori(btori.w(), btori.x(), btori.y(), btori.z());

		/*
		this->physics->getWorld()->removeRigidBody(body);
		btCollisionObject * co = new btStaticPlaneShape(btVector3(1, 0 ,0), 100);
		btTransform trans;
		trans.setOrigin(btVector3(10, 0 ,0));
		co->setWorldTransform(trans);
		co->setUserPointer(this);
		this->physics->getWorld()->addCollisionObject(co);
		*/


		//this->rootNode->setOrientation(ori);
	}

	void animate(const FrameEvent &evt) {}
};

#endif /* WALL_H_ */
