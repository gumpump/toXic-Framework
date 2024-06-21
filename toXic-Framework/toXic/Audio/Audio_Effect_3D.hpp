#ifndef AUDIO_EFFECT_3D_IS_DEFINED
#define AUDIO_EFFECT_3D_IS_DEFINED

#include "Audio_Device.hpp"

class CAudio_Effect_3D
{
	public:
		bool Init (ISoundEngine *SoundEngine);
		void Delete ();

		void Load (const string Filename);
		void Play ();

		bool IsPlaying ();

		void SetPos (float X, float Y, float Z);

	private:
		ISoundEngine *m_SoundEngine;
		ISoundSource *m_Sound;

		vec3df m_Pos;
};
#endif