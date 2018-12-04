#ifndef AICONTROLLER_H_
#define AICONTROLLER_H_

#include <iostream>
#include <queue>
#include "InputContainer.h"
#include "ActorController.h"
#include <set>
#include "Actor.h"
#include "BehaviorNode.h"
#include <mutex>

class AIController: public ActorController {
protected:
	GameState * gs;
	BehaviorType currentBehavior = BehaviorType::DoNothing;
	BehaviorNode * behaviorRoot;
	std::set<InputType> activeInputs;
	Actor * self;
	Actor * opponent;
	std::thread * stateChecker;
	std::mutex sleepLock;
	void testForBehavior() {
		while (1) {
			if (sleepLock.try_lock()) {
				sleep(0.75);
				currentBehavior = behaviorRoot->decide();
				sleepLock.unlock();
			} else {
				//printf("break\n");
				break;
			}
		}
	}
	void doBehavior() {
		switch (currentBehavior) {
		case BehaviorType::ProjectileAttack: {
			activeInputs.clear();
			int ran = rand() % 3;
			switch (ran) {
			case 0:
				activeInputs.insert(InputType::L);
				break;
			case 1:
				activeInputs.insert(InputType::M);
				break;
			case 2:
				activeInputs.insert(InputType::H);
				break;
			}
		}
			break;
		case BehaviorType::CloseAttack:
			activeInputs.clear();
			activeInputs.insert(InputType::L);
			break;
		case BehaviorType::SpaceAttack:
			activeInputs.insert(InputType::M);
			break;
		case BehaviorType::DoNothing:
			activeInputs.clear();
			break;
		case BehaviorType::Push:
			//walk forward
			activeInputs.clear();
			activeInputs.insert(self->onP2Side() ? InputType::LEFT : InputType::RIGHT);
			break;
		}
	}
public:
	AIController(Actor * me, Actor * opp, GameState * game) :
			self(me), opponent(opp), gs(game) {
		behaviorRoot = new OpponentIsJumpingNode(self, opponent, gs);
		behaviorRoot->setLeft(new SpaceAttackNode(self, opponent, gs));
		behaviorRoot->setRight(new NearOpponentDistanceNode(self, opponent, gs, 300));
		auto cur = behaviorRoot->getRight();
		cur->setLeft(new CloseAttackNode(self, opponent, gs));
		cur->setRight(new FarFromCenterDistanceNode(self, opponent, gs, 300.0));
		cur = cur->getRight();
		cur->setLeft(new PushNode(self, opponent, gs));
		cur->setRight(new ProjectileAttackNode(self, opponent, gs));
		stateChecker = new std::thread(&AIController::testForBehavior, this);

	}
	~AIController() {
		printf("deleting aicontroller\n");
		sleepLock.lock();
		//printf("delete has lock\n");
		stateChecker->join();
		printf("joined\n");
	}
	bool checkForInput(InputType it) {
		doBehavior();
		return activeInputs.count(it);
	}
	bool readQCF() {
		if (currentBehavior == BehaviorType::SpaceAttack && (rand() % 2)) {
			return true;
		}
		if (currentBehavior == BehaviorType::ProjectileAttack) {
			return true;
		}
		return false;
	}
	bool readQCB() {
		if (currentBehavior == BehaviorType::SpaceAttack && (rand() % 2)) {
			return true;
		}
		if (currentBehavior == BehaviorType::ProjectileAttack) {
			return true;
		}
		return false;
	}
	bool readDoubleQCF() {
		return self->getMeterVal() >= self->getMeterMax();
	}
	bool readDoubleQCB() {
		return self->getMeterVal() >= self->getMeterMax();
	}

};

#endif /* AICONTROLLER_H_ */
