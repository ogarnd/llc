#include "llc_arduino_stream.h"

#include "llc_label.h"
#include "llc_array_pod.h"

#ifndef LLC_ARDUINO_STRING_H
#define LLC_ARDUINO_STRING_H

#ifdef LLC_ARDUINO
#	include <WString.h>

namespace llc
{
	ndstain	::llc::vcc		tovcc   (const String & srcstr)						    	{ return srcstr.length() ? ::llc::vcc{srcstr.begin(), srcstr.length()} : vcs{}; }
	stainli	::llc::error_t	tovcc   (::llc::vcc		& output, const String	& srcstr)	{ return (output = ::llc::tovcc(srcstr)).size(); }
	stainli	::llc::error_t	tolabel (::llc::vcc		& output, const String	& srcstr)	{ return (output = ::llc::label(::llc::tovcc(srcstr))).size(); }
	stainli	::llc::error_t	toachar (::llc::achar	& output, const String	& srcstr)	{ llc_necs(output.reserve(srcstr.length())); return (output = ::llc::tovcc(srcstr)).size(); }
	stainli	::llc::error_t	append 	(::llc::achar	& output, const String	& srcstr)	{ return output.append(::llc::tovcc(srcstr)); }

	ndstain	::llc::vcc		tolabel (const String & srcstr)	{ return ::llc::label(::llc::tovcc(srcstr)); }
	ndstain	::llc::achar	toachar (const String & srcstr)	{ return ::llc::tovcc(srcstr); }
	ndstain	::llc::vcc		str		(const String & srcstr)	{ return ::llc::tovcc(srcstr); }
	ndstain	uint32_t 		size	(const String & srcstr)	{ return srcstr.length(); }
} // namespace
#endif // LLC_ARDUINO

#endif // LLC_ARDUINO_STRING_H
