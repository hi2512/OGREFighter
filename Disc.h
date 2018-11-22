#ifndef DISC_H_
#define DISC_H_

#include <Ogre.h>
#include "physics.h"

using namespace Ogre;
using namespace std;
class Disc: public GameObject {

protected:

	SceneNode * offsetNode;
	void createAnim();
	void animate(const FrameEvent& evt);

public:
	Disc(SceneManager * sceneMgr, SceneNode * rootNode, String name, Entity * e, Physics * phys,
			btCollisionShape * shape, const Ogre::Vector3& origin, const btQuaternion& orientation,
			const btVector3& linearVelocity, const btVector3& angularVelocity) :
			GameObject(sceneMgr, rootNode, name, e, phys, shape, 2.0, false, origin,
					btQuaternion(1.0, 0.0, 0.0, 0.0), btVector3(0, 20, 0), btVector3(0, 0, 0), 1.0,
					0.0) {
		offsetNode = rootNode->createChildSceneNode("Offset" + name);

		offsetNode->attachObject(rootNode->detachObject((unsigned short) 0));
		//printf("collision flags: %d\n", this->body->getCollisionFlags());
		//this->body->setCollisionFlags(1);

		this->createAnim();
	}

};

#endif /* DISC_H_ */
