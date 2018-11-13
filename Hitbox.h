#ifndef HITBOX_H_
#define HITBOX_H_

#include <Ogre.h>
#include "physics.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <SDL2/SDL.h>

using namespace Ogre;
using namespace std;
class Hitbox: public GameObject {

	Hitbox(SceneManager * mgr, SceneNode * rootNode, String name,
			Physics * phys, btCollisionShape * shape,
			const Ogre::Vector3& origin) :
			GameObject(mgr, rootNode, name, NULL, phys, shape, 0.0, true,
					origin, btQuaternion::getIdentity(), 0.0, 0.0) {

	}

};

#endif /* HITBOX_H_ */
