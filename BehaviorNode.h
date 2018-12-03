#ifndef BEHAVIORNODE_H_
#define BEHAVIORNODE_H_

#include "AIController.h"
#include "state.h"

class BehaviorNode {

protected:
	BehaviorType behavior = BehaviorType::Test;
	BehaviorNode * l;
	BehaviorNode * r;

public:
	BehaviorNode() {
	}
	BehaviorNode(BehaviorType bt) :
			behavior(bt) {
	}
	~BehaviorNode() {
	}
	void setLeft(BehaviorNode * left) {
		l = left;
	}
	void setRight(BehaviorNode * right) {
		r = right;
	}
	virtual BehaviorNode * test(GameState * gs) {
		return rand() % 2 ? l : r;
	}
	BehaviorType decide(GameState * gs) {
		if(behavior == BehaviorType::Test) {
			return test(gs)->decide(gs);
		} else {
			return behavior;
		}
	}

};

class TimeNode: public BehaviorNode {
	BehaviorNode * test(GameState * gs) {
		if(gs->getTime() < 15) {
			return l;
		} else {
			return r;
		}
	}
};

#endif /* BEHAVIORNODE_H_ */
