#include "Event_Manager.hpp"

CEvent_Manager::CEvent_Manager ()
{
	while (m_qEvents.empty () == false)
	{
		m_qEvents.pop ();
	}
}

CEvent_Manager::~CEvent_Manager ()
{
}

void CEvent_Manager::Update ()
{
	if (m_qEvents.empty() == false)
	{
		for (m_itIterator = m_liListener.begin(); m_itIterator != m_liListener.end(); m_itIterator++)
		{
			if ((*m_itIterator)->GetType() == m_qEvents.front().Type)
			{
				(*m_itIterator)->Update(m_qEvents.front());
				m_qEvents.pop();
			}
		}
	}
}

void CEvent_Manager::PushIn(tX_Event Event)
{
	m_qEvents.push (Event);
}