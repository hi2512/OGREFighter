#ifndef ACTOR_H_
#define ACTOR_H_

#include <Ogre.h>
#include "physics.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <SDL2/SDL.h>
#include "InputContainer.h"

using namespace Ogre;
using namespace std;

enum AttackType {
	NONE, LIGHT, MEDIUM, HEAVY, SPECIAL, AIRHEAVY
};

enum StateType {
	STOP, FREE, ATTACK, JUMPING, AIRRECOVERY, FALLING, KNOCKDOWN, HITSTUN, BLOCKSTUN

};

enum InputType {
	UP, DOWN, LEFT, RIGHT, L, M, H, S

};

struct HitboxData {
	btCollisionObject * hitbox;
	Real hitPushback;
	Real blockPushback;
	int hitstun;
	int blockstun;
	int hitstop;
	int blockstop;
	bool active;
};

class Actor: public GameObject {

protected:
	//SceneNode * jumpNode;
	//SceneNode * jumpP2Node;
	Real groundHeight = 0;

	int comboCounter = 0;
	bool onPlayer2Side;
	bool isPlayer2;
	bool moveLock = false;
	bool newHit = false;
	bool jumpAttack = false;
	InputType jumpType = InputType::UP;

	Actor * opponent = NULL;
	StateType actorState = StateType::FREE;

	int stopFrameCount = -1;
	StateType beforeStopState = StateType::FREE;

	int attackFrameCount = -1;
	AttackType currentAttack = AttackType::NONE;

	int hitstunFrames = -1;
	int blockstunFrames = -1;

	std::map<int, InputType> keyBinding;

	String playingAnimation;

	std::deque<KeyInput> * inputBuffer;
	std::deque<KeyInput> * releaseBuffer;
	std::vector<KeyInput> * keysHeld;

	std::map<AttackType, HitboxData> hitboxes;

	virtual void createLightBox() {
	}
	virtual void createMediumBox() {
	}
	virtual void createHeavyBox() {
	}
	virtual void createSpecialBox() {
	}
	virtual void createJumpAttackBox() {
	}
	int lAttackFrames = -1;
	int mAttackFrames = -1;
	int hAttackFrames = -1;
	int sAttackFrames = -1;
	int jhAttackFrames = -1;
	virtual void lightAnimation() {
	}
	virtual void mediumAnimation() {
	}
	virtual void heavyAnimation() {
	}
	virtual void jumpAttackAnimation() {
	}
	CollisionType myHitType() {
		return this->isPlayer2 ? CollisionType::HITBOX_P2 : CollisionType::HITBOX_P1;
	}
	CollisionType oppHitType() {
		return this->isPlayer2 ? CollisionType::HITBOX_P1 : CollisionType::HITBOX_P2;
	}
	CollisionType myHurtType() {
		return this->isPlayer2 ? CollisionType::HURTBOX_P2 : CollisionType::HURTBOX_P1;
	}
	CollisionType oppHurtType() {
		return this->isPlayer2 ? CollisionType::HURTBOX_P1 : CollisionType::HURTBOX_P2;
	}
	void setBox(btCollisionObject * box, const btVector3& targetPos);
	void clearAttack();
	void recieveHit(HitboxData * hbd);
	void recieveBlock(HitboxData * hbd);
	void enterStopState(int stopFrames);
	void exitStopState();
	void doFall();
	bool isAboveGround();
	virtual void cancelJump() {

	}
	virtual void createJumpUpArc() {
	}
	virtual void createJumpLeftArc() {
	}
	virtual void createJumpRightArc() {
	}
	virtual void playJumpAnimation(InputType jumpType) {
	}
	//virtual void clearJumpAnimation() {}
	virtual void playHitAnimation() {
	}
	virtual void playBlockAnimation() {
	}

public:

	Actor(bool player2, SceneManager * sceneMgr, SceneNode * rootNode, String name, Entity * e,
			Physics * phys, btCollisionShape * shape, const Ogre::Vector3& origin,
			btQuaternion orientation, std::deque<KeyInput> * inBuf, std::deque<KeyInput> * relBuf,
			std::vector<KeyInput> * kBuf, int left, int right, int up, int light, int medium,
			int heavy) :
			GameObject(sceneMgr, rootNode, name, e, phys, shape, 0., true, origin, orientation, 1.0,
					0.0), isPlayer2(player2), onPlayer2Side(player2) {
		inputBuffer = inBuf;
		releaseBuffer = relBuf;
		keysHeld = kBuf;
		playingAnimation = "NOTSET";

		keyBinding.insert(pair<int, InputType>(left, InputType::LEFT));
		keyBinding.insert(pair<int, InputType>(right, InputType::RIGHT));
		keyBinding.insert(pair<int, InputType>(up, InputType::UP));
		keyBinding.insert(pair<int, InputType>(light, InputType::L));
		keyBinding.insert(pair<int, InputType>(medium, InputType::M));
		keyBinding.insert(pair<int, InputType>(heavy, InputType::H));

	}
	int comboCount() {
		return this->comboCounter;
	}
	bool isBlocking();
	void pushBack(Real dist);
	void setP1Orientation();
	void setP2Orientation();
	bool onP1Side();
	bool onP2Side();
	void setOpponent(Actor * opp) {
		opponent = opp;
	}
	void setAnimation(String animationName);
	void readInputs(std::deque<KeyInput>& buf, std::deque<KeyInput>& rBuf);
	//void animate(const FrameEvent& evt);
	void doCollision(const FrameEvent& evt);

};

#endif /* ACTOR_H_ */
