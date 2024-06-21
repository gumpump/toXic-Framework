#include "Pumpgun.hpp"

bool CPumpgun::Init ()
{
	m_ShotLock = true;

	return true;
}

void CPumpgun::Delete ()
{
	m_Shoot->Delete ();
	m_ReloadLvl1->Delete ();
	m_ReloadLvl2->Delete ();
}

void CPumpgun::SetShootSound (CAudio_Effect *Shoot)
{
	m_Shoot = Shoot;
}

void CPumpgun::SetReloadSoundLvl1 (CAudio_Effect *Reload)
{
	m_ReloadLvl1 = Reload;
}

void CPumpgun::SetReloadSoundLvl2 (CAudio_Effect *Reload)
{
	m_ReloadLvl2 = Reload;
}

void CPumpgun::Shoot ()
{
	if (m_ShotLock == false)
	{
		m_Shoot->Play ();
		m_ShotLock = true;
	}
}

void CPumpgun::Reload (int Lvl)
{
	if (m_ShotLock == true)
	{
		if (Lvl == 1)
		{
			m_ReloadLvl1->Play ();
		}

		else if (Lvl == 2)
		{
			m_ReloadLvl2->Play ();
			m_ShotLock = false;
		}
	}
}