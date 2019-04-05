#pragma once

#define CURRENT_RUNTIME_VERSION CURRENT_RELEASE_RUNTIME

#define DECLARE_EVENT_DISPATCHER_EX(Event, address) \
template<> inline BSTEventDispatcher<Event> * GetEventDispatcher() \
{ \
	typedef BSTEventDispatcher<Event> * (*_GetEventDispatcher)(); \
	RelocAddr<_GetEventDispatcher> GetDispatcher(address.GetUIntPtr()-RelocationManager::s_baseAddr); \
	return GetDispatcher(); \
}

#define REGISTER_EVENT(_event, _sink) GetEventDispatcher<_event>()->AddEventSink(&_sink);

#define REGISTER_EVENT_SIMPLE(_event, _functionName) \
class _functionName##_class : public BSTEventSink<_event> \
{ \
public: \
	virtual ~##_functionName##_class() { }; \
	virtual	EventResult	ReceiveEvent(_event * evn, void * dispatcher) override \
	{ \
		return _functionName(evn); \
	}; \
}; \
 \
static _functionName##_class _functionName##_sink; \
 \
GetEventDispatcher<_event>()->AddEventSink(&##_functionName##_sink);



#include "f4se/PluginAPI.h"
#include "f4se/GameAPI.h"
#include "f4se/GameData.h"
#include <shlobj.h>
#include <string>

#include "GameReferences.h"

#include "Relocation/RVA.h"
#include "f4se_common/Relocation.h"

#include "ScaleformValue.h"

#include "SharedClasses_EventStruct.h"

extern IDebugLog	gLog;

void logMessage(std::string aString);

void InitReloc();

class InventoryInterface
{
public:
	struct FavoriteChangedEvent
	{

	};
	struct CountChangedEvent
	{

	};
	void*												unk00;
	BSTEventDispatcher<CountChangedEvent>				countChangedEventDispatcher;		// 08
	BSTEventDispatcher<FavoriteChangedEvent>			favoriteChangedEventDispatcher;		// 60
	struct Entry
	{
	public:
		UInt32			handleID; // 00
		UInt32			ownerHandle; // 04
		UInt16			itemPosition; // 08 position in inventoryList
		UInt16			unk0A;
	};
	STATIC_ASSERT(sizeof(Entry) == 0xC);
	tArray<Entry>										inventoryItems;						// B8
};
STATIC_ASSERT(sizeof(InventoryInterface) == 0xD0);

extern RelocPtr <InventoryInterface*> g_inventoryInterface;

class ActorEquipManager
{
public:
	void*												unk00;
	BSTEventDispatcher<ActorEquipManagerEvent::Event>	actorEquipManagerEventDispatcher;	// 08
};
STATIC_ASSERT(sizeof(ActorEquipManager) == 0x60);

extern RelocPtr <ActorEquipManager*> g_actorEquipManager;

void Shared2_Init();

extern RelocPtr <void*> g_holotapeStateChangedEventDispatcherAddress;
DECLARE_EVENT_DISPATCHER_EX(HolotapeStateChanged::Event, g_holotapeStateChangedEventDispatcherAddress)

extern RelocPtr <void*> g_bGSInventoryItemEventDispatcherAddress;
DECLARE_EVENT_DISPATCHER_EX(BGSInventoryItemEvent::Event, g_bGSInventoryItemEventDispatcherAddress)

extern RelocPtr <void*> g_playerDifficultySettingChangedDispatcherAddress;
DECLARE_EVENT_DISPATCHER_EX(PlayerDifficultySettingChanged::Event, g_playerDifficultySettingChangedDispatcherAddress)

void Shared2_InitEvents();

/*

*/
