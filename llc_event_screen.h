#include "llc_system_event.h"
#include "llc_n2.h"

#ifndef LLC_EVENT_SCREEN_H_23627
#define LLC_EVENT_SCREEN_H_23627

namespace llc
{
	GDEFINE_ENUM_TYPE (EVENT_SCREEN, uint8_t);
	GDEFINE_ENUM_VALUE(EVENT_SCREEN, Create			,  0);
	GDEFINE_ENUM_VALUE(EVENT_SCREEN, Destroy		,  1);
	GDEFINE_ENUM_VALUE(EVENT_SCREEN, Close			,  2);
	GDEFINE_ENUM_VALUE(EVENT_SCREEN, Move			,  3);
	GDEFINE_ENUM_VALUE(EVENT_SCREEN, Activate		,  4);
	GDEFINE_ENUM_VALUE(EVENT_SCREEN, Deactivate		,  5);
	GDEFINE_ENUM_VALUE(EVENT_SCREEN, Resize			,  6);
	GDEFINE_ENUM_VALUE(EVENT_SCREEN, Redraw			,  7);
	GDEFINE_ENUM_VALUE(EVENT_SCREEN, Show			,  8);
	GDEFINE_ENUM_VALUE(EVENT_SCREEN, Hide			,  9);
	GDEFINE_ENUM_VALUE(EVENT_SCREEN, Constraints	, 10);

	typedef ::llc::SEvent            <EVENT_SCREEN>	SScreenEvent;
	typedef ::llc::SEventView        <EVENT_SCREEN>	SScreenEventView;
	typedef ::llc::FEventHandler     <EVENT_SCREEN>	FScreenEvent;
	typedef ::llc::FEventHandlerConst<EVENT_SCREEN>	FScreenEventConst;

	struct SEventArgsScreenCreate {
		::llc::n2u16		Size;
#ifdef LLC_WINDOWS
		CREATESTRUCT		PlatformDetail;
#endif
	};

	stainli	::llc::error_t	eventEnqueueScreenDestroy		(::llc::apobj<::llc::SEventSystem> & queue)						{ return ::llc::eventEnqueueChild(queue, ::llc::SYSTEM_EVENT_Screen, ::llc::EVENT_SCREEN_Destroy, {}); }
	stainli	::llc::error_t	eventEnqueueScreenClose			(::llc::apobj<::llc::SEventSystem> & queue)						{ return ::llc::eventEnqueueChild(queue, ::llc::SYSTEM_EVENT_Screen, ::llc::EVENT_SCREEN_Close  , {}); }
	stainli	::llc::error_t	eventEnqueueScreenCreate		(::llc::apobj<::llc::SEventSystem> & queue, const SEventArgsScreenCreate & key)	{ return ::llc::eventEnqueueChild(queue, ::llc::SYSTEM_EVENT_Screen, ::llc::EVENT_SCREEN_Create, key); }
	stainli	::llc::error_t	eventEnqueueScreenActivate		(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)		{ return ::llc::eventEnqueueChild(queue, ::llc::SYSTEM_EVENT_Screen, ::llc::EVENT_SCREEN_Activate	, key); }
	stainli	::llc::error_t	eventEnqueueScreenDeactivate	(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)		{ return ::llc::eventEnqueueChild(queue, ::llc::SYSTEM_EVENT_Screen, ::llc::EVENT_SCREEN_Deactivate	, key); }
	stainli	::llc::error_t	eventEnqueueScreenRedraw		(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)		{ return ::llc::eventEnqueueChild(queue, ::llc::SYSTEM_EVENT_Screen, ::llc::EVENT_SCREEN_Redraw		, key); }
	stainli	::llc::error_t	eventEnqueueScreenShow			(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)		{ return ::llc::eventEnqueueChild(queue, ::llc::SYSTEM_EVENT_Screen, ::llc::EVENT_SCREEN_Show		, key); }
	stainli	::llc::error_t	eventEnqueueScreenHide			(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)		{ return ::llc::eventEnqueueChild(queue, ::llc::SYSTEM_EVENT_Screen, ::llc::EVENT_SCREEN_Hide		, key); }
	stainli	::llc::error_t	eventEnqueueScreenConstraints	(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)		{ return ::llc::eventEnqueueChild(queue, ::llc::SYSTEM_EVENT_Screen, ::llc::EVENT_SCREEN_Constraints, key); }
	stainli	::llc::error_t	eventEnqueueScreenMove			(::llc::apobj<::llc::SEventSystem> & queue, ::llc::n2u16 coord)	{ return ::llc::eventEnqueueChild(queue, ::llc::SYSTEM_EVENT_Screen, ::llc::EVENT_SCREEN_Move		, coord); }
	stainli	::llc::error_t	eventEnqueueScreenResize		(::llc::apobj<::llc::SEventSystem> & queue, ::llc::n2u16 size)	{ return ::llc::eventEnqueueChild(queue, ::llc::SYSTEM_EVENT_Screen, ::llc::EVENT_SCREEN_Resize		, size); }
} // namespace 

#endif // LLC_EVENT_SCREEN_H_23627
