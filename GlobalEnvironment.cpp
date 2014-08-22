#include "GlobalEnvironment.h"

bool GlobalEnvironment::Initialize()
{
	// Initialize the DirectX Manager first because other managers have DirectX related dependencies
	D3DManagerInstance = &D3DManager::getInstance();

	if (!D3DManagerInstance->Initialize())
	{
		return false;
	}

	EventDispatcherInstance = &EventDispatcher::getInstance();
	TextureManagerInstance = &TextureManager::getInstance();
	InputManagerInstance = &InputManager::getInstance();
	BackgroundManagerInstance = &BackgroundManager::getInstance();
}

EventDispatcher* GlobalEnvironment::getEventDispatcher()
{
	return EventDispatcherInstance;
}

TextureManager* GlobalEnvironment::getTextureManager()
{
	return TextureManagerInstance;
}

InputManager* GlobalEnvironment::getInputManager()
{
	return InputManagerInstance;
}

BackgroundManager* GlobalEnvironment::getBackgroundManager()
{
	return BackgroundManagerInstance;
}

D3DManager* GlobalEnvironment::getD3DManager()
{
	return D3DManagerInstance;
}

HWND& GlobalEnvironment::getWindow()
{
	return (*window);
}

unsigned int GlobalEnvironment::getNewID()
{
	return ID++;
}

GlobalEnvironment::GlobalEnvironment()
{
	EventDispatcherInstance = NULL; 
	TextureManagerInstance = NULL;
	InputManagerInstance = NULL;
	BackgroundManagerInstance = NULL;
	D3DManagerInstance = NULL;
	window = new HWND();
	
	ID = 0;
}

GlobalEnvironment::~GlobalEnvironment()
{
	if (EventDispatcherInstance)
	{
		delete EventDispatcherInstance;
		EventDispatcherInstance = NULL;
	}

	if (TextureManagerInstance)
	{
		delete TextureManagerInstance;
		TextureManagerInstance = NULL;
	}

	if (InputManagerInstance)
	{
		delete InputManagerInstance;
		InputManagerInstance = NULL;
	}

	if (BackgroundManagerInstance)
	{
		delete BackgroundManagerInstance;
		BackgroundManagerInstance = NULL;
	}

	if (window)
	{
		delete window;
	}
}
