#include "SharedClasses_Pipboy.h"
#include "Relocation/RVA.h"

RelocPtr <PipboyDataManager*> g_PipboyDataManager(0x0); // 0x58D0AF0 1.10.130

void SharedClasses_PipboyObjectInit()
{
	RELOC_MEMBER_FN(PipboyObject, Construct, "41 55 41 56 41 57 48 83 EC 20 48 8B F9 48 89 0D", 26, 1, 5); // 0x00C311B0 1.10.130
	RELOC_MEMBER_FN(PipboyObject, SetMember, "4C 89 44 24 18 53 55 56 57 41 55 41 56 41 57 48 83 EC 30"); // 0x00C31940 1.10.130
	RELOC_MEMBER_FN(PipboyObject, SetMember_BSFixedStringCS, "E8 ? ? ? ? 48 8D 4C 24 68 E8 ? ? ? ? 83 3D", 0, 1, 5); // 0x00C15580 1.10.130
	RELOC_MEMBER_FN(PipboyObject, SetMember_int, "E8 ? ? ? ? 49 8B 0E 49 8B D5 E8", 0, 1, 5, { { -160, 0, 0 } }); // 0x00C15390 1.10.130
	RELOC_MEMBER_FN(PipboyObject, SetMember_uint, "E8 ? ? ? ? 49 8B 0E 49 8B D5 E8", 0, 1, 5); // 0x00C15430 1.10.130
	RELOC_MEMBER_FN(PipboyObject, SetMember_float, "E8 ? ? ? ? 33 F6 49 8B 45 00", 0, 1, 5); // 0x00C154D0 1.10.130
	RELOC_MEMBER_FN(PipboyObject, SetMember_bool, "E8 ? ? ? ? 48 8B 5D FF 4C 8B 7C 24 70", 0, 1, 5); // 0x00C15640 1.10.130
}

void SharedClasses_PipboyArrayInit()
{
	RELOC_MEMBER_FN(PipboyArray, Construct, "E8 ? ? ? ? 48 8B D8 EB ? 33 DB 48 8D 54 24 48", 0, 1, 5); // 0x00C04040 1.10.130
	RELOC_MEMBER_FN(PipboyArray, PushBack, "48 89 5C 24 10 48 89 6C 24 20 56 57 41 55 41 56 41 57 48 83 EC 30"); // 0x00C044A0 1.10.130
	RELOC_MEMBER_FN(PipboyArray, Insert, "48 89 5C 24 10 48 89 6C 24 18 56 57 41 55 41 56 41 57 48 83 EC 40 44 8B 49 20"); // 0x00C04660 1.10.130
	RELOC_MEMBER_FN(PipboyArray, PushBack_Object, "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 49 8B C8 48 8B F2 ", 21, 1, 5); // 0x00C151D0 1.10.130	


}

void SharedClasses_PipboyInit()
{
	RELOC_GLOBAL_VAL(g_PipboyDataManager, "48 8B 0D ? ? ? ? 48 8D 44 24 48 48 8D 54 24 20 48 89 44 24 20 48 8D 44 24 50 48 81 C1 E8 08 00 00", 0, 3, 7); // 0x058D0AF0 1.10.130

	SharedClasses_PipboyObjectInit();
	SharedClasses_PipboyArrayInit();
}




void tracePipboyPrimitiveValueInt(PipboyPrimitiveValue<SInt32>* val)
{
	_MESSAGE("type:     int\t\tvalue: %16i\t\thex: 0x%016I64X", val->value, val->value);
};

void tracePipboyPrimitiveValueUInt(PipboyPrimitiveValue<UInt32>* val)
{
	_MESSAGE("type:    uint\t\tvalue: %16u\t\thex: 0x%016I64X", val->value, val->value);
};

void tracePipboyPrimitiveValueUChar(PipboyPrimitiveValue<UInt8>* val)
{
	_MESSAGE("type:    uchar\t\tvalue: %16u\t\thex: 0x%016I64X", val->value, val->value);
};

void tracePipboyPrimitiveValueFloat(PipboyPrimitiveValue<float>* val)
{
	_MESSAGE("type:   float\t\tvalue: %16f\t\thex: 0x%016I64X", val->value, val->value);
};

void tracePipboyPrimitiveValueBool(PipboyPrimitiveValue<bool>* val)
{
	_MESSAGE("type:    bool\t\tvalue: %16s", val->value ? "true" : "false");
};

void tracePipboyPrimitiveValueBSFixedStringCS(PipboyPrimitiveValue<BSFixedString>* val)
{
	_MESSAGE("type:  string\t\tvalue: %16s", val->value.c_str());
};

void tracePipboyPrimitiveThrottledValueFloat(PipboyPrimitiveThrottledValue<float>* val)
{
	_MESSAGE("type:   float\t\tvalue: %16f\t\thex: 0x%016I64X", val->value, val->value);
	//DumpClass(val, 0x70 / 8);
};

void tracePipboyPrimitiveThrottledValueBool(PipboyPrimitiveThrottledValue<bool>* val)
{
	_MESSAGE("type:    bool\t\tvalue: %16s", val->value ? "true" : "false");
	//DumpClass(val, 0x70/8);
};

void tracePipboyPrimitiveThrottledValueUChar(PipboyPrimitiveThrottledValue<UInt8>* val)
{
	_MESSAGE("type:    uchar\t\tvalue: %16u\t\thex: 0x%016I64X", val->value, val->value);
	//DumpClass(val, 0x70 / 8);
};

void tracePipboyValue(PipboyValue* pv)
{
	_MESSAGE("%s",GetObjectClassName(pv));
	UInt64 vtbladdress = *reinterpret_cast<UInt64*>((uintptr_t)pv) - RelocationManager::s_baseAddr;
	//_MESSAGE("%s 0x%016I64X", GetObjectClassName(pv), vtbladdress);
	switch (vtbladdress)
	{
	case 0x2D2A550:	// BSFixedStringCS
		tracePipboyPrimitiveValueBSFixedStringCS((PipboyPrimitiveValue<BSFixedString>*)pv);
		break;
	case 0x2D2A5F8:	// uint
		tracePipboyPrimitiveValueUInt((PipboyPrimitiveValue<UInt32>*)pv);
		break;
	case 0x2D2B5C0:	// uchar
		tracePipboyPrimitiveValueUChar((PipboyPrimitiveValue<UInt8>*)pv);
		break;
	case 0x2D2B928:	// Throttled uchar
		tracePipboyPrimitiveThrottledValueUChar((PipboyPrimitiveThrottledValue<UInt8>*)pv);
		break;
	case 0x2D2A588:	// bool
		tracePipboyPrimitiveValueBool((PipboyPrimitiveValue<bool>*)pv);
		break;
	case 0x2D2B970:	// Throttled bool
		tracePipboyPrimitiveThrottledValueBool((PipboyPrimitiveThrottledValue<bool>*)pv);
		break;
	case 0x2D2A5C0:	// int
		tracePipboyPrimitiveValueInt((PipboyPrimitiveValue<SInt32>*)pv);
		break;
	case 0x2D2A630:	// float
		tracePipboyPrimitiveValueFloat((PipboyPrimitiveValue<float>*)pv);
		break;
	case 0x2D2B8E0:	// Throttled float
		tracePipboyPrimitiveThrottledValueFloat((PipboyPrimitiveThrottledValue<float>*)pv);
		break;
	case 0x2D29F78:	// PipboyArray
		tracePipboyArray((PipboyArray*)pv);
		break;
	case 0x2D2BB08:	// PipboyObject
		tracePipboyObject((PipboyObject*)pv);
		break;
	default:
		break;
	}
};

void tracePipboyArray(PipboyArray* arr)
{
	_MESSAGE("type:  array\t\titem count:%i", arr->value.count);
	//DumpClass(arr->value.entries, arr->value.count);
	gLog.Indent();
	for (size_t i = 0; i < arr->value.count; i++)
	{
		tracePipboyValue(arr->value[i]);
	};
	gLog.Outdent();
};

void tracePipboyObject(PipboyObject* obj)
{
	_MESSAGE("type:  object");
	gLog.Indent();
	obj->table.ForEach([](PipboyObject::PipboyTableItem* ti) {
		_MESSAGE("key: %s", ti->key.c_str());
		tracePipboyValue(ti->value);
		return true;
	}
	);
	gLog.Outdent();
};

void tracePipboyObjectLight(PipboyObject* obj)
{
	_MESSAGE("type:  object");
	gLog.Indent();
	obj->table.ForEach([](PipboyObject::PipboyTableItem* ti) {
		_MESSAGE("key: %s, value type %s", ti->key.c_str(), GetObjectClassName(ti->value));
		
		return true;
	}
	);
	gLog.Outdent();
};

PipboyObject* CreatePipboyObject(PipboyValue* parent)
{
	PipboyObject* po = (PipboyObject*)Heap_Allocate(sizeof(PipboyObject));
	memset(po, 0, sizeof(PipboyObject));
	return CALL_MEMBER_FN(po, Construct)(nullptr);
};

PipboyArray* CreatePipboyArray(PipboyValue* parent)
{
	PipboyArray* po = (PipboyArray*)Heap_Allocate(sizeof(PipboyArray));
	memset(po, 0, sizeof(PipboyArray));
	return CALL_MEMBER_FN(po, Construct)(nullptr);
};