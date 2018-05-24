#include "gfxfunctions.h"


void RegisterString(GFxValue * dst,  GFxMovieRoot * root, const char * name, const char * str)
{
	GFxValue	fxValue;
	root->CreateString(&fxValue, str);
	dst->SetMember(name, &fxValue);
}
void RegisterNumber(GFxValue * dst, const char * name, double value)
{
	GFxValue	fxValue;
	fxValue.SetNumber(value);
	dst->SetMember(name, &fxValue);
}
void RegisterInt(GFxValue * dst, const char * name, int value)
{
	GFxValue	fxValue;
	fxValue.SetInt(value);
	dst->SetMember(name, &fxValue);
}
void RegisterBool(GFxValue * dst, const char * name, bool value)
{
	GFxValue	fxValue;
	fxValue.SetBool(value);
	dst->SetMember(name, &fxValue);
}