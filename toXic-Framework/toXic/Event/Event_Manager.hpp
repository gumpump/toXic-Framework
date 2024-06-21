#ifndef EVENT_MANAGER_IS_DEFINED
#define EVENT_MANAGER_IS_DEFINED

#define g_sEventManager Singleton<CEvent_Manager>::Instance()

#include <list>
#include <queue>
#include "../Common/Common.hpp"
#include "Event_Listener_Base.hpp"

class CEvent_Manager : public Singleton<CEvent_Manager>
{
	public:
		CEvent_Manager ();
		~CEvent_Manager ();

		void Update ();
		void PushIn (tX_Event Event);

	private:
		std::queue<tX_Event> m_qEvents;
		std::list<CEvent_Listener_Base*> m_liListener;
		std::list<CEvent_Listener_Base*>::iterator m_itIterator;
};

#endif