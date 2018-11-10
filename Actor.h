#ifndef ACTOR_H_
#define ACTOR_H_

#include <Ogre.h>
#include "physics.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

using namespace Ogre;
using namespace std;

enum {
	LIGHT, MEDIUM, HEAVY, SPECIAL
};

enum {
	STOP, FREE, ATTACK, BLOCK, AIR, DOWN, STUN

};

class Actor: public GameObject {

protected:
	std::vector<btRigidBody> hitboxes;
	void createLightBox(Real x, Real y, Real z);
	void createMediumBox(Real x, Real y, Real z);
	void createHeavyBox(Real x, Real y, Real z);
	void createSpecialBox(Real x, Real y, Real z);

public:

	Actor(SceneManager * sceneMgr, SceneNode * rootNode, String name,
			Entity * e, Physics * phys, btCollisionShape * shape,
			const Ogre::Vector3& origin, btQuaternion orientation) :
			GameObject(sceneMgr, rootNode, name, e, phys, shape, 0., false,
					origin, orientation, 1.0, 0.0) {

	}

	void readInputs(std::deque<tuple<int, Uint32>>& buf,
			std::deque<tuple<int, Uint32>>& rBuf);
	//void animate(const FrameEvent& evt);

};

#endif /* ACTOR_H_ */
