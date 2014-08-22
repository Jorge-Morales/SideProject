#ifndef INPUTMAN_H
#define INPUTMAN_H

#pragma warning (disable : 4005)

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include <xinput.h>
#include <vector>

// Forward declare this here so we don't need to include the .h in this file
class IInputDevice;

class InputManager
{
private:

	// Keyboard input array
	char keys[256];

	// Input devices
	IInputDevice* pMouse;
	IInputDevice* pKeyboard;

	// Vector that stores the input keys we need to check for
	std::vector<int> keyboardDIKCodes;

	// DirectInput variables - These are required to 
	DIMOUSESTATE mouse_state;
	LPDIRECTINPUT8 dInput;
	LPDIRECTINPUTDEVICE8 diMouse;
	LPDIRECTINPUTDEVICE8 diKeyboard;

	// Not currently supporting controllers
	// XINPUT_GAMEPAD controllers[4];

	// DirectInput maintenence functions
	void DirectInputInit();
	void DirectInputUpdate();

	InputManager();

public:

	static InputManager& getInstance()
	{
		static InputManager* pInstance = NULL;

		if (!pInstance)
		{
			pInstance = new InputManager();
		}

		return (*pInstance);
	}

	/*
		Stores an IInputDevice as the desginated mouse for the purpose of passing it 
		mouse related input later in Update().
	*/
	void setInputDevice_Mouse(IInputDevice* pMouse);

	/*
		Stores an IInputDevice as the designated keyboard for the purpose of 
		passing it keyboard related input later in Update().
	*/
	void setInputDevice_Keyboard(IInputDevice* pKeyboard);

	/*
		Set the keyboardDIKCode vector so that input can be checked in Update().

		Call this function if the keys needed to perform an action change for some
		reason (I.E. keybinds were changed), or during first-time initialization to 
		ensure the correct keys are being checked for.
	*/
	void setKeyboardKeys(const std::vector<int>& DIKCodes); 

	/*
		Update calls DirectInputUpdate to get the most recent input, and than 
		checks for input based on whether or not an input device has been 
		'registered' with the InputManager.	

		Right now, the InputManager only checks for Left and Right mouse clicks.
		I belive the standard DirectInput functionality allows for the checking of
		6 different keys (scroll up, scroll down, scroll 'click', etc), but we don't
		need them right now so I haven't implemented that functionality.

		If a Keyboard is registered, Update will search through the keyboard key 
		vector, and check for inputs matching the key codes stored in the vector. 
		If input is detected, a corresponding flag will be set within a bitmask.

		Once all applicable input has been checked for, the masks are sent to their 
		target objects to be processed.
	*/
	void Update();

	/*
		Some input devices have a physical representation on the screen, and therefore
		need to be rendered. To make sure we don't inadvertently call Render() on an object
		that doesn't have the function, we attempt to dynamic_cast the object to an 
		IRenderableObject first.
	*/
	void Render();

	~InputManager();
};

#endif

/*
	We don't support controllers right now, but I want to keep this code on hand,
	because it's something I'd like to do in the future.
*/
//bool XInput_Controller_Found()
//{
//	XINPUT_CAPABILITIES caps;
//
//	ZeroMemory(&caps, sizeof(XINPUT_CAPABILITIES));
//	XInputgetCapabilities(0, XINPUT_FLAG_GAMEPAD, &caps);
//
//	if (caps.Type != 0)
//	{
//		return false;
//	}
//
//	return true;
//}
//
//void XInput_Vibrate(int contNum, int amount)
//{
//	XINPUT_VIBRATION vibration;
//	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
//	vibration.wLeftMotorSpeed = amount;
//	vibration.wRightMotorSpeed = amount;
//	XInputSetState(contNum, &vibration);
//}