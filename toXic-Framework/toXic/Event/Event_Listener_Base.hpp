#ifndef EVENT_LISTENER_BASE_IS_DEFINED
#define EVENT_LISTENER_BASE_IS_DEFINED

#include "Event_Types.hpp"

class CEvent_Listener_Base
{
	public:
		CEvent_Listener_Base() { m_iType = tX_EVENT_NO_TYPE; }
		virtual ~CEvent_Listener_Base () {}

		virtual void Update (tX_Event Event) {}

		int GetType () { return m_iType; }

	private:
		int m_iType;
};

#endif