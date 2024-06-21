#include "Audio_Device.hpp"

IAudio_Device::IAudio_Device ()
{
}

IAudio_Device::~IAudio_Device ()
{
}

IAudio_Device *CreateAudioDevice ()
{
	return new IAudio_Device;
}

void ReleaseAudioDevice (IAudio_Device *Device)
{
	delete Device;
}