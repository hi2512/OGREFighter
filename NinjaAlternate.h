#ifndef NINJAALTERNATE_H_
#define NINJAALTERNATE_H_

#include <Ogre.h>
#include "physics.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "Actor.h"
#include <SDL2/SDL.h>
#include "InputContainer.h"
#include "Disc.h"
#include "Ninja.h"

using namespace std;
using namespace Ogre;
class NinjaAlternate: public Ninja {
protected:
	void createLightBox();
	void createMediumBox();
	void createHeavyBox();
	void createSpecial1LBox();
	void createSpecial1MBox();
	void createSpecial1HBox();

	void lightAnimation();
	void mediumAnimation();
	void heavyAnimation();
	void special1LAnimation();
	void special1MAnimation();
	void special1HAnimation();
public:
	NinjaAlternate(bool isPlayer2, SceneManager * sceneMgr, SceneNode * rootNode, String name,
			Entity * e, Physics * phys, btCollisionShape * shape, const Ogre::Vector3& origin,
			btQuaternion orientation, ActorController * con) :
			Ninja(isPlayer2, sceneMgr, rootNode, name, e, phys, shape, origin, orientation, con) {
		geom->setMaterialName("Examples/BumpyMetal");

		this->lAttackFrames = 20;
		this->mAttackFrames = 35;
		this->hAttackFrames = 50;
		this->s1LAttackFrames = 60;
		this->s1MAttackFrames = 60;
		this->s1HAttackFrames = 60;
	}
};

#endif /* NINJAALTERNATE_H_ */
