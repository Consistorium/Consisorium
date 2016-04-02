#pragma once

#include <SDL\SDL_mixer.h>

namespace GameEngineAudio
{
	class SoundEffect {
	private:
		Mix_Chunk* m_chunk = nullptr;
		static int playSoundEffect(void* loops);
	public:
		friend class AudioEngine;

		/// Plays the effect file
		/// @param loops: If loops == -1, loop forever,
		/// otherwise play it loops+1 times 
		void play(int loops = 0);
	};
}