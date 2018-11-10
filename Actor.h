#ifndef ACTOR_H_
#define ACTOR_H_

#include <Ogre.h>
#include "physics.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

using namespace Ogre;
using namespace std;

enum {
	LIGHT,
	MEDIUM,
	HEAVY,
	SPECIAL
};

class Actor: public GameObject {

protected:
	std::vector<btRigidBody> hitboxes;

public:

	Actor(SceneManager * sceneMgr, SceneNode * rootNode,
			String name, Entity * e, Physics * phys, btCollisionShape * shape,
			const Ogre::Vector3& origin) :
			GameObject(sceneMgr, rootNode, name, e, phys, shape, 0., false,
					origin, btQuaternion(1.0, 0.0, 0.0, 0.0), 1.0, 0.0) {

	}
	void readInputs(const std::vector<int>& keys);
	void animate(const FrameEvent& evt);

};



#endif /* ACTOR_H_ */
