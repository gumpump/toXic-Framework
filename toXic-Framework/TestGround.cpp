#include "TestGround.hpp"

bool CTestGround::Init (LPDIRECT3DDEVICE9 Device)
{
	if (Device != ZERO)
	{
		m_D3D9Device = Device;
	}

	else
	{
		return false;
	}

	m_Size = 5.0f;

	return true;
}

bool CTestGround::InitTextures (CGraphic_Textures *TexMng)
{
	if (TexMng != ZERO)
	{
		m_TexMng = TexMng;
	}

	else
	{
		return false;
	}

	return true;
}

void CTestGround::Create ()
{
	// Unten Links
	m_Vertices[0].x = -m_Size;
	m_Vertices[0].y =  0.0f;
	m_Vertices[0].z = -m_Size;
	m_Vertices[0].tu = 0.0f;
	m_Vertices[0].tv = 1.0f;

	// Oben Links
	m_Vertices[1].x = -m_Size;
	m_Vertices[1].y =  0.0f;
	m_Vertices[1].z =  m_Size;
	m_Vertices[1].tu = 0.0f;
	m_Vertices[1].tv = 0.0f;

	// Oben Rechts
	m_Vertices[2].x =  m_Size;
	m_Vertices[2].y =  0.0f;
	m_Vertices[2].z =  m_Size;
	m_Vertices[2].tu = 1.0f;
	m_Vertices[2].tv = 0.0f;

	// Oben Rechts
	m_Vertices[3].x =  m_Size;
	m_Vertices[3].y =  0.0f;
	m_Vertices[3].z =  m_Size;
	m_Vertices[3].tu = 1.0f;
	m_Vertices[3].tv = 0.0f;

	// Unten Rechts
	m_Vertices[4].x =  m_Size;
	m_Vertices[4].y =  0.0f;
	m_Vertices[4].z = -m_Size;
	m_Vertices[4].tu = 1.0f;
	m_Vertices[4].tv = 1.0f;

	// Unten Links
	m_Vertices[5].x = -m_Size;
	m_Vertices[5].y =  0.0f;
	m_Vertices[5].z = -m_Size;
	m_Vertices[5].tu = 0.0f;
	m_Vertices[5].tv = 1.0f;

	BYTE *VertexBufferStart;

	FAIL (m_D3D9Device->CreateVertexBuffer (sizeof (GroundVertex) * 6,
											D3DUSAGE_WRITEONLY, 
											GROUNDVERTEX, 
											D3DPOOL_MANAGED,
											&m_VBuffer,
											ZERO));

	FAIL (m_VBuffer->Lock (ZERO, ZERO, reinterpret_cast<void**>(&VertexBufferStart), ZERO));

	memcpy (VertexBufferStart, m_Vertices, sizeof (GroundVertex) * 6);

	FAIL (m_VBuffer->Unlock ());

	FAIL (m_D3D9Device->SetFVF (GROUNDVERTEX));

	FAIL (m_D3D9Device->SetTextureStageState (ZERO,
											  D3DTSS_COLOROP,
											  D3DTOP_SELECTARG1));
}

void CTestGround::Delete ()
{
	m_D3D9Device = ZERO;

	m_TexMng = ZERO;

	if (m_VBuffer != ZERO)
	{
		m_VBuffer->Release ();
		m_VBuffer = ZERO;
	}
}

void CTestGround::SetSize (float Value)
{
	m_Size = Value;
}

void CTestGround::SetTex (LPCSTR Path)
{
	m_Path = Path;
}

void CTestGround::Render ()
{
	FAIL (m_D3D9Device->SetStreamSource (ZERO, m_VBuffer, ZERO, sizeof (GroundVertex)));
	FAIL (m_D3D9Device->SetTexture (0, m_TexMng->Add (m_Path)->Texture));
	FAIL (m_D3D9Device->DrawPrimitive (D3DPT_TRIANGLELIST, 0, 2));
}