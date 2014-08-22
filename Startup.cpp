// Beginning Game Programming, Third Edition
// MyWindows.cpp

#include "GlobalEnvironment.h"
#include "Game.h"

using namespace std;

#pragma (ignore, 4244)

string APPTITLE = "RGB_Hell";

LRESULT WINAPI WinProc( HWND hWnd, UINT Event, WPARAM wParam, LPARAM lParam )
{
    switch (Event)
    {
        case WM_DESTROY:

			if (GameInstance)
			{
				delete GameInstance;
			}

			if (gEnv)
			{
				delete gEnv;
			}

            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc( hWnd, Event, wParam, lParam );
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //initialize window settings
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX); 
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)WinProc;
    wc.cbClsExtra	 = 0;
    wc.cbWndExtra	 = 0;
    wc.hInstance     = hInstance;
	wc.hIcon		 = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = APPTITLE.c_str();  
    wc.hIconSm       = NULL;
    RegisterClassEx(&wc);
    
	gEnv->getWindow() = CreateWindow(APPTITLE.c_str(), APPTITLE.c_str(),
			 WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			 SCREENW, SCREENH, NULL, NULL, hInstance, NULL);

    if (!gEnv->getWindow())
	{
		MessageBox(NULL, "Window didn't load?", "gEnv did not load window", MB_OK);
		return 0;
	}

    // Display the window that the game will run in 
    ShowWindow(gEnv->getWindow(), nCmdShow);
	UpdateWindow(gEnv->getWindow());

	// Initialize the Global Environment
	gEnv->Initialize();
	
	//initialize the game
	if (!GameInstance->InitializeGame())
	{
		// TODO: Generate an appropriate error message
		return 0;
	}

	// Player input vector default values. This should be managed somewhere
	// std::vector<int>InputKeys;
	// gEnv->getInputManager()->setKeyboardKeys(InputKeys);

	MSG msg;

	long long startTime = 0;

	// The game as a whole
	while (!GameInstance->endProgram)
	{
		GameInstance->PurgeGameObjects();
		GameInstance->CreateLevel();

		// A particular game level
		while (!GameInstance->gameOver)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (GetTickCount() > startTime + ((1 / GameInstance->getFrameInterval()) * 1000))
			{
				GameInstance->Update();
				startTime = GetTickCount();
			}

			GameInstance->Render();
			gEnv->getEventDispatcher()->Update();
		}
	}

    // Memory cleanup
	delete GameInstance;
	delete gEnv;
	return msg.wParam;
}