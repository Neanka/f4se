#pragma once
#include "f4se/PluginAPI.h"

namespace f4eeeSerialization
{
	void RevertCallback(const F4SESerializationInterface * intfc);
	void LoadCallback(const F4SESerializationInterface * intfc);
	void SaveCallback(const F4SESerializationInterface * intfc);
}