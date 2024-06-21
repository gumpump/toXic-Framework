#ifndef PUMPGUN_IS_DEFINED
#define PUMPGUN_IS_DEFINED

#include "Gun_Base.hpp"

class CPumpgun : public CGun_Base
{
	public:
		bool Init ();
		void Delete ();

		void SetShootSound  (CAudio_Effect *Shoot);
		void SetReloadSoundLvl1 (CAudio_Effect *Reload);
		void SetReloadSoundLvl2 (CAudio_Effect *Reload);
		void SetReloadMagazineSound (CAudio_Effect *Reload) {m_Reload_Mag = Reload;}

		void SetClip (int Value) {m_MagCap = Value;}

		void Shoot ();
		void Reload (int Lvl);

	private:
		CAudio_Effect *m_Shoot;
		CAudio_Effect *m_ReloadLvl1;
		CAudio_Effect *m_ReloadLvl2;
		CAudio_Effect *m_Reload_Mag;
		int m_MagCap;
		bool m_ShotLock;
};
#endif