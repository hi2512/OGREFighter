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
	NONE, LIGHT, MEDIUM, HEAVY, SPECIAL
};

enum StateType {
	STOP, FREE, ATTACK, BLOCK, AIR, KNOCKDOWN, STUN

};

enum InputType {
	UP, DOWN, LEFT, RIGHT, L, M, H, S

};


class Actor: public GameObject {

protected:
	bool onPlayer2Side;
	bool isPlayer2;
	Actor * opponent = NULL;
	StateType actorState = StateType::FREE;

	int stopFrameCount = -1;
	StateType beforeStopState = StateType::FREE;

	int attackFrameCount = -1;
	AttackType currentAttack = AttackType::NONE;

	std::map<int, InputType> keyBinding;

	String playingAnimation;

	std::deque<KeyInput> * inputBuffer;
	std::deque<KeyInput> * releaseBuffer;
	std::vector<KeyInput> * keysHeld;

	std::map<AttackType, btCollisionObject *> hitboxes;
	virtual void createLightBox() {}
	virtual void createMediumBox() {}
	virtual void createHeavyBox() {}
	virtual void createSpecialBox() {}
	int lAttackFrames = -1;
	int mAttackFrames = -1;
	int hAttackFrames = -1;
	int sAttackFrames = -1;
	virtual void lightAnimation() {}
	virtual void mediumAnimation() {}
	virtual void heavyAnimation() {}

	void clearAttack();

public:

	Actor(bool player2, SceneManager * sceneMgr, SceneNode * rootNode, String name,
			Entity * e, Physics * phys, btCollisionShape * shape,
			const Ogre::Vector3& origin, btQuaternion orientation,
			std::deque<KeyInput> * inBuf,
			std::deque<KeyInput> * relBuf,
			std::vector<KeyInput> * kBuf, int left, int right, int medium, int heavy) :
			GameObject(sceneMgr, rootNode, name, e, phys, shape, 0., true,
					origin, orientation, 1.0, 0.0), isPlayer2(player2), onPlayer2Side(player2) {
		inputBuffer = inBuf;
		releaseBuffer = relBuf;
		keysHeld = kBuf;
		playingAnimation = "NOTSET";

		keyBinding.insert(pair<int, InputType>(left, InputType::LEFT));
		keyBinding.insert(pair<int, InputType>(right, InputType::RIGHT));
		keyBinding.insert(pair<int, InputType>(medium, InputType::M));
		keyBinding.insert(pair<int, InputType>(heavy, InputType::H));

	}
	void pushBack(Real dist);
	void setP1Orientation();
	void setP2Orientation();
	bool onP1Side();
	bool onP2Side();
	void setOpponent(Actor * opp) {opponent = opp;}
	void setAnimation(String animationName);
	void readInputs(std::deque<KeyInput>& buf,
			std::deque<KeyInput>& rBuf);
	//void animate(const FrameEvent& evt);

};

#endif /* ACTOR_H_ */
