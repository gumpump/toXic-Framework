#include "Process_Timer.hpp"

CProcess_Timer::CProcess_Timer ()
{
	m_fTimer = 0.0f;
	m_fEndTime = 0.0f;
	m_bActive = false;
	m_nNextValue = 0;
}

CProcess_Timer::~CProcess_Timer ()
{
}

void CProcess_Timer::Start (int Value)
{
	m_fEndTime = static_cast<float> (Value);
	m_bActive = true;
}

void CProcess_Timer::Update (float Elapsed)
{
	m_fTimer += Elapsed;

	if (m_fTimer >= m_fEndTime)
	{
		Kill ();
	}

	else
	{
		// Do nothing and go on
		// Like in real life
	}
}

void CProcess_Timer::Kill()
{
	m_bActive = false;
}