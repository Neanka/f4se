#pragma once

#include "f4se/PapyrusScaleformAdapter.h"
#include "f4se/GameMenus.h"
#include "f4se/GameForms.h"
#include "consts.h"

void RegisterString(GFxValue * dst,  GFxMovieRoot * root, const char * name, const char * str);
void RegisterNumber(GFxValue * dst, const char * name, double value);
void RegisterInt(GFxValue * dst, const char * name, int value);
void RegisterBool(GFxValue * dst, const char * name, bool value);