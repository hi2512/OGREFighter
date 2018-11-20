#include "Actor.h"
#include <cassert>


bool Actor::isAboveGround() {
	/*
	printf("my height %f, ground height %f\n",
			this->rootNode->convertLocalToWorldPosition(Vector3::ZERO).y, this->groundHeight);
			*/
	return this->rootNode->convertLocalToWorldPosition(Vector3::ZERO).y > this->groundHeight + 0.1;
}

void Actor::doFall() {
	if (isAboveGround()) {
		this->body->setCollisionFlags(0);
		this->body->setLinearVelocity(btVector3(0, -300, 0));
	} else {
		//stop falling
		this->actorState = StateType::FREE;
		this->body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
	}
}

bool Actor::isBlocking() {
	if (this->actorState != StateType::FREE) {
		return false;
	}
	bool blocking = false;
	InputType directionToBlock = this->onPlayer2Side ? InputType::RIGHT : InputType::LEFT;
	InputType forwardDir = this->onPlayer2Side ? InputType::LEFT : InputType::RIGHT; //Can't block if holding forward
	for (KeyInput ki : *this->keysHeld) {
		if (this->keyBinding.find(ki.key) == this->keyBinding.end()) {
			continue;
		}
		if (this->keyBinding.at(ki.key) == directionToBlock) {
			blocking = true;
		}
		if (this->keyBinding.at(ki.key) == forwardDir) {
			return false;
		}
	}
	return blocking;
}

void Actor::setBox(btCollisionObject * box, const btVector3& targetPos) {
	btTransform trans;
	trans = box->getWorldTransform();
	trans.setOrigin(targetPos);
	box->setWorldTransform(trans);
}

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
			//printf("I am %s\n", this->name.c_str());
			HitboxData * hbd = (HitboxData *) context.body->getUserPointer();
			if (hbd->active) {

				//do was hit
				hbd->active = false;

				//AM I BLOCKING???
				if (this->isBlocking()) {
					this->recieveBlock(hbd);
				} else if(this->actorState != StateType::FALLING) {
					this->recieveHit(hbd);
				}

			}
		}
	}

}

void Actor::recieveBlock(HitboxData * hbd) {
	assert(this->actorState == StateType::FREE);
	this->actorState = StateType::BLOCKSTUN;
	this->blockstunFrames = hbd->blockstun;
	this->enterStopState(hbd->blockstop);
	this->opponent->enterStopState(hbd->blockstop);

	this->pushBack(hbd->blockPushback);

}

void Actor::recieveHit(HitboxData * hbd) {

	//this->beforeStopState = StateType::HITSTUN;

	if (this->actorState == StateType::ATTACK) {
		//reset hurtbox, hitbox, and collision
		Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
		btVector3 targetPos(curPos.x, curPos.y - 500, curPos.z);
		//this->setBox(this->hurtboxes.at(currentAttack), targetPos);
		this->setBox(this->hitboxes.at(currentAttack).hitbox, targetPos);
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));

		this->clearAttack();
	}
	if(this->actorState == StateType::JUMPING) {
		this->cancelJump();
		this->setAnimation("Death1");
		this->enterStopState(hbd->hitstop);
		this->opponent->enterStopState(hbd->hitstop);
		return;
	}
	this->actorState = StateType::HITSTUN;
	this->hitstunFrames = hbd->hitstun;
	this->enterStopState(hbd->hitstop);
	this->opponent->enterStopState(hbd->hitstop);
	this->comboCounter += 1;
	this->newHit = true;

	this->pushBack(hbd->hitPushback);

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
		auto as = this->geom->getAnimationState(playingAnimation);
		as->setEnabled(false);
		as->setTimePosition(0);
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

