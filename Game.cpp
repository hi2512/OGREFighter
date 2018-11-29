#include <Ogre.h>
#include <OgreAnimation.h>
#include <OgreApplicationContext.h>
#include <iostream>
#include <string>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <SDL2/SDL.h>
#include <cmath>
#include <queue>
#include <BulletDynamics/Character/btCharacterControllerInterface.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <LinearMath/btIDebugDraw.h>

#include <ImguiManager.h>

//! [our file includes]
#include "audio.h"

#include "DebugDraw.h"

#include "gui.h"
#include "physics.h"
#include "Ground.h"
//! [our file includes]
#include "Actor.h"
#include "Ninja.h"
#include "InputContainer.h"
#include "Disc.h"
#include "Spark.h"
#include "Wall.h"

#include "ball.h"

using namespace Ogre;
using namespace std;

class Game: public OgreBites::ApplicationContext, public OgreBites::InputListener {
public:
	Game();
	void setup();
	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	bool keyReleased(const OgreBites::KeyboardEvent& evt);
	bool mouseMoved(const OgreBites::MouseMotionEvent &evt);
	bool mousePressed(const OgreBites::MouseButtonEvent &evt);
	bool mouseReleased(const OgreBites::MouseButtonEvent &evt);
	bool frameStarted(const FrameEvent& evt);
	bool frameRenderingQueued(const FrameEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);
	Physics * phys;
	void createCameraSwingAnimation(const Vector3& point, bool leftSide);
	void cameraSwing(Real time, const Vector3& point);
	void cameraZoom(const Vector3& point);
	void cameraSwap();
	void cameraTracking(Real time);
private:
	bool inKeysHeld(const OgreBites::KeyboardEvent& evt, std::vector<KeyInput> kh);
	void initPhys();
	bool leftMouse = false;
	bool leftMouseRelease = false;
	bool middleMouse = false;
	bool rightMouse = false;
	bool rightMouseRelease = false;
	bool mouseMove = false;
	bool swing = false;
	bool swing2 = false;
	bool ret = false;
	// define the camera
	Camera* camera;
	SceneNode* camNode;

	SceneManager * mgr;
	GameState* gameState;
	GameGui* gameGui;
	GameGui* healthDisplay;
	Vector3 camDir = Ogre::Vector3(0, 0, 0);
	Quaternion defaultCamOrientation;

	Vector3 moveDir = Vector3(0, 0, 0);
	int moveVal = 5;

	const int fps = 60;
	const int frameDelay = 1000 / fps;

	Uint32 frameStart;
	int frameTime;

	Uint32 frameCount = 0;

	bool debug = false;

	//key and frame
	std::deque<KeyInput> inputBuffer;
	std::deque<KeyInput> releaseBuffer;
	//stores what key is held and the time it was pressed
	std::vector<KeyInput> keysHeld;

	std::deque<KeyInput> inputBuffer2;
	std::deque<KeyInput> releaseBuffer2;
	std::vector<KeyInput> keysHeld2;

	Actor * player1;
	Actor * player2;

	Actor * curSuperPlayer;

};

//! [constructor]
Game::Game() :
		OgreBites::ApplicationContext("GameTechFinal") {
	gameState = new GameState();
	gameState->inputBuffer = &inputBuffer;
	gameState->releaseBuffer = &releaseBuffer;
	gameGui = new GameGui(gameState);
}
//! [constructor]

bool Game::inKeysHeld(const OgreBites::KeyboardEvent& evt, std::vector<KeyInput> kh) {
	//check if key was held
	for (KeyInput t : kh) {
		if (evt.keysym.sym == t.key) {
			return true;
		}
	}
	return false;
}

//! [key_handler]
bool Game::keyPressed(const OgreBites::KeyboardEvent& evt) {
	/*
	 if (gameState->gameIsPaused() && evt.keysym.sym != OgreBites::SDLK_ESCAPE
	 && evt.keysym.sym != OgreBites::SDLK_RETURN) {
	 return true;
	 }
	 */
	if (inputBuffer.size() > 200) {
		inputBuffer.pop_front();
	}

	this->inputBuffer.push_back(KeyInput { evt.keysym.sym, this->frameCount });

	if (!inKeysHeld(evt, keysHeld)) {
		this->keysHeld.push_back(KeyInput { evt.keysym.sym, this->frameCount });
	}

	if (inputBuffer2.size() > 200) {
		inputBuffer2.pop_front();
	}

	this->inputBuffer2.push_back(KeyInput { evt.keysym.sym, this->frameCount });

	if (!inKeysHeld(evt, keysHeld2)) {
		this->keysHeld2.push_back(KeyInput { evt.keysym.sym, this->frameCount });
	}

	switch (evt.keysym.sym) {
	case OgreBites::SDLK_ESCAPE:
		gameState->shouldExit = true;
		getRoot()->queueEndRendering();
		break;
	case OgreBites::SDLK_RETURN:
		gameState->nextRound();
		break;
	case OgreBites::SDLK_UP:
		camDir.z = -1000;
		break;
	case OgreBites::SDLK_DOWN:
		camDir.z = 1000;
		break;
	case OgreBites::SDLK_LEFT:
		camDir.x = -1000;
		break;
	case OgreBites::SDLK_RIGHT:
		camDir.x = 1000;
		break;
	case OgreBites::SDLK_SPACE:
		break;
	case OgreBites::SDLK_F1:
		//player1->setP1Orientation();
		break;
	case OgreBites::SDLK_F2:
		//player1->setP2Orientation();
		break;
	case 'r':
		debug = !debug;
		break;
	case 'w':
		moveDir.z = -moveVal;
		break;
	case 'a':
		moveDir.x = -moveVal;
		break;
	case 's':
		moveDir.z = moveVal;
		break;
	case 'd':
		moveDir.x = moveVal;
		break;
	case 'y':
		cameraSwap();
		createCameraSwingAnimation(player1->getRootNode()->getPosition(), player1->onP1Side());
		curSuperPlayer = player1;
		swing = !swing;
		break;
	case 'p':
		//gameState->incrementScore(0);
		SceneNode * sn = mgr->getSceneNode("SideNode");
		if (!sn->getAttachedObjects().empty()) {
			camNode->attachObject(sn->detachObject("mainCamera"));
			break;
		}
		sn->setPosition(Vector3(-1500, 200, 0));
		sn->attachObject(camNode->detachObject("mainCamera"));

		sn->lookAt(Vector3(0, 200, 0), Node::TS_WORLD);
		break;
	}

	return true;
}

bool Game::keyReleased(const OgreBites::KeyboardEvent& evt) {
	/*
	 if (gameState->gameIsPaused()) {
	 return true;
	 }
	 */
	if (releaseBuffer.size() > 200) {
		releaseBuffer.pop_front();
	}
	this->releaseBuffer.push_back(KeyInput { evt.keysym.sym, this->frameCount });

	//remove from keys held
	for (auto it = keysHeld.begin(); it != keysHeld.end(); it++) {
		KeyInput t = *it;
		if (evt.keysym.sym == t.key) {
			keysHeld.erase(it);
			break;
		}
	}

	if (releaseBuffer2.size() > 200) {
		releaseBuffer2.pop_front();
	}
	this->releaseBuffer2.push_back(KeyInput { evt.keysym.sym, this->frameCount });

	//remove from keys held
	for (auto it = keysHeld2.begin(); it != keysHeld2.end(); it++) {
		KeyInput t = *it;
		if (evt.keysym.sym == t.key) {
			keysHeld2.erase(it);
			break;
		}
	}

	LogManager::getSingleton().logMessage("Num of keys held");
	LogManager::getSingleton().logMessage(to_string(keysHeld.size()));
	switch (evt.keysym.sym) {
	case OgreBites::SDLK_UP:
	case OgreBites::SDLK_DOWN:
		camDir.z = 0;
		break;
	case OgreBites::SDLK_LEFT:
	case OgreBites::SDLK_RIGHT:
		camDir.x = 0;
		break;
	case 'w':
	case 's':
		moveDir.z = 0;
		break;
	case 'a':
	case 'd':
		moveDir.x = 0;
		break;
	}
	return true;
}
//! [key_handler]

//! [mouse_handler]
bool Game::mouseMoved(const OgreBites::MouseMotionEvent &evt) {
	if (gameState->gameIsPaused()) {
		return true;
	}
	if (leftMouse) {
		//camNode->yaw(Degree(-.1 * evt.xrel), Node::TS_WORLD);
		//camNode->pitch(Degree(-.1 * evt.yrel), Node::TS_LOCAL);
	}
	moveDir.x = evt.xrel;
	moveDir.y = -evt.yrel;
	mouseMove = true;
	return true;
}
//! [mouse_handler]

bool Game::mousePressed(const OgreBites::MouseButtonEvent &evt) {
	if (gameState->gameIsPaused()) {
		return true;
	}
	if (evt.button == OgreBites::BUTTON_RIGHT) {

		rightMouse = true;
	}
	if (evt.button == OgreBites::BUTTON_MIDDLE) {
		middleMouse = true;
	}
	if (evt.button == OgreBites::BUTTON_LEFT) {
		leftMouse = true;
	}
	return true;
}

bool Game::mouseReleased(const OgreBites::MouseButtonEvent &evt) {
	if (gameState->gameIsPaused()) {
		return true;
	}
	if (rightMouse && evt.button == OgreBites::BUTTON_RIGHT) {
		rightMouseRelease = true;
		rightMouse = false;
	}
	if (leftMouse && evt.button == OgreBites::BUTTON_LEFT) {
		leftMouseRelease = true;
		leftMouse = false;
	}
	return true;
}

//! [setup]
void Game::setup(void) {

	OgreBites::ApplicationContext::setup();

	// sets "this" class as the input handler class (we inherit from OgreBites::InputListener)
	addInputListener(this);

	Ogre::ImguiManager::createSingleton();
	addInputListener(Ogre::ImguiManager::getSingletonPtr());

	// get pointer to root and use it to create and get pointer to the scene manager
	Root* root = getRoot();
	SceneManager* scnMgr = root->createSceneManager();
	mgr = scnMgr;
	Ogre::ImguiManager::getSingleton().init(scnMgr);
	scnMgr->setAmbientLight(ColourValue(0.3, 0.3, 0.3));
	scnMgr->setShadowTechnique(Ogre::ShadowTechnique::SHADOWDETAILTYPE_STENCIL);
	//scnMgr->setSkyBox(true, "OurRoom", 5000);

	// register scene with the shader

	RTShader::ShaderGenerator* shaderGen = RTShader::ShaderGenerator::getSingletonPtr();
	shaderGen->addSceneManager(scnMgr);

	// set up camera node's position
	camNode = scnMgr->getRootSceneNode()->createChildSceneNode(Vector3(0, 300, 1400));
	camNode->lookAt(Vector3(0, 50, -1), Node::TS_PARENT);

	// create the camera and attach it to the node we just created
	Camera* cam = scnMgr->createCamera("mainCamera");
	camera = cam;
	cam->setNearClipDistance(5);
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);
	defaultCamOrientation = camera->getOrientation();

	// tell the camera to render to the main window
	getRenderWindow()->addViewport(cam);

	SceneNode * sideNode = scnMgr->getRootSceneNode()->createChildSceneNode("SideNode",
			Vector3(800, 200, 0));
	SceneNode * superCamNode = scnMgr->getRootSceneNode()->createChildSceneNode("SuperCamNode",
			camNode->getPosition());

	// render the light at the top of the room
	Light* pointLight1 = scnMgr->createLight("pointLight1");
	pointLight1->setType(Light::LT_POINT);

	pointLight1->setSpecularColour(1, 1, 1);
	pointLight1->setDiffuseColour(1, 1, 1);

	SceneNode* pointLightNode1 = scnMgr->getRootSceneNode()->createChildSceneNode(
			Vector3(-300, 900, 700));
	pointLightNode1->lookAt(Vector3(0, 0, 0), Node::TS_LOCAL);
	pointLightNode1->attachObject(pointLight1);

	initPhys();

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshPtr planePtr = Ogre::MeshManager::getSingleton().createPlane("ground",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 3000, 4000, 20, 20,
			true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::Entity *entGround = scnMgr->createEntity("GroundEntity", "ground");
	Ogre::SceneNode *groundNode = scnMgr->getRootSceneNode()->createChildSceneNode("GroundNode");
	btCollisionShape *groundShape = new btBoxShape(
			btVector3(btScalar(1500.), btScalar(0), btScalar(1000.)));

	Ground * g = new Ground(scnMgr, groundNode, "GroundObject", entGround, phys, groundShape,
			Vector3(0, 0, 0));

	Ogre::Plane wallLeftPlane(Ogre::Vector3::UNIT_X, 0);
	Ogre::MeshPtr wallLeftPlanePtr = Ogre::MeshManager::getSingleton().createPlane("WallLeft",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, wallLeftPlane, 3000, 4000, 20,
			20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	Ogre::Entity *wallLeft = scnMgr->createEntity("wallLeftEntity", "WallLeft");
	Ogre::SceneNode *wallLeftNode = scnMgr->getRootSceneNode()->createChildSceneNode(
			"WallLeftNode");
	btCollisionShape *wallLeftShape = new btBoxShape(
			btVector3(btScalar(1000.), btScalar(1500.), btScalar(50)));
	Wall * wallL = new Wall(scnMgr, wallLeftNode, "WallLeftObject", wallLeft, phys, wallLeftShape,
			Vector3(-1500, 1500, 0));

	Ogre::Plane wallRightPlane(Ogre::Vector3::NEGATIVE_UNIT_X, 0);
	Ogre::MeshPtr wallRightPlanePtr = Ogre::MeshManager::getSingleton().createPlane("WallRight",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, wallRightPlane, 3000, 4000, 20,
			20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	Ogre::Entity *wallRight = scnMgr->createEntity("wallRightEntity", "WallRight");
	Ogre::SceneNode *wallRightNode = scnMgr->getRootSceneNode()->createChildSceneNode(
			"WallRightNode");
	btCollisionShape *wallRightShape = new btBoxShape(
			btVector3(btScalar(1000.), btScalar(1500.), btScalar(50)));
	Wall * wallR = new Wall(scnMgr, wallRightNode, "WallRightObject", wallRight, phys,
			wallRightShape, Vector3(1500, 1500, 0));

	//this wall is just for show
	Ogre::Plane backWall(Ogre::Vector3::UNIT_Z, 0);
	Ogre::MeshManager::getSingleton().createPlane("back",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, backWall, 3000, 4000, 20, 20,
			true, 1, 5, 5, Ogre::Vector3::UNIT_X);
	Ogre::Entity* backEntity = scnMgr->createEntity("back");
	backEntity->setMaterialName("WoodPallet");
	Ogre::SceneNode * bWallNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	bWallNode->attachObject(backEntity);
	bWallNode->setPosition(Vector3(0, 1000, -2000));

	Entity * p1Entity = scnMgr->createEntity("ninja.mesh");
	//p1Entity->setMaterialName("Examples/BumpyMetal");
	SceneNode * p1Node = scnMgr->getRootSceneNode()->createChildSceneNode("P1Node");
	auto p1OgreBox = p1Entity->getBoundingBox().getSize();
	btCollisionShape * p1Box = new btBoxShape(btVector3(p1OgreBox.x, p1OgreBox.y, p1OgreBox.z));
	Actor * p1 = new Ninja(false, scnMgr, p1Node, "P1", p1Entity, phys, p1Box,
			Vector3(-400, 200, 0), btQuaternion(0.0, -0.707, 0.0, 0.707), &inputBuffer,
			&releaseBuffer, &keysHeld, 'a', 'd', 'w', 's', 'x', 'c', 'v');

	Entity * p2Entity = scnMgr->createEntity("ninja.mesh");
	SceneNode * p2Node = scnMgr->getRootSceneNode()->createChildSceneNode("P2Node");
	auto p2OgreBox = p2Entity->getBoundingBox().getSize();
	btCollisionShape * p2Box = new btBoxShape(btVector3(p2OgreBox.x, p2OgreBox.y, p2OgreBox.z));
	Actor * p2 = new Ninja(true, scnMgr, p2Node, "P2", p2Entity, phys, p2Box, Vector3(400, 200, 0),
			btQuaternion(0.0, -0.707, 0.0, -0.707), &inputBuffer2, &releaseBuffer2, &keysHeld2, 'j',
			'l', 'i', 'k', 'b', 'n', 'm');
	p1->setOpponent(p2);
	p2->setOpponent(p1);
	player1 = p1;
	player2 = p2;
	gameState->p1 = p1;
	gameState->p2 = p2;

	/*
	 Entity * p3Entity = scnMgr->createEntity("Sinbad.mesh");
	 SceneNode * p3Node = scnMgr->getRootSceneNode()->createChildSceneNode("SinbadNode");
	 p3Node->setPosition(Vector3(0, 200, 0));
	 p3Node->attachObject(p3Entity);
	 p3Node->setScale(Vector3(15, 15, 15));
	 AnimationStateSet *mAnims = p3Entity->getAllAnimationStates();
	 AnimationStateIterator it = mAnims->getAnimationStateIterator();
	 while (it.hasMoreElements()) {
	 AnimationStateMap::mapped_type as = it.getNext();
	 LogManager::getSingleton().logMessage(as->getAnimationName());
	 as->setLoop(true);
	 }
	 */
	/*
	 SceneNode * dn = mgr->getRootSceneNode()->createChildSceneNode("disc");
	 Entity * di = mgr->createEntity("disc.mesh");
	 dn->setScale(Vector3(60, 60, 60));
	 auto diSize = di->getBoundingBox().getSize() * 35.0;
	 btCollisionShape * diShape = new btBoxShape(btVector3(diSize.x, diSize.y, diSize.z));
	 //btCollisionShape * diShape = new btSphereShape(diSize.x);
	 Disc * dObj = new Disc(scnMgr, dn, "Disc", di, phys, diShape, Vector3(0, 100, 0),
	 btQuaternion(1.0f, 0.0f, 0.0f, 0.0f), btVector3(0, 0, 0), btVector3(0, 0, 0));
	 */
	/*
	 auto temp1 = p1->getRigidBody();
	 phys->dynamicsWorld->removeRigidBody(temp1);
	 phys->dynamicsWorld->addRigidBody(temp1, 128, 3);
	 //p1->getRigidBody()->setFlags(128);
	 //printf("col flags %d\n", p1->getRigidBody()->getFlags());

	 auto temp2 = p2->getRigidBody();
	 phys->dynamicsWorld->removeRigidBody(temp2);
	 phys->dynamicsWorld->addRigidBody(temp2, 128, 3);
	 */
	/*
	 Entity* blEnt = scnMgr->createEntity("sphere.mesh");
	 SceneNode * bl2 = scnMgr->getRootSceneNode()->createChildSceneNode("BallObject");
	 bl2->setScale(0.2, 0.2, 0.2);
	 auto camPos2 = camNode->getPosition();
	 auto blPos = Vector3(camPos2.x + (rand() % 500 - 250), camPos2.y + (rand() % 500 - 350),
	 camPos2.z + (rand() % 500 - 2000));
	 Ball * bl = new Ball(scnMgr, bl2, "BallObject", blEnt, phys, blPos,
	 btQuaternion(1.0f, 0.0f, 0.0f, 0.0f), btVector3(rand() % 10 - 10, rand() % 10 - 10, 100),
	 btVector3(0, 0, 0));
	 */
	//SceneNode * spNode = mgr->getRootSceneNode()->createChildSceneNode();
	//GameObject * spObj = new Spark(mgr, spNode, "SparkTest1", phys, Vector3(100, 200, 200), 5.0);
}

void Game::initPhys() {
	//PHYSICS INIT
	phys = new Physics();
	phys->initObjects();

	btIDebugDraw * debugDrawer = new CDebugDraw(mgr, phys->dynamicsWorld);
	debugDrawer->setDebugMode(1);
	phys->dbd = (CDebugDraw *) debugDrawer;
	phys->dynamicsWorld->setDebugDrawer(debugDrawer);

}

//! [main]
int main(int argc, char *argv[]) {

	SDL_Init(SDL_INIT_AUDIO);

	initAudio();
	playMusic("../assets/Stealth Groover.wav", SDL_MIX_MAXVOLUME / 3);

	srand((unsigned) time(NULL));
	Game app;
	app.initApp();
	app.getRoot()->startRendering();
	app.closeApp();
	return 0;
}

bool Game::frameStarted(const FrameEvent &evt) {
	frameStart = SDL_GetTicks();

	OgreBites::ApplicationContext::frameStarted(evt);

	Ogre::ImguiManager::getSingleton().newFrame(evt.timeSinceLastFrame,
			Ogre::Rect(0, 0, getRenderWindow()->getWidth(), getRenderWindow()->getHeight()));
	if (debug) {
		gameGui->showFrameCount();
		gameState->camPos = Vector3(camNode->getPosition());
		//gameState->camPos = Vector3(mgr->getSceneNode("SuperCamNode")->getPosition());
		gameGui->showCamPos();
		gameGui->showInputBuffer();
	}
	if (player1->comboCount()) {
		gameGui->showComboCounter1();
	}
	if (player2->comboCount()) {
		gameGui->showComboCounter2();
	}
	gameGui->showHealth1();
	gameGui->showHealth2();
	/*
	 if (gameState->shouldExit) {
	 getRoot()->queueEndRendering();
	 return false;
	 }

	 if (gameState->waitingOnPlayers) {
	 gameGui->showWaitingOnPlayers();
	 return true;
	 }

	 if (!gameState->gameStarted) {
	 return true;
	 }

	 if (gameState->showingGameScoreboard) {
	 gameGui->showScore();
	 }
	 if (gameState->showLoseScreen) {
	 gameGui->showLoseScreen();
	 }

	 if (gameState->showWinScreen) {
	 gameGui->showWinScreen();
	 }
	 */
	return true;
}

bool Game::frameRenderingQueued(const FrameEvent &evt) {
	bool frameVal = OgreBites::ApplicationContext::frameRenderingQueued(evt);
	/*
	 if (gameState->gameIsPaused()) {
	 return frameVal;
	 }
	 */
	phys->dynamicsWorld->stepSimulation(1.0f / 6.0f, 100);

	phys->dbd->Update();

	for (int i = 0; i < phys->dynamicsWorld->getNumCollisionObjects(); i++) {
		btCollisionObject* obj = phys->dynamicsWorld->getCollisionObjectArray()[i];
		if (obj->getCollisionFlags() == btCollisionObject::CF_NO_CONTACT_RESPONSE) {
			//LogManager::getSingleton().logMessage();
			continue;
		}

		btRigidBody* body = btRigidBody::upcast(obj);

		void *userPointer = body->getUserPointer();

		GameObject * go = static_cast<GameObject *>(userPointer);
		/*
		 if (obj->getCollisionFlags() == 1) {
		 printf("checking box %s \n", go->getName().c_str());
		 }
		 */

		go->animate(evt);

	}
	//check which side players should be facing
	Real p1X = player1->getRootNode()->convertLocalToWorldPosition(Vector3::ZERO).x;
	Real p2X = player2->getRootNode()->convertLocalToWorldPosition(Vector3::ZERO).x;
	if (p1X < p2X) {
		player1->setP1Orientation();
		player2->setP2Orientation();
	} else {
		player1->setP2Orientation();
		player2->setP1Orientation();
	}

	/*
	 auto centerPosX = (player1->getRootNode()->getPosition().x
	 + player2->getRootNode()->getPosition().x) / 2;
	 auto curCamPos = camNode->getPosition();
	 //camNode->setPosition(centerPosX, curCamPos.y, curCamPos.z);
	 Real xDir = centerPosX - curCamPos.x;
	 camNode->translate(Vector3(xDir * 1.0, 0, 0) * evt.timeSinceLastFrame, Node::TS_LOCAL);
	 */
	if (player1->getStartSuperFreeze()) {
		cameraSwap();
		createCameraSwingAnimation(player1->getRootNode()->getPosition(), player1->onP1Side());
		swing = true;
		player1->setStartSuperFreeze(false);
		curSuperPlayer = player1;
	} else if (player2->getStartSuperFreeze()) {
		cameraSwap();
		createCameraSwingAnimation(player2->getRootNode()->getPosition(), player2->onP1Side());
		swing = true;
		player2->setStartSuperFreeze(false);
		curSuperPlayer = player2;
	}
	if (!swing) {
		cameraTracking(evt.timeSinceLastFrame);
	} else {
		//printf("start camera swing\n");
		cameraSwing(evt.timeSinceLastFrame, curSuperPlayer->getSuperPos());
	}
	//cameraTracking(evt.timeSinceLastFrame);

	//camNode->translate(camDir * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	leftMouseRelease = false;
	rightMouseRelease = false;
	return frameVal;
}

void Game::createCameraSwingAnimation(const Vector3& point, bool leftSide) {
	//hooray for linear algebra...
	if (mgr->hasAnimation("CamSwing")) {
		mgr->destroyAnimation("CamSwing");
	}
	Animation * animation = mgr->createAnimation("CamSwing", 8.5);
	animation->setDefaultInterpolationMode(Animation::IM_SPLINE);
	SceneNode * swingNode = mgr->getSceneNode("SuperCamNode");
	swingNode->setPosition(camNode->getPosition());
	Ogre::NodeAnimationTrack * track = animation->createNodeTrack(0, swingNode);
	Vector3 curPos = swingNode->convertLocalToWorldPosition(Vector3::ZERO);
	Vector3 newPos;
	Vector3 pointXZ(point.x, 0, point.z);
	Vector3 swingNodeXZ(curPos.x, 0, curPos.z);
	Vector3 dir = swingNodeXZ - pointXZ;
	Quaternion rot = Quaternion::IDENTITY;
	Real rotDir = leftSide ? 10 : -10;

	printf("swingnode: x: %f z:%f\n", curPos.x, curPos.z);
	printf("point: x: %f z:%f\n", pointXZ.x, pointXZ.z);

	printf("0: x: %f z:%f\n", dir.x + pointXZ.x, dir.z + pointXZ.z);
	//printf("0: x: %f z:%f\n", pointXZ.x, pointXZ.z);

	TransformKeyFrame * key;
	key = track->createNodeKeyFrame(0.0f);
	key->setTranslate(curPos + pointXZ);
	//key->setRotation(rot);

	rot = rot * Quaternion(Degree(rotDir), Vector3::UNIT_Y);
	//newPos = rot * swingNodeXZ;
	newPos = rot * dir;
	newPos = newPos + pointXZ;
	printf("1: x: %f z:%f\n", newPos.x, newPos.z);

	key = track->createNodeKeyFrame(2.0f);
	key->setTranslate(Vector3(newPos.x, curPos.y, newPos.z) * 0.85);
	//key->setRotation(rot);

	rot = rot * Quaternion(Degree(rotDir), Vector3::UNIT_Y);
	//newPos = rot * swingNodeXZ;
	newPos = rot * dir;
	newPos = newPos + pointXZ;
	//printf("2: x: %f z:%f\n", newPos.x, newPos.z);

	key = track->createNodeKeyFrame(4.0f);
	key->setTranslate(Vector3(newPos.x, curPos.y, newPos.z) * 0.7);
	//key->setRotation(rot);

	rot = rot * Quaternion(Degree(rotDir), Vector3::UNIT_Y);
	//newPos = rot * swingNodeXZ;
	newPos = rot * dir;
	newPos = newPos + pointXZ;
	//printf("3: x: %f z:%f\n", newPos.x, newPos.z);

	key = track->createNodeKeyFrame(6.0f);
	key->setTranslate(Vector3(newPos.x, curPos.y, newPos.z) * 0.55);
	//key->setRotation(rot);

	rot = rot * Quaternion(Degree(rotDir), Vector3::UNIT_Y);
	//newPos = rot * swingNodeXZ;
	newPos = rot * dir;
	newPos = newPos + pointXZ;
	//printf("4: x: %f z:%f\n", newPos.x, newPos.z);

	key = track->createNodeKeyFrame(8.0f);
	key->setTranslate(Vector3(newPos.x, curPos.y, newPos.z) * 0.4);
	//key->setRotation(rot);

	mgr->createAnimationState("CamSwing");
}

void Game::cameraSwing(Real time, const Vector3& targetPoint) {

	camera->lookAt(targetPoint);
	AnimationState * swingAnim = mgr->getAnimationState("CamSwing");
	swingAnim->setLoop(false);
	swingAnim->setEnabled(true);
	swingAnim->addTime(time * 3);
	//mgr->getSceneNode("SuperCamNode")->lookAt(targetPoint, Node::TS_WORLD);
	if (swingAnim->hasEnded()) {
		swingAnim->setTimePosition(0);
		swingAnim->setEnabled(false);
		cameraSwap();
		swing = false;
	}
}

void Game::cameraZoom(const Vector3& point) {

}

void Game::cameraSwap() {

	SceneNode * sn = mgr->getSceneNode("SuperCamNode");
	if (!sn->getAttachedObjects().empty()) {
		camNode->attachObject(sn->detachObject("mainCamera"));
		camera->setOrientation(defaultCamOrientation);
		return;
	}
	sn->attachObject(camNode->detachObject("mainCamera"));
	//camNode->lookAt(Vector3(0, 50, -1), Node::TS_PARENT);
	//sn->lookAt(Vector3(0, 200, 0), Node::TS_WORLD);
}

void Game::cameraTracking(Real time) {
	auto centerPos = (player1->getRootNode()->getPosition() + player2->getRootNode()->getPosition())
			/ 2;
	//offset of initial height - average playerheights
	centerPos.y += 200;
	Vector3 transDir = centerPos - camNode->getPosition();
	camNode->translate(Vector3(transDir.x * 1.0, transDir.y * 0.8, 0) * time, Node::TS_LOCAL);
}

bool Game::frameEnded(const FrameEvent &evt) {
	bool res = OgreBites::ApplicationContext::frameEnded(evt);
	frameTime = SDL_GetTicks() - frameStart;
	if (frameDelay > frameTime) {
		SDL_Delay(frameDelay - frameTime);
	}
	frameCount++;
	this->gameState->frameCount = this->frameCount;
	return res;
}

//! [main]
