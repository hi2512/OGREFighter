
#include "state.h"


void GameState::enterPauseState(){
	this->isPaused = true;
	SDL_SetRelativeMouseMode(SDL_FALSE);
}

void GameState::leavePauseState(){
	//playMusic("../assets/Upbeat Forever.wav", SDL_MIX_MAXVOLUME/3);
	this->isPaused = false;
	SDL_SetRelativeMouseMode(SDL_TRUE);
}
