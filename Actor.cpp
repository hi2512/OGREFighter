#include "Actor.h"

void Actor::doCollision(const FrameEvent& evt) {
	CollisionContext context;
	BulletContactCallback* thing = new BulletContactCallback(*body, context);
	this->physics->getWorld()->contactTest(body, *thing);
	if (context.hit) {
		if (context.body->getCollisionFlags() == btCollisionObject::CF_KINEMATIC_OBJECT) {
			this->opponent->pushBack(12.0);
		}
		if (context.body->getUserIndex() == this->oppHurtType()) {
			this->moveLock = true;
		}
		//CHECK IF I WAS HIT
		if (context.body->getUserIndex() == this->oppHitType()) {
			printf("I am %s\n", this->name.c_str());
			HitboxData * hbd = (HitboxData *) context.body->getUserPointer();
			printf("hitbox data %f, %f\n", hbd->hitPushback, hbd->blockPushback);
			printf("hitbox data cont %d, %d %d\n", hbd->hitstun, hbd->blockstun, hbd->active);
			if (hbd->active) {
				//do was hit
				hbd->active = false;
				this->recieveHit(hbd);
			}
		}
	}

}

void Actor::recieveHit(HitboxData * hbd) {

	//this->beforeStopState = StateType::HITSTUN;

	this->enterStopState(hbd->hitstop);
	this->opponent->enterStopState(hbd->hitstop);

}

void Actor::enterStopState(int stopFrames) {
	this->beforeStopState = this->actorState;
	this->stopFrameCount = stopFrames;
	this->actorState = StateType::STOP;
}

void Actor::exitStopState() {
	this->actorState = this->beforeStopState;
}

bool Actor::onP1Side() {
	return !this->onPlayer2Side;
}

bool Actor::onP2Side() {
	return this->onPlayer2Side;
}

void Actor::clearAttack() {
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setTimePosition(0.0);
	this->hitboxes.at(currentAttack).active = false;
	this->attackFrameCount = -1;
	this->currentAttack = AttackType::NONE;
	this->actorState = StateType::FREE;
}

void Actor::pushBack(Real dist) {
	dist = this->onPlayer2Side ? dist : -dist;
	btTransform trans;
	this->body->getMotionState()->getWorldTransform(trans);
	btVector3 newPos(trans.getOrigin().getX() + dist, trans.getOrigin().getY(),
			trans.getOrigin().getZ());
	trans.setOrigin(newPos);
	this->body->getMotionState()->setWorldTransform(trans);
	Vector3 ogrePos(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
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

