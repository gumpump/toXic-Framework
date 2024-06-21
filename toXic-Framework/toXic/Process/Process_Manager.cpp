#include "Process_Manager.hpp"

CProcess_Manager::CProcess_Manager()
{
	m_liProcessList = 0;
	m_liProcessList = new list<CProcess_Base*>;
	m_liProcessList->clear ();
}

CProcess_Manager::~CProcess_Manager()
{
	m_liProcessList->clear ();
	delete m_liProcessList;
	m_liProcessList = 0;
}

void CProcess_Manager::Update(float Elapsed)
{
	m_itIterator = m_liProcessList->begin ();
	while (m_itIterator != m_liProcessList->end ())
	{
		if ((*m_itIterator)->IsActive() == true)
		{
			(*m_itIterator)->Update (Elapsed);
			m_itIterator++;
		}

		else
		{
			if ((*m_itIterator)->HasNext() == true)
			{
				CProcess_Base *Process = (*m_itIterator)->GetNext();
				Process->Start((*m_itIterator)->GetNextValue());
				m_liProcessList->push_back(Process);
				(*m_itIterator)->SetNext (0, 0);
				m_liProcessList->erase(m_itIterator++);
				
			}
		}
	};
}

void CProcess_Manager::AttachProcess(CProcess_Base *Process)
{
	if (Process != NULL)
	{
		m_liProcessList->push_back(Process);
	}
}