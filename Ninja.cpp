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
	Ogre::Animation * animation = sceneMgr->createAnimation("JumpN" + name, 5.4);
	animation->setDefaultInterpolationMode(Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack * track = animation->createNodeTrack(0, this->rootNode);
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Quaternion curRot = this->rootNode->convertLocalToWorldOrientation(Quaternion::IDENTITY);

	TransformKeyFrame * key;
	key = track->createNodeKeyFrame(0.0f);
	key->setTranslate((curPos + Vector3(0, 0, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(0.75);
	key->setTranslate((curPos + Vector3(0, 300, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(2.0);
	key->setTranslate((curPos + Vector3(0, 550, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(3.8);
	key->setTranslate((curPos + Vector3(0, 250, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(5.0);
	key->setTranslate((curPos + Vector3(0, 0, 0)));
	key->setRotation(curRot);

	sceneMgr->createAnimationState("JumpN" + name);

}

void Ninja::createJumpLeftArc() {

	if (this->sceneMgr->hasAnimation("JumpL" + name)) {
		this->sceneMgr->destroyAnimation("JumpL" + name);
	}
	Ogre::Animation * animation = sceneMgr->createAnimation("JumpL" + name, 5.4);
	animation->setDefaultInterpolationMode(Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack * track = animation->createNodeTrack(1, this->rootNode);
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Quaternion curRot = this->rootNode->convertLocalToWorldOrientation(Quaternion::IDENTITY);

	TransformKeyFrame * key;
	key = track->createNodeKeyFrame(0.0f);
	key->setTranslate((curPos + Vector3(0, 0, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(0.75);
	key->setTranslate((curPos + Vector3(-80, 300, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(2.0);
	key->setTranslate((curPos + Vector3(-250, 550, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(3.8);
	key->setTranslate((curPos + Vector3(-320, 250, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(5.0);
	key->setTranslate((curPos + Vector3(-430, 0, 0)));
	key->setRotation(curRot);

	sceneMgr->createAnimationState("JumpL" + name);

}

void Ninja::createJumpRightArc() {

	if (this->sceneMgr->hasAnimation("JumpR" + name)) {
		this->sceneMgr->destroyAnimation("JumpR" + name);
	}
	Ogre::Animation * animation = sceneMgr->createAnimation("JumpR" + name, 5.4);
	animation->setDefaultInterpolationMode(Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack * track = animation->createNodeTrack(2, this->rootNode);
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Quaternion curRot = this->rootNode->convertLocalToWorldOrientation(Quaternion::IDENTITY);

	TransformKeyFrame * key;
	key = track->createNodeKeyFrame(0.0f);
	key->setTranslate((curPos + Vector3(0, 0, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(0.75);
	key->setTranslate((curPos + Vector3(80, 300, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(2.0);
	key->setTranslate((curPos + Vector3(250, 550, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(3.8);
	key->setTranslate((curPos + Vector3(380, 250, 0)));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(5.0);
	key->setTranslate((curPos + Vector3(430, 0, 0)));
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
	HitboxData hbd { hbox, 6.0, 12.0, 16.0, 20.0, 40.0, 10.0, 10.0, 10.0, 42, 35, 4, 4, false };
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
	HitboxData hbd { hbox, 15.0, 25.0, 35.0, 35.0, 60.0, 20.0, 15.0, 15.0, 44, 15, 6, 4, false };
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
	HitboxData hbd { hbox, 10.0, 5.0, 25.0, 0.0, 150.0, 50.0, 15.0, 15.0, 45, 5, 8, 6, false };
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

void Ninja::createSpecial1LBox() {
	SceneNode * dn = this->sceneMgr->getRootSceneNode()->createChildSceneNode();
	Entity * di = sceneMgr->createEntity("disc.mesh");
	dn->setScale(Vector3(50, 50, 50));
	auto diSize = di->getBoundingBox().getSize() * 25.0;
	//btCollisionObject * hbox = new btPairCachingGhostObject();
	btCollisionShape * diShape = new btBoxShape(btVector3(diSize.x, diSize.y, diSize.z));
	//hbox->setCollisionShape(diShape);
	HitboxData hbd { NULL, 55.0, 45.0, 0.0, 0.0, 90.0, 28.0, 15.0, 15.0, 50, 20, 10, 8, true };

	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Real frontPos = this->onPlayer2Side ? -140.0 : 140.0;
	Disc * dObj = new Disc(sceneMgr, dn, name + to_string(this->inputBuffer->back().frame), di,
			physics, diShape, curPos + Vector3(frontPos, -50.0, 0.0),
			btQuaternion(1.0f, 0.0f, 0.0f, 0.0f), btVector3(frontPos / 6, 0, 0),
			btVector3(0, 0, 0), hbd, this);
	dObj->getRigidBody()->setUserIndex(this->myHitType());
	this->activeProjectile = dObj;
}

void Ninja::createSpecial1MBox() {
	SceneNode * dn = this->sceneMgr->getRootSceneNode()->createChildSceneNode();
	Entity * di = sceneMgr->createEntity("disc.mesh");
	dn->setScale(Vector3(50, 50, 50));
	auto diSize = di->getBoundingBox().getSize() * 25.0;
	//btCollisionObject * hbox = new btPairCachingGhostObject();
	btCollisionShape * diShape = new btBoxShape(btVector3(diSize.x, diSize.y, diSize.z));
	//hbox->setCollisionShape(diShape);
	HitboxData hbd { NULL, 55.0, 45.0, 0.0, 0.0, 100.0, 30.0, 15.0, 5.0, 45, 10, 10, 8, true };

	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Real frontPos = this->onPlayer2Side ? -200.0 : 200.0;
	Disc * dObj = new Disc(sceneMgr, dn, name + to_string(this->inputBuffer->back().frame), di,
			physics, diShape, curPos + Vector3(frontPos, -50.0, 0.0),
			btQuaternion(1.0f, 0.0f, 0.0f, 0.0f), btVector3(frontPos / 4, 0, 0), btVector3(0, 0, 0),
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

void Ninja::createSpecial1HBox() {
	SceneNode * dn = this->sceneMgr->getRootSceneNode()->createChildSceneNode();
	Entity * di = sceneMgr->createEntity("disc.mesh");
	dn->setScale(Vector3(50, 50, 50));
	auto diSize = di->getBoundingBox().getSize() * 25.0;
	//btCollisionObject * hbox = new btPairCachingGhostObject();
	btCollisionShape * diShape = new btBoxShape(btVector3(diSize.x, diSize.y, diSize.z));
	//hbox->setCollisionShape(diShape);
	HitboxData hbd { NULL, 55.0, 45.0, 0.0, 0.0, 110.0, 33.0, 15.0, 15.0, 50, 30, 10, 8, true };

	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Real frontPos = this->onPlayer2Side ? -140.0 : 140.0;
	Disc * dObj = new Disc(sceneMgr, dn, name + to_string(this->inputBuffer->back().frame), di,
			physics, diShape, curPos + Vector3(frontPos, -50.0, 0.0),
			btQuaternion(1.0f, 0.0f, 0.0f, 0.0f), btVector3(frontPos / 2, 0, 0), btVector3(0, 0, 0),
			hbd, this);
	dObj->getRigidBody()->setUserIndex(this->myHitType());
	this->activeProjectile = dObj;
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
	HitboxData hbd { hbox, 10.0, 5.0, 0.0, 0.0, 90.0, 30.0, 15.0, 15.0, 52, 30, 8, 6, false };
	/*
	 this->hitboxes.insert(pair<AttackType, HitboxData>(AttackType::AIRHEAVY, hbd));
	 hbox->setUserPointer(&this->hitboxes.at(AttackType::AIRHEAVY));
	 hbox->setUserIndex(this->myHitType());
	 */
	Hitbox * hitObj = new Hitbox(sceneMgr, this->name + "AIRHEAVY", physics, hbox, pos, hbd,
			this->myHitType());
	this->hitboxes.insert(pair<AttackType, Hitbox *>(AttackType::AIRHEAVY, hitObj));
}

void Ninja::createSuperBox() {
	btCollisionObject * hbox = new btPairCachingGhostObject();
	hbox->setCollisionShape(new btBoxShape(btVector3(120, 180, 50)));
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	btVector3 pos(curPos.x, curPos.y - 1500, curPos.z);

	HitboxData hbd { hbox, 10.0, 5.0, 5.0, 5.0, 320.0, 50.0, 20.0, 20.0, 100, 20, 10, 8, false };
	Hitbox * hitObj = new Hitbox(sceneMgr, this->name + "SUPER", physics, hbox, pos, hbd,
			this->myHitType());
	this->hitboxes.insert(pair<AttackType, Hitbox *>(AttackType::SUPER, hitObj));

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
	Real xPos = curPos.x + 300;

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
		xPos = curPos.x - 300;
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
	as->addTime(0.024);

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
	Real xPos = curPos.x + 160;

	Real yPos = curPos.y + 80;
	std::vector<btVector3> hitFrames;
	if (this->onP1Side()) {
		hitFrames.push_back(btVector3(xPos, yPos + 140, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 140, curPos.z));
		hitFrames.push_back(btVector3(xPos + 80, yPos + 100, curPos.z));
		hitFrames.push_back(btVector3(xPos + 80, yPos + 100, curPos.z));
		hitFrames.push_back(btVector3(xPos + 80, yPos + 80, curPos.z));
		hitFrames.push_back(btVector3(xPos + 40, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos + 40, yPos + 30, curPos.z));
	} else {
		xPos = curPos.x - 160;
		hitFrames.push_back(btVector3(xPos, yPos + 140, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 140, curPos.z));
		hitFrames.push_back(btVector3(xPos - 80, yPos + 100, curPos.z));
		hitFrames.push_back(btVector3(xPos - 80, yPos + 100, curPos.z));
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
	if (frameTime >= -10 && frameTime <= 18) {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, .75, 1.8));
	} else {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
	}
	//printf("in attack x: %f, y: %f, z %f\n", pos.getX(), pos.getY(), pos.getZ());
	trans.setOrigin(pos);
	hbox->setWorldTransform(trans);
}

void Ninja::special1LAnimation() {
	this->setAnimation("Spin");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.012);

	int frameTime = -this->attackFrameCount + 30;
	//printf("frametime: %d\n", frameTime);
	if (frameTime == 0) {
		//projectile activates and animates itself
		this->createSpecial1LBox();
	}
	if (frameTime >= -45 && frameTime <= 40) {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1.3, 2.5));
	} else {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
	}
}

void Ninja::special1MAnimation() {
	this->setAnimation("Spin");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.012);

	int frameTime = -this->attackFrameCount + 40;
	//printf("frametime: %d\n", frameTime);
	if (frameTime == 0) {
		//projectile activates and animates itself
		this->createSpecial1MBox();
	}
	if (frameTime >= -35 && frameTime <= 40) {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1.2, 2));
	} else {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
	}
}

void Ninja::special1HAnimation() {
	this->setAnimation("Spin");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.012);

	int frameTime = -this->attackFrameCount + 50;
	//printf("frametime: %d\n", frameTime);
	if (frameTime == 0) {
		//projectile activates and animates itself
		this->createSpecial1HBox();
	}
	if (frameTime >= -45 && frameTime <= 40) {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1.3, 2.5));
	} else {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
	}
}

void Ninja::superAnimation() {
	this->setAnimation(this->superName);
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.012);

	btTransform trans;
	btCollisionObject * hbox = this->hitboxes.at(currentAttack)->myHbd.hitbox;
	trans = hbox->getWorldTransform();

	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Real xPos = curPos.x + 350;

	Real yPos = curPos.y + 80;
	std::vector<btVector3> hitFrames;
	if (this->onP1Side()) {
		hitFrames.push_back(btVector3(xPos, yPos + 100, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 100, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 80, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 80, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 80, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
	} else {
		xPos = curPos.x - 350;
		hitFrames.push_back(btVector3(xPos, yPos + 100, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 100, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 80, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 80, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 80, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 30, curPos.z));
	}

	btVector3 pos(curPos.x, curPos.y - 1500, curPos.z);
	//btVector3 hurtpos(curPos.x, curPos.y - 500, curPos.z);

	int frameTime = -this->attackFrameCount + 70;
	//do super freeze
	if (frameTime == -5) {
		this->enterStopState(170);
		this->opponent->enterStopState(170);
		this->setStartSuperFreeze(true);
		playSound("../assets/impact.wav", SDL_MIX_MAXVOLUME / 1.5);
		return;
	}
	if (frameTime >= -30 && frameTime <= 10) {
		this->invincible = true;
	}
	if (frameTime >= 0 && frameTime <= 15) {
		pos = hitFrames.at(frameTime);
	}
	if (frameTime >= 11 && frameTime <= 30) {
		this->invincible = false;
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
	}
	//printf("in attack x: %f, y: %f, z %f\n", pos.getX(), pos.getY(), pos.getZ());
	trans.setOrigin(pos);
	hbox->setWorldTransform(trans);
}

void Ninja::doDeath() {
	this->body->getCollisionShape()->setLocalScaling(btVector3(0, 0, 0));
	this->setAnimation("Death2");
	AnimationState * asd = this->geom->getAnimationState(this->playingAnimation);
	asd->setLoop(false);
	asd->addTime(0.01);

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
			if (this->keyBinding.at(ki.key) == InputType::DOWN) {
				//holdDown = true;
			}
			if (this->keyBinding.at(ki.key) == InputType::L) {
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
			if (this->keyBinding.at(ki.key) == InputType::M) {
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
			if (this->keyBinding.at(ki.key) == InputType::H) {
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
			this->setAnimation("Walk");
		} else {
			//not walking
			this->setAnimation("Idle1");
		}
		/*
		//check if movement locked
		if (moveLock) {
			printf("MOVE LOCKED\n");
			moveX = 0;
			this->setAnimation("Block");
			AnimationState * asb = this->geom->getAnimationState(this->playingAnimation);
			asb->addTime(0.005);
			break;
		}
		*/
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

