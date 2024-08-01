#include "llc_string_compose.h"

#ifndef LLC_APPEND_JSON_H
#define LLC_APPEND_JSON_H

namespace llc
{
	llc::err_t			appendOpenKey	(::llc::asc_t & output, ::llc::vcs key								, bool prependComma = false);
	llc::err_t			appendKeyValue	(::llc::asc_t & output, ::llc::vcs key, ::llc::vcs value			, bool prependComma = false);
	llc::err_t			appendKeyObject	(::llc::asc_t & output, ::llc::vcs key, ::llc::vcs valuesNotEnclosed, bool prependComma = false);
	llc::err_t			appendKeyList	(::llc::asc_t & output, ::llc::vcs key, ::llc::vcs valuesNotEnclosed, bool prependComma = false);
	llc::err_t			appendKeyString	(::llc::asc_t & output, ::llc::vcs key, ::llc::vcs value			, bool prependComma = false);
	template<size_t nSize>
	stainli	llc::err_t	appendKeyString	(::llc::asc_t & output, ::llc::vcs key, const char(&value)[nSize]	, bool prependComma = false)	{ return appendKeyString(output, key, ::llc::vcs{value}, prependComma); }
	stainli	llc::err_t	appendKeyString	(::llc::asc_t & output, ::llc::vcs key, const ::llc::vcc & value	, bool prependComma = false)	{ return appendKeyString(output, key, ::llc::vcs{value}, prependComma); }

} // namespace 

#endif // LLC_APPEND_JSON_H