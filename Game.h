#ifndef GAME_H
#define GAME_H

#include "IGameObject.h"
#include <vector>

class Game : public IGameObject
{
private:

	std::vector<IGameObject*>GameObjects;
	std::vector<IGameObject*>::iterator goIt;
	
	/*
		The rate at which everything in the game will be updated. 
		
		This is done to ensure that the game runs nearly identically across
		a wide range of computer hardware by only allowing objects to update
		every (1 / frameInterval) number of milliseconds.

		This value defaults to 60, but can be changed through the setFrameInterval
		function.
	*/
	unsigned int frameInterval;

	/*
		Keeps track of the currently active level, so that we can go back into
		it if the player dies. Also used to make sure we don't reload the same
		assets unnecessarily.
	*/
	unsigned int currentLevel;

	/*
		A function pointer that is used to load the necessary assets needed for
		a given level.

		The level functions are defined in Game.cpp, and are kept seperate from 
		the Game Object so that Game doesn't need to have a function for every
		possible level. This allows us to easily add/remove levels without modifying
		too much code.
	*/
	void (*levelPointer)();

	Game();
public:

	static Game& getInstance()
	{
		static Game* pInstance = NULL;

		if (!pInstance)
		{
			pInstance = new Game();
		}

		return (*pInstance);
	}

	/*
		endProgram is set whenever the player selects an option that would cause
		the program to end (I.E clicking exit on the main menu).

		This is functionally different than the gameOver flag, and should not be
		used interchangably with it.
	*/
	bool endProgram;

	/*
		When the player beats a level, dies, or is otherwise removed from a level,
		this flag gets set to true. 
		
		Depending on what ended up causing the flag to change, the player is 
		either sent back to the main menu, sent onwards to the next level, or 
		starts the current level over again.
	*/
	bool gameOver;
	
	/*
		One time startup function that gets called in Startup.cpp.

		Initializes DirectX, and gets any other misc dependencies (random number
		generation, audio, etc) spun up.
	*/
	bool InitializeGame();

	/*
		This function is just a wrapper for levelPointer, and only serves to
		disallow direct access to the function pointer itself.

		This function just calls whatever levelPointer points to.
	*/
	void CreateLevel();

	/*
		Gets called every (1 / frameInterval) number of milliseconds in Startup.cpp

		This function is used to update all objects stored in the GameObjects vector,
		as well as all applicable managers (Input, AI, TemporaryObject, etc).
	*/
	void Update();

	/*
		This function is called as often as humanly possible in Startup.cpp, and is
		used to render all GameObjects, as well as any objects stored in applicable
		managers.
	*/
	void Render();

	void HandleEvent(Event* pEvent);

	/*
		Removes any active GameObjects from the GameObject vector.

		DO NOT CALL THIS DURING GAMEPLAY UNDER ANY CIRCUMSTANCES.
	*/
	void PurgeGameObjects();

	// Self-explanatory getter/setter
	const unsigned int getFrameInterval();
	void setFrameInterval(unsigned int newFrameInterval);

	/*
		Sets the GameObject member vector to be equal to the passed vector.

		This is used to allow us to have multiple levels without having to
		preload/cache every single asset that's going to be used in those levels.
	*/
	void setGameObjects(std::vector<IGameObject*> levelGameObjects);

	~Game();
};

// Game instance
static Game* GameInstance = &Game::getInstance();
#endif