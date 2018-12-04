#ifndef ACTORCONTROLLER_H_
#define ACTORCONTROLLER_H_

#include "InputContainer.h"

class ActorController {
protected:

public:
	virtual bool checkForInput(InputType it) {
		return false;
	}
	virtual bool readQCF() {
		return false;
	}
	virtual bool readQCB() {
		return false;
	}
	virtual bool readDoubleQCF() {
		return false;
	}
	virtual bool readDoubleQCB() {
		return false;
	}

};

#endif /* ACTORCONTROLLER_H_ */
