#ifndef KEYBOARDCONTROLLER_H_
#define KEYBOARDCONTROLLER_H_

#include <iostream>
#include <queue>
#include "InputContainer.h"
#include <map>

#include "ActorController.h"

class KeyboardController: public ActorController {
protected:
	const int sizeLimit = 200;
	std::map<int, InputType> keyBinding;
	std::deque<KeyInput> inputBuffer;
	std::deque<KeyInput> releaseBuffer;
	std::vector<KeyInput> keysHeld;

	bool inKeysHeld(KeyInput ki, std::vector<KeyInput> kh) {
		//check if key was held
		for (KeyInput t : kh) {
			if (ki.key == t.key) {
				return true;
			}
		}
		return false;
	}
	bool keyIsInputType(KeyInput ki, InputType ipt) {
		if (!keyIsMapped(ki)) {
			//not mapped
			return false;
		}
		return this->keyBinding.at(ki.key) == ipt;
	}
	bool keyIsMapped(KeyInput ki) {
		if (this->keyBinding.find(ki.key) == this->keyBinding.end()) {
			//not mapped
			return false;
		}
		return true;
	}

public:
	KeyboardController(int left, int right, int up, int down, int light, int medium, int heavy) {
		keyBinding.insert(pair<int, InputType>(left, InputType::LEFT));
		keyBinding.insert(pair<int, InputType>(right, InputType::RIGHT));
		keyBinding.insert(pair<int, InputType>(up, InputType::UP));
		keyBinding.insert(pair<int, InputType>(down, InputType::DOWN));
		keyBinding.insert(pair<int, InputType>(light, InputType::L));
		keyBinding.insert(pair<int, InputType>(medium, InputType::M));
		keyBinding.insert(pair<int, InputType>(heavy, InputType::H));

	}
	void addKey(KeyInput ki) {
		//printf("adding key %c\n", ki.key);
		if (!keyIsMapped(ki)) {
			return;
		}
		if (inputBuffer.size() > sizeLimit) {
			inputBuffer.pop_front();
		}
		this->inputBuffer.push_back(ki);
		if (!inKeysHeld(ki, keysHeld)) {
			this->keysHeld.push_back(ki);
		}
	}
	void releaseKey(KeyInput ki) {
		if (!keyIsMapped(ki)) {
			return;
		}
		if (releaseBuffer.size() > 200) {
			releaseBuffer.pop_front();
		}
		this->releaseBuffer.push_back(ki);
		//remove from keys held
		for (auto it = keysHeld.begin(); it != keysHeld.end(); it++) {
			KeyInput t = *it;
			if (ki.key == t.key) {
				keysHeld.erase(it);
				break;
			}
		}
	}
	bool checkForInput(InputType it) {
		for (KeyInput ki : this->keysHeld) {
			if (this->keyBinding.find(ki.key) == this->keyBinding.end()) {
				//not mapped
				return false;
			}
			//printf("key is %c\n", ki.key);
			if (this->keyBinding.at(ki.key) == it) {
				return true;
			}
		}
		return false;
	}
	bool readQCF() {
		if (this->inputBuffer.empty()) {
			return false;
		}
		const int cancelWindow = 7;
		int endInputWindow = inputBuffer.back().frame - cancelWindow;
		bool right = false;
		bool drDown = false;
		bool drRight = false;
		bool down = false;
		Uint32 rightFrame, downRightFrame, downFrame;
		for (auto it = this->inputBuffer.rbegin(); it != this->inputBuffer.rend(); it++) {
			KeyInput cur = *it;
			if (cur.frame < endInputWindow) {
				//printf("INPUTS END\n");
				break;
			}
			if (!right) {
				//printf("checking right\n");
				//check for right
				right = this->keyIsInputType(cur, InputType::RIGHT);
				if (right) {
					rightFrame = cur.frame;
				}
				continue;
			}
			if (!down) {
				//printf("checking down\n");
				//check for down
				down = this->keyIsInputType(cur, InputType::DOWN);
				if (down) {
					//downFrame = cur.frame;
					//fufilled all requirements
					return true;
				}
				continue;
			}
		}
		return false;
	}

	bool readQCB() {
		if (this->inputBuffer.empty()) {
			return false;
		}
		const int cancelWindow = 7;
		int endInputWindow = inputBuffer.back().frame - cancelWindow;
		bool right = false;
		bool drDown = false;
		bool drRight = false;
		bool down = false;
		Uint32 rightFrame, downRightFrame, downFrame;
		for (auto it = this->inputBuffer.rbegin(); it != this->inputBuffer.rend(); it++) {
			KeyInput cur = *it;
			if (cur.frame < endInputWindow) {
				//printf("INPUTS END\n");
				break;
			}
			if (!right) {
				//check for right
				right = this->keyIsInputType(cur, InputType::LEFT);
				if (right) {
					rightFrame = cur.frame;
				}
				continue;
			}

			if (!down) {
				down = this->keyIsInputType(cur, InputType::DOWN);
				if (down) {
					//downFrame = cur.frame;
					//fufilled all requirements
					return true;
				}
				continue;
			}
		}
		return false;
	}

	bool readDoubleQCF() {
		if (this->inputBuffer.empty()) {
			return false;
		}
		const int cancelWindow = 20;
		int endInputWindow = inputBuffer.back().frame - cancelWindow;
		bool right1 = false;
		bool down1 = false;
		bool right2 = false;
		bool down2 = false;
		Uint32 right1Frame, down1Frame, right2Frame, down2Frame;
		for (auto it = this->inputBuffer.rbegin(); it != this->inputBuffer.rend(); it++) {
			KeyInput cur = *it;
			if (cur.frame < endInputWindow) {
				//printf("INPUTS END\n");
				break;
			}
			if (!right1) {
				//check for right
				right1 = this->keyIsInputType(cur, InputType::RIGHT);
				if (right1) {
					//printf("A\n");
					right1Frame = cur.frame;
				}
				continue;
			}
			if (!down1) {
				down1 = this->keyIsInputType(cur, InputType::DOWN);
				if (down1) {
					//printf("B\n");
					down1Frame = cur.frame;
				}
				continue;
			}
			if (!right2) {
				right2 = this->keyIsInputType(cur, InputType::RIGHT);
				if (right2) {
					//printf("C\n");
					right2Frame = cur.frame;
				}
				continue;
			}
			if (!down2) {
				down2 = this->keyIsInputType(cur, InputType::DOWN);
				if (down2) {
					//printf("D\n");
					return true;
				}
				continue;
			}
		}

		return false;
	}

	bool readDoubleQCB() {
		if (this->inputBuffer.empty()) {
			return false;
		}
		const int cancelWindow = 20;
		int endInputWindow = inputBuffer.back().frame - cancelWindow;
		bool left1 = false;
		bool down1 = false;
		bool left2 = false;
		bool down2 = false;
		Uint32 left1Frame, down1Frame, left2Frame, down2Frame;
		for (auto it = this->inputBuffer.rbegin(); it != this->inputBuffer.rend(); it++) {
			KeyInput cur = *it;
			if (cur.frame < endInputWindow) {
				//printf("INPUTS END\n");
				break;
			}
			if (!left1) {
				//check for right
				left1 = this->keyIsInputType(cur, InputType::LEFT);
				if (left1) {
					left1Frame = cur.frame;
				}
				continue;
			}
			if (!down1) {
				down1 = this->keyIsInputType(cur, InputType::DOWN);
				if (down1) {
					down1Frame = cur.frame;
				}
				continue;
			}
			if (!left2) {
				left2 = this->keyIsInputType(cur, InputType::LEFT);
				if (left2) {
					left2Frame = cur.frame;
				}
				continue;
			}
			if (!down2) {
				down2 = this->keyIsInputType(cur, InputType::DOWN);
				if (down2) {
					return true;
				}
				continue;
			}
		}

		return false;
	}
};

#endif /* KEYBOARDCONTROLLER_H_ */
