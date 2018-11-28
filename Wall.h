#ifndef WALL_H_
#define WALL_H_

#include <Ogre.h>
#include "physics.h"

class Wall: public GameObject {

protected:

public:
	Wall(SceneManager * sceneMgr, SceneNode * rootNode,
			String name, Entity * e, Physics * phys, btCollisionShape * shape,
			const Ogre::Vector3& origin) :
			GameObject(sceneMgr, rootNode, name, e, phys, shape, 0., false,
					origin, btQuaternion(1.0, 0.0, 0.0, 0.0), 1.15, 0.0) {
		this->setCollisionType(CollisionType::WALL);
	}

	void animate(const FrameEvent &evt){} //nothing?
};



#endif /* WALL_H_ */
