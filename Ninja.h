#ifndef NINJA_H_
#define NINJA_H_

#include <Ogre.h>
#include "physics.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "Actor.h"
#include <SDL2/SDL.h>
#include "InputContainer.h"
#include "Disc.h"

using namespace std;
using namespace Ogre;
class Ninja: public Actor {

private:
	SceneNode * ninOffsetNode;

protected:
	void createLightBox();
	void createMediumBox();
	void createHeavyBox();
	void createSpecial1Box();
	void createJumpAttackBox();
	void lightAnimation();
	void mediumAnimation();
	void heavyAnimation();
	void special1Animation();
	void jumpAttackAnimation();

	void createJumpUpArc();
	void createJumpLeftArc();
	void createJumpRightArc();
	void playJumpAnimation(InputType jumpType);
	void cancelJump();
	//void clearJumpAnimation();
	void playHitAnimation();
	void playBlockAnimation();





public:
	Ninja(bool isPlayer2, SceneManager * sceneMgr, SceneNode * rootNode, String name, Entity * e,
			Physics * phys, btCollisionShape * shape, const Ogre::Vector3& origin,
			btQuaternion orientation, std::deque<KeyInput> * inBuf, std::deque<KeyInput> * relBuf,
			std::vector<KeyInput> * kBuf, int left, int right, int up, int down, int light, int medium, int heavy) :
			Actor(isPlayer2, sceneMgr, rootNode, name, e, phys, shape, origin, orientation, inBuf,
					relBuf, kBuf, left, right, up, down, light, medium, heavy) {
		ninOffsetNode = rootNode->createChildSceneNode("NinOffset" + name);

		ninOffsetNode->attachObject(rootNode->detachObject((unsigned short) 0));
		ninOffsetNode->setScale(Vector3(2, 2, 2));
		ninOffsetNode->setPosition(Vector3(0, -200, 0));
		playingAnimation = "Idle1";
		geom->getAnimationState(playingAnimation)->setEnabled(true);
		geom->getAnimationState(playingAnimation)->setLoop(true);

		this->walkSpeed = 350.0;

		AnimationStateSet *mAnims = this->geom->getAllAnimationStates();
		AnimationStateIterator it = mAnims->getAnimationStateIterator();
		while (it.hasMoreElements()) {
			AnimationStateMap::mapped_type as = it.getNext();
			LogManager::getSingleton().logMessage(as->getAnimationName());
			as->setLoop(true);
		}
		this->groundHeight = 200;
		this->lAttackFrames = 30;
		this->mAttackFrames = 40;
		this->hAttackFrames = 90;
		this->s1AttackFrames = 80;
		this->jhAttackFrames = 60;

		this->createLightBox();
		this->createMediumBox();
		this->createHeavyBox();
		//this->createSpecialBox();
		this->createJumpAttackBox();

		this->createJumpUpArc();
		this->createJumpLeftArc();
		this->createJumpRightArc();

	}

	void animate(const Ogre::FrameEvent& evt);

};

#endif /* NINJA_H_ */
