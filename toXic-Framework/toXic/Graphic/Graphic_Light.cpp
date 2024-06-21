#include "Graphic_Light.hpp"

bool CGraphic_Light::Init (LPDIRECT3DDEVICE9 Device)
{
	if (Device != ZERO)
	{
		m_D3D9Device = Device;
		m_Light = NULL;
		Refer = false;
	}

	else
	{
		return false;
	}

	return true;
}

void CGraphic_Light::Delete ()
{
	if (Refer == true)
	{
		m_Light = NULL;
	}

	else
	{
		if (m_Light != NULL)
		{
			delete m_Light;
			m_Light = NULL;
		}
	}
	m_D3D9Device = ZERO;
}

#pragma region Initialisierungsfunktionen

void CGraphic_Light::SetLightData (D3DLIGHT9 *Light)
{
	m_Light = Light;
	Refer = true;
}

void CGraphic_Light::SetType (D3DLIGHTTYPE Type)
{
	if (m_Light == NULL)
	{
		m_Light = new D3DLIGHT9;
		m_Light->Type = Type;
	}

	else
	{
		m_Light->Type = Type;
		return;
	}
}

void CGraphic_Light::SetDiffuse (D3DCOLORVALUE Diffuse)
{
	if (m_Light == NULL)
	{
		m_Light = new D3DLIGHT9;
		m_Light->Diffuse = Diffuse;
	}

	else
	{
		m_Light->Diffuse = Diffuse;
		return;
	}
}

void CGraphic_Light::SetDiffuse (float R, float G, float B, float A)
{
	if (m_Light == NULL)
	{
		m_Light = new D3DLIGHT9;
		m_Light->Diffuse.r = R;
		m_Light->Diffuse.g = G;
		m_Light->Diffuse.b = B;
		m_Light->Diffuse.a = A;
	}

	else
	{
		m_Light->Diffuse.r = R;
		m_Light->Diffuse.g = G;
		m_Light->Diffuse.b = B;
		m_Light->Diffuse.a = A;
		return;
	}
}

void CGraphic_Light::SetSpecular (D3DCOLORVALUE Specular)
{
	if (m_Light == NULL)
	{
		m_Light = new D3DLIGHT9;
		m_Light->Specular = Specular;
	}

	else
	{
		m_Light->Specular = Specular;
		return;
	}
}

void CGraphic_Light::SetSpecular (float R, float G, float B, float A)
{
	if (m_Light == NULL)
	{
		m_Light = new D3DLIGHT9;
		m_Light->Specular.r = R;
		m_Light->Specular.g = G;
		m_Light->Specular.b = B;
		m_Light->Specular.a = A;
	}

	else
	{
		m_Light->Specular.r = R;
		m_Light->Specular.g = G;
		m_Light->Specular.b = B;
		m_Light->Specular.a = A;
		return;
	}
}

void CGraphic_Light::SetAmbient (D3DCOLORVALUE Ambient)
{
	if (m_Light == NULL)
	{
		m_Light = new D3DLIGHT9;
		m_Light->Ambient = Ambient;
	}

	else
	{
		m_Light->Ambient = Ambient;
		return;
	}
}

void CGraphic_Light::SetAmbient (float R, float G, float B, float A)
{
	if (m_Light == NULL)
	{
		m_Light = new D3DLIGHT9;
		m_Light->Ambient.r = R;
		m_Light->Ambient.g = G;
		m_Light->Ambient.b = B;
		m_Light->Ambient.a = A;
	}

	else
	{
		m_Light->Ambient.r = R;
		m_Light->Ambient.g = G;
		m_Light->Ambient.b = B;
		m_Light->Ambient.a = A;
		return;
	}
}

void CGraphic_Light::SetPos (D3DXVECTOR3 Pos)
{
	if (m_Light == NULL)
	{
		m_Light = new D3DLIGHT9;
		m_Light->Position = Pos;
	}

	else
	{
		m_Light->Position = Pos;
		return;
	}
}

void CGraphic_Light::SetPos (float X, float Y, float Z)
{
	if (m_Light == NULL)
	{
		m_Light = new D3DLIGHT9;
		m_Light->Position.x = X;
		m_Light->Position.y = Y;
		m_Light->Position.z = Z;
	}

	else
	{
		m_Light->Position.x = X;
		m_Light->Position.y = Y;
		m_Light->Position.z = Z;
		return;
	}
}

void CGraphic_Light::SetDir (D3DXVECTOR3 Dir)
{
	if (m_Light == NULL)
	{
		m_Light = new D3DLIGHT9;
		m_Light->Direction = Dir;
	}

	else
	{
		m_Light->Direction = Dir;
		return;
	}
}

void CGraphic_Light::SetDir (float X, float Y, float Z)
{
	if (m_Light == NULL)
	{
		m_Light = new D3DLIGHT9;
		m_Light->Direction.x = X;
		m_Light->Direction.y = Y;
		m_Light->Direction.z = Z;
	}

	else
	{
		m_Light->Direction.x = X;
		m_Light->Direction.y = Y;
		m_Light->Direction.z = Z;
		return;
	}
}

void CGraphic_Light::SetRange (float Range)
{
	if (m_Light == NULL)
	{
		m_Light = new D3DLIGHT9;
		m_Light->Range = Range;
	}

	else
	{
		m_Light->Range = Range;
		return;
	}
}

void CGraphic_Light::SetFalloff (float Falloff)
{
	if (m_Light == NULL)
	{
		m_Light = new D3DLIGHT9;
		m_Light->Falloff = Falloff;
	}

	else
	{
		m_Light->Falloff = Falloff;
		return;
	}
}

void CGraphic_Light::SetAttenuation (float Attenuation, int Index)
{
	if (m_Light == NULL)
	{
		m_Light = new D3DLIGHT9;
		switch (Index)
		{
			case 0:
			{
				m_Light->Attenuation0 = Attenuation;
			} break;

			case 1:
			{
				m_Light->Attenuation1 = Attenuation;
			} break;

			case 2:
			{
				m_Light->Attenuation2 = Attenuation;
			} break;
		}
	}

	else
	{
		switch (Index)
		{
			case 0:
			{
				m_Light->Attenuation0 = Attenuation;
			} break;

			case 1:
			{
				m_Light->Attenuation1 = Attenuation;
			} break;

			case 2:
			{
				m_Light->Attenuation2 = Attenuation;
			} break;
		}
	}
}

void CGraphic_Light::SetTheta (float Theta)
{
	if (m_Light == NULL)
	{
		m_Light = new D3DLIGHT9;
		m_Light->Theta = Theta;
	}

	else
	{
		m_Light->Theta = Theta;
		return;
	}
}

void CGraphic_Light::SetPhi (float Phi)
{
	if (m_Light == NULL)
	{
		m_Light = new D3DLIGHT9;
		m_Light->Phi = Phi;
	}

	else
	{
		m_Light->Phi = Phi;
		return;
	}
}

void CGraphic_Light::SetIndex (int Index)
{
	m_Index = Index;
}

#pragma endregion

void CGraphic_Light::RegisterLight ()
{
	FAIL (m_D3D9Device->SetLight (m_Index, m_Light));
}

void CGraphic_Light::SetEnable (BOOL Value)
{
	FAIL (m_D3D9Device->LightEnable (m_Index, Value));
}