#pragma once

#include "Shared.h"

//0x1400f46d0 - 140100E80
struct unk100E80Event {

};
DECLARE_EVENT_DISPATCHER(unk100E80Event, 0x100e80);

class unk100E80EventSink : public BSTEventSink<unk100E80Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk100E80Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk100E80Event:");
		return kEvent_Continue;
	}
};

unk100E80EventSink _unk100E80EventSink;

//0x140100d90 - 14010B730
struct unk10B730Event {

};
DECLARE_EVENT_DISPATCHER(unk10B730Event, 0x10b730);

class unk10B730EventSink : public BSTEventSink<unk10B730Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk10B730Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk10B730Event:");
		return kEvent_Continue;
	}
};

unk10B730EventSink _unk10B730EventSink;

//0x140161f20 - 140162970
struct unk162970Event {

};
DECLARE_EVENT_DISPATCHER(unk162970Event, 0x162970);

class unk162970EventSink : public BSTEventSink<unk162970Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk162970Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk162970Event:");
		return kEvent_Continue;
	}
};

unk162970EventSink _unk162970EventSink;

//0x1401a8a00 - 1401A8D90
struct unk1A8D90Event {

};
DECLARE_EVENT_DISPATCHER(unk1A8D90Event, 0x1a8d90);

class unk1A8D90EventSink : public BSTEventSink<unk1A8D90Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk1A8D90Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk1A8D90Event:");
		return kEvent_Continue;
	}
};

unk1A8D90EventSink _unk1A8D90EventSink;

//0x1401f3d40 - 140229FB0
struct unk229FB0Event {

};
DECLARE_EVENT_DISPATCHER(unk229FB0Event, 0x229fb0);

class unk229FB0EventSink : public BSTEventSink<unk229FB0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk229FB0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk229FB0Event:");
		return kEvent_Continue;
	}
};

unk229FB0EventSink _unk229FB0EventSink;

//0x1401f3da0 - 14022A050
struct unk22A050Event {

};
DECLARE_EVENT_DISPATCHER(unk22A050Event, 0x22a050);

class unk22A050EventSink : public BSTEventSink<unk22A050Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk22A050Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk22A050Event:");
		return kEvent_Continue;
	}
};

unk22A050EventSink _unk22A050EventSink;

//0x1401f3e00 - 140229DD0
struct unk229DD0Event {

};
DECLARE_EVENT_DISPATCHER(unk229DD0Event, 0x229dd0);

class unk229DD0EventSink : public BSTEventSink<unk229DD0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk229DD0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk229DD0Event:");
		return kEvent_Continue;
	}
};

unk229DD0EventSink _unk229DD0EventSink;

//0x1401f3e60 - 140229F10
struct unk229F10Event {

};
DECLARE_EVENT_DISPATCHER(unk229F10Event, 0x229f10);

class unk229F10EventSink : public BSTEventSink<unk229F10Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk229F10Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk229F10Event:");
		return kEvent_Continue;
	}
};

unk229F10EventSink _unk229F10EventSink;

//0x1401f3ec0 - 140229E70
struct unk229E70Event {

};
DECLARE_EVENT_DISPATCHER(unk229E70Event, 0x229e70);

class unk229E70EventSink : public BSTEventSink<unk229E70Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk229E70Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk229E70Event:");
		return kEvent_Continue;
	}
};

unk229E70EventSink _unk229E70EventSink;

//0x1401f3f20 - 14022A370
struct unk22A370Event {

};
DECLARE_EVENT_DISPATCHER(unk22A370Event, 0x22a370);

class unk22A370EventSink : public BSTEventSink<unk22A370Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk22A370Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk22A370Event:");
		return kEvent_Continue;
	}
};

unk22A370EventSink _unk22A370EventSink;

//0x1401f3f80 - 14022A2D0
struct unk22A2D0Event {

};
DECLARE_EVENT_DISPATCHER(unk22A2D0Event, 0x22a2d0);

class unk22A2D0EventSink : public BSTEventSink<unk22A2D0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk22A2D0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk22A2D0Event:");
		return kEvent_Continue;
	}
};

unk22A2D0EventSink _unk22A2D0EventSink;

//0x1401f3fe0 - 140229D30
struct unk229D30Event {

};
DECLARE_EVENT_DISPATCHER(unk229D30Event, 0x229d30);

class unk229D30EventSink : public BSTEventSink<unk229D30Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk229D30Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk229D30Event:");
		return kEvent_Continue;
	}
};

unk229D30EventSink _unk229D30EventSink;

//0x1401f4040 - 14022A190
struct unk22A190Event {

};
DECLARE_EVENT_DISPATCHER(unk22A190Event, 0x22a190);

class unk22A190EventSink : public BSTEventSink<unk22A190Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk22A190Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk22A190Event:");
		return kEvent_Continue;
	}
};

unk22A190EventSink _unk22A190EventSink;

//0x1401f40a0 - 14022A0F0
struct unk22A0F0Event {

};
DECLARE_EVENT_DISPATCHER(unk22A0F0Event, 0x22a0f0);

class unk22A0F0EventSink : public BSTEventSink<unk22A0F0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk22A0F0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk22A0F0Event:");
		return kEvent_Continue;
	}
};

unk22A0F0EventSink _unk22A0F0EventSink;

//0x1401f4100 - 14022A410
struct unk22A410Event {

};
DECLARE_EVENT_DISPATCHER(unk22A410Event, 0x22a410);

class unk22A410EventSink : public BSTEventSink<unk22A410Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk22A410Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk22A410Event:");
		return kEvent_Continue;
	}
};

unk22A410EventSink _unk22A410EventSink;

//0x1401f4160 - 14022A230
struct unk22A230Event {

};
DECLARE_EVENT_DISPATCHER(unk22A230Event, 0x22a230);

class unk22A230EventSink : public BSTEventSink<unk22A230Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk22A230Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk22A230Event:");
		return kEvent_Continue;
	}
};

unk22A230EventSink _unk22A230EventSink;

//0x140335c00 - 140337110
struct unk337110Event {

};
DECLARE_EVENT_DISPATCHER(unk337110Event, 0x337110);

class unk337110EventSink : public BSTEventSink<unk337110Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk337110Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk337110Event:");
		return kEvent_Continue;
	}
};

unk337110EventSink _unk337110EventSink;

//0x14033acf0 - 14033F6C0
struct unk33F6C0Event {

};
DECLARE_EVENT_DISPATCHER(unk33F6C0Event, 0x33f6c0);

class unk33F6C0EventSink : public BSTEventSink<unk33F6C0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk33F6C0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk33F6C0Event:");
		return kEvent_Continue;
	}
};

unk33F6C0EventSink _unk33F6C0EventSink;

//0x14037d380 - 140382500
struct unk382500Event {

};
DECLARE_EVENT_DISPATCHER(unk382500Event, 0x382500);

class unk382500EventSink : public BSTEventSink<unk382500Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk382500Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk382500Event:");
		return kEvent_Continue;
	}
};

unk382500EventSink _unk382500EventSink;

//0x14037d3e0 - 1403825D0
struct unk3825D0Event {

};
DECLARE_EVENT_DISPATCHER(unk3825D0Event, 0x3825d0);

class unk3825D0EventSink : public BSTEventSink<unk3825D0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk3825D0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk3825D0Event:");
		return kEvent_Continue;
	}
};

unk3825D0EventSink _unk3825D0EventSink;

//0x1403eb260 - 140414FC0
struct unk414FC0Event {

};
DECLARE_EVENT_DISPATCHER(unk414FC0Event, 0x414fc0);

class unk414FC0EventSink : public BSTEventSink<unk414FC0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk414FC0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk414FC0Event:");
		return kEvent_Continue;
	}
};

unk414FC0EventSink _unk414FC0EventSink;

//0x140434690 - 140441170
struct unk441170Event {

};
DECLARE_EVENT_DISPATCHER(unk441170Event, 0x441170);

class unk441170EventSink : public BSTEventSink<unk441170Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441170Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441170Event:");
		return kEvent_Continue;
	}
};

unk441170EventSink _unk441170EventSink;

//0x140434720 - 140444410
struct unk444410Event {

};
DECLARE_EVENT_DISPATCHER(unk444410Event, 0x444410);

class unk444410EventSink : public BSTEventSink<unk444410Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk444410Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk444410Event:");
		return kEvent_Continue;
	}
};

unk444410EventSink _unk444410EventSink;

//0x1404347e0 - 140441B70
struct unk441B70Event {

};
DECLARE_EVENT_DISPATCHER(unk441B70Event, 0x441b70);

class unk441B70EventSink : public BSTEventSink<unk441B70Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441B70Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441B70Event:");
		return kEvent_Continue;
	}
};

unk441B70EventSink _unk441B70EventSink;

//0x1404348e0 - 140442930
struct unk442930Event {

};
DECLARE_EVENT_DISPATCHER(unk442930Event, 0x442930);

class unk442930EventSink : public BSTEventSink<unk442930Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442930Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442930Event:");
		return kEvent_Continue;
	}
};

unk442930EventSink _unk442930EventSink;

//0x1404349e0 - 140441C10
struct unk441C10Event {

};
DECLARE_EVENT_DISPATCHER(unk441C10Event, 0x441c10);

class unk441C10EventSink : public BSTEventSink<unk441C10Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441C10Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441C10Event:");
		return kEvent_Continue;
	}
};

unk441C10EventSink _unk441C10EventSink;

//0x140434af0 - 140441CB0
struct unk441CB0Event {

};
DECLARE_EVENT_DISPATCHER(unk441CB0Event, 0x441cb0);

class unk441CB0EventSink : public BSTEventSink<unk441CB0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441CB0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441CB0Event:");
		return kEvent_Continue;
	}
};

unk441CB0EventSink _unk441CB0EventSink;

//0x140434bc0 - 140441D50
struct unk441D50Event {

};
DECLARE_EVENT_DISPATCHER(unk441D50Event, 0x441d50);

class unk441D50EventSink : public BSTEventSink<unk441D50Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441D50Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441D50Event:");
		return kEvent_Continue;
	}
};

unk441D50EventSink _unk441D50EventSink;

//0x140434cf0 - 140441DF0
struct unk441DF0Event {

};
DECLARE_EVENT_DISPATCHER(unk441DF0Event, 0x441df0);

class unk441DF0EventSink : public BSTEventSink<unk441DF0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441DF0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441DF0Event:");
		return kEvent_Continue;
	}
};

unk441DF0EventSink _unk441DF0EventSink;

//0x140434de0 - 140441E90
struct unk441E90Event {

};
DECLARE_EVENT_DISPATCHER(unk441E90Event, 0x441e90);

class unk441E90EventSink : public BSTEventSink<unk441E90Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441E90Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441E90Event:");
		return kEvent_Continue;
	}
};

unk441E90EventSink _unk441E90EventSink;

//0x140434ea0 - 140441F30
struct unk441F30Event {

};
DECLARE_EVENT_DISPATCHER(unk441F30Event, 0x441f30);

class unk441F30EventSink : public BSTEventSink<unk441F30Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441F30Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441F30Event:");
		return kEvent_Continue;
	}
};

unk441F30EventSink _unk441F30EventSink;

//0x140434f00 - 140441FD0
struct unk441FD0Event {

};
DECLARE_EVENT_DISPATCHER(unk441FD0Event, 0x441fd0);

class unk441FD0EventSink : public BSTEventSink<unk441FD0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441FD0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441FD0Event:");
		return kEvent_Continue;
	}
};

unk441FD0EventSink _unk441FD0EventSink;

//0x140435000 - 140442070
struct unk442070Event {

};
DECLARE_EVENT_DISPATCHER(unk442070Event, 0x442070);

class unk442070EventSink : public BSTEventSink<unk442070Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442070Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442070Event:");
		return kEvent_Continue;
	}
};

unk442070EventSink _unk442070EventSink;

//0x140435100 - 140442110
struct unk442110Event {

};
DECLARE_EVENT_DISPATCHER(unk442110Event, 0x442110);

class unk442110EventSink : public BSTEventSink<unk442110Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442110Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442110Event:");
		return kEvent_Continue;
	}
};

unk442110EventSink _unk442110EventSink;

//0x1404351c0 - 1404421B0
struct unk4421B0Event {

};
DECLARE_EVENT_DISPATCHER(unk4421B0Event, 0x4421b0);

class unk4421B0EventSink : public BSTEventSink<unk4421B0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4421B0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4421B0Event:");
		return kEvent_Continue;
	}
};

unk4421B0EventSink _unk4421B0EventSink;

//0x140435280 - 140442250
struct unk442250Event {

};
DECLARE_EVENT_DISPATCHER(unk442250Event, 0x442250);

class unk442250EventSink : public BSTEventSink<unk442250Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442250Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442250Event:");
		return kEvent_Continue;
	}
};

unk442250EventSink _unk442250EventSink;

//0x140435380 - 140442390
struct unk442390Event {

};
DECLARE_EVENT_DISPATCHER(unk442390Event, 0x442390);

class unk442390EventSink : public BSTEventSink<unk442390Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442390Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442390Event:");
		return kEvent_Continue;
	}
};

unk442390EventSink _unk442390EventSink;

//0x140435430 - 140441210
struct unk441210Event {

};
DECLARE_EVENT_DISPATCHER(unk441210Event, 0x441210);

class unk441210EventSink : public BSTEventSink<unk441210Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441210Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441210Event:");
		return kEvent_Continue;
	}
};

unk441210EventSink _unk441210EventSink;

//0x1404354c0 - 1404424D0
struct unk4424D0Event {

};
DECLARE_EVENT_DISPATCHER(unk4424D0Event, 0x4424d0);

class unk4424D0EventSink : public BSTEventSink<unk4424D0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4424D0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4424D0Event:");
		return kEvent_Continue;
	}
};

unk4424D0EventSink _unk4424D0EventSink;

//0x1404355c0 - 140442430
struct unk442430Event {

};
DECLARE_EVENT_DISPATCHER(unk442430Event, 0x442430);

class unk442430EventSink : public BSTEventSink<unk442430Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442430Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442430Event:");
		return kEvent_Continue;
	}
};

unk442430EventSink _unk442430EventSink;

//0x140435760 - 140442570
struct unk442570Event {

};
DECLARE_EVENT_DISPATCHER(unk442570Event, 0x442570);

class unk442570EventSink : public BSTEventSink<unk442570Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442570Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442570Event:");
		return kEvent_Continue;
	}
};

unk442570EventSink _unk442570EventSink;

//0x140435830 - 140442610
struct unk442610Event {

};
DECLARE_EVENT_DISPATCHER(unk442610Event, 0x442610);

class unk442610EventSink : public BSTEventSink<unk442610Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442610Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442610Event:");
		return kEvent_Continue;
	}
};

unk442610EventSink _unk442610EventSink;

//0x1404358f0 - 1404426B0
struct unk4426B0Event {

};
DECLARE_EVENT_DISPATCHER(unk4426B0Event, 0x4426b0);

class unk4426B0EventSink : public BSTEventSink<unk4426B0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4426B0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4426B0Event:");
		return kEvent_Continue;
	}
};

unk4426B0EventSink _unk4426B0EventSink;

//0x1404359b0 - 1404427F0
struct unk4427F0Event {

};
DECLARE_EVENT_DISPATCHER(unk4427F0Event, 0x4427f0);

class unk4427F0EventSink : public BSTEventSink<unk4427F0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4427F0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4427F0Event:");
		return kEvent_Continue;
	}
};

unk4427F0EventSink _unk4427F0EventSink;

//0x140435a70 - 140442890
struct unk442890Event {

};
DECLARE_EVENT_DISPATCHER(unk442890Event, 0x442890);

class unk442890EventSink : public BSTEventSink<unk442890Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442890Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442890Event:");
		return kEvent_Continue;
	}
};

unk442890EventSink _unk442890EventSink;

//0x140435b30 - 140442750
struct unk442750Event {

};
DECLARE_EVENT_DISPATCHER(unk442750Event, 0x442750);

class unk442750EventSink : public BSTEventSink<unk442750Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442750Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442750Event:");
		return kEvent_Continue;
	}
};

unk442750EventSink _unk442750EventSink;

//0x140435c10 - 1404429D0
struct unk4429D0Event {

};
DECLARE_EVENT_DISPATCHER(unk4429D0Event, 0x4429d0);

class unk4429D0EventSink : public BSTEventSink<unk4429D0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4429D0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4429D0Event:");
		return kEvent_Continue;
	}
};

unk4429D0EventSink _unk4429D0EventSink;

//0x140435c70 - 140442A70
struct unk442A70Event {

};
DECLARE_EVENT_DISPATCHER(unk442A70Event, 0x442a70);

class unk442A70EventSink : public BSTEventSink<unk442A70Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442A70Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442A70Event:");
		return kEvent_Continue;
	}
};

unk442A70EventSink _unk442A70EventSink;

//0x140435d30 - 140442B10
struct unk442B10Event {

};
DECLARE_EVENT_DISPATCHER(unk442B10Event, 0x442b10);

class unk442B10EventSink : public BSTEventSink<unk442B10Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442B10Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442B10Event:");
		return kEvent_Continue;
	}
};

unk442B10EventSink _unk442B10EventSink;

//0x140435e30 - 140442BB0
struct unk442BB0Event {

};
DECLARE_EVENT_DISPATCHER(unk442BB0Event, 0x442bb0);

class unk442BB0EventSink : public BSTEventSink<unk442BB0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442BB0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442BB0Event:");
		return kEvent_Continue;
	}
};

unk442BB0EventSink _unk442BB0EventSink;

//0x140435ef0 - 140444550
struct unk444550Event {

};
DECLARE_EVENT_DISPATCHER(unk444550Event, 0x444550);

class unk444550EventSink : public BSTEventSink<unk444550Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk444550Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk444550Event:");
		return kEvent_Continue;
	}
};

unk444550EventSink _unk444550EventSink;

//0x140436150 - 140441A30
struct unk441A30Event {

};
DECLARE_EVENT_DISPATCHER(unk441A30Event, 0x441a30);

class unk441A30EventSink : public BSTEventSink<unk441A30Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441A30Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441A30Event:");
		return kEvent_Continue;
	}
};

unk441A30EventSink _unk441A30EventSink;

//0x1404362a0 - 140441AD0
struct unk441AD0Event {

};
DECLARE_EVENT_DISPATCHER(unk441AD0Event, 0x441ad0);

class unk441AD0EventSink : public BSTEventSink<unk441AD0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441AD0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441AD0Event:");
		return kEvent_Continue;
	}
};

unk441AD0EventSink _unk441AD0EventSink;

//0x1404363a0 - 1404444B0
struct unk4444B0Event {

};
DECLARE_EVENT_DISPATCHER(unk4444B0Event, 0x4444b0);

class unk4444B0EventSink : public BSTEventSink<unk4444B0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4444B0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4444B0Event:");
		return kEvent_Continue;
	}
};

unk4444B0EventSink _unk4444B0EventSink;

//0x140436470 - 140442C50
struct unk442C50Event {

};
DECLARE_EVENT_DISPATCHER(unk442C50Event, 0x442c50);

class unk442C50EventSink : public BSTEventSink<unk442C50Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442C50Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442C50Event:");
		return kEvent_Continue;
	}
};

unk442C50EventSink _unk442C50EventSink;

//0x140436530 - 140442E30
struct unk442E30Event {

};
DECLARE_EVENT_DISPATCHER(unk442E30Event, 0x442e30);

class unk442E30EventSink : public BSTEventSink<unk442E30Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442E30Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442E30Event:");
		return kEvent_Continue;
	}
};

unk442E30EventSink _unk442E30EventSink;

//0x1404365c0 - 140442ED0
struct unk442ED0Event {

};
DECLARE_EVENT_DISPATCHER(unk442ED0Event, 0x442ed0);

class unk442ED0EventSink : public BSTEventSink<unk442ED0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442ED0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442ED0Event:");
		return kEvent_Continue;
	}
};

unk442ED0EventSink _unk442ED0EventSink;

//0x140436680 - 140442D90
struct unk442D90Event {

};
DECLARE_EVENT_DISPATCHER(unk442D90Event, 0x442d90);

class unk442D90EventSink : public BSTEventSink<unk442D90Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442D90Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442D90Event:");
		return kEvent_Continue;
	}
};

unk442D90EventSink _unk442D90EventSink;

//0x140436710 - 140442F70
struct unk442F70Event {

};
DECLARE_EVENT_DISPATCHER(unk442F70Event, 0x442f70);

class unk442F70EventSink : public BSTEventSink<unk442F70Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442F70Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442F70Event:");
		return kEvent_Continue;
	}
};

unk442F70EventSink _unk442F70EventSink;

//0x140436810 - 140443010
struct unk443010Event {

};
DECLARE_EVENT_DISPATCHER(unk443010Event, 0x443010);

class unk443010EventSink : public BSTEventSink<unk443010Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443010Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443010Event:");
		return kEvent_Continue;
	}
};

unk443010EventSink _unk443010EventSink;

//0x140436920 - 1404430B0
struct unk4430B0Event {

};
DECLARE_EVENT_DISPATCHER(unk4430B0Event, 0x4430b0);

class unk4430B0EventSink : public BSTEventSink<unk4430B0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4430B0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4430B0Event:");
		return kEvent_Continue;
	}
};

unk4430B0EventSink _unk4430B0EventSink;

//0x1404369b0 - 140443290
struct unk443290Event {

};
DECLARE_EVENT_DISPATCHER(unk443290Event, 0x443290);

class unk443290EventSink : public BSTEventSink<unk443290Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443290Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443290Event:");
		return kEvent_Continue;
	}
};

unk443290EventSink _unk443290EventSink;

//0x140436ab0 - 140443330
struct unk443330Event {

};
DECLARE_EVENT_DISPATCHER(unk443330Event, 0x443330);

class unk443330EventSink : public BSTEventSink<unk443330Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443330Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443330Event:");
		return kEvent_Continue;
	}
};

unk443330EventSink _unk443330EventSink;

//0x140436b80 - 1404433D0
struct unk4433D0Event {

};
DECLARE_EVENT_DISPATCHER(unk4433D0Event, 0x4433d0);

class unk4433D0EventSink : public BSTEventSink<unk4433D0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4433D0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4433D0Event:");
		return kEvent_Continue;
	}
};

unk4433D0EventSink _unk4433D0EventSink;

//0x140436c90 - 140443510
struct unk443510Event {

};
DECLARE_EVENT_DISPATCHER(unk443510Event, 0x443510);

class unk443510EventSink : public BSTEventSink<unk443510Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443510Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443510Event:");
		return kEvent_Continue;
	}
};

unk443510EventSink _unk443510EventSink;

//0x140436d50 - 1404435B0
struct unk4435B0Event {

};
DECLARE_EVENT_DISPATCHER(unk4435B0Event, 0x4435b0);

class unk4435B0EventSink : public BSTEventSink<unk4435B0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4435B0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4435B0Event:");
		return kEvent_Continue;
	}
};

unk4435B0EventSink _unk4435B0EventSink;

//0x140436de0 - 140443650
struct unk443650Event {

};
DECLARE_EVENT_DISPATCHER(unk443650Event, 0x443650);

class unk443650EventSink : public BSTEventSink<unk443650Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443650Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443650Event:");
		return kEvent_Continue;
	}
};

unk443650EventSink _unk443650EventSink;

//0x140436ea0 - 1404436F0
struct unk4436F0Event {

};
DECLARE_EVENT_DISPATCHER(unk4436F0Event, 0x4436f0);

class unk4436F0EventSink : public BSTEventSink<unk4436F0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4436F0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4436F0Event:");
		return kEvent_Continue;
	}
};

unk4436F0EventSink _unk4436F0EventSink;

//0x140436f30 - 140443790
struct unk443790Event {

};
DECLARE_EVENT_DISPATCHER(unk443790Event, 0x443790);

class unk443790EventSink : public BSTEventSink<unk443790Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443790Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443790Event:");
		return kEvent_Continue;
	}
};

unk443790EventSink _unk443790EventSink;

//0x140436fc0 - 140443830
struct unk443830Event {

};
DECLARE_EVENT_DISPATCHER(unk443830Event, 0x443830);

class unk443830EventSink : public BSTEventSink<unk443830Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443830Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443830Event:");
		return kEvent_Continue;
	}
};

unk443830EventSink _unk443830EventSink;

//0x140437080 - 1404438D0
struct unk4438D0Event {

};
DECLARE_EVENT_DISPATCHER(unk4438D0Event, 0x4438d0);

class unk4438D0EventSink : public BSTEventSink<unk4438D0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4438D0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4438D0Event:");
		return kEvent_Continue;
	}
};

unk4438D0EventSink _unk4438D0EventSink;

//0x140437110 - 140443A10
struct unk443A10Event {

};
DECLARE_EVENT_DISPATCHER(unk443A10Event, 0x443a10);

class unk443A10EventSink : public BSTEventSink<unk443A10Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443A10Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443A10Event:");
		return kEvent_Continue;
	}
};

unk443A10EventSink _unk443A10EventSink;

//0x1404371d0 - 140443970
struct unk443970Event {

};
DECLARE_EVENT_DISPATCHER(unk443970Event, 0x443970);

class unk443970EventSink : public BSTEventSink<unk443970Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443970Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443970Event:");
		return kEvent_Continue;
	}
};

unk443970EventSink _unk443970EventSink;

//0x1404372a0 - 140443AB0
struct unk443AB0Event {

};
DECLARE_EVENT_DISPATCHER(unk443AB0Event, 0x443ab0);

class unk443AB0EventSink : public BSTEventSink<unk443AB0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443AB0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443AB0Event:");
		return kEvent_Continue;
	}
};

unk443AB0EventSink _unk443AB0EventSink;

//0x140437370 - 140443B50
struct unk443B50Event {

};
DECLARE_EVENT_DISPATCHER(unk443B50Event, 0x443b50);

class unk443B50EventSink : public BSTEventSink<unk443B50Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443B50Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443B50Event:");
		return kEvent_Continue;
	}
};

unk443B50EventSink _unk443B50EventSink;

//0x140437440 - 140443BF0
struct unk443BF0Event {

};
DECLARE_EVENT_DISPATCHER(unk443BF0Event, 0x443bf0);

class unk443BF0EventSink : public BSTEventSink<unk443BF0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443BF0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443BF0Event:");
		return kEvent_Continue;
	}
};

unk443BF0EventSink _unk443BF0EventSink;

//0x140437540 - 140443C90
struct unk443C90Event {

};
DECLARE_EVENT_DISPATCHER(unk443C90Event, 0x443c90);

class unk443C90EventSink : public BSTEventSink<unk443C90Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443C90Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443C90Event:");
		return kEvent_Continue;
	}
};

unk443C90EventSink _unk443C90EventSink;

//0x140437630 - 140443D30
struct unk443D30Event {

};
DECLARE_EVENT_DISPATCHER(unk443D30Event, 0x443d30);

class unk443D30EventSink : public BSTEventSink<unk443D30Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443D30Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443D30Event:");
		return kEvent_Continue;
	}
};

unk443D30EventSink _unk443D30EventSink;

//0x1404376f0 - 140443E70
struct unk443E70Event {

};
DECLARE_EVENT_DISPATCHER(unk443E70Event, 0x443e70);

class unk443E70EventSink : public BSTEventSink<unk443E70Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443E70Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443E70Event:");
		return kEvent_Continue;
	}
};

unk443E70EventSink _unk443E70EventSink;

//0x1404377f0 - 140443F10
struct unk443F10Event {

};
DECLARE_EVENT_DISPATCHER(unk443F10Event, 0x443f10);

class unk443F10EventSink : public BSTEventSink<unk443F10Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443F10Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443F10Event:");
		return kEvent_Continue;
	}
};

unk443F10EventSink _unk443F10EventSink;

//0x1404378a0 - 140443150
struct unk443150Event {

};
DECLARE_EVENT_DISPATCHER(unk443150Event, 0x443150);

class unk443150EventSink : public BSTEventSink<unk443150Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443150Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443150Event:");
		return kEvent_Continue;
	}
};

unk443150EventSink _unk443150EventSink;

//0x140437960 - 140443FB0
struct unk443FB0Event {

};
DECLARE_EVENT_DISPATCHER(unk443FB0Event, 0x443fb0);

class unk443FB0EventSink : public BSTEventSink<unk443FB0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443FB0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443FB0Event:");
		return kEvent_Continue;
	}
};

unk443FB0EventSink _unk443FB0EventSink;

//0x140437aa0 - 1404440F0
struct unk4440F0Event {

};
DECLARE_EVENT_DISPATCHER(unk4440F0Event, 0x4440f0);

class unk4440F0EventSink : public BSTEventSink<unk4440F0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4440F0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4440F0Event:");
		return kEvent_Continue;
	}
};

unk4440F0EventSink _unk4440F0EventSink;

//0x140437ba0 - 140444050
struct unk444050Event {

};
DECLARE_EVENT_DISPATCHER(unk444050Event, 0x444050);

class unk444050EventSink : public BSTEventSink<unk444050Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk444050Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk444050Event:");
		return kEvent_Continue;
	}
};

unk444050EventSink _unk444050EventSink;

//0x140437ca0 - 140444190
struct unk444190Event {

};
DECLARE_EVENT_DISPATCHER(unk444190Event, 0x444190);

class unk444190EventSink : public BSTEventSink<unk444190Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk444190Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk444190Event:");
		return kEvent_Continue;
	}
};

unk444190EventSink _unk444190EventSink;

//0x140437da0 - 140444230
struct unk444230Event {

};
DECLARE_EVENT_DISPATCHER(unk444230Event, 0x444230);

class unk444230EventSink : public BSTEventSink<unk444230Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk444230Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk444230Event:");
		return kEvent_Continue;
	}
};

unk444230EventSink _unk444230EventSink;

//0x140437e40 - 1404442D0
struct unk4442D0Event {

};
DECLARE_EVENT_DISPATCHER(unk4442D0Event, 0x4442d0);

class unk4442D0EventSink : public BSTEventSink<unk4442D0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4442D0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4442D0Event:");
		return kEvent_Continue;
	}
};

unk4442D0EventSink _unk4442D0EventSink;

//0x140437ed0 - 140444370
struct unk444370Event {

};
DECLARE_EVENT_DISPATCHER(unk444370Event, 0x444370);

class unk444370EventSink : public BSTEventSink<unk444370Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk444370Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk444370Event:");
		return kEvent_Continue;
	}
};

unk444370EventSink _unk444370EventSink;

//0x140437f60 - 140443DD0
struct unk443DD0Event {

};
DECLARE_EVENT_DISPATCHER(unk443DD0Event, 0x443dd0);

class unk443DD0EventSink : public BSTEventSink<unk443DD0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443DD0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443DD0Event:");
		return kEvent_Continue;
	}
};

unk443DD0EventSink _unk443DD0EventSink;

//0x140438020 - 1404422F0
struct unk4422F0Event {

};
DECLARE_EVENT_DISPATCHER(unk4422F0Event, 0x4422f0);

class unk4422F0EventSink : public BSTEventSink<unk4422F0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4422F0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4422F0Event:");
		return kEvent_Continue;
	}
};

unk4422F0EventSink _unk4422F0EventSink;

//0x140438120 - 140442CF0
struct unk442CF0Event {

};
DECLARE_EVENT_DISPATCHER(unk442CF0Event, 0x442cf0);

class unk442CF0EventSink : public BSTEventSink<unk442CF0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk442CF0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk442CF0Event:");
		return kEvent_Continue;
	}
};

unk442CF0EventSink _unk442CF0EventSink;

//0x140438220 - 140443470
struct unk443470Event {

};
DECLARE_EVENT_DISPATCHER(unk443470Event, 0x443470);

class unk443470EventSink : public BSTEventSink<unk443470Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk443470Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk443470Event:");
		return kEvent_Continue;
	}
};

unk443470EventSink _unk443470EventSink;

//0x1404382e0 - 1404431F0
struct unk4431F0Event {

};
DECLARE_EVENT_DISPATCHER(unk4431F0Event, 0x4431f0);

class unk4431F0EventSink : public BSTEventSink<unk4431F0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4431F0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4431F0Event:");
		return kEvent_Continue;
	}
};

unk4431F0EventSink _unk4431F0EventSink;

//0x1404383a0 - 140441990
struct unk441990Event {

};
DECLARE_EVENT_DISPATCHER(unk441990Event, 0x441990);

class unk441990EventSink : public BSTEventSink<unk441990Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441990Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441990Event:");
		return kEvent_Continue;
	}
};

unk441990EventSink _unk441990EventSink;

//0x140438460 - 1404415D0
struct unk4415D0Event {

};
DECLARE_EVENT_DISPATCHER(unk4415D0Event, 0x4415d0);

class unk4415D0EventSink : public BSTEventSink<unk4415D0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4415D0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4415D0Event:");
		return kEvent_Continue;
	}
};

unk4415D0EventSink _unk4415D0EventSink;

//0x140438520 - 1404412B0
struct unk4412B0Event {

};
DECLARE_EVENT_DISPATCHER(unk4412B0Event, 0x4412b0);

class unk4412B0EventSink : public BSTEventSink<unk4412B0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4412B0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4412B0Event:");
		return kEvent_Continue;
	}
};

unk4412B0EventSink _unk4412B0EventSink;

//0x1404385e0 - 140441490
struct unk441490Event {

};
DECLARE_EVENT_DISPATCHER(unk441490Event, 0x441490);

class unk441490EventSink : public BSTEventSink<unk441490Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441490Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441490Event:");
		return kEvent_Continue;
	}
};

unk441490EventSink _unk441490EventSink;

//0x140438670 - 140441670
struct unk441670Event {

};
DECLARE_EVENT_DISPATCHER(unk441670Event, 0x441670);

class unk441670EventSink : public BSTEventSink<unk441670Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441670Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441670Event:");
		return kEvent_Continue;
	}
};

unk441670EventSink _unk441670EventSink;

//0x140438700 - 140441350
struct unk441350Event {

};
DECLARE_EVENT_DISPATCHER(unk441350Event, 0x441350);

class unk441350EventSink : public BSTEventSink<unk441350Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441350Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441350Event:");
		return kEvent_Continue;
	}
};

unk441350EventSink _unk441350EventSink;

//0x1404387c0 - 140441710
struct unk441710Event {

};
DECLARE_EVENT_DISPATCHER(unk441710Event, 0x441710);

class unk441710EventSink : public BSTEventSink<unk441710Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441710Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441710Event:");
		return kEvent_Continue;
	}
};

unk441710EventSink _unk441710EventSink;

//0x140438890 - 140441530
struct unk441530Event {

};
DECLARE_EVENT_DISPATCHER(unk441530Event, 0x441530);

class unk441530EventSink : public BSTEventSink<unk441530Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441530Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441530Event:");
		return kEvent_Continue;
	}
};

unk441530EventSink _unk441530EventSink;

//0x140438920 - 1404417B0
struct unk4417B0Event {

};
DECLARE_EVENT_DISPATCHER(unk4417B0Event, 0x4417b0);

class unk4417B0EventSink : public BSTEventSink<unk4417B0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4417B0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4417B0Event:");
		return kEvent_Continue;
	}
};

unk4417B0EventSink _unk4417B0EventSink;

//0x1404389b0 - 1404413F0
struct unk4413F0Event {

};
DECLARE_EVENT_DISPATCHER(unk4413F0Event, 0x4413f0);

class unk4413F0EventSink : public BSTEventSink<unk4413F0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4413F0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4413F0Event:");
		return kEvent_Continue;
	}
};

unk4413F0EventSink _unk4413F0EventSink;

//0x140438a70 - 140441850
struct unk441850Event {

};
DECLARE_EVENT_DISPATCHER(unk441850Event, 0x441850);

class unk441850EventSink : public BSTEventSink<unk441850Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk441850Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk441850Event:");
		return kEvent_Continue;
	}
};

unk441850EventSink _unk441850EventSink;

//0x140438b30 - 1404418F0
struct unk4418F0Event {

};
DECLARE_EVENT_DISPATCHER(unk4418F0Event, 0x4418f0);

class unk4418F0EventSink : public BSTEventSink<unk4418F0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4418F0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4418F0Event:");
		return kEvent_Continue;
	}
};

unk4418F0EventSink _unk4418F0EventSink;

//0x1404a8d00 - 1404A9180
struct unk4A9180Event {

};
DECLARE_EVENT_DISPATCHER(unk4A9180Event, 0x4a9180);

class unk4A9180EventSink : public BSTEventSink<unk4A9180Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk4A9180Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk4A9180Event:");
		return kEvent_Continue;
	}
};

unk4A9180EventSink _unk4A9180EventSink;

//0x14056f1b0 - 140571770
struct unk571770Event {

};
DECLARE_EVENT_DISPATCHER(unk571770Event, 0x571770);

class unk571770EventSink : public BSTEventSink<unk571770Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk571770Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk571770Event:");
		return kEvent_Continue;
	}
};

unk571770EventSink _unk571770EventSink;

//0x140577ab0 - 140577BB0
struct unk577BB0Event {

};
DECLARE_EVENT_DISPATCHER(unk577BB0Event, 0x577bb0);

class unk577BB0EventSink : public BSTEventSink<unk577BB0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk577BB0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk577BB0Event:");
		return kEvent_Continue;
	}
};

unk577BB0EventSink _unk577BB0EventSink;

//0x1405d3fe0 - 1405E2E10
struct unk5E2E10Event {

};
DECLARE_EVENT_DISPATCHER(unk5E2E10Event, 0x5e2e10);

class unk5E2E10EventSink : public BSTEventSink<unk5E2E10Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk5E2E10Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk5E2E10Event:");
		return kEvent_Continue;
	}
};

unk5E2E10EventSink _unk5E2E10EventSink;

//0x1405d4070 - 1405E2EB0
struct unk5E2EB0Event {

};
DECLARE_EVENT_DISPATCHER(unk5E2EB0Event, 0x5e2eb0);

class unk5E2EB0EventSink : public BSTEventSink<unk5E2EB0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk5E2EB0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk5E2EB0Event:");
		return kEvent_Continue;
	}
};

unk5E2EB0EventSink _unk5E2EB0EventSink;

//0x140b85910 - 140B88420
struct unkB88420Event {

};
DECLARE_EVENT_DISPATCHER(unkB88420Event, 0xb88420);

class unkB88420EventSink : public BSTEventSink<unkB88420Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkB88420Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkB88420Event:");
		return kEvent_Continue;
	}
};

unkB88420EventSink _unkB88420EventSink;

//0x140b859a0 - 140B884C0
struct unkB884C0Event {

};
DECLARE_EVENT_DISPATCHER(unkB884C0Event, 0xb884c0);

class unkB884C0EventSink : public BSTEventSink<unkB884C0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkB884C0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkB884C0Event:");
		return kEvent_Continue;
	}
};

unkB884C0EventSink _unkB884C0EventSink;

//0x140b85a30 - 140B88560
struct unkB88560Event {

};
DECLARE_EVENT_DISPATCHER(unkB88560Event, 0xb88560);

class unkB88560EventSink : public BSTEventSink<unkB88560Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkB88560Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkB88560Event:");
		return kEvent_Continue;
	}
};

unkB88560EventSink _unkB88560EventSink;

//0x140bb8530 - 140BB85C0
struct unkBB85C0Event {

};
DECLARE_EVENT_DISPATCHER(unkBB85C0Event, 0xbb85c0);

class unkBB85C0EventSink : public BSTEventSink<unkBB85C0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkBB85C0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkBB85C0Event:");
		return kEvent_Continue;
	}
};

unkBB85C0EventSink _unkBB85C0EventSink;

//0x140d1d5a0 - 140D1E500
struct unkD1E500Event {

};
DECLARE_EVENT_DISPATCHER(unkD1E500Event, 0xd1e500);

class unkD1E500EventSink : public BSTEventSink<unkD1E500Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkD1E500Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkD1E500Event:");
		return kEvent_Continue;
	}
};

unkD1E500EventSink _unkD1E500EventSink;

//0x140d1d600 - 140D1E5D0
struct unkD1E5D0Event {

};
DECLARE_EVENT_DISPATCHER(unkD1E5D0Event, 0xd1e5d0);

class unkD1E5D0EventSink : public BSTEventSink<unkD1E5D0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkD1E5D0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkD1E5D0Event:");
		return kEvent_Continue;
	}
};

unkD1E5D0EventSink _unkD1E5D0EventSink;

//0x140d6d8b0 - 140DC5E10
struct unkDC5E10Event {

};
DECLARE_EVENT_DISPATCHER(unkDC5E10Event, 0xdc5e10);

class unkDC5E10EventSink : public BSTEventSink<unkDC5E10Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkDC5E10Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkDC5E10Event:");
		return kEvent_Continue;
	}
};

unkDC5E10EventSink _unkDC5E10EventSink;

//0x140d6d910 - 140DC5EF0
struct unkDC5EF0Event {

};
DECLARE_EVENT_DISPATCHER(unkDC5EF0Event, 0xdc5ef0);

class unkDC5EF0EventSink : public BSTEventSink<unkDC5EF0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkDC5EF0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkDC5EF0Event:");
		return kEvent_Continue;
	}
};

unkDC5EF0EventSink _unkDC5EF0EventSink;

//0x140d6d970 - 140DC6170
struct unkDC6170Event {

};
DECLARE_EVENT_DISPATCHER(unkDC6170Event, 0xdc6170);

class unkDC6170EventSink : public BSTEventSink<unkDC6170Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkDC6170Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkDC6170Event:");
		return kEvent_Continue;
	}
};

unkDC6170EventSink _unkDC6170EventSink;

//0x140d6d9d0 - 140DC6240
struct unkDC6240Event {

};
DECLARE_EVENT_DISPATCHER(unkDC6240Event, 0xdc6240);

class unkDC6240EventSink : public BSTEventSink<unkDC6240Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkDC6240Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkDC6240Event:");
		return kEvent_Continue;
	}
};

unkDC6240EventSink _unkDC6240EventSink;

//0x140d6da30 - 140DC6310
struct unkDC6310Event {

};
DECLARE_EVENT_DISPATCHER(unkDC6310Event, 0xdc6310);

class unkDC6310EventSink : public BSTEventSink<unkDC6310Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkDC6310Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkDC6310Event:");
		return kEvent_Continue;
	}
};

unkDC6310EventSink _unkDC6310EventSink;

//0x140d6da90 - 140DC5FC0
struct unkDC5FC0Event {

};
DECLARE_EVENT_DISPATCHER(unkDC5FC0Event, 0xdc5fc0);

class unkDC5FC0EventSink : public BSTEventSink<unkDC5FC0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkDC5FC0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkDC5FC0Event:");
		return kEvent_Continue;
	}
};

unkDC5FC0EventSink _unkDC5FC0EventSink;

//0x140d6daf0 - 140DC60A0
struct unkDC60A0Event {

};
DECLARE_EVENT_DISPATCHER(unkDC60A0Event, 0xdc60a0);

class unkDC60A0EventSink : public BSTEventSink<unkDC60A0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkDC60A0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkDC60A0Event:");
		return kEvent_Continue;
	}
};

unkDC60A0EventSink _unkDC60A0EventSink;

//0x140df5fc0 - 140DF9580
struct unkDF9580Event {

};
DECLARE_EVENT_DISPATCHER(unkDF9580Event, 0xdf9580);

class unkDF9580EventSink : public BSTEventSink<unkDF9580Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkDF9580Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkDF9580Event:");
		return kEvent_Continue;
	}
};

unkDF9580EventSink _unkDF9580EventSink;

//0x140dfc8a0 - 140E07A10
struct unkE07A10Event {

};
DECLARE_EVENT_DISPATCHER(unkE07A10Event, 0xe07a10);

class unkE07A10EventSink : public BSTEventSink<unkE07A10Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkE07A10Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkE07A10Event:");
		return kEvent_Continue;
	}
};

unkE07A10EventSink _unkE07A10EventSink;

//0x140dfc930 - 140E07AB0
struct unkE07AB0Event {

};
DECLARE_EVENT_DISPATCHER(unkE07AB0Event, 0xe07ab0);

class unkE07AB0EventSink : public BSTEventSink<unkE07AB0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkE07AB0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkE07AB0Event:");
		return kEvent_Continue;
	}
};

unkE07AB0EventSink _unkE07AB0EventSink;

//0x140e10600 - 140E15EA0
struct unkE15EA0Event {

};
DECLARE_EVENT_DISPATCHER(unkE15EA0Event, 0xe15ea0);

class unkE15EA0EventSink : public BSTEventSink<unkE15EA0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkE15EA0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkE15EA0Event:");
		return kEvent_Continue;
	}
};

unkE15EA0EventSink _unkE15EA0EventSink;

//0x140e10660 - 140E15F80
struct unkE15F80Event {

};
DECLARE_EVENT_DISPATCHER(unkE15F80Event, 0xe15f80);

class unkE15F80EventSink : public BSTEventSink<unkE15F80Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkE15F80Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkE15F80Event:");
		return kEvent_Continue;
	}
};

unkE15F80EventSink _unkE15F80EventSink;

//0x140e959b0 - 140EC2400
struct unkEC2400Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2400Event, 0xec2400);

class unkEC2400EventSink : public BSTEventSink<unkEC2400Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2400Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2400Event:");
		return kEvent_Continue;
	}
};

unkEC2400EventSink _unkEC2400EventSink;

//0x140e95a10 - 140EC24E0
struct unkEC24E0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC24E0Event, 0xec24e0);

class unkEC24E0EventSink : public BSTEventSink<unkEC24E0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC24E0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC24E0Event:");
		return kEvent_Continue;
	}
};

unkEC24E0EventSink _unkEC24E0EventSink;

//0x140e95aa0 - 140EC2580
struct unkEC2580Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2580Event, 0xec2580);

class unkEC2580EventSink : public BSTEventSink<unkEC2580Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2580Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2580Event:");
		return kEvent_Continue;
	}
};

unkEC2580EventSink _unkEC2580EventSink;

//0x140e95b30 - 140EC2620
struct unkEC2620Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2620Event, 0xec2620);

class unkEC2620EventSink : public BSTEventSink<unkEC2620Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2620Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2620Event:");
		return kEvent_Continue;
	}
};

unkEC2620EventSink _unkEC2620EventSink;

//0x140e95bc0 - 140EC26C0
struct unkEC26C0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC26C0Event, 0xec26c0);

class unkEC26C0EventSink : public BSTEventSink<unkEC26C0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC26C0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC26C0Event:");
		return kEvent_Continue;
	}
};

unkEC26C0EventSink _unkEC26C0EventSink;

//0x140e95c50 - 140EC2760
struct unkEC2760Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2760Event, 0xec2760);

class unkEC2760EventSink : public BSTEventSink<unkEC2760Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2760Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2760Event:");
		return kEvent_Continue;
	}
};

unkEC2760EventSink _unkEC2760EventSink;

//0x140e95ce0 - 140EC2800
struct unkEC2800Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2800Event, 0xec2800);

class unkEC2800EventSink : public BSTEventSink<unkEC2800Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2800Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2800Event:");
		return kEvent_Continue;
	}
};

unkEC2800EventSink _unkEC2800EventSink;

//0x140e95d70 - 140EC28A0
struct unkEC28A0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC28A0Event, 0xec28a0);

class unkEC28A0EventSink : public BSTEventSink<unkEC28A0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC28A0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC28A0Event:");
		return kEvent_Continue;
	}
};

unkEC28A0EventSink _unkEC28A0EventSink;

//0x140e95e00 - 140EC2940
struct unkEC2940Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2940Event, 0xec2940);

class unkEC2940EventSink : public BSTEventSink<unkEC2940Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2940Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2940Event:");
		return kEvent_Continue;
	}
};

unkEC2940EventSink _unkEC2940EventSink;

//0x140e95e90 - 140EC29E0
struct unkEC29E0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC29E0Event, 0xec29e0);

class unkEC29E0EventSink : public BSTEventSink<unkEC29E0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC29E0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC29E0Event:");
		return kEvent_Continue;
	}
};

unkEC29E0EventSink _unkEC29E0EventSink;

//0x140e95f20 - 140EC2A80
struct unkEC2A80Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2A80Event, 0xec2a80);

class unkEC2A80EventSink : public BSTEventSink<unkEC2A80Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2A80Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2A80Event:");
		return kEvent_Continue;
	}
};

unkEC2A80EventSink _unkEC2A80EventSink;

//0x140e95fb0 - 140EC2B20
struct unkEC2B20Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2B20Event, 0xec2b20);

class unkEC2B20EventSink : public BSTEventSink<unkEC2B20Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2B20Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2B20Event:");
		return kEvent_Continue;
	}
};

unkEC2B20EventSink _unkEC2B20EventSink;

//0x140e96040 - 140EC2BC0
struct unkEC2BC0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2BC0Event, 0xec2bc0);

class unkEC2BC0EventSink : public BSTEventSink<unkEC2BC0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2BC0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2BC0Event:");
		return kEvent_Continue;
	}
};

unkEC2BC0EventSink _unkEC2BC0EventSink;

//0x140e960d0 - 140EC2C60
struct unkEC2C60Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2C60Event, 0xec2c60);

class unkEC2C60EventSink : public BSTEventSink<unkEC2C60Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2C60Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2C60Event:");
		return kEvent_Continue;
	}
};

unkEC2C60EventSink _unkEC2C60EventSink;

//0x140e96160 - 140EC2D00
struct unkEC2D00Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2D00Event, 0xec2d00);

class unkEC2D00EventSink : public BSTEventSink<unkEC2D00Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2D00Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2D00Event:");
		return kEvent_Continue;
	}
};

unkEC2D00EventSink _unkEC2D00EventSink;

//0x140e961f0 - 140EC2DA0
struct unkEC2DA0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2DA0Event, 0xec2da0);

class unkEC2DA0EventSink : public BSTEventSink<unkEC2DA0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2DA0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2DA0Event:");
		return kEvent_Continue;
	}
};

unkEC2DA0EventSink _unkEC2DA0EventSink;

//0x140e96280 - 140EC2E40
struct unkEC2E40Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2E40Event, 0xec2e40);

class unkEC2E40EventSink : public BSTEventSink<unkEC2E40Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2E40Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2E40Event:");
		return kEvent_Continue;
	}
};

unkEC2E40EventSink _unkEC2E40EventSink;

//0x140e96310 - 140EC2EE0
struct unkEC2EE0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2EE0Event, 0xec2ee0);

class unkEC2EE0EventSink : public BSTEventSink<unkEC2EE0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2EE0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2EE0Event:");
		return kEvent_Continue;
	}
};

unkEC2EE0EventSink _unkEC2EE0EventSink;

//0x140e963a0 - 140EC2F80
struct unkEC2F80Event {

};
DECLARE_EVENT_DISPATCHER(unkEC2F80Event, 0xec2f80);

class unkEC2F80EventSink : public BSTEventSink<unkEC2F80Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC2F80Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC2F80Event:");
		return kEvent_Continue;
	}
};

unkEC2F80EventSink _unkEC2F80EventSink;

//0x140e96430 - 140EC3020
struct unkEC3020Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3020Event, 0xec3020);

class unkEC3020EventSink : public BSTEventSink<unkEC3020Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3020Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3020Event:");
		return kEvent_Continue;
	}
};

unkEC3020EventSink _unkEC3020EventSink;

//0x140e964c0 - 140EC30C0
struct unkEC30C0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC30C0Event, 0xec30c0);

class unkEC30C0EventSink : public BSTEventSink<unkEC30C0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC30C0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC30C0Event:");
		return kEvent_Continue;
	}
};

unkEC30C0EventSink _unkEC30C0EventSink;

//0x140e96550 - 140EC3160
struct unkEC3160Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3160Event, 0xec3160);

class unkEC3160EventSink : public BSTEventSink<unkEC3160Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3160Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3160Event:");
		return kEvent_Continue;
	}
};

unkEC3160EventSink _unkEC3160EventSink;

//0x140e965e0 - 140EC3200
struct unkEC3200Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3200Event, 0xec3200);

class unkEC3200EventSink : public BSTEventSink<unkEC3200Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3200Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3200Event:");
		return kEvent_Continue;
	}
};

unkEC3200EventSink _unkEC3200EventSink;

//0x140e96670 - 140EC32A0
struct unkEC32A0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC32A0Event, 0xec32a0);

class unkEC32A0EventSink : public BSTEventSink<unkEC32A0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC32A0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC32A0Event:");
		return kEvent_Continue;
	}
};

unkEC32A0EventSink _unkEC32A0EventSink;

//0x140e96700 - 140EC3340
struct unkEC3340Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3340Event, 0xec3340);

class unkEC3340EventSink : public BSTEventSink<unkEC3340Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3340Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3340Event:");
		return kEvent_Continue;
	}
};

unkEC3340EventSink _unkEC3340EventSink;

//0x140e96790 - 140EC33E0
struct unkEC33E0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC33E0Event, 0xec33e0);

class unkEC33E0EventSink : public BSTEventSink<unkEC33E0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC33E0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC33E0Event:");
		return kEvent_Continue;
	}
};

unkEC33E0EventSink _unkEC33E0EventSink;

//0x140e96820 - 140EC3480
struct unkEC3480Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3480Event, 0xec3480);

class unkEC3480EventSink : public BSTEventSink<unkEC3480Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3480Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3480Event:");
		return kEvent_Continue;
	}
};

unkEC3480EventSink _unkEC3480EventSink;

//0x140e968b0 - 140EC3520
struct unkEC3520Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3520Event, 0xec3520);

class unkEC3520EventSink : public BSTEventSink<unkEC3520Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3520Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3520Event:");
		return kEvent_Continue;
	}
};

unkEC3520EventSink _unkEC3520EventSink;

//0x140e96940 - 140EC35C0
struct unkEC35C0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC35C0Event, 0xec35c0);

class unkEC35C0EventSink : public BSTEventSink<unkEC35C0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC35C0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC35C0Event:");
		return kEvent_Continue;
	}
};

unkEC35C0EventSink _unkEC35C0EventSink;

//0x140e969d0 - 140EC3660
struct unkEC3660Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3660Event, 0xec3660);

class unkEC3660EventSink : public BSTEventSink<unkEC3660Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3660Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3660Event:");
		return kEvent_Continue;
	}
};

unkEC3660EventSink _unkEC3660EventSink;

//0x140e96a60 - 140EC3700
struct unkEC3700Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3700Event, 0xec3700);

class unkEC3700EventSink : public BSTEventSink<unkEC3700Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3700Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3700Event:");
		return kEvent_Continue;
	}
};

unkEC3700EventSink _unkEC3700EventSink;

//0x140e96af0 - 140EC37A0
struct unkEC37A0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC37A0Event, 0xec37a0);

class unkEC37A0EventSink : public BSTEventSink<unkEC37A0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC37A0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC37A0Event:");
		return kEvent_Continue;
	}
};

unkEC37A0EventSink _unkEC37A0EventSink;

//0x140e96b80 - 140EC3840
struct unkEC3840Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3840Event, 0xec3840);

class unkEC3840EventSink : public BSTEventSink<unkEC3840Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3840Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3840Event:");
		return kEvent_Continue;
	}
};

unkEC3840EventSink _unkEC3840EventSink;

//0x140e96c10 - 140EC38E0
struct unkEC38E0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC38E0Event, 0xec38e0);

class unkEC38E0EventSink : public BSTEventSink<unkEC38E0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC38E0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC38E0Event:");
		return kEvent_Continue;
	}
};

unkEC38E0EventSink _unkEC38E0EventSink;

//0x140e96ca0 - 140EC3980
struct unkEC3980Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3980Event, 0xec3980);

class unkEC3980EventSink : public BSTEventSink<unkEC3980Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3980Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3980Event:");
		return kEvent_Continue;
	}
};

unkEC3980EventSink _unkEC3980EventSink;

//0x140e96d40 - 140EC3A20
struct unkEC3A20Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3A20Event, 0xec3a20);

class unkEC3A20EventSink : public BSTEventSink<unkEC3A20Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3A20Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3A20Event:");
		return kEvent_Continue;
	}
};

unkEC3A20EventSink _unkEC3A20EventSink;

//0x140e96da0 - 140EC3AF0
struct unkEC3AF0Event {

};
DECLARE_EVENT_DISPATCHER(unkEC3AF0Event, 0xec3af0);

class unkEC3AF0EventSink : public BSTEventSink<unkEC3AF0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkEC3AF0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkEC3AF0Event:");
		return kEvent_Continue;
	}
};

unkEC3AF0EventSink _unkEC3AF0EventSink;

//0x140e971f0 - 140E97250
struct unkE97250Event {

};
DECLARE_EVENT_DISPATCHER(unkE97250Event, 0xe97250);

class unkE97250EventSink : public BSTEventSink<unkE97250Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkE97250Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkE97250Event:");
		return kEvent_Continue;
	}
};

unkE97250EventSink _unkE97250EventSink;

//0x140f421c0 - 140F45BF0
struct unkF45BF0Event {

};
DECLARE_EVENT_DISPATCHER(unkF45BF0Event, 0xf45bf0);

class unkF45BF0EventSink : public BSTEventSink<unkF45BF0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkF45BF0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkF45BF0Event:");
		return kEvent_Continue;
	}
};

unkF45BF0EventSink _unkF45BF0EventSink;

//0x140f5bad0 - 140F5BF80
struct unkF5BF80Event {

};
DECLARE_EVENT_DISPATCHER(unkF5BF80Event, 0xf5bf80);

class unkF5BF80EventSink : public BSTEventSink<unkF5BF80Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkF5BF80Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkF5BF80Event:");
		return kEvent_Continue;
	}
};

unkF5BF80EventSink _unkF5BF80EventSink;

//0x140fc8090 - 140FD97D0
struct unkFD97D0Event {

};
DECLARE_EVENT_DISPATCHER(unkFD97D0Event, 0xfd97d0);

class unkFD97D0EventSink : public BSTEventSink<unkFD97D0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkFD97D0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkFD97D0Event:");
		return kEvent_Continue;
	}
};

unkFD97D0EventSink _unkFD97D0EventSink;

//0x140fe7300 - 240FE7230
struct unkFE7300Event {

};
DECLARE_EVENT_DISPATCHER(unkFE7300Event, 0xfe7300);

class unkFE7300EventSink : public BSTEventSink<unkFE7300Event>
{
public:
	virtual	EventResult	ReceiveEvent(unkFE7300Event * evn, void * dispatcher) override
	{
		_MESSAGE("unkFE7300Event:");
		return kEvent_Continue;
	}
};

unkFE7300EventSink _unkFE7300EventSink;

//0x141279c60 - 14127DB30
struct unk127DB30Event {

};
DECLARE_EVENT_DISPATCHER(unk127DB30Event, 0x127db30);

class unk127DB30EventSink : public BSTEventSink<unk127DB30Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk127DB30Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk127DB30Event:");
		return kEvent_Continue;
	}
};

unk127DB30EventSink _unk127DB30EventSink;

//0x141279cf0 - 14127DBD0
struct unk127DBD0Event {

};
DECLARE_EVENT_DISPATCHER(unk127DBD0Event, 0x127dbd0);

class unk127DBD0EventSink : public BSTEventSink<unk127DBD0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk127DBD0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk127DBD0Event:");
		return kEvent_Continue;
	}
};

unk127DBD0EventSink _unk127DBD0EventSink;

//0x14129bf30 - 14129EC30
struct unk129EC30Event {

};
DECLARE_EVENT_DISPATCHER(unk129EC30Event, 0x129ec30);

class unk129EC30EventSink : public BSTEventSink<unk129EC30Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk129EC30Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk129EC30Event:");
		return kEvent_Continue;
	}
};

unk129EC30EventSink _unk129EC30EventSink;

//0x1412b0a20 - 1412B1800
struct unk12B1800Event {

};
DECLARE_EVENT_DISPATCHER(unk12B1800Event, 0x12b1800);

class unk12B1800EventSink : public BSTEventSink<unk12B1800Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk12B1800Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk12B1800Event:");
		return kEvent_Continue;
	}
};

unk12B1800EventSink _unk12B1800EventSink;

//0x141b0dd00 - 141B0FDF0
struct unk1B0FDF0Event {

};
DECLARE_EVENT_DISPATCHER(unk1B0FDF0Event, 0x1b0fdf0);

class unk1B0FDF0EventSink : public BSTEventSink<unk1B0FDF0Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk1B0FDF0Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk1B0FDF0Event:");
		return kEvent_Continue;
	}
};

unk1B0FDF0EventSink _unk1B0FDF0EventSink;

//0x141b15b80 - 141B16400
struct unk1B16400Event {

};
DECLARE_EVENT_DISPATCHER(unk1B16400Event, 0x1b16400);

class unk1B16400EventSink : public BSTEventSink<unk1B16400Event>
{
public:
	virtual	EventResult	ReceiveEvent(unk1B16400Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk1B16400Event:");
		return kEvent_Continue;
	}
};

unk1B16400EventSink _unk1B16400EventSink;

void testreg()
{
	GetEventDispatcher<unk100E80Event>()->AddEventSink(&_unk100E80EventSink);
_MESSAGE("unk100E80Event: registered");
GetEventDispatcher<unk10B730Event>()->AddEventSink(&_unk10B730EventSink);
_MESSAGE("unk10B730Event: registered");
GetEventDispatcher<unk162970Event>()->AddEventSink(&_unk162970EventSink);
_MESSAGE("unk162970Event: registered");
GetEventDispatcher<unk1A8D90Event>()->AddEventSink(&_unk1A8D90EventSink);
_MESSAGE("unk1A8D90Event: registered");
GetEventDispatcher<unk229FB0Event>()->AddEventSink(&_unk229FB0EventSink);
_MESSAGE("unk229FB0Event: registered");
GetEventDispatcher<unk22A050Event>()->AddEventSink(&_unk22A050EventSink);
_MESSAGE("unk22A050Event: registered");
GetEventDispatcher<unk229DD0Event>()->AddEventSink(&_unk229DD0EventSink);
_MESSAGE("unk229DD0Event: registered");
GetEventDispatcher<unk229F10Event>()->AddEventSink(&_unk229F10EventSink);
_MESSAGE("unk229F10Event: registered");
GetEventDispatcher<unk229E70Event>()->AddEventSink(&_unk229E70EventSink);
_MESSAGE("unk229E70Event: registered");
GetEventDispatcher<unk22A370Event>()->AddEventSink(&_unk22A370EventSink);
_MESSAGE("unk22A370Event: registered");
GetEventDispatcher<unk22A2D0Event>()->AddEventSink(&_unk22A2D0EventSink);
_MESSAGE("unk22A2D0Event: registered");
GetEventDispatcher<unk229D30Event>()->AddEventSink(&_unk229D30EventSink);
_MESSAGE("unk229D30Event: registered");
GetEventDispatcher<unk22A190Event>()->AddEventSink(&_unk22A190EventSink);
_MESSAGE("unk22A190Event: registered");
GetEventDispatcher<unk22A0F0Event>()->AddEventSink(&_unk22A0F0EventSink);
_MESSAGE("unk22A0F0Event: registered");
GetEventDispatcher<unk22A410Event>()->AddEventSink(&_unk22A410EventSink);
_MESSAGE("unk22A410Event: registered");
GetEventDispatcher<unk22A230Event>()->AddEventSink(&_unk22A230EventSink);
_MESSAGE("unk22A230Event: registered");
GetEventDispatcher<unk337110Event>()->AddEventSink(&_unk337110EventSink);
_MESSAGE("unk337110Event: registered");
GetEventDispatcher<unk33F6C0Event>()->AddEventSink(&_unk33F6C0EventSink);
_MESSAGE("unk33F6C0Event: registered");
GetEventDispatcher<unk382500Event>()->AddEventSink(&_unk382500EventSink);
_MESSAGE("unk382500Event: registered");
GetEventDispatcher<unk3825D0Event>()->AddEventSink(&_unk3825D0EventSink);
_MESSAGE("unk3825D0Event: registered");
GetEventDispatcher<unk414FC0Event>()->AddEventSink(&_unk414FC0EventSink);
_MESSAGE("unk414FC0Event: registered");
GetEventDispatcher<unk441170Event>()->AddEventSink(&_unk441170EventSink);
_MESSAGE("unk441170Event: registered");
GetEventDispatcher<unk444410Event>()->AddEventSink(&_unk444410EventSink);
_MESSAGE("unk444410Event: registered");
GetEventDispatcher<unk441B70Event>()->AddEventSink(&_unk441B70EventSink);
_MESSAGE("unk441B70Event: registered");
GetEventDispatcher<unk442930Event>()->AddEventSink(&_unk442930EventSink);
_MESSAGE("unk442930Event: registered");
GetEventDispatcher<unk441C10Event>()->AddEventSink(&_unk441C10EventSink);
_MESSAGE("unk441C10Event: registered");
GetEventDispatcher<unk441CB0Event>()->AddEventSink(&_unk441CB0EventSink);
_MESSAGE("unk441CB0Event: registered");
GetEventDispatcher<unk441D50Event>()->AddEventSink(&_unk441D50EventSink);
_MESSAGE("unk441D50Event: registered");
GetEventDispatcher<unk441DF0Event>()->AddEventSink(&_unk441DF0EventSink);
_MESSAGE("unk441DF0Event: registered");
GetEventDispatcher<unk441E90Event>()->AddEventSink(&_unk441E90EventSink);
_MESSAGE("unk441E90Event: registered");
GetEventDispatcher<unk441F30Event>()->AddEventSink(&_unk441F30EventSink);
_MESSAGE("unk441F30Event: registered");
GetEventDispatcher<unk441FD0Event>()->AddEventSink(&_unk441FD0EventSink);
_MESSAGE("unk441FD0Event: registered");
GetEventDispatcher<unk442070Event>()->AddEventSink(&_unk442070EventSink);
_MESSAGE("unk442070Event: registered");
GetEventDispatcher<unk442110Event>()->AddEventSink(&_unk442110EventSink);
_MESSAGE("unk442110Event: registered");
GetEventDispatcher<unk4421B0Event>()->AddEventSink(&_unk4421B0EventSink);
_MESSAGE("unk4421B0Event: registered");
GetEventDispatcher<unk442250Event>()->AddEventSink(&_unk442250EventSink);
_MESSAGE("unk442250Event: registered");
GetEventDispatcher<unk442390Event>()->AddEventSink(&_unk442390EventSink);
_MESSAGE("unk442390Event: registered");
GetEventDispatcher<unk441210Event>()->AddEventSink(&_unk441210EventSink);
_MESSAGE("unk441210Event: registered");
GetEventDispatcher<unk4424D0Event>()->AddEventSink(&_unk4424D0EventSink);
_MESSAGE("unk4424D0Event: registered");
GetEventDispatcher<unk442430Event>()->AddEventSink(&_unk442430EventSink);
_MESSAGE("unk442430Event: registered");
GetEventDispatcher<unk442570Event>()->AddEventSink(&_unk442570EventSink);
_MESSAGE("unk442570Event: registered");
GetEventDispatcher<unk442610Event>()->AddEventSink(&_unk442610EventSink);
_MESSAGE("unk442610Event: registered");
GetEventDispatcher<unk4426B0Event>()->AddEventSink(&_unk4426B0EventSink);
_MESSAGE("unk4426B0Event: registered");
GetEventDispatcher<unk4427F0Event>()->AddEventSink(&_unk4427F0EventSink);
_MESSAGE("unk4427F0Event: registered");
GetEventDispatcher<unk442890Event>()->AddEventSink(&_unk442890EventSink);
_MESSAGE("unk442890Event: registered");
GetEventDispatcher<unk442750Event>()->AddEventSink(&_unk442750EventSink);
_MESSAGE("unk442750Event: registered");
GetEventDispatcher<unk4429D0Event>()->AddEventSink(&_unk4429D0EventSink);
_MESSAGE("unk4429D0Event: registered");
GetEventDispatcher<unk442A70Event>()->AddEventSink(&_unk442A70EventSink);
_MESSAGE("unk442A70Event: registered");
GetEventDispatcher<unk442B10Event>()->AddEventSink(&_unk442B10EventSink);
_MESSAGE("unk442B10Event: registered");
GetEventDispatcher<unk442BB0Event>()->AddEventSink(&_unk442BB0EventSink);
_MESSAGE("unk442BB0Event: registered");
GetEventDispatcher<unk444550Event>()->AddEventSink(&_unk444550EventSink);
_MESSAGE("unk444550Event: registered");
GetEventDispatcher<unk441A30Event>()->AddEventSink(&_unk441A30EventSink);
_MESSAGE("unk441A30Event: registered");
GetEventDispatcher<unk441AD0Event>()->AddEventSink(&_unk441AD0EventSink);
_MESSAGE("unk441AD0Event: registered");
GetEventDispatcher<unk4444B0Event>()->AddEventSink(&_unk4444B0EventSink);
_MESSAGE("unk4444B0Event: registered");
GetEventDispatcher<unk442C50Event>()->AddEventSink(&_unk442C50EventSink);
_MESSAGE("unk442C50Event: registered");
GetEventDispatcher<unk442E30Event>()->AddEventSink(&_unk442E30EventSink);
_MESSAGE("unk442E30Event: registered");
GetEventDispatcher<unk442ED0Event>()->AddEventSink(&_unk442ED0EventSink);
_MESSAGE("unk442ED0Event: registered");
GetEventDispatcher<unk442D90Event>()->AddEventSink(&_unk442D90EventSink);
_MESSAGE("unk442D90Event: registered");
GetEventDispatcher<unk442F70Event>()->AddEventSink(&_unk442F70EventSink);
_MESSAGE("unk442F70Event: registered");
GetEventDispatcher<unk443010Event>()->AddEventSink(&_unk443010EventSink);
_MESSAGE("unk443010Event: registered");
GetEventDispatcher<unk4430B0Event>()->AddEventSink(&_unk4430B0EventSink);
_MESSAGE("unk4430B0Event: registered");
GetEventDispatcher<unk443290Event>()->AddEventSink(&_unk443290EventSink);
_MESSAGE("unk443290Event: registered");
GetEventDispatcher<unk443330Event>()->AddEventSink(&_unk443330EventSink);
_MESSAGE("unk443330Event: registered");
GetEventDispatcher<unk4433D0Event>()->AddEventSink(&_unk4433D0EventSink);
_MESSAGE("unk4433D0Event: registered");
GetEventDispatcher<unk443510Event>()->AddEventSink(&_unk443510EventSink);
_MESSAGE("unk443510Event: registered");
GetEventDispatcher<unk4435B0Event>()->AddEventSink(&_unk4435B0EventSink);
_MESSAGE("unk4435B0Event: registered");
GetEventDispatcher<unk443650Event>()->AddEventSink(&_unk443650EventSink);
_MESSAGE("unk443650Event: registered");
GetEventDispatcher<unk4436F0Event>()->AddEventSink(&_unk4436F0EventSink);
_MESSAGE("unk4436F0Event: registered");
GetEventDispatcher<unk443790Event>()->AddEventSink(&_unk443790EventSink);
_MESSAGE("unk443790Event: registered");
GetEventDispatcher<unk443830Event>()->AddEventSink(&_unk443830EventSink);
_MESSAGE("unk443830Event: registered");
GetEventDispatcher<unk4438D0Event>()->AddEventSink(&_unk4438D0EventSink);
_MESSAGE("unk4438D0Event: registered");
GetEventDispatcher<unk443A10Event>()->AddEventSink(&_unk443A10EventSink);
_MESSAGE("unk443A10Event: registered");
GetEventDispatcher<unk443970Event>()->AddEventSink(&_unk443970EventSink);
_MESSAGE("unk443970Event: registered");
GetEventDispatcher<unk443AB0Event>()->AddEventSink(&_unk443AB0EventSink);
_MESSAGE("unk443AB0Event: registered");
GetEventDispatcher<unk443B50Event>()->AddEventSink(&_unk443B50EventSink);
_MESSAGE("unk443B50Event: registered");
GetEventDispatcher<unk443BF0Event>()->AddEventSink(&_unk443BF0EventSink);
_MESSAGE("unk443BF0Event: registered");
GetEventDispatcher<unk443C90Event>()->AddEventSink(&_unk443C90EventSink);
_MESSAGE("unk443C90Event: registered");
GetEventDispatcher<unk443D30Event>()->AddEventSink(&_unk443D30EventSink);
_MESSAGE("unk443D30Event: registered");
GetEventDispatcher<unk443E70Event>()->AddEventSink(&_unk443E70EventSink);
_MESSAGE("unk443E70Event: registered");
GetEventDispatcher<unk443F10Event>()->AddEventSink(&_unk443F10EventSink);
_MESSAGE("unk443F10Event: registered");
GetEventDispatcher<unk443150Event>()->AddEventSink(&_unk443150EventSink);
_MESSAGE("unk443150Event: registered");
GetEventDispatcher<unk443FB0Event>()->AddEventSink(&_unk443FB0EventSink);
_MESSAGE("unk443FB0Event: registered");
GetEventDispatcher<unk4440F0Event>()->AddEventSink(&_unk4440F0EventSink);
_MESSAGE("unk4440F0Event: registered");
GetEventDispatcher<unk444050Event>()->AddEventSink(&_unk444050EventSink);
_MESSAGE("unk444050Event: registered");
GetEventDispatcher<unk444190Event>()->AddEventSink(&_unk444190EventSink);
_MESSAGE("unk444190Event: registered");
GetEventDispatcher<unk444230Event>()->AddEventSink(&_unk444230EventSink);
_MESSAGE("unk444230Event: registered");
GetEventDispatcher<unk4442D0Event>()->AddEventSink(&_unk4442D0EventSink);
_MESSAGE("unk4442D0Event: registered");
GetEventDispatcher<unk444370Event>()->AddEventSink(&_unk444370EventSink);
_MESSAGE("unk444370Event: registered");
GetEventDispatcher<unk443DD0Event>()->AddEventSink(&_unk443DD0EventSink);
_MESSAGE("unk443DD0Event: registered");
GetEventDispatcher<unk4422F0Event>()->AddEventSink(&_unk4422F0EventSink);
_MESSAGE("unk4422F0Event: registered");
GetEventDispatcher<unk442CF0Event>()->AddEventSink(&_unk442CF0EventSink);
_MESSAGE("unk442CF0Event: registered");
GetEventDispatcher<unk443470Event>()->AddEventSink(&_unk443470EventSink);
_MESSAGE("unk443470Event: registered");
GetEventDispatcher<unk4431F0Event>()->AddEventSink(&_unk4431F0EventSink);
_MESSAGE("unk4431F0Event: registered");
GetEventDispatcher<unk441990Event>()->AddEventSink(&_unk441990EventSink);
_MESSAGE("unk441990Event: registered");
GetEventDispatcher<unk4415D0Event>()->AddEventSink(&_unk4415D0EventSink);
_MESSAGE("unk4415D0Event: registered");
GetEventDispatcher<unk4412B0Event>()->AddEventSink(&_unk4412B0EventSink);
_MESSAGE("unk4412B0Event: registered");
GetEventDispatcher<unk441490Event>()->AddEventSink(&_unk441490EventSink);
_MESSAGE("unk441490Event: registered");
GetEventDispatcher<unk441670Event>()->AddEventSink(&_unk441670EventSink);
_MESSAGE("unk441670Event: registered");
GetEventDispatcher<unk441350Event>()->AddEventSink(&_unk441350EventSink);
_MESSAGE("unk441350Event: registered");
GetEventDispatcher<unk441710Event>()->AddEventSink(&_unk441710EventSink);
_MESSAGE("unk441710Event: registered");
GetEventDispatcher<unk441530Event>()->AddEventSink(&_unk441530EventSink);
_MESSAGE("unk441530Event: registered");
GetEventDispatcher<unk4417B0Event>()->AddEventSink(&_unk4417B0EventSink);
_MESSAGE("unk4417B0Event: registered");
GetEventDispatcher<unk4413F0Event>()->AddEventSink(&_unk4413F0EventSink);
_MESSAGE("unk4413F0Event: registered");
GetEventDispatcher<unk441850Event>()->AddEventSink(&_unk441850EventSink);
_MESSAGE("unk441850Event: registered");
GetEventDispatcher<unk4418F0Event>()->AddEventSink(&_unk4418F0EventSink);
_MESSAGE("unk4418F0Event: registered");
GetEventDispatcher<unk4A9180Event>()->AddEventSink(&_unk4A9180EventSink);
_MESSAGE("unk4A9180Event: registered");
GetEventDispatcher<unk571770Event>()->AddEventSink(&_unk571770EventSink);
_MESSAGE("unk571770Event: registered");
GetEventDispatcher<unk577BB0Event>()->AddEventSink(&_unk577BB0EventSink);
_MESSAGE("unk577BB0Event: registered");
GetEventDispatcher<unk5E2E10Event>()->AddEventSink(&_unk5E2E10EventSink);
_MESSAGE("unk5E2E10Event: registered");
GetEventDispatcher<unk5E2EB0Event>()->AddEventSink(&_unk5E2EB0EventSink);
_MESSAGE("unk5E2EB0Event: registered");
GetEventDispatcher<unkB88420Event>()->AddEventSink(&_unkB88420EventSink);
_MESSAGE("unkB88420Event: registered");
GetEventDispatcher<unkB884C0Event>()->AddEventSink(&_unkB884C0EventSink);
_MESSAGE("unkB884C0Event: registered");
GetEventDispatcher<unkB88560Event>()->AddEventSink(&_unkB88560EventSink);
_MESSAGE("unkB88560Event: registered");
GetEventDispatcher<unkBB85C0Event>()->AddEventSink(&_unkBB85C0EventSink);
_MESSAGE("unkBB85C0Event: registered");
GetEventDispatcher<unkD1E500Event>()->AddEventSink(&_unkD1E500EventSink);
_MESSAGE("unkD1E500Event: registered");
GetEventDispatcher<unkD1E5D0Event>()->AddEventSink(&_unkD1E5D0EventSink);
_MESSAGE("unkD1E5D0Event: registered");
GetEventDispatcher<unkDC5E10Event>()->AddEventSink(&_unkDC5E10EventSink);
_MESSAGE("unkDC5E10Event: registered");
GetEventDispatcher<unkDC5EF0Event>()->AddEventSink(&_unkDC5EF0EventSink);
_MESSAGE("unkDC5EF0Event: registered");
GetEventDispatcher<unkDC6170Event>()->AddEventSink(&_unkDC6170EventSink);
_MESSAGE("unkDC6170Event: registered");
GetEventDispatcher<unkDC6240Event>()->AddEventSink(&_unkDC6240EventSink);
_MESSAGE("unkDC6240Event: registered");
GetEventDispatcher<unkDC6310Event>()->AddEventSink(&_unkDC6310EventSink);
_MESSAGE("unkDC6310Event: registered");
GetEventDispatcher<unkDC5FC0Event>()->AddEventSink(&_unkDC5FC0EventSink);
_MESSAGE("unkDC5FC0Event: registered");
GetEventDispatcher<unkDC60A0Event>()->AddEventSink(&_unkDC60A0EventSink);
_MESSAGE("unkDC60A0Event: registered");
GetEventDispatcher<unkDF9580Event>()->AddEventSink(&_unkDF9580EventSink);
_MESSAGE("unkDF9580Event: registered");
GetEventDispatcher<unkE07A10Event>()->AddEventSink(&_unkE07A10EventSink);
_MESSAGE("unkE07A10Event: registered");
GetEventDispatcher<unkE07AB0Event>()->AddEventSink(&_unkE07AB0EventSink);
_MESSAGE("unkE07AB0Event: registered");
GetEventDispatcher<unkE15EA0Event>()->AddEventSink(&_unkE15EA0EventSink);
_MESSAGE("unkE15EA0Event: registered");
GetEventDispatcher<unkE15F80Event>()->AddEventSink(&_unkE15F80EventSink);
_MESSAGE("unkE15F80Event: registered");
GetEventDispatcher<unkEC2400Event>()->AddEventSink(&_unkEC2400EventSink);
_MESSAGE("unkEC2400Event: registered");
GetEventDispatcher<unkEC24E0Event>()->AddEventSink(&_unkEC24E0EventSink);
_MESSAGE("unkEC24E0Event: registered");
GetEventDispatcher<unkEC2580Event>()->AddEventSink(&_unkEC2580EventSink);
_MESSAGE("unkEC2580Event: registered");
GetEventDispatcher<unkEC2620Event>()->AddEventSink(&_unkEC2620EventSink);
_MESSAGE("unkEC2620Event: registered");
GetEventDispatcher<unkEC26C0Event>()->AddEventSink(&_unkEC26C0EventSink);
_MESSAGE("unkEC26C0Event: registered");
GetEventDispatcher<unkEC2760Event>()->AddEventSink(&_unkEC2760EventSink);
_MESSAGE("unkEC2760Event: registered");
GetEventDispatcher<unkEC2800Event>()->AddEventSink(&_unkEC2800EventSink);
_MESSAGE("unkEC2800Event: registered");
GetEventDispatcher<unkEC28A0Event>()->AddEventSink(&_unkEC28A0EventSink);
_MESSAGE("unkEC28A0Event: registered");
GetEventDispatcher<unkEC2940Event>()->AddEventSink(&_unkEC2940EventSink);
_MESSAGE("unkEC2940Event: registered");
GetEventDispatcher<unkEC29E0Event>()->AddEventSink(&_unkEC29E0EventSink);
_MESSAGE("unkEC29E0Event: registered");
GetEventDispatcher<unkEC2A80Event>()->AddEventSink(&_unkEC2A80EventSink);
_MESSAGE("unkEC2A80Event: registered");
GetEventDispatcher<unkEC2B20Event>()->AddEventSink(&_unkEC2B20EventSink);
_MESSAGE("unkEC2B20Event: registered");
GetEventDispatcher<unkEC2BC0Event>()->AddEventSink(&_unkEC2BC0EventSink);
_MESSAGE("unkEC2BC0Event: registered");
GetEventDispatcher<unkEC2C60Event>()->AddEventSink(&_unkEC2C60EventSink);
_MESSAGE("unkEC2C60Event: registered");
GetEventDispatcher<unkEC2D00Event>()->AddEventSink(&_unkEC2D00EventSink);
_MESSAGE("unkEC2D00Event: registered");
GetEventDispatcher<unkEC2DA0Event>()->AddEventSink(&_unkEC2DA0EventSink);
_MESSAGE("unkEC2DA0Event: registered");
GetEventDispatcher<unkEC2E40Event>()->AddEventSink(&_unkEC2E40EventSink);
_MESSAGE("unkEC2E40Event: registered");
GetEventDispatcher<unkEC2EE0Event>()->AddEventSink(&_unkEC2EE0EventSink);
_MESSAGE("unkEC2EE0Event: registered");
GetEventDispatcher<unkEC2F80Event>()->AddEventSink(&_unkEC2F80EventSink);
_MESSAGE("unkEC2F80Event: registered");
GetEventDispatcher<unkEC3020Event>()->AddEventSink(&_unkEC3020EventSink);
_MESSAGE("unkEC3020Event: registered");
GetEventDispatcher<unkEC30C0Event>()->AddEventSink(&_unkEC30C0EventSink);
_MESSAGE("unkEC30C0Event: registered");
GetEventDispatcher<unkEC3160Event>()->AddEventSink(&_unkEC3160EventSink);
_MESSAGE("unkEC3160Event: registered");
GetEventDispatcher<unkEC3200Event>()->AddEventSink(&_unkEC3200EventSink);
_MESSAGE("unkEC3200Event: registered");
GetEventDispatcher<unkEC32A0Event>()->AddEventSink(&_unkEC32A0EventSink);
_MESSAGE("unkEC32A0Event: registered");
GetEventDispatcher<unkEC3340Event>()->AddEventSink(&_unkEC3340EventSink);
_MESSAGE("unkEC3340Event: registered");
GetEventDispatcher<unkEC33E0Event>()->AddEventSink(&_unkEC33E0EventSink);
_MESSAGE("unkEC33E0Event: registered");
GetEventDispatcher<unkEC3480Event>()->AddEventSink(&_unkEC3480EventSink);
_MESSAGE("unkEC3480Event: registered");
GetEventDispatcher<unkEC3520Event>()->AddEventSink(&_unkEC3520EventSink);
_MESSAGE("unkEC3520Event: registered");
GetEventDispatcher<unkEC35C0Event>()->AddEventSink(&_unkEC35C0EventSink);
_MESSAGE("unkEC35C0Event: registered");
GetEventDispatcher<unkEC3660Event>()->AddEventSink(&_unkEC3660EventSink);
_MESSAGE("unkEC3660Event: registered");
GetEventDispatcher<unkEC3700Event>()->AddEventSink(&_unkEC3700EventSink);
_MESSAGE("unkEC3700Event: registered");
GetEventDispatcher<unkEC37A0Event>()->AddEventSink(&_unkEC37A0EventSink);
_MESSAGE("unkEC37A0Event: registered");
GetEventDispatcher<unkEC3840Event>()->AddEventSink(&_unkEC3840EventSink);
_MESSAGE("unkEC3840Event: registered");
GetEventDispatcher<unkEC38E0Event>()->AddEventSink(&_unkEC38E0EventSink);
_MESSAGE("unkEC38E0Event: registered");
GetEventDispatcher<unkEC3980Event>()->AddEventSink(&_unkEC3980EventSink);
_MESSAGE("unkEC3980Event: registered");
GetEventDispatcher<unkEC3A20Event>()->AddEventSink(&_unkEC3A20EventSink);
_MESSAGE("unkEC3A20Event: registered");
GetEventDispatcher<unkEC3AF0Event>()->AddEventSink(&_unkEC3AF0EventSink);
_MESSAGE("unkEC3AF0Event: registered");
GetEventDispatcher<unkE97250Event>()->AddEventSink(&_unkE97250EventSink);
_MESSAGE("unkE97250Event: registered");
GetEventDispatcher<unkF45BF0Event>()->AddEventSink(&_unkF45BF0EventSink);
_MESSAGE("unkF45BF0Event: registered");
GetEventDispatcher<unkF5BF80Event>()->AddEventSink(&_unkF5BF80EventSink);
_MESSAGE("unkF5BF80Event: registered");
GetEventDispatcher<unkFD97D0Event>()->AddEventSink(&_unkFD97D0EventSink);
_MESSAGE("unkFD97D0Event: registered");
//GetEventDispatcher<unkFE7300Event>()->AddEventSink(&_unkFE7300EventSink);
//_MESSAGE("unkFE7300Event: registered");
GetEventDispatcher<unk127DB30Event>()->AddEventSink(&_unk127DB30EventSink);
_MESSAGE("unk127DB30Event: registered");
GetEventDispatcher<unk127DBD0Event>()->AddEventSink(&_unk127DBD0EventSink);
_MESSAGE("unk127DBD0Event: registered");
GetEventDispatcher<unk129EC30Event>()->AddEventSink(&_unk129EC30EventSink);
_MESSAGE("unk129EC30Event: registered");
GetEventDispatcher<unk12B1800Event>()->AddEventSink(&_unk12B1800EventSink);
_MESSAGE("unk12B1800Event: registered");
GetEventDispatcher<unk1B0FDF0Event>()->AddEventSink(&_unk1B0FDF0EventSink);
_MESSAGE("unk1B0FDF0Event: registered");
//GetEventDispatcher<unk1B16400Event>()->AddEventSink(&_unk1B16400EventSink);
//_MESSAGE("unk1B16400Event: registered");
}

void testdump()
{
	DumpClass(GetEventDispatcher<unk100E80Event>()->eventSinks.entries, 16);
	_MESSAGE("unk100E80Event: registered");
	DumpClass(GetEventDispatcher<unk10B730Event>()->eventSinks.entries, 16);
	_MESSAGE("unk10B730Event: registered");
	DumpClass(GetEventDispatcher<unk162970Event>()->eventSinks.entries, 16);
	_MESSAGE("unk162970Event: registered");
	DumpClass(GetEventDispatcher<unk1A8D90Event>()->eventSinks.entries, 16);
	_MESSAGE("unk1A8D90Event: registered");
	DumpClass(GetEventDispatcher<unk229FB0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk229FB0Event: registered");
	DumpClass(GetEventDispatcher<unk22A050Event>()->eventSinks.entries, 16);
	_MESSAGE("unk22A050Event: registered");
	DumpClass(GetEventDispatcher<unk229DD0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk229DD0Event: registered");
	DumpClass(GetEventDispatcher<unk229F10Event>()->eventSinks.entries, 16);
	_MESSAGE("unk229F10Event: registered");
	DumpClass(GetEventDispatcher<unk229E70Event>()->eventSinks.entries, 16);
	_MESSAGE("unk229E70Event: registered");
	DumpClass(GetEventDispatcher<unk22A370Event>()->eventSinks.entries, 16);
	_MESSAGE("unk22A370Event: registered");
	DumpClass(GetEventDispatcher<unk22A2D0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk22A2D0Event: registered");
	DumpClass(GetEventDispatcher<unk229D30Event>()->eventSinks.entries, 16);
	_MESSAGE("unk229D30Event: registered");
	DumpClass(GetEventDispatcher<unk22A190Event>()->eventSinks.entries, 16);
	_MESSAGE("unk22A190Event: registered");
	DumpClass(GetEventDispatcher<unk22A0F0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk22A0F0Event: registered");
	DumpClass(GetEventDispatcher<unk22A410Event>()->eventSinks.entries, 16);
	_MESSAGE("unk22A410Event: registered");
	DumpClass(GetEventDispatcher<unk22A230Event>()->eventSinks.entries, 16);
	_MESSAGE("unk22A230Event: registered");
	DumpClass(GetEventDispatcher<unk337110Event>()->eventSinks.entries, 16);
	_MESSAGE("unk337110Event: registered");
	DumpClass(GetEventDispatcher<unk33F6C0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk33F6C0Event: registered");
	DumpClass(GetEventDispatcher<unk382500Event>()->eventSinks.entries, 16);
	_MESSAGE("unk382500Event: registered");
	DumpClass(GetEventDispatcher<unk3825D0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk3825D0Event: registered");
	DumpClass(GetEventDispatcher<unk414FC0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk414FC0Event: registered");
	DumpClass(GetEventDispatcher<unk441170Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441170Event: registered");
	DumpClass(GetEventDispatcher<unk444410Event>()->eventSinks.entries, 16);
	_MESSAGE("unk444410Event: registered");
	DumpClass(GetEventDispatcher<unk441B70Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441B70Event: registered");
	DumpClass(GetEventDispatcher<unk442930Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442930Event: registered");
	DumpClass(GetEventDispatcher<unk441C10Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441C10Event: registered");
	DumpClass(GetEventDispatcher<unk441CB0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441CB0Event: registered");
	DumpClass(GetEventDispatcher<unk441D50Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441D50Event: registered");
	DumpClass(GetEventDispatcher<unk441DF0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441DF0Event: registered");
	DumpClass(GetEventDispatcher<unk441E90Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441E90Event: registered");
	DumpClass(GetEventDispatcher<unk441F30Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441F30Event: registered");
	DumpClass(GetEventDispatcher<unk441FD0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441FD0Event: registered");
	DumpClass(GetEventDispatcher<unk442070Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442070Event: registered");
	DumpClass(GetEventDispatcher<unk442110Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442110Event: registered");
	DumpClass(GetEventDispatcher<unk4421B0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4421B0Event: registered");
	DumpClass(GetEventDispatcher<unk442250Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442250Event: registered");
	DumpClass(GetEventDispatcher<unk442390Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442390Event: registered");
	DumpClass(GetEventDispatcher<unk441210Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441210Event: registered");
	DumpClass(GetEventDispatcher<unk4424D0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4424D0Event: registered");
	DumpClass(GetEventDispatcher<unk442430Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442430Event: registered");
	DumpClass(GetEventDispatcher<unk442570Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442570Event: registered");
	DumpClass(GetEventDispatcher<unk442610Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442610Event: registered");
	DumpClass(GetEventDispatcher<unk4426B0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4426B0Event: registered");
	DumpClass(GetEventDispatcher<unk4427F0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4427F0Event: registered");
	DumpClass(GetEventDispatcher<unk442890Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442890Event: registered");
	DumpClass(GetEventDispatcher<unk442750Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442750Event: registered");
	DumpClass(GetEventDispatcher<unk4429D0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4429D0Event: registered");
	DumpClass(GetEventDispatcher<unk442A70Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442A70Event: registered");
	DumpClass(GetEventDispatcher<unk442B10Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442B10Event: registered");
	DumpClass(GetEventDispatcher<unk442BB0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442BB0Event: registered");
	DumpClass(GetEventDispatcher<unk444550Event>()->eventSinks.entries, 16);
	_MESSAGE("unk444550Event: registered");
	DumpClass(GetEventDispatcher<unk441A30Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441A30Event: registered");
	DumpClass(GetEventDispatcher<unk441AD0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441AD0Event: registered");
	DumpClass(GetEventDispatcher<unk4444B0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4444B0Event: registered");
	DumpClass(GetEventDispatcher<unk442C50Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442C50Event: registered");
	DumpClass(GetEventDispatcher<unk442E30Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442E30Event: registered");
	DumpClass(GetEventDispatcher<unk442ED0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442ED0Event: registered");
	DumpClass(GetEventDispatcher<unk442D90Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442D90Event: registered");
	DumpClass(GetEventDispatcher<unk442F70Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442F70Event: registered");
	DumpClass(GetEventDispatcher<unk443010Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443010Event: registered");
	DumpClass(GetEventDispatcher<unk4430B0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4430B0Event: registered");
	DumpClass(GetEventDispatcher<unk443290Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443290Event: registered");
	DumpClass(GetEventDispatcher<unk443330Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443330Event: registered");
	DumpClass(GetEventDispatcher<unk4433D0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4433D0Event: registered");
	DumpClass(GetEventDispatcher<unk443510Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443510Event: registered");
	DumpClass(GetEventDispatcher<unk4435B0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4435B0Event: registered");
	DumpClass(GetEventDispatcher<unk443650Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443650Event: registered");
	DumpClass(GetEventDispatcher<unk4436F0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4436F0Event: registered");
	DumpClass(GetEventDispatcher<unk443790Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443790Event: registered");
	DumpClass(GetEventDispatcher<unk443830Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443830Event: registered");
	DumpClass(GetEventDispatcher<unk4438D0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4438D0Event: registered");
	DumpClass(GetEventDispatcher<unk443A10Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443A10Event: registered");
	DumpClass(GetEventDispatcher<unk443970Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443970Event: registered");
	DumpClass(GetEventDispatcher<unk443AB0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443AB0Event: registered");
	DumpClass(GetEventDispatcher<unk443B50Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443B50Event: registered");
	DumpClass(GetEventDispatcher<unk443BF0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443BF0Event: registered");
	DumpClass(GetEventDispatcher<unk443C90Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443C90Event: registered");
	DumpClass(GetEventDispatcher<unk443D30Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443D30Event: registered");
	DumpClass(GetEventDispatcher<unk443E70Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443E70Event: registered");
	DumpClass(GetEventDispatcher<unk443F10Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443F10Event: registered");
	DumpClass(GetEventDispatcher<unk443150Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443150Event: registered");
	DumpClass(GetEventDispatcher<unk443FB0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443FB0Event: registered");
	DumpClass(GetEventDispatcher<unk4440F0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4440F0Event: registered");
	DumpClass(GetEventDispatcher<unk444050Event>()->eventSinks.entries, 16);
	_MESSAGE("unk444050Event: registered");
	DumpClass(GetEventDispatcher<unk444190Event>()->eventSinks.entries, 16);
	_MESSAGE("unk444190Event: registered");
	DumpClass(GetEventDispatcher<unk444230Event>()->eventSinks.entries, 16);
	_MESSAGE("unk444230Event: registered");
	DumpClass(GetEventDispatcher<unk4442D0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4442D0Event: registered");
	DumpClass(GetEventDispatcher<unk444370Event>()->eventSinks.entries, 16);
	_MESSAGE("unk444370Event: registered");
	DumpClass(GetEventDispatcher<unk443DD0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443DD0Event: registered");
	DumpClass(GetEventDispatcher<unk4422F0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4422F0Event: registered");
	DumpClass(GetEventDispatcher<unk442CF0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk442CF0Event: registered");
	DumpClass(GetEventDispatcher<unk443470Event>()->eventSinks.entries, 16);
	_MESSAGE("unk443470Event: registered");
	DumpClass(GetEventDispatcher<unk4431F0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4431F0Event: registered");
	DumpClass(GetEventDispatcher<unk441990Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441990Event: registered");
	DumpClass(GetEventDispatcher<unk4415D0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4415D0Event: registered");
	DumpClass(GetEventDispatcher<unk4412B0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4412B0Event: registered");
	DumpClass(GetEventDispatcher<unk441490Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441490Event: registered");
	DumpClass(GetEventDispatcher<unk441670Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441670Event: registered");
	DumpClass(GetEventDispatcher<unk441350Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441350Event: registered");
	DumpClass(GetEventDispatcher<unk441710Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441710Event: registered");
	DumpClass(GetEventDispatcher<unk441530Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441530Event: registered");
	DumpClass(GetEventDispatcher<unk4417B0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4417B0Event: registered");
	DumpClass(GetEventDispatcher<unk4413F0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4413F0Event: registered");
	DumpClass(GetEventDispatcher<unk441850Event>()->eventSinks.entries, 16);
	_MESSAGE("unk441850Event: registered");
	DumpClass(GetEventDispatcher<unk4418F0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4418F0Event: registered");
	DumpClass(GetEventDispatcher<unk4A9180Event>()->eventSinks.entries, 16);
	_MESSAGE("unk4A9180Event: registered");
	DumpClass(GetEventDispatcher<unk571770Event>()->eventSinks.entries, 16);
	_MESSAGE("unk571770Event: registered");
	DumpClass(GetEventDispatcher<unk577BB0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk577BB0Event: registered");
	DumpClass(GetEventDispatcher<unk5E2E10Event>()->eventSinks.entries, 16);
	_MESSAGE("unk5E2E10Event: registered");
	DumpClass(GetEventDispatcher<unk5E2EB0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk5E2EB0Event: registered");
	DumpClass(GetEventDispatcher<unkB88420Event>()->eventSinks.entries, 16);
	_MESSAGE("unkB88420Event: registered");
	DumpClass(GetEventDispatcher<unkB884C0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkB884C0Event: registered");
	DumpClass(GetEventDispatcher<unkB88560Event>()->eventSinks.entries, 16);
	_MESSAGE("unkB88560Event: registered");
	DumpClass(GetEventDispatcher<unkBB85C0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkBB85C0Event: registered");
	DumpClass(GetEventDispatcher<unkD1E500Event>()->eventSinks.entries, 16);
	_MESSAGE("unkD1E500Event: registered");
	DumpClass(GetEventDispatcher<unkD1E5D0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkD1E5D0Event: registered");
	DumpClass(GetEventDispatcher<unkDC5E10Event>()->eventSinks.entries, 16);
	_MESSAGE("unkDC5E10Event: registered");
	DumpClass(GetEventDispatcher<unkDC5EF0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkDC5EF0Event: registered");
	DumpClass(GetEventDispatcher<unkDC6170Event>()->eventSinks.entries, 16);
	_MESSAGE("unkDC6170Event: registered");
	DumpClass(GetEventDispatcher<unkDC6240Event>()->eventSinks.entries, 16);
	_MESSAGE("unkDC6240Event: registered");
	DumpClass(GetEventDispatcher<unkDC6310Event>()->eventSinks.entries, 16);
	_MESSAGE("unkDC6310Event: registered");
	DumpClass(GetEventDispatcher<unkDC5FC0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkDC5FC0Event: registered");
	DumpClass(GetEventDispatcher<unkDC60A0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkDC60A0Event: registered");
	DumpClass(GetEventDispatcher<unkDF9580Event>()->eventSinks.entries, 16);
	_MESSAGE("unkDF9580Event: registered");
	DumpClass(GetEventDispatcher<unkE07A10Event>()->eventSinks.entries, 16);
	_MESSAGE("unkE07A10Event: registered");
	DumpClass(GetEventDispatcher<unkE07AB0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkE07AB0Event: registered");
	DumpClass(GetEventDispatcher<unkE15EA0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkE15EA0Event: registered");
	DumpClass(GetEventDispatcher<unkE15F80Event>()->eventSinks.entries, 16);
	_MESSAGE("unkE15F80Event: registered");
	DumpClass(GetEventDispatcher<unkEC2400Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC2400Event: registered");
	DumpClass(GetEventDispatcher<unkEC24E0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC24E0Event: registered");
	DumpClass(GetEventDispatcher<unkEC2580Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC2580Event: registered");
	DumpClass(GetEventDispatcher<unkEC2620Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC2620Event: registered");
	DumpClass(GetEventDispatcher<unkEC26C0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC26C0Event: registered");
	DumpClass(GetEventDispatcher<unkEC2760Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC2760Event: registered");
	DumpClass(GetEventDispatcher<unkEC2800Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC2800Event: registered");
	DumpClass(GetEventDispatcher<unkEC28A0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC28A0Event: registered");
	DumpClass(GetEventDispatcher<unkEC2940Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC2940Event: registered");
	DumpClass(GetEventDispatcher<unkEC29E0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC29E0Event: registered");
	DumpClass(GetEventDispatcher<unkEC2A80Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC2A80Event: registered");
	DumpClass(GetEventDispatcher<unkEC2B20Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC2B20Event: registered");
	DumpClass(GetEventDispatcher<unkEC2BC0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC2BC0Event: registered");
	DumpClass(GetEventDispatcher<unkEC2C60Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC2C60Event: registered");
	DumpClass(GetEventDispatcher<unkEC2D00Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC2D00Event: registered");
	DumpClass(GetEventDispatcher<unkEC2DA0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC2DA0Event: registered");
	DumpClass(GetEventDispatcher<unkEC2E40Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC2E40Event: registered");
	DumpClass(GetEventDispatcher<unkEC2EE0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC2EE0Event: registered");
	DumpClass(GetEventDispatcher<unkEC2F80Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC2F80Event: registered");
	DumpClass(GetEventDispatcher<unkEC3020Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC3020Event: registered");
	DumpClass(GetEventDispatcher<unkEC30C0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC30C0Event: registered");
	DumpClass(GetEventDispatcher<unkEC3160Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC3160Event: registered");
	DumpClass(GetEventDispatcher<unkEC3200Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC3200Event: registered");
	DumpClass(GetEventDispatcher<unkEC32A0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC32A0Event: registered");
	DumpClass(GetEventDispatcher<unkEC3340Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC3340Event: registered");
	DumpClass(GetEventDispatcher<unkEC33E0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC33E0Event: registered");
	DumpClass(GetEventDispatcher<unkEC3480Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC3480Event: registered");
	DumpClass(GetEventDispatcher<unkEC3520Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC3520Event: registered");
	DumpClass(GetEventDispatcher<unkEC35C0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC35C0Event: registered");
	DumpClass(GetEventDispatcher<unkEC3660Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC3660Event: registered");
	DumpClass(GetEventDispatcher<unkEC3700Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC3700Event: registered");
	DumpClass(GetEventDispatcher<unkEC37A0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC37A0Event: registered");
	DumpClass(GetEventDispatcher<unkEC3840Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC3840Event: registered");
	DumpClass(GetEventDispatcher<unkEC38E0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC38E0Event: registered");
	DumpClass(GetEventDispatcher<unkEC3980Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC3980Event: registered");
	DumpClass(GetEventDispatcher<unkEC3A20Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC3A20Event: registered");
	DumpClass(GetEventDispatcher<unkEC3AF0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkEC3AF0Event: registered");
	DumpClass(GetEventDispatcher<unkE97250Event>()->eventSinks.entries, 16);
	_MESSAGE("unkE97250Event: registered");
	DumpClass(GetEventDispatcher<unkF45BF0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkF45BF0Event: registered");
	DumpClass(GetEventDispatcher<unkF5BF80Event>()->eventSinks.entries, 16);
	_MESSAGE("unkF5BF80Event: registered");
	DumpClass(GetEventDispatcher<unkFD97D0Event>()->eventSinks.entries, 16);
	_MESSAGE("unkFD97D0Event: registered");
	//DumpClass(GetEventDispatcher<unkFE7300Event>()->eventSinks.entries, 16);
	//_MESSAGE("unkFE7300Event: registered");
	DumpClass(GetEventDispatcher<unk127DB30Event>()->eventSinks.entries, 16);
	_MESSAGE("unk127DB30Event: registered");
	DumpClass(GetEventDispatcher<unk127DBD0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk127DBD0Event: registered");
	DumpClass(GetEventDispatcher<unk129EC30Event>()->eventSinks.entries, 16);
	_MESSAGE("unk129EC30Event: registered");
	DumpClass(GetEventDispatcher<unk12B1800Event>()->eventSinks.entries, 16);
	_MESSAGE("unk12B1800Event: registered");
	DumpClass(GetEventDispatcher<unk1B0FDF0Event>()->eventSinks.entries, 16);
	_MESSAGE("unk1B0FDF0Event: registered");
	//DumpClass(GetEventDispatcher<unk1B16400Event>()->eventSinks.entries, 16);
	//_MESSAGE("unk1B16400Event: registered");
}