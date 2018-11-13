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

void Ninja::createHeavyBox() {

	/*
	btCollisionObject * hbox  = new btGhostObject();
	hbox->setCollisionShape(new btBoxShape(btVector3(10, 10, 10)));
	hbox->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	btVector3 pos(curPos.x, curPos.y + 50, curPos.z);
	btTransform trans;
	trans.setIdentity();
	trans.setOrigin(pos);
	hbox->setWorldTransform(trans);
	int collidesWith = this->isPlayer2 ? CollisionType::HURTBOX_P1 : CollisionType::HURTBOX_P2;
	physics->getWorld()->addCollisionObject(hbox);
	//this->hitboxes.insert(pair<AttackType, btGhostObject *>(AttackType::HEAVY, hbox));
	 */
	btCollisionObject * hbox = new btGhostObject();
	hbox->setCollisionShape(new btBoxShape(btVector3(50, 50, 50)));

	btTransform trans;
	trans.setIdentity();
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	btVector3 pos(curPos.x, curPos.y - 500, curPos.z);
	trans.setOrigin(pos);
	hbox->setWorldTransform(trans);
	hbox->setCollisionFlags(CollisionType::HITBOX);
	physics->dynamicsWorld->addCollisionObject(hbox);
	this->hitboxes.insert(pair<AttackType, btCollisionObject *>(AttackType::HEAVY, hbox));


}

void Ninja::heavyAnimation() {
	this->setAnimation("Attack3");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->addTime(0.012);

	btTransform trans;
	btCollisionObject * hbox = this->hitboxes.at(currentAttack);
	trans = hbox->getWorldTransform();
	auto tv = trans.getOrigin();
	printf("hitbox pos %f, %f, %f\n", tv.getX(), tv.getY(), tv.getZ());
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	btVector3 pos(curPos.x + 200, curPos.y + 80, curPos.z);

	trans.setOrigin(pos);
	hbox->setWorldTransform(trans);
}

void Ninja::animate(const Ogre::FrameEvent& evt) {
	//Actor::animate(evt);

	CollisionContext context;
	BulletContactCallback* thing = new BulletContactCallback(*body, context);
	this->physics->getWorld()->contactTest(body, *thing);

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
	case StateType::ATTACK:
		if (this->attackFrameCount == 0) {
			//reset animation
			AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
			as->setTimePosition(0.0);
			this->attackFrameCount = -1;
			this->currentAttack = AttackType::NONE;
			this->actorState = StateType::FREE;
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
			if (this->keyBinding.at(ki.key) == InputType::H) {
				this->actorState = StateType::ATTACK;
				this->currentAttack = AttackType::HEAVY;
			}
		}
		//if walking
		if (moveX) {
			this->setAnimation("Walk");
		} else {
			//not walking
			this->setAnimation("Idle1");
		}
		//pushback if walk into each other
		if (context.hit && context.body->getCollisionFlags() == CollisionType::COLLISIONBOX) {
			printf("col flags 0x%x", context.body->getCollisionFlags());
			moveX = -moveX * 3;
		}

		if(context.hit && context.body->getCollisionFlags() == CollisionType::HITBOX) {
			printf("COllision box collided with hitbox\n");
		}

		pos = btVector3(ogrePos.x + moveX, ogrePos.y, ogrePos.z);

		//play animation
		AnimationState * as = this->geom->getAnimationState(
				this->playingAnimation);

		Real timeToAdd =
				reverse ? -evt.timeSinceLastFrame : evt.timeSinceLastFrame;

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

	//check after collision
	thing = new BulletContactCallback(*body, context);
	this->physics->getWorld()->contactTest(body, *thing);

	if (context.hit && context.body->getCollisionFlags() == CollisionType::COLLISIONBOX && playingAnimation == "Walk") {
		this->body->getMotionState()->getWorldTransform(trans);
		Real pushbackVal = 2;
		Vector3 afterOgrePos(
				rootNode->convertLocalToWorldPosition(Vector3::ZERO));
		Real afterX =
				reverse ?
						afterOgrePos.x + pushbackVal :
						afterOgrePos.x - pushbackVal;
		pos = btVector3(afterX, afterOgrePos.y, afterOgrePos.z);
		trans.setOrigin(pos);
		this->body->getMotionState()->setWorldTransform(trans);
		btpos = trans.getOrigin();
		gloPos = Vector3(btpos.getX(), btpos.getY(), btpos.getZ());
		this->rootNode->setPosition(gloPos);

		if (this->opponent != NULL) {
			Real oppPushbackVal = 8;
			Real opp = reverse ? -oppPushbackVal : oppPushbackVal;
			this->opponent->pushBack(opp);
		}

	}

}

