#include <Ogre.h>
#include "physics.h"
#include <OgreApplicationContext.h>
#include "Ninja.h"
#include "audio.h"

using namespace Ogre;
using namespace std;

void Ninja::animate(const Ogre::FrameEvent& evt) {
	//Actor::animate(evt);

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
		//if (!this->keysHeld->empty()) {
		for (KeyInput ki : *this->keysHeld) {
			if (ki.key == 'a') {
				moveX -= move;
			}
			if (ki.key == 'd') {
				moveX += move;
			}
		}
		//}
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

}

