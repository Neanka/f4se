#pragma once

#include "Shared.h"

/*
+8	04432D0	TESPackageEvent
+10	0443370	TESPerkEntryRunEvent
+18	04435F0	TESQuestStageEvent
+20	0443910	TESSceneActionEvent
+28	04439B0	TESSceneEvent
+30	0443A50	TESScenePhaseEvent
+38	0443E10	TESTopicInfoEvent

+0	04443B0	TerminalMenuItemRunEvent

*/


//0x140434fa0 - 140442010
struct unk442010Event {

};
DECLARE_EVENT_DISPATCHER(unk442010Event, 0x442010);

class unk442010EventSink : public BSTEventSink<unk442010Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442010Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442010Event:");
		return kEvent_Continue;
	}
};

unk442010EventSink _unk442010EventSink;

//0x1404350a0 - 1404420B0
struct unk4420B0Event {

};
DECLARE_EVENT_DISPATCHER(unk4420B0Event, 0x4420b0);

class unk4420B0EventSink : public BSTEventSink<unk4420B0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4420B0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4420B0Event:");
		return kEvent_Continue;
	}
};

unk4420B0EventSink _unk4420B0EventSink;

//0x140435160 - 140442150
struct unk442150Event {

};
DECLARE_EVENT_DISPATCHER(unk442150Event, 0x442150);

class unk442150EventSink : public BSTEventSink<unk442150Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442150Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442150Event:");
		return kEvent_Continue;
	}
};

unk442150EventSink _unk442150EventSink;

//0x140435220 - 1404421F0
struct unk4421F0Event {

};
DECLARE_EVENT_DISPATCHER(unk4421F0Event, 0x4421f0);

class unk4421F0EventSink : public BSTEventSink<unk4421F0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4421F0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4421F0Event:");
		return kEvent_Continue;
	}
};

unk4421F0EventSink _unk4421F0EventSink;

//0x140435320 - 140442330
struct unk442330Event {

};
DECLARE_EVENT_DISPATCHER(unk442330Event, 0x442330);

class unk442330EventSink : public BSTEventSink<unk442330Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442330Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442330Event:");
		return kEvent_Continue;
	}
};

unk442330EventSink _unk442330EventSink;

//0x1404353d0 - 1404411B0
struct unk4411B0Event {

};
DECLARE_EVENT_DISPATCHER(unk4411B0Event, 0x4411b0);

class unk4411B0EventSink : public BSTEventSink<unk4411B0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4411B0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4411B0Event:");
		return kEvent_Continue;
	}
};

unk4411B0EventSink _unk4411B0EventSink;

//0x140435460 - 140442470
struct unk442470Event {

};
DECLARE_EVENT_DISPATCHER(unk442470Event, 0x442470);

class unk442470EventSink : public BSTEventSink<unk442470Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442470Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442470Event:");
		return kEvent_Continue;
	}
};

unk442470EventSink _unk442470EventSink;

//0x140435560 - 1404423D0
struct unk4423D0Event {

};
DECLARE_EVENT_DISPATCHER(unk4423D0Event, 0x4423d0);

class unk4423D0EventSink : public BSTEventSink<unk4423D0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4423D0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4423D0Event:");
		return kEvent_Continue;
	}
};

unk4423D0EventSink _unk4423D0EventSink;

//0x140435700 - 140442510
struct unk442510Event {

};
DECLARE_EVENT_DISPATCHER(unk442510Event, 0x442510);

class unk442510EventSink : public BSTEventSink<unk442510Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442510Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442510Event:");
		return kEvent_Continue;
	}
};

unk442510EventSink _unk442510EventSink;

//0x1404357d0 - 1404425B0
struct unk4425B0Event {

};
DECLARE_EVENT_DISPATCHER(unk4425B0Event, 0x4425b0);

class unk4425B0EventSink : public BSTEventSink<unk4425B0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4425B0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4425B0Event:");
		return kEvent_Continue;
	}
};

unk4425B0EventSink _unk4425B0EventSink;

//0x140435890 - 140442650
struct unk442650Event {

};
DECLARE_EVENT_DISPATCHER(unk442650Event, 0x442650);

class unk442650EventSink : public BSTEventSink<unk442650Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442650Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442650Event:");
		return kEvent_Continue;
	}
};

unk442650EventSink _unk442650EventSink;

//0x140435950 - 140442790
struct unk442790Event {

};
DECLARE_EVENT_DISPATCHER(unk442790Event, 0x442790);

class unk442790EventSink : public BSTEventSink<unk442790Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442790Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442790Event:");
		return kEvent_Continue;
	}
};

unk442790EventSink _unk442790EventSink;

//0x140435a10 - 140442830
struct unk442830Event {

};
DECLARE_EVENT_DISPATCHER(unk442830Event, 0x442830);

class unk442830EventSink : public BSTEventSink<unk442830Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442830Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442830Event:");
		return kEvent_Continue;
	}
};

unk442830EventSink _unk442830EventSink;

//0x140435ad0 - 1404426F0
struct unk4426F0Event {

};
DECLARE_EVENT_DISPATCHER(unk4426F0Event, 0x4426f0);

class unk4426F0EventSink : public BSTEventSink<unk4426F0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4426F0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4426F0Event:");
		return kEvent_Continue;
	}
};

unk4426F0EventSink _unk4426F0EventSink;

//0x140435bb0 - 140442970
struct unk442970Event {

};
DECLARE_EVENT_DISPATCHER(unk442970Event, 0x442970);

class unk442970EventSink : public BSTEventSink<unk442970Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442970Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442970Event:");
		return kEvent_Continue;
	}
};

unk442970EventSink _unk442970EventSink;

//0x140435c10 - 140442A10
struct unk442A10Event {

};
DECLARE_EVENT_DISPATCHER(unk442A10Event, 0x442a10);

class unk442A10EventSink : public BSTEventSink<unk442A10Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442A10Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442A10Event:");
		return kEvent_Continue;
	}
};

unk442A10EventSink _unk442A10EventSink;

//0x140435cd0 - 140442AB0
struct unk442AB0Event {

};
DECLARE_EVENT_DISPATCHER(unk442AB0Event, 0x442ab0);

class unk442AB0EventSink : public BSTEventSink<unk442AB0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442AB0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442AB0Event:");
		return kEvent_Continue;
	}
};

unk442AB0EventSink _unk442AB0EventSink;

//0x140435dd0 - 140442B50
struct unk442B50Event {

};
DECLARE_EVENT_DISPATCHER(unk442B50Event, 0x442b50);

class unk442B50EventSink : public BSTEventSink<unk442B50Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442B50Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442B50Event:");
		return kEvent_Continue;
	}
};

unk442B50EventSink _unk442B50EventSink;

//0x140435e90 - 1404444F0
struct unk4444F0Event {

};
DECLARE_EVENT_DISPATCHER(unk4444F0Event, 0x4444f0);

class unk4444F0EventSink : public BSTEventSink<unk4444F0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4444F0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4444F0Event:");
		return kEvent_Continue;
	}
};

unk4444F0EventSink _unk4444F0EventSink;

//0x1404360f0 - 1404419D0
struct unk4419D0Event {

};
DECLARE_EVENT_DISPATCHER(unk4419D0Event, 0x4419d0);

class unk4419D0EventSink : public BSTEventSink<unk4419D0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4419D0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4419D0Event:");
		return kEvent_Continue;
	}
};

unk4419D0EventSink _unk4419D0EventSink;

//0x140436240 - 140441A70
struct unk441A70Event {

};
DECLARE_EVENT_DISPATCHER(unk441A70Event, 0x441a70);

class unk441A70EventSink : public BSTEventSink<unk441A70Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441A70Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441A70Event:");
		return kEvent_Continue;
	}
};

unk441A70EventSink _unk441A70EventSink;

//0x140436340 - 140444450
struct unk444450Event {

};
DECLARE_EVENT_DISPATCHER(unk444450Event, 0x444450);

class unk444450EventSink : public BSTEventSink<unk444450Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk444450Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk444450Event:");
		return kEvent_Continue;
	}
};

unk444450EventSink _unk444450EventSink;

//0x140436410 - 140442BF0
struct unk442BF0Event {

};
DECLARE_EVENT_DISPATCHER(unk442BF0Event, 0x442bf0);

class unk442BF0EventSink : public BSTEventSink<unk442BF0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442BF0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442BF0Event:");
		return kEvent_Continue;
	}
};

unk442BF0EventSink _unk442BF0EventSink;

//0x1404364d0 - 140442DD0
struct unk442DD0Event {

};
DECLARE_EVENT_DISPATCHER(unk442DD0Event, 0x442dd0);

class unk442DD0EventSink : public BSTEventSink<unk442DD0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442DD0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442DD0Event:");
		return kEvent_Continue;
	}
};

unk442DD0EventSink _unk442DD0EventSink;

//0x140436560 - 140442E70
struct unk442E70Event {

};
DECLARE_EVENT_DISPATCHER(unk442E70Event, 0x442e70);

class unk442E70EventSink : public BSTEventSink<unk442E70Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442E70Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442E70Event:");
		return kEvent_Continue;
	}
};

unk442E70EventSink _unk442E70EventSink;

//0x140436620 - 140442D30
struct unk442D30Event {

};
DECLARE_EVENT_DISPATCHER(unk442D30Event, 0x442d30);

class unk442D30EventSink : public BSTEventSink<unk442D30Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442D30Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442D30Event:");
		return kEvent_Continue;
	}
};

unk442D30EventSink _unk442D30EventSink;

//0x1404366b0 - 140442F10
struct unk442F10Event {

};
DECLARE_EVENT_DISPATCHER(unk442F10Event, 0x442f10);

class unk442F10EventSink : public BSTEventSink<unk442F10Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442F10Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442F10Event:");
		return kEvent_Continue;
	}
};

unk442F10EventSink _unk442F10EventSink;

//0x1404367b0 - 140442FB0
struct unk442FB0Event {

};
DECLARE_EVENT_DISPATCHER(unk442FB0Event, 0x442fb0);

class unk442FB0EventSink : public BSTEventSink<unk442FB0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442FB0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442FB0Event:");
		return kEvent_Continue;
	}
};

unk442FB0EventSink _unk442FB0EventSink;

//0x1404368c0 - 140443050
struct unk443050Event {

};
DECLARE_EVENT_DISPATCHER(unk443050Event, 0x443050);

class unk443050EventSink : public BSTEventSink<unk443050Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443050Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443050Event:");
		return kEvent_Continue;
	}
};

unk443050EventSink _unk443050EventSink;

//0x140436950 - 140443230
struct unk443230Event {

};
DECLARE_EVENT_DISPATCHER(unk443230Event, 0x443230);

class unk443230EventSink : public BSTEventSink<unk443230Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443230Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443230Event:");
		return kEvent_Continue;
	}
};

unk443230EventSink _unk443230EventSink;

//0x140436a50 - 1404432D0 TESPackageEvent ?
struct unk4432D0Event {

};
DECLARE_EVENT_DISPATCHER(unk4432D0Event, 0x4432d0);

class unk4432D0EventSink : public BSTEventSink<unk4432D0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4432D0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4432D0Event:");
		return kEvent_Continue;
	}
};

unk4432D0EventSink _unk4432D0EventSink;

//0x140436b20 - 140443370 TESPerkEntryRunEvent
struct unk443370Event {

};
DECLARE_EVENT_DISPATCHER(unk443370Event, 0x443370);

class unk443370EventSink : public BSTEventSink<unk443370Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443370Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443370Event:");
		return kEvent_Continue;
	}
};

unk443370EventSink _unk443370EventSink;

//0x140436c30 - 1404434B0
struct unk4434B0Event {

};
DECLARE_EVENT_DISPATCHER(unk4434B0Event, 0x4434b0);

class unk4434B0EventSink : public BSTEventSink<unk4434B0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4434B0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4434B0Event:");
		return kEvent_Continue;
	}
};

unk4434B0EventSink _unk4434B0EventSink;

//0x140436cf0 - 140443550
struct unk443550Event {

};
DECLARE_EVENT_DISPATCHER(unk443550Event, 0x443550);

class unk443550EventSink : public BSTEventSink<unk443550Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443550Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443550Event:");
		return kEvent_Continue;
	}
};

unk443550EventSink _unk443550EventSink;

//0x140436d80 - 1404435F0 TESQuestStageEvent
struct unk4435F0Event {

};
DECLARE_EVENT_DISPATCHER(unk4435F0Event, 0x4435f0);

class unk4435F0EventSink : public BSTEventSink<unk4435F0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4435F0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4435F0Event:");
		return kEvent_Continue;
	}
};

unk4435F0EventSink _unk4435F0EventSink;

//0x140436e40 - 140443690
struct unk443690Event {

};
DECLARE_EVENT_DISPATCHER(unk443690Event, 0x443690);

class unk443690EventSink : public BSTEventSink<unk443690Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443690Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443690Event:");
		return kEvent_Continue;
	}
};

unk443690EventSink _unk443690EventSink;

//0x140436ed0 - 140443730 TESQuestStartStopEvent
struct unk443730Event {

};
DECLARE_EVENT_DISPATCHER(unk443730Event, 0x443730);

class unk443730EventSink : public BSTEventSink<unk443730Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443730Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443730Event:");
		return kEvent_Continue;
	}
};

unk443730EventSink _unk443730EventSink;

//0x140436f60 - 1404437D0
struct unk4437D0Event {

};
DECLARE_EVENT_DISPATCHER(unk4437D0Event, 0x4437d0);

class unk4437D0EventSink : public BSTEventSink<unk4437D0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4437D0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4437D0Event:");
		return kEvent_Continue;
	}
};

unk4437D0EventSink _unk4437D0EventSink;

//0x140437020 - 140443870
struct unk443870Event {

};
DECLARE_EVENT_DISPATCHER(unk443870Event, 0x443870);

class unk443870EventSink : public BSTEventSink<unk443870Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443870Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443870Event:");
		return kEvent_Continue;
	}
};

unk443870EventSink _unk443870EventSink;

//0x1404370b0 - 1404439B0 TESSceneEvent
struct unk4439B0Event {

};
DECLARE_EVENT_DISPATCHER(unk4439B0Event, 0x4439b0);

class unk4439B0EventSink : public BSTEventSink<unk4439B0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4439B0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4439B0Event:");
		return kEvent_Continue;
	}
};

unk4439B0EventSink _unk4439B0EventSink;

//0x140437170 - 140443910 TESSceneActionEvent
struct unk443910Event {

};
DECLARE_EVENT_DISPATCHER(unk443910Event, 0x443910);

class unk443910EventSink : public BSTEventSink<unk443910Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443910Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443910Event:");
		return kEvent_Continue;
	}
};

unk443910EventSink _unk443910EventSink;

//0x140437240 - 140443A50 TESScenePhaseEvent
struct unk443A50Event {

};
DECLARE_EVENT_DISPATCHER(unk443A50Event, 0x443a50);

class unk443A50EventSink : public BSTEventSink<unk443A50Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443A50Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443A50Event:");
		return kEvent_Continue;
	}
};

unk443A50EventSink _unk443A50EventSink;

//0x140437310 - 140443AF0
struct unk443AF0Event {

};
DECLARE_EVENT_DISPATCHER(unk443AF0Event, 0x443af0);

class unk443AF0EventSink : public BSTEventSink<unk443AF0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443AF0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443AF0Event:");
		return kEvent_Continue;
	}
};

unk443AF0EventSink _unk443AF0EventSink;

//0x1404373e0 - 140443B90
struct unk443B90Event {

};
DECLARE_EVENT_DISPATCHER(unk443B90Event, 0x443b90);

class unk443B90EventSink : public BSTEventSink<unk443B90Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443B90Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443B90Event:");
		return kEvent_Continue;
	}
};

unk443B90EventSink _unk443B90EventSink;

//0x1404374e0 - 140443C30
struct unk443C30Event {

};
DECLARE_EVENT_DISPATCHER(unk443C30Event, 0x443c30);

class unk443C30EventSink : public BSTEventSink<unk443C30Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443C30Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443C30Event:");
		return kEvent_Continue;
	}
};

unk443C30EventSink _unk443C30EventSink;

//0x1404375d0 - 140443CD0
struct unk443CD0Event {

};
DECLARE_EVENT_DISPATCHER(unk443CD0Event, 0x443cd0);

class unk443CD0EventSink : public BSTEventSink<unk443CD0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443CD0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443CD0Event:");
		return kEvent_Continue;
	}
};

unk443CD0EventSink _unk443CD0EventSink;

//0x140437690 - 140443E10 TESTopicInfoEvent
struct unk443E10Event {

};
DECLARE_EVENT_DISPATCHER(unk443E10Event, 0x443e10);

class unk443E10EventSink : public BSTEventSink<unk443E10Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443E10Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443E10Event:");
		return kEvent_Continue;
	}
};

unk443E10EventSink _unk443E10EventSink;

//0x140437790 - 140443EB0
struct unk443EB0Event {

};
DECLARE_EVENT_DISPATCHER(unk443EB0Event, 0x443eb0);

class unk443EB0EventSink : public BSTEventSink<unk443EB0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443EB0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443EB0Event:");
		return kEvent_Continue;
	}
};

unk443EB0EventSink _unk443EB0EventSink;

//0x140437840 - 1404430F0
struct unk4430F0Event {

};
DECLARE_EVENT_DISPATCHER(unk4430F0Event, 0x4430f0);

class unk4430F0EventSink : public BSTEventSink<unk4430F0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4430F0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4430F0Event:");
		return kEvent_Continue;
	}
};

unk4430F0EventSink _unk4430F0EventSink;

//0x140437900 - 140443F50
struct unk443F50Event {

};
DECLARE_EVENT_DISPATCHER(unk443F50Event, 0x443f50);

class unk443F50EventSink : public BSTEventSink<unk443F50Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443F50Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443F50Event:");
		return kEvent_Continue;
	}
};

unk443F50EventSink _unk443F50EventSink;

//0x140437a40 - 140444090
struct unk444090Event {

};
DECLARE_EVENT_DISPATCHER(unk444090Event, 0x444090);

class unk444090EventSink : public BSTEventSink<unk444090Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk444090Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk444090Event:");
		return kEvent_Continue;
	}
};

unk444090EventSink _unk444090EventSink;

//0x140437b40 - 140443FF0
struct unk443FF0Event {

};
DECLARE_EVENT_DISPATCHER(unk443FF0Event, 0x443ff0);

class unk443FF0EventSink : public BSTEventSink<unk443FF0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443FF0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443FF0Event:");
		return kEvent_Continue;
	}
};

unk443FF0EventSink _unk443FF0EventSink;

//0x140437c40 - 140444130
struct unk444130Event {

};
DECLARE_EVENT_DISPATCHER(unk444130Event, 0x444130);

class unk444130EventSink : public BSTEventSink<unk444130Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk444130Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk444130Event:");
		return kEvent_Continue;
	}
};

unk444130EventSink _unk444130EventSink;

//0x140437d40 - 1404441D0
struct unk4441D0Event {

};
DECLARE_EVENT_DISPATCHER(unk4441D0Event, 0x4441d0);

class unk4441D0EventSink : public BSTEventSink<unk4441D0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4441D0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4441D0Event:");
		return kEvent_Continue;
	}
};

unk4441D0EventSink _unk4441D0EventSink;

//0x140437de0 - 140444270
struct unk444270Event {

};
DECLARE_EVENT_DISPATCHER(unk444270Event, 0x444270);

class unk444270EventSink : public BSTEventSink<unk444270Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk444270Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk444270Event:");
		return kEvent_Continue;
	}
};

unk444270EventSink _unk444270EventSink;

//0x140437e70 - 140444310
struct unk444310Event {

};
DECLARE_EVENT_DISPATCHER(unk444310Event, 0x444310);

class unk444310EventSink : public BSTEventSink<unk444310Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk444310Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk444310Event:");
		return kEvent_Continue;
	}
};

unk444310EventSink _unk444310EventSink;

//0x140437f00 - 140443D70
struct unk443D70Event {

};
DECLARE_EVENT_DISPATCHER(unk443D70Event, 0x443d70);

class unk443D70EventSink : public BSTEventSink<unk443D70Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443D70Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443D70Event:");
		return kEvent_Continue;
	}
};

unk443D70EventSink _unk443D70EventSink;

//0x140437fc0 - 140442290
struct unk442290Event {

};
DECLARE_EVENT_DISPATCHER(unk442290Event, 0x442290);

class unk442290EventSink : public BSTEventSink<unk442290Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442290Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442290Event:");
		return kEvent_Continue;
	}
};

unk442290EventSink _unk442290EventSink;

//0x1404380c0 - 140442C90
struct unk442C90Event {

};
DECLARE_EVENT_DISPATCHER(unk442C90Event, 0x442c90);

class unk442C90EventSink : public BSTEventSink<unk442C90Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442C90Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442C90Event:");
		return kEvent_Continue;
	}
};

unk442C90EventSink _unk442C90EventSink;

//0x1404381c0 - 140443410
struct unk443410Event {

};
DECLARE_EVENT_DISPATCHER(unk443410Event, 0x443410);

class unk443410EventSink : public BSTEventSink<unk443410Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443410Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443410Event:");
		return kEvent_Continue;
	}
};

unk443410EventSink _unk443410EventSink;

//0x140438280 - 140443190
struct unk443190Event {

};
DECLARE_EVENT_DISPATCHER(unk443190Event, 0x443190);

class unk443190EventSink : public BSTEventSink<unk443190Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443190Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443190Event:");
		return kEvent_Continue;
	}
};

unk443190EventSink _unk443190EventSink;

//0x140438340 - 140441930
struct unk441930Event {

};
DECLARE_EVENT_DISPATCHER(unk441930Event, 0x441930);

class unk441930EventSink : public BSTEventSink<unk441930Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441930Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441930Event:");
		return kEvent_Continue;
	}
};

unk441930EventSink _unk441930EventSink;

//0x140438400 - 140441570
struct unk441570Event {

};
DECLARE_EVENT_DISPATCHER(unk441570Event, 0x441570);

class unk441570EventSink : public BSTEventSink<unk441570Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441570Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441570Event:");
		return kEvent_Continue;
	}
};

unk441570EventSink _unk441570EventSink;

//0x1404384c0 - 140441250
struct unk441250Event {

};
DECLARE_EVENT_DISPATCHER(unk441250Event, 0x441250);

class unk441250EventSink : public BSTEventSink<unk441250Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441250Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441250Event:");
		return kEvent_Continue;
	}
};

unk441250EventSink _unk441250EventSink;

//0x140438580 - 140441430
struct unk441430Event {

};
DECLARE_EVENT_DISPATCHER(unk441430Event, 0x441430);

class unk441430EventSink : public BSTEventSink<unk441430Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441430Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441430Event:");
		return kEvent_Continue;
	}
};

unk441430EventSink _unk441430EventSink;

//0x140438610 - 140441610 BGSOnPlayerModArmorWeaponEvent
struct unk441610Event {

};
DECLARE_EVENT_DISPATCHER(unk441610Event, 0x441610);

class unk441610EventSink : public BSTEventSink<unk441610Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441610Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441610Event:");
		return kEvent_Continue;
	}
};

unk441610EventSink _unk441610EventSink;

//0x1404386a0 - 1404412F0
struct unk4412F0Event {

};
DECLARE_EVENT_DISPATCHER(unk4412F0Event, 0x4412f0);

class unk4412F0EventSink : public BSTEventSink<unk4412F0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4412F0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4412F0Event:");
		return kEvent_Continue;
	}
};

unk4412F0EventSink _unk4412F0EventSink;

//0x140438760 - 1404416B0
struct unk4416B0Event {

};
DECLARE_EVENT_DISPATCHER(unk4416B0Event, 0x4416b0);

class unk4416B0EventSink : public BSTEventSink<unk4416B0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4416B0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4416B0Event:");
		return kEvent_Continue;
	}
};

unk4416B0EventSink _unk4416B0EventSink;

//0x140438830 - 1404414D0
struct unk4414D0Event {

};
DECLARE_EVENT_DISPATCHER(unk4414D0Event, 0x4414d0);

class unk4414D0EventSink : public BSTEventSink<unk4414D0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4414D0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4414D0Event:");
		return kEvent_Continue;
	}
};

unk4414D0EventSink _unk4414D0EventSink;

//0x1404388c0 - 140441750
struct unk441750Event {

};
DECLARE_EVENT_DISPATCHER(unk441750Event, 0x441750);

class unk441750EventSink : public BSTEventSink<unk441750Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441750Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441750Event:");
		return kEvent_Continue;
	}
};

unk441750EventSink _unk441750EventSink;

//0x140438950 - 140441390
struct unk441390Event {

};
DECLARE_EVENT_DISPATCHER(unk441390Event, 0x441390);

class unk441390EventSink : public BSTEventSink<unk441390Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441390Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441390Event:");
		return kEvent_Continue;
	}
};

unk441390EventSink _unk441390EventSink;

//0x140438a10 - 1404417F0
struct unk4417F0Event {

};
DECLARE_EVENT_DISPATCHER(unk4417F0Event, 0x4417f0);

class unk4417F0EventSink : public BSTEventSink<unk4417F0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4417F0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4417F0Event:");
		return kEvent_Continue;
	}
};

unk4417F0EventSink _unk4417F0EventSink;

//0x140438ad0 - 140441890
struct unk441890Event {

};
DECLARE_EVENT_DISPATCHER(unk441890Event, 0x441890);

class unk441890EventSink : public BSTEventSink<unk441890Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441890Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441890Event:");
		return kEvent_Continue;
	}
};

unk441890EventSink _unk441890EventSink;

//0x1404a8ca0 - 1404A9120
struct unk4A9120Event {

};
DECLARE_EVENT_DISPATCHER(unk4A9120Event, 0x4a9120);

class unk4A9120EventSink : public BSTEventSink<unk4A9120Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4A9120Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4A9120Event:");
		return kEvent_Continue;
	}
};

unk4A9120EventSink _unk4A9120EventSink;

//0x14056f150 - 140571710
struct unk571710Event {

};
DECLARE_EVENT_DISPATCHER(unk571710Event, 0x571710);

class unk571710EventSink : public BSTEventSink<unk571710Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk571710Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk571710Event:");
		return kEvent_Continue;
	}
};

unk571710EventSink _unk571710EventSink;

//0x140577a50 - 140577B50
struct unk577B50Event {

};
DECLARE_EVENT_DISPATCHER(unk577B50Event, 0x577b50);

class unk577B50EventSink : public BSTEventSink<unk577B50Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk577B50Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk577B50Event:");
		return kEvent_Continue;
	}
};

unk577B50EventSink _unk577B50EventSink;

//0x1405d3f80 - 1405E2DB0
struct unk5E2DB0Event {

};
DECLARE_EVENT_DISPATCHER(unk5E2DB0Event, 0x5e2db0);

class unk5E2DB0EventSink : public BSTEventSink<unk5E2DB0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk5E2DB0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk5E2DB0Event:");
		return kEvent_Continue;
	}
};

unk5E2DB0EventSink _unk5E2DB0EventSink;

//0x1405d4010 - 1405E2E50
struct unk5E2E50Event {

};
DECLARE_EVENT_DISPATCHER(unk5E2E50Event, 0x5e2e50);

class unk5E2E50EventSink : public BSTEventSink<unk5E2E50Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk5E2E50Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk5E2E50Event:");
		return kEvent_Continue;
	}
};

unk5E2E50EventSink _unk5E2E50EventSink;

//0x140b85490 - 140B87FA0
struct unkB87FA0Event {

};
DECLARE_EVENT_DISPATCHER(unkB87FA0Event, 0xb87fa0);

class unkB87FA0EventSink : public BSTEventSink<unkB87FA0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkB87FA0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkB87FA0Event:");
		return kEvent_Continue;
	}
};

unkB87FA0EventSink _unkB87FA0EventSink;

//0x140b85520 - 140B88040
struct unkB88040Event {

};
DECLARE_EVENT_DISPATCHER(unkB88040Event, 0xb88040);

class unkB88040EventSink : public BSTEventSink<unkB88040Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkB88040Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkB88040Event:");
		return kEvent_Continue;
	}
};

unkB88040EventSink _unkB88040EventSink;

//0x140b855b0 - 140B880E0
struct unkB880E0Event {

};
DECLARE_EVENT_DISPATCHER(unkB880E0Event, 0xb880e0);

class unkB880E0EventSink : public BSTEventSink<unkB880E0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkB880E0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkB880E0Event:");
		return kEvent_Continue;
	}
};

unkB880E0EventSink _unkB880E0EventSink;

//0x140bb80b0 - 140BB8140
struct unkBB8140Event {

};
DECLARE_EVENT_DISPATCHER(unkBB8140Event, 0xbb8140);

class unkBB8140EventSink : public BSTEventSink<unkBB8140Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkBB8140Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkBB8140Event:");
		return kEvent_Continue;
	}
};

unkBB8140EventSink _unkBB8140EventSink;

//0x140d1d120 - 140D1E080
struct unkD1E080Event {

};
DECLARE_EVENT_DISPATCHER(unkD1E080Event, 0xd1e080);

class unkD1E080EventSink : public BSTEventSink<unkD1E080Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkD1E080Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkD1E080Event:");
		return kEvent_Continue;
	}
};

unkD1E080EventSink _unkD1E080EventSink;

//0x140d1d180 - 140D1E150
struct unkD1E150Event {

};
DECLARE_EVENT_DISPATCHER(unkD1E150Event, 0xd1e150);

class unkD1E150EventSink : public BSTEventSink<unkD1E150Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkD1E150Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkD1E150Event:");
		return kEvent_Continue;
	}
};

unkD1E150EventSink _unkD1E150EventSink;

//0x140d6d430 - 140DC5990
struct unkDC5990Event {

};
DECLARE_EVENT_DISPATCHER(unkDC5990Event, 0xdc5990);

class unkDC5990EventSink : public BSTEventSink<unkDC5990Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkDC5990Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkDC5990Event:");
		return kEvent_Continue;
	}
};

unkDC5990EventSink _unkDC5990EventSink;

//0x140d6d490 - 140DC5A70
struct unkDC5A70Event {

};
DECLARE_EVENT_DISPATCHER(unkDC5A70Event, 0xdc5a70);

class unkDC5A70EventSink : public BSTEventSink<unkDC5A70Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkDC5A70Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkDC5A70Event:");
		return kEvent_Continue;
	}
};

unkDC5A70EventSink _unkDC5A70EventSink;

//0x140d6d4f0 - 140DC5CF0
struct unkDC5CF0Event {

};
DECLARE_EVENT_DISPATCHER(unkDC5CF0Event, 0xdc5cf0);

class unkDC5CF0EventSink : public BSTEventSink<unkDC5CF0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkDC5CF0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkDC5CF0Event:");
		return kEvent_Continue;
	}
};

unkDC5CF0EventSink _unkDC5CF0EventSink;

//0x140d6d550 - 140DC5DC0
struct unkDC5DC0Event {

};
DECLARE_EVENT_DISPATCHER(unkDC5DC0Event, 0xdc5dc0);

class unkDC5DC0EventSink : public BSTEventSink<unkDC5DC0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkDC5DC0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkDC5DC0Event:");
		return kEvent_Continue;
	}
};

unkDC5DC0EventSink _unkDC5DC0EventSink;

//0x140d6d5b0 - 140DC5E90
struct unkDC5E90Event {

};
DECLARE_EVENT_DISPATCHER(unkDC5E90Event, 0xdc5e90);

class unkDC5E90EventSink : public BSTEventSink<unkDC5E90Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkDC5E90Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkDC5E90Event:");
		return kEvent_Continue;
	}
};

unkDC5E90EventSink _unkDC5E90EventSink;

//0x140d6d610 - 140DC5B40
struct unkDC5B40Event {

};
DECLARE_EVENT_DISPATCHER(unkDC5B40Event, 0xdc5b40);

class unkDC5B40EventSink : public BSTEventSink<unkDC5B40Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkDC5B40Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkDC5B40Event:");
		return kEvent_Continue;
	}
};

unkDC5B40EventSink _unkDC5B40EventSink;

//0x140d6d670 - 140DC5C20
struct unkDC5C20Event {

};
DECLARE_EVENT_DISPATCHER(unkDC5C20Event, 0xdc5c20);

class unkDC5C20EventSink : public BSTEventSink<unkDC5C20Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkDC5C20Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkDC5C20Event:");
		return kEvent_Continue;
	}
};

unkDC5C20EventSink _unkDC5C20EventSink;

//0x140df5b40 - 140DF9100
struct unkDF9100Event {

};
DECLARE_EVENT_DISPATCHER(unkDF9100Event, 0xdf9100);

class unkDF9100EventSink : public BSTEventSink<unkDF9100Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkDF9100Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkDF9100Event:");
		return kEvent_Continue;
	}
};

unkDF9100EventSink _unkDF9100EventSink;

//0x140dfc420 - 140E07590
struct unkE07590Event {

};
DECLARE_EVENT_DISPATCHER(unkE07590Event, 0xe07590);

class unkE07590EventSink : public BSTEventSink<unkE07590Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkE07590Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkE07590Event:");
		return kEvent_Continue;
	}
};

unkE07590EventSink _unkE07590EventSink;

//0x140dfc4b0 - 140E07630
struct unkE07630Event {

};
DECLARE_EVENT_DISPATCHER(unkE07630Event, 0xe07630);

class unkE07630EventSink : public BSTEventSink<unkE07630Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkE07630Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkE07630Event:");
		return kEvent_Continue;
	}
};

unkE07630EventSink _unkE07630EventSink;

//0x140e10180 - 140E15A20
struct unkE15A20Event {

};
DECLARE_EVENT_DISPATCHER(unkE15A20Event, 0xe15a20);

class unkE15A20EventSink : public BSTEventSink<unkE15A20Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkE15A20Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkE15A20Event:");
		return kEvent_Continue;
	}
};

unkE15A20EventSink _unkE15A20EventSink;

//0x140e101e0 - 140E15B00
struct unkE15B00Event {

};
DECLARE_EVENT_DISPATCHER(unkE15B00Event, 0xe15b00);

class unkE15B00EventSink : public BSTEventSink<unkE15B00Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkE15B00Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkE15B00Event:");
		return kEvent_Continue;
	}
};

unkE15B00EventSink _unkE15B00EventSink;

//0x140e95530 - 140EC1F80
struct unkEC1F80Event {

};
DECLARE_EVENT_DISPATCHER(unkEC1F80Event, 0xec1f80);

class unkEC1F80EventSink : public BSTEventSink<unkEC1F80Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC1F80Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC1F80Event:");
		return kEvent_Continue;
	}
};

unkEC1F80EventSink _unkEC1F80EventSink;

//0x140e95590 - 140EC2060
struct unkEC2060Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2060Event, 0xec2060);

class unkEC2060EventSink : public BSTEventSink<unkEC2060Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2060Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2060Event:");
		return kEvent_Continue;
	}
};

unkEC2060EventSink _unkEC2060EventSink;

//0x140e95620 - 140EC2100
struct unkEC2100Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2100Event, 0xec2100);

class unkEC2100EventSink : public BSTEventSink<unkEC2100Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2100Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2100Event:");
		return kEvent_Continue;
	}
};

unkEC2100EventSink _unkEC2100EventSink;

//0x140e956b0 - 140EC21A0
struct unkEC21A0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC21A0Event, 0xec21a0);

class unkEC21A0EventSink : public BSTEventSink<unkEC21A0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC21A0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC21A0Event:");
		return kEvent_Continue;
	}
};

unkEC21A0EventSink _unkEC21A0EventSink;

//0x140e95740 - 140EC2240
struct unkEC2240Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2240Event, 0xec2240);

class unkEC2240EventSink : public BSTEventSink<unkEC2240Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2240Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2240Event:");
		return kEvent_Continue;
	}
};

unkEC2240EventSink _unkEC2240EventSink;

//0x140e957d0 - 140EC22E0
struct unkEC22E0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC22E0Event, 0xec22e0);

class unkEC22E0EventSink : public BSTEventSink<unkEC22E0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC22E0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC22E0Event:");
		return kEvent_Continue;
	}
};

unkEC22E0EventSink _unkEC22E0EventSink;

//0x140e95860 - 140EC2380
struct unkEC2380Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2380Event, 0xec2380);

class unkEC2380EventSink : public BSTEventSink<unkEC2380Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2380Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2380Event:");
		return kEvent_Continue;
	}
};

unkEC2380EventSink _unkEC2380EventSink;

//0x140e958f0 - 140EC2420
struct unkEC2420Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2420Event, 0xec2420);

class unkEC2420EventSink : public BSTEventSink<unkEC2420Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2420Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2420Event:");
		return kEvent_Continue;
	}
};

unkEC2420EventSink _unkEC2420EventSink;

//0x140e95980 - 140EC24C0
struct unkEC24C0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC24C0Event, 0xec24c0);

class unkEC24C0EventSink : public BSTEventSink<unkEC24C0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC24C0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC24C0Event:");
		return kEvent_Continue;
	}
};

unkEC24C0EventSink _unkEC24C0EventSink;

//0x140e95a10 - 140EC2560
struct unkEC2560Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2560Event, 0xec2560);

class unkEC2560EventSink : public BSTEventSink<unkEC2560Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2560Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2560Event:");
		return kEvent_Continue;
	}
};

unkEC2560EventSink _unkEC2560EventSink;

//0x140e95aa0 - 140EC2600
struct unkEC2600Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2600Event, 0xec2600);

class unkEC2600EventSink : public BSTEventSink<unkEC2600Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2600Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2600Event:");
		return kEvent_Continue;
	}
};

unkEC2600EventSink _unkEC2600EventSink;

//0x140e95b30 - 140EC26A0
struct unkEC26A0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC26A0Event, 0xec26a0);

class unkEC26A0EventSink : public BSTEventSink<unkEC26A0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC26A0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC26A0Event:");
		return kEvent_Continue;
	}
};

unkEC26A0EventSink _unkEC26A0EventSink;

//0x140e95bc0 - 140EC2740
struct unkEC2740Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2740Event, 0xec2740);

class unkEC2740EventSink : public BSTEventSink<unkEC2740Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2740Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2740Event:");
		return kEvent_Continue;
	}
};

unkEC2740EventSink _unkEC2740EventSink;

//0x140e95c50 - 140EC27E0
struct unkEC27E0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC27E0Event, 0xec27e0);

class unkEC27E0EventSink : public BSTEventSink<unkEC27E0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC27E0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC27E0Event:");
		return kEvent_Continue;
	}
};

unkEC27E0EventSink _unkEC27E0EventSink;

//0x140e95ce0 - 140EC2880
struct unkEC2880Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2880Event, 0xec2880);

class unkEC2880EventSink : public BSTEventSink<unkEC2880Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2880Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2880Event:");
		return kEvent_Continue;
	}
};

unkEC2880EventSink _unkEC2880EventSink;

//0x140e95d70 - 140EC2920
struct unkEC2920Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2920Event, 0xec2920);

class unkEC2920EventSink : public BSTEventSink<unkEC2920Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2920Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2920Event:");
		return kEvent_Continue;
	}
};

unkEC2920EventSink _unkEC2920EventSink;

//0x140e95e00 - 140EC29C0
struct unkEC29C0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC29C0Event, 0xec29c0);

class unkEC29C0EventSink : public BSTEventSink<unkEC29C0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC29C0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC29C0Event:");
		return kEvent_Continue;
	}
};

unkEC29C0EventSink _unkEC29C0EventSink;

//0x140e95e90 - 140EC2A60
struct unkEC2A60Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2A60Event, 0xec2a60);

class unkEC2A60EventSink : public BSTEventSink<unkEC2A60Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2A60Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2A60Event:");
		return kEvent_Continue;
	}
};

unkEC2A60EventSink _unkEC2A60EventSink;

//0x140e95f20 - 140EC2B00
struct unkEC2B00Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2B00Event, 0xec2b00);

class unkEC2B00EventSink : public BSTEventSink<unkEC2B00Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2B00Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2B00Event:");
		return kEvent_Continue;
	}
};

unkEC2B00EventSink _unkEC2B00EventSink;

//0x140e95fb0 - 140EC2BA0
struct unkEC2BA0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2BA0Event, 0xec2ba0);

class unkEC2BA0EventSink : public BSTEventSink<unkEC2BA0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2BA0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2BA0Event:");
		return kEvent_Continue;
	}
};

unkEC2BA0EventSink _unkEC2BA0EventSink;

//0x140e96040 - 140EC2C40
struct unkEC2C40Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2C40Event, 0xec2c40);

class unkEC2C40EventSink : public BSTEventSink<unkEC2C40Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2C40Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2C40Event:");
		return kEvent_Continue;
	}
};

unkEC2C40EventSink _unkEC2C40EventSink;

//0x140e960d0 - 140EC2CE0
struct unkEC2CE0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2CE0Event, 0xec2ce0);

class unkEC2CE0EventSink : public BSTEventSink<unkEC2CE0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2CE0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2CE0Event:");
		return kEvent_Continue;
	}
};

unkEC2CE0EventSink _unkEC2CE0EventSink;

//0x140e96160 - 140EC2D80
struct unkEC2D80Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2D80Event, 0xec2d80);

class unkEC2D80EventSink : public BSTEventSink<unkEC2D80Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2D80Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2D80Event:");
		return kEvent_Continue;
	}
};

unkEC2D80EventSink _unkEC2D80EventSink;

//0x140e961f0 - 140EC2E20
struct unkEC2E20Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2E20Event, 0xec2e20);

class unkEC2E20EventSink : public BSTEventSink<unkEC2E20Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2E20Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2E20Event:");
		return kEvent_Continue;
	}
};

unkEC2E20EventSink _unkEC2E20EventSink;

//0x140e96280 - 140EC2EC0 PlayerDifficultySettingChanged::Event 
struct unkEC2EC0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2EC0Event, 0xec2ec0);

class unkEC2EC0EventSink : public BSTEventSink<unkEC2EC0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2EC0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2EC0Event:");
		return kEvent_Continue;
	}
};

unkEC2EC0EventSink _unkEC2EC0EventSink;

//0x140e96310 - 140EC2F60
struct unkEC2F60Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2F60Event, 0xec2f60);

class unkEC2F60EventSink : public BSTEventSink<unkEC2F60Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2F60Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2F60Event:");
		return kEvent_Continue;
	}
};

unkEC2F60EventSink _unkEC2F60EventSink;

//0x140e963a0 - 140EC3000
struct unkEC3000Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3000Event, 0xec3000);

class unkEC3000EventSink : public BSTEventSink<unkEC3000Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3000Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3000Event:");
		return kEvent_Continue;
	}
};

unkEC3000EventSink _unkEC3000EventSink;

//0x140e96430 - 140EC30A0
struct unkEC30A0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC30A0Event, 0xec30a0);

class unkEC30A0EventSink : public BSTEventSink<unkEC30A0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC30A0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC30A0Event:");
		return kEvent_Continue;
	}
};

unkEC30A0EventSink _unkEC30A0EventSink;

//0x140e964c0 - 140EC3140
struct unkEC3140Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3140Event, 0xec3140);

class unkEC3140EventSink : public BSTEventSink<unkEC3140Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3140Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3140Event:");
		return kEvent_Continue;
	}
};

unkEC3140EventSink _unkEC3140EventSink;

//0x140e96550 - 140EC31E0
struct unkEC31E0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC31E0Event, 0xec31e0);

class unkEC31E0EventSink : public BSTEventSink<unkEC31E0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC31E0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC31E0Event:");
		return kEvent_Continue;
	}
};

unkEC31E0EventSink _unkEC31E0EventSink;

//0x140e965e0 - 140EC3280
struct unkEC3280Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3280Event, 0xec3280);

class unkEC3280EventSink : public BSTEventSink<unkEC3280Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3280Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3280Event:");
		return kEvent_Continue;
	}
};

unkEC3280EventSink _unkEC3280EventSink;

//0x140e96670 - 140EC3320
struct unkEC3320Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3320Event, 0xec3320);

class unkEC3320EventSink : public BSTEventSink<unkEC3320Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3320Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3320Event:");
		return kEvent_Continue;
	}
};

unkEC3320EventSink _unkEC3320EventSink;

//0x140e96700 - 140EC33C0
struct unkEC33C0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC33C0Event, 0xec33c0);

class unkEC33C0EventSink : public BSTEventSink<unkEC33C0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC33C0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC33C0Event:");
		return kEvent_Continue;
	}
};

unkEC33C0EventSink _unkEC33C0EventSink;

//0x140e96790 - 140EC3460
struct unkEC3460Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3460Event, 0xec3460);

class unkEC3460EventSink : public BSTEventSink<unkEC3460Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3460Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3460Event:");
		return kEvent_Continue;
	}
};

unkEC3460EventSink _unkEC3460EventSink;

//0x140e96820 - 140EC3500
struct unkEC3500Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3500Event, 0xec3500);

class unkEC3500EventSink : public BSTEventSink<unkEC3500Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3500Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3500Event:");
		return kEvent_Continue;
	}
};

unkEC3500EventSink _unkEC3500EventSink;

//0x140e968c0 - 140EC35A0
struct unkEC35A0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC35A0Event, 0xec35a0);

class unkEC35A0EventSink : public BSTEventSink<unkEC35A0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC35A0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC35A0Event:");
		return kEvent_Continue;
	}
};

unkEC35A0EventSink _unkEC35A0EventSink;

//0x140e96920 - 140EC3670
struct unkEC3670Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3670Event, 0xec3670);

class unkEC3670EventSink : public BSTEventSink<unkEC3670Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3670Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3670Event:");
		return kEvent_Continue;
	}
};

unkEC3670EventSink _unkEC3670EventSink;

//0x140e96d70 - 140E96DD0
struct unkE96DD0Event {

};
DECLARE_EVENT_DISPATCHER(unkE96DD0Event, 0xe96dd0);

class unkE96DD0EventSink : public BSTEventSink<unkE96DD0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkE96DD0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkE96DD0Event:");
		return kEvent_Continue;
	}
};

unkE96DD0EventSink _unkE96DD0EventSink;

//0x140f41d40 - 140F45770
struct unkF45770Event {

};
DECLARE_EVENT_DISPATCHER(unkF45770Event, 0xf45770);

class unkF45770EventSink : public BSTEventSink<unkF45770Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkF45770Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkF45770Event:");
		return kEvent_Continue;
	}
};

unkF45770EventSink _unkF45770EventSink;

//0x140f5b650 - 140F5BB00
struct unkF5BB00Event {

};
DECLARE_EVENT_DISPATCHER(unkF5BB00Event, 0xf5bb00);

class unkF5BB00EventSink : public BSTEventSink<unkF5BB00Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkF5BB00Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkF5BB00Event:");
		return kEvent_Continue;
	}
};

unkF5BB00EventSink _unkF5BB00EventSink;

//0x140fc7c10 - 140FD9350
struct unkFD9350Event {

};
DECLARE_EVENT_DISPATCHER(unkFD9350Event, 0xfd9350);

class unkFD9350EventSink : public BSTEventSink<unkFD9350Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkFD9350Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkFD9350Event:");
		return kEvent_Continue;
	}
};

unkFD9350EventSink _unkFD9350EventSink;

//0x140fe6e80 - 240FE6DB0
struct unk100FE6DB0Event {

};
DECLARE_EVENT_DISPATCHER(unk100FE6DB0Event, 0x100fe6db0);

class unk100FE6DB0EventSink : public BSTEventSink<unk100FE6DB0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk100FE6DB0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk100FE6DB0Event:");
		return kEvent_Continue;
	}
};

unk100FE6DB0EventSink _unk100FE6DB0EventSink;

//0x1412797e0 - 14127D6B0
struct unk127D6B0Event {

};
DECLARE_EVENT_DISPATCHER(unk127D6B0Event, 0x127d6b0);

class unk127D6B0EventSink : public BSTEventSink<unk127D6B0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk127D6B0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk127D6B0Event:");
		return kEvent_Continue;
	}
};

unk127D6B0EventSink _unk127D6B0EventSink;

//0x141279870 - 14127D750
struct unk127D750Event {

};
DECLARE_EVENT_DISPATCHER(unk127D750Event, 0x127d750);

class unk127D750EventSink : public BSTEventSink<unk127D750Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk127D750Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk127D750Event:");
		return kEvent_Continue;
	}
};

unk127D750EventSink _unk127D750EventSink;

//0x14129bab0 - 14129E7B0
struct unk129E7B0Event {

};
DECLARE_EVENT_DISPATCHER(unk129E7B0Event, 0x129e7b0);

class unk129E7B0EventSink : public BSTEventSink<unk129E7B0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk129E7B0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk129E7B0Event:");
		return kEvent_Continue;
	}
};

unk129E7B0EventSink _unk129E7B0EventSink;

//0x1412b05a0 - 1412B1380
struct unk12B1380Event {

};
DECLARE_EVENT_DISPATCHER(unk12B1380Event, 0x12b1380);

class unk12B1380EventSink : public BSTEventSink<unk12B1380Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk12B1380Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk12B1380Event:");
		return kEvent_Continue;
	}
};

unk12B1380EventSink _unk12B1380EventSink;

//0x141b0d880 - 141B0F970
struct unk1B0F970Event {

};
DECLARE_EVENT_DISPATCHER(unk1B0F970Event, 0x1b0f970);

class unk1B0F970EventSink : public BSTEventSink<unk1B0F970Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk1B0F970Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk1B0F970Event:");
		return kEvent_Continue;
	}
};

unk1B0F970EventSink _unk1B0F970EventSink;

//0x141b15700 - 141B15F80
struct unk1B15F80Event {

};
DECLARE_EVENT_DISPATCHER(unk1B15F80Event, 0x1b15f80);

class unk1B15F80EventSink : public BSTEventSink<unk1B15F80Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk1B15F80Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk1B15F80Event:");
		return kEvent_Continue;
	}
};

unk1B15F80EventSink _unk1B15F80EventSink;

