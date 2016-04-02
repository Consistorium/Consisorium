#pragma once

#include <SDL\SDL_mixer.h>

namespace GameEngineAudio
{
	class Music {
	private:
		static int Music::playMusic(void* arg);
		Mix_Music* m_music = nullptr;
	public:
		friend class AudioEngine;

		/// Plays the music file
		/// @param loops: If loops == -1, loop forever,
		/// otherwise play it loops times 
		void play(int loops = 1);

		/// Pauses whatever song is currently playing
		static void pause();
		/// Stops whatever song is currently playing
		static void stop();
		/// Resumes whatever song is currently playing
		static void resume();
	};
}