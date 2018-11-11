#include <Ogre.h>
#include "physics.h"
#include <OgreApplicationContext.h>
#include "Ninja.h"
#include "audio.h"

using namespace Ogre;
using namespace std;

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

	btVector3 pos;
	switch (this->actorState) {
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
		}
		//if walking
		if (moveX) {
			this->setAnimation("Walk");
		} else {
			//not walking
			this->setAnimation("Idle1");
		}
		//pushback if walk into each other
		if (context.hit) {
			moveX = -moveX * -3;
		}
		pos = btVector3(ogrePos.x + moveX, ogrePos.y, ogrePos.z);
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

	//play animation
	AnimationState * as = this->geom->getAnimationState(this->playingAnimation);

	Real timeToAdd = reverse ? -evt.timeSinceLastFrame : evt.timeSinceLastFrame;
	as->addTime(evt.timeSinceLastFrame);

	//check after collision
	thing = new BulletContactCallback(*body, context);
	this->physics->getWorld()->contactTest(body, *thing);
	if (context.hit && playingAnimation == "Walk") {
		Vector3 afterOgrePos(
				rootNode->convertLocalToWorldPosition(Vector3::ZERO));
		Real afterX = reverse ? afterOgrePos.x + 20 : afterOgrePos.x - 20;
		pos = btVector3(afterX, afterOgrePos.y, afterOgrePos.z);
		trans.setOrigin(pos);
		btpos = trans.getOrigin();
		gloPos = Vector3(btpos.getX(), btpos.getY(), btpos.getZ());
		this->rootNode->setPosition(gloPos);

	}

}

