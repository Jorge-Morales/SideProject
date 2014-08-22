#ifndef MP3_H
#define MP3_H

#include <DShow.h>

class MP3
{
private:
	IGraphBuilder *g_pDSGraphBuilder;
	IMediaControl * g_pDSMediaControl;
	IMediaEvent *g_pDSMediaEvent;

public:
	MP3();
	~MP3();

	BOOL PlaySongMP3(const char *filename);

	void MP3Stop();
	void MP3Run();
	void MP3Pause();
	BOOL MP3Init();
	void MP3Release();

	bool IsPlaying;
};

#endif