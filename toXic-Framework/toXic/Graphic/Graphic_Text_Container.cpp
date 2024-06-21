#include "Graphic_Text_Container.hpp"

bool CGraphic_Text_Container::Init ()
{
	if (m_TextList.empty () != true)
	{
		m_TextList.clear ();
	}

	return true;
}

void CGraphic_Text_Container::Delete ()
{
	list<tX_TXT*>::iterator i;
	for (i = m_TextList.begin ();i != m_TextList.end ();i++)
	{
		(*i)->Text.Delete ();
		delete (*i);
	}

	m_TextList.clear ();
}

tX_TXT *CGraphic_Text_Container::Add (int ID)
{
	tX_TXT *Text = new tX_TXT;
	Text->ID = ID;
	m_TextList.push_front (Text);

	return Text;
}

tX_TXT *CGraphic_Text_Container::Get (int ID)
{
	list<tX_TXT*>::iterator i;
	for (i = m_TextList.begin (); i != m_TextList.end (); i++)
	{
		if ((*i)->ID == ID)
		{
			return (*i);
		}

		else
		{
			continue;
		}
	}

	return ZERO;
}

void CGraphic_Text_Container::Delete_ID (int ID)
{
	list<tX_TXT*>::iterator i;
	for (i = m_TextList.begin (); i!= m_TextList.end (); i++)
	{
		if ((*i)->ID == ID)
		{
			(*i)->Text.Delete ();
			delete (*i);
			m_TextList.erase (i);
			return;
		}

		else
		{
			continue;
		}
	}
}