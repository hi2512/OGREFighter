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

enum CharacterType {
	NINJA, NINJAALT
};

class GameState {
public:

	//bool isServer = true;
	//NetBase* netManager = NULL;

	bool isPaused = true;
	bool gameStartScreen = true;
	bool showingGameScoreboard = false;
	bool shouldExit = false;

	bool showLoseScreen = false;
	bool showWinScreen = false;

	bool soundPlaying = true;

	bool showConnectionScreen = false;
	bool waitingOnPlayers = false;
	bool multiplayer = false;
	bool showSingleSelect = false;
	bool showP1Select = false;
	bool showP2Select = false;
	bool showStage = false;
	CharacterType p1Char = CharacterType::NINJA;
	CharacterType p2Char = CharacterType::NINJA;
	int stageNumber = -1;

	Uint32 frameCount = 0;
	Ogre::Vector3 camPos = Ogre::Vector3(0, 0, 0);

	std::deque<KeyInput> * inputBuffer = 0;
	std::deque<KeyInput> * releaseBuffer = 0;

	Actor * p1 = NULL;
	Actor * p2 = NULL;

	Actor * winner = NULL;
	const int restartTime = 300;
	int restartTimer = restartTime;

	const Uint32 maxTime = 5500;

	GameState(void) {

	}
	~GameState(void) {
	}

	bool gameIsPaused() {
		return isPaused;
	}

	void startGame() {
		//playMusic("../assets/Upbeat Forever.wav", SDL_MIX_MAXVOLUME / 3);
		//this->gameStarted = true;
		this->leavePauseState();

	}



	void endGame(Actor * winningPlayer) {
		if(restartTimer < restartTime) {
			restartTimer -= 1;
			return;
		}
		restartTimer -= 1;
		this->winner = winningPlayer;
	}
	bool gameOver() {
		return restartTimer < restartTime;
	}

	bool gameRestartReady() {
		return restartTimer == 0;
	}

	int getTime() {
		if (frameCount > maxTime) {
			return 0;
		}
		return (maxTime - frameCount) / (maxTime / 100);
	}

	void nextRound() {
		/*
		if (gameIsPaused()) {
			if (!gameStarted) {
				this->startGame();
			} else {
				this->showingGameScoreboard = false;
				this->showLoseScreen = false;
				this->showWinScreen = false;
			}
			leavePauseState();
		}
		*/
	}

	void enterPauseState();

	void leavePauseState();

};

#endif
