#ifndef AUDIO_EFFECT_2D_IS_DEFINED
#define AUDIO_EFFECT_2D_IS_DEFINED

#include "Audio_Device.hpp"

class CAudio_Effect_2D
{
	public:
		bool Init (ISoundEngine *SoundEngine);
		void Delete ();

		void Load (const string Filename);
		void Play ();

		bool IsPlaying ();

	private:
		ISoundEngine *m_SoundEngine;
		ISoundSource *m_Sound;
};
#endif