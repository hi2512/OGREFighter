#include "Actor.h"

void Actor::setAnimation(String animation) {
	if (playingAnimation != animation) {
		this->geom->getAnimationState(playingAnimation)->setEnabled(false);
		this->playingAnimation = animation;
	}
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	if (!as->getEnabled()) {
		as->setEnabled(true);
	}

}

