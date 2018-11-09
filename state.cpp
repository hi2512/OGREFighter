
#include "state.h"


void GameState::enterPauseState(){
	SDL_SetRelativeMouseMode(SDL_FALSE);
}

void GameState::leavePauseState(){
	playMusic("../assets/Upbeat Forever.wav", SDL_MIX_MAXVOLUME/3);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}