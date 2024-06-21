#include "Movement_Process.hpp"

CMovement_Process::CMovement_Process()
{
	m_bActive = false;
	m_nNextValue = 0;
	m_vPosition = D3DXVECTOR3 (0, 0, 0);
	m_vLastPosition = D3DXVECTOR3 (0, 0, 0);
}

CMovement_Process::~CMovement_Process()
{
}

void CMovement_Process::Start(int Value)
{
	m_bActive = true;
	m_itIterator = m_liPositions.begin ();
}

void CMovement_Process::Update(float Elapsed)
{
	if (m_itIterator != m_liPositions.end())
	{
		D3DXVECTOR3 Direction;
		D3DXVec3Subtract(&Direction, &m_itIterator->Vec, &m_vPosition);
		D3DXVec3Normalize(&Direction, &Direction);

		m_vPosition += (Direction * m_itIterator->Speed * Elapsed);

		if (IsReached(m_vPosition, m_itIterator->Vec))
		{
			m_vPosition = m_itIterator->Vec;
			m_vLastPosition = m_vPosition;
			m_itIterator++;
		}
	}

	else
	{
		if (m_bLoop == true)
		{
			m_itIterator = m_liPositions.begin();
		}

		else
		{
			m_bActive = false;
		}
	}
}

void CMovement_Process::Kill()
{
	m_liPositions.clear ();
}

void CMovement_Process::SetPosition(D3DXVECTOR3 Pos)
{
	m_vPosition = Pos;
}

void CMovement_Process::SetPosition(float x, float y, float z)
{
	m_vPosition = D3DXVECTOR3(x, y, z);
}

void CMovement_Process::AddPosition(tX_MOVE Pos)
{
	m_liPositions.push_back(Pos);
}

void CMovement_Process::AddPosition(D3DXVECTOR3 Pos, float Speed)
{
	m_liPositions.push_back(tX_MOVE(Pos, Speed));
}

void CMovement_Process::AddPosition(float x, float y, float z, float Speed)
{
	m_liPositions.push_back(tX_MOVE (x, y, z, Speed));
}

bool CMovement_Process::IsReached(D3DXVECTOR3 Start, D3DXVECTOR3 Dest)
{
	D3DXVECTOR3 Diff = Dest - Start;
	float Dist = sqrtf(D3DXVec3Dot(&Diff, &Diff));

	if (Dist <= 2)
	{
		return true;
	}

	else
	{
		return false;
	}
}