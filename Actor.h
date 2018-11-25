#ifndef ACTOR_H_
#define ACTOR_H_

#include <Ogre.h>
#include "physics.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <SDL2/SDL.h>
#include "InputContainer.h"
#include "Spark.h"
#include "Hitbox.h"

using namespace Ogre;
using namespace std;

enum AttackType {
	NONE, LIGHT, MEDIUM, HEAVY, SPECIAL1, AIRHEAVY
};

enum StateType {
	STOP, FREE, ATTACK, JUMPING, AIRRECOVERY, FALLING, KNOCKDOWN, HITSTUN, BLOCKSTUN

};

enum InputType {
	UP, DOWN, LEFT, RIGHT, DOWNRIGHT, DOWNLEFT, L, M, H, S

};

class Actor: public GameObject {

protected:
	//SceneNode * jumpNode;
	//SceneNode * jumpP2Node;
	Real groundHeight = 0;
	Real walkSpeed = 350.0;
	int comboCounter = 0;
	bool onPlayer2Side;
	bool isPlayer2;
	bool moveLock = false;
	bool newHit = false;
	bool jumpAttack = false;
	GameObject * activeProjectile = NULL;
	InputType jumpType = InputType::UP;

	Actor * opponent = NULL;
	StateType actorState = StateType::FREE;

	int stopFrameCount = -1;
	StateType beforeStopState = StateType::FREE;

	int attackFrameCount = -1;
	AttackType currentAttack = AttackType::NONE;

	int hitstunFrames = -1;
	int blockstunFrames = -1;

	int specialMoveWindow = -1;
	int attackCancelWindow = -1;

	std::map<int, InputType> keyBinding;

	String playingAnimation;

	std::deque<KeyInput> * inputBuffer;
	std::deque<KeyInput> * releaseBuffer;
	std::vector<KeyInput> * keysHeld;

	//std::map<AttackType, HitboxData> hitboxes;
	std::map<AttackType, Hitbox *> hitboxes;

	virtual void createLightBox() {
	}
	virtual void createMediumBox() {
	}
	virtual void createHeavyBox() {
	}
	virtual void createSpecial1Box() {
	}
	virtual void createJumpAttackBox() {
	}
	int lAttackFrames = -1;
	int mAttackFrames = -1;
	int hAttackFrames = -1;
	int s1AttackFrames = -1;
	int jhAttackFrames = -1;
	virtual void lightAnimation() {
	}
	virtual void mediumAnimation() {
	}
	virtual void heavyAnimation() {
	}
	virtual void special1Animation() {
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
	bool readQCF();
	bool readQCB();
	bool readQCFwithOrientation();
	bool keyIsInputType(KeyInput ki, InputType ipt);

public:

	Actor(bool player2, SceneManager * sceneMgr, SceneNode * rootNode, String name, Entity * e,
			Physics * phys, btCollisionShape * shape, const Ogre::Vector3& origin,
			btQuaternion orientation, std::deque<KeyInput> * inBuf, std::deque<KeyInput> * relBuf,
			std::vector<KeyInput> * kBuf, int left, int right, int up, int down, int light,
			int medium, int heavy) :
			GameObject(sceneMgr, rootNode, name, e, phys, shape, 0., true, origin, orientation, 1.0,
					0.0), isPlayer2(player2), onPlayer2Side(player2) {
		inputBuffer = inBuf;
		releaseBuffer = relBuf;
		keysHeld = kBuf;
		playingAnimation = "NOTSET";

		keyBinding.insert(pair<int, InputType>(left, InputType::LEFT));
		keyBinding.insert(pair<int, InputType>(right, InputType::RIGHT));
		keyBinding.insert(pair<int, InputType>(up, InputType::UP));
		keyBinding.insert(pair<int, InputType>(down, InputType::DOWN));
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
	bool isP1() {
		return !this->isPlayer2;
	}
	bool isP2() {
		return this->isPlayer2;
	}
	void setOpponent(Actor * opp) {
		opponent = opp;
	}
	void setAnimation(String animationName);
	void readInputs(std::deque<KeyInput>& buf, std::deque<KeyInput>& rBuf);
	//void animate(const FrameEvent& evt);
	void doCollision(const FrameEvent& evt);
	bool hasActiveProjectile() {
		return this->activeProjectile != NULL;
	}
	void removeActiveProjectile() {
		this->activeProjectile = NULL;
	}

};

#endif /* ACTOR_H_ */
