#include "Audio_Effect_3D.hpp"

bool CAudio_Effect_3D::Init (ISoundEngine *SoundEngine)
{
	if (SoundEngine != ZERO)
	{
		m_SoundEngine = SoundEngine;

		m_Pos.X = 0.0f;
		m_Pos.Y = 0.0f;
		m_Pos.Z = 0.0f;
	}

	else
	{
		return false;
	}

	return true;
}

void CAudio_Effect_3D::Delete ()
{
}

void CAudio_Effect_3D::Load (const string Filename)
{
	m_Sound = m_SoundEngine->addSoundSourceFromFile (Filename.c_str ());
}

void CAudio_Effect_3D::Play ()
{
	m_SoundEngine->play3D (m_Sound, m_Pos);
}

bool CAudio_Effect_3D::IsPlaying ()
{
	return m_SoundEngine->isCurrentlyPlaying (m_Sound);
}

void CAudio_Effect_3D::SetPos (float X, float Y, float Z)
{
	m_Pos.X = X;
	m_Pos.Y = Y;
	m_Pos.Z = Z;
}