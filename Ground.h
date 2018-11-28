#ifndef GROUND_H_
#define GROUND_H_

#include <Ogre.h>
#include "physics.h"

class Ground: public GameObject {

protected:
	//Plane *plane;

public:
	Ground(SceneManager * sceneMgr, SceneNode * rootNode,
			String name, Entity * e, Physics * phys, btCollisionShape * shape,
			const Ogre::Vector3& origin) :
			GameObject(sceneMgr, rootNode, name, e, phys, shape, 0., false,
					origin, btQuaternion(1.0, 0.0, 0.0, 0.0), 1.15, 0.0) {
		this->setCollisionType(CollisionType::GROUND);
		//does this help performance?
		//this->physics->dynamicsWorld->removeRigidBody(body);
	}

	void animate(const FrameEvent &evt){} //nothing?
};

#endif /* GROUND_H_ */
