#pragma once

#include <string>
#include <map>

#include <SDL\SDL_mixer.h>

#include "Music.h"
#include "SoundEffect.h"

namespace GameEngineAudio {
    class AudioEngine {
	private:

		std::map<std::string, Mix_Chunk*> m_effectMap; ///< Effects cache
		std::map<std::string, Mix_Music*> m_musicMap; ///< Music cache

		bool m_isInitialized = false;
    public:
        AudioEngine();
        ~AudioEngine();

        void init();
        void destroy();

		static AudioEngine& getInstance();
        SoundEffect loadSoundEffect(const std::string& filePath);
        Music loadMusic(const std::string& filePath);   
    };

}