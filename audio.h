#pragma once
#include "vcpkg/installed/x86-windows/include/SDL2/SDL_mixer.h"

#include <string>

class Audio
{
public:
	//load a music file
	static Mix_Music* loadMusic(const std::string& path);
	//load a small sound file
	static Mix_Chunk* loadChunk(const std::string& path);
	//play a Mix_Music
	static void playMusic(Mix_Music* music);
	//play a Mix_Chunk
	static void playChunk(Mix_Chunk* chunk);
	//toggle if the music playing is paused
	static void toggleMusicPause();
};