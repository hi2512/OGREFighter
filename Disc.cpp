#include "Disc.h"

using namespace Ogre;
using namespace std;
void Disc::createAnim() {

	Ogre::Animation * animation = sceneMgr->createAnimation("Spin" + name, 1.0);
	animation->setDefaultInterpolationMode(Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack * track = animation->createNodeTrack(0, this->offsetNode);
	//Vector3 curPos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	Quaternion curRot = this->offsetNode->convertLocalToWorldOrientation(Quaternion::IDENTITY);

	TransformKeyFrame * key;
	key = track->createNodeKeyFrame(0.0f);
	key->setRotation(curRot);

	curRot = curRot * Quaternion(Degree(30), Vector3::UNIT_Y);
	key = track->createNodeKeyFrame(0.25f);
	key->setRotation(curRot);

	curRot = curRot * Quaternion(Degree(30), Vector3::UNIT_Y);
	key = track->createNodeKeyFrame(0.5f);
	key->setRotation(curRot);

	curRot = curRot * Quaternion(Degree(30), Vector3::UNIT_Y);
	key = track->createNodeKeyFrame(0.75f);
	key->setRotation(curRot);

	curRot = curRot * Quaternion(Degree(30), Vector3::UNIT_Y);
	key = track->createNodeKeyFrame(1.0f);
	key->setRotation(curRot);

	sceneMgr->createAnimationState("Spin" + name);

}

void Disc::animate(const FrameEvent& evt) {

	AnimationState * as = sceneMgr->getAnimationState("Spin" + name);
	as->setEnabled(true);
	as->addTime(0.05);
	GameObject::animate(evt);
	//auto opos = this->offsetNode->convertLocalToWorldPosition(Vector3::ZERO);
	//printf("Offset node pos: x: %f, y: %f, z: %f\n", opos.x, opos.y, opos.z);
	//auto pos = this->rootNode->convertLocalToWorldPosition(Vector3::ZERO);
	//printf("root node pos: x: %f, y: %f, z: %f\n", pos.x, pos.y, pos.z);
}

