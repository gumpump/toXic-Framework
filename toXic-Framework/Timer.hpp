#ifndef TIMER_IS_DEFINED
#define TIMER_IS_DEFINED

#include "toXic/Common/Common.hpp"
#include "toXic/Process/Process_Base.hpp"

#pragma comment (lib, "winmm.lib")

class CTimer : public CProcess_Base
{
	public:
		void Start (int Value);
		void Update (float Elapsed);
		void Delete ();

		int GetFramerate ();
		float GetElapsed ();

	private:
		// Frequenz
		LONGLONG m_lFrequency;

		// Aktueller Z�hlerstand
		LONGLONG m_lCurCount;

		// Letzter Z�hlerstand
		LONGLONG m_lLastCount;

		// Framerate
		unsigned int m_Framerate;

		// Aktueller Frame
		int m_CurFrame;

		// Aktueller Z�hlerstand f�r Elapsed
		float m_lCurCountElapsed;

		// Letzter Z�hlerstand f�r Elapsed
		float m_lLastCountElapsed;

		// Zeit f�r einen Frame
		float m_fElapsed;
};

#endif