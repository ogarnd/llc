#include "llc_array_ptr.h"
#include "llc_enum.h"

#include "llc_apod_serialize.h"

#ifndef LLC_EVENT_H_23627
#define LLC_EVENT_H_23627

#define llc_event_printf verbose_printf

namespace llc
{
	tplt<tpnm _tEventType>
	struct SEventView {
		typedef	_tEventType			T;
		typedef	SEventView<T>		TEView;

		T				Type		= {};
		::llc::vcu8		Data		= {};

		::llc::error_t	Save		(::llc::au8 & output)	const	{
			llc_necs(llc::savePOD (output, Type));
			llc_necs(llc::saveView(output, Data));
			return 0;
		}

		::llc::error_t	Load		(::llc::vcu8 & input)			{
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
		typedef _tEventType			T;
		typedef ::llc::SEView<T>	TEView;
		typedef ::llc::SEvent<T>	TEvent;

		T				Type		= {};
		::llc::au8		Data		= {};

						SEvent		(const TEvent &)							= default;
		constexpr		SEvent		(T type = {})						: Type(type) {}
						SEvent		(T type, const ::llc::vcu8 data)	: Type(type), Data(data.cu8()) {}
						SEvent		(const TEView & eventView)			: Type(eventView.Type), Data(eventView.Data) {}

		TEvent&			operator= 	(const TEvent &)				= default;
		TEvent&			operator= 	(const TEView & eventView)		{ Type = eventView.Type; Data = eventView.Data; return *this; }

		operator		TEView		()						const	{ return {Type, Data.cu8()}; }

		::llc::error_t	Save		(::llc::au8 & output)	const	{
			llc_necs(llc::savePOD(output, Type));
			llc_necs(llc::saveView(output, Data));
			return 0;
		}

		::llc::error_t	Load		(::llc::vcu8 & input)			{
			llc_necs(llc::loadPOD(input, Type));
			llc_necs(llc::loadView(input, Data));
			return 0;
		}

		tplt<tpnm _tETypeOther>
		::llc::error_t	ExtractChild(::llc::SEvent<_tETypeOther> & outputEvent)		const	{
			::llc::vcu8			input				= Data;
			llc_necs(outputEvent.Load(input));
			llc_event_printf("%s", ::llc::get_value_namep(outputEvent.Type)); 
			return 0; 
		}

		tplt<tpnm _tETypeOther>
		::llc::error_t	ExtractChild(::llc::SEView<_tETypeOther> & outputEvent)	const	{
			::llc::vcu8			input				= Data;
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
	static	::llc::error_t	eventWrapChild		(::llc::SEvent<_tEvntParent> & parentEvent, _tEvntChild childEventType, ::llc::vcu8 eventData) {
		::llc::SEView<_tEvntChild>	childEvent			= {childEventType, eventData};
		return childEvent.Save(parentEvent.Data);
	}

	tplt <tpnm _tEvntParent, tpnm _tEvntChild>
	static	::llc::error_t	eventEnqueueChild	(::llc::TEventQueue<_tEvntParent> & eventQueue, _tEvntParent parentEventType, _tEvntChild childEventType, ::llc::vcu8 eventData) {
		::llc::PEvent<_tEvntParent>	parentEvent			= {};
		parentEvent->Type = parentEventType;
		llc_necs(llc::eventWrapChild(*parentEvent, childEventType, eventData));
		return eventQueue.push_back(parentEvent);
	}

	tplt <tpnm _tEvntParent, tpnm _tEvntChild, tpnm _tPOD>
	static	::llc::error_t	eventEnqueueChild	(::llc::TEventQueue<_tEvntParent> & eventQueue, _tEvntParent parentEventType, _tEvntChild childEventType, ::llc::view<const _tPOD> eventData) {
		return ::llc::eventEnqueueChild(eventQueue, parentEventType, childEventType, ::llc::vcu8{(const uint8_t*)eventData.begin(), eventData.byte_count()});
	}

	tplt <tpnm _tEvntParent, tpnm _tEvntChild, tpnm _tPOD>
	static	::llc::error_t	eventEnqueueChild	(::llc::TEventQueue<_tEvntParent> & eventQueue, _tEvntParent parentEventType, _tEvntChild childEventType, const _tPOD & childEventDataType) {
		return ::llc::eventEnqueueChild(eventQueue, parentEventType, childEventType, ::llc::vcu8{(const uint8_t*)&childEventDataType, sizeof(_tPOD)});
	}

	tplt<tpnm _tChildEvent, tpnm _tParentEvent>
	static	::llc::error_t	eventExtractAndHandle	(const ::llc::SEvent<_tParentEvent> & parentEvent, const ::llc::function<::llc::error_t (const ::llc::SEventView<_tChildEvent> &)> & funcHandleChild) {
		::llc::SEView<_tChildEvent>	childEvent; 
		llc_necs(parentEvent.ExtractChild(childEvent)); 
		return funcHandleChild(childEvent);
	}

	typedef ::llc::SEvent            <::llc::RESULT>	SEventResult;
	typedef ::llc::SEventView        <::llc::RESULT>	SEViewResult;
	typedef ::llc::FEventHandler     <::llc::RESULT>	FEventResult;
	typedef ::llc::FEventHandlerConst<::llc::RESULT>	FEventResultConst;
	typedef ::llc::SEvent            <::llc::COMMAND>	SEventCommand;
	typedef ::llc::SEventView        <::llc::COMMAND>	SEViewCommand;
	typedef ::llc::FEventHandler     <::llc::COMMAND>	FEventCommand;
	typedef ::llc::FEventHandlerConst<::llc::COMMAND>	FEventCommandConst;
}

#define llc_warning_unhandled_event(eventUnhandled)	warning_printf("Unhandled '%s' event: '%s' (0x%llX)(%lli)(%c)"	, ::llc::get_enum_namep((eventUnhandled).Type), ::llc::get_value_namep((eventUnhandled).Type), (uint64_t)(eventUnhandled).Type, (int64_t)(eventUnhandled).Type, char((eventUnhandled).Type ? (eventUnhandled).Type : ' '))
#define llc_warning_not_implemented(eventUnhandled) warning_printf("Implement for '%s'! '%s' (0x%llX)(%lli)(%c)"	, ::llc::get_enum_namep((eventUnhandled).Type), ::llc::get_value_namep((eventUnhandled).Type), (uint64_t)(eventUnhandled).Type, (int64_t)(eventUnhandled).Type, char((eventUnhandled).Type ? (eventUnhandled).Type : ' '))

#endif // LLC_EVENT_H_23627