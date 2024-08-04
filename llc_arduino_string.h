#include "llc_arduino_stream.h"

#include "llc_label.h"
#include "llc_array_pod.h"

#ifndef LLC_ARDUINO_STRING_H
#define LLC_ARDUINO_STRING_H

#ifdef LLC_ARDUINO
#	include <WString.h>

namespace llc
{
	ndsi	::llc::vcc		tovcc   (const String & srcstr)						    	{ return srcstr.length() ? ::llc::vcc{srcstr.begin(), srcstr.length()} : vcs{}; }
	stin	::llc::error_t	tovcc   (::llc::vcc		& output, const String	& srcstr)	{ return (output = ::llc::tovcc(srcstr)).size(); }
	stin	::llc::error_t	tolabel (::llc::vcc		& output, const String	& srcstr)	{ return (output = ::llc::label(::llc::tovcc(srcstr))).size(); }
	stin	::llc::error_t	toachar (::llc::asc_t	& output, const String	& srcstr)	{ llc_necs(output.reserve(srcstr.length())); return (output = ::llc::tovcc(srcstr)).size(); }
	stin	::llc::error_t	append 	(::llc::asc_t	& output, const String	& srcstr)	{ return output.append(::llc::tovcc(srcstr)); }

	ndsi	::llc::vcc		tolabel (const String & srcstr)	{ return ::llc::label(::llc::tovcc(srcstr)); }
	ndsi	::llc::asc_t	toachar (const String & srcstr)	{ return ::llc::tovcc(srcstr); }
	ndsi	::llc::vcc		str		(const String & srcstr)	{ return ::llc::tovcc(srcstr); }
	ndsi	uint32_t 		size	(const String & srcstr)	{ return srcstr.length(); }
} // namespace
#endif // LLC_ARDUINO

#endif // LLC_ARDUINO_STRING_H
