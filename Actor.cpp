#include "Actor.h"

bool Actor::onP1Side() {
	return !this->onPlayer2Side;
}

bool Actor::onP2Side() {
	return this->onPlayer2Side;
}

void Actor::clearAttack() {
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setTimePosition(0.0);
	this->attackFrameCount = -1;
	this->currentAttack = AttackType::NONE;
	this->actorState = StateType::FREE;
}

void Actor::pushBack(Real dist) {
	btTransform trans;
	this->body->getMotionState()->getWorldTransform(trans);
	btVector3 newPos(trans.getOrigin().getX() + dist, trans.getOrigin().getY(),
			trans.getOrigin().getZ());
	trans.setOrigin(newPos);
	this->body->getMotionState()->setWorldTransform(trans);
	Vector3 ogrePos(trans.getOrigin().getX(), trans.getOrigin().getY(),
			trans.getOrigin().getZ());
	this->rootNode->setPosition(ogrePos);
}

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

void Actor::setP1Orientation() {

	btQuaternion p1orientation(0.0, -0.707, 0.0, 0.707);
	btTransform trans;
	this->body->getMotionState()->getWorldTransform(trans);

	trans.setRotation(p1orientation);
	this->body->getMotionState()->setWorldTransform(trans);
	btQuaternion btori = trans.getRotation();
	Quaternion ori(btori.w(), btori.x(), btori.y(), btori.z());

	this->rootNode->setOrientation(ori);

	this->onPlayer2Side = false;

}

void Actor::setP2Orientation() {

	btQuaternion p2orientation(0.0, -0.707, 0.0, -0.707);
	btTransform trans;
	this->body->getMotionState()->getWorldTransform(trans);

	trans.setRotation(p2orientation);
	this->body->getMotionState()->setWorldTransform(trans);
	btQuaternion btori = trans.getRotation();
	Quaternion ori(btori.w(), btori.x(), btori.y(), btori.z());

	this->rootNode->setOrientation(ori);

	this->onPlayer2Side = true;

}

