#include "Actor.h"
#include <cassert>

void Actor::doSuperFreeze() {

}

void Actor::checkForSpecial1Cancel() {
	if ((!this->isAboveGround()) && (this->currentAttack != AttackType::NONE)
			&& (this->specialMove1Window >= 0)) {
		for (KeyInput ki : *this->keysHeld) {
			//skip if key is not binded for this ninja
			if (this->keyBinding.find(ki.key) == this->keyBinding.end()) {
				continue;
			}
			if (this->keyBinding.at(ki.key) == InputType::L) {
				this->clearAttack();
				this->beforeStopState = StateType::ATTACK;
				this->currentAttack = AttackType::SPECIAL1L;
			}
			if (this->keyBinding.at(ki.key) == InputType::M) {
				this->clearAttack();
				this->beforeStopState = StateType::ATTACK;
				this->currentAttack = AttackType::SPECIAL1M;
			}
			if (this->keyBinding.at(ki.key) == InputType::H) {
				this->clearAttack();
				this->beforeStopState = StateType::ATTACK;
				this->currentAttack = AttackType::SPECIAL1H;
			}
		}
	}
}

Real Actor::hitScaling() {
	Real scale = 1.0;
	scale -= (this->comboCounter + 1) * 0.06;
	if (health / maxHealth <= .25) {
		scale *= 0.8;
	}
	return scale;
}

bool Actor::keyIsInputType(KeyInput ki, InputType ipt) {
	if (this->keyBinding.find(ki.key) == this->keyBinding.end()) {
		//not mapped
		return false;
	}
	//printf("key is %c\n", ki.key);
	return this->keyBinding.at(ki.key) == ipt;
}

bool Actor::readQCFwithOrientation() {
	return this->onPlayer2Side ? this->readQCB() : this->readQCF();
}

bool Actor::readDoubleQCFwithOrientation() {
	return this->onPlayer2Side ? this->readDoubleQCB() : this->readDoubleQCF();
}

bool Actor::readQCF() {
	if (this->inputBuffer->empty()) {
		return false;
	}
	const int cancelWindow = 7;
	int endInputWindow = inputBuffer->back().frame - cancelWindow;
	bool right = false;
	bool drDown = false;
	bool drRight = false;
	bool down = false;
	Uint32 rightFrame, downRightFrame, downFrame;
	for (auto it = this->inputBuffer->rbegin(); it != this->inputBuffer->rend(); it++) {
		KeyInput cur = *it;
		if (cur.frame < endInputWindow) {
			//printf("INPUTS END\n");
			break;
		}
		if (!right) {
			//printf("checking right\n");
			//check for right
			right = this->keyIsInputType(cur, InputType::RIGHT);
			if (right) {
				rightFrame = cur.frame;
			}
			continue;
		}
		/*
		 //check for both down and right inputs on the same frame
		 if (!(drDown && drRight)) {
		 printf("checking downright\n");
		 if (cur.frame >= rightFrame) {
		 continue;
		 }
		 //down and right have to held on the same frame
		 if ((drDown && !drRight) || (!drDown && drRight)) {
		 if (cur.frame != downRightFrame) {
		 drDown = false;
		 drRight = false;
		 continue;
		 }
		 }

		 if (!drDown) {
		 drDown = this->keyIsInputType(cur, InputType::DOWN);
		 if (drDown) {
		 printf("GOT DRDOWN\n");
		 downRightFrame = cur.frame;
		 }
		 continue;
		 }
		 if (!drRight) {
		 drRight = this->keyIsInputType(cur, InputType::RIGHT);
		 if (drRight) {
		 printf("GOT DRRIGHT\n");
		 downRightFrame = cur.frame;
		 }
		 continue;
		 }

		 }
		 */
		if (!down) {
			//printf("checking down\n");
			//check for down
			down = this->keyIsInputType(cur, InputType::DOWN);
			if (down) {
				//downFrame = cur.frame;
				//fufilled all requirements
				return true;
			}
			continue;
		}
	}
	return false;
}

bool Actor::readDoubleQCF() {
	if (this->inputBuffer->empty()) {
		return false;
	}
	const int cancelWindow = 23;
	int endInputWindow = inputBuffer->back().frame - cancelWindow;
	bool right1 = false;
	bool down1 = false;
	bool right2 = false;
	bool down2 = false;
	Uint32 right1Frame, down1Frame, right2Frame, down2Frame;
	for (auto it = this->inputBuffer->rbegin(); it != this->inputBuffer->rend(); it++) {
		KeyInput cur = *it;
		if (cur.frame < endInputWindow) {
			//printf("INPUTS END\n");
			break;
		}
		if (!right1) {
			//check for right
			right1 = this->keyIsInputType(cur, InputType::RIGHT);
			if (right1) {
				//printf("A\n");
				right1Frame = cur.frame;
			}
			continue;
		}
		if (!down1) {
			down1 = this->keyIsInputType(cur, InputType::DOWN);
			if (down1) {
				//printf("B\n");
				down1Frame = cur.frame;
			}
			continue;
		}
		if (!right2) {
			right2 = this->keyIsInputType(cur, InputType::RIGHT);
			if (right2) {
				//printf("C\n");
				right2Frame = cur.frame;
			}
			continue;
		}
		if (!down2) {
			down2 = this->keyIsInputType(cur, InputType::DOWN);
			if (down2) {
				//printf("D\n");
				return true;
			}
			continue;
		}
	}

	return false;
}

bool Actor::readQCB() {
	if (this->inputBuffer->empty()) {
		return false;
	}
	const int cancelWindow = 7;
	int endInputWindow = inputBuffer->back().frame - cancelWindow;
	bool right = false;
	bool drDown = false;
	bool drRight = false;
	bool down = false;
	Uint32 rightFrame, downRightFrame, downFrame;
	for (auto it = this->inputBuffer->rbegin(); it != this->inputBuffer->rend(); it++) {
		KeyInput cur = *it;
		if (cur.frame < endInputWindow) {
			//printf("INPUTS END\n");
			break;
		}
		if (!right) {
			//check for right
			right = this->keyIsInputType(cur, InputType::LEFT);
			if (right) {
				rightFrame = cur.frame;
			}
			continue;
		}

		if (!down) {
			down = this->keyIsInputType(cur, InputType::DOWN);
			if (down) {
				//downFrame = cur.frame;
				//fufilled all requirements
				return true;
			}
			continue;
		}
	}
	return false;
}

bool Actor::readDoubleQCB() {
	if (this->inputBuffer->empty()) {
		return false;
	}
	const int cancelWindow = 23;
	int endInputWindow = inputBuffer->back().frame - cancelWindow;
	bool left1 = false;
	bool down1 = false;
	bool left2 = false;
	bool down2 = false;
	Uint32 left1Frame, down1Frame, left2Frame, down2Frame;
	for (auto it = this->inputBuffer->rbegin(); it != this->inputBuffer->rend(); it++) {
		KeyInput cur = *it;
		if (cur.frame < endInputWindow) {
			//printf("INPUTS END\n");
			break;
		}
		if (!left1) {
			//check for right
			left1 = this->keyIsInputType(cur, InputType::LEFT);
			if (left1) {
				left1Frame = cur.frame;
			}
			continue;
		}
		if (!down1) {
			down1 = this->keyIsInputType(cur, InputType::DOWN);
			if (down1) {
				down1Frame = cur.frame;
			}
			continue;
		}
		if (!left2) {
			left2 = this->keyIsInputType(cur, InputType::LEFT);
			if (left2) {
				left2Frame = cur.frame;
			}
			continue;
		}
		if (!down2) {
			down2 = this->keyIsInputType(cur, InputType::DOWN);
			if (down2) {
				return true;
			}
			continue;
		}
	}

	return false;
}

bool Actor::isAboveGround() {
	/*
	 printf("my height %f, ground height %f\n",
	 this->rootNode->convertLocalToWorldPosition(Vector3::ZERO).y, this->groundHeight);
	 */
	return this->rootNode->convertLocalToWorldPosition(Vector3::ZERO).y > this->groundHeight + 0.3;
}

void Actor::doFall() {
	if (isAboveGround()) {
		this->body->setCollisionFlags(0);
		Real fallAway = this->onPlayer2Side ? 10 : -10;
		this->body->setLinearVelocity(btVector3(fallAway, -45, 0));
	} else {
		//stop falling
		this->actorState = StateType::FREE;
		this->body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
		if (this->health <= 0) {
			this->actorState = StateType::DEAD;
		}
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
		}
		if (curCol == CollisionType::COLLISIONBOX) {
			//printf("collided with %s\n", ((GameObject *) context.body->getUserPointer())->getName().c_str());
			this->opponent->pushBack(12.0);
			this->pushBack(3.0);
		}
		if (context.body->getUserIndex() == this->oppHurtType()) {
			this->moveLock = true;
		}
		//printf("check for hit context, %d\n", context.body->getUserIndex());
		//CHECK IF I WAS HIT
		if (context.body->getUserIndex() == this->oppHitType() && !invincible) {
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
							this->name + to_string(this->inputBuffer->back().frame), this->physics,
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
							this->name + to_string(this->inputBuffer->back().frame), this->physics,
							Vector3(hitPoint.getX() / 3.0, hitPoint.getY() / 3.0, 100)); //THE COORDINATES ARE AFFECTED BY THE SCALE OF THE NODE
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
	this->opponent->pushBack(hbd->attackBlockPushback);
	this->health -= hbd->blockDmg;

}

void Actor::recieveHit(HitboxData * hbd) {

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
		counterFrames = 5;
	}
	if (this->actorState == StateType::JUMPING) {
		this->cancelJump();
		this->setAnimation("Death1");
		this->enterStopState(hbd->hitstop);
		this->opponent->enterStopState(hbd->hitstop);
		this->health -= hbd->hitDmg * hitScaling() * 1.25;
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

	if (this->health <= 0) {
		this->beforeStopState = StateType::DEAD;
	}
}

void Actor::enterStopState(int stopFrames) {
	if (actorState == StateType::STOP) {
		return;
	}
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

