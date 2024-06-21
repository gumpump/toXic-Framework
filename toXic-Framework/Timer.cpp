#include "Timer.hpp"

void CTimer::Start (int Value)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_lFrequency);

	QueryPerformanceCounter ((LARGE_INTEGER*) &m_lCurCount);

	m_lLastCount = m_lCurCount;

	m_lCurCountElapsed = timeGetTime () / 1000.0f;

	m_lLastCountElapsed = m_lCurCountElapsed;

	m_fElapsed = 0.0f;

	m_bActive = true;
}

void CTimer::Update (float Elapsed)
{
	QueryPerformanceCounter ((LARGE_INTEGER*) &m_lCurCount);

	if (m_lCurCount - m_lLastCount > m_lFrequency)
	{
		m_lLastCount = m_lCurCount;
		m_Framerate = m_CurFrame;
		m_CurFrame = 0;

		if (m_Framerate == 0)
		{
			m_Framerate = 1;
		}
	}

	else
	{
		m_CurFrame++;
	}

	m_lCurCountElapsed = timeGetTime () / 1000.0f;

	m_fElapsed = m_lCurCountElapsed - m_lLastCountElapsed;
	m_lLastCountElapsed = m_lCurCountElapsed;
}

void CTimer::Delete ()
{
	m_bActive = false;
}

int CTimer::GetFramerate ()
{
	if (m_Framerate == 0)
	{
		m_Framerate = 1;
	}

	return m_Framerate;
}

float CTimer::GetElapsed ()
{
	return m_fElapsed;
}