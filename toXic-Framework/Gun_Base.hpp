#ifndef GUN_BASE_IS_DEFINED
#define GUN_BASE_IS_DEFINED

#include "toXic/Audio/Audio_Effect.hpp"

class CGun_Base
{
	public:
		virtual ~CGun_Base () {}

		// Klassen, die alle abgeleiteten Klassen
		// definieren müssen!
			virtual bool Init () {return false;}
			virtual void Delete () {}

			virtual void SetClip (int Value) {}

			virtual void SetShootSound  (CAudio_Effect *Shoot) {}
			virtual void SetReloadMagazineSound (CAudio_Effect *Reload) {}

			virtual void Shoot () {}
			virtual void ReloadMagazine () {}

		// Klassen, die Gestenerkennung benutzen
		
		// Für Gestenerkennung, damit für jede Geste ein Sound
		// abgespielt werden kann.
		virtual void SetReloadSoundLvl1 (CAudio_Effect *Reload) {}
		virtual void SetReloadSoundLvl2 (CAudio_Effect *Reload) {}

		virtual void Reload (int Lvl) {}

		// Funktionen, die nötig werden, wenn, wie bei einer Schrotflinte,
		// nach jedem Schuss nachgeladen wird.
		virtual void SetReloadSound (CAudio_Effect *Reload) {}
		virtual void Reload () {}
};
#endif