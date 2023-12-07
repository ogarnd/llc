#include "llc_append_css.h"

llc::err_t	llc::appendCSSBorderWidth			(::llc::achar & output, uint8_t borderWidth, bool absoluteSize)	{
	char				cssBuffer	[32]		= {};
	stacxpr char		cssFormat	[]			= "border-width:%u%s;";
	const char			* unit					= absoluteSize ? "px" : "%";
	const int32_t		len						= ::llc::sprintf_s(cssBuffer, cssFormat, borderWidth, unit);
	llc_necs(output.append_string(cssBuffer));
	return len;
}
llc::err_t	llc::appendCSSControlWidth			(::llc::achar & output, uint16_t outerLimit, bool absoluteSize)	{
	char				cssBuffer	[24]		= {};
	stacxpr char		cssFormat	[]			= "width:%u%s;";
	const char			* unit					= absoluteSize ? "px" : "%";
	const int32_t 		len						= ::llc::sprintf_s(cssBuffer, cssFormat, outerLimit, unit);
	llc_necs(output.append_string(cssBuffer));
	return len;
}
llc::err_t	llc::appendCSSControlHeight		(::llc::achar & output, uint16_t outerLimit, bool absoluteSize)	{
	char				cssBuffer	[24]		= {};
	stacxpr char		cssFormat	[]			= "height:%u%s;";
	const char			* unit					= absoluteSize ? "px" : "%";
	const int32_t 		len						= ::llc::sprintf_s(cssBuffer, cssFormat, outerLimit, unit);
	llc_necs(output.append_string(cssBuffer));
	return len;
}
llc::err_t	llc::appendCSSControlSize			(::llc::achar & output, ::llc::n2u16 outerLimit, bool absoluteSize)	{
	return appendCSSControlWidth(output, outerLimit.x, absoluteSize) + appendCSSControlHeight(output, outerLimit.y, absoluteSize);
}
llc::err_t	llc::appendCSSSizeWithBorderWidthAbsolute	(::llc::achar & output, ::llc::n2u16 outerLimit, uint8_t borderWidth)	{
	return appendCSSControlSize(output, ::llc::n2i32{outerLimit.x - borderWidth * 2, outerLimit.y - borderWidth * 2}.u16(), true) + appendCSSBorderWidth(output, borderWidth);
}
llc::err_t	llc::appendCSSSizeWithBorderWidthRelative	(::llc::achar & output, ::llc::n2u16 outerLimit, uint8_t borderWidth)	{
	const ::llc::n2u16	contentLimit 			= llc::n2i32{outerLimit.x - borderWidth * 2, outerLimit.y - borderWidth * 2}.u16();
	char				cssBuffer	[128]		= {};
	stacxpr char		cssFormat	[]			= "width:calc(%u%% - %upx);height:calc(%u%% - %upx);";
	const int32_t 		len						= ::llc::sprintf_s(cssBuffer, cssFormat, outerLimit.x, borderWidth * 2, outerLimit.y, borderWidth * 2);
	llc_necs(output.append_string(cssBuffer));
	return len + appendCSSBorderWidth(output, borderWidth);
}
llc::err_t	llc::appendCSSSizeWithBorderWidth	(::llc::achar & output, ::llc::n2u16 outerLimit, uint8_t borderWidth, bool absoluteSize)	{
	return absoluteSize 
		? appendCSSSizeWithBorderWidthAbsolute(output, outerLimit, borderWidth)
		: appendCSSSizeWithBorderWidthRelative(output, outerLimit, borderWidth)
		;
}
