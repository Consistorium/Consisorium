#include <stdio.h>

#include "Music.h"

namespace GameEngineAudio
{
	struct MusicArgs
	{
		int loops;
		Mix_Music* music;
	};

	int Music::playMusic(void* args) 
	{
		MusicArgs* musicArgs = (MusicArgs*)(args);
		Mix_PlayMusic(musicArgs->music, musicArgs->loops);

		return 0;
	}

	void Music::play(int loops /* = -1 */) {
		MusicArgs musicArgs;
		musicArgs.loops = loops;
		musicArgs.music = m_music;

		SDL_Thread *thread;
		int threadReturnValue;

		// Simply create a thread
		thread = SDL_CreateThread(playMusic, "PlaySoundEffect", (void *)&musicArgs);

		if (NULL == thread) {
			printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
		}
		else {
			SDL_WaitThread(thread, &threadReturnValue);
			printf("\nThread returned value: %d", threadReturnValue);
		}
	}

	void Music::pause() {
		Mix_PauseMusic();
	}

	void Music::stop() {
		Mix_HaltMusic();
	}

	void Music::resume() {
		Mix_ResumeMusic();
	}
}