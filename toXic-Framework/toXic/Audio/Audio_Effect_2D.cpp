#include "Audio_Effect_2D.hpp"

bool CAudio_Effect_2D::Init (ISoundEngine *SoundEngine)
{
	if (SoundEngine != ZERO)
	{
		m_SoundEngine = SoundEngine;
	}

	else
	{
		return false;
	}

	return true;
}

void CAudio_Effect_2D::Delete ()
{
}

void CAudio_Effect_2D::Load (const string Filename)
{
	m_Sound = m_SoundEngine->addSoundSourceFromFile (Filename.c_str ());
}

void CAudio_Effect_2D::Play ()
{
	m_SoundEngine->play2D (m_Sound);
}

bool CAudio_Effect_2D::IsPlaying ()
{
	return m_SoundEngine->isCurrentlyPlaying (m_Sound);
}