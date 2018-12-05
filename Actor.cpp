#include "Actor.h"
#include <cassert>
#include "audio.h"
#include <time.h>

void Actor::doSuperFreeze() {

}

void Actor::checkForSpecial1Cancel() {
	//printf("cur attack %d, %d\n", this->currentAttack, attackTypeIsNormal(this->currentAttack));
	if ((!this->isAboveGround()) && (attackTypeIsNormal(this->currentAttack))
			&& (this->specialMove1Window >= 0)) {
		if (this->myController->checkForInput(InputType::L)) {
			this->clearAttack();
			this->beforeStopState = StateType::ATTACK;
			this->currentAttack = AttackType::SPECIAL1L;
			this->actorState = StateType::STOP;
		}
		if (this->myController->checkForInput(InputType::M)) {
			this->clearAttack();
			this->beforeStopState = StateType::ATTACK;
			this->currentAttack = AttackType::SPECIAL1M;
			this->actorState = StateType::STOP;
			//printf("CANCELED\n");
		}
		if (this->myController->checkForInput(InputType::H)) {
			this->clearAttack();
			this->beforeStopState = StateType::ATTACK;
			this->currentAttack = AttackType::SPECIAL1H;
			this->actorState = StateType::STOP;
		}
	}
}

void Actor::checkForSuperCancel() {
	//printf("check for super cancel\n");
	if ((!this->isAboveGround()) && (attackTypeIsSpecial(this->currentAttack))
			&& (this->superMoveWindow >= 0) && (this->superVal.isFull())) {
		//printf("in window\n");
		if (this->myController->checkForInput(InputType::L)) {
			this->clearAttack();
			this->beforeStopState = StateType::ATTACK;
			this->currentAttack = AttackType::SUPER;
			this->actorState = StateType::STOP;
			this->superVal.reset();
		}
		if (this->myController->checkForInput(InputType::M)) {
			this->clearAttack();
			this->beforeStopState = StateType::ATTACK;
			this->currentAttack = AttackType::SUPER;
			this->actorState = StateType::STOP;
			this->superVal.reset();
		}
		if (this->myController->checkForInput(InputType::H)) {
			this->clearAttack();
			this->beforeStopState = StateType::ATTACK;
			this->currentAttack = AttackType::SUPER;
			this->actorState = StateType::STOP;
			this->superVal.reset();
		}
	}
}

Real Actor::hitScaling() {
	Real scale = 1.0;
	scale -= (this->comboCounter + 1) * 0.07;
	if (health / maxHealth <= .25) {
		scale *= 0.8;
	}
	return scale;
}

bool Actor::readQCFwithOrientation() {
	return this->onPlayer2Side ? this->myController->readQCB() : this->myController->readQCF();
}

bool Actor::readDoubleQCFwithOrientation() {
	return this->onPlayer2Side ?
			this->myController->readDoubleQCB() : this->myController->readDoubleQCF();
}

bool Actor::isAboveGround() {
	/*
	 printf("my height %f, ground height %f\n",
	 this->rootNode->convertLocalToWorldPosition(Vector3::ZERO).y, this->groundHeight);
	 */
	return this->rootNode->convertLocalToWorldPosition(Vector3::ZERO).y > this->groundHeight;
}

void Actor::doFall() {
	if (isAboveGround()) {
		this->body->setCollisionFlags(0);
		//this->setCollisionType(CollisionType::COL_NONE);
		Real fallAway = this->onPlayer2Side ? 10 : -10;
		this->body->setLinearVelocity(btVector3(fallAway, -45, 0));
	} else {
		printf("EEEended fall\n");
		//stop falling
		this->actorState = StateType::FREE;
		this->body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
		if (this->health <= 0) {
			this->actorState = StateType::DEAD;
		}
	}
}

bool Actor::isBlocking() {
	if (!((this->actorState == StateType::FREE) || (this->actorState == StateType::BLOCKSTUN))) {
		return false;
	}
	bool blocking = false;
	InputType directionToBlock = this->onPlayer2Side ? InputType::RIGHT : InputType::LEFT;
	InputType forwardDir = this->onPlayer2Side ? InputType::LEFT : InputType::RIGHT; //Can't block if holding forward

	if (this->myController->checkForInput(directionToBlock)) {
		blocking = true;
	}
	if (this->myController->checkForInput(forwardDir)) {
		return false;
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
		//printf("START COLLISION\n");
		/*
		 if (context.body->getCollisionFlags() == btCollisionObject::CF_KINEMATIC_OBJECT) {
		 this->opponent->pushBack(12.0);
		 }
		 */
		CollisionType curCol = ((GameObject *) context.body->getUserPointer())->getCollisionType();
		if (curCol == CollisionType::WALL) {
			if (this->actorState == StateType::JUMPING) {
				this->cancelJump();
				this->health -= 40;
				this->pushBack(-40);
			}
			this->pushBack(-22.0);
			this->health -= 4.0;
			if (this->health <= 0) {
				this->actorState = StateType::DEAD;
			}
		}
		if (curCol == CollisionType::COLLISIONBOX) {
			//printf("collided with %s\n", ((GameObject *) context.body->getUserPointer())->getName().c_str());
			this->opponent->pushBack(12.0);
			this->pushBack(3.0);
		}
		/*
		 if (context.body->getUserIndex() == this->oppHurtType()) {
		 this->moveLock = true;
		 }
		 */
		//printf("check for hit context, %d\n", context.body->getUserIndex());
		//printf("check for hit context, %d to %d\n", ((GameObject *) context.body->getUserPointer())->getCollisionType(), this->oppHitType());
		//CHECK IF I WAS HIT
		//if (context.body->getUserIndex() == this->oppHitType() && !invincible) {
		if (((GameObject *) context.body->getUserPointer())->getCollisionType()
				== this->oppHitType() && !invincible) {
			//printf("I am %s\n", this->name.c_str());
			HitboxData * hbd = &((Hitbox *) context.body->getUserPointer())->myHbd;
			//printf("IS HITBOX ACTIVE? %d\n", hbd->active);
			if (hbd->active) {

				//do was hit
				hbd->active = false;

				//AM I BLOCKING???
				if (this->isBlocking()) {
					auto hitPoint = context.body->getWorldTransform().getOrigin();
					new Spark("Examples/Flare3", this->sceneMgr,
							this->sceneMgr->getRootSceneNode()->createChildSceneNode(),
							this->name + to_string(time(NULL)), this->physics,
							Vector3(hitPoint.getX() / 3.0, hitPoint.getY() / 3.0, 100));
					this->recieveBlock(hbd);
				} else if (this->actorState != StateType::FALLING) {
					auto hitPoint = context.body->getWorldTransform().getOrigin();
					/*
					 printf("SPARK POINT x: %f, y: %f, z %f\n", hitPoint.getX(), hitPoint.getY(),
					 hitPoint.getZ());
					 */
					new Spark("Spark", this->sceneMgr,
							this->sceneMgr->getRootSceneNode()->createChildSceneNode(),
							this->name + to_string(time(NULL)), this->physics,
							Vector3(hitPoint.getX() / 3.0, hitPoint.getY() / 3.0, 100)); //THE COORDINATES ARE AFFECTED BY THE SCALE OF THE NODE
					this->recieveHit(hbd);
				}

			}
		}
	}
}

void Actor::recieveBlock(HitboxData * hbd) {
	assert((this->actorState == StateType::FREE) || (this->actorState == StateType::BLOCKSTUN));
	playSound("../assets/metal.wav", SDL_MIX_MAXVOLUME / 14);
	this->actorState = StateType::BLOCKSTUN;
	this->blockstunFrames = hbd->blockstun;
	this->enterStopState(hbd->blockstop);
	this->opponent->enterStopState(hbd->blockstop);

	this->pushBack(hbd->blockPushback);
	this->opponent->pushBack(hbd->attackBlockPushback);
	this->health -= hbd->blockDmg;
	this->superVal.addVal(hbd->blockMeterGain);

}

void Actor::recieveHit(HitboxData * hbd) {
	playSound("../assets/hit1.wav", SDL_MIX_MAXVOLUME / 2);
	int counterFrames = 0;
//this->beforeStopState = StateType::HITSTUN;
	if (this->actorState == StateType::ATTACK) {
		//reset hurtbox, hitbox, and collision
		/*
		 Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
		 btVector3 targetPos(curPos.x, curPos.y - 500, curPos.z);
		 //this->setBox(this->hurtboxes.at(currentAttack), targetPos);
		 this->setBox(this->hitboxes.at(currentAttack).hitbox, targetPos);
		 this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
		 */
		this->clearAttack();
		//counter status
		counterFrames = counterValue;
	}
	if (this->actorState == StateType::JUMPING) {
		this->cancelJump();
		this->setAnimation("Death1");
		this->enterStopState(hbd->hitstop);
		this->opponent->enterStopState(hbd->hitstop);
		this->health -= hbd->hitDmg * hitScaling() * 1.5;
		this->superVal.addVal(hbd->hitMeterGain);
		return;
	}
	this->actorState = StateType::HITSTUN;
	this->hitstunFrames = hbd->hitstun + counterFrames;
	this->enterStopState(hbd->hitstop);
	this->opponent->enterStopState(hbd->hitstop);
	this->comboCounter += 1;
	this->newHit = true;

	this->pushBack(hbd->hitPushback);
	this->opponent->pushBack(hbd->attackHitPushback);
	this->health -= hbd->hitDmg * hitScaling();
	this->superVal.addVal(hbd->hitMeterGain);

	if (this->health <= 0) {
		this->beforeStopState = StateType::DEAD;
	}
}

void Actor::enterStopState(int stopFrames) {
	if (actorState == StateType::STOP) {
		return;
	}
	if (actorState == StateType::FALLING) {
		this->body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
	}
	this->beforeStopState = this->actorState;
	this->stopFrameCount = stopFrames;
	this->actorState = StateType::STOP;
}

void Actor::exitStopState() {
	if (this->beforeStopState == StateType::FALLING) {
		this->body->setCollisionFlags(0);
	}
	this->actorState = this->beforeStopState;
}

bool Actor::onP1Side() {
	return !this->onPlayer2Side;
}

bool Actor::onP2Side() {
	return this->onPlayer2Side;
}

void Actor::clearAttack() {
	if (currentAttack == AttackType::NONE) {
		return;
	}
	if (Actor::attackTypeIsNormal(this->currentAttack)) {
		//printf("here cur attack is %d\n", this->currentAttack);
		Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
		btVector3 targetPos(curPos.x, curPos.y - 1500, curPos.z);
		this->setBox(this->hitboxes.at(currentAttack)->myHbd.hitbox, targetPos);
		this->hitboxes.at(currentAttack)->myHbd.active = false;
		//printf("done\n");
	}

	this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setTimePosition(0.0);

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

void Actor::animate(const Ogre::FrameEvent& evt) {
	//Actor::animate(evt);

	bool reverse = false;
	bool startJump = false;

	btTransform trans;
	this->body->getMotionState()->getWorldTransform(trans);
	Vector3 ogrePos(rootNode->convertLocalToWorldPosition(Vector3::ZERO));
	btVector3 pos = btVector3(ogrePos.x, ogrePos.y, ogrePos.z);

	//read for special move
	if (this->readQCFwithOrientation()) {
		//this->actorState = StateType::STOP;
		//this->stopFrameCount = 40;
		//this->createSpecialBox();
		this->specialMove1Window = 7;
	}

	if (this->readDoubleQCFwithOrientation()) {
		this->superMoveWindow = 6;
	}

	switch (this->actorState) {
	case StateType::DEAD:
		this->doDeath();
		break;
	case StateType::FALLING:
		this->doFall();
		//printf("FALL POS x: %f, y: %f, z: %f\n", ogrePos.x, ogrePos.y, ogrePos.z);
		break;
	case StateType::JUMPING:
		//printf("jump attack frame count %d\n", this->attackFrameCount);
		//printf("playing animation %s \n", this->playingAnimation.c_str());
		if (this->attackFrameCount == 0) {
			//printf("finished jump attack\n");
			this->cancelJump();
			this->clearAttack();
			//this->actorState = StateType::FALLING;
			break;
		}
		//read inputs for a jump attack
		if (this->myController->checkForInput(InputType::H)) {
			//printf("got command for air heavy\n");
			this->currentAttack = AttackType::AIRHEAVY;
			if (!this->jumpAttack) {
				this->hitboxes.at(currentAttack)->myHbd.active = true;
				this->attackFrameCount = this->jhAttackFrames;
				this->jumpAttack = true;
			}
		}
		//CHANGE STATE TYPE IN JUMP ANIMATION
		this->playJumpAnimation(this->jumpType);
		if (jumpAttack) {
			//printf("STARTING JUMP ATTACK\n");
			this->jumpAttackAnimation();
			this->attackFrameCount -= 1;
		}
		ogrePos = rootNode->convertLocalToWorldPosition(Vector3::ZERO);
		//printf("JUMP  OGREPOS x: %f, y: %f, z: %f\n", ogrePos.x, ogrePos.y, ogrePos.z);
		pos = btVector3(ogrePos.x, ogrePos.y, ogrePos.z);
		break;
	case StateType::BLOCKSTUN:
		this->playBlockAnimation();
		if (this->blockstunFrames == 0) {
			this->actorState = StateType::FREE;
		}
		this->blockstunFrames -= 1;
		break;
	case StateType::HITSTUN:
		//printf("hitstun frames: %d\n", this->hitstunFrames);
		this->playHitAnimation();
		if (this->hitstunFrames == 0) {
			this->actorState = StateType::FREE;
			this->comboCounter = 0;
		}
		this->hitstunFrames -= 1;
		break;
	case StateType::STOP:
		//printf("Stop frame count: %d\n", this->stopFrameCount);
		if (this->stopFrameCount == 0) {
			this->exitStopState();
			//printf("exit actor state%d\n", this->actorState);
		} else {
			//check for cancel
			this->checkForSpecial1Cancel();
			this->checkForSuperCancel();
		}
		this->stopFrameCount -= 1;
		break;
	case StateType::ATTACK:
		//printf("attack reached, attack frame count %d\n", this->attackFrameCount);
		if (this->attackFrameCount == 0) {
			//reset animation
			this->clearAttack();
			break;
		}
		if (this->attackFrameCount == -1) {
			switch (this->currentAttack) {
			case AttackType::LIGHT:
				this->attackFrameCount = this->lAttackFrames;
				this->hitboxes.at(currentAttack)->myHbd.active = true;
				playSound("../assets/swing1.wav", SDL_MIX_MAXVOLUME / 3);
				break;
			case AttackType::MEDIUM:
				this->attackFrameCount = this->mAttackFrames;
				this->hitboxes.at(currentAttack)->myHbd.active = true;
				playSound("../assets/swing1.wav", SDL_MIX_MAXVOLUME / 2);
				break;
			case AttackType::HEAVY:
				this->attackFrameCount = this->hAttackFrames;
				this->hitboxes.at(currentAttack)->myHbd.active = true;
				break;
			case AttackType::SPECIAL1L:
				//projectile with activate on creation
				this->attackFrameCount = this->s1LAttackFrames;
				this->superVal.addVal(10.0);
				break;
			case AttackType::SPECIAL1M:
				this->attackFrameCount = this->s1MAttackFrames;
				this->superVal.addVal(10.0);
				break;
			case AttackType::SPECIAL1H:
				this->attackFrameCount = this->s1HAttackFrames;
				this->superVal.addVal(10.0);
				break;
			case AttackType::SUPER:
				this->attackFrameCount = this->superAttackFrames;
				this->hitboxes.at(currentAttack)->myHbd.active = true;
				break;
			}
		}
		switch (this->currentAttack) {
		case AttackType::LIGHT:
			this->lightAnimation();
			break;
		case AttackType::MEDIUM:
			this->mediumAnimation();
			break;
		case AttackType::HEAVY:
			this->heavyAnimation();
			break;
		case AttackType::SPECIAL1L:
			//printf("entering special animation\n");
			this->special1LAnimation();
			break;
		case AttackType::SPECIAL1M:
			this->special1MAnimation();
			break;
		case AttackType::SPECIAL1H:
			this->special1HAnimation();
			break;
		case AttackType::SUPER:
			this->superAnimation();
			break;
		}
		this->attackFrameCount -= 1;
		break;
	case StateType::FREE:
		//check to see if still needs to fall
		if (this->isAboveGround()) {
			this->actorState = StateType::FALLING;
			break;
		}
		Real move = walkSpeed * evt.timeSinceLastFrame;
		Real moveX = 0;
		//bool holdDown = false;
		if (this->myController->checkForInput(InputType::UP)) {
			startJump = true;
			this->actorState = StateType::JUMPING;
		}
		if (this->myController->checkForInput(InputType::LEFT)) {
			moveX -= move;
			reverse = true;
		}
		if (this->myController->checkForInput(InputType::RIGHT)) {
			moveX += move;
		}
		if (this->myController->checkForInput(InputType::DOWN)) {
			//holdDown = true;
		}
		if (this->myController->checkForInput(InputType::L)) {
			this->actorState = StateType::ATTACK;
			this->currentAttack = AttackType::LIGHT;
			if (this->specialMove1Window > -1 && !this->hasActiveProjectile()) {
				//printf("DO SPECIAL MOVE\n");
				this->currentAttack = AttackType::SPECIAL1L;
				this->specialMove1Window = -1;
			}
			if (this->superMoveWindow > -1 && this->superVal.isFull()) {
				this->superVal.reset();
				this->currentAttack = AttackType::SUPER;
				this->superMoveWindow = -1;
			}
		}
		if (this->myController->checkForInput(InputType::M)) {
			this->actorState = StateType::ATTACK;
			this->currentAttack = AttackType::MEDIUM;
			if (this->specialMove1Window > -1 && !this->hasActiveProjectile()) {
				this->currentAttack = AttackType::SPECIAL1M;
				this->specialMove1Window = -1;
			}
			if (this->superMoveWindow > -1 && this->superVal.isFull()) {
				this->superVal.reset();
				this->currentAttack = AttackType::SUPER;
				this->superMoveWindow = -1;
			}
		}
		if (this->myController->checkForInput(InputType::H)) {
			this->actorState = StateType::ATTACK;
			this->currentAttack = AttackType::HEAVY;
			if (this->specialMove1Window > -1 && !this->hasActiveProjectile()) {
				this->currentAttack = AttackType::SPECIAL1H;
				this->specialMove1Window = -1;
			}
			if (this->superMoveWindow > -1 && this->superVal.isFull()) {
				this->superVal.reset();
				this->currentAttack = AttackType::SUPER;
				this->superMoveWindow = -1;
			}
		}
		//set up jump

		if (this->actorState == StateType::JUMPING) {
			if (moveX > 0) {
				this->jumpType = InputType::RIGHT;
				this->createJumpRightArc();
			} else if (moveX < 0) {
				this->jumpType = InputType::LEFT;
				this->createJumpLeftArc();
			} else {
				//equals 0
				this->jumpType = InputType::UP;
				this->createJumpUpArc();
			}
		}
		/*
		 if(holdDown && moveX) {
		 moveX = 0;
		 }
		 */

		//if walking
		if (moveX) {
			this->setAnimation(this->getWalkName());
		} else {
			//not walking
			this->setAnimation(this->getIdleName());
		}
		pos = btVector3(ogrePos.x + moveX, ogrePos.y, ogrePos.z);
		//play animation
		AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
		Real timeToAdd = reverse ? -evt.timeSinceLastFrame : evt.timeSinceLastFrame;
		as->addTime(evt.timeSinceLastFrame);
		break;
	}
	if (this->actorState != StateType::FALLING) {
		//keep orientation
		btQuaternion rot = trans.getRotation();

		trans.setOrigin(pos);
		trans.setRotation(rot);
		this->body->getMotionState()->setWorldTransform(trans);

		btVector3 btpos = trans.getOrigin();
		Vector3 gloPos(btpos.getX(), btpos.getY(), btpos.getZ());
		//auto relativePos = this->rootNode->convertWorldToLocalPosition(gloPos);
		this->rootNode->setPosition(gloPos);

		btQuaternion btori = trans.getRotation();
		Quaternion ori(btori.w(), btori.x(), btori.y(), btori.z());

		this->rootNode->setOrientation(ori);
	} else {
		/*
		 printf("FALL POS x: %f, y: %f, z: %f\n", trans.getOrigin().getX(), trans.getOrigin().getY(),
		 trans.getOrigin().getZ());
		 */
		AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
		as->addTime(0.003);
		GameObject::animate(evt);
		//AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
		//as->addTime(0.005);
	}

	if (specialMove1Window > -1) {
		this->specialMove1Window -= 1;
	}
	if (superMoveWindow > -1) {
		this->superMoveWindow -= 1;
	}
	this->moveLock = false;
	this->doCollision(evt);
}

