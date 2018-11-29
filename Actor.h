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
	NONE, LIGHT, MEDIUM, HEAVY, SPECIAL1L, SPECIAL1M, SPECIAL1H, AIRHEAVY, SUPER
};

enum StateType {
	STOP, FREE, ATTACK, JUMPING, AIRRECOVERY, FALLING, KNOCKDOWN, HITSTUN, BLOCKSTUN, DEAD

};

enum InputType {
	UP, DOWN, LEFT, RIGHT, DOWNRIGHT, DOWNLEFT, L, M, H, S

};

class Actor: public GameObject {
private:
	Real hitScaling();

protected:
	const Real maxHealth = 1000.0;
	Real health = maxHealth;
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
	bool invincible = false;
	bool startSuperFreeze = false;
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

	int specialMove1Window = -1;
	int superMoveWindow = -1;
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
	virtual void createSpecial1LBox() {
	}
	virtual void createSpecial1MBox() {
	}
	virtual void createSpecial1HBox() {
	}
	virtual void createJumpAttackBox() {
	}
	virtual void createSuperBox() {
	}
	int lAttackFrames = -1;
	int mAttackFrames = -1;
	int hAttackFrames = -1;
	int s1LAttackFrames = -1;
	int s1MAttackFrames = -1;
	int s1HAttackFrames = -1;
	int jhAttackFrames = -1;
	int superAttackFrames = -1;
	int superFreezeFrames = -1;
	virtual void lightAnimation() {
	}
	virtual void mediumAnimation() {
	}
	virtual void heavyAnimation() {
	}
	virtual void special1LAnimation() {
	}
	virtual void special1MAnimation() {
	}
	virtual void special1HAnimation() {
	}
	virtual void jumpAttackAnimation() {
	}
	virtual void superAnimation() {
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
	void checkForSpecial1Cancel();
	bool readQCF();
	bool readDoubleQCF();
	bool readQCB();
	bool readDoubleQCB();
	bool readQCFwithOrientation();
	bool readDoubleQCFwithOrientation();
	bool keyIsInputType(KeyInput ki, InputType ipt);
	virtual void doDeath() {
	}
	void doSuperFreeze();
	virtual void doSuperFreezeAnimation() {
	}

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
	void enterStopState(int stopFrames);
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
	Real getMaxHealth() {
		return this->maxHealth;
	}
	Real getHealth() {
		return this->health;
	}
	static bool attackTypeIsNormal(AttackType at) {
		return (at == AttackType::LIGHT) || (at == AttackType::MEDIUM) || (at == AttackType::HEAVY)
				|| (at == AttackType::AIRHEAVY);
	}
	void setStartSuperFreeze(bool b) {
		this->startSuperFreeze = b;
	}
	bool getStartSuperFreeze() {
		return this->startSuperFreeze;
	}
	virtual Vector3 getSuperPos() {
		return this->getRootNode()->getPosition();
	}

};

#endif /* ACTOR_H_ */
