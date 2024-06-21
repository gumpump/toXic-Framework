#ifndef INPUT_DEVICE_IS_DEFINED
#define INPUT_DEVICE_IS_DEFINED

#include "../Common/Common.hpp"
#include "../Process/Process_Base.hpp"

#pragma comment(lib, "x64/dinput8.lib")
#pragma comment(lib, "x64/dxguid.lib")

#include <dinput.h>

class IInput_Device
{
	friend class CInput_Keyboard;
	friend class CInput_Mouse;

	public:
		IDirectInput8 *m_Interface;
		HWND m_hWnd;
		HINSTANCE m_hInstance;
};

namespace
{
	IInput_Device *I_Device;

	IInput_Device *CreateInputDevice(HWND hWnd, HINSTANCE hInstance)
	{
		I_Device = new IInput_Device();
		IDirectInput8 *I_Temp;
		FAIL(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&I_Temp, NULL));
		I_Device->m_Interface = I_Temp;
		I_Device->m_hWnd = hWnd;
		I_Device->m_hInstance = hInstance;

		return I_Device;
	}

	void ReleaseInputDevice(IInput_Device *Device)
	{
		Device->m_Interface->Release();
		Device->m_Interface = NULL;
		Device = NULL;
	}
}
#endif