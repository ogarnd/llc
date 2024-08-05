#include "llc_string_compose.h"

#ifndef LLC_APPEND_JSON_H
#define LLC_APPEND_JSON_H

namespace llc
{
				err_t	appendOpenKey	(::llc::asc_t & output, ::llc::vcs key								, bool prependComma = false);
				err_t	appendKeyValue	(::llc::asc_t & output, ::llc::vcs key, ::llc::vcs value			, bool prependComma = false);
				err_t	appendKeyObject	(::llc::asc_t & output, ::llc::vcs key, ::llc::vcs valuesNotEnclosed, bool prependComma = false);
				err_t	appendKeyList	(::llc::asc_t & output, ::llc::vcs key, ::llc::vcs valuesNotEnclosed, bool prependComma = false);
				err_t	appendKeyString	(::llc::asc_t & output, ::llc::vcs key, ::llc::vcs value			, bool prependComma = false);
	tplN2ustin	err_t	appendKeyString	(::llc::asc_t & output, ::llc::vcs key, const char(&value)[N]	, bool prependComma = false)	{ return appendKeyString(output, key, ::llc::vcs{value}, prependComma); }
	stin		err_t	appendKeyString	(::llc::asc_t & output, ::llc::vcs key, ::llc::vcsc_c & value	, bool prependComma = false)	{ return appendKeyString(output, key, ::llc::vcs{value}, prependComma); }

} // namespace 

#endif // LLC_APPEND_JSON_H