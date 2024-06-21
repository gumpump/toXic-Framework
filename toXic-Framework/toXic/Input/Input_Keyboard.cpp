#include "Input_Keyboard.hpp"

bool CInput_Keyboard::Init (IInput_Device *Device)
{
	FAIL (Device->m_Interface->CreateDevice (GUID_SysKeyboard, &m_Keyboard, NULL));

	FAIL (m_Keyboard->SetDataFormat (&c_dfDIKeyboard));

	FAIL (m_Keyboard->SetCooperativeLevel (Device->m_hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE));

	FAIL (m_Keyboard->Acquire ());

	return true;
}

void CInput_Keyboard::Delete ()
{
	m_Keyboard->Unacquire ();
	m_Keyboard->Release ();
	m_Keyboard = NULL;
}

void CInput_Keyboard::Update (float Elapsed)
{
	HRESULT HR;
	HR = m_Keyboard->GetDeviceState (sizeof (m_KeyboardState), (LPVOID)&m_KeyboardState);

	if (HR == DIERR_INPUTLOST || HR == DIERR_NOTACQUIRED)
	{
		m_Keyboard->Acquire ();
	}
}

bool CInput_Keyboard::IsPressed (int Key)
{
	if (m_KeyboardState[Key] & 0x80)
	{
		return true;
	}

	return false;
}