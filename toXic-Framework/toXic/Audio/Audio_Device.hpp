#ifndef AUDIO_DEVICE_IS_DEFINED
#define AUDIO_DEVICE_IS_DEFINED

#include "../Common/Common.hpp"
#include <Bass.h>

#pragma comment lib (lib, "Bass.lib")

class IAudio_Device
{
	public:
		IAudio_Device ();
		~IAudio_Device ();

	private:
};

IAudio_Device *CreateAudioDevice ();
void ReleaseAudioDevice (IAudio_Device *Device);
#endif