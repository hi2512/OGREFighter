#ifndef WALL_H_
#define WALL_H_

#include <Ogre.h>
#include "physics.h"

class Wall: public GameObject {

protected:

public:
	Wall(SceneManager * sceneMgr, SceneNode * rootNode, String name, Entity * e, Physics * phys,
			btCollisionShape * shape, const Ogre::Vector3& origin) :
			GameObject(sceneMgr, rootNode, name, e, phys, shape, 0., true, origin,
					btQuaternion(0.0, 0.0, 0.0, 1.0), 1.15, 0.0) {
		this->setCollisionType(CollisionType::WALL);
		//printf("start orientation, w:%f, x:%f y:%f z:%f\n", orientation.getW(), orientation.getX(),
		//	orientation.getY(), orientation.getZ());

		//set body orientation
		btQuaternion p1orientation(0.0, -0.707, 0.0, 0.707);
		btTransform trans;
		this->body->getMotionState()->getWorldTransform(trans);

		trans.setRotation(p1orientation);
		this->body->getMotionState()->setWorldTransform(trans);
		btQuaternion btori = trans.getRotation();
		Quaternion ori(btori.w(), btori.x(), btori.y(), btori.z());

		//this->rootNode->setOrientation(ori);
	}

	void animate(const FrameEvent &evt) {
		/*
		 auto curPos = this->rootNode->getPosition();
		 printf("before wall node pos: x:%f y:%f z:%f\n", curPos.x, curPos.y, curPos.z);
		 curPos = this->rootNode->getPosition();
		 printf("after wall node pos: x:%f y:%f z:%f\n", curPos.x, curPos.y, curPos.z);
		 */
		/*
		 btTransform trans;
		 this->body->getMotionState()->getWorldTransform(trans);

		 btQuaternion orientation = trans.getRotation();
		 printf("cur orientation, w:%f, x:%f y:%f z:%f\n", orientation.getW(), orientation.getX(),
		 orientation.getY(), orientation.getZ());
		 rootNode->setPosition(
		 Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(),
		 trans.getOrigin().getZ()));
		 rootNode->setOrientation(
		 Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(),
		 orientation.getZ()));
		 */
	}
};

#endif /* WALL_H_ */
