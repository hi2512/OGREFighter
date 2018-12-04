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
	std::mutex deleteLock;
	std::condition_variable cond;
	void testForBehavior() {
		while (1) {
			if (sleepLock.try_lock()) {
				sleep(0.5);
				currentBehavior = behaviorRoot->decide();
				sleepLock.unlock();
			} else {
				printf("break\n");
				break;
			}
		}
	}
	void doBehavior() {
		switch (currentBehavior) {
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
		behaviorRoot = new CloseToCenterDistanceNode(self, opponent, gs, 20.0);
		behaviorRoot->setLeft(new DoNothingNode(self, opponent, gs));
		behaviorRoot->setRight(new PushNode(self, opponent, gs));
		stateChecker = new std::thread(&AIController::testForBehavior, this);

	}
	~AIController() {
		printf("deleting aicontroller\n");
		sleepLock.lock();
		stateChecker->join();
		printf("joined\n");
	}
	bool checkForInput(InputType it) {
		doBehavior();
		return activeInputs.count(it);
	}
	bool readQCF() {
		return false;
	}
	bool readQCB() {
		return false;
	}
	bool readDoubleQCF() {
		return false;
	}
	bool readDoubleQCB() {
		return false;
	}

};

#endif /* AICONTROLLER_H_ */
