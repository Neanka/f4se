
#include "main.h"
#include "PBTSerialization.h"

#define CURRENT_INI_VERSION 2

std::string mName = "PipboyTabs";
UInt32 mVer = 1;

std::vector<ActorValueInfo*> Skills;
struct avifStruct
{
	int type;
	int ShowListOnly;
	std::string id;
	std::string name;
	int	page;
	std::vector<TESForm*> list;
	std::vector<TESForm*> list2;
	std::vector<std::string> stringList;
	std::vector<TESForm*> filters;
	std::vector<float> maxValues;
	int precision;
};
std::vector<avifStruct> avifsPages;



PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;
F4SEPapyrusInterface		*g_papyrus = NULL;
F4SEScaleformInterface		*g_scaleform = NULL;
F4SEMessagingInterface		*g_messaging = NULL;
F4SESerializationInterface	*g_serialization = NULL;


void UpdateMenu_int(GFxMovieRoot* root)
{
	_DMESSAGE("ready callback");
	if (Skills.size() > 0)
	{
		GFxValue arrArgs[7];
		root->CreateString(&arrArgs[0], "skills");
		root->CreateString(&arrArgs[1], "$PBT_SKILLS");
		arrArgs[2].SetInt(0);
		arrArgs[3].SetInt(0);
		root->CreateObject(&arrArgs[4]);
		GFxValue skarray;
		root->CreateArray(&skarray);
		std::vector<std::string> strarr;
		for (int j = 0; j < Skills.size(); j++)
		{
			ActorValueInfo * baseSkill = Skills[j];
			PopulateSkillEntry(&skarray, root, baseSkill, 1, strarr);
		}
		arrArgs[4].SetMember("skillsList", &skarray);
		arrArgs[5].SetInt(0);
		arrArgs[6].SetInt(0);
		root->Invoke("root.PipboyTabs_loader.content.registerTab", nullptr, arrArgs, 7);
	}
	for (auto f : avifsPages)
	{
		_MESSAGE("fill pages");
		GFxValue arrArgs[7];
		root->CreateString(&arrArgs[0], f.id.c_str());
		root->CreateString(&arrArgs[1], f.name.c_str());
		arrArgs[2].SetInt(f.page);
		arrArgs[3].SetInt(f.type);
		root->CreateObject(&arrArgs[4]);

		GFxValue skarray;
		root->CreateArray(&skarray);
		for (int j = 0; j < f.list.size(); j++)
		{
			TESForm * baseSkill = f.list[j];

			int filterVal = 1;
			if (f.filters.size() > j)
			{

				TESForm * form = f.filters[j];
				if (form->formType == kFormType_GLOB)
				{
					TESGlobal* glob = DYNAMIC_CAST(form, TESForm, TESGlobal);
					filterVal = (int)glob->value;
				}
				else if(form->formType == kFormType_AVIF)
				{
					ActorValueInfo* avif = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
					filterVal = (int)GetBaseAV(avif, (*g_player));
				}
			}
			float maxVal = 0.0;
			if (f.maxValues.size() > j)
			{
				maxVal = f.maxValues[j];
			}
			else
			{
				maxVal = f.maxValues[0];
			}
			if (f.list2.size() > j)
			{
				Populate_entry(&skarray, root, baseSkill, f.list2[j], filterVal, f.stringList, maxVal);
			}
			else
			{
				Populate_entry(&skarray, root, baseSkill, nullptr, filterVal, f.stringList, maxVal);
			}
			/*
			switch (baseSkill->formType)
			{
			case 11: // GLOB
				if (f.list2.size() > j)
				{
					Populate_GLOB_FORM_Pair(&skarray, root, DYNAMIC_CAST(baseSkill, TESForm, TESGlobal), f.list2[j], filterVal, f.stringList);
				}
				else
				{
					Populate_GLOB_FORM_Pair(&skarray, root, DYNAMIC_CAST(baseSkill, TESForm, TESGlobal), nullptr, filterVal, f.stringList);
				}
				break;
			case 98: // AVIF
				PopulateSkillEntry(&skarray, root, DYNAMIC_CAST(baseSkill, TESForm, ActorValueInfo), filterVal, f.stringList);
				break;
			case 108: // MESG
				if (f.list2.size() > j)
				{
					Populate_MESG_FORM_Pair(&skarray, root, DYNAMIC_CAST(baseSkill, TESForm, BGSMessage), f.list2[j], filterVal, f.stringList);
				}
				else
				{
					Populate_MESG_FORM_Pair(&skarray, root, DYNAMIC_CAST(baseSkill, TESForm, BGSMessage), nullptr, filterVal, f.stringList);
				}
				break;
			case 30: // BOOK
				if (f.list2.size() > j)
				{
					Populate_BOOK_FORM_Pair(&skarray, root, DYNAMIC_CAST(baseSkill, TESForm, TESObjectBOOK), f.list2[j], filterVal, f.stringList);
				}
				else
				{
					Populate_BOOK_FORM_Pair(&skarray, root, DYNAMIC_CAST(baseSkill, TESForm, TESObjectBOOK), nullptr, filterVal, f.stringList);
				}
				break;
			default:
				break;
			}

			;
			*/
		}
		arrArgs[4].SetMember("skillsList", &skarray);

		GFxValue charArray;
		root->CreateArray(&charArray);
		for (int j = 0; j < f.stringList.size(); j++)
		{
			GFxValue strValue;
			//_MESSAGE("%s", f.stringList[j].c_str());
			root->CreateString(&strValue, f.stringList[j].c_str());
			charArray.PushBack(&strValue);
		}
		arrArgs[4].SetMember("StringArray", &charArray);
		arrArgs[5].SetInt(f.ShowListOnly);
		arrArgs[6].SetInt(f.precision);
		root->Invoke("root.PipboyTabs_loader.content.registerTab", nullptr, arrArgs, 7);
	}
}


void Populate_entry(GFxValue * dst, GFxMovieRoot * root, TESForm* form1, TESForm* form2, int filter, std::vector<std::string> stringValue, float maxVal)
{
	GFxValue arrArg;
	root->CreateObject(&arrArg);
	float value = 0;
	float buffedValue = 0;
	switch (form1->formType)
	{
	case kFormType_AVIF:
		value = GetBaseAV(static_cast<ActorValueInfo*>(form1), (*g_player));
		buffedValue = GetFullAV(static_cast<ActorValueInfo*>(form1), (*g_player));
		break;
	case kFormType_GLOB:
		value = static_cast<TESGlobal*>(form1)->value;
		buffedValue = value;
		break;
	default:
		break;
	}
	std::string name = "";
	TESFullName* fullname = DYNAMIC_CAST(form1, TESForm, TESFullName);
	if (fullname)
	{
		name = fullname->name;
	}
	std::string desc = "";
	TESDescription * pDescription = DYNAMIC_CAST(form1, TESForm, TESDescription);
	if (pDescription) {
		BSString str;
		CALL_MEMBER_FN(pDescription, Get)(&str, nullptr);
		desc = str.Get();
	}
	if (form2)
	{
		fullname = DYNAMIC_CAST(form2, TESForm, TESFullName);
		if (fullname)
		{
			std::string tempname = fullname->name;
			if (tempname.length() > 0)
			{
				name = tempname;
			}
		}
		pDescription = DYNAMIC_CAST(form2, TESForm, TESDescription);
		if (pDescription) {
			BSString str;
			CALL_MEMBER_FN(pDescription, Get)(&str, nullptr);
			desc = str.Get();
			std::string tempdesc = str.Get();
			if (tempdesc.length() > 0)
			{
				desc = tempdesc;
			}
		}
	}

	RegisterBool(&arrArg, "readed", PBTSerialization::CheckRN(form1->formID));
	if (name.length() > 0)
	{
		RegisterString(&arrArg, root, "text", name.c_str());
	}
	else
	{
		RegisterString(&arrArg, root, "text", form1->GetEditorID());
	}
	RegisterString(&arrArg, root, "qname", form1->GetEditorID());
	RegisterString(&arrArg, root, "description", desc.c_str());
	if (stringValue.size() > (int)value)
	{
		RegisterString(&arrArg, root, "stringValue", stringValue[(int)value].c_str());
	}
	else
	{
		RegisterString(&arrArg, root, "stringValue", "");
	}
	RegisterInt(&arrArg, "formid", form1->formID);

	RegisterNumber(&arrArg, "value", buffedValue);
	RegisterNumber(&arrArg, "maxVal", maxVal);
	RegisterNumber(&arrArg, "basevalue", value);
	RegisterNumber(&arrArg, "modifier", buffedValue - value);
	RegisterNumber(&arrArg, "buffedvalue", buffedValue);

	RegisterInt(&arrArg, "filterFlag", filter);

	dst->PushBack(&arrArg);

}
/*
void Populate_GLOB_FORM_Pair(GFxValue * dst, GFxMovieRoot * root, TESGlobal* glob, TESForm* form, int filter, std::vector<std::string> stringValue)
{
	GFxValue arrArg;
	root->CreateObject(&arrArg);
	float value = glob->value;
	if (form)
	{
		switch (form->formType)
		{
		case 98:
			RegisterString(&arrArg, root, "text", static_cast<ActorValueInfo*>(form)->fullName.name);
			RegisterString(&arrArg, root, "description", GetDescription(static_cast<ActorValueInfo*>(form)).c_str());
			break;
		case 108:
			RegisterString(&arrArg, root, "text", static_cast<BGSMessage*>(form)->fullName.name);
			RegisterString(&arrArg, root, "description", GetDescription(static_cast<BGSMessage*>(form)).c_str());
			break;
		case 30:
			RegisterString(&arrArg, root, "text", static_cast<TESObjectBOOK*>(form)->fullName.name);
			RegisterString(&arrArg, root, "description", GetDescription(static_cast<TESObjectBOOK*>(form)).c_str());
			break;
		default:
			break;
		}
	}
	else
	{
		RegisterString(&arrArg, root, "text", glob->editorID);
		RegisterString(&arrArg, root, "description", "");
	}
	
	RegisterBool(&arrArg, "readed", PBTSerialization::CheckRN(glob->formID));
	RegisterString(&arrArg, root, "qname", glob->editorID);
	if (stringValue.size() > (int)value)
	{
		RegisterString(&arrArg, root, "stringValue", stringValue[(int)value].c_str());
	}
	else
	{
		RegisterString(&arrArg, root, "stringValue", "");
	}


	RegisterInt(&arrArg, "formid", glob->formID);
	RegisterNumber(&arrArg, "value", value);
	RegisterNumber(&arrArg, "basevalue", value);
	RegisterNumber(&arrArg, "modifier", 0);
	RegisterNumber(&arrArg, "buffedvalue", value);
	RegisterInt(&arrArg, "filterFlag", filter);
	dst->PushBack(&arrArg);
	//_DMESSAGE("EdID: %s, FormID: %i, value: %i, description %s", baseSkill->avName, baseSkill->formID, (int)value, GetDescription(baseSkill).c_str());
}

void Populate_MESG_FORM_Pair(GFxValue * dst, GFxMovieRoot * root, BGSMessage* msg, TESForm* form, int filter, std::vector<std::string> stringValue)
{
	GFxValue arrArg;
	root->CreateObject(&arrArg);
	float value = 0;
	float buffedValue = 0;
	if (form)
	{
		switch (form->formType)
		{
		case 98: // AVIF
			value = GetBaseAV(static_cast<ActorValueInfo*>(form), (*g_player));
			buffedValue = GetFullAV(static_cast<ActorValueInfo*>(form), (*g_player));
			break;
		case 11: // GLOB
			value = static_cast<TESGlobal*>(form)->value;
			buffedValue = value;
			break;
		default:
			break;
		}
	}

	RegisterBool(&arrArg, "readed", PBTSerialization::CheckRN(msg->formID));
	RegisterString(&arrArg, root, "text", msg->fullName.name);
	RegisterString(&arrArg, root, "qname", msg->GetEditorID());
	RegisterString(&arrArg, root, "description", GetDescription(msg).c_str());
	if (stringValue.size() > (int)value)
	{
		RegisterString(&arrArg, root, "stringValue", stringValue[(int)value].c_str());
	}
	else
	{
		RegisterString(&arrArg, root, "stringValue", "");
	}
	RegisterInt(&arrArg, "formid", msg->formID);

	RegisterNumber(&arrArg, "value", buffedValue);
	RegisterNumber(&arrArg, "basevalue", value);
	RegisterNumber(&arrArg, "modifier", buffedValue - value);
	RegisterNumber(&arrArg, "buffedvalue", buffedValue);

	RegisterInt(&arrArg, "filterFlag", filter);

	dst->PushBack(&arrArg);
	//_DMESSAGE("EdID: %s, FormID: %i, value: %i, description %s", baseSkill->avName, baseSkill->formID, (int)value, GetDescription(baseSkill).c_str());
}

void Populate_BOOK_FORM_Pair(GFxValue * dst, GFxMovieRoot * root, TESObjectBOOK* book, TESForm* form, int filter, std::vector<std::string> stringValue)
{
	GFxValue arrArg;
	root->CreateObject(&arrArg);
	float value = 0;
	float buffedValue = 0;
	if (form)
	{
		switch (form->formType)
		{
		case 98: // AVIF
			value = GetBaseAV(static_cast<ActorValueInfo*>(form), (*g_player));
			buffedValue = GetFullAV(static_cast<ActorValueInfo*>(form), (*g_player));
			break;
		case 11: // GLOB
			value = static_cast<TESGlobal*>(form)->value;
			buffedValue = value;
			break;
		default:
			break;
		}
	}

	RegisterBool(&arrArg, "readed", PBTSerialization::CheckRN(book->formID));
	RegisterString(&arrArg, root, "text", book->fullName.name);
	RegisterString(&arrArg, root, "qname", book->GetEditorID());
	RegisterString(&arrArg, root, "description", GetDescription(book).c_str());
	if (stringValue.size() > (int)value)
	{
		RegisterString(&arrArg, root, "stringValue", stringValue[(int)value].c_str());
	}
	else
	{
		RegisterString(&arrArg, root, "stringValue", "");
	}
	RegisterInt(&arrArg, "formid", book->formID);

	RegisterNumber(&arrArg, "value", buffedValue);
	RegisterNumber(&arrArg, "basevalue", value);
	RegisterNumber(&arrArg, "modifier", buffedValue - value);
	RegisterNumber(&arrArg, "buffedvalue", buffedValue);

	RegisterInt(&arrArg, "filterFlag", filter);

	dst->PushBack(&arrArg);
	//_DMESSAGE("EdID: %s, FormID: %i, value: %i, description %s", baseSkill->avName, baseSkill->formID, (int)value, GetDescription(baseSkill).c_str());
}
*/
void PopulateSkillEntry(GFxValue * dst, GFxMovieRoot * root, ActorValueInfo * baseSkill, int filter, std::vector<std::string> stringValue)
{
	GFxValue arrArg;
	root->CreateObject(&arrArg);
	float value = GetBaseAV(baseSkill, (*g_player));
	float buffedValue = GetFullAV(baseSkill, (*g_player));
	RegisterString(&arrArg, root, "text", baseSkill->fullName.name);
	RegisterString(&arrArg, root, "qname", baseSkill->GetEditorID());
	RegisterString(&arrArg, root, "description", GetDescription(baseSkill).c_str());
	if (stringValue.size() > (int)value)
	{
		RegisterString(&arrArg, root, "stringValue", stringValue[(int)value].c_str());
	}
	else
	{
		RegisterString(&arrArg, root, "stringValue", "");
	}
	PRKFIsTaggedMessage message;
	message.formid = baseSkill->formID;
	g_messaging->Dispatch(g_pluginHandle, PRKFIsTaggedMessage::kMessage_PRKFIsTagged, (void*)&message, sizeof(PRKFIsTaggedMessage*), "PRKF");
	if (message.tagged)
	{
		filter |= 2;
	}
	RegisterBool(&arrArg, "readed", PBTSerialization::CheckRN(baseSkill->formID));
	RegisterInt(&arrArg, "formid", baseSkill->formID);
	RegisterNumber(&arrArg, "value", buffedValue);
	RegisterNumber(&arrArg, "maxVal", 0.0);
	RegisterNumber(&arrArg, "basevalue", value);
	RegisterNumber(&arrArg, "modifier", buffedValue - value);
	RegisterNumber(&arrArg, "buffedvalue", buffedValue);
	RegisterInt(&arrArg, "filterFlag", filter);
	dst->PushBack(&arrArg);
	//_DMESSAGE("EdID: %s, FormID: %i, value: %i, description %s", baseSkill->avName, baseSkill->formID, (int)value, GetDescription(baseSkill).c_str());
}

#include "f4se/ScaleformLoader.h"
#include "PBTTranslator.h"

void ReadINIs(std::vector<WIN32_FIND_DATA>* arr, char* modSettingsDirectory)
{
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

void OnF4SEMessage(F4SEMessagingInterface::Message* msg) {
	switch (msg->type) {
	case F4SEMessagingInterface::kMessage_GameDataReady:
		CheckArchiveInvalidation(mName);
		avifsPages.clear();
		Skills.clear();
		fillSkills();
		fillAvifsPages();
		break;
	case F4SEMessagingInterface::kMessage_GameLoaded:

		// Inject translations
		BSScaleformTranslator * translator = (BSScaleformTranslator*)(*g_scaleformManager)->stateBag->GetStateAddRef(GFxState::kInterface_Translator);
		if (translator) {
			PBTTranslator::LoadTranslations(translator);
		}
		break;
	}
}

void fillSkills()
{
	std::vector<WIN32_FIND_DATA> modSettingFiles;
	ReadINIs(&modSettingFiles, "Data\\PRKF\\*.ini");
	for (int i = 0; i < modSettingFiles.size(); i++) {
		_MESSAGE("ini: %s", modSettingFiles[i].cFileName);

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
				Skills.push_back(baseSkill);
			}
		}
		else
		{
			_DMESSAGE("SkillsList is empty");
			continue;
		}
	}
	_MESSAGE("total skills count: %i", Skills.size());
}



void fillAvifsPages()
{
	std::vector<WIN32_FIND_DATA> modSettingFiles;
	ReadINIs(&modSettingFiles, "Data\\PBT\\*.ini");
	int disableVanillaPerks = 0;
	Setting	* setting = GetINISetting("sLanguage:General");
	for (int i = 0; i < modSettingFiles.size(); i++) {
		_MESSAGE("ini: %s", modSettingFiles[i].cFileName);
		_MESSAGE("ini version: %i", PBT_GetConfigOptionInt(modSettingFiles[i].cFileName, "Main", "INIVersion"));
		avifStruct str;
		if (PBT_GetConfigOptionInt(modSettingFiles[i].cFileName, "Main", "INIVersion") != CURRENT_INI_VERSION)
		{
			_MESSAGE("wrong ini version");
			continue;
		} 
		str.type = PBT_GetConfigOptionInt(modSettingFiles[i].cFileName, "Main", "TabType");
		str.id = PBT_GetConfigOptionString(modSettingFiles[i].cFileName, "Main", "UniqueID");
		str.name = PBT_GetConfigOptionString(modSettingFiles[i].cFileName, "Main", "TabName");

		std::string TabNameLoc = PBT_GetConfigOptionString(modSettingFiles[i].cFileName, "Main", "TabName_" + std::string(setting->data.s));
		_MESSAGE("TabName %s", str.name.c_str());
		if (TabNameLoc.size() > 0)
		{
			_MESSAGE("TabNameLoc %s", TabNameLoc.c_str());
			str.name = TabNameLoc;
		}

		str.page = PBT_GetConfigOptionInt(modSettingFiles[i].cFileName, "Main", "PageNumberToInsert");
		_MESSAGE("type %i", str.type);
		_MESSAGE("id %s", str.id.c_str());
		_MESSAGE("name %s", str.name.c_str());
		_MESSAGE("page %i", str.page);
		str.ShowListOnly = PBT_GetConfigOptionInt(modSettingFiles[i].cFileName, "Main", "ShowListOnly");
		_MESSAGE("ShowListOnly %i", str.ShowListOnly);

		str.precision = PBT_GetConfigOptionInt(modSettingFiles[i].cFileName, "Main", "Precision");
		_MESSAGE("Precision %i", str.precision);

		std::vector<TESForm*> arr;

		std::string FirstList = PBT_GetConfigOptionString(modSettingFiles[i].cFileName, "Main", "FirstList");
		_MESSAGE("FirstList %s", FirstList.c_str());
		if (FirstList.size() > 0)
		{
			auto _FirstList = DYNAMIC_CAST(GetFormFromIdentifier(FirstList), TESForm, BGSListForm);
			if (_FirstList == nullptr) {
				_DMESSAGE("FirstList form is not BGSListForm");
				continue;
			}
			_DMESSAGE("form count %i", _FirstList->forms.count);
			for (int j = 0; j < _FirstList->forms.count; j++)
			{
				TESForm * baseForm = _FirstList->forms.entries[j]; //GLOB or AVIF or MESG
				//if (baseForm->formType == 11 || baseForm->formType == 98 || baseForm->formType == 108 || baseForm->formType == 30)
				//{
					arr.push_back(baseForm);
				//}
				//else
				//{
			//		_DMESSAGE("entry is not GLOB or AVIF: %s", baseForm->GetFullName());
			//	}
			}
		}
		else
		{
			_DMESSAGE("FirstList is empty");
			continue;
		}
		str.list = arr;




		std::vector<TESForm*> arr2;

		std::string SecondList = PBT_GetConfigOptionString(modSettingFiles[i].cFileName, "Main", "SecondList");
		_MESSAGE("SecondList %s", SecondList.c_str());
		if (SecondList.size() > 0)
		{
			auto _SecondList = DYNAMIC_CAST(GetFormFromIdentifier(SecondList), TESForm, BGSListForm);
			if (_SecondList == nullptr) {
				_DMESSAGE("SecondList form is not BGSListForm");
			}
			else
			{
				_DMESSAGE("form count %i", _SecondList->forms.count);
				for (int j = 0; j < _SecondList->forms.count; j++)
				{
					TESForm * baseForm = _SecondList->forms.entries[j]; //GLOB or AVIF or MESG
					//if (baseForm->formType == 11 || baseForm->formType == 98 || baseForm->formType == 108)
					//{
						arr2.push_back(baseForm);
					//}
					//else
					//{
					//	_DMESSAGE("entry is not GLOB or AVIF or MESG: %s", baseForm->GetFullName());
					//}
				}
			}
		}
		else
		{
			_DMESSAGE("SecondList is empty");
		}
		str.list2 = arr2;





		std::vector<std::string> charArr;
		std::string StringArray = PBT_GetConfigOptionString(modSettingFiles[i].cFileName, "Main", "StringArray");

		std::string StringArrayLoc = PBT_GetConfigOptionString(modSettingFiles[i].cFileName, "Main", "StringArray_"+ std::string(setting->data.s));
		_MESSAGE("StringArray %s", StringArray.c_str());
		if (StringArrayLoc.size() > 0)
		{
			_MESSAGE("StringArrayLoc %s", StringArrayLoc.c_str());
			StringArray = StringArrayLoc;
		}

		if (StringArray.size() > 0)
		{
			std::size_t found = 0;
			std::size_t found2 = StringArray.find("|");
			std::string tempstring = StringArray.substr(found, found2 - found);
			charArr.push_back(tempstring);
			while (found2 < StringArray.size() - 1)
			{
				found = found2 + 1;
				found2 = StringArray.find("|", found);
				tempstring = StringArray.substr(found, found2 - found);
				charArr.push_back(tempstring);
			}
		}
		str.stringList = charArr;

		std::vector<float> maxValuesArr;
		std::string maxValuesArray = PBT_GetConfigOptionString(modSettingFiles[i].cFileName, "Main", "MaxValueList");
		_MESSAGE("maxValuesArray %s", maxValuesArray.c_str());
		if (maxValuesArray.size() > 0)
		{
			std::size_t found = 0;
			std::size_t found2 = maxValuesArray.find("|");
			std::string tempstring = maxValuesArray.substr(found, found2 - found);
			maxValuesArr.push_back(std::stof(tempstring));
			while (found2 < maxValuesArray.size() - 1)
			{
				found = found2 + 1;
				found2 = maxValuesArray.find("|", found);
				tempstring = maxValuesArray.substr(found, found2 - found);
				maxValuesArr.push_back(std::stof(tempstring));
			}

		}
		else
		{
			maxValuesArr.push_back(0.0);
		}
		str.maxValues = maxValuesArr;

		std::vector<TESForm*> filterArr;
		std::string FilterList = PBT_GetConfigOptionString(modSettingFiles[i].cFileName, "Main", "FilterList");
		_MESSAGE("FilterList %s", FilterList.c_str());
		if (FilterList.size() > 0)
		{
			auto _FilterList = DYNAMIC_CAST(GetFormFromIdentifier(FilterList), TESForm, BGSListForm);
			if (_FilterList == nullptr) {
				_DMESSAGE("form is not BGSListForm");
			}
			else
			{
				_DMESSAGE("form count %i", _FilterList->forms.count);
				for (int j = 0; j < _FilterList->forms.count; j++)
				{
					TESForm * baseForm = _FilterList->forms.entries[j]; //GLOB or AVIF
					if (baseForm->formType == 11 || baseForm->formType == 98)
					{
						filterArr.push_back(baseForm);
					}
					else
					{
						_DMESSAGE("filter entry is not GLOB or AVIF: %s", baseForm->GetFullName());
					}
				}
			}
		}
		else
		{
			_DMESSAGE("AVIFsList is empty");
		}
		str.filters = filterArr;




		avifsPages.push_back(str);
	}
	_MESSAGE("total extra pages: %i", avifsPages.size());
}

class Scaleform_ready : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args) {
		UpdateMenu_int(args->movie->movieRoot);
	}
};

class Scaleform_AddReadedNote : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args) {
		PBTSerialization::AddRN(args->args[0].GetUInt());
	}
};

class Scaleform_RemoveReadedNote : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args) {
		PBTSerialization::RemoveRN(args->args[0].GetUInt());
	}
};

class Scaleform_IsReadedNote : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args) {
		args->result->SetBool(PBTSerialization::CheckRN(args->args[0].GetUInt()));
	}
};

bool RegisterScaleform(GFxMovieView * view, GFxValue * f4se_root)
{

	GFxMovieRoot	*movieRoot = view->movieRoot;

	GFxValue currentSWFPath;
	std::string currentSWFPathString = "";
	if (movieRoot->GetVariable(&currentSWFPath, "root.loaderInfo.url")) {
		currentSWFPathString = currentSWFPath.GetString();
		//_MESSAGE("hooking %s", currentSWFPathString.c_str());
		if (currentSWFPathString.find("PipboyMenu.swf") != std::string::npos)
		{
			_DMESSAGE("hooking pipboymenu");
			if (!movieRoot)
				return false;
			GFxValue loader, urlRequest, root;
			movieRoot->GetVariable(&root, "root");
			movieRoot->CreateObject(&loader, "flash.display.Loader");
			movieRoot->CreateObject(&urlRequest, "flash.net.URLRequest", &GFxValue("PipboyTabs.swf"), 1);
			root.SetMember("PipboyTabs_loader", &loader);
			GFxValue pbt; movieRoot->CreateObject(&pbt);
			root.SetMember("pbt", &pbt);
			RegisterFunction<Scaleform_ready>(&pbt, view->movieRoot, "ready");
			RegisterFunction<Scaleform_AddReadedNote>(&pbt, view->movieRoot, "AddReadedNote");
			RegisterFunction<Scaleform_RemoveReadedNote>(&pbt, view->movieRoot, "RemoveReadedNote");
			RegisterFunction<Scaleform_IsReadedNote>(&pbt, view->movieRoot, "IsReadedNote");
			//GFxValue codeObj;
			//movieRoot->GetVariable(&codeObj, "root.Menu_mc.BGSCodeObj");
			//if (!codeObj.IsUndefined()) {
			//	RegisterFunction<Scaleform_ready>(&codeObj, movieRoot, "ready");
			//}
			movieRoot->Invoke("root.PipboyTabs_loader.load", nullptr, &urlRequest, 1);
			movieRoot->Invoke("root.Menu_mc.addChild", nullptr, &loader, 1);

		}
	}
	return true;
}

#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"

bool UpdateMenu_pap()
{
	_DMESSAGE("update menu");
	IMenu * menu = (*g_ui)->GetMenu(BSFixedString("PipboyMenu"));
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
	UpdateMenu_int(root);
	return true;
}

bool UpdateMenu(StaticFunctionTag*)
{
	return UpdateMenu_pap();
}

void AddReadedNote(StaticFunctionTag*, BGSMessage* msg)
{
	PBTSerialization::AddRN(msg->formID);
}

void RemoveReadedNote(StaticFunctionTag*, BGSMessage* msg)
{
	PBTSerialization::RemoveRN(msg->formID);
}

bool IsReadedNote(StaticFunctionTag*, BGSMessage* msg)
{
	return PBTSerialization::CheckRN(msg->formID);
}

bool RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, bool>("UpdateMenu", "PBT:PBT", UpdateMenu, vm));
	vm->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, BGSMessage*>("AddReadedNoteMESG", "PBT:PBT", AddReadedNote, vm));
	vm->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, BGSMessage*>("RemoveReadedNoteMESG", "PBT:PBT", RemoveReadedNote, vm));
	vm->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, bool, BGSMessage*>("IsReadedNote", "PBT:PBT", IsReadedNote, vm));
	return true;
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
			return false;
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
		g_serialization->SetUniqueID(g_pluginHandle, 'PBT');
		g_serialization->SetRevertCallback(g_pluginHandle, PBTSerialization::RevertCallback);
		g_serialization->SetLoadCallback(g_pluginHandle, PBTSerialization::LoadCallback);
		g_serialization->SetSaveCallback(g_pluginHandle, PBTSerialization::SaveCallback);
		if (g_scaleform)
		{
			g_scaleform->Register("PipboyTabs", RegisterScaleform);
			_MESSAGE("Scaleform Register Succeeded");
		}
		g_messaging->RegisterListener(g_pluginHandle, "F4SE", OnF4SEMessage);
		if (g_papyrus)
		{
			g_papyrus->Register(RegisterFuncs);
			_MESSAGE("Papyrus Register Succeeded");
		}
		return true;
	}

};
