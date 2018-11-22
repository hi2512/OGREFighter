#ifndef SPARK_H_
#define SPARK_H_

#include <Ogre.h>

using namespace Ogre;
using namespace std;
class Spark: public GameObject {
private:
	Entity * createBillboardSet(SceneManager * sMgr, SceneNode * rNode, String name,
			const Vector3& origin) {
		bbSet = sMgr->createBillboardSet(name);
		bbSet->setMaterialName("Spark");
		Billboard* myBill = bbSet->createBillboard(origin);
		return (Entity *) bbSet;
	}

protected:
	Real timeOnScreen;
	BillboardSet * bbSet;
public:
	Spark(SceneManager * mgr, SceneNode * rNode, String name, Physics * phys, const Vector3& origin,
			Real time = 0.2) :
			GameObject(mgr, rNode, name, this->createBillboardSet(mgr, rNode, name, origin), phys,
					new btBoxShape(btVector3(0, 0, 0)), 0.0, true, origin,
					btQuaternion(1.0f, 0.0f, 0.0f, 0.0f), 0.0, 0.0), timeOnScreen(time), bbSet(
					bbSet) {
		//this->body->setCollisionFlags(btCollisionObject::CO_GHOST_OBJECT);
		this->rootNode->setScale(Vector3(2.0, 2.0, 2.0));
	}
	~Spark() {
		this->sceneMgr->destroyBillboardSet(bbSet);
		//scnMgr->destroySceneNode(rootNode);
	}

	void animate(const FrameEvent& evt) {
		//LogManager::getSingleton().logMessage("ANIMATING SPARK");
		//printf("SPARK remaining time %f\n", this->timeOnScreen);
		auto point = this->rootNode->getPosition();
		//printf("spark is at point x: %f, y: %f, z: %f\n", point.x, point.y, point.z);
		auto btPoint = this->body->getWorldTransform().getOrigin();
		//printf("spark is at BTpoint x: %f, y: %f, z: %f\n", btPoint.getX(), btPoint.getY(), btPoint.getZ());
		this->timeOnScreen -= evt.timeSinceLastFrame;
		if (timeOnScreen < 0.0) {
			this->sceneMgr->destroyBillboardSet(bbSet);
			this->physics->dynamicsWorld->removeCollisionObject(body);
		}
	}
};

#endif /* SPARK_H_ */
