#include <Ogre.h>
#include "physics.h"
#include <OgreApplicationContext.h>
#include "Ninja.h"
#include "audio.h"

using namespace Ogre;
using namespace std;

void Ninja::animate(const Ogre::FrameEvent& evt) {
	//Actor::animate(evt);

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
		//LogManager::getSingleton().logMessage("Reached HERE");
		Real move = walkSpeed * evt.timeSinceLastFrame;
		Real moveX = 0;
		for (KeyInput ki : *this->keysHeld) {
			if (ki.key == 'a') {
				moveX -= move;
				reverse = true;
			}
			if (ki.key == 'd') {
				moveX += move;
			}
		}
		//if walking
		if (moveX) {
			if (playingAnimation != "Walk") {
				this->geom->getAnimationState(playingAnimation)->setEnabled(
						false);
				this->playingAnimation = "Walk";
			}
		} else {
			//not walking
			if (playingAnimation != "Idle1") {
				this->geom->getAnimationState(playingAnimation)->setEnabled(
						false);
				this->playingAnimation = "Idle1";
			}
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
	if (!as->getEnabled()) {
		as->setEnabled(true);
	}

	Real timeToAdd = reverse ? -evt.timeSinceLastFrame : evt.timeSinceLastFrame;
	as->addTime(evt.timeSinceLastFrame);

}

