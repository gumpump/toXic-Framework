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

		// Aktueller Zählerstand
		LONGLONG m_lCurCount;

		// Letzter Zählerstand
		LONGLONG m_lLastCount;

		// Framerate
		unsigned int m_Framerate;

		// Aktueller Frame
		int m_CurFrame;

		// Aktueller Zählerstand für Elapsed
		float m_lCurCountElapsed;

		// Letzter Zählerstand für Elapsed
		float m_lLastCountElapsed;

		// Zeit für einen Frame
		float m_fElapsed;
};

#endif