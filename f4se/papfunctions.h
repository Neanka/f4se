#pragma once

#include "f4se/GameForms.h"
#include "f4se/GameData.h"
#include "f4se/GameFormComponents.h"
#include "f4se/GameReferences.h"
#include "f4se/GameObjects.h"
#include "f4se/GameRTTI.h"
#include "f4se/PapyrusEvents.h"
//#include <string>

BSFixedString GetName(TESForm* thisForm);
BSFixedString GetDescription(TESForm * thisForm);
UInt8 GetActorLevel(Actor * actor);

ActorValueInfo * GetAVByFormID(int fromid);
BGSPerk * GetPerkByFormID(int fromid);

float GetBaseAV(ActorValueInfo * pAV,Actor * actor);
void SetBaseAV(ActorValueInfo * pAV, Actor * actor, int value);
void ModBaseAV(ActorValueInfo * pAV,Actor * actor,int delta);
void ModAV(ActorValueInfo * pAV,Actor * actor,int delta);
float GetModAVValue(ActorValueInfo * pAV,Actor * actor);
float GetFullAV(ActorValueInfo * pAV,Actor * actor);

float GetAVValueByFormID(int fromid,Actor * actor);
void ModBaseAVByFormID(int fromid,Actor * actor,int delta);
void ModAVByFormID(int fromid,Actor * actor,int delta);
void SetBaseAVByFormID(int fromid,Actor * actor,int value);
float GetModAVValueByFormID(int fromid,Actor * actor);
float GetFullAVValueByFormID(int fromid,Actor * actor);

std::string DEFGetConfigOption(const char * section, const char * key);

void TraceActorAvifs(Actor * actor);
UInt8 GetActorSex(Actor * actor);

void papMessageBox(BSFixedString asMessageBoxText);
void papMessageBox(std::string asMessageBoxText);
void papMessageBox(const char* asMessageBoxText);
void papNotification(BSFixedString asNotificationText);
void papNotification(std::string asNotificationText);
void papNotification(const char* asNotificationText);
void papTrace(BSFixedString asTextToPrint, UInt32 aiSeverity);
void papTrace(std::string asTextToPrint, UInt32 aiSeverity);
void papTrace(const char* asTextToPrint, UInt32 aiSeverity);