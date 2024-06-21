#include "Graphic_Camera.hpp"

bool CGraphic_Camera::Init (LPDIRECT3DDEVICE9 Device, float Range)
{
	if (Device != ZERO)
	{
		m_D3D9Device = Device;

		m_Pos.x = 0.0f;
		m_Pos.y = 0.0f;
		m_Pos.z = 0.0f;

		m_LookAt.x = 0.0f;
		m_LookAt.y = 0.0f;
		m_LookAt.z = 1.0f;

		m_Up.x = 0.0f;
		m_Up.y = 1.0f;
		m_Up.z = 0.0f;

		D3DXMatrixLookAtLH(&m_ViewMat,
						   &m_Pos,
						   &m_LookAt,
						   &m_Up);

		FAIL (m_D3D9Device->SetTransform (D3DTS_VIEW, &m_ViewMat));

		D3DXMATRIX ProjMatrix;
		D3DXMatrixPerspectiveFovLH (&ProjMatrix,
									D3DX_PI/4,
									static_cast<float>(1024) / static_cast<float>(768),
									1.0f,
									Range);

		FAIL (m_D3D9Device->SetTransform (D3DTS_PROJECTION, &ProjMatrix));

		return true;
	}

	else
	{
		return false;
	}
}

void CGraphic_Camera::Delete ()
{
	m_D3D9Device = ZERO;
}

void CGraphic_Camera::SetPos (D3DXVECTOR3 Pos)
{
	m_Pos = Pos;

	D3DXMatrixLookAtLH(&m_ViewMat,
					   &m_Pos,
					   &m_LookAt,
					   &m_Up);

	FAIL (m_D3D9Device->SetTransform (D3DTS_VIEW, &m_ViewMat));
}

void CGraphic_Camera::SetPos (float x, float y, float z)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;

	D3DXMatrixLookAtLH(&m_ViewMat,
					   &m_Pos,
					   &m_LookAt,
					   &m_Up);

	FAIL (m_D3D9Device->SetTransform (D3DTS_VIEW, &m_ViewMat));
}

void CGraphic_Camera::SetLookAt (D3DXVECTOR3 Pos)
{
	m_LookAt = Pos;

	D3DXMatrixLookAtLH(&m_ViewMat,
					   &m_Pos,
					   &m_LookAt,
					   &m_Up);

	FAIL (m_D3D9Device->SetTransform (D3DTS_VIEW, &m_ViewMat));
}

void CGraphic_Camera::SetLookAt (float x, float y, float z)
{
	m_LookAt.x = x;
	m_LookAt.y = y;
	m_LookAt.z = z;

	D3DXMatrixLookAtLH(&m_ViewMat,
					   &m_Pos,
					   &m_LookAt,
					   &m_Up);

	FAIL (m_D3D9Device->SetTransform (D3DTS_VIEW, &m_ViewMat));
}