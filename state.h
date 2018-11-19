#ifndef _STATE_H_
#define _STATE_H_

#include <Ogre.h>
#include <SDL2/SDL.h>
#include <LinearMath/btVector3.h>

#include "audio.h"
#include "InputContainer.h"
#include "Actor.h"

class NetBase;

using namespace std;

class GameState {
public:

	//bool isServer = true;
	//NetBase* netManager = NULL;

	bool gameStarted = false;
	bool showingGameScoreboard = false;
	bool shouldExit = false;

	bool showLoseScreen = false;
	bool showWinScreen = false;

	bool soundPlaying = true;

	bool showConnectionScreen = false;
	bool waitingOnPlayers = false;
	bool multiplayer = false;
	bool showSingleSelect = false;

	Uint32 frameCount = 0;
	Ogre::Vector3 camPos = Ogre::Vector3(0, 0, 0);

	std::deque<KeyInput> * inputBuffer = 0;
	std::deque<KeyInput> * releaseBuffer = 0;

	Actor * p1 = NULL;
	Actor * p2 = NULL;


	GameState(void) {

	}
	~GameState(void){}

	bool gameIsPaused(){
		return !gameStarted || showingGameScoreboard || showLoseScreen || showWinScreen || showConnectionScreen || waitingOnPlayers;
	}

	void startGame(){
		playMusic("../assets/Upbeat Forever.wav", SDL_MIX_MAXVOLUME/3);
		this->gameStarted = true;
		this->leavePauseState();
		
	}

	void nextRound(){
		if(gameIsPaused()){
			if(!gameStarted) {
				this->startGame();
			} else {
				this->showingGameScoreboard = false;
				this->showLoseScreen = false;
				this->showWinScreen = false;
			}
			leavePauseState();
		}
	}


	void enterPauseState();

	void leavePauseState();

};


#endif
