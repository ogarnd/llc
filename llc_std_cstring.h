#include "llc_label.h"
#include "llc_array_pod.h"

#include <string>

#ifndef LLC_STD_CSTRING_H
#define LLC_STD_CSTRING_H

namespace llc
{
	ndstain	::llc::vcc		tovcc   (const char * srcstr)							{ return srcstr ? ::llc::vcs{srcstr, (uint32_t)-1} : ::llc::vcs{}; }
	stainli	::llc::error_t	tovcc   (::llc::vcc		& output, const char * srcstr)	{ return (output = ::llc::tovcc(srcstr)).size(); }
	stainli	::llc::error_t	tolabel (::llc::vcc		& output, const char * srcstr)	{ return (output = ::llc::label(::llc::tovcc(srcstr))).size(); }
	stainli	::llc::error_t	toachar (::llc::achar	& output, const char * srcstr)	{ 
		const ::llc::vcc			vsrc	= ::llc::tovcc(srcstr);
		llc_necs(output.reserve(vsrc.size())); 
		return (output = vsrc).size(); 
	}
	stainli	::llc::error_t	append 	(::llc::achar	& output, const char * srcstr)	{ return output.append(::llc::tovcc(srcstr)); }

	ndstain	::llc::vcc		tolabel (const char * srcstr)	{ return ::llc::label(::llc::tovcc(srcstr)); }
	ndstain	::llc::achar	toachar (const char * srcstr)	{ return ::llc::tovcc(srcstr); }
} // namespace llc

#endif // LLC_STD_CSTRING_H
