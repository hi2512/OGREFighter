#include "gui.h"
#include <ImguiManager.h>

void GameGui::showScore(){
	ImGui::Begin("Scoreboard", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	if(ImGui::Button("Next Game")){
		this->state->nextRound();
	}
	ImGui::SameLine();
	if(ImGui::Button("Exit")){
		this->state->shouldExit = true;
	}
	ImGui::End();
}

bool GameGui::showGameStart(){
	bool result = false;
	ImGui::Begin("Game", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	if(ImGui::Button("Single Player")){
		this->state->startGame();
		result = true;
	}
	ImGui::SameLine();
	if(ImGui::Button("Exit")){
		this->state->shouldExit = true;
	}
	ImGui::End();
	return result;
}

void GameGui::showLoseScreen(){
	ImGui::Begin("Game", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("You lost :(");
	if(ImGui::Button("Exit")){
		this->state->shouldExit = true;
	}
	ImGui::End();
}

void GameGui::showWinScreen(){
	ImGui::Begin("Game", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("You won!");
	if(ImGui::Button("Exit")){
		this->state->shouldExit = true;
	}
	ImGui::End();
}


void GameGui::showWaitingOnPlayers(){
	ImGui::Begin("Game", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Waiting on players...");
	ImGui::End();
}
