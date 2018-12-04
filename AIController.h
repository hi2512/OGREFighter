#ifndef AICONTROLLER_H_
#define AICONTROLLER_H_

#include <iostream>
#include <queue>
#include "InputContainer.h"
#include "ActorController.h"
#include <set>
#include "Actor.h"
#include "BehaviorNode.h"

enum BehaviorType {
	Test, DoNothing, Push, SpaceAttack, JumpAttack, ProjectileAttack, CounterAttack, Stall, Defend
};

class AIController: public ActorController {
protected:
	GameState * gs;
	BehaviorNode * behaviorRoot;
	std::set<InputType> activeInputs;
	Actor * self;
	Actor * opponent;
public:
	AIController(Actor * me, Actor * opp, GameState * game) :
			self(me), opponent(opp), gs(game) {
		behaviorRoot = new CloseToCenterDistanceNode(self, opponent, gs, 20.0);
		behaviorRoot->setLeft(new DoNothingNode(self, opponent, gs));
		behaviorRoot->setRight(new PushNode(self, opponent, gs));
	}
	bool checkForInput(InputType it) {

		return false;
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
