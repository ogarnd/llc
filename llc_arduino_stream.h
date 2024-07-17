#include "llc_typeint.h"

#ifndef LLC_ARDUINO_STREAM_H
#define LLC_ARDUINO_STREAM_H

#ifdef LLC_ARDUINO
#include <Stream.h>

namespace llc
{
	//ndstain	::llc::vcc		tovcc   (const Stream   & srcstr)							{ return srcstr.length() ? ::llc::vcc{srcstr.begin(), srcstr.length()} : vcs{}; }
	//stainli	::llc::error_t	tovcc   (::llc::vcc		& output, const Stream	& srcstr)	{ return (output = ::llc::tovcc(srcstr)).size(); }
	//stainli	::llc::error_t	tolabel (::llc::vcc		& output, const Stream	& srcstr)	{ return (output = ::llc::label(::llc::tovcc(srcstr))).size(); }
	//stainli	::llc::error_t	toachar (::llc::achar	& output, const Stream	& srcstr)	{ llc_necs(output.reserve(srcstr.length())); return (output = ::llc::tovcc(srcstr)).size(); }
	//stainli	::llc::error_t	append 	(::llc::achar	& output, const Stream	& srcstr)	{ return output.append(::llc::tovcc(srcstr)); }

	//ndstain	::llc::vcc		tolabel (const Stream & srcstr)	{ return ::llc::label(::llc::tovcc(srcstr)); }
	//ndstain	::llc::achar	toachar (const Stream & srcstr)	{ return ::llc::tovcc(srcstr); }
	//ndstain	::llc::vcc		str		(const Stream & srcstr)	{ return ::llc::tovcc(srcstr); }
	ndstain	uint32_t 		size	(const Stream & srcstr)	{ return (*((Stream*)&srcstr)).available(); }
	ndstain	uint32_t 		size	(Stream & srcstr)		{ return srcstr.available(); }
} // namespace
#endif // LLC_ARDUINO

#endif // LLC_ARDUINO_STREAM_H
