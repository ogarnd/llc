#include "llc_event.h"

#ifndef LLC_SYSTEM_EVENT_H_23627
#define LLC_SYSTEM_EVENT_H_23627

namespace llc
{
	GDEFINE_ENUM_TYPE(SYSTEM_EVENT, uint8_t);
	GDEFINE_ENUM_VALUE(SYSTEM_EVENT, Runtime	, 0);
	GDEFINE_ENUM_VALUE(SYSTEM_EVENT, Screen		, 1);
	GDEFINE_ENUM_VALUE(SYSTEM_EVENT, Keyboard	, 2);
	GDEFINE_ENUM_VALUE(SYSTEM_EVENT, Mouse		, 3);
	GDEFINE_ENUM_VALUE(SYSTEM_EVENT, Touch		, 4);
	GDEFINE_ENUM_VALUE(SYSTEM_EVENT, Joypad		, 5);
	GDEFINE_ENUM_VALUE(SYSTEM_EVENT, Text		, 6);
	GDEFINE_ENUM_VALUE(SYSTEM_EVENT, GUI		, 7);
	GDEFINE_ENUM_VALUE(SYSTEM_EVENT, Audio		, 8);
	GDEFINE_ENUM_VALUE(SYSTEM_EVENT, Camera		, 9);
	GDEFINE_ENUM_VALUE(SYSTEM_EVENT, Raster		,10);
	GDEFINE_ENUM_VALUE(SYSTEM_EVENT, Device		,11);

	typedef ::llc::SEvent            <::llc::SYSTEM_EVENT>	SEventSystem;
	typedef ::llc::SEView            <::llc::SYSTEM_EVENT>	SEViewSystem;
	typedef ::llc::FEventHandler     <::llc::SYSTEM_EVENT>	FEventSystem;
	typedef ::llc::FEventHandlerConst<::llc::SYSTEM_EVENT>	FEventSystemConst;
	typedef ::llc::FEViewHandler     <::llc::SYSTEM_EVENT>	FEViewSystem;
	typedef ::llc::FEViewHandlerConst<::llc::SYSTEM_EVENT>	FEViewSystemConst;
	typedef ::llc::pobj <::llc::SEventSystem>				PEventSystem;
	typedef ::llc::apobj<::llc::SEventSystem>				TQueueSystemEvent;
	
	template<typename _t>
	stainli	::llc::error_t	eventEnqueueChild	(::llc::apobj<::llc::SEventSystem> & queue, ::llc::RESULT eventType, _t & eventData)	{ 
		return ::llc::eventEnqueueChild(queue, ::llc::SYSTEM_EVENT_Device, eventType, eventData); 
	}

	//GDEFINE_ENUM_TYPE (EVENT_RUNTIME, uint8_t);
	//GDEFINE_ENUM_VALUE(EVENT_RUNTIME, Init			, 0);
	//GDEFINE_ENUM_VALUE(EVENT_RUNTIME, Exit			, 1);
	//GDEFINE_ENUM_VALUE(EVENT_RUNTIME, Process_queue	, 2);
	//GDEFINE_ENUM_VALUE(EVENT_RUNTIME, Process_event	, 3);

#pragma pack(push, 1)
	struct SDeviceResult {
		const ::llc::SYSTEM_EVENT	SystemEvent 	= {};
		const uint8_t				TailWidth		: 2;
		const uint8_t				Multiplier		: 6;
		::llc::RESULT				DeviceEvent		= {};

		cnstxpr						SDeviceResult	(::llc::RESULT deviceEvent = ::llc::RESULT_Error)
			: SystemEvent {::llc::SYSTEM_EVENT_Device}
			, TailWidth   {::llc::tail_width<uint32_t>((uint32_t)sizeof(::llc::RESULT))}
			, Multiplier  {::llc::tail_multiplier<uint32_t>((uint32_t)sizeof(::llc::RESULT))}
			, DeviceEvent {deviceEvent}
			{}
	};
	struct SDeviceCommand {
		const ::llc::SYSTEM_EVENT	SystemEvent 	= {};
		const uint8_t				TailWidth		: 2;
		const uint8_t				Multiplier		: 6;
		::llc::COMMAND				DeviceEvent		= {};

		cnstxpr						SDeviceCommand	(::llc::COMMAND deviceEvent = ::llc::COMMAND_Ok)
			: SystemEvent {::llc::SYSTEM_EVENT_Device}
			, TailWidth   {::llc::tail_width<uint32_t>((uint32_t)sizeof(::llc::COMMAND))}
			, Multiplier  {::llc::tail_multiplier<uint32_t>((uint32_t)sizeof(::llc::COMMAND))}
			, DeviceEvent {deviceEvent}
			{}
	};
#pragma pack(pop)

	//stainli	::llc::error_t	eventEnqueueRuntimeInit			(::llc::TQueueSystemEvent & queue)	{ return ::llc::eventEnqueueChild(queue, ::llc::SYSTEM_EVENT_Runtime, ::llc::EVENT_RUNTIME_Init			, ::llc::EVENT_RUNTIME_Init			); }
	//stainli	::llc::error_t	eventEnqueueRuntimeExit			(::llc::TQueueSystemEvent & queue)	{ return ::llc::eventEnqueueChild(queue, ::llc::SYSTEM_EVENT_Runtime, ::llc::EVENT_RUNTIME_Exit			, ::llc::EVENT_RUNTIME_Exit			); }
	//stainli	::llc::error_t	eventEnqueueRuntimeProcessQueue	(::llc::TQueueSystemEvent & queue)	{ return ::llc::eventEnqueueChild(queue, ::llc::SYSTEM_EVENT_Runtime, ::llc::EVENT_RUNTIME_Process_queue, ::llc::EVENT_RUNTIME_Process_queue); }
	//stainli	::llc::error_t	eventEnqueueRuntimeProcessEvent	(::llc::TQueueSystemEvent & queue)	{ return ::llc::eventEnqueueChild(queue, ::llc::SYSTEM_EVENT_Runtime, ::llc::EVENT_RUNTIME_Process_event, ::llc::EVENT_RUNTIME_Process_event); }
} // namespace

#endif // LLC_SYSTEM_EVENT_H_23627
