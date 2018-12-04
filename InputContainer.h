#ifndef INPUTCONTAINER_H_
#define INPUTCONTAINER_H_

#include <SDL2/SDL.h>

enum InputType {
	UP, DOWN, LEFT, RIGHT, DOWNRIGHT, DOWNLEFT, L, M, H, S

};

enum BehaviorType {
	Test, DoNothing, Push, SpaceAttack, JumpAttack, ProjectileAttack, CounterAttack, Stall, Defend, CloseAttack
};

struct KeyInput {
	int key;
	Uint32 frame;
};



#endif /* INPUTCONTAINER_H_ */
