#ifndef _GUI_H_
#define _GUI_H_

#include <Ogre.h>
#include <ImguiManager.h>

#include "state.h"
//#include "Multiplayer.h"

/*
class NetBase;
class NetClient;
class NetServer;
*/


class GameGui {
	GameState* state;

public:

	GameGui(GameState* gameState){
		state = gameState;
	}
	~GameGui(void){}

	void showTest();
	void showScore();
	bool showGameStart();
	void showLoseScreen();
	void showWinScreen();
	bool showMultiplaySelect();
	void showWaitingOnPlayers();
	void showSingleSelect();

	void showFrameCount();
	void showCamPos();
};


#endif
