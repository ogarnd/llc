#include "llc_label.h"
#include "llc_array_pod.h"

#include <string>

#ifndef LLC_STD_STRING_H
#define LLC_STD_STRING_H

namespace llc
{
	ndstain	::llc::vcc		tovcc   (const std::string & srcstr)							{ return srcstr.size() ? ::llc::vcc{&srcstr[0], (uint32_t)srcstr.size()} : ::llc::vcs{}; }
	stainli	::llc::error_t	tovcc   (::llc::vcc		& output, const std::string & srcstr)	{ return (output = ::llc::tovcc(srcstr)).size(); }
	stainli	::llc::error_t	tolabel (::llc::vcc		& output, const std::string & srcstr)	{ return (output = ::llc::label(::llc::tovcc(srcstr))).size(); }
	stainli	::llc::error_t	toachar (::llc::asc_t	& output, const std::string & srcstr)	{ llc_necs(output.reserve((uint32_t)srcstr.length())); return (output = ::llc::tovcc(srcstr)).size(); }
	stainli	::llc::error_t	append 	(::llc::asc_t	& output, const std::string & srcstr)	{ return output.append(::llc::tovcc(srcstr)); }

	ndstain	::llc::vcc		tolabel (const std::string & srcstr) 		{ return ::llc::label(::llc::tovcc(srcstr)); }
	ndstain	::llc::asc_t	toachar (const std::string & srcstr) 		{ return ::llc::tovcc(srcstr); }
} // namespace llc

#endif // LLC_STD_STRING_H
