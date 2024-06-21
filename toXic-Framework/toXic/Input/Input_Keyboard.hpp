#ifndef INPUT_KEYBOARD_IS_DEFINED
#define INPUT_KEYBOARD_IS_DEFINED

#include "Input_Device.hpp"

class CInput_Keyboard : public CProcess_Base
{
	public:
		bool Init (IInput_Device *Device);
		void Start (int Value) { m_bActive = true; }
		void Delete ();

		void Update (float Elapsed);

		bool IsPressed (int Key);

		void Kill() { m_bActive = false; }

	private:
		IDirectInputDevice8 *m_Keyboard;
		unsigned char m_KeyboardState[256];
};

#endif