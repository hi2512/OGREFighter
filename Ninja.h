#ifndef NINJA_H_
#define NINJA_H_

#include <Ogre.h>
#include "physics.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "Actor.h"
#include <SDL2/SDL.h>
#include "InputContainer.h"

using namespace std;
using namespace Ogre;
class Ninja: public Actor {

private:
	SceneNode * ninOffsetNode;
	Real walkSpeed = 300.0;

public:
	Ninja(SceneManager * sceneMgr, SceneNode * rootNode, String name,
			Entity * e, Physics * phys, btCollisionShape * shape,
			const Ogre::Vector3& origin, btQuaternion orientation,
			std::deque<KeyInput> * inBuf, std::deque<KeyInput> * relBuf,
			std::vector<KeyInput> * kBuf) :
			Actor(sceneMgr, rootNode, name, e, phys, shape, origin, orientation,
					inBuf, relBuf, kBuf) {
		ninOffsetNode = rootNode->createChildSceneNode("NinOffset" + name);

		ninOffsetNode->attachObject(rootNode->detachObject((unsigned short) 0));
		ninOffsetNode->setScale(Vector3(2, 2, 2));
		ninOffsetNode->setPosition(Vector3(0, -200, 0));
		playingAnimation = "Idle1";
		geom->getAnimationState(playingAnimation)->setEnabled(true);
		geom->getAnimationState(playingAnimation)->setLoop(true);

		AnimationStateSet *mAnims = this->geom->getAllAnimationStates();
		AnimationStateIterator it = mAnims->getAnimationStateIterator();
		while (it.hasMoreElements()) {
			AnimationStateMap::mapped_type as = it.getNext();
			LogManager::getSingleton().logMessage(as->getAnimationName());
			as->setLoop(true);
		}

	}

	void animate(const Ogre::FrameEvent& evt);

};

#endif /* NINJA_H_ */
