#ifndef MOVEMENT_PROCESS_IS_DEFINED
#define MOVEMENT_PROCESS_IS_DEFINED

#include <math.h>
#include <list>
#include "../Process/Process_Base.hpp"
#include "Movement_Types.hpp"

class CMovement_Process : public CProcess_Base
{
	public:
		CMovement_Process ();
		~CMovement_Process ();

		void Start (int Value);
		void Update (float Elapsed);

		void Kill ();

		void Loop (bool L) { m_bLoop = L; }
		bool Loop () { return m_bLoop; }

		void SetPosition (D3DXVECTOR3 Pos);
		void SetPosition (float x, float y, float z);

		void AddPosition (tX_MOVE Pos);
		void AddPosition (D3DXVECTOR3 Pos, float Speed);
		void AddPosition (float x, float y, float z, float Speed);

		D3DXVECTOR3 GetPosition () { return m_vPosition; }

	protected:
		bool IsReached(D3DXVECTOR3 Start, D3DXVECTOR3 Dest);

		D3DXVECTOR3 m_vPosition;
		D3DXVECTOR3 m_vLastPosition;
		bool m_bLoop;
		std::list<tX_MOVE> m_liPositions;
		std::list<tX_MOVE>::iterator m_itIterator;
};

#endif