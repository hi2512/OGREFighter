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
	const String walkName = "Walk";
	const String idleName = "Idle1";
	const String jumpName = "JumpNoHeight";
	const String superName = "HighJump";
	void createLightBox();
	void createMediumBox();
	void createHeavyBox();
	void createSpecial1LBox();
	void createSpecial1MBox();
	void createSpecial1HBox();
	void createJumpAttackBox();
	void createSuperBox();
	void lightAnimation();
	void mediumAnimation();
	void heavyAnimation();
	void special1LAnimation();
	void special1MAnimation();
	void special1HAnimation();
	void jumpAttackAnimation();
	void superAnimation();

	void createJumpUpArc();
	void createJumpLeftArc();
	void createJumpRightArc();
	void playJumpAnimation(InputType jumpType);
	void cancelJump();
	//void clearJumpAnimation();
	void playHitAnimation();
	void playBlockAnimation();
	void doDeath();
	Vector3 getSuperPos() {
		return this->getRootNode()->getPosition() + Vector3(0, 380, 0);
	}
	const String getWalkName() {
		return walkName;
	}
	const String getIdleName() {
		return idleName;
	}
	const String getJumpName() {
		return jumpName;
	}
	const String getSuperName() {
		return superName;
	}

public:
	Ninja(bool isPlayer2, SceneManager * sceneMgr, SceneNode * rootNode, String name, Entity * e,
			Physics * phys, btCollisionShape * shape, const Ogre::Vector3& origin,
			btQuaternion orientation, ActorController * con) :
			Actor(isPlayer2, sceneMgr, rootNode, name, e, phys, shape, origin, orientation, con) {
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
		this->lAttackFrames = 25;
		this->mAttackFrames = 40;
		this->hAttackFrames = 90;
		this->s1LAttackFrames = 90;
		this->s1MAttackFrames = 80;
		this->s1HAttackFrames = 90;
		this->jhAttackFrames = 60;
		this->superAttackFrames = 100;
		this->superFreezeFrames = 180;

		this->createLightBox();
		this->createMediumBox();
		this->createHeavyBox();
		//this->createSpecialBox();
		this->createJumpAttackBox();
		this->createSuperBox();

		this->createJumpUpArc();
		this->createJumpLeftArc();
		this->createJumpRightArc();

	}
	~Ninja() {
		this->sceneMgr->destroySceneNode(ninOffsetNode);
	}
	void animate(const Ogre::FrameEvent& evt);

};

#endif /* NINJA_H_ */
