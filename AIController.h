#ifndef AICONTROLLER_H_
#define AICONTROLLER_H_

enum BehaviorType {
	Test, Push, SpaceAttack, JumpAttack, ProjectileAttack, CounterAttack, Stall, Defend
};

class AIController {
	BehaviorNode * behaviorRoot;

};

#endif /* AICONTROLLER_H_ */
