#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "IInputDevice.h"

class Keyboard : public IInputDevice
{
private:

public:

	void ProcessInput(const unsigned int mask);
	Keyboard();
	~Keyboard(){};
};

#endif