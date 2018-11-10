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

using namespace Ogre;
using namespace std;

class Game: public OgreBites::ApplicationContext,
		public OgreBites::InputListener {
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
private:
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
	Vector3 camDir = Ogre::Vector3(0, 0, 0);

	Vector3 moveDir = Vector3(0, 0, 0);
	int moveVal = 5;

	const int fps = 60;
	const int frameDelay = 1000 / fps;

	Uint32 frameStart;
	int frameTime;

	Uint32 frameCount = 0;

	bool debug = false;

	//key and frame
	std::deque<tuple<int, Uint32>> inputBuffer;
	std::deque<tuple<int, Uint32>> releaseBuffer;

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
	this->inputBuffer.push_back(
			tuple<int, Uint32>(evt.keysym.sym, this->frameCount));
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
	case 'i':
		//gameState->incrementScore(0);
		SceneNode * sn = mgr->getSceneNode("SideNode");
		if (!sn->getAttachedObjects().empty()) {
			camNode->attachObject(sn->detachObject("mainCamera"));
			break;
		}
		sn->setPosition(Vector3(1500, 200, 0));
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
	this->releaseBuffer.push_back(
			tuple<int, Uint32>(evt.keysym.sym, this->frameCount));
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

	RTShader::ShaderGenerator* shaderGen =
			RTShader::ShaderGenerator::getSingletonPtr();
	shaderGen->addSceneManager(scnMgr);

	// set up camera node's position
	camNode = scnMgr->getRootSceneNode()->createChildSceneNode(
			Vector3(0, 400, 1750));
	camNode->lookAt(Vector3(0, 0, -1), Node::TS_PARENT);

	// create the camera and attach it to the node we just created
	Camera* cam = scnMgr->createCamera("mainCamera");
	camera = cam;
	cam->setNearClipDistance(5);
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);

	// tell the camera to render to the main window
	getRenderWindow()->addViewport(cam);

	SceneNode * sideNode = scnMgr->getRootSceneNode()->createChildSceneNode(
			"SideNode", Vector3(800, 200, 0));

	// render the light at the top of the room
	Light* pointLight1 = scnMgr->createLight("pointLight1");
	pointLight1->setType(Light::LT_POINT);

	pointLight1->setSpecularColour(1, 1, 1);
	pointLight1->setDiffuseColour(1, 1, 1);

	SceneNode* pointLightNode1 =
			scnMgr->getRootSceneNode()->createChildSceneNode(
					Vector3(-300, 500, -700));
	pointLightNode1->lookAt(Vector3(0, 0, 0), Node::TS_LOCAL);
	pointLightNode1->attachObject(pointLight1);

	initPhys();

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshPtr planePtr = Ogre::MeshManager::getSingleton().createPlane(
			"ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			plane, 3000, 2500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::Entity *entGround = scnMgr->createEntity("GroundEntity", "ground");
	Ogre::SceneNode *groundNode =
			scnMgr->getRootSceneNode()->createChildSceneNode("GroundNode");
	btCollisionShape *groundShape = new btBoxShape(
			btVector3(btScalar(1500.), btScalar(0), btScalar(1250.)));

	Ground * g = new Ground(scnMgr, groundNode, "GroundObject", entGround, phys,
			groundShape, Vector3(0, 0, 0));
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
			Ogre::Rect(0, 0, getRenderWindow()->getWidth(),
					getRenderWindow()->getHeight()));
	if (debug) {
		gameGui->showFrameCount();
		gameState->camPos = Vector3(camNode->getPosition());
		gameGui->showCamPos();
		gameGui->showInputBuffer();
	}
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

	phys->dynamicsWorld->stepSimulation(1.0f / 12.0f, 50);

	phys->dbd->Update();

	for (int i = 0; i < phys->dynamicsWorld->getNumCollisionObjects(); i++) {
		btCollisionObject* obj =
				phys->dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);

		void *userPointer = body->getUserPointer();

		GameObject * go = static_cast<GameObject *>(userPointer);

		go->animate(evt);

	}
	camNode->translate(camDir * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	leftMouseRelease = false;
	rightMouseRelease = false;
	return frameVal;
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
