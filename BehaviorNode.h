#ifndef BEHAVIORNODE_H_
#define BEHAVIORNODE_H_

#include "AIController.h"
#include "state.h"

class BehaviorNode {

protected:
	BehaviorType behavior = BehaviorType::Test;
	BehaviorNode * t;
	BehaviorNode * f;
	Actor * myPlayer;
	Actor * opponent;
	GameState * gs;
	virtual BehaviorNode * test() {
		return rand() % 2 ? t : f;
	}
public:
	BehaviorNode(Actor * me, Actor * opp, GameState * game) :
			myPlayer(me), opponent(opp), gs(game) {
	}
	BehaviorNode(Actor * me, Actor * opp, GameState * game, BehaviorType bt) :
			myPlayer(me), opponent(opp), behavior(bt), gs(game) {
	}
	~BehaviorNode() {
	}
	void setLeft(BehaviorNode * left) {
		t = left;
	}
	void setRight(BehaviorNode * right) {
		f = right;
	}
	BehaviorNode * getLeft() {
		return t;
	}
	BehaviorNode * getRight() {
		return f;
	}
	BehaviorType decide() {
		if (behavior == BehaviorType::Test) {
			return test()->decide();
		} else {
			return behavior;
		}
	}

};

class OutOfTimeNode: public BehaviorNode {
	int timeThreshold;
	OutOfTimeNode(Actor * me, Actor * opp, GameState * game, int time) :
			BehaviorNode(me, opp, game), timeThreshold(time) {
	}
public:
	BehaviorNode * test() {
		if (gs->getTime() < timeThreshold) {
			return t;
		} else {
			return f;
		}
	}
};

class NearOpponentDistanceNode: public BehaviorNode {
protected:
	Real distanceThreshold;
	BehaviorNode * test() {
		auto myDist = myPlayer->getRootNode()->convertLocalToWorldPosition(Vector3::ZERO);
		auto oppDist = opponent->getRootNode()->convertLocalToWorldPosition(Vector3::ZERO);
		if (myDist.distance(oppDist) < distanceThreshold) {
			return t;
		} else {
			return f;
		}
	}
public:
	NearOpponentDistanceNode(Actor * me, Actor * opp, GameState * game, Real dist) :
			BehaviorNode(me, opp, game), distanceThreshold(dist) {
	}
};

class FarOpponentDistanceNode: public BehaviorNode {
protected:
	Real distanceThreshold;
	BehaviorNode * test() {
		auto myDist = myPlayer->getRootNode()->convertLocalToWorldPosition(Vector3::ZERO);
		auto oppDist = opponent->getRootNode()->convertLocalToWorldPosition(Vector3::ZERO);
		if (myDist.distance(oppDist) > distanceThreshold) {
			return t;
		} else {
			return f;
		}
	}
public:
	FarOpponentDistanceNode(Actor * me, Actor * opp, GameState * game, Real dist) :
			BehaviorNode(me, opp, game), distanceThreshold(dist) {
	}
};

class CloseToCenterDistanceNode: public BehaviorNode {
protected:
	Real distanceThreshold;
	BehaviorNode * test() {
		if (abs(myPlayer->getRootNode()->convertLocalToWorldPosition(Vector3::ZERO).x)
				< distanceThreshold) {
			return t;
		} else {
			return f;
		}

	}
public:
	CloseToCenterDistanceNode(Actor * me, Actor * opp, GameState * game, Real dist) :
			BehaviorNode(me, opp, game), distanceThreshold(dist) {
	}

};

class FarFromCenterDistanceNode: public BehaviorNode {
protected:
	Real distanceThreshold;
	BehaviorNode * test() {
		if (abs(myPlayer->getRootNode()->convertLocalToWorldPosition(Vector3::ZERO).x)
				> distanceThreshold) {
			return t;
		} else {
			return f;
		}

	}
public:
	FarFromCenterDistanceNode(Actor * me, Actor * opp, GameState * game, Real dist) :
			BehaviorNode(me, opp, game), distanceThreshold(dist) {
	}

};

class HealthLeadNode: public BehaviorNode {
protected:
	Real healthThreshold;
	BehaviorNode * test() {
		Real myHealth = myPlayer->getHealth();
		Real oppHealth = opponent->getHealth();
		if ((myHealth - oppHealth) > healthThreshold) {
			return t;
		} else {
			return f;
		}
	}
public:
	HealthLeadNode(Actor * me, Actor * opp, GameState * game, Real health) :
			BehaviorNode(me, opp, game), healthThreshold(health) {
	}
};

class HealthTrailNode: public BehaviorNode {
protected:
	Real healthThreshold;
	BehaviorNode * test() {
		Real myHealth = myPlayer->getHealth();
		Real oppHealth = opponent->getHealth();
		if ((oppHealth - myHealth) > healthThreshold) {
			return t;
		} else {
			return f;
		}
	}
public:
	HealthTrailNode(Actor * me, Actor * opp, GameState * game, Real health) :
			BehaviorNode(me, opp, game), healthThreshold(health) {
	}
};

class OpponentIsJumpingNode: public BehaviorNode {
protected:
	BehaviorNode * test() {
		if (opponent->getRootNode()->getPosition().y > 300) {
			return t;
		} else {
			return f;
		}
	}
public:
	OpponentIsJumpingNode(Actor * me, Actor * opp, GameState * game) :
			BehaviorNode(me, opp, game) {
	}

};

class PushNode: public BehaviorNode {
public:
	PushNode(Actor * me, Actor * opp, GameState * game) :
			BehaviorNode(me, opp, game, BehaviorType::Push) {
	}
};

class SpaceAttackNode: public BehaviorNode {
public:
	SpaceAttackNode(Actor * me, Actor * opp, GameState * game) :
			BehaviorNode(me, opp, game, BehaviorType::SpaceAttack) {
	}
};

class CounterAttackNode: public BehaviorNode {
public:
	CounterAttackNode(Actor * me, Actor * opp, GameState * game) :
			BehaviorNode(me, opp, game, BehaviorType::CounterAttack) {
	}
};

class StallNode: public BehaviorNode {
public:
	StallNode(Actor * me, Actor * opp, GameState * game) :
			BehaviorNode(me, opp, game, BehaviorType::Stall) {
	}
};

class DefendNode: public BehaviorNode {
public:
	DefendNode(Actor * me, Actor * opp, GameState * game) :
			BehaviorNode(me, opp, game, BehaviorType::Defend) {
	}
};

class DoNothingNode: public BehaviorNode {
public:
	DoNothingNode(Actor * me, Actor * opp, GameState * game) :
			BehaviorNode(me, opp, game, BehaviorType::DoNothing) {
	}
};

class ProjectileAttackNode: public BehaviorNode {
public:
	ProjectileAttackNode(Actor * me, Actor * opp, GameState * game) :
			BehaviorNode(me, opp, game, BehaviorType::ProjectileAttack) {
	}
};

class CloseAttackNode: public BehaviorNode {
public:
	CloseAttackNode(Actor * me, Actor * opp, GameState * game) :
			BehaviorNode(me, opp, game, BehaviorType::CloseAttack) {
	}
};

#endif /* BEHAVIORNODE_H_ */
