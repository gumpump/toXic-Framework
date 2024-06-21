#include "Graphic_Skybox.hpp"

bool CGraphic_Skybox::Init (LPDIRECT3DDEVICE9 Device)
{
	if (Device != ZERO)
	{
		m_D3D9Device = Device;

		m_Pos.x = 0.0f;
		m_Pos.y = 0.0f;
		m_Pos.z = 0.0f;

		m_Dx = 10.0f;
		m_Dy = 10.0f;
		m_Dz = 10.0f;

		return true;
	}

	else
	{
		return false;
	}
}

bool CGraphic_Skybox::InitTextures (CGraphic_Textures *TexMng)
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

void CGraphic_Skybox::Delete ()
{
	for (int i = 0; i < 6; i++)
	{
		m_TexMng->DeleteTexture (m_TexNames[i]);
	}

	m_TexMng = ZERO;
	m_D3D9Device = ZERO;
}

void CGraphic_Skybox::SetTexture (LPCSTR Filename, tX_Skybox_Sides Side)
{
	m_TexNames[Side] = Filename;
}

void CGraphic_Skybox::SetPos (D3DVECTOR Pos)
{
	m_Pos = Pos;
}

void CGraphic_Skybox::SetPos (float X, float Y, float Z)
{
	m_Pos.x = X;
	m_Pos.y = Y;
	m_Pos.z = Z;
}

void CGraphic_Skybox::Create ()
{
	tX_SkyboxVertex Vertices[6*4];

	// Vorne
	Vertices[0].Coords.x =   -m_Dx;
    Vertices[0].Coords.y =   -m_Dy;
    Vertices[0].Coords.z =    m_Dz;
    Vertices[0].tu =   0.0f;
    Vertices[0].tv =   1.0f;

    Vertices[1].Coords.x =   -m_Dx;
    Vertices[1].Coords.y =    m_Dy;
    Vertices[1].Coords.z =    m_Dz;
    Vertices[1].tu =   0.0f;
    Vertices[1].tv =   0.0f;

    Vertices[2].Coords.x =    m_Dx;
    Vertices[2].Coords.y =   -m_Dy;
    Vertices[2].Coords.z =    m_Dz;
    Vertices[2].tu =   1.0f;
    Vertices[2].tv =   1.0f;

    Vertices[3].Coords.x =    m_Dx;
    Vertices[3].Coords.y =    m_Dy;
    Vertices[3].Coords.z =    m_Dz;
    Vertices[3].tu =   1.0f;
    Vertices[3].tv =   0.0f;

    // Hinten
    Vertices[4].Coords.x =    m_Dx;
    Vertices[4].Coords.y =   -m_Dy;
    Vertices[4].Coords.z =   -m_Dz;
    Vertices[4].tu =   0.0f;
    Vertices[4].tv =   1.0f;

    Vertices[5].Coords.x =    m_Dx;
    Vertices[5].Coords.y =    m_Dy;
    Vertices[5].Coords.z =   -m_Dz;
    Vertices[5].tu =   0.0f;
    Vertices[5].tv =   0.0f;

    Vertices[6].Coords.x =   -m_Dx;
    Vertices[6].Coords.y =   -m_Dy;
    Vertices[6].Coords.z =   -m_Dz;
    Vertices[6].tu =   1.0f;
    Vertices[6].tv =   1.0f;

    Vertices[7].Coords.x =   -m_Dx;
    Vertices[7].Coords.y =    m_Dy;
    Vertices[7].Coords.z =   -m_Dz;
    Vertices[7].tu =   1.0f;
    Vertices[7].tv =   0.0f;

    // Links
    Vertices[8].Coords.x =   -m_Dx;
    Vertices[8].Coords.y =   -m_Dy;
    Vertices[8].Coords.z =   -m_Dz;
    Vertices[8].tu =   0.0f;
    Vertices[8].tv =   1.0f;

    Vertices[9].Coords.x =   -m_Dx;
    Vertices[9].Coords.y =    m_Dy;
    Vertices[9].Coords.z =   -m_Dz;
    Vertices[9].tu =   0.0f;
    Vertices[9].tv =   0.0f;

    Vertices[10].Coords.x =  -m_Dx;
    Vertices[10].Coords.y =  -m_Dy;
    Vertices[10].Coords.z =   m_Dz;
    Vertices[10].tu =  1.0f;
    Vertices[10].tv =  1.0f;

    Vertices[11].Coords.x =  -m_Dx;
    Vertices[11].Coords.y =   m_Dy;
    Vertices[11].Coords.z =   m_Dz;
    Vertices[11].tu =  1.0f;
    Vertices[11].tv =  0.0f;

    // Rechts
    Vertices[12].Coords.x =   m_Dx;
    Vertices[12].Coords.y =  -m_Dy;
    Vertices[12].Coords.z =   m_Dz;
    Vertices[12].tu =  0.0f;
    Vertices[12].tv =  1.0f;

    Vertices[13].Coords.x =   m_Dx;
    Vertices[13].Coords.y =   m_Dy;
    Vertices[13].Coords.z =   m_Dz;
    Vertices[13].tu =  0.0f;
    Vertices[13].tv =  0.0f;

    Vertices[14].Coords.x =   m_Dx;
    Vertices[14].Coords.y =  -m_Dy;
    Vertices[14].Coords.z =  -m_Dz;
    Vertices[14].tu =  1.0f;
    Vertices[14].tv =  1.0f;

    Vertices[15].Coords.x =   m_Dx;
    Vertices[15].Coords.y =   m_Dy;
    Vertices[15].Coords.z =  -m_Dz;
    Vertices[15].tu =  1.0f;
    Vertices[15].tv =  0.0f;


    // Oben
	Vertices[16].Coords.x =  -m_Dx;
    Vertices[16].Coords.y =   m_Dy;
    Vertices[16].Coords.z =   m_Dz;
    Vertices[16].tu =  1.0f;
    Vertices[16].tv =  0.0f;

    Vertices[17].Coords.x =  -m_Dx;
    Vertices[17].Coords.y =   m_Dy;
    Vertices[17].Coords.z =  -m_Dz;
    Vertices[17].tu =  1.0f;
    Vertices[17].tv =  1.0f;

    Vertices[18].Coords.x =   m_Dx;
    Vertices[18].Coords.y =   m_Dy;
    Vertices[18].Coords.z =   m_Dz;
    Vertices[18].tu =  0.0f;
    Vertices[18].tv =  0.0f;

    Vertices[19].Coords.x =   m_Dx;
    Vertices[19].Coords.y =   m_Dy;
    Vertices[19].Coords.z =  -m_Dz;
    Vertices[19].tu =  0.0f;
    Vertices[19].tv =  1.0f;

    // Unten
    Vertices[20].Coords.x =  -m_Dx;
    Vertices[20].Coords.y =  -m_Dy;
    Vertices[20].Coords.z =  -m_Dz;
    Vertices[20].tu =  1.0f;
    Vertices[20].tv =  0.0f;

    Vertices[21].Coords.x =  -m_Dx;
    Vertices[21].Coords.y =  -m_Dy;
    Vertices[21].Coords.z =   m_Dz;
    Vertices[21].tu =  1.0f;
    Vertices[21].tv =  1.0f;

    Vertices[22].Coords.x =   m_Dx;
    Vertices[22].Coords.y =  -m_Dy;
    Vertices[22].Coords.z =  -m_Dz;
    Vertices[22].tu =  0.0f;
    Vertices[22].tv =  0.0f;

    Vertices[23].Coords.x =   m_Dx;
    Vertices[23].Coords.y =  -m_Dy;
    Vertices[23].Coords.z =   m_Dz;
    Vertices[23].tu =  0.0f;
    Vertices[23].tv =  1.0f;

	FAIL (m_D3D9Device->CreateVertexBuffer (6 * 4 * sizeof(tX_SkyboxVertex), 
											0, 
											SKYBOX_VERTEX, 
											D3DPOOL_DEFAULT, 
											&m_Buffer, 0));

	void *pVertices;

	FAIL (m_Buffer->Lock(0, sizeof(Vertices), &pVertices, 0));
	memcpy (pVertices, Vertices, sizeof (Vertices));
	FAIL (m_Buffer->Unlock());
}

void CGraphic_Skybox::Render ()
{
	D3DXMATRIX MatSkyBox;

	D3DXMatrixIdentity (&MatSkyBox);

    // Skybox verschieben
    D3DXMatrixTranslation (&MatSkyBox, m_Pos.x, m_Pos.y, m_Pos.z);

    FAIL (m_D3D9Device->SetTransform (D3DTS_WORLD, &MatSkyBox));

    // Vorbereitungen zum Rendern treffen
    FAIL (m_D3D9Device->SetFVF(SKYBOX_VERTEX));
    FAIL (m_D3D9Device->SetStreamSource(0, m_Buffer, 0, sizeof(tX_SkyboxVertex)));

    FAIL (m_D3D9Device->SetTextureStageState (0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1));
    FAIL (m_D3D9Device->SetTextureStageState (0, D3DTSS_COLORARG1, D3DTA_TEXTURE));

    // Filterung fuer die SkyBox-Texturen, da sie vergroessert werden
    // lineare Filterung fuer D3DSAMP_MAGFILTER angeben
    FAIL(m_D3D9Device->SetSamplerState (0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR));

    // Wichtig - Clamp-Texturmodus einschalten
    // durch die Interpoltion/Filterung/Vergroesserung der
    // Texturen kommt es bei manchen Karten zu dem Effekt, dass im Wrap-Modus
    // (naeheres dazu im DX9 SDK) "Nahtstellen" an den Uebergaengen zwischen
    // den Texturen sichtbar werden. Der Clamp-Modus sollte dies verhindern.

    // Wenn die folgenden Zeilen auskommentiert werden, werden diese Nahtstellen
    // zwischen den Texturen sichtbar
    FAIL (m_D3D9Device->SetSamplerState (0, D3DSAMP_ADDRESSU , D3DTADDRESS_CLAMP));
    FAIL (m_D3D9Device->SetSamplerState (0, D3DSAMP_ADDRESSV , D3DTADDRESS_CLAMP));

    // Z-Buffer-Test abschalten
    FAIL (m_D3D9Device->SetRenderState (D3DRS_ZENABLE, D3DZB_FALSE));

    // die 6 Ebenen des Wuerfels rendern
    for (int i = 0; i < 6; i++)
    {
        // passende Textur waehlen
		FAIL (m_D3D9Device->SetTexture(0, m_TexMng->Add (m_TexNames[i])->Texture));

		FAIL (m_D3D9Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, i*4, 2));
    }

	
    // Z-Buffer-Test wieder einschalten
    FAIL (m_D3D9Device->SetRenderState (D3DRS_ZENABLE, D3DZB_TRUE));

    // Wichtig - Clamp-Texturmodus wieder ausschalten
    FAIL (m_D3D9Device->SetSamplerState (0, D3DSAMP_ADDRESSU , D3DTADDRESS_WRAP));
    FAIL (m_D3D9Device->SetSamplerState (0, D3DSAMP_ADDRESSV , D3DTADDRESS_WRAP));

    // Textur aus der Texture-Stage entfernen
    //FAILEX(m_Device->SetTexture (0, NULL));

	D3DXMatrixIdentity (&MatSkyBox);

	FAIL (m_D3D9Device->SetTransform (D3DTS_WORLD, &MatSkyBox));
}