#include "Graphic_Textures.hpp"

bool CGraphic_Textures::Init (LPDIRECT3DDEVICE9 Device)
{

	if (Device != ZERO)
	{
		m_D3D9Device = Device;
	}

	else
	{
		return false;
	}

	m_Textures.clear ();

	Count = 0;

	return true;
}

void CGraphic_Textures::Delete ()
{
	DeleteTexture ();
}

tX_TEX *CGraphic_Textures::Add (LPCSTR File)
{
	for (list<tX_TEX*>::iterator i = m_Textures.begin ();
		 i != m_Textures.end ();
		 i++)
	{
		if ((*i)->Filename == File)
		{
			return (*i);
		}
	}

	Tex = new tX_TEX;
	Tex->Filename = File;
	FAIL (D3DXCreateTextureFromFileA (m_D3D9Device,
									  File,
									  &Tex->Texture));
	m_Textures.push_back (Tex);
	Count++;

	return Tex;
}

void CGraphic_Textures::DeleteTexture ()
{
	for (list<tX_TEX*>::iterator i = m_Textures.begin ();
		 i != m_Textures.end ();
		 i++)
	{
		(*i)->Texture->Release ();
		Count--;
		delete (*i);
	}

	m_Textures.clear ();
}

void CGraphic_Textures::DeleteTexture (LPCSTR File)
{
	for (list<tX_TEX*>::iterator i = m_Textures.begin ();
		 i != m_Textures.end ();
		 i++)
	{
		if ((*i)->Filename == File)
		{
			(*i)->Texture->Release ();
			Count--;
			delete (*i);
			list<tX_TEX*>::iterator j = i;
			j++;
			m_Textures.erase (i);
			i = j;
			return;
		}
	}
}

void CGraphic_Textures::DeleteTextureByPath (LPCSTR Path)
{
	for (list<tX_TEX*>::iterator i = m_Textures.begin ();
		 i != m_Textures.end ();
		 i++)
	{
		if ((*i)->Path == Path)
		{
			(*i)->Texture->Release ();
			Count--;
			delete (*i);
			list<tX_TEX*>::iterator j = i;
			j++;
			m_Textures.erase (i);
			i = j;
			return;
		}
	}
}