// Header files
#include "Game.h"
#include "GlobalEnvironment.h"
#include "test.h"
#include <ctime>

// Change these as needed
const std::string APPTITLE = "Joe's Inferno";

bool Game::InitializeGame()
{
	// Seed the random number generator in case it's needed later
	srand(time(NULL));

	// For MP3
	CoInitialize(0);

	// Register with Event System
	ID = gEnv->getNewID();

	return true;
}

void Game::CreateLevel()
{
	// Invoke the function that levelPointer points to
	// levelPointer();

	IGameObject* pTemp = new Test();
	GameObjects.push_back(pTemp);

	// Reset the gameOver flag so that the next level can begin
	gameOver = false;
}

void Game::Update()
{

}

void Game::Render()
{
    // Make sure the Direct3D device is valid
	if (!gEnv->getD3DManager()->getD3DDevice())
	{
		// TODO: Create proper error message
		return;
	}
								
	gEnv->getD3DManager()->getD3DDevice()->Clear(0, NULL, D3DCLEAR_TARGET, 255, 0.0f, 0);
	// Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(55, 55, 55), 1.0f, 0);
	//gEnv->getD3DManager()->getD3DDevice()->SetTexture(0, NULL);

	 // Start rendering
	if (gEnv->getD3DManager()->getD3DDevice()->BeginScene())
    {
		gEnv->getD3DManager()->getSpriteObject()->Begin(D3DXSPRITE_ALPHABLEND);

		IRenderableObject* pRenderObject = NULL;

		for (goIt = GameObjects.begin(); goIt != GameObjects.end(); ++goIt)
		{
			pRenderObject = dynamic_cast<IRenderableObject*>((*goIt));

			if (pRenderObject)
			{
				pRenderObject->Render();
			}
		}

		gEnv->getD3DManager()->getSpriteObject()->End();

		gEnv->getD3DManager()->getD3DDevice()->EndScene();
		gEnv->getD3DManager()->getD3DDevice()->Present(NULL, NULL, NULL, NULL);
	}
}

void Game::HandleEvent(Event* pEvent)
{
	
}

void Game::PurgeGameObjects()
{
	// Deallocate any memory before switching to the new vector
	for (goIt = GameObjects.begin(); goIt != GameObjects.end();
		/* INTENTIONALLY LEFT BLANK */)
	{
		delete (*goIt);
		goIt = GameObjects.erase(goIt);
	}
}

const unsigned int Game::getFrameInterval()
{
	return frameInterval;
}

void Game::setFrameInterval(unsigned int newFrameInterval)
{
	frameInterval = newFrameInterval;
}

void Game::setGameObjects(std::vector<IGameObject*> levelInformation)
{
	// Deallocate any memory before switching to the new vector
	for (goIt = GameObjects.begin(); goIt != GameObjects.end();
		/* INTENTIONALLY LEFT BLANK */)
	{
		delete (*goIt);
		goIt = GameObjects.erase(goIt);
	}

	// Shallow copy the vector to preserve the pointers
	GameObjects = levelInformation;
}

Game::Game()
{
	gameOver = false;
	endProgram = false;
	frameInterval = 60;
	GameObjects.clear();

	// levelPointer = &LevelMenu;
}

Game::~Game()
{
	PurgeGameObjects();
}