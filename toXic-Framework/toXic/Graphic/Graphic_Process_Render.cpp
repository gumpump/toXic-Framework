#include "Graphic_Process_Render.hpp"

CGraphic_Process_Render::CGraphic_Process_Render ()
{
	m_pMesh = NULL;
	m_bActive = false;
	m_nNextValue = 0;
}

CGraphic_Process_Render::~CGraphic_Process_Render ()
{
}

void CGraphic_Process_Render::Start(int Value)
{
	m_bActive = true;
}

void CGraphic_Process_Render::Update (float Elapsed)
{
	m_pMesh->Render ();
}

void CGraphic_Process_Render::Kill ()
{
	m_bActive = false;
}