#include "llc_color.h"
#include "llc_view.h"

#ifndef LLC_VIEW_COLOR_H_23627
#define LLC_VIEW_COLOR_H_23627

namespace llc
{
	typedef	::llc::view<::llc::frgba	>		vrgbaf	, vfrgba	;
	typedef	::llc::view<::llc::u8bgra	>		vbgra	, v8bgra	;
	typedef	::llc::view<::llc::u8bgr	>		vbgr	, v8bgr		;
	typedef	::llc::view<::llc::u8rgba	>		vrgba	, v8rgba	;
	typedef	::llc::view<::llc::u8rgb	>		vrgb	, v8rgb		;

	typedef	::llc::view<const ::llc::frgba	>	vcrgbaf	, vcfrgba	;
	typedef	::llc::view<const ::llc::u8bgra	>	vcbgra	, vc8bgra	;
	typedef	::llc::view<const ::llc::u8bgr	>	vcbgr	, vc8bgr		;
	typedef	::llc::view<const ::llc::u8rgba	>	vcrgba	, vc8rgba	;
	typedef	::llc::view<const ::llc::u8rgb	>	vcrgb	, vc8rgb		;

	::llc::error_t 		vcu82bgra8	(const ::llc::vcu0_t & bytes, ::llc::bgra8 & colorToSet);
	::llc::error_t 		vcu82bgr8	(const ::llc::vcu0_t & bytes, ::llc::bgr8 & colorToSet);
} // namespace

#endif // LLC_VIEW_COLOR_H_23627
