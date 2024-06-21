#ifndef GRAPHIC_TEXT_CONTAINER_IS_DEFINED
#define GRAPHIC_TEXT_CONTAINER_IS_DEFINED

#include "Graphic_Text.hpp"
#include "Graphic_Text_Container_Types.hpp"
#include <list>

using namespace std;

class CGraphic_Text_Container
{
	public:
		bool Init ();
		void Delete ();

		tX_TXT *Add		(int ID);
		tX_TXT *Get		(int ID);
		void Delete_ID  (int ID);

	private:
		list<tX_TXT*> m_TextList;
};
#endif