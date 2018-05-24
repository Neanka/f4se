#include "papfunctions.h"
#include "consts.h"

BSFixedString GetName(TESForm* thisForm)
{
	if (!thisForm)
		return BSFixedString();

	TESFullName* pFullName = DYNAMIC_CAST(thisForm, TESForm, TESFullName);
	if (pFullName)
		return pFullName->name;

	return BSFixedString();
}

BSFixedString GetDescription(TESForm * thisForm)
{
	if(!thisForm)
		return BSFixedString();

	TESDescription * pDescription = DYNAMIC_CAST(thisForm, TESForm, TESDescription);
	if(pDescription) {
		BSString str;
		CALL_MEMBER_FN(pDescription, Get)(&str, nullptr);
		return str.Get();
	}

	return BSFixedString();
}

UInt8 GetActorLevel(Actor * actor){
	float fexp = GetModAVValueByFormID(ExperienceID,actor);
	float flevel = (sqrt(pow(87.5,2)+4*37.5*(124+fexp))-87.5)/75;
	return floor(flevel+0.01);
}

ActorValueInfo * GetAVByFormID(int fromid) {
	TESForm * form = LookupFormByID(fromid);
	if(form && form->formType == ActorValueInfo::kTypeID){
		return (ActorValueInfo *)form;
	}	
	return nullptr;
}

BGSPerk * GetPerkByFormID(int fromid) {
	TESForm * form = LookupFormByID(fromid);
	if(form && form->formType == BGSPerk::kTypeID){
		return (BGSPerk *)form;
	}	
	return nullptr;
}

float GetBaseAV(ActorValueInfo * pAV,Actor * actor) {
	return actor->actorValueOwner.GetBase(pAV);
}

void ModBaseAV(ActorValueInfo * pAV,Actor * actor,int delta) {
	actor->actorValueOwner.ModBase(pAV,delta);
}

void ModAV(ActorValueInfo * pAV,Actor * actor,int delta){
	actor->actorValueOwner.Mod(0,pAV,delta);
}

float GetModAVValue(ActorValueInfo * pAV,Actor * actor) {
	return actor->actorValueOwner.GetMod(0,pAV);
}

float GetFullAV(ActorValueInfo * pAV,Actor * actor) {
	return actor->actorValueOwner.GetValue(pAV);
}

float GetAVValueByFormID(int fromid,Actor * actor) {
	float value = 0.0;
	TESForm * form = LookupFormByID(fromid);
	if(form && form->formType == ActorValueInfo::kTypeID){
		value = actor->actorValueOwner.GetBase((ActorValueInfo *)form);
	}
	return value;
}

void ModBaseAVByFormID(int fromid,Actor * actor,int delta) {
	TESForm * form = LookupFormByID(fromid);
	if(form && form->formType == ActorValueInfo::kTypeID){
		actor->actorValueOwner.ModBase((ActorValueInfo *)form,delta);
	}
}

void ModAVByFormID(int fromid,Actor * actor,int delta){
	TESForm * form = LookupFormByID(fromid);
	if(form && form->formType == ActorValueInfo::kTypeID){
		actor->actorValueOwner.Mod(0,(ActorValueInfo *)form,delta);
	}
}

void SetBaseAVByFormID(int fromid,Actor * actor,int value) {
	TESForm * form = LookupFormByID(fromid);
	if(form && form->formType == ActorValueInfo::kTypeID){
		actor->actorValueOwner.SetBase((ActorValueInfo *)form,value);
	}
}

float GetModAVValueByFormID(int fromid,Actor * actor) {
	float value = 0.0;
	TESForm * form = LookupFormByID(fromid);
	if(form && form->formType == ActorValueInfo::kTypeID){
		value = actor->actorValueOwner.GetMod(0,(ActorValueInfo *)form);
	}
	return value;
}

float GetFullAVValueByFormID(int fromid,Actor * actor) {
	float value = 0.0;
	TESForm * form = LookupFormByID(fromid);
	if(form && form->formType == ActorValueInfo::kTypeID){
		value = actor->actorValueOwner.GetValue((ActorValueInfo *)form);
	}
	return value;
}

TESForm * GetFormFromFile(UInt32 formID, const char * pluginName)
{
    auto mod = (*g_dataHandler)->LookupLoadedModByName(pluginName);
    if(!mod) // No loaded mod by this name
        return nullptr;

    formID |= ((UInt32)mod->modIndex) << 24;

    return LookupFormByID(formID);
}

UInt32 GetFormIDFromFile(UInt32 formID, const char * pluginName)
{
    auto mod = (*g_dataHandler)->LookupLoadedModByName(pluginName);
    if(!mod) // No loaded mod by this name
        return 0;

    formID |= ((UInt32)mod->modIndex) << 24;

    return formID;
}

TESForm * GetFormFromIdentifier(const std::string formIdentifier)
{
	std::size_t pos = formIdentifier.find_first_of('|');
	std::string modName = formIdentifier.substr(0, pos);
	std::string modForm = formIdentifier.substr(pos+1);

	auto mod = (*g_dataHandler)->LookupLoadedModByName(modName.c_str());
	if(!mod) // No loaded mod by this name
		return nullptr;

	UInt32 formId = 0;
	sscanf_s(modForm.c_str(), "%X", &formId);
	formId |= ((UInt32)mod->modIndex) << 24;

	return LookupFormByID(formId);
}

UInt32 GetFormIDFromIdentifier(const std::string formIdentifier)
{
	std::size_t pos = formIdentifier.find_first_of('|');
	std::string modName = formIdentifier.substr(0, pos);
	std::string modForm = formIdentifier.substr(pos+1);

	auto mod = (*g_dataHandler)->LookupLoadedModByName(modName.c_str());
	if(!mod) // No loaded mod by this name
		return 0;

	UInt32 formId = 0;
	sscanf_s(modForm.c_str(), "%X", &formId);
	formId |= ((UInt32)mod->modIndex) << 24;

	return formId;
}

std::string DEFGetConfigOption(const char * section, const char * key)
{
	std::string	result;

	const std::string & configPath = "./Data/F4SE/Plugins/def_plugin.ini";
	if(!configPath.empty())
	{
		char	resultBuf[256];
		resultBuf[0] = 0;

		UInt32	resultLen = GetPrivateProfileString(section, key, NULL, resultBuf, sizeof(resultBuf), configPath.c_str());

		result = resultBuf;
	}

	return result;
}

void TraceActorAvifs(Actor * actor) {
	tArray<Actor::ActorValueData> pcavifsarray = actor->actorValueData;
	_MESSAGE("===========BASE VALUES============");
	for (int j = 0; j < pcavifsarray.count; j++) {
		_MESSAGE("formid: %u, value: %f",pcavifsarray.entries[j].avFormID,pcavifsarray.entries[j].value);
	}
	_MESSAGE("==========MOD VALUES==============");
	tArray<Actor::Data350> pcavifsarray1 = actor->unk350;
	for (int j = 0; j < pcavifsarray1.count; j++) {
		_MESSAGE("formid: %u, value: %f %f %f",pcavifsarray1.entries[j].avFormID,pcavifsarray1.entries[j].unk04,pcavifsarray1.entries[j].unk08,pcavifsarray1.entries[j].unk0C);
	}
	_MESSAGE("==================================");
}

UInt8 GetActorSex(Actor * actor) {
	UInt8 gender = 0;
	TESNPC * actorBase = DYNAMIC_CAST(actor->baseForm, TESForm, TESNPC);
	if(actorBase) {
		gender = CALL_MEMBER_FN(actorBase, GetSex)();
	}
	return gender;
}

void papMessageBox(BSFixedString asMessageBoxText){
	CallGlobalFunctionNoWait1<BSFixedString>("Debug", "MessageBox", asMessageBoxText);
}

void papMessageBox(std::string asMessageBoxText){
	CallGlobalFunctionNoWait1<BSFixedString>("Debug", "MessageBox", BSFixedString(asMessageBoxText.c_str()));
}

void papMessageBox(const char* asMessageBoxText){
	CallGlobalFunctionNoWait1<BSFixedString>("Debug", "MessageBox", BSFixedString(asMessageBoxText));
}

void papNotification(BSFixedString asNotificationText){
	CallGlobalFunctionNoWait1<BSFixedString>("Debug", "Notification", asNotificationText);
}

void papNotification(std::string asNotificationText){
	CallGlobalFunctionNoWait1<BSFixedString>("Debug", "Notification", BSFixedString(asNotificationText.c_str()));
}

void papNotification(const char* asNotificationText){
	CallGlobalFunctionNoWait1<BSFixedString>("Debug", "Notification", BSFixedString(asNotificationText));
}

void papTrace(BSFixedString asTextToPrint, UInt32 aiSeverity = 0){
	CallGlobalFunctionNoWait2<BSFixedString, UInt32>("Debug", "Trace", asTextToPrint, aiSeverity);
}

void papTrace(std::string asTextToPrint, UInt32 aiSeverity = 0){
	CallGlobalFunctionNoWait2<BSFixedString, UInt32>("Debug", "Trace", BSFixedString(asTextToPrint.c_str()), aiSeverity);
}

void papTrace(const char* asTextToPrint, UInt32 aiSeverity = 0){
	CallGlobalFunctionNoWait2<BSFixedString, UInt32>("Debug", "Trace", BSFixedString(asTextToPrint), aiSeverity);
}