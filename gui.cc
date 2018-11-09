#include "gui.h"
#include <ImguiManager.h>

void GameGui::showFrameCount() {
	ImGui::Begin("Scoreboard", NULL,
				ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Frame Number: %d", this->state->frameCount);
	ImGui::SetNextWindowPos(ImVec2(250, 50));
	ImGui::End();
}

void GameGui::showCamPos() {
	ImGui::Begin("CamPos", NULL,
					ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Camera X Position: %f", state->camPos.x);
	ImGui::Text("Camera Y Position: %f", state->camPos.y);
	ImGui::Text("Camera Z Position: %f", state->camPos.z);

	ImVec2 windowPos = ImGui::GetWindowPos();

	ImGui::Text("Window X Position: %f", windowPos.x);
	ImGui::Text("Window Y Position: %f", windowPos.y);
	ImGui::SetNextWindowPos(ImVec2(250, 0));
	ImGui::End();

}

void GameGui::showScore() {
	ImGui::Begin("Scoreboard", NULL,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::Button("Next Game")) {
		this->state->nextRound();
	}
	ImGui::SameLine();
	if (ImGui::Button("Exit")) {
		this->state->shouldExit = true;
	}
	ImGui::End();
}

bool GameGui::showGameStart() {
	bool result = false;
	ImGui::Begin("Game", NULL,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::Button("Single Player")) {
		this->state->startGame();
		result = true;
	}
	ImGui::SameLine();
	if (ImGui::Button("Exit")) {
		this->state->shouldExit = true;
	}
	ImGui::End();
	return result;
}

void GameGui::showLoseScreen() {
	ImGui::Begin("Game", NULL,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("You lost :(");
	if (ImGui::Button("Exit")) {
		this->state->shouldExit = true;
	}
	ImGui::End();
}

void GameGui::showWinScreen() {
	ImGui::Begin("Game", NULL,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("You won!");
	if (ImGui::Button("Exit")) {
		this->state->shouldExit = true;
	}
	ImGui::End();
}

void GameGui::showWaitingOnPlayers() {
	ImGui::Begin("Game", NULL,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Waiting on players...");
	ImGui::End();
}
