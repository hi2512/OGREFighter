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
				sleep(0.7);
				currentBehavior = behaviorRoot->decide();
				sleepLock.unlock();
			} else {
				break;
			}
		}
	}
	void doBehavior() {
		activeInputs.clear();
		switch (currentBehavior) {
		case BehaviorType::ProjectileAttack: {
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
			activeInputs.insert(InputType::L);
			break;
		case BehaviorType::SpaceAttack:
			activeInputs.insert(InputType::M);
			break;
		case BehaviorType::DoNothing:
			break;
		case BehaviorType::Push:
			//walk forward
			activeInputs.insert(self->onP2Side() ? InputType::LEFT : InputType::RIGHT);
			break;
		case BehaviorType::Stall:
			activeInputs.insert(self->onP2Side() ? InputType::RIGHT : InputType::LEFT);
			if ((rand() % 100 > 96) && (abs(self->getRootNode()->getPosition().x) < 1000)) {
				activeInputs.insert(InputType::UP);
			}
			break;
		}
	}
public:
	AIController(Actor * me, Actor * opp, GameState * game) :
			self(me), opponent(opp), gs(game) {
		behaviorRoot = new OutOfTimeNode(self, opponent, gs, 15);
		behaviorRoot->setLeft(new HealthLeadNode(self, opponent, gs, 150));
		behaviorRoot->setRight(new OpponentIsJumpingNode(self, opponent, gs));
		auto cur = behaviorRoot->getLeft();
		cur->setLeft(new StallNode(self, opponent, gs));
		cur->setRight(new FarOpponentDistanceNode(self, opponent, gs, 500));
		cur = cur->getRight();
		cur->setLeft(new PushNode(self, opponent, gs));
		cur->setRight(new SpaceAttackNode(self, opponent, gs));

		cur = behaviorRoot->getRight();
		cur->setLeft(new SpaceAttackNode(self, opponent, gs));
		cur->setRight(new NearOpponentDistanceNode(self, opponent, gs, 270));
		cur = cur->getRight();
		cur->setLeft(new CloseAttackNode(self, opponent, gs));
		cur->setRight(new FarFromCenterDistanceNode(self, opponent, gs, 300.0));
		cur = cur->getRight();
		cur->setLeft(new PushNode(self, opponent, gs));
		cur->setRight(new BehaviorNode(self, opponent, gs));
		cur = cur->getRight();
		cur->setLeft(new ProjectileAttackNode(self, opponent, gs));
		cur->setRight(new DoNothingNode(self, opponent, gs));
		stateChecker = new std::thread(&AIController::testForBehavior, this);

	}
	~AIController() {
		printf("deleting aicontroller\n");
		sleepLock.lock();
		//printf("delete has lock\n");
		stateChecker->join();
		//printf("joined\n");
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
			return !self->hasActiveProjectile();
		}
		return false;
	}
	bool readQCB() {
		if (currentBehavior == BehaviorType::SpaceAttack && (rand() % 2)) {
			return true;
		}
		if (currentBehavior == BehaviorType::ProjectileAttack) {
			return !self->hasActiveProjectile();
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
