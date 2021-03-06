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
	HitboxData hbd { hbox, 18.0, 12.0, 28.0, 20.0, 40.0, 10.0, 10.0, 10.0, 30, 28, 4, 4, false };
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
	Disc * dObj = new Disc(sceneMgr, dn, name + to_string(time(NULL)), di, physics, diShape,
			curPos + Vector3(frontPos, -50.0, 0.0), btQuaternion(1.0f, 0.0f, 0.0f, 0.0f),
			btVector3(frontPos / 6, 0, 0), btVector3(0, 0, 0), hbd, this);
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
	Disc * dObj = new Disc(sceneMgr, dn, name + to_string(time(NULL)), di, physics, diShape,
			curPos + Vector3(frontPos, -50.0, 0.0), btQuaternion(1.0f, 0.0f, 0.0f, 0.0f),
			btVector3(frontPos / 4, 0, 0), btVector3(0, 0, 0), hbd, this);
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
	Disc * dObj = new Disc(sceneMgr, dn, name + to_string(time(NULL)), di, physics, diShape,
			curPos + Vector3(frontPos, -50.0, 0.0), btQuaternion(1.0f, 0.0f, 0.0f, 0.0f),
			btVector3(frontPos / 2, 0, 0), btVector3(0, 0, 0), hbd, this);
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
	HitboxData hbd { hbox, 10.0, 5.0, 0.0, 0.0, 90.0, 30.0, 15.0, 15.0, 52, 30, 10, 8, false };
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
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1.1, 1.8));
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
	this->setAnimation("Attack2");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.01);

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
	this->setAnimation("Attack2");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.01);

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
	this->setAnimation("Attack2");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.01);

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
	Actor::animate(evt);
	//fix...
	this->ninOffsetNode->detachObject(geom);
	this->ninOffsetNode->attachObject(geom);
	/*
	if (!this->isPlayer2) {

		auto ogrePos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
		printf("root   x: %f, y: %f, z: %f\n", ogrePos.x, ogrePos.y, ogrePos.z);

		auto grePos = this->ninOffsetNode->getPosition();
		printf("locset x: %f, y: %f, z: %f\n", grePos.x, grePos.y, grePos.z);

		auto oogrePos = this->ninOffsetNode->convertLocalToWorldPosition(Vector3::ZERO);
		printf("offset x: %f, y: %f, z: %f", oogrePos.x, oogrePos.y, oogrePos.z);
		printf("%s\n", this->ninOffsetNode->getParentSceneNode()->getName().c_str());
	}
	*/

}
