#ifndef IINPUT_H
#define IINPUT_H

class IInputDevice
{
public:
	virtual void ProcessInput(const unsigned int mask) = 0;

	virtual ~IInputDevice(){}
};

#endif