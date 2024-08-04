#include "llc_array_ptr.h"
#include "llc_enum.h"

#include "llc_apod_serialize.h"

#ifndef LLC_EVENT_H_23627
#define LLC_EVENT_H_23627

#define llc_event_printf verbose_printf

namespace llc
{
	tpl_t struct SEventView {
		tdfT(_t);
		tydf	SEventView<T>		TEView;

		T				Type		= {};
		::llc::vcu0_t	Data		= {};

		::llc::error_t	Save		(::llc::au0_t & output)	const	{
			llc_necs(llc::savePOD (output, Type));
			llc_necs(llc::saveView(output, Data));
			return 0;
		}

		::llc::error_t	Load		(::llc::vcu0_t & input)			{
			llc_necs(llc::loadPOD (input, Type));
			llc_necs(llc::loadView(input, Data));
			return 0;
		}
	};
	tplt<tpnm T> using SEView 					= ::llc::SEventView<T>;
	tplt<tpnm T> using TEViewQueue 				= ::llc::aobj<::llc::SEView<T>>;

	tplt<tpnm T> using FEViewHandler			= ::llc::function<::llc::error_t(      ::llc::SEView<T>&)>;
	tplt<tpnm T> using FEViewHandlerConst		= ::llc::function<::llc::error_t(const ::llc::SEView<T>&)>;
	tplt<tpnm T> using FEventViewHandler		= ::llc::function<::llc::error_t(      ::llc::SEView<T>&)>;
	tplt<tpnm T> using FEventViewHandlerConst	= ::llc::function<::llc::error_t(const ::llc::SEView<T>&)>;

	tplt<tpnm _tEventType>
	struct SEvent {
		tydf _tEventType			T;
		tydf ::llc::SEView<T>	TEView;
		tydf ::llc::SEvent<T>	TEvent;

		T				Type		= {};
		::llc::au0_t		Data		= {};

						SEvent		(const TEvent &)							= default;
		constexpr		SEvent		(T type = {})						: Type(type) {}
						SEvent		(T type, const ::llc::vcu0_t data)	: Type(type), Data(data.cu8()) {}
						SEvent		(const TEView & eventView)			: Type(eventView.Type), Data(eventView.Data) {}

		TEvent&			oper= 	(const TEvent &)				= default;
		TEvent&			oper= 	(const TEView & eventView)		{ Type = eventView.Type; Data = eventView.Data; return *this; }

		oper		TEView		()						const	{ return {Type, Data.cu8()}; }

		::llc::error_t	Save		(::llc::au0_t & output)	const	{
			llc_necs(llc::savePOD(output, Type));
			llc_necs(llc::saveView(output, Data));
			return 0;
		}

		::llc::error_t	Load		(::llc::vcu0_t & input)			{
			llc_necs(llc::loadPOD(input, Type));
			llc_necs(llc::loadView(input, Data));
			return 0;
		}

		tplt<tpnm _tETypeOther>
		::llc::error_t	ExtractChild(::llc::SEvent<_tETypeOther> & outputEvent)		const	{
			::llc::vcu0_t			input				= Data;
			llc_necs(outputEvent.Load(input));
			llc_event_printf("%s", ::llc::get_value_namep(outputEvent.Type)); 
			return 0; 
		}

		tplt<tpnm _tETypeOther>
		::llc::error_t	ExtractChild(::llc::SEView<_tETypeOther> & outputEvent)	const	{
			::llc::vcu0_t			input				= Data;
			llc_necs(outputEvent.Load(input));
			llc_event_printf("%s", ::llc::get_value_namep(outputEvent.Type)); 
			return 0; 
		}
	};

	tplt<tpnm T> using FEventHandler		= ::llc::function<::llc::error_t(      ::llc::SEvent<T>&)>;
	tplt<tpnm T> using FEventHandlerConst	= ::llc::function<::llc::error_t(const ::llc::SEvent<T>&)>;

	tplt<tpnm T> using PEvent 				= ::llc::pobj <::llc::SEvent<T>>;
	tplt<tpnm T> using TEventQueue 			= ::llc::apobj<::llc::SEvent<T>>;

	tplt <tpnm _tEvntParent, tpnm _tEvntChild>
	static	::llc::error_t	eventWrapChild		(::llc::SEvent<_tEvntParent> & parentEvent, _tEvntChild childEventType, ::llc::vcu0_t eventData) {
		::llc::SEView<_tEvntChild>	childEvent			= {childEventType, eventData};
		return childEvent.Save(parentEvent.Data);
	}

	tplt <tpnm _tEvntParent, tpnm _tEvntChild>
	static	::llc::error_t	eventEnqueueChild	(::llc::TEventQueue<_tEvntParent> & eventQueue, _tEvntParent parentEventType, _tEvntChild childEventType, ::llc::vcu0_t eventData) {
		::llc::PEvent<_tEvntParent>	parentEvent			= {};
		parentEvent->Type = parentEventType;
		llc_necs(llc::eventWrapChild(*parentEvent, childEventType, eventData));
		return eventQueue.push_back(parentEvent);
	}

	tplt <tpnm _tEvntParent, tpnm _tEvntChild, tpnm _tPOD>
	static	::llc::error_t	eventEnqueueChild	(::llc::TEventQueue<_tEvntParent> & eventQueue, _tEvntParent parentEventType, _tEvntChild childEventType, ::llc::view<const _tPOD> eventData) {
		return ::llc::eventEnqueueChild(eventQueue, parentEventType, childEventType, ::llc::vcu0_t{(const uint8_t*)eventData.begin(), eventData.byte_count()});
	}

	tplt <tpnm _tEvntParent, tpnm _tEvntChild, tpnm _tPOD>
	static	::llc::error_t	eventEnqueueChild	(::llc::TEventQueue<_tEvntParent> & eventQueue, _tEvntParent parentEventType, _tEvntChild childEventType, const _tPOD & childEventDataType) {
		return ::llc::eventEnqueueChild(eventQueue, parentEventType, childEventType, ::llc::vcu0_t{(const uint8_t*)&childEventDataType, szof(_tPOD)});
	}

	tplt<tpnm _tChildEvent, tpnm _tParentEvent>
	static	::llc::error_t	eventExtractAndHandle	(const ::llc::SEvent<_tParentEvent> & parentEvent, const ::llc::function<::llc::error_t (const ::llc::SEventView<_tChildEvent> &)> & funcHandleChild) {
		::llc::SEView<_tChildEvent>	childEvent; 
		llc_necs(parentEvent.ExtractChild(childEvent)); 
		return funcHandleChild(childEvent);
	}

	tydf ::llc::SEvent            <::llc::RESULT>	SEventResult;
	tydf ::llc::SEventView        <::llc::RESULT>	SEViewResult;
	tydf ::llc::FEventHandler     <::llc::RESULT>	FEventResult;
	tydf ::llc::FEventHandlerConst<::llc::RESULT>	FEventResultConst;
	tydf ::llc::SEvent            <::llc::COMMAND>	SEventCommand;
	tydf ::llc::SEventView        <::llc::COMMAND>	SEViewCommand;
	tydf ::llc::FEventHandler     <::llc::COMMAND>	FEventCommand;
	tydf ::llc::FEventHandlerConst<::llc::COMMAND>	FEventCommandConst;
}

#define llc_warning_unhandled_event(eventUnhandled)	warning_printf("Unhandled '%s' event: '%s' (0x%llX)(%lli)(%c)"	, ::llc::get_enum_namep((eventUnhandled).Type), ::llc::get_value_namep((eventUnhandled).Type), (uint64_t)(eventUnhandled).Type, (int64_t)(eventUnhandled).Type, char((eventUnhandled).Type ? (eventUnhandled).Type : ' '))
#define llc_warning_not_implemented(eventUnhandled) warning_printf("Implement for '%s'! '%s' (0x%llX)(%lli)(%c)"	, ::llc::get_enum_namep((eventUnhandled).Type), ::llc::get_value_namep((eventUnhandled).Type), (uint64_t)(eventUnhandled).Type, (int64_t)(eventUnhandled).Type, char((eventUnhandled).Type ? (eventUnhandled).Type : ' '))

#endif // LLC_EVENT_H_23627