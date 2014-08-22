#include "MP3.h"

// TOR
MP3::MP3()
{
	g_pDSGraphBuilder = NULL;
	g_pDSMediaControl = NULL;
	g_pDSMediaEvent = NULL;

	IsPlaying = false;

	MP3Init();
}

MP3::~MP3()
{
	MP3Release();
}

BOOL MP3::PlaySongMP3(const char *filename)
{
	// Convert filename into wide character string
	WCHAR wFilename[MAX_PATH];
	mbstowcs(wFilename, filename, MAX_PATH);

	// Render the file
	g_pDSGraphBuilder->RenderFile(wFilename, NULL);

	//Play the file
	g_pDSMediaControl->Run();

	return TRUE;
}

void MP3::MP3Stop()
{
	g_pDSMediaControl->Stop();
}

void MP3::MP3Run()
{
	g_pDSMediaControl->Run();
}

void MP3::MP3Pause()
{
	g_pDSMediaControl->Pause();
}

BOOL MP3::MP3Init()
{
	// Initializing and configuring the Direct Show
	if (FAILED(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void**)&g_pDSGraphBuilder)))
	{
		MessageBox(NULL, "THAT WAS A HELLUVA FAILURE", "MP3INIT", MB_OK);

		return FALSE;
	}

	// Query for media controls
	g_pDSGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&g_pDSMediaControl);
	g_pDSGraphBuilder->QueryInterface(IID_IMediaEvent, (void**)&g_pDSMediaEvent);

	return TRUE;
}

void MP3::MP3Release()
{
	g_pDSGraphBuilder->Release();
	g_pDSGraphBuilder = NULL;

	g_pDSMediaControl->Stop();
	g_pDSMediaControl->Release();
	g_pDSMediaControl = NULL;

	g_pDSMediaEvent->Release();
	g_pDSMediaEvent = NULL;
}