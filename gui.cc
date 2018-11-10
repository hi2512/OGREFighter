#include "gui.h"
#include <ImguiManager.h>

using namespace std;
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
	//ImGui::SetNextWindowPos(ImVec2(250, 200));
	ImGui::End();

}

void GameGui::showInputBuffer() {
	ImGui::Begin("InputBuffer", NULL,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	auto buf = state->inputBuffer;

	for (int i = 0; i < 20 && ((int) buf->size() - (1 + i) >= 0); i++) {
		auto ax = buf->at(buf->size() - (1 + i));
		int input = get<0>(ax);
		Uint32 frame = get<1>(ax);
		if(input > 127) {
			//handle non keyboard characters
			switch(input) {
			case OgreBites::SDLK_LEFT:
				ImGui::Text("Input: <-, Frame Inputed: %d", frame);
				break;
			case OgreBites::SDLK_UP:
				ImGui::Text("Input: ^, Frame Inputed: %d", frame);
				break;
			case OgreBites::SDLK_RIGHT:
				ImGui::Text("Input: ->, Frame Inputed: %d", frame);
				break;
			case OgreBites::SDLK_DOWN:
				ImGui::Text("Input: V, Frame Inputed: %d", frame);
				break;

			}
		} else {
			ImGui::Text("Input: %c, Frame Inputed: %d", input, frame);
		}
	}
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
