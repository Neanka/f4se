#include "main.h"

#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"

#include "f4se/GameSettings.h"
#include "common/IDirectoryIterator.h"

#include "PRKFSerialization.h"
#include "PRKFTranslator.h"

std::string mName = "PRKF";
UInt32 mVer = 1;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;
F4SEPapyrusInterface		*g_papyrus = NULL;
F4SEScaleformInterface		*g_scaleform = NULL;
F4SEMessagingInterface		*g_messaging = NULL;
F4SESerializationInterface	*g_serialization = NULL;

#define CURRENT_INI_VERSION 3

std::string modsWithWrongIniVersion = "";

bool PRKFStarted;
float PerksPoints;
float SkillsPoints;
SInt32 PPPerLevelToAdd = 0;
SInt32 SPPerLevelToAdd = 0;
UInt32 overrideMaxSkillsValue = 100;
int disableVanillaPerks = 0;
bool vanillaPerksPopulated = false;
UInt32 pLVL;
UInt8 pSex;
int pSTR;
int pPER;
int pEND;
int pCHA;
int pINT;
int pAGI;
int pLCK;

tArray<BGSPerk*> Perks;
tArray<ActorValueInfo*> Skills;

//ActorValueInfo * avPerksPoints;
//ActorValueInfo * avSkillsPoints;
//ActorValueInfo * avPRKFStarted;

enum menuMode
{
	normalMode,
	traitsMode,
	tagSkillsMode
};

int currentMode = normalMode;
BGSListForm*	traitsList;
UInt32 traitsPoints = 0;
bool traitsAllowClose = true;
UInt32 tagSkillsNum = 0;
UInt32 tagSkillsAmount = 0;
bool tagSkillsAllowRetag = false;

namespace PRKF_ModSettings
{
	bool		bPlayPerkSound = true;
	bool		bPlayPerkSoundLoop = true;
	bool		bIneligible = true;


	void ReadModSettings()
	{
		bPlayPerkSound = GetPrivateProfileInt("Main", "bPlayPerkSound", 1, "./Data/MCM/Settings/PRKF.ini") != 0;
		bPlayPerkSoundLoop = GetPrivateProfileInt("Main", "bPlayPerkSoundLoop", 1, "./Data/MCM/Settings/PRKF.ini") != 0;
		bIneligible = GetPrivateProfileInt("Filters", "bIneligible", 1, "./Data/MCM/Settings/PRKF.ini") != 0;
	}

}

PRKF_LevelIncrease__EventSink g_PRKF_LevelIncrease__EventSink;

EventResult	PRKF_LevelIncrease__EventSink::ReceiveEvent(LevelIncrease::Event * evn, void * dispatcher)
{
	_DMESSAGE("PRKF LevelIncrease__Event recieved");
	_MESSAGE("PP SP before: %i %i", GetPerkPoints(), GetSkillsPointsAV());
	_MESSAGE("ExtraPPPerLevelToAdd SPPerLevelToAdd : %i %i", PPPerLevelToAdd, SPPerLevelToAdd);
	//ModPerkPointsAV(PPPerLevelToAdd);	
	ModSkillsPointsAV(SPPerLevelToAdd);
	ModPerkPoints(PPPerLevelToAdd);
	//UpdateMenu_int(); // updated in ModPerkPoints hook TODO need BSTGlobalEvent::EventSource<PerkPointIncreaseEvent>::`vftable';
	_MESSAGE("PP SP after: %i %i", GetPerkPoints(), GetSkillsPointsAV());
	return kEvent_Continue;
}

EventResult	TESLoadGameHandler::ReceiveEvent(TESLoadGameEvent * evn, void * dispatcher)
{
	_DMESSAGE("PRKF TESLoadGameEvent recieved");
	if (modsWithWrongIniVersion != "")
	{
		papMessageBox("<b>PRKF warning!</b>\n\nYou have mods with wrong INI version.\nU must update it:\n\n" + modsWithWrongIniVersion);
	}

	GetBasicData();
	return kEvent_Continue;
}


inline SInt32 GetPerkPointsAV()
{
	return PRKFSerialization::GETPP();
	//return GetFullAV(avPerksPoints, *g_player);
}

inline SInt32 GetSkillsPointsAV()
{
	return PRKFSerialization::GETSP();
	//return GetFullAV(avSkillsPoints, *g_player);
}

inline bool GetPRKFStartedAV()
{
	return PRKFSerialization::GETPRKFStarted();
	//return GetFullAV(avPRKFStarted, *g_player) == 1;
}

inline void SetPRKFStartedAV(bool started)
{
	PRKFSerialization::SETPRKFStarted(started);
	//SetBaseAV(avPRKFStarted, *g_player, started? 1:0);
}

inline void ModSkillsPointsAV(SInt32 count)
{
	SInt32 result = GetSkillsPointsAV();
	if (count != 0)
	{
		result = result + count;
		if (result > 65535) result = 65535;
		if (result < 0) result = 0;
		//SetBaseAV(avSkillsPoints, *g_player, result);
		PRKFSerialization::SETSP(result);
	}
}

inline void ModPerkPointsAV(SInt32 count)
{
	SInt32 result = GetPerkPointsAV();
	if (count != 0)
	{
		result = result + count;
		if (result > 255) result = 255;
		if (result < 0) result = 0;
		//SetBaseAV(avPerksPoints, *g_player, result);
		PRKFSerialization::SETPP(result);
	}
}

AvailablePerk GetSpecialPerk(BGSPerk* aPerk, int aVal) {
	AvailablePerk result;
	if (aVal > aPerk->numRanks)
	{
		result.Perk = nullptr;
		result.Level = 0;
		result.NumRanks = 0;
		result.ranksInfo = BSFixedString("");
		return result;
	}
	BGSPerk* tempperk = aPerk;
	for (int i = 0; i < aVal - 1; i++)
	{
		tempperk = tempperk->nextPerk;
	}
	result.Perk = tempperk;
	result.Level = aVal;
	result.NumRanks = 9;
	result.ranksInfo = BSFixedString("");
	return result;
}

AvailablePerk GetAvailablePerk(BGSPerk* aPerk) {
	AvailablePerk result;

	result.Level = 0;
	result.Perk = nullptr;
	result.ranksInfo = BSFixedString("");
	result.NumRanks = aPerk->numRanks;
	std::string tempRanksInfo = "";
	BGSPerk* tempperk;
	switch (aPerk->formID)
	{
	case StrengthPerkID:
		return GetSpecialPerk(aPerk, pSTR);
		break;
	case PerceptionPerkID:
		return GetSpecialPerk(aPerk, pPER);
		break;
	case EndurancePerkID:
		return GetSpecialPerk(aPerk, pEND);
		break;
	case CharismaPerkID:
		return GetSpecialPerk(aPerk, pCHA);
		break;
	case IntelligencePerkID:
		return GetSpecialPerk(aPerk, pINT);
		break;
	case AgilityPerkID:
		return GetSpecialPerk(aPerk, pAGI);
		break;
	case LuckPerkID:
		return GetSpecialPerk(aPerk, pLCK);
		break;
	default:

		bool gotresult = false;
		bool learned = false;
		tempperk = aPerk;
		// workaround for broken perks with wrong numranks and support one entry multylevel perks
		if (aPerk->numRanks > 1 && (aPerk->nextPerk == aPerk || aPerk->nextPerk == nullptr))
		{
			int hasRank = HasPerk(*g_player, tempperk);
			if (hasRank < aPerk->numRanks)
			{
				result.Level = hasRank+1;
				result.Perk = aPerk;
				return result;
			}
			else
			{
				return result;
			}
		}
		else
		{
			int counter = 0;
			while (true)
			{
				tempperk = tempperk->nextPerk;
				counter++;
				if (tempperk == aPerk || tempperk == nullptr)
				{
					break;
				}
			}
			if (counter != aPerk->numRanks)
			{
				result.NumRanks = counter;
			}
		}
		// end
		tempperk = aPerk;

		for (int i = 0; i < result.NumRanks; i++)
		{
			if (!HasPerk(*g_player, tempperk))
			{
				if (!gotresult)
				{
					gotresult = true;
					if (learned)
					{
						tempRanksInfo += "\n<u>$PRKF_NotLearned:</u>\n";
					}
					else
					{
						tempRanksInfo += "<u>$PRKF_NotLearned:</u>\n";
					}
					result.Perk = tempperk;
					result.Level = i + 1;
				}
				auto perkdata = getperkreqs_internal(tempperk);
				if (perkdata.isEligible)
				{
					tempRanksInfo += "$Rank: " + std::to_string(i + 1) + "\n" + std::string(GetDescription(tempperk)) + "\n";
				}
				else
				{
					if (perkdata.reqlevel > pLVL)
					{
						tempRanksInfo += "$Rank: " + std::to_string(i + 1) + ". $PRKF_Requires: <font color=\'#fa8e47\'>$PRKF_Level " + std::to_string(perkdata.reqlevel) + "</font>" + perkdata.reqs + "\n" + std::string(GetDescription(tempperk)) + "\n";
					}
					else
					{
						tempRanksInfo += "$Rank: " + std::to_string(i + 1) + ". $PRKF_Requires: $PRKF_Level " + std::to_string(perkdata.reqlevel) + "" + perkdata.reqs + "\n" + std::string(GetDescription(tempperk)) + "\n";
					}

				}
				//return result;
			}
			else
			{
				if (!learned)
				{
					learned = true;
					tempRanksInfo += "<u>$PRKF_Learned:</u>\n";
				}
				tempRanksInfo += "$Rank: " + std::to_string(i + 1) + "\n" + std::string(GetDescription(tempperk)) + "\n";
			}
			tempperk = tempperk->nextPerk;
		}
		break;
	}
	result.ranksInfo = BSFixedString(tempRanksInfo.c_str());
	return result;
}

perkData getperkreqs_internal(BGSPerk* thisPerk) {

	perkData result;
	PlayerCharacter* pPC = (*g_player);
	bool isAllowable = true;
	bool isHighLevel = thisPerk->perkLevel > pLVL;
	bool isEligible = !isHighLevel;
	int filterFlag = 0;
	result.reqlevel = thisPerk->perkLevel;
	std::string str = ", ";
	/*if (isHighLevel)
		str = "$PRKF_Requires: <font color=\'#fa8e47\'>";// fa8e47
	else
		str = "$PRKF_Requires: ";
	str += "$PRKF_Level " + std::to_string(thisPerk->perkLevel);
	if (isHighLevel)
		str += "</font>";*/
	Condition* tempcondition = thisPerk->condition;
	bool lastFlag = false; // and
	while (tempcondition) {
		UInt32 functionId = tempcondition->functionId;
		float compareValue = tempcondition->compareValue;
		TESForm * param1 = tempcondition->param1.form;
		UInt32 u321 = tempcondition->param1.u32;
		UInt8 op = tempcondition->comparisonType.op;
		UInt8 flag = tempcondition->comparisonType.flags;
		ActorValueInfo * tempav;
		bool iselig = true;
		switch (functionId)
		{
		case kFunction_GetPermanentValue:
		case kFunction_GetBaseValue:
		case kFunction_GetValue:
			tempav = DYNAMIC_CAST(param1, TESForm, ActorValueInfo);
			switch (op)
			{
			case kCompareOp_Equal:
				iselig = GetBaseAV(tempav, pPC) == compareValue;
				break;
			case kCompareOp_NotEqual:
				iselig = GetBaseAV(tempav, pPC) != compareValue;
				break;
			case kCompareOp_Greater:
				iselig = GetBaseAV(tempav, pPC) > compareValue;
				break;
			case kCompareOp_GreaterEqual:
				iselig = GetBaseAV(tempav, pPC) >= compareValue;
				break;
			case kCompareOp_Less:
				iselig = GetBaseAV(tempav, pPC) < compareValue;
				break;
			case kCompareOp_LessEqual:
				iselig = GetBaseAV(tempav, pPC) <= compareValue;
				break;
			default:
				break;
			}
			switch (tempav->formID)
			{
			case StrengthID:
				filterFlag |= filterFlag_S;
				break;
			case PerceptionID:
				filterFlag |= filterFlag_P;
				break;
			case EnduranceID:
				filterFlag |= filterFlag_E;
				break;
			case CharismaID:
				filterFlag |= filterFlag_C;
				break;
			case IntelligenceID:
				filterFlag |= filterFlag_I;
				break;
			case AgilityID:
				filterFlag |= filterFlag_A;
				break;
			case LuckID:
				filterFlag |= filterFlag_L;
				break;
			default:
				filterFlag |= filterFlag_NonSpecial;
				break;
			}

			//	if (iselig)
			//		str += "";
			//	else
			//		str += "<font color=\'#fa8e47\'>";// fa8e47
			if (!iselig)
				str += "<font color=\'#fa8e47\'>";// fa8e47
			if (tempav->fullName.name == BSFixedString(""))
			{
				str += tempav->avName;
			}
			else {
				str += GetName(tempav).c_str();
			}

			str += compareops[op] + std::to_string((int)compareValue);
			if (!iselig)
				str += "</font>";
			break;
		case kFunction_GetIsSex:
			isAllowable = isAllowable && (pSex != (u321 ^ (int)compareValue ^ (op != kCompareOp_Equal)));
			break;
		case kFunction_HasPerk:

			break;
		default:
			break;
		}
		lastFlag = ((flag & 1) == 0);
		tempcondition = tempcondition->next;
		if (tempcondition)
		{
			if (lastFlag)
			{
				str += ", ";
			}
			else
			{
				str += " $PRKF_or ";
			}
		}
	}
	result.isEligible = isEligible & EvaluationConditions(&(thisPerk->condition), pPC, pPC);
	result.isAllowable = isAllowable;
	result.isHighLevel = isHighLevel;
	if (filterFlag == 0) filterFlag |= filterFlag_Other;
	result.filterFlag = filterFlag | (result.isEligible ? 1 : 2);
	result.reqs = str;
	result.SWFPath = thisPerk->swfPath;
	return result;
}

void PopulatePerkEntry(GFxValue * dst, GFxMovieRoot * root, BGSPerk * basePerk) {
	//_DMESSAGE("PopulatePerkEntry %s", basePerk->fullName.name.c_str());
	AvailablePerk curperk = GetAvailablePerk(basePerk);
	if (curperk.Perk != nullptr)
	{

		perkData tempperkdata = getperkreqs_internal(curperk.Perk);
		GFxValue arrArg;
		root->CreateObject(&arrArg);

		RegisterString(&arrArg, root, "text", curperk.Perk->fullName.name);
		RegisterString(&arrArg, root, "reqs", tempperkdata.reqs.c_str());
		RegisterInt(&arrArg, "filterFlag", tempperkdata.filterFlag); //,tempperkdata.isEligible? 1:2);
		RegisterBool(&arrArg, "iselig", tempperkdata.isEligible);
		RegisterBool(&arrArg, "isHighLevel", tempperkdata.isHighLevel);
		RegisterInt(&arrArg, "reqlevel", tempperkdata.reqlevel);
		RegisterInt(&arrArg, "qname", basePerk->formID);
		RegisterInt(&arrArg, "formid", curperk.Perk->formID);
		RegisterInt(&arrArg, "level", curperk.Level);
		RegisterString(&arrArg, root, "SWFPath", tempperkdata.SWFPath.c_str());
		RegisterInt(&arrArg, "numranks", curperk.NumRanks);

		//if (basePerk->formID == IntenseTrainingPerkID) {
		//	RegisterInt(&arrArg, "type", type_intensetraining);
		//}
		//else {
		RegisterInt(&arrArg, "type", type_default);
		//}

		RegisterString(&arrArg, root, "ranksInfo", curperk.ranksInfo);
		RegisterString(&arrArg, root, "description", GetDescription(curperk.Perk).c_str());
		if (tempperkdata.isAllowable)// && !tempperkdata.isHighLevel)
		{
			dst->PushBack(&arrArg);
		}
	}
}

void PopulateSkillEntry(GFxValue * dst, GFxMovieRoot * root, ActorValueInfo * baseSkill)
{
	GFxValue arrArg;
	root->CreateObject(&arrArg);
	float value = GetBaseAV(baseSkill, (*g_player));
	float buffedValue = GetFullAV(baseSkill, (*g_player));
	RegisterString(&arrArg, root, "text", baseSkill->fullName.name);
	RegisterString(&arrArg, root, "qname", baseSkill->GetEditorID());
	RegisterString(&arrArg, root, "description", GetDescription(baseSkill).c_str());
	RegisterInt(&arrArg, "formid", baseSkill->formID);
	RegisterInt(&arrArg, "value", (int)value);
	RegisterInt(&arrArg, "basevalue", (int)value);
	RegisterInt(&arrArg, "unmodifiedValue", (int)value);
	RegisterInt(&arrArg, "buffedvalue", (int)buffedValue);
	RegisterBool(&arrArg, "alreadyTagged", PRKFSerialization::CheckTaggedSkill(baseSkill->formID));
	RegisterBool(&arrArg, "tagged", PRKFSerialization::CheckTaggedSkill(baseSkill->formID));
	dst->PushBack(&arrArg);
	//_DMESSAGE("EdID: %s, FormID: %i, value: %i, description %s", baseSkill->avName, baseSkill->formID, (int)value, GetDescription(baseSkill).c_str());
}

bool processTagSkillsLists(GFxMovieRoot * root) {
	GetBasicData();
	GFxValue arrArgs[4];
	root->CreateArray(&arrArgs[0]);
	for (int j = 0; j < Skills.count; j++)
	{
		ActorValueInfo * baseSkill = Skills.entries[j];
		PopulateSkillEntry(&arrArgs[0], root, baseSkill);
	}
	arrArgs[1].SetInt(tagSkillsNum);
	arrArgs[2].SetInt(tagSkillsAmount);
	arrArgs[3].SetBool(tagSkillsAllowRetag);
	root->Invoke("root.Menu_mc.tagSkillsModeStart", nullptr, arrArgs, 4);
	return true;
}

bool processTraitsLists(GFxMovieRoot * root) {
	GFxValue arrArgs[3];
	root->CreateArray(&arrArgs[0]);
	BGSPerk * temptrait;
	for (size_t i = 0; i < traitsList->forms.count; i++)
	{
		temptrait = DYNAMIC_CAST(traitsList->forms.entries[i], TESForm, BGSPerk);
		if (!temptrait)
			continue;
		if (HasPerk(*g_player, temptrait)>=temptrait->numRanks)
			continue;
		GFxValue arrArg;
		root->CreateObject(&arrArg);

		RegisterString(&arrArg, root, "text", temptrait->fullName.name);
		RegisterString(&arrArg, root, "reqs", "");
		RegisterInt(&arrArg, "filterFlag", 1); //,tempperkdata.isEligible? 1:2);
		RegisterBool(&arrArg, "iselig", 1);
		RegisterBool(&arrArg, "isHighLevel", 0);
		RegisterInt(&arrArg, "reqlevel", 1);
		RegisterInt(&arrArg, "qname", temptrait->formID);
		RegisterInt(&arrArg, "formid", temptrait->formID);
		RegisterInt(&arrArg, "level", HasPerk(*g_player, temptrait));
		RegisterString(&arrArg, root, "SWFPath", temptrait->swfPath.c_str());
		RegisterInt(&arrArg, "numranks", temptrait->numRanks);
		RegisterInt(&arrArg, "type", type_default);

		RegisterString(&arrArg, root, "ranksInfo", "");
		RegisterString(&arrArg, root, "description", GetDescription(temptrait).c_str());
		arrArgs[0].PushBack(&arrArg);

	}
	arrArgs[1].SetInt(traitsPoints);
	arrArgs[2].SetBool(traitsAllowClose);
	root->Invoke("root.Menu_mc.traitsModeStart", nullptr, arrArgs, 3);
	return true;
}

bool processLists(GFxMovieRoot * root) {
	GetBasicData();
	GFxValue arrArgs[5];
	root->CreateArray(&arrArgs[0]);
	for (int i = 0; i < Perks.count; i++)
	{
		BGSPerk * basePerk = Perks.entries[i];
		PopulatePerkEntry(&arrArgs[0], root, basePerk);
	}
	root->CreateArray(&arrArgs[1]);
	for (int j = 0; j < Skills.count; j++)
	{
		ActorValueInfo * baseSkill = Skills.entries[j];
		PopulateSkillEntry(&arrArgs[1], root, baseSkill);
	}
	_DMESSAGE("filling special");
	//--------------------------------fill special----------------------
	GFxValue arrSpec;
	root->CreateArray(&arrSpec);
	GFxValue Spec;
	Spec.SetInt(pSTR);
	arrSpec.PushBack(&Spec);
	Spec.SetInt(pPER);
	arrSpec.PushBack(&Spec);
	Spec.SetInt(pEND);
	arrSpec.PushBack(&Spec);
	Spec.SetInt(pCHA);
	arrSpec.PushBack(&Spec);
	Spec.SetInt(pINT);
	arrSpec.PushBack(&Spec);
	Spec.SetInt(pAGI);
	arrSpec.PushBack(&Spec);
	Spec.SetInt(pLCK);
	arrSpec.PushBack(&Spec);
	root->SetVariable("root.Menu_mc.Specials", &arrSpec);
	/*
	std::string specials = "";
	specials += "S:" + std::to_string(pSTR) + " | ";
	specials += "P:" + std::to_string(pPER) + " | ";
	specials += "E:" + std::to_string(pEND) + " | ";
	specials += "C:" + std::to_string(pCHA) + " | ";
	specials += "I:" + std::to_string(pINT) + " | ";
	specials += "A:" + std::to_string(pAGI) + " | ";
	specials += "L:" + std::to_string(pLCK);
	arrArgs[2].SetString(specials.c_str());*/
	//--------------------------------EO fill special-------------------
	arrArgs[2].SetInt((int)PerksPoints);
	arrArgs[3].SetInt((int)SkillsPoints);
	root->Invoke("root.Menu_mc.menuStart", nullptr, arrArgs, 4);

	return true;
}

void GetBasicData() {
	_DMESSAGE("GetBasicData");
	PlayerCharacter* pPlayerCharacter = (*g_player);
	if (GetPRKFStartedAV() == 0)
	{
		//SInt32 ppts = GetPerkPoints();
		//papNotification(std::to_string(ppts)+" perkpoints will be converted to PRKF format");
		//ModPerkPointsAV(ppts);
		_DMESSAGE("PRKF started");
		SetPRKFStartedAV(1);
	}
	//int realPP = GetPerkPoints();
	//int	modsPP = GetPerkPointsAV();
	//if (modsPP != realPP)
	//{
	//	ModPerkPointsAV(realPP- modsPP);
	//}
	PerksPoints = GetPerkPoints();
	SkillsPoints = GetSkillsPointsAV();
	pLVL = GetLevel(pPlayerCharacter);
	pSex = GetActorSex(pPlayerCharacter);
	pSTR = (int)GetAVValueByFormID(StrengthID, pPlayerCharacter);
	pPER = (int)GetAVValueByFormID(PerceptionID, pPlayerCharacter);
	pEND = (int)GetAVValueByFormID(EnduranceID, pPlayerCharacter);
	pCHA = (int)GetAVValueByFormID(CharismaID, pPlayerCharacter);
	pINT = (int)GetAVValueByFormID(IntelligenceID, pPlayerCharacter);
	pAGI = (int)GetAVValueByFormID(AgilityID, pPlayerCharacter);
	pLCK = (int)GetAVValueByFormID(LuckID, pPlayerCharacter);
}

void ReadINIs(std::vector<WIN32_FIND_DATA>* arr)
{
	char* modSettingsDirectory = "Data\\PRKF\\*.ini";

	HANDLE hFind;
	WIN32_FIND_DATA data;
	hFind = FindFirstFile(modSettingsDirectory, &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			arr->push_back(data);
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}
}

class Scaleform_AddPerk : public GFxFunctionHandler
{
public:


	virtual void	Invoke(Args * args) {
		switch (args->args[1].GetUInt())
		{
		case StrengthPerkID:
			ModBaseAVByFormID(StrengthID, *g_player, 1);
			break;
		case PerceptionPerkID:
			ModBaseAVByFormID(PerceptionID, *g_player, 1);
			break;
		case EndurancePerkID:
			ModBaseAVByFormID(EnduranceID, *g_player, 1);
			break;
		case CharismaPerkID:
			ModBaseAVByFormID(CharismaID, *g_player, 1);
			break;
		case IntelligencePerkID:
			ModBaseAVByFormID(IntelligenceID, *g_player, 1);
			break;
		case AgilityPerkID:
			ModBaseAVByFormID(AgilityID, *g_player, 1);
			break;
		case LuckPerkID:
			ModBaseAVByFormID(LuckID, *g_player, 1);
			break;
		default:
			TESForm * aForm = LookupFormByID(args->args[0].GetUInt());
			BGSPerk* aPerk = DYNAMIC_CAST(aForm, TESForm, BGSPerk);
			AddPerk(*g_player, aPerk, 0);
			break;
		}
		//ModPerkPointsAV(-1);
		ModPerkPoints(-1);
		UpdateMenu_int();
	}
};

class Scaleform_AddTrait : public GFxFunctionHandler
{
public:


	virtual void	Invoke(Args * args) {
		TESForm * aForm = LookupFormByID(args->args[0].GetUInt());
		BGSPerk* aPerk = DYNAMIC_CAST(aForm, TESForm, BGSPerk);
		AddPerk(*g_player, aPerk, 0);
	}
};

class Scaleform_LearnSkills : public GFxFunctionHandler
{
public:


	virtual void	Invoke(Args * args) {
		UInt32 count = args->args[0].GetArraySize();
		ModSkillsPointsAV(args->args[1].GetInt());
		//ModAV(aSP, *g_player, args->args[1].GetInt());
		GFxValue arrayelement;
		GFxValue objelementformid;
		GFxValue objelementvalue;
		for (int i = 0; i < count; i++)
		{
			args->args[0].GetElement(i, &arrayelement);
			arrayelement.GetMember("iformid", &objelementformid);
			arrayelement.GetMember("ivalue", &objelementvalue);
			//_DMESSAGE("formid: %i, value: %i", objelementformid.GetInt(), objelementvalue.GetInt());
			ModBaseAVByFormID(objelementformid.GetInt(), *g_player, objelementvalue.GetInt());
		}
		UpdateMenu_int();
	}
};

class Scaleform_CloseMenu : public GFxFunctionHandler
{
public:


	virtual void	Invoke(Args * args) {
		//RegisterForInput(false);
	}
};

class Scaleform_OpenMenu : public GFxFunctionHandler
{
public:


	virtual void	Invoke(Args * args) {
		//RegisterForInput(true);
	}
};

class Scaleform_MessageBox : public GFxFunctionHandler
{
public:


	virtual void	Invoke(Args * args) {
		if (args->args[0].GetType() != GFxValue::kType_String) return;
		papMessageBox(args->args[0].GetString());
	}
};

class Scaleform_PlayPerkSound : public GFxFunctionHandler
{
public:


	virtual void	Invoke(Args * args) {
		if (args->args[0].GetType() != GFxValue::kType_Int) return;
		LevelUpMenu* menu = DYNAMIC_CAST((*g_ui)->GetMenu(BSFixedString("LevelUpMenu")), IMenu, LevelUpMenu);
		if (!menu) return;
		LevelupMenuPlayPerkSound(menu, args->args[0].GetInt());
	}
};

class Scaleform_PlaySound2 : public GFxFunctionHandler
{
public:


	virtual void	Invoke(Args * args) {
		if (args->args[0].GetType() != GFxValue::kType_String) return;
		PlaySound2_int(args->args[0].GetString());
	}
};

class Scaleform_TagSkill : public GFxFunctionHandler
{
public:


	virtual void	Invoke(Args * args) {
		_MESSAGE("type1 %i type2 %i", args->args[0].GetType(), args->args[1].GetType());
		PRKFSerialization::AddTS(args->args[0].GetUInt());
		SetBaseAVByFormID(args->args[0].GetUInt(), *g_player, args->args[1].GetUInt());
		_DMESSAGE("tagskill: %08X setbasevalue to %i", args->args[0].GetUInt(), args->args[1].GetUInt());
	}
};

class Scaleform_UnTagSkill : public GFxFunctionHandler
{
public:


	virtual void	Invoke(Args * args) {
		_MESSAGE("type1 %i type2 %i", args->args[0].GetType(), args->args[1].GetType());
		PRKFSerialization::RemoveTS(args->args[0].GetUInt());
		SetBaseAVByFormID(args->args[0].GetUInt(), *g_player, args->args[1].GetUInt());
		_DMESSAGE("untagskill: %08X setbasevalue to %i", args->args[0].GetUInt(), args->args[1].GetUInt());
	}
};

bool RegisterScaleform(GFxMovieView * view, GFxValue * f4se_root)
{
	RegisterFunction<Scaleform_TagSkill>(f4se_root, view->movieRoot, "TagSkill");
	RegisterFunction<Scaleform_UnTagSkill>(f4se_root, view->movieRoot, "UnTagSkill");
	RegisterFunction<Scaleform_AddPerk>(f4se_root, view->movieRoot, "AddPerk");
	RegisterFunction<Scaleform_AddTrait>(f4se_root, view->movieRoot, "AddTrait");
	RegisterFunction<Scaleform_LearnSkills>(f4se_root, view->movieRoot, "LearnSkills");
	RegisterFunction<Scaleform_OpenMenu>(f4se_root, view->movieRoot, "OpenMenu");
	RegisterFunction<Scaleform_CloseMenu>(f4se_root, view->movieRoot, "CloseMenu");
	RegisterFunction<Scaleform_MessageBox>(f4se_root, view->movieRoot, "MessageBox");
	RegisterFunction<Scaleform_PlayPerkSound>(f4se_root, view->movieRoot, "PlayPerkSound");
	RegisterFunction<Scaleform_PlaySound2>(f4se_root, view->movieRoot, "PlaySound2");

	GFxMovieRoot	*movieRoot = view->movieRoot;

	GFxValue currentSWFPath;
	std::string currentSWFPathString = "";
	if (movieRoot->GetVariable(&currentSWFPath, "root.loaderInfo.url")) {
		currentSWFPathString = currentSWFPath.GetString();
	}
	else {
		_MESSAGE("WARNING: Scaleform registration failed.");
	}
	if (currentSWFPathString.find("LevelUpMenu.swf") != std::string::npos) {
		_MESSAGE("Hooking LevelUpMenu menu.");
		//RegisterForInput(true);
		auto root = view->movieRoot;
		if (!root)
			return false;
	//	processLists(root);
	}
	return true;
}

void populateVanilaPerks()
{
	BGSPerk * tempPerk;
	tempPerk = DYNAMIC_CAST(LookupFormByID(890756), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(121598), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(303285), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(307796), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(307795), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(303318), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(307790), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(1909895), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(417273), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(1909887), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(317595), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(890761), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(317578), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(303286), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(860807), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(336895), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(313635), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(313659), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(829853), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(313642), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(150271), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(317584), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(890766), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(303275), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(303289), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(303311), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(303317), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(931577), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(955475), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(1909881), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(313645), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(307801), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(317598), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(317607), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(890771), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(1909846), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(105123), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(303316), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(1909867), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(307821), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(124543), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(317581), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(317575), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(317576), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(1909857), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(1909898), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(1901237), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(890776), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(133073), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(313638), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(303322), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(336899), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(417381), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(156889), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(931583), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(317577), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(1909871), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(317574), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(890781), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(303263), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(303301), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(313653), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(307800), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(317545), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(317554), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(318958), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(317606), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(139772), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(1909841), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(317569), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(890786), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(313666), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(303280), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(303291), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(313641), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(1909854), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(317562), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(313631), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(317602), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(317589), TESForm, BGSPerk);
	Perks.Push(tempPerk);
	tempPerk = DYNAMIC_CAST(LookupFormByID(1909884), TESForm, BGSPerk);
	Perks.Push(tempPerk);
}

void fillarrays()
{
	Perks.Clear();
	Skills.Clear();
	std::vector<WIN32_FIND_DATA> modSettingFiles;
	ReadINIs(&modSettingFiles);

	for (int i = 0; i < modSettingFiles.size(); i++) {
		_MESSAGE("ini: %s", modSettingFiles[i].cFileName);
		SInt8 iniVersion = _GetConfigOptionInt(modSettingFiles[i].cFileName, "Main", "INIVersion");
		_MESSAGE("ini version: %i", iniVersion);
		if (iniVersion != CURRENT_INI_VERSION)
		{
			modsWithWrongIniVersion += modSettingFiles[i].cFileName;
			modsWithWrongIniVersion += "\n";
			continue;
		}
		SInt8 currentDisableVanillaPerks = _GetConfigOptionInt(modSettingFiles[i].cFileName, "Main", "disableVanillaPerks");
		UInt32 currentOverrideMaxSkillsValue = _GetConfigOptionInt(modSettingFiles[i].cFileName, "Main", "overrideMaxSkillsValue");
		if (currentOverrideMaxSkillsValue != 0)
		{
			if (overrideMaxSkillsValue != 100 && currentOverrideMaxSkillsValue != overrideMaxSkillsValue)
			{
				_WARNING("There are few ini files with overrideMaxSkillsValue. Last value will be used.");
			}			
			overrideMaxSkillsValue = currentOverrideMaxSkillsValue;
		}
		_MESSAGE("disableVanillaPerks: %i", currentDisableVanillaPerks);
		disableVanillaPerks |= currentDisableVanillaPerks;
		std::string PerksList = _GetConfigOptionString(modSettingFiles[i].cFileName, "Main", "PerksList");
		_MESSAGE("PerksList %s", PerksList.c_str());
		if (PerksList.size() > 0)
		{
			auto _PerksList = DYNAMIC_CAST(GetFormFromIdentifier(PerksList), TESForm, BGSListForm);
			if (_PerksList == nullptr) {
				_DMESSAGE("form is not BGSListForm");
				continue;
			}
			_DMESSAGE("form count %i", _PerksList->forms.count);
			for (int j = 0; j < _PerksList->forms.count; j++)
			{
				BGSPerk * basePerk = DYNAMIC_CAST(_PerksList->forms.entries[j], TESForm, BGSPerk);
				if (basePerk == nullptr) {
					_DMESSAGE("entry is not a perk");
					continue;
				}
				//_DMESSAGE("entry is a perk: %s", basePerk->GetFullName());
				//_MESSAGE("tempPerk = DYNAMIC_CAST(GetFormFromIdentifier(%i), TESForm, BGSPerk);", basePerk->formID);
				//_MESSAGE("Perks.Push(tempPerk);");
				Perks.Push(basePerk);
			}
		}

		std::string SkillsList = _GetConfigOptionString(modSettingFiles[i].cFileName, "Main", "SkillsList");
		_MESSAGE("SkillsList %s", SkillsList.c_str());
		if (SkillsList.size() > 0)
		{
			auto _SkillsList = DYNAMIC_CAST(GetFormFromIdentifier(SkillsList), TESForm, BGSListForm);
			if (_SkillsList == nullptr) {
				_DMESSAGE("form is not BGSListForm");
				continue;
			}
			_DMESSAGE("form count %i", _SkillsList->forms.count);
			for (int j = 0; j < _SkillsList->forms.count; j++)
			{
				ActorValueInfo * baseSkill = DYNAMIC_CAST(_SkillsList->forms.entries[j], TESForm, ActorValueInfo);
				if (baseSkill == nullptr) {
					_DMESSAGE("entry is not a avif");
					continue;
				}
				//_DMESSAGE("entry is a avif: %s", baseSkill->GetFullName());
				Skills.Push(baseSkill);
			}
		}
		SInt8 PPPerLevel = _GetConfigOptionInt(modSettingFiles[i].cFileName, "Main", "PPPerLevel");
		_MESSAGE("PPPerLevel %i", PPPerLevel);
		PPPerLevelToAdd += PPPerLevel;
		SInt16 SPPerLevel = _GetConfigOptionInt(modSettingFiles[i].cFileName, "Main", "SPPerLevel");
		_MESSAGE("SPPerLevel %i", SPPerLevel);
		SPPerLevelToAdd += SPPerLevel;
	}

	_DMESSAGE("Total PP to add per level: %i ", PPPerLevelToAdd);
	_DMESSAGE("Total SP to add per level: %i ", SPPerLevelToAdd);
	_MESSAGE("total perks count: %i", Perks.count);
	_MESSAGE("total skills count: %i", Skills.count);
	PRKFReadyMessage message;
	g_messaging->Dispatch(g_pluginHandle, PRKFReadyMessage::kMessage_PRKFReady, (void*)&message, sizeof(PRKFReadyMessage*), nullptr);
}

bool UpdateMenu_int()
{
	_DMESSAGE("update menu");
	if (!vanillaPerksPopulated)
	{
		vanillaPerksPopulated = true;
		if (disableVanillaPerks)
		{
			_DMESSAGE("Vanilla perks disabled!");
		}
		else
		{
			_DMESSAGE("populate vanilla perks!");
			populateVanilaPerks();
		}
	}

	IMenu * menu = (*g_ui)->GetMenu(BSFixedString("LevelUpMenu"));
	if (!menu)
	{
		_DMESSAGE("menu closed");
		return false;
	}
	else
	{
		_DMESSAGE("menu opened");
	}

	auto movie = menu->movie;
	if (!movie)
		return false;

	auto root = movie->movieRoot;
	if (!root)
		return false;

	PRKF_ModSettings::ReadModSettings();
	GFxValue val;
	val.SetBool(PRKF_ModSettings::bPlayPerkSound);
	root->SetVariable("root.Menu_mc.bPlayPerkSound", &val);
	val.SetBool(PRKF_ModSettings::bPlayPerkSoundLoop);
	root->SetVariable("root.Menu_mc.bPlayPerkSoundLoop", &val);
	if (currentMode == traitsMode)
	{
		processTraitsLists(root);
		return true;
	}
	if (currentMode == tagSkillsMode)
	{
		processTagSkillsLists(root);
		return true;
	}
	if (PRKF_ModSettings::bIneligible)
	{
		val.SetInt(2);
	}
	else
	{
		val.SetInt(-2);
	}
	GFxValue loadedVar;
	root->GetVariable(&loadedVar, "root.Menu_mc.loaded");
	if (loadedVar.GetInt() == 0)
	{
		root->SetVariable("root.Menu_mc.fFinit", &val);
	}
	GFxValue maxSkillsValue;
	maxSkillsValue.SetInt(overrideMaxSkillsValue);
	_DMESSAGE("overrideMaxSkillsValue %i", overrideMaxSkillsValue);
	root->SetVariable("root.Menu_mc.maxSkillLevel", &maxSkillsValue);
	processLists(root);
	return true;
}

bool DoMagic(StaticFunctionTag *base) {

	return true;

}

SInt32 PRKF_Papyrus::AddPP(StaticFunctionTag*, SInt32 aiPP)
{
	//ModPerkPointsAV(aiPP);
	ModPerkPoints(aiPP);
	return GetPerkPoints();
}

SInt32 PRKF_Papyrus::AddSP(StaticFunctionTag*, SInt32 aiSP)
{
	ModSkillsPointsAV(aiSP);
	UpdateMenu_int();
	return GetSkillsPointsAV();
}

SInt32 PRKF_Papyrus::GetPP(StaticFunctionTag*)
{
	return GetPerkPoints();
}

SInt32 PRKF_Papyrus::GetSP(StaticFunctionTag*)
{
	return GetSkillsPointsAV();
}

bool PRKF_Papyrus::UpdateMenu(StaticFunctionTag*)
{
	return UpdateMenu_int();
}

void PRKF_Papyrus::OpenMenu(StaticFunctionTag*)
{
	MenuOpenClose_int("VignetteMenu", true);
	MenuOpenClose_int("LevelUpMenu", true);
}

void PRKF_Papyrus::OpenTraitsMenu(StaticFunctionTag*, BGSListForm* list, UInt32 TP, bool allowClose)
{
	if (!list)
		return;
	currentMode = traitsMode;
	traitsList = list;
	traitsPoints = TP;
	traitsAllowClose = allowClose;
	MenuOpenClose_int("VignetteMenu", true);
	MenuOpenClose_int("LevelUpMenu", true);
}

void PRKF_Papyrus::OpenTagSkillsMenu(StaticFunctionTag*, UInt32 numSkills, UInt32 numPoints, bool allowRetag)
{
	currentMode = tagSkillsMode;
	tagSkillsNum = numSkills;
	tagSkillsAmount = numPoints;
	tagSkillsAllowRetag = allowRetag;
	MenuOpenClose_int("VignetteMenu", true);
	MenuOpenClose_int("LevelUpMenu", true);
}

void PRKF_Papyrus::AddTagSkillAV(StaticFunctionTag*, ActorValueInfo* skill)
{
	PRKFSerialization::AddTS(skill->formID);
}

void PRKF_Papyrus::RemoveTagSkillAV(StaticFunctionTag*, ActorValueInfo* skill)
{
	PRKFSerialization::RemoveTS(skill->formID);
}

bool PRKF_Papyrus::IsTagSkillAV(StaticFunctionTag*, ActorValueInfo* skill)
{
	return PRKFSerialization::CheckTaggedSkill(skill->formID);
}

bool RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, bool>("DoMagicPRKF", "MyDebug:debugS", DoMagic, vm));
	vm->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, SInt32, SInt32>("AddPP", "PRKF:PRKF", PRKF_Papyrus::AddPP, vm));
	vm->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, SInt32, SInt32>("AddSP", "PRKF:PRKF", PRKF_Papyrus::AddSP, vm));
	vm->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, SInt32>("GetPP", "PRKF:PRKF", PRKF_Papyrus::GetPP, vm));
	vm->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, SInt32>("GetSP", "PRKF:PRKF", PRKF_Papyrus::GetSP, vm));
	vm->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, bool>("UpdateMenu", "PRKF:PRKF", PRKF_Papyrus::UpdateMenu, vm));
	vm->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, void>("OpenMenu", "PRKF:PRKF", PRKF_Papyrus::OpenMenu, vm));
	vm->RegisterFunction(
		new NativeFunction3 <StaticFunctionTag, void, BGSListForm*, UInt32, bool>("OpenTraitsMenuFL", "PRKF:PRKF", PRKF_Papyrus::OpenTraitsMenu, vm));
	vm->RegisterFunction(
		new NativeFunction3 <StaticFunctionTag, void, UInt32, UInt32, bool>("OpenTagSkillsMenu", "PRKF:PRKF", PRKF_Papyrus::OpenTagSkillsMenu, vm));
	vm->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, ActorValueInfo*>("AddTagSkillAV", "PRKF:PRKF", PRKF_Papyrus::AddTagSkillAV, vm));
	vm->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, ActorValueInfo*>("RemoveTagSkillAV", "PRKF:PRKF", PRKF_Papyrus::RemoveTagSkillAV, vm));
	vm->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, bool, ActorValueInfo*>("IsTagSkillAV", "PRKF:PRKF", PRKF_Papyrus::IsTagSkillAV, vm));
	return true;
}

//-------------------------
// Input Handler
//-------------------------
class F4SEInputHandler : public BSInputEventUser
{
public:
	F4SEInputHandler() : BSInputEventUser(true) { }

	virtual void OnButtonEvent(ButtonEvent * inputEvent)
	{
		UInt32	keyCode;
		UInt32	deviceType = inputEvent->deviceType;
		UInt32	keyMask = inputEvent->keyMask;

		if (deviceType == InputEvent::kDeviceType_Mouse) {
			// Mouse
			keyCode = InputMap::kMacro_MouseButtonOffset + keyMask;
		}
		else if (deviceType == InputEvent::kDeviceType_Gamepad) {
			// Gamepad
			keyCode = InputMap::GamepadMaskToKeycode(keyMask);
		}
		else {
			// Keyboard
			keyCode = keyMask;
		}

		float timer = inputEvent->timer;
		bool  isDown = inputEvent->isDown == 1.0f && timer == 0.0f;
		bool  isUp = inputEvent->isDown == 0.0f && timer != 0.0f;

		BSFixedString* control = inputEvent->GetControlID();

		if (isDown) {
			ProcessKeyEvent(keyCode, true);
			ProcessUserEvent(control->c_str(), true, deviceType, keyCode);
		}
		else if (isUp) {
			ProcessKeyEvent(keyCode, false);
			ProcessUserEvent(control->c_str(), false, deviceType, keyCode);
		}
	}
};

F4SEInputHandler g_scaleformInputHandler;

void ProcessKeyEvent(UInt32 keyCode, bool isDown)
{
	BSFixedString mainMenuStr("LevelUpMenu");
	if ((*g_ui)->IsMenuOpen("LevelUpMenu")) {
		IMenu* menu = (*g_ui)->GetMenu(mainMenuStr);
		GFxMovieRoot* movieRoot = menu->movie->movieRoot;
		GFxValue args[2];
		args[0].SetInt(keyCode);
		args[1].SetBool(isDown);
		movieRoot->Invoke("root.Menu_mc.ProcessKeyEventEx", nullptr, args, 2);
	}
}

void ProcessUserEvent(const char * controlName, bool isDown, int deviceType, UInt32 keyCode)
{
	BSFixedString mainMenuStr("LevelUpMenu");
	if ((*g_ui)->IsMenuOpen("LevelUpMenu")) {
		IMenu* menu = (*g_ui)->GetMenu(mainMenuStr);
		GFxMovieRoot* movieRoot = menu->movie->movieRoot;
		GFxValue args[4];
		args[0].SetString(controlName);
		args[1].SetBool(isDown);
		args[2].SetInt(deviceType);
		args[3].SetInt(keyCode);
		movieRoot->Invoke("root.Menu_mc.ProcessUserEventEx", nullptr, args, 4);
	}
}

void RegisterForInput(bool bRegister) {
	if (bRegister) {
		g_scaleformInputHandler.enabled = true;
		tArray<BSInputEventUser*>* inputEvents = &((*g_menuControls)->inputEvents);
		BSInputEventUser* inputHandler = &g_scaleformInputHandler;
		int idx = inputEvents->GetItemIndex(inputHandler);
		if (idx == -1) {
			inputEvents->Push(&g_scaleformInputHandler);
			_MESSAGE("Registered for input events.");
		}
	}
	else {
		g_scaleformInputHandler.enabled = false;
	}
}

#include "f4se/ScaleformLoader.h"

void OnF4SEMessage(F4SEMessagingInterface::Message* msg) {
	switch (msg->type) {
	case F4SEMessagingInterface::kMessage_GameDataReady:
		CheckArchiveInvalidation(mName);
		fillarrays();
		REGISTER_EVENT(LevelIncrease::Event, g_PRKF_LevelIncrease__EventSink);
		static auto pLoadGameHandler = new TESLoadGameHandler();
		GetEventDispatcher<TESLoadGameEvent>()->AddEventSink(pLoadGameHandler);

		break;
	case F4SEMessagingInterface::kMessage_GameLoaded:

		// Inject translations
		BSScaleformTranslator * translator = (BSScaleformTranslator*)(*g_scaleformManager)->stateBag->GetStateAddRef(GFxState::kInterface_Translator);
		if (translator) {
			PRKFTranslator::LoadTranslations(translator);
		}
		break;
	}
}

bool AddData(PRKFAddDataMessage* msg)
{
	_MESSAGE("AddData: %s", msg->ININame.c_str());
	_MESSAGE("ini version: %i", msg->INIVersion);
	if (msg->INIVersion != CURRENT_INI_VERSION)
	{
		modsWithWrongIniVersion += msg->ININame;
		modsWithWrongIniVersion += "\n";
		return false;
	}
	_MESSAGE("disableVanillaPerks: %i", msg->disableVanillaPerks);
	disableVanillaPerks |= msg->disableVanillaPerks;
	if (msg->overrideMaxSkillsValue != 0)
	{
		if (overrideMaxSkillsValue != 100 && msg->overrideMaxSkillsValue != overrideMaxSkillsValue)
		{
			_WARNING("There are few ini files with overrideMaxSkillsValue. Last value will be used.");
		}
		overrideMaxSkillsValue = msg->overrideMaxSkillsValue;
	}

	if (msg->PerksList == nullptr) {
		_DMESSAGE("form is not BGSListForm");
	}
	else
	{
		_DMESSAGE("form count %i", msg->PerksList->forms.count);
		for (int j = 0; j < msg->PerksList->forms.count; j++)
		{
			BGSPerk * basePerk = DYNAMIC_CAST(msg->PerksList->forms.entries[j], TESForm, BGSPerk);
			if (basePerk == nullptr) {
				_DMESSAGE("entry is not a perk");
				continue;
			}
			Perks.Push(basePerk);
		}
	}

	if (msg->SkillsList == nullptr) {
		_DMESSAGE("form is not BGSListForm");
	}
	else
	{
		_DMESSAGE("form count %i", msg->SkillsList->forms.count);
		for (int j = 0; j < msg->SkillsList->forms.count; j++)
		{
			ActorValueInfo * baseSkill = DYNAMIC_CAST(msg->SkillsList->forms.entries[j], TESForm, ActorValueInfo);
			if (baseSkill == nullptr) {
				_DMESSAGE("entry is not a avif");
				continue;
			}
			Skills.Push(baseSkill);
		}
	}
	_MESSAGE("PPPerLevel %i", msg->PPPerLevel);
	PPPerLevelToAdd += msg->PPPerLevel;
	_MESSAGE("SPPerLevel %i", msg->SPPerLevel);
	SPPerLevelToAdd += msg->SPPerLevel;

	return true;
}

void PRKFMessageHandler(F4SEMessagingInterface::Message* msg) {
	switch (msg->type)
	{
	case PRKFIsTaggedMessage::kMessage_PRKFIsTagged:
	{
		PRKFIsTaggedMessage * message = (PRKFIsTaggedMessage*)msg->data;
		//_DMESSAGE("%i", message->formid);
		message->tagged = PRKFSerialization::CheckTaggedSkill(message->formid);
		break;
	}
	case PRKFAddDataMessage::kMessage_PRKFAddData:
	{
		PRKFAddDataMessage * message = (PRKFAddDataMessage*)msg->data;
		_DMESSAGE("PRKFAddDataMessage recieved");
		AddData(message);
		break;
	}
	
	}
}

#include "xbyak/xbyak.h"
#include "f4se_common/BranchTrampoline.h"

_SetPerkPoints_int SetPerkPoints_int_Original;

void SetPerkPoints_int_Hook(PlayerCharacter * param1, SInt8 param2) {
	_MESSAGE("Game.AddPerkPoints hook");
	SetPerkPoints_int_Original(param1, param2);
	UpdateMenu_int();
}

_LevelupMenuProcessMessage LevelupMenuProcessMessage_Original;

UInt32 LevelupMenuProcessMessage_Hook(LevelUpMenu * menu, UIMessage * message) {
	if (message->type == 1)
	{
		RegisterForInput(true);
		UpdateMenu_int();
	}
	else if (message->type == 3)
	{
		currentMode = normalMode;
		RegisterForInput(false);
	}
	return LevelupMenuProcessMessage_Original(menu, message);
}


extern "C"
{

	bool F4SEPlugin_Query(const F4SEInterface * f4se, PluginInfo * info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, (const char*)("\\My Games\\Fallout4\\F4SE\\" + mName + ".log").c_str());

		logMessage("query");

		// populate info structure
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = mName.c_str();
		info->version = mVer;

		// store plugin handle so we can identify ourselves later
		g_pluginHandle = f4se->GetPluginHandle();

		// Check game version
		if (f4se->runtimeVersion != CURRENT_RUNTIME_VERSION) {
			_WARNING("WARNING: Unsupported runtime version %08X. This DLL is built for v1.10.89 only.", f4se->runtimeVersion);
			MessageBox(NULL, (LPCSTR)("Unsupported runtime version (expected v1.10.89). \n" + mName + " will be disabled.").c_str(), (LPCSTR)mName.c_str(), MB_OK | MB_ICONEXCLAMATION);
			//	return false;
		}

		// get the papyrus interface and query its version
		g_papyrus = (F4SEPapyrusInterface *)f4se->QueryInterface(kInterface_Papyrus);
		if (!g_papyrus)
		{
			_MESSAGE("couldn't get papyrus interface");
			return false;
		}
		else {
			_MESSAGE("got papyrus interface");
		}
		g_scaleform = (F4SEScaleformInterface *)f4se->QueryInterface(kInterface_Scaleform);
		if (!g_scaleform)
		{
			_MESSAGE("couldn't get scaleform interface");
			return false;
		}
		else {
			_MESSAGE("got scaleform interface");
		}
		// Get the messaging interface
		g_messaging = (F4SEMessagingInterface *)f4se->QueryInterface(kInterface_Messaging);
		if (!g_messaging) {
			_MESSAGE("couldn't get messaging interface");
			return false;
		}
		// Get the serialization interface
		g_serialization = (F4SESerializationInterface *)f4se->QueryInterface(kInterface_Serialization);
		if (!g_serialization) {
			_MESSAGE("couldn't get serialization interface");
			return false;
		}

		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface *f4se)
	{
		logMessage("load");
		if (CheckModDropClientService() == 0)
		{
			_WARNING("WARNING: ModDropClient found.");
			MessageBox(NULL, (LPCSTR)("ModDropClient found. \n" + mName + " will be disabled.").c_str(), (LPCSTR)mName.c_str(), MB_OK | MB_ICONEXCLAMATION);
			return false;
		}

		g_serialization->SetUniqueID(g_pluginHandle, 'PRKF');
		g_serialization->SetRevertCallback(g_pluginHandle, PRKFSerialization::RevertCallback);
		g_serialization->SetLoadCallback(g_pluginHandle, PRKFSerialization::LoadCallback);
		g_serialization->SetSaveCallback(g_pluginHandle, PRKFSerialization::SaveCallback);
		InitExeAddress();
		InitUIManager();
		InitAddresses();
		LevelIncrease__Event_Dispatcher_Init();
		RVAManager::UpdateAddresses(f4se->runtimeVersion);
		g_messaging->RegisterListener(g_pluginHandle, "F4SE", OnF4SEMessage);
		g_messaging->RegisterListener(g_pluginHandle, nullptr, PRKFMessageHandler);
		if (g_papyrus)
		{
			g_papyrus->Register(RegisterFuncs);
			_MESSAGE("Papyrus Register Succeeded");
		}
		if (g_scaleform)
		{
			g_scaleform->Register("PRKF", RegisterScaleform);
			_MESSAGE("Scaleform Register Succeeded");
		}

		if (!g_branchTrampoline.Create(1024 * 64))
		{
			_ERROR("couldn't create branch trampoline. this is fatal. skipping remainder of init process.");
			return false;
		}

		if (!g_localTrampoline.Create(1024 * 64, nullptr))
		{
			_ERROR("couldn't create codegen buffer. this is fatal. skipping remainder of init process.");
			return false;
		}
		{
			struct SetPerkPoints_int_Code : Xbyak::CodeGenerator {
				SetPerkPoints_int_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					sub(rsp, 0x28);
					mov(ptr[rcx + 0xCF1], dl);
					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(SetPerkPoints_int.GetUIntPtr() + 10);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			SetPerkPoints_int_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			SetPerkPoints_int_Original = (_SetPerkPoints_int)codeBuf;

			g_branchTrampoline.Write6Branch(SetPerkPoints_int.GetUIntPtr(), (uintptr_t)SetPerkPoints_int_Hook);
		}
		{
			struct LevelupMenuProcessMessage_Code : Xbyak::CodeGenerator {
				LevelupMenuProcessMessage_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(ptr[rsp + 8], rbx);
					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(LevelupMenuProcessMessage.GetUIntPtr() + 5);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			LevelupMenuProcessMessage_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			LevelupMenuProcessMessage_Original = (_LevelupMenuProcessMessage)codeBuf;

			g_branchTrampoline.Write5Branch(LevelupMenuProcessMessage.GetUIntPtr(), (uintptr_t)LevelupMenuProcessMessage_Hook);
		}
		return true;
	}

};
