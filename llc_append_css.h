#include "llc_string_compose.h"
#include "llc_n2.h"

#ifndef LLC_APPEND_CSS_H
#define LLC_APPEND_CSS_H

namespace llc
{
	tplt<tpnm... _tArgs>
	llc::err_t			appendCSSTag							(::llc::asc_t & output, llc::vcs tagName, _tArgs&&... cssAttributes)					{ return llc::append_strings(output, tagName, '{', cssAttributes..., '}', '\n'); }	
	llc::err_t			appendCSSBorderWidth					(::llc::asc_t & output, uint8_t borderWidth, bool absoluteSize = true);
	llc::err_t			appendCSSControlWidth					(::llc::asc_t & output, uint16_t outerLimit, bool absoluteSize = false);
	llc::err_t			appendCSSControlHeight					(::llc::asc_t & output, uint16_t outerLimit, bool absoluteSize = false);
	llc::err_t			appendCSSControlSize					(::llc::asc_t & output, ::llc::n2u1_t outerLimit, bool absoluteSize = false);
	llc::err_t			appendCSSSizeWithBorderWidthAbsolute	(::llc::asc_t & output, ::llc::n2u1_t outerLimit, uint8_t borderWidth);
	llc::err_t			appendCSSSizeWithBorderWidthRelative	(::llc::asc_t & output, ::llc::n2u1_t outerLimit, uint8_t borderWidth);
	llc::err_t			appendCSSSizeWithBorderWidth			(::llc::asc_t & output, ::llc::n2u1_t outerLimit, uint8_t borderWidth, bool absoluteSize = false);
} // namespace 

#endif // LLC_APPEND_CSS_H