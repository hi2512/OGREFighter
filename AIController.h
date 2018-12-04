#ifndef AICONTROLLER_H_
#define AICONTROLLER_H_

#include <iostream>
#include <queue>
#include "InputContainer.h"
#include "ActorController.h"
#include <set>
#include "Actor.h"
#include "BehaviorNode.h"


class AIController: public ActorController {
protected:
	GameState * gs;
	BehaviorType currentBehavior = BehaviorType::DoNothing;
	BehaviorNode * behaviorRoot;
	std::set<InputType> activeInputs;
	Actor * self;
	Actor * opponent;
	std::thread * stateChecker;
	void testForBehavior() {
		while (1) {
			sleep(0.5);
			currentBehavior =  behaviorRoot->decide();
		}
	}
	void doBehavior() {
		switch(currentBehavior) {
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
		stateChecker->join();
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
