#ifndef GENV_H
#define GENV_H

#include "TextureManager.h"
#include "InputManager.h"
#include "EventDispatcher.h"
#include "BackgroundManager.h"
#include "DirectXManager.h"

const unsigned int SCREENW = 1920;
const unsigned int SCREENH =  1080;
const bool fullscreen = false;

/*
	GlobalEnvironment is a managed global file that stores pointers to commonly 
	needed Managers, Windows/DX9 variables, timing variables, and a pointer 
	to the player.

	It is accessible through the gEnv pointer.
*/
class GlobalEnvironment
{
private:

	// Objects that need to be globally accessible in some way
	EventDispatcher* EventDispatcherInstance;
	TextureManager* TextureManagerInstance;
	InputManager* InputManagerInstance;
	BackgroundManager* BackgroundManagerInstance;
	D3DManager* D3DManagerInstance;

	// Reference to our active window
	HWND* window;

	/*
		Objects need a unique ID so that they can be indentified in the Event
		System. 
		
		Being that we don't have a concrete place where object instantiation
		is occuring at (shame on us), we're going to leave this here until we come
		up with a better method.
	*/
	unsigned int ID;

	GlobalEnvironment();

public: 

	static GlobalEnvironment& getInstance()
	{
		static GlobalEnvironment* pInstance = NULL;

		if (!pInstance)
		{
			pInstance = new GlobalEnvironment();
		}

		return (*pInstance);
	}

	// Retrieve instance of all objects that need to be globally accessible
	bool Initialize();
	
	// getters that return a pointer to the requested objects
	EventDispatcher* getEventDispatcher();
	TextureManager* getTextureManager();
	InputManager* getInputManager();
	BackgroundManager* getBackgroundManager();
	D3DManager* getD3DManager();
	HWND& getWindow();
	

	// getters that just return a value
	unsigned int getNewID();

	// TODO: IMPLEMENT
	Delegate CreateDelegate();

	/*
		Deallocate any memory associated with this object

		For DirectX objects, this involves the additional step of calling
		the Release function to deal with any DirectX specific cleanups
	*/
	~GlobalEnvironment();
};

static GlobalEnvironment* gEnv = &GlobalEnvironment::getInstance();
#endif