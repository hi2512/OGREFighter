#include "gui.h"
#include <ImguiManager.h>

using namespace std;
void GameGui::showHealth1() {
	ImGui::Begin("Player 1 Health", NULL,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	auto size = ImGui::GetIO().DisplaySize;
	//ImGui::SetWindowPos(ImVec2(100, 500));
	ImGui::SetWindowPos(ImVec2(size.x / 14, size.y / 1.5));
	ImGui::Text("HEALTH                   ");
	ImGui::ProgressBar(state->p1->getHealth() / state->p1->getMaxHealth());
	ImGui::End();
}

void GameGui::showHealth2() {
	ImGui::Begin("Player 2 Health", NULL,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	auto size = ImGui::GetIO().DisplaySize;
	//ImGui::SetWindowPos(ImVec2(1100, 500));
	ImGui::SetWindowPos(ImVec2(size.x / 1.254, size.y / 1.5));
	ImGui::Text("HEALTH                   ");
	ImGui::ProgressBar(state->p2->getHealth() / state->p2->getMaxHealth());
	ImGui::End();
}

void GameGui::showComboCounter1() {
	ImGui::Begin("Player 1", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	auto size = ImGui::GetIO().DisplaySize;
	//ImGui::SetWindowPos(ImVec2(100, 50));
	ImGui::SetWindowPos(ImVec2(size.x / 14, size.y / 15.6));
	ImGui::Text("%d Hits    ", this->state->p1->comboCount());
	ImGui::End();
}
void GameGui::showComboCounter2() {
	ImGui::Begin("Player 2", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	auto size = ImGui::GetIO().DisplaySize;
	//ImGui::SetWindowPos(ImVec2(1100, 50));
	ImGui::SetWindowPos(ImVec2(size.x / 1.254, size.y / 15.6));
	ImGui::Text("%d Hits    ", this->state->p2->comboCount());
	ImGui::End();
}

void GameGui::showMeter1() {
	ImGui::Begin("Player 1 Meter", NULL,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	auto size = ImGui::GetIO().DisplaySize;
	//ImGui::SetWindowPos(ImVec2(100, 600));
	ImGui::SetWindowPos(ImVec2(size.x / 14, size.y / 1.3));
	ImGui::Text("SUPER                   ");
	ImGui::ProgressBar(state->p1->getMeterVal() / state->p1->getMeterMax());
	ImGui::End();
}

void GameGui::showMeter2() {
	ImGui::Begin("Player 2 Meter", NULL,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	auto size = ImGui::GetIO().DisplaySize;
	//ImGui::SetWindowPos(ImVec2(1100, 600));
	ImGui::SetWindowPos(ImVec2(size.x / 1.254, size.y / 1.3));
	ImGui::Text("SUPER                   ");
	ImGui::ProgressBar(state->p2->getMeterVal() / state->p2->getMeterMax());
	ImGui::End();
}

void GameGui::showFrameCount(float fps) {
	ImGui::Begin("Frame Count", NULL,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Frame Number: %d", this->state->frameCount);
	ImGui::Text("FPS: %f", fps);
	//ImGui::SetNextWindowPos(ImVec2(250, 50));
	ImGui::End();
}

void GameGui::showTime() {
	ImGui::Begin("Time", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	auto size = ImGui::GetIO().DisplaySize;
	//ImGui::SetWindowPos(ImVec2(650, 50));
	ImGui::SetWindowPos(ImVec2(size.x / 2.12, size.y / 15.6));
	ImGui::Text("%d  \n", state->getTime());
	ImGui::End();
}

void GameGui::showCamPos() {
	ImGui::Begin("Camera Position", NULL,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowPos(ImVec2(300, 50));
	ImGui::Text("Camera X Position: %f", state->camPos.x);
	ImGui::Text("Camera Y Position: %f", state->camPos.y);
	ImGui::Text("Camera Z Position: %f", state->camPos.z);

	//ImVec2 windowPos = ImGui::GetWindowPos();
	ImVec2 windowPos = ImGui::GetWindowContentRegionMax();

	ImGui::Text("Window X Position: %f", windowPos.x);
	ImGui::Text("Window Y Position: %f", windowPos.y);

	auto size = ImGui::GetIO().DisplaySize;
	ImGui::Text("Render Window X Size: %f", size.x);
	ImGui::Text("Render Window Y Size: %f", size.y);

	//ImGui::SetNextWindowPos(ImVec2(250, 200));
	ImGui::End();

}

void GameGui::showInputBuffer() {
	ImGui::Begin("Input Buffer", NULL,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowPos(ImVec2(1000, 50));
	auto buf = state->inputBuffer;
	for (int i = 0; i < 20 && ((int) buf->size() - (1 + i) >= 0); i++) {
		auto ax = buf->at(buf->size() - (1 + i));
		int input = ax.key;
		Uint32 frame = ax.frame;
		if (input > 127) {
			//handle non keyboard characters
			switch (input) {
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
			case OgreBites::SDLK_F1:
				ImGui::Text("Input: F1, Frame Inputed: %d", frame);
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
	bool result = true;
	ImGui::Begin("Game", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	auto size = ImGui::GetIO().DisplaySize;
	ImGui::SetWindowPos(ImVec2(size.x / 2.5, size.y / 2.5));
	if (ImGui::Button("Single Player")) {
		this->state->showP1Select = true;
		result = false;
	}
	if (ImGui::Button("Two Players")) {
		this->state->showP1Select = true;
		this->state->showP2Select = true;
		state->multiplayer = true;
		result = false;
	}
	ImGui::SameLine();
	if (ImGui::Button("Exit")) {
		this->state->shouldExit = true;
	}
	ImGui::End();
	return result;
}

bool GameGui::showCharacterSelect1() {
	ImGui::Begin("Player 1 Character", NULL,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	bool res = true;
	auto size = ImGui::GetIO().DisplaySize;
	ImGui::SetWindowPos(ImVec2(size.x / 14, size.y / 2));
	if (ImGui::Button("Ninja        ")) {
		state->p1Char = CharacterType::NINJA;
		res = false;
	}
	if (ImGui::Button("Silver Ninja    ")) {
		state->p1Char = CharacterType::NINJAALT;
		res = false;
	}
	ImGui::End();
	return res;
}

bool GameGui::showCharacterSelect2() {
	ImGui::Begin("Player 2 Character", NULL,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	bool res = true;
	auto size = ImGui::GetIO().DisplaySize;
	ImGui::SetWindowPos(ImVec2(size.x / 1.254, size.y / 2));
	if (ImGui::Button("Ninja        ")) {
		state->p2Char = CharacterType::NINJA;
		res = false;
	}
	if (ImGui::Button("Silver Ninja    ")) {
		state->p2Char = CharacterType::NINJAALT;
		res = false;
	}
	ImGui::End();
	return res;
}

void GameGui::showLoseScreen() {
	ImGui::Begin("Game", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("You lost :(");
	if (ImGui::Button("Exit")) {
		this->state->shouldExit = true;
	}
	ImGui::End();
}

void GameGui::showWinScreen() {
	ImGui::Begin("Game", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	auto size = ImGui::GetIO().DisplaySize;
	ImGui::SetWindowPos(ImVec2(size.x / 2.12, size.y / 2));
	if (state->winner == NULL) {
		ImGui::Text("TIME OVER");
	} else if (state->winner == state->p1) {
		ImGui::Text("Player 1 wins!");
	} else {
		ImGui::Text("Player 2 wins!");
	}
	/*
	 if (ImGui::Button("Exit")) {
	 this->state->shouldExit = true;
	 }
	 */
	ImGui::End();
}

void GameGui::showWaitingOnPlayers() {
	ImGui::Begin("Game", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Waiting on players...");
	ImGui::End();
}
