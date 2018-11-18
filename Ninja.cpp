#include <Ogre.h>
#include "physics.h"
#include <OgreApplicationContext.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include "Ninja.h"
#include "audio.h"

using namespace Ogre;
using namespace std;

void Ninja::createLightBox() {

}

void Ninja::createMediumBox() {
	btCollisionObject * hbox = new btPairCachingGhostObject();
	hbox->setCollisionShape(new btBoxShape(btVector3(50, 50, 50)));

	btTransform trans;
	trans.setIdentity();
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	btVector3 pos(curPos.x, curPos.y - 500, curPos.z);
	trans.setOrigin(pos);
	hbox->setWorldTransform(trans);
	hbox->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	physics->dynamicsWorld->addCollisionObject(hbox);
	HitboxData hbd { hbox, 8.0, 5.0, 30, 25, 10, 10, false};
	this->hitboxes.insert(pair<AttackType, HitboxData>(AttackType::MEDIUM, hbd));
	hbox->setUserPointer(&this->hitboxes.at(AttackType::MEDIUM));
	hbox->setUserIndex(this->myHitType());

	//SET HURTBOX
	btCollisionObject * htbox = new btPairCachingGhostObject();
	htbox->setCollisionShape(new btBoxShape(btVector3(75, 75, 75)));

	btTransform trans2;
	trans2.setIdentity();
	btVector3 pos2(curPos.x, curPos.y - 500, curPos.z);
	trans2.setOrigin(pos2);
	htbox->setWorldTransform(trans2);
	htbox->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	physics->dynamicsWorld->addCollisionObject(htbox);
	this->hurtboxes.insert(pair<AttackType, btCollisionObject *>(AttackType::MEDIUM, htbox));
	htbox->setUserIndex(this->myHurtType());

}

void Ninja::createHeavyBox() {
	btCollisionObject * hbox = new btPairCachingGhostObject();
	hbox->setCollisionShape(new btBoxShape(btVector3(100, 50, 50)));

	btTransform trans;
	trans.setIdentity();
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	btVector3 pos(curPos.x, curPos.y - 500, curPos.z);
	trans.setOrigin(pos);
	hbox->setWorldTransform(trans);
	hbox->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	physics->dynamicsWorld->addCollisionObject(hbox);
	HitboxData hbd { hbox, 8.0, 5.0, 50, 10, 10, 10, false};
	this->hitboxes.insert(pair<AttackType, HitboxData>(AttackType::HEAVY, hbd));
	auto re = &this->hitboxes.at(AttackType::HEAVY);
	printf("hitbox data %f, %f", re->hitPushback, re->blockPushback);
	printf("hitbox data %f, %f", hbd.hitPushback, hbd.blockPushback);
	hbox->setUserPointer(&this->hitboxes.at(AttackType::HEAVY));
	hbox->setUserIndex(this->myHitType());

	//SET HURTBOX
	btCollisionObject * htbox = new btPairCachingGhostObject();
	htbox->setCollisionShape(new btBoxShape(btVector3(150, 75, 75)));

	btTransform trans2;
	trans2.setIdentity();
	btVector3 pos2(curPos.x, curPos.y - 500, curPos.z);
	trans2.setOrigin(pos2);
	htbox->setWorldTransform(trans2);
	htbox->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	physics->dynamicsWorld->addCollisionObject(htbox);
	this->hurtboxes.insert(pair<AttackType, btCollisionObject *>(AttackType::HEAVY, htbox));
	htbox->setUserIndex(this->myHurtType());
}

void Ninja::playHitAnimation() {
	this->setAnimation("Death1");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->addTime(0.002);
}

void Ninja::heavyAnimation() {
	this->setAnimation("Kick");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.011);

	btTransform trans;
	btCollisionObject * hbox = this->hitboxes.at(currentAttack).hitbox;
	trans = hbox->getWorldTransform();
	auto tv = trans.getOrigin();
	//printf("hitbox pos %f, %f, %f\n", tv.getX(), tv.getY(), tv.getZ());
	btTransform trans2;
	btCollisionObject * htbox = this->hurtboxes.at(currentAttack);
	trans2 = htbox->getWorldTransform();

	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Real xPos = curPos.x + 400;

	Real yPos = curPos.y + 10;
	std::vector<btVector3> hitFrames;
	if (this->onP1Side()) {
		hitFrames.push_back(btVector3(xPos, yPos + 20, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 20, curPos.z));
		hitFrames.push_back(btVector3(xPos + 20, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos + 20, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos + 20, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos + 20, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos + 20, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
	} else {
		xPos = curPos.x - 400;
		hitFrames.push_back(btVector3(xPos, yPos + 20, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 20, curPos.z));
		hitFrames.push_back(btVector3(xPos - 20, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos - 20, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos - 20, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos - 20, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos - 20, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
	}

	btVector3 pos(curPos.x, curPos.y - 500, curPos.z);
	btVector3 hurtpos(curPos.x, curPos.y - 500, curPos.z);

	int frameTime = -this->attackFrameCount + 50;
	//printf("frametime: %d\n", frameTime);
	if (frameTime >= 0 && frameTime <= 8) {
		pos = hitFrames.at(frameTime);
	}
	if (frameTime >= -40 && frameTime <= 12) {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 3));
	} else {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
	}
	//hurtbox timing
	if (frameTime >= -20 && frameTime <= 12) {
		hurtpos = btVector3(xPos, yPos, curPos.z);
	}

	trans.setOrigin(pos);
	hbox->setWorldTransform(trans);

	trans2.setOrigin(hurtpos);
	htbox->setWorldTransform(trans2);
}

void Ninja::mediumAnimation() {
	this->setAnimation("Attack3");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.012);

	btTransform trans;
	btCollisionObject * hbox = this->hitboxes.at(currentAttack).hitbox;
	trans = hbox->getWorldTransform();

	btTransform trans2;
	btCollisionObject * htbox = this->hurtboxes.at(currentAttack);
	trans2 = htbox->getWorldTransform();

	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Real xPos = curPos.x + 200;

	Real yPos = curPos.y + 80;
	std::vector<btVector3> hitFrames;
	if (this->onP1Side()) {
		hitFrames.push_back(btVector3(xPos, yPos + 20, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 20, curPos.z));
		hitFrames.push_back(btVector3(xPos + 80, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos + 80, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos + 80, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
	} else {
		xPos = curPos.x - 200;
		hitFrames.push_back(btVector3(xPos, yPos + 20, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 20, curPos.z));
		hitFrames.push_back(btVector3(xPos - 80, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos - 80, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos - 80, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
	}

	btVector3 pos(curPos.x, curPos.y - 500, curPos.z);
	btVector3 hurtpos(curPos.x, curPos.y - 500, curPos.z);

	int frameTime = -this->attackFrameCount + 20;
	//printf("frametime: %d\n", frameTime);
	if (frameTime >= 0 && frameTime <= 6) {
		pos = hitFrames.at(frameTime);
	}
	if (frameTime >= -10 && frameTime <= 10) {
		hurtpos = btVector3(xPos, yPos, curPos.z);
	}
	trans.setOrigin(pos);
	hbox->setWorldTransform(trans);

	trans2.setOrigin(hurtpos);
	htbox->setWorldTransform(trans2);
}

void Ninja::animate(const Ogre::FrameEvent& evt) {
	//Actor::animate(evt);

	/*
	CollisionContext context;
	BulletContactCallback* thing = new BulletContactCallback(*body, context);
	this->physics->getWorld()->contactTest(body, *thing);
	*/

	bool reverse = false;

	btTransform trans;
	this->body->getMotionState()->getWorldTransform(trans);
	Vector3 ogrePos(rootNode->convertLocalToWorldPosition(Vector3::ZERO));
	/*
	 LogManager::getSingleton().logMessage("OGREPOS");
	 LogManager::getSingleton().logMessage(to_string(ogrePos.x));
	 LogManager::getSingleton().logMessage(to_string(ogrePos.y));
	 LogManager::getSingleton().logMessage(to_string(ogrePos.z));
	 */

	btVector3 pos = btVector3(ogrePos.x, ogrePos.y, ogrePos.z);
	switch (this->actorState) {
	case StateType::HITSTUN:
		printf("hitstun frames: %d\n", this->hitstunFrames);
		this->playHitAnimation();
		if(this->hitstunFrames == 0) {
			this->actorState = StateType::FREE;
		}
		this->hitstunFrames -= 1;
		break;
	case StateType::STOP:
		printf("Stop frame count: %d\n", this->stopFrameCount);
		if(this->stopFrameCount == 0) {
			this->exitStopState();
		}
		this->stopFrameCount -= 1;
		break;
	case StateType::ATTACK:
		if (this->attackFrameCount == 0) {
			//reset animation
			this->clearAttack();
			break;
		}
		if (this->attackFrameCount == -1) {
			switch (this->currentAttack) {
			case AttackType::LIGHT:
				this->attackFrameCount = this->lAttackFrames;
				break;
			case AttackType::MEDIUM:
				this->attackFrameCount = this->mAttackFrames;
				break;
			case AttackType::HEAVY:
				this->attackFrameCount = this->hAttackFrames;
				break;
			case AttackType::SPECIAL:
				this->attackFrameCount = this->sAttackFrames;
				break;
			}
		}
		switch (this->currentAttack) {
		case AttackType::LIGHT:

			break;
		case AttackType::MEDIUM:
			this->mediumAnimation();
			break;
		case AttackType::HEAVY:
			this->heavyAnimation();
			break;
		}
		this->attackFrameCount -= 1;
		break;
	case StateType::FREE:
		Real move = walkSpeed * evt.timeSinceLastFrame;
		Real moveX = 0;
		for (KeyInput ki : *this->keysHeld) {
			//skip if key is not binded for this ninja
			if (this->keyBinding.find(ki.key) == this->keyBinding.end()) {
				continue;
			}
			if (this->keyBinding.at(ki.key) == InputType::LEFT) {
				moveX -= move;
				reverse = true;
			}
			if (this->keyBinding.at(ki.key) == InputType::RIGHT) {
				moveX += move;
			}
			if (this->keyBinding.at(ki.key) == InputType::M) {
				this->actorState = StateType::ATTACK;
				this->currentAttack = AttackType::MEDIUM;
				this->hitboxes.at(currentAttack).active = true;
			}
			if (this->keyBinding.at(ki.key) == InputType::H) {
				this->actorState = StateType::ATTACK;
				this->currentAttack = AttackType::HEAVY;
				this->hitboxes.at(currentAttack).active = true;
			}
		}
		//if walking
		if (moveX) {
			this->setAnimation("Walk");
		} else {
			//not walking
			this->setAnimation("Idle1");
		}
		//check if movement locked
		if (moveLock) {
			printf("MOVE LOCKED\n");
			moveX = 0;
			this->setAnimation("Block");
			AnimationState * asb = this->geom->getAnimationState(this->playingAnimation);
			asb->addTime(0.005);
			break;
		}
		pos = btVector3(ogrePos.x + moveX, ogrePos.y, ogrePos.z);
		//play animation
		AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
		Real timeToAdd = reverse ? -evt.timeSinceLastFrame : evt.timeSinceLastFrame;
		as->addTime(evt.timeSinceLastFrame);
		break;
	}

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

	this->moveLock = false;
	this->doCollision(evt);
}

