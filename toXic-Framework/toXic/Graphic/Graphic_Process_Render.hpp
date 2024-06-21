#ifndef GRAPHIC_PROCESS_RENDER_IS_DEFINED
#define GRAPHIC_PROCESS_RENDER_IS_DEFINED

#include "../Process/Process_Base.hpp"
#include "Graphic_SimpleMesh.hpp"

class CGraphic_Process_Render : public CProcess_Base
{
	public:
		CGraphic_Process_Render ();
		~CGraphic_Process_Render ();

		void Start(int Value);
		void Update (float Elapsed);

		void Kill();

		CGraphic_SimpleMesh *m_pMesh;
};

#endif