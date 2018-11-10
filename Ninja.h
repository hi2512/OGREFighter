#ifndef NINJA_H_
#define NINJA_H_

#include <Ogre.h>
#include "physics.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "Actor.h"

using namespace std;
using namespace Ogre;
class Ninja: public Actor {

private:
	SceneNode * ninOffsetNode;

public:
	Ninja(SceneManager * sceneMgr, SceneNode * rootNode, String name,
			Entity * e, Physics * phys, btCollisionShape * shape,
			const Ogre::Vector3& origin) :
			Actor(sceneMgr, rootNode, name, e, phys, shape, origin,
					btQuaternion(0.0, -0.707, 0.0, 0.707)) {
		ninOffsetNode = rootNode->createChildSceneNode("NinOffset");

		ninOffsetNode->attachObject(rootNode->detachObject((unsigned short) 0));
		ninOffsetNode->setScale(Vector3(2, 2, 2));
		ninOffsetNode->setPosition(Vector3(0, -200, 0));
	}

};

#endif /* NINJA_H_ */
