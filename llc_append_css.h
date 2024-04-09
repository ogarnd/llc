#include "llc_string_compose.h"
#include "llc_n2.h"

#ifndef LLC_APPEND_CSS_H
#define LLC_APPEND_CSS_H

namespace llc
{
	tplt<tpnm... _tArgs>
	llc::err_t			appendCSSTag							(::llc::achar & output, llc::vcs tagName, _tArgs&&... cssAttributes)					{ return llc::append_strings(output, tagName, '{', cssAttributes..., '}', '\n'); }	
	llc::err_t			appendCSSBorderWidth					(::llc::achar & output, uint8_t borderWidth, bool absoluteSize = true);
	llc::err_t			appendCSSControlWidth					(::llc::achar & output, uint16_t outerLimit, bool absoluteSize = false);
	llc::err_t			appendCSSControlHeight					(::llc::achar & output, uint16_t outerLimit, bool absoluteSize = false);
	llc::err_t			appendCSSControlSize					(::llc::achar & output, ::llc::n2u16 outerLimit, bool absoluteSize = false);
	llc::err_t			appendCSSSizeWithBorderWidthAbsolute	(::llc::achar & output, ::llc::n2u16 outerLimit, uint8_t borderWidth);
	llc::err_t			appendCSSSizeWithBorderWidthRelative	(::llc::achar & output, ::llc::n2u16 outerLimit, uint8_t borderWidth);
	llc::err_t			appendCSSSizeWithBorderWidth			(::llc::achar & output, ::llc::n2u16 outerLimit, uint8_t borderWidth, bool absoluteSize = false);
} // namespace 

#endif // LLC_APPEND_CSS_H