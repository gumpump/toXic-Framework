#include "Common.hpp"

void tX_Error_Description (HRESULT hr)
{
	if (hr != S_OK)
	{
		MessageBox (ZERO,
					DXGetErrorDescription (hr),
					DXGetErrorString (hr),
					MB_ICONWARNING);
	}
}