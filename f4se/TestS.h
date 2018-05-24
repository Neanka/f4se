#pragma once

#include "Shared.h"

typedef UInt32(*_xx)(void* param1, void* param2, void* param3, SInt8 param4, SInt8 param5, void* param6, SInt8 param7, SInt8 param8, SInt8 param9, SInt8 param10, SInt8 param11);
RelocAddr<_xx> xx(0xE1BB10);

_xx xx_Original = nullptr;

UInt8 xx_Hook(void* param1, void* param2, void* param3, SInt8 param4, SInt8 param5, void* param6, SInt8 param7, SInt8 param8, SInt8 param9, SInt8 param10, SInt8 param11)
{
	_DMESSAGE("equip hook");
	DumpClass(param1,5);
	DumpClass(param2, 5);
	DumpClass(param3, 5);

	DumpClass(param6, 5);


	_DMESSAGE("param 4 - %i", param4);
	_DMESSAGE("param 5 - %i", param4);

	_DMESSAGE("param 7 - %i", param7);
	_DMESSAGE("param 8 - %i", param8);
	_DMESSAGE("param 9 - %i", param9);
	_DMESSAGE("param 10 - %i", param10);
	_DMESSAGE("param 11 - %i", param11);

	return xx_Original(param1, param2, param3, param4, param5, param6, param7, param8, param9, param10, param11);
}
