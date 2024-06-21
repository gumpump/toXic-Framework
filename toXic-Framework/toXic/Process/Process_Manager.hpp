#ifndef PROCESS_MANAGER_IS_DEFINED
#define PROCESS_MANAGER_IS_DEFINED

#include <list>
#include "Process_Base.hpp"

using namespace std;

class CProcess_Manager
{
	public:
		CProcess_Manager ();
		~CProcess_Manager ();

		void Update (float Elapsed);

		void AttachProcess (CProcess_Base *Process);

	protected:
		list<CProcess_Base*> *m_liProcessList;
		list<CProcess_Base*>::iterator m_itIterator;
};
#endif