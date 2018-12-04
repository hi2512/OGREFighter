#ifndef AICONTROLLER_H_
#define AICONTROLLER_H_

#include <iostream>
#include <queue>
#include "InputContainer.h"

enum BehaviorType {
	Test, Push, SpaceAttack, JumpAttack, ProjectileAttack, CounterAttack, Stall, Defend
};

class AIController {
	BehaviorNode * behaviorRoot;
public:
	AIController(std::deque<KeyInput>) {

	}

};

#endif /* AICONTROLLER_H_ */
