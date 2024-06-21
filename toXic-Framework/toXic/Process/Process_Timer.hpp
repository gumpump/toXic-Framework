#ifndef PROCESS_TIMER_IS_DEFINED
#define PROCESS_TIMER_IS_DEFINED

#include "Process_Base.hpp"

class CProcess_Timer : public CProcess_Base
{
	public:
		CProcess_Timer ();
		~CProcess_Timer ();

		void Start (int Value);
		void Update (float Elapsed);

		void Kill();

	protected:
		float m_fTimer;
		float m_fEndTime;
};

#endif