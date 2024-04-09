#include "llc_system_event.h"
#include "llc_geometry2.h"
#include "llc_n2.h"

#ifndef LLC_EVENT_RASTER_H
#define LLC_EVENT_RASTER_H

namespace llc
{
	GDEFINE_ENUM_TYPE (EVENT_RASTER, uint8_t);
	GDEFINE_ENUM_VALUE(EVENT_RASTER, Clear			,  0);
	GDEFINE_ENUM_VALUE(EVENT_RASTER, Pixel			,  1);
	GDEFINE_ENUM_VALUE(EVENT_RASTER, Line			,  2);
	GDEFINE_ENUM_VALUE(EVENT_RASTER, Outline		,  3);
	GDEFINE_ENUM_VALUE(EVENT_RASTER, Fill			,  4);
	GDEFINE_ENUM_VALUE(EVENT_RASTER, BitBlt			,  5);
	GDEFINE_ENUM_VALUE(EVENT_RASTER, Text			,  6);
	GDEFINE_ENUM_VALUE(EVENT_RASTER, Font			,  7);
	GDEFINE_ENUM_VALUE(EVENT_RASTER, FontIndex		,  8);
	GDEFINE_ENUM_VALUE(EVENT_RASTER, FontColor		,  9);
	GDEFINE_ENUM_VALUE(EVENT_RASTER, FontBackground	, 10);
	GDEFINE_ENUM_VALUE(EVENT_RASTER, Color			, 11);
	GDEFINE_ENUM_VALUE(EVENT_RASTER, ColorIndex		, 12);
	GDEFINE_ENUM_VALUE(EVENT_RASTER, Palette		, 13);
	GDEFINE_ENUM_VALUE(EVENT_RASTER, PaletteIndex	, 14);
	GDEFINE_ENUM_VALUE(EVENT_RASTER, PaletteColor	, 15);

	typedef ::llc::SEvent            <EVENT_RASTER>	SEventRaster;
	typedef ::llc::SEventView        <EVENT_RASTER>	SEViewRaster;
	typedef ::llc::FEventHandler     <EVENT_RASTER>	FRasterEvent;
	typedef ::llc::FEventHandlerConst<EVENT_RASTER>	FRasterEventConst;

	template<typename _t>
	stainli	::llc::error_t	eventEnqueueChild	(::llc::apobj<::llc::SEventSystem> & queue, ::llc::EVENT_RASTER eventType, _t & eventData)	{ 
		return ::llc::eventEnqueueChild(queue, ::llc::SYSTEM_EVENT_Raster, eventType, eventData); 
	}

	stainli	::llc::error_t	eventEnqueueRasterClear			(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)	{ return ::llc::eventEnqueueChild(queue, ::llc::EVENT_RASTER_Clear			, key); }
	stainli	::llc::error_t	eventEnqueueRasterOutline		(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)	{ return ::llc::eventEnqueueChild(queue, ::llc::EVENT_RASTER_Outline		, key); }
	stainli	::llc::error_t	eventEnqueueRasterFill			(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)	{ return ::llc::eventEnqueueChild(queue, ::llc::EVENT_RASTER_Fill			, key); }
	stainli	::llc::error_t	eventEnqueueRasterBitBlt		(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)	{ return ::llc::eventEnqueueChild(queue, ::llc::EVENT_RASTER_BitBlt			, key); }
	stainli	::llc::error_t	eventEnqueueRasterText			(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)	{ return ::llc::eventEnqueueChild(queue, ::llc::EVENT_RASTER_Text			, key); }
	stainli	::llc::error_t	eventEnqueueRasterFont			(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)	{ return ::llc::eventEnqueueChild(queue, ::llc::EVENT_RASTER_Font			, key); }
	stainli	::llc::error_t	eventEnqueueRasterFontIndex		(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)	{ return ::llc::eventEnqueueChild(queue, ::llc::EVENT_RASTER_FontIndex		, key); }
	stainli	::llc::error_t	eventEnqueueRasterColor			(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)	{ return ::llc::eventEnqueueChild(queue, ::llc::EVENT_RASTER_Color			, key); }
	stainli	::llc::error_t	eventEnqueueRasterColorIndex	(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)	{ return ::llc::eventEnqueueChild(queue, ::llc::EVENT_RASTER_ColorIndex		, key); }
	stainli	::llc::error_t	eventEnqueueRasterPalette		(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)	{ return ::llc::eventEnqueueChild(queue, ::llc::EVENT_RASTER_Palette		, key); }
	stainli	::llc::error_t	eventEnqueueRasterPaletteIndex	(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)	{ return ::llc::eventEnqueueChild(queue, ::llc::EVENT_RASTER_PaletteIndex	, key); }
	stainli	::llc::error_t	eventEnqueueRasterPaletteColor	(::llc::apobj<::llc::SEventSystem> & queue, uint8_t key)	{ return ::llc::eventEnqueueChild(queue, ::llc::EVENT_RASTER_PaletteColor	, key); }
} // namespace 

#endif // LLC_EVENT_RASTER_H
