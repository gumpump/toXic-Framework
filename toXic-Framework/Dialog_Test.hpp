#ifndef DIALOG_IS_DEFINED
#define DIALOG_IS_DEFINED

#include "toXic/Common/Common.hpp"

#define DEUTSCH 1
#define ENGLISH 0

BOOL WINAPI Dialog_Test (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_INITDIALOG:
		{
			SendDlgItemMessage (hwnd, IDC_COMBO1, CB_ADDSTRING, ZERO, (LPARAM) L"Deutsch");
			SendDlgItemMessage (hwnd, IDC_COMBO1, CB_SETCURSEL, ZERO, (LPARAM) L"Deutsch");
			SendDlgItemMessage (hwnd, IDC_COMBO1, CB_ADDSTRING, ZERO, (LPARAM) L"English");
		} break;

		case WM_COMMAND:
		{
			switch (wparam)
			{
				case IDOK:
				{
					int Value = SendDlgItemMessage (hwnd, IDC_COMBO1, CB_GETCURSEL, ZERO, ZERO);
					EndDialog (hwnd, Value);
				} break;
			};
		} break;

		case WM_QUIT:
		{
		} break;
	};

	return TRUE;
}
#endif