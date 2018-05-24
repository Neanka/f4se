#pragma once
#include <vector>

class GFxMovieRoot;
class GFxMovieView;
class GFxValue;

class TESTopicInfo;
class BGSSceneActionPlayerDialogue;

namespace Scaleform
{
	bool RegisterScaleform(GFxMovieView* view, GFxValue* f4se_root);
	void RegisterFuncs(GFxValue* codeObj, GFxMovieRoot* movieRoot);

    void PopulateDialogueOptions();
}

//--------------------------
// Internal functions
//--------------------------
namespace
{
    void GetDialogueGFXValue(GFxMovieRoot* movieRoot, GFxValue* outValue);
}