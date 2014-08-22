#include "InputManager.h"
#include "GlobalEnvironment.h"
#include "IInputDevice.h"
#include "IGameObject.h"

void InputManager::setInputDevice_Mouse(IInputDevice* pMouse)
{
	this->pMouse = pMouse;
}

void InputManager::setInputDevice_Keyboard(IInputDevice* pKeyboard)
{
	this->pKeyboard = pKeyboard;
}

void InputManager::setKeyboardKeys(const std::vector<int>& DIKCodes)
{
	keyboardDIKCodes = DIKCodes;
}

void InputManager::Update()
{
	// Poll the virtual input devices
	DirectInputUpdate();

	// If a mouse 
	if (pMouse)
	{
		unsigned int mouseMask = 0;

		if (mouse_state.rgbButtons[0] & 0x80)
		{
			mouseMask |= 1;
		}

		if (mouse_state.rgbButtons[1] & 0x80)
		{
			mouseMask |= 2;
		}

		// Attempt to Update the object
		IGameObject* pTemp = dynamic_cast<IGameObject*>(pMouse);
		if (pTemp)
		{
			pTemp->Update();
		}

		// Pass the input mask to the InputDevice to be processed
		pMouse->ProcessInput(mouseMask);
	}

	if (pKeyboard)
	{
		unsigned int keyboardMask = 0;

		if (keyboardDIKCodes.size() != 0)
		{
			/*
				This loop iterates through the DIK Key vector, and checks to see
				if any input has occured.

				If input has occured, the mask is bitwise OR'd by 1 bit-shifted 
				left by the value of i. 
			*/
			for (int i = 0; i < keyboardDIKCodes.size(); ++i)
			{
				if ((bool)(keys[keyboardDIKCodes[i]] & 0x80))
				{
					keyboardMask |= (1 << i);
				}
			}

			// Attempt to Update the object
			IGameObject* pTemp = dynamic_cast<IGameObject*>(pKeyboard);
			if (pTemp)
			{
				pTemp->Update();
			}

			// Pass the input mask to the InputDevice to be processed
			pKeyboard->ProcessInput(keyboardMask);
		}
	}
}

void InputManager::Render()
{
	// Attempt to render the keyboard
	IRenderableObject* pTemp = dynamic_cast<IRenderableObject*>(pKeyboard);
	if (pTemp)
	{
		pTemp->Render();
	}

	// Attempt to render the mouse
	pTemp = dynamic_cast<IRenderableObject*>(pMouse);
	if (pTemp)
	{
		pTemp->Render();
	}
}

void InputManager::DirectInputInit()
{
	// Initialize DirectInput object
	DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&dInput,
		NULL);
	
	// Initialize the virtual keyboard
	dInput->CreateDevice(GUID_SysKeyboard, &diKeyboard, NULL);
	diKeyboard->SetDataFormat(&c_dfDIKeyboard);
	diKeyboard->SetCooperativeLevel(gEnv->getWindow(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	diKeyboard->Acquire();
	
	// Initialize the virtual mouse
	dInput->CreateDevice(GUID_SysMouse, &diMouse, NULL);
	diMouse->SetDataFormat(&c_dfDIMouse);
	diMouse->SetCooperativeLevel(gEnv->getWindow(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	diMouse->Acquire();
	gEnv->getD3DManager()->getD3DDevice()->ShowCursor(false);

	/*
		We don't support controllers right now, but I want to keep this code on hand,
		because it's something I'd like to do in the future.
	*/
	//for (int i = 0; i< 4; ++i)
	//{
	//	ZeroMemory(&controllers[i], sizeof(XINPUT_STATE));
	//
	//	//get the state of the controller
	//	XINPUT_STATE state;
	//	DWORD result = XInputgetState(i, &state);
	//
	//	//store state in global controllers array
	//	if (result == 0) controllers[i] = state.Gamepad;
	//}
}

void InputManager::DirectInputUpdate()
{
	// Update the virtual mouse
	if (diMouse)
	{
		diMouse->Poll();
		if (!SUCCEEDED(diMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouse_state)))
		{
			//mouse device lose, try to re-acquire
			diMouse->Acquire();
		}
	}
	
	// Update the virtual keyboard
	if (diKeyboard)
	{
		diKeyboard->Poll();
		if (!SUCCEEDED(diKeyboard->GetDeviceState(256, (LPVOID)&keys)))
		{
			//keyboard device lost, try to re-acquire
			diKeyboard->Acquire();
		}
	}
}

InputManager::InputManager()
{
	DirectInputInit();

	pMouse = NULL;
	pKeyboard = NULL;

	// If the InputManager ever needs to register for Events, this is where that would happen
}

InputManager::~InputManager()
{
	if (diKeyboard)
	{
		diKeyboard->Unacquire();
		diKeyboard->Release();
		diKeyboard = NULL;
	}
	if (diMouse)
	{
		diMouse->Unacquire();
		diMouse->Release();
		diMouse = NULL;
	}

	if (dInput)
	{
		dInput->Release();
	}

	if (pKeyboard)
	{
		delete pKeyboard;
		pKeyboard = NULL;
	}

	if (pMouse)
	{
		delete pMouse;
		pMouse = NULL;
	}
}