#ifndef ACTOR_H_
#define ACTOR_H_

#include <Ogre.h>
#include "physics.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <SDL2/SDL.h>
#include "InputContainer.h"

using namespace Ogre;
using namespace std;

enum AttackType {
	LIGHT, MEDIUM, HEAVY, SPECIAL
};

enum StateType {
	STOP, FREE, ATTACK, BLOCK, AIR, KNOCKDOWN, STUN

};

enum InputType {
	UP, DOWN, LEFT, RIGHT, L, M, H, S

};


class Actor: public GameObject {

protected:
	Actor * opponent = NULL;
	StateType actorState = StateType::FREE;

	std::map<int, InputType> keyBinding;

	String playingAnimation;

	std::deque<KeyInput> * inputBuffer;
	std::deque<KeyInput> * releaseBuffer;
	std::vector<KeyInput> * keysHeld;

	std::vector<btRigidBody> hitboxes;
	void createLightBox(Real x, Real y, Real z);
	void createMediumBox(Real x, Real y, Real z);
	void createHeavyBox(Real x, Real y, Real z);
	void createSpecialBox(Real x, Real y, Real z);

public:

	Actor(SceneManager * sceneMgr, SceneNode * rootNode, String name,
			Entity * e, Physics * phys, btCollisionShape * shape,
			const Ogre::Vector3& origin, btQuaternion orientation,
			std::deque<KeyInput> * inBuf,
			std::deque<KeyInput> * relBuf,
			std::vector<KeyInput> * kBuf, int left, int right) :
			GameObject(sceneMgr, rootNode, name, e, phys, shape, 0., true,
					origin, orientation, 1.0, 0.0) {
		inputBuffer = inBuf;
		releaseBuffer = relBuf;
		keysHeld = kBuf;
		playingAnimation = "NOTSET";

		keyBinding.insert(pair<int, InputType>(left, InputType::LEFT));
		keyBinding.insert(pair<int, InputType>(right, InputType::RIGHT));

	}
	void setP1Orientation();
	void setP2Orientation();
	void setOpponent(Actor * opp) {opponent = opp;}
	void setAnimation(String animationName);
	void readInputs(std::deque<KeyInput>& buf,
			std::deque<KeyInput>& rBuf);
	//void animate(const FrameEvent& evt);

};

#endif /* ACTOR_H_ */
