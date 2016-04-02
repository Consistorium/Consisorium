#include <SDL\SDL_thread.h>
#include <SDL\SDL_timer.h>

#include "SoundEffect.h"
#include"BengineErrors.h"

namespace GameEngineAudio
{
	struct SoundArgs
	{
		int loops;
		Mix_Chunk* chunk;
	};

	int SoundEffect::playSoundEffect(void* arg)
	{
		SoundArgs* soundArgs = (SoundArgs*)(arg);

		int loops = (int)arg;
		if (Mix_PlayChannel(-1, soundArgs->chunk, soundArgs->loops) == -1) {
			if (Mix_PlayChannel(0, soundArgs->chunk, soundArgs->loops) == -1) {
				Bengine::fatalError("Mix_PlayChannel error: " + std::string(Mix_GetError()));
				return -1;
			}
		}

		return 0;
	}

	void SoundEffect::play(int loops /* = 0 */) {
		SoundArgs soundArgs;
		soundArgs.loops = loops;
		soundArgs.chunk = m_chunk;

		SDL_Thread *thread;
		int threadReturnValue;

		// Simply create a thread
		thread = SDL_CreateThread(playSoundEffect, "PlaySoundEffect", (void *)&soundArgs);

		if (NULL == thread) {
			printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
		}
		else {
			SDL_Delay(200); //  exceptionally good code practice
			SDL_WaitThread(thread, &threadReturnValue);
			printf("\nThread returned value: %d", threadReturnValue);
		}
	}
}