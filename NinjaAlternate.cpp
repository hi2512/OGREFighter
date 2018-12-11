#include <Ogre.h>
#include "physics.h"
#include <OgreApplicationContext.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include "Ninja.h"
#include "audio.h"
#include "NinjaAlternate.h"

using namespace std;
using namespace Ogre;

void NinjaAlternate::createLightBox() {
	btCollisionObject * hbox = new btPairCachingGhostObject();
	hbox->setCollisionShape(new btBoxShape(btVector3(50, 50, 50)));

	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	btVector3 pos(curPos.x, curPos.y - 1500, curPos.z);

	HitboxData hbd { hbox, 30.0, 20.0, 40.0, 16.0, 30.0, 5.0, 10.0, 10.0, 35, 20, 4, 4, false };
	Hitbox * hitObj = new Hitbox(sceneMgr, this->name + "LIGHT", physics, hbox, pos, hbd,
			this->myHitType());
	this->hitboxes.insert(pair<AttackType, Hitbox *>(AttackType::LIGHT, hitObj));
}
void NinjaAlternate::createMediumBox() {
	btCollisionObject * hbox = new btPairCachingGhostObject();
	hbox->setCollisionShape(new btBoxShape(btVector3(50, 50, 50)));
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	btVector3 pos(curPos.x, curPos.y - 1500, curPos.z);
	HitboxData hbd { hbox, 30.0, 35.0, 50.0, 45.0, 40.0, 10.0, 15.0, 15.0, 47, 15, 6, 4, false };
	Hitbox * hitObj = new Hitbox(sceneMgr, this->name + "MEDIUM", physics, hbox, pos, hbd,
			this->myHitType());
	this->hitboxes.insert(pair<AttackType, Hitbox *>(AttackType::MEDIUM, hitObj));
}
void NinjaAlternate::createHeavyBox() {
	btCollisionObject * hbox = new btPairCachingGhostObject();
	hbox->setCollisionShape(new btBoxShape(btVector3(120, 50, 50)));
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	btVector3 pos(curPos.x, curPos.y - 500, curPos.z);
	HitboxData hbd { hbox, 15.0, 30.0, 30.0, 35.0, 70.0, 20.0, 15.0, 15.0, 40, 30, 8, 6, false };
	Hitbox * hitObj = new Hitbox(sceneMgr, this->name + "HEAVY", physics, hbox, pos, hbd,
			this->myHitType());
	this->hitboxes.insert(pair<AttackType, Hitbox *>(AttackType::HEAVY, hitObj));
}
void NinjaAlternate::createSpecial1LBox() {
	if (this->sceneMgr->hasAnimation("DashL" + name)) {
		this->sceneMgr->destroyAnimation("DashL" + name);
	}
	Ogre::Animation * animation = sceneMgr->createAnimation("DashL" + name, 0.8);
	animation->setDefaultInterpolationMode(Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack * track = animation->createNodeTrack(0, this->rootNode);
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Quaternion curRot = this->rootNode->convertLocalToWorldOrientation(Quaternion::IDENTITY);
	const Real wallDist = 1150;
	const Real maxDist = 300;
	Real curX = this->rootNode->getPosition().x;

	Real midX = this->onP2Side() ? curX - maxDist / 2 : curX + maxDist / 2;
	if (midX > abs(wallDist)) {
		midX = this->onP2Side() ? -wallDist : wallDist;
	}
	Real endX = this->onP2Side() ? curX - maxDist : curX + maxDist;
	if (endX > abs(wallDist)) {
		endX = this->onP2Side() ? -wallDist : wallDist;
	}
	TransformKeyFrame * key;
	key = track->createNodeKeyFrame(0.0f);
	key->setTranslate(curPos);
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(0.3f);
	key->setTranslate(Vector3(midX, curPos.y, curPos.z));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(0.6f);
	key->setTranslate(Vector3(endX, curPos.y, curPos.z));
	key->setRotation(curRot);

	sceneMgr->createAnimationState("DashL" + name);
}
void NinjaAlternate::createSpecial1MBox() {
	if (this->sceneMgr->hasAnimation("DashM" + name)) {
		this->sceneMgr->destroyAnimation("DashM" + name);
	}
	Ogre::Animation * animation = sceneMgr->createAnimation("DashM" + name, 1.0);
	animation->setDefaultInterpolationMode(Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack * track = animation->createNodeTrack(0, this->rootNode);
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Quaternion curRot = this->rootNode->convertLocalToWorldOrientation(Quaternion::IDENTITY);
	const Real wallDist = 1150;
	const Real maxDist = 450;
	Real curX = this->rootNode->getPosition().x;

	Real midX = this->onP2Side() ? curX - maxDist / 2 : curX + maxDist / 2;
	if (midX > abs(wallDist)) {
		midX = this->onP2Side() ? -wallDist : wallDist;
	}
	Real endX = this->onP2Side() ? curX - maxDist : curX + maxDist;
	if (endX > abs(wallDist)) {
		endX = this->onP2Side() ? -wallDist : wallDist;
	}
	TransformKeyFrame * key;
	key = track->createNodeKeyFrame(0.0f);
	key->setTranslate(curPos);
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(0.4f);
	key->setTranslate(Vector3(midX, curPos.y, curPos.z));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(0.8f);
	key->setTranslate(Vector3(endX, curPos.y, curPos.z));
	key->setRotation(curRot);

	sceneMgr->createAnimationState("DashM" + name);
}
void NinjaAlternate::createSpecial1HBox() {
	if (this->sceneMgr->hasAnimation("DashH" + name)) {
		this->sceneMgr->destroyAnimation("DashH" + name);
	}
	Ogre::Animation * animation = sceneMgr->createAnimation("DashH" + name, 1.4);
	animation->setDefaultInterpolationMode(Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack * track = animation->createNodeTrack(0, this->rootNode);
	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Quaternion curRot = this->rootNode->convertLocalToWorldOrientation(Quaternion::IDENTITY);
	const Real wallDist = 1150;
	const Real maxDist = 600;
	Real curX = this->rootNode->getPosition().x;

	Real midX = this->onP2Side() ? curX - maxDist / 2 : curX + maxDist / 2;
	if (midX > abs(wallDist)) {
		midX = this->onP2Side() ? -wallDist : wallDist;
	}
	Real endX = this->onP2Side() ? curX - maxDist : curX + maxDist;
	if (endX > abs(wallDist)) {
		endX = this->onP2Side() ? -wallDist : wallDist;
	}
	TransformKeyFrame * key;
	key = track->createNodeKeyFrame(0.0f);
	key->setTranslate(curPos);
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(0.6f);
	key->setTranslate(Vector3(midX, curPos.y, curPos.z));
	key->setRotation(curRot);

	key = track->createNodeKeyFrame(1.0f);
	key->setTranslate(Vector3(endX, curPos.y, curPos.z));
	key->setRotation(curRot);

	sceneMgr->createAnimationState("DashH" + name);
}

void NinjaAlternate::lightAnimation() {
	this->setAnimation("Attack1");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.028);

	btTransform trans;
	btCollisionObject * hbox = this->hitboxes.at(currentAttack)->myHbd.hitbox;
	trans = hbox->getWorldTransform();

	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Real xPos = curPos.x + 130;

	Real yPos = curPos.y + 80;
	std::vector<btVector3> hitFrames;
	if (this->onP1Side()) {
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos + 50, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos + 50, yPos + 10, curPos.z));
	} else {
		xPos = curPos.x - 130;
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos - 50, yPos + 10, curPos.z));
		hitFrames.push_back(btVector3(xPos - 50, yPos + 10, curPos.z));
	}

	btVector3 pos(curPos.x, curPos.y - 1500, curPos.z);
	btVector3 hurtpos(curPos.x, curPos.y - 1500, curPos.z);

	int frameTime = -this->attackFrameCount + 14;
	//printf("frametime: %d\n", frameTime);
	if (frameTime >= 0 && frameTime <= 3) {
		pos = hitFrames.at(frameTime);
	}
	if (frameTime >= -5 && frameTime <= 5) {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1.1));
	} else {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
	}
	trans.setOrigin(pos);
	hbox->setWorldTransform(trans);
}
void NinjaAlternate::mediumAnimation() {
	this->setAnimation("Attack3");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.016);

	btTransform trans;
	btCollisionObject * hbox = this->hitboxes.at(currentAttack)->myHbd.hitbox;
	trans = hbox->getWorldTransform();

	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Real xPos = curPos.x + 160;

	Real yPos = curPos.y + 60;
	std::vector<btVector3> hitFrames;
	if (this->onP1Side()) {
		hitFrames.push_back(btVector3(xPos, yPos + 140, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 140, curPos.z));
		hitFrames.push_back(btVector3(xPos + 80, yPos + 100, curPos.z));
		hitFrames.push_back(btVector3(xPos + 80, yPos + 100, curPos.z));
	} else {
		xPos = curPos.x - 160;
		hitFrames.push_back(btVector3(xPos, yPos + 140, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos + 140, curPos.z));
		hitFrames.push_back(btVector3(xPos - 80, yPos + 100, curPos.z));
		hitFrames.push_back(btVector3(xPos - 80, yPos + 100, curPos.z));
	}

	btVector3 pos(curPos.x, curPos.y - 1500, curPos.z);
	//btVector3 hurtpos(curPos.x, curPos.y - 500, curPos.z);

	int frameTime = -this->attackFrameCount + 25;
	//printf("frametime: %d\n", frameTime);
	if (frameTime >= 0 && frameTime <= 3) {
		pos = hitFrames.at(frameTime);
	}
	if (frameTime >= -10 && frameTime <= 10) {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, .85, 1.6));
	} else {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
	}
	//printf("in attack x: %f, y: %f, z %f\n", pos.getX(), pos.getY(), pos.getZ());
	trans.setOrigin(pos);
	hbox->setWorldTransform(trans);
}
void NinjaAlternate::heavyAnimation() {
	this->setAnimation("Spin");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.03);

	btTransform trans;
	btCollisionObject * hbox = this->hitboxes.at(currentAttack)->myHbd.hitbox;
	trans = hbox->getWorldTransform();
	auto tv = trans.getOrigin();
	//printf("hitbox pos %f, %f, %f\n", tv.getX(), tv.getY(), tv.getZ());

	Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Real xPos = curPos.x + 200;

	Real yPos = curPos.y + 70;
	std::vector<btVector3> hitFrames;
	if (this->onP1Side()) {
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos + 20, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos + 20, yPos, curPos.z));
	} else {
		xPos = curPos.x - 200;
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos - 20, yPos, curPos.z));
		hitFrames.push_back(btVector3(xPos - 20, yPos, curPos.z));
	}

	btVector3 pos(curPos.x, curPos.y - 1500, curPos.z);
	btVector3 hurtpos(curPos.x, curPos.y - 1500, curPos.z);

	int frameTime = -this->attackFrameCount + 30;
	//printf("frametime: %d\n", frameTime);
	if (frameTime >= 0 && frameTime <= 3) {
		pos = hitFrames.at(frameTime);
	}
	if (frameTime >= -10 && frameTime <= 10) {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1.2, 1.75));
	} else {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
	}

	trans.setOrigin(pos);
	hbox->setWorldTransform(trans);
}

void NinjaAlternate::clearAttack() {
	if (this->attackTypeIsSpecial(currentAttack)) {
		AnimationState * dashAnim = this->sceneMgr->getAnimationState(dashName);
		dashAnim->setEnabled(false);
	}
	Actor::clearAttack();
}
void NinjaAlternate::special1LAnimation() {
	this->setAnimation("Stealth");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.028);

	if (this->attackFrameCount == this->s1LAttackFrames) {
		this->createSpecial1LBox();
	}
	this->dashName = "DashL" + name;
	AnimationState * dashAnim = this->sceneMgr->getAnimationState(dashName);
	dashAnim->setLoop(false);
	dashAnim->setEnabled(true);
	dashAnim->addTime(0.02);

	int frameTime = -this->attackFrameCount + 33;
	if (frameTime >= 0 && frameTime <= 15) {
		this->invincible = true;
	}
	if (frameTime >= 16 && frameTime <= 31) {
		this->invincible = false;
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1.6));
	}
	if (frameTime == 32) {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
		dashAnim->setEnabled(false);
	}
}
void NinjaAlternate::special1MAnimation() {
	this->setAnimation("Stealth");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.023);

	if (this->attackFrameCount == this->s1MAttackFrames) {
		this->createSpecial1MBox();
	}
	this->dashName = "DashM" + name;
	AnimationState * dashAnim = this->sceneMgr->getAnimationState(dashName);
	dashAnim->setLoop(false);
	dashAnim->setEnabled(true);
	dashAnim->addTime(0.02);

	int frameTime = -this->attackFrameCount + 50;
	if (frameTime >= 0 && frameTime <= 40) {
		this->invincible = true;
	}
	if (frameTime >= 41 && frameTime <= 48) {
		this->invincible = false;
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1.6));
	}
	if (frameTime == 49) {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
		dashAnim->setEnabled(false);
	}
}
void NinjaAlternate::special1HAnimation() {
	this->setAnimation("Stealth");
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);
	as->setLoop(false);
	as->addTime(0.02);

	if (this->attackFrameCount == this->s1HAttackFrames) {
		this->createSpecial1HBox();
	}
	this->dashName = "DashH" + name;
	AnimationState * dashAnim = this->sceneMgr->getAnimationState(dashName);
	dashAnim->setLoop(false);
	dashAnim->setEnabled(true);
	dashAnim->addTime(0.02);

	int frameTime = -this->attackFrameCount + 57;
	if (frameTime >= 0 && frameTime <= 25) {
		this->invincible = true;
	}
	if (frameTime >= 26 && frameTime <= 55) {
		this->invincible = false;
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1.6));
	}
	if (frameTime == 56) {
		this->body->getCollisionShape()->setLocalScaling(btVector3(1, 1, 1));
		dashAnim->setEnabled(false);
	}
}
