#include "audio.h"

Mix_Music* Audio::loadMusic(const std::string& path)
{
	return Mix_LoadMUS(path.c_str());
}

Mix_Chunk* Audio::loadChunk(const std::string& path)
{
	return Mix_LoadWAV(path.c_str());
}

void Audio::playMusic(Mix_Music* music)
{
	Mix_PlayMusic(music, -1);
}

void Audio::playChunk(Mix_Chunk* chunk)
{
	Mix_PlayChannel(-1, chunk, 0);
}

void Audio::toggleMusicPause()
{
	if (Mix_PausedMusic() == 1)
	{
		Mix_ResumeMusic();
	}
	else
	{
		Mix_PauseMusic();
	}
}
