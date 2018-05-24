#pragma once
#include "f4seee\f4seeeEvents.h"
#include "consts.h"
#include "Shared.h"
#include "gfxfunctions.h"
#include "papfunctions.h"



class PRKF_LevelIncrease__EventSink : public BSTEventSink<LevelIncrease::Event>
{
public:
	virtual	EventResult	ReceiveEvent(LevelIncrease::Event * evn, void * dispatcher) override;
};

extern PRKF_LevelIncrease__EventSink g_PRKF_LevelIncrease__EventSink;


class TESLoadGameHandler : public BSTEventSink<TESLoadGameEvent>
{
public:
	virtual ~TESLoadGameHandler() { };
	virtual	EventResult	ReceiveEvent(TESLoadGameEvent * evn, void * dispatcher) override;
};


void GetBasicData();
AvailablePerk GetSpecialPerk(BGSPerk* aPerk, int aVal);
AvailablePerk GetAvailablePerk(BGSPerk* aPerk);
void PopulatePerkEntry(GFxValue * dst, GFxMovieRoot * root, BGSPerk * basePerk);
perkData getperkreqs_internal(BGSPerk* thisPerk);
void PopulateSkillEntry(GFxValue * dst, GFxMovieRoot * root, ActorValueInfo * baseSkill);

bool processLists(GFxMovieRoot * root);

SInt32 GetPerkPointsAV();

SInt32 GetSkillsPointsAV();

bool GetPRKFStartedAV();

void SetPRKFStartedAV(bool started);

void ModSkillsPointsAV(SInt32 count);

void ModPerkPointsAV(SInt32 count);

void populateVanilaPerks();

bool UpdateMenu_int();

namespace PRKF_ModSettings
{
	extern		bool		bPlayPerkSound;
	extern		bool		bPlayPerkSoundLoop;
	extern		bool		bIneligible;

	void ReadModSettings();
}

namespace PRKF_Papyrus
{
	SInt32 AddPP(StaticFunctionTag*, SInt32 aiPP);
	SInt32 AddSP(StaticFunctionTag *, SInt32 aiSP);
	SInt32 GetPP(StaticFunctionTag *);
	SInt32 GetSP(StaticFunctionTag *);
	bool UpdateMenu(StaticFunctionTag *);
	void OpenMenu(StaticFunctionTag *);
	void OpenTraitsMenu(StaticFunctionTag *, BGSListForm * list, UInt32 TP, bool allowClose);
	void OpenTagSkillsMenu(StaticFunctionTag *, UInt32 numSkills, UInt32 numPoints, bool allowRetag);
	void AddTagSkillAV(StaticFunctionTag *, ActorValueInfo * skill);
	void RemoveTagSkillAV(StaticFunctionTag *, ActorValueInfo * skill);
	bool IsTagSkillAV(StaticFunctionTag *, ActorValueInfo * skill);
}

#include "GameInput.h"
#include "InputMap.h"

void ProcessKeyEvent(UInt32 keyCode, bool isDown);

void ProcessUserEvent(const char * controlName, bool isDown, int deviceType, UInt32 keyCode);

void RegisterForInput(bool bRegister);
