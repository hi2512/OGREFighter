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

void Ninja::createJumpUpArc() {

	if (this->sceneMgr->hasAnimation("JumpN" + name)) {
		this->sceneMgr->destroyAnimation("JumpN" + name);
	}
	Ogre::Animation * animation = sceneMgr->createAnimation("JumpN" + name, 5.2);
	animation->setDefaultInterpolationMode(Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack * track = animation->createNodeTrack(0, this->rootNode);
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Quaternion curRot = this->rootNode->convertLocalToWorldOrientation(Quaternion::IDENTITY);

	TransformKeyFrame * key;
	key = track->createNodeKeyFrame(0.0f);
	key->setTranslate((curPos + Vector3(0, 0, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(0.75);
	key->setTranslate((curPos + Vector3(0, 200, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(2.0);
	key->setTranslate((curPos + Vector3(0, 400, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(3.8);
	key->setTranslate((curPos + Vector3(0, 200, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(4.8);
	key->setTranslate((curPos + Vector3(0, 0, 0)));
	key->setRotation(curRot);

	sceneMgr->createAnimationState("JumpN" + name);

}

void Ninja::createJumpLeftArc() {

	if (this->sceneMgr->hasAnimation("JumpL" + name)) {
		this->sceneMgr->destroyAnimation("JumpL" + name);
	}
	Ogre::Animation * animation = sceneMgr->createAnimation("JumpL" + name, 5.2);
	animation->setDefaultInterpolationMode(Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack * track = animation->createNodeTrack(1, this->rootNode);
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Quaternion curRot = this->rootNode->convertLocalToWorldOrientation(Quaternion::IDENTITY);

	TransformKeyFrame * key;
	key = track->createNodeKeyFrame(0.0f);
	key->setTranslate((curPos + Vector3(0, 0, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(0.75);
	key->setTranslate((curPos + Vector3(-75, 200, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(2.0);
	key->setTranslate((curPos + Vector3(-150, 400, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(3.8);
	key->setTranslate((curPos + Vector3(-250, 200, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(4.8);
	key->setTranslate((curPos + Vector3(-350, 0, 0)));
	key->setRotation(curRot);

	sceneMgr->createAnimationState("JumpL" + name);

}

void Ninja::createJumpRightArc() {

	if (this->sceneMgr->hasAnimation("JumpR" + name)) {
		this->sceneMgr->destroyAnimation("JumpR" + name);
	}
	Ogre::Animation * animation = sceneMgr->createAnimation("JumpR" + name, 5.2);
	animation->setDefaultInterpolationMode(Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack * track = animation->createNodeTrack(2, this->rootNode);
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Quaternion curRot = this->rootNode->convertLocalToWorldOrientation(Quaternion::IDENTITY);

	TransformKeyFrame * key;
	key = track->createNodeKeyFrame(0.0f);
	key->setTranslate((curPos + Vector3(0, 0, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(0.75);
	key->setTranslate((curPos + Vector3(75, 200, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(2.0);
	key->setTranslate((curPos + Vector3(150, 400, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(3.8);
	key->setTranslate((curPos + Vector3(250, 200, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(4.8);
	key->setTranslate((curPos + Vector3(350, 0, 0)));
	key->setRotation(curRot);

	sceneMgr->createAnimationState("JumpR" + name);

}

void Ninja::createLightBox() {
	btCollisionObject * hbox = new btPairCachingGhostObject();
	hbox->setCollisionShape(new btBoxShape(btVector3(40, 40, 40)));

	/*
	 btTransform trans;
	 trans.setIdentity();
	 */
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	btVector3 pos(curPos.x, curPos.y - 500, curPos.z);
	/*
	 trans.setOrigin(pos);
	 hbox->setWorldTransform(trans);
	 hbox->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	 physics->dynamicsWorld->addCollisionObject(hbox);
	 */
	HitboxData hbd { hbox, 22.0, 12.0, 40.0, 10.0, 35, 30, 4, 3, false };
	/*
	 this->hitboxes.insert(pair<AttackType, HitboxData>(AttackType::LIGHT, hbd));
	 hbox->setUserPointer(&this->hitboxes.at(AttackType::LIGHT));
	 hbox->setUserIndex(this->myHitType());
	 */
	Hitbox * hitObj = new Hitbox(sceneMgr, this->name + "LIGHT", physics, hbox, pos, hbd,
			this->myHitType());
	this->hitboxes.insert(pair<AttackType, Hitbox *>(AttackType::LIGHT, hitObj));
}

void Ninja::createMediumBox() {
	btCollisionObject * hbox = new btPairCachingGhostObject();
	hbox->setCollisionShape(new btBoxShape(btVector3(50, 50, 50)));
	/*
	 btTransform trans;
	 trans.setIdentity();
	 */
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	btVector3 pos(curPos.x, curPos.y - 500, curPos.z);
	/*
	 trans.setOrigin(pos);
	 hbox->setWorldTransform(trans);
	 hbox->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	 physics->dynamicsWorld->addCollisionObject(hbox);
	 */
	HitboxData hbd { hbox, 50.0, 30.0, 60.0, 20.0, 44, 25, 6, 4, false };
	/*
	 this->hitboxes.insert(pair<AttackType, HitboxData>(AttackType::MEDIUM, hbd));
	 hbox->setUserPointer(&this->hitboxes.at(AttackType::MEDIUM));
	 hbox->setUserIndex(this->myHitType());
	 */
	Hitbox * hitObj = new Hitbox(sceneMgr, this->name + "MEDIUM", physics, hbox, pos, hbd,
			this->myHitType());
	this->hitboxes.insert(pair<AttackType, Hitbox *>(AttackType::MEDIUM, hitObj));
}

void Ninja::createHeavyBox() {
	btCollisionObject * hbox = new btPairCachingGhostObject();
	hbox->setCollisionShape(new btBoxShape(btVector3(100, 50, 50)));
	/*
	 btTransform trans;
	 trans.setIdentity();
	 */
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	btVector3 pos(curPos.x, curPos.y - 500, curPos.z);
	/*
	 trans.setOrigin(pos);
	 hbox->setWorldTransform(trans);
	 hbox->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	 physics->dynamicsWorld->addCollisionObject(hbox);
	 */
	HitboxData hbd { hbox, 35.0, 5.0, 120.0, 40.0, 50, 5, 8, 6, false };
	/*
	 this->hitboxes.insert(pair<AttackType, HitboxData>(AttackType::HEAVY, hbd));
	 //auto re = &this->hitboxes.at(AttackType::HEAVY);
	 //printf("hitbox data %f, %f", re->hitPushback, re->blockPushback);
	 //printf("hitbox data %f, %f", hbd.hitPushback, hbd.blockPushback);
	 hbox->setUserPointer(&this->hitboxes.at(AttackType::HEAVY));
	 hbox->setUserIndex(this->myHitType());
	 */
	Hitbox * hitObj = new Hitbox(sceneMgr, this->name + "HEAVY", physics, hbox, pos, hbd,
			this->myHitType());
	this->hitboxes.insert(pair<AttackType, Hitbox *>(AttackType::HEAVY, hitObj));
}

void Ninja::createSpecial1Box() {
	SceneNode * dn = this->sceneMgr->getRootSceneNode()->createChildSceneNode();
	Entity * di = sceneMgr->createEntity("disc.mesh");
	dn->setScale(Vector3(50, 50, 50));
	auto diSize = di->getBoundingBox().getSize() * 25.0;
	//btCollisionObject * hbox = new btPairCachingGhostObject();
	btCollisionShape * diShape = new btBoxShape(btVector3(diSize.x, diSize.y, diSize.z));
	//hbox->setCollisionShape(diShape);
	HitboxData hbd { NULL, 35.0, 25.0, 100.0, 30.0, 50, 30, 10, 8, true };

	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Real frontPos = this->onPlayer2Side ? -160.0 : 160.0;
	Disc * dObj = new Disc(sceneMgr, dn, name + to_string(this->inputBuffer->back().frame), di,
			physics, diShape, curPos + Vector3(frontPos, -50.0, 0.0),
			btQuaternion(1.0f, 0.0f, 0.0f, 0.0f), btVector3(frontPos / 3, 0, 0), btVector3(0, 0, 0),
			hbd, this);
	dObj->getRigidBody()->setUserIndex(this->myHitType());
	this->activeProjectile = dObj;
	//this->hitboxes.insert(pair<AttackType, Hitbox *>(AttackType::SPECIAL1, hitObj));
	//hbox->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);

	//remove a previous hitbox
	/*
	 for(auto it = this->hitboxes.begin(); it != this->hitboxes.end(); it++) {
	 auto elem = *it;
	 if(elem.first == AttackType::SPECIAL1) {
	 this->hitboxes.erase(it);
	 break;
	 }
	 }
	 */
	//this->hitboxes.insert(pair<AttackType, HitboxData>(AttackType::SPECIAL1, hbd));
	//dObj->getRigidBody()->setUserIndex(this->myHitType());
	//THE RIGID BODY POINTS TO THE GAME OBJECT
	//dObj->getRigidBody()->setUserPointer(&this->hitboxes.at(AttackType::HEAVY));
	//hbox->setUserPointer(&this->hitboxes.at(AttackType::SPECIAL1));
	//hbox->setUserIndex(this->myHitType());
}

void Ninja::createJumpAttackBox() {
	btCollisionObject * hbox = new btPairCachingGhostObject();
	hbox->setCollisionShape(new btBoxShape(btVector3(75, 75, 50)));
	/*
	 btTransform trans;
	 trans.setIdentity();
	 */
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	btVector3 pos(curPos.x, curPos.y - 500, curPos.z);
	/*
	 trans.setOrigin(pos);
	 hbox->setWorldTransform(trans);
	 hbox->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	 physics->dynamicsWorld->addCollisionObject(hbox);
	 */
	HitboxData hbd { hbox, 10.0, 5.0, 90.0, 30.0, 52, 30, 8, 6, false };
	/*
	 this->hitboxes.insert(pair<AttackType, HitboxData>(AttackType::AIRHEAVY, hbd));
	 hbox->setUserPointer(&this->hitboxes.at(AttackType::AIRHEAVY));
	 hbox->setUserIndex(this->myHitType());
	 */
	Hitbox * hitObj = new Hitbox(sceneMgr, this->name + "AIRHEAVY", physics, hbox, pos, hbd,
			this->myHitType());
	this->hitboxes.insert(pair<AttackType, Hitbox *>(AttackType::AIRHEAVY, hitObj));
}

void Ninja::playJumpAnimation(InputType jumpType) {
	if (!jumpAttack) {
		this->setAnimation("JumpNoHeight");
		AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
		as->addTime(0.005);
	}

	String animName;
	if (jumpType == InputType::RIGHT) {
		animName = "JumpR" + name;
	} else if (jumpType == InputType::LEFT) {
		animName = "JumpL" + name;
	} else if (jumpType == InputType::UP) {
		//printf("jumpN called\n");
		animName = "JumpN" + name;
	}
	AnimationState * jumpAnim = this->sceneMgr->getAnimationState(animName);
	jumpAnim->setLoop(false);
	jumpAnim->setEnabled(true);
	jumpAnim->addTime(0.05);
	if (jumpAnim->hasEnded()) {
		jumpAnim->setTimePosition(0);
		jumpAnim->setEnabled(false);
		this->actorState = StateType::FREE;
		this->jumpAttack = false;
		this->clearAttack();
	}

}

void Ninja::cancelJump() {
	String animName;
	if (jumpType == InputType::RIGHT) {
		animName = "JumpR" + name;
	} else if (jumpType == InputType::LEFT) {
		animName = "JumpL" + name;
	} else if (jumpType == InputType::UP) {
		printf("jumpN called\n");
		animName = "JumpN" + name;
	}
	AnimationState * jumpAnim = this->sceneMgr->getAnimationState(animName);
	jumpAnim->setLoop(false);
	jumpAnim->setTimePosition(0);
	jumpAnim->setEnabled(false);
	this->jumpAttack = false;
	this->actorState = StateType::FALLING;
	if (this->currentAttack != AttackType::NONE) {
		this->clearAttack();
	}
}

void Ninja::playHitAnimation() {
	this->setAnimation("Death1");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	if (newHit) {
		as->setTimePosition(0);
		newHit = false;
	}
	as->addTime(0.002);
}

void Ninja::playBlockAnimation() {
	this->setAnimation("Block");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.03);
}

void Ninja::jumpAttackAnimation() {
	this->setAnimation("SideKick");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.01);

	btTransform trans;
	btCollisionObject * hbox = this->hitboxes.at(currentAttack)->myHbd.hitbox;
	trans = hbox->getWorldTransform();

	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Real xPos = curPos.x + 250;

	Real yPos = curPos.y;
	std::vector<btVector3> hitFrames;
	if (this->onP1Side()) {
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos + 20, yPos - 30, curPos.z));
		hitFrames.push_back(btVector3(xPos + 20, yPos - 30, curPos.z));
		hitFrames.push_back(btVector3(xPos + 20, yPos - 50, curPos.z));
		hitFrames.push_back(btVector3(xPos + 20, yPos - 50, curPos.z));
		hitFrames.push_back(btVector3(xPos + 20, yPos - 80, curPos.z));
		hitFrames.push_back(btVector3(xPos + 20, yPos - 80, curPos.z));
		hitFrames.push_back(btVector3(xPos + 20, yPos - 80, curPos.z));
		hitFrames.push_back(btVector3(xPos + 20, yPos - 100, curPos.z));
		hitFrames.push_back(btVector3(xPos + 20, yPos - 100, curPos.z));
		hitFrames.push_back(btVector3(xPos + 20, yPos - 100, curPos.z));
		/*
		 hitFrames.push_back(btVector3(xPos + 30, yPos - 120, curPos.z));
		 hitFrames.push_back(btVector3(xPos + 30, yPos - 120, curPos.z));
		 hitFrames.push_back(btVector3(xPos + 30, yPos - 120, curPos.z));
		 hitFrames.push_back(btVector3(xPos + 30, yPos - 120, curPos.z));
		 */
	} else {
		xPos = curPos.x - 250;
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos - 20, yPos - 30, curPos.z));
		hitFrames.push_back(btVector3(xPos - 20, yPos - 30, curPos.z));
		hitFrames.push_back(btVector3(xPos - 20, yPos - 50, curPos.z));
		hitFrames.push_back(btVector3(xPos - 20, yPos - 50, curPos.z));
		hitFrames.push_back(btVector3(xPos - 20, yPos - 80, curPos.z));
		hitFrames.push_back(btVector3(xPos - 20, yPos - 80, curPos.z));
		hitFrames.push_back(btVector3(xPos - 20, yPos - 80, curPos.z));
		hitFrames.push_back(btVector3(xPos - 20, yPos - 100, curPos.z));
		hitFrames.push_back(btVector3(xPos - 20, yPos - 100, curPos.z));
		hitFrames.push_back(btVector3(xPos - 20, yPos - 100, curPos.z));
		/*
		 hitFrames.push_back(btVector3(xPos - 30, yPos - 120, curPos.z));
		 hitFrames.push_back(btVector3(xPos - 30, yPos - 120, curPos.z));
		 hitFrames.push_back(btVector3(xPos - 30, yPos - 120, curPos.z));
		 hitFrames.push_back(btVector3(xPos - 30, yPos - 120, curPos.z));
		 */
	}

	btVector3 pos(curPos.x, curPos.y - 1500, curPos.z);

	int frameTime = -this->attackFrameCount + 30;
	//printf("frametime: %d\n", frameTime);
	if (frameTime >= 0 && frameTime <= 12) {
		pos = hitFrames.at(frameTime);
	}
	if (frameTime >= -30 && frameTime <= 25) {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1.2, 2));
	} else {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
	}

	trans.setOrigin(pos);
	hbox->setWorldTransform(trans);
}

void Ninja::heavyAnimation() {
	this->setAnimation("Kick");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.011);

	btTransform trans;
	btCollisionObject * hbox = this->hitboxes.at(currentAttack)->myHbd.hitbox;
	trans = hbox->getWorldTransform();
	auto tv = trans.getOrigin();
	//printf("hitbox pos %f, %f, %f\n", tv.getX(), tv.getY(), tv.getZ());

	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Real xPos = curPos.x + 350;

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
		xPos = curPos.x - 350;
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
	if (frameTime >= -40 && frameTime <= 40) {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 2.9));
	} else {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
	}

	trans.setOrigin(pos);
	hbox->setWorldTransform(trans);
}

void Ninja::lightAnimation() {
	this->setAnimation("Attack1");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.02);

	btTransform trans;
	btCollisionObject * hbox = this->hitboxes.at(currentAttack)->myHbd.hitbox;
	trans = hbox->getWorldTransform();

	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Real xPos = curPos.x + 100;

	Real yPos = curPos.y + 80;
	std::vector<btVector3> hitFrames;
	if (this->onP1Side()) {
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos + 60, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos + 60, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos + 60, yPos + 10, curPos.z));
	} else {
		xPos = curPos.x - 100;
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos - 60, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos - 60, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos - 60, yPos + 10, curPos.z));
	}

	btVector3 pos(curPos.x, curPos.y - 500, curPos.z);
	btVector3 hurtpos(curPos.x, curPos.y - 500, curPos.z);

	int frameTime = -this->attackFrameCount + 20;
	//printf("frametime: %d\n", frameTime);
	if (frameTime >= 0 && frameTime <= 4) {
		pos = hitFrames.at(frameTime);
	}
	if (frameTime >= -5 && frameTime <= 6) {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1.2));
	} else {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
	}
	trans.setOrigin(pos);
	hbox->setWorldTransform(trans);
}

void Ninja::mediumAnimation() {
	this->setAnimation("Attack3");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.012);

	btTransform trans;
	btCollisionObject * hbox = this->hitboxes.at(currentAttack)->myHbd.hitbox;
	trans = hbox->getWorldTransform();

	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Real xPos = curPos.x + 200;

	Real yPos = curPos.y + 80;
	std::vector<btVector3> hitFrames;
	if (this->onP1Side()) {
		hitFrames.push_back(btVector3(xPos, yPos + 100, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 100, curPos.z));
		hitFrames.push_back(btVector3(xPos + 80, yPos + 80, curPos.z));
		hitFrames.push_back(btVector3(xPos + 80, yPos + 80, curPos.z));
		hitFrames.push_back(btVector3(xPos + 80, yPos + 80, curPos.z));
		hitFrames.push_back(btVector3(xPos + 40, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos + 40, yPos + 30, curPos.z));
	} else {
		xPos = curPos.x - 200;
		hitFrames.push_back(btVector3(xPos, yPos + 100, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 100, curPos.z));
		hitFrames.push_back(btVector3(xPos - 80, yPos + 80, curPos.z));
		hitFrames.push_back(btVector3(xPos - 80, yPos + 80, curPos.z));
		hitFrames.push_back(btVector3(xPos - 80, yPos + 80, curPos.z));
		hitFrames.push_back(btVector3(xPos - 40, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos - 40, yPos + 30, curPos.z));
	}

	btVector3 pos(curPos.x, curPos.y - 500, curPos.z);
	//btVector3 hurtpos(curPos.x, curPos.y - 500, curPos.z);

	int frameTime = -this->attackFrameCount + 20;
	//printf("frametime: %d\n", frameTime);
	if (frameTime >= 0 && frameTime <= 6) {
		pos = hitFrames.at(frameTime);
	}
	if (frameTime >= -10 && frameTime <= 12) {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, .75, 1.8));
	} else {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
	}
	//printf("in attack x: %f, y: %f, z %f\n", pos.getX(), pos.getY(), pos.getZ());
	trans.setOrigin(pos);
	hbox->setWorldTransform(trans);
}

void Ninja::special1Animation() {
	this->setAnimation("Spin");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.012);

	int frameTime = -this->attackFrameCount + 40;
	//printf("frametime: %d\n", frameTime);
	if (frameTime == 0) {
		//projectile activates and animates itself
		this->createSpecial1Box();
	}
	if (frameTime >= -35 && frameTime <= 40) {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1.2, 2.5));
	} else {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
	}
}

void Ninja::animate(const Ogre::FrameEvent& evt) {
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
		this->specialMoveWindow = 6;
	}

	switch (this->actorState) {
	case StateType::DEAD: {
		this->body->getCollisionShape()->setLocalScaling(btVector3(0, 0, 0));
		this->setAnimation("Death2");
		AnimationState * asd = this->geom->getAnimationState(this->playingAnimation);
		asd->setLoop(false);
		asd->addTime(evt.timeSinceLastFrame * 0.5);
	}
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
		for (KeyInput ki : *this->keysHeld) {
			if (this->keyBinding.find(ki.key) == this->keyBinding.end()) {
				continue;
			}
			if (this->keyBinding.at(ki.key) == InputType::H) {
				//printf("got command for air heavy\n");
				this->currentAttack = AttackType::AIRHEAVY;
				if (!this->jumpAttack) {
					this->hitboxes.at(currentAttack)->myHbd.active = true;
					this->attackFrameCount = this->jhAttackFrames;
					this->jumpAttack = true;
				}
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
		//check for cancel
		if ((!this->isAboveGround()) && (this->currentAttack != AttackType::NONE)
				&& (this->specialMoveWindow >= 0)) {
			for (KeyInput ki : *this->keysHeld) {
				//skip if key is not binded for this ninja
				if (this->keyBinding.find(ki.key) == this->keyBinding.end()) {
					continue;
				}
				if (this->keyBinding.at(ki.key) == InputType::L) {
					this->clearAttack();
					this->beforeStopState = StateType::ATTACK;
					this->currentAttack = AttackType::SPECIAL1;
				}
			}
		}
		//printf("Stop frame count: %d\n", this->stopFrameCount);
		if (this->stopFrameCount == 0) {
			this->exitStopState();
		}
		this->stopFrameCount -= 1;
		break;
	case StateType::ATTACK:
		//printf("attack reached\n");
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
				break;
			case AttackType::MEDIUM:
				this->attackFrameCount = this->mAttackFrames;
				this->hitboxes.at(currentAttack)->myHbd.active = true;
				break;
			case AttackType::HEAVY:
				this->attackFrameCount = this->hAttackFrames;
				this->hitboxes.at(currentAttack)->myHbd.active = true;
				break;
			case AttackType::SPECIAL1:
				//projectile with activate on creation
				this->attackFrameCount = this->s1AttackFrames;
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
		case AttackType::SPECIAL1:
			//printf("entering special animation\n");
			this->special1Animation();
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
		for (KeyInput ki : *this->keysHeld) {
			//skip if key is not binded for this ninja
			if (this->keyBinding.find(ki.key) == this->keyBinding.end()) {
				continue;
			}
			if (this->keyBinding.at(ki.key) == InputType::UP) {
				startJump = true;
				this->actorState = StateType::JUMPING;
			}
			if (this->keyBinding.at(ki.key) == InputType::LEFT) {
				moveX -= move;
				reverse = true;
			}
			if (this->keyBinding.at(ki.key) == InputType::RIGHT) {
				moveX += move;
			}
			if (this->keyBinding.at(ki.key) == InputType::L) {
				this->actorState = StateType::ATTACK;
				this->currentAttack = AttackType::LIGHT;
				if (this->specialMoveWindow > -1 && !this->hasActiveProjectile()) {
					printf("DO SPECIAL MOVE\n");
					this->currentAttack = AttackType::SPECIAL1;
				}
			}
			if (this->keyBinding.at(ki.key) == InputType::M) {
				this->actorState = StateType::ATTACK;
				this->currentAttack = AttackType::MEDIUM;
			}
			if (this->keyBinding.at(ki.key) == InputType::H) {
				this->actorState = StateType::ATTACK;
				this->currentAttack = AttackType::HEAVY;
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
		GameObject::animate(evt);
		//AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
		//as->addTime(0.005);
	}

	if (specialMoveWindow > -1) {
		this->specialMoveWindow -= 1;
	}
	this->moveLock = false;
	this->doCollision(evt);
}

