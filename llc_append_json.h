#include "llc_string_compose.h"

#ifndef LLC_APPEND_JSON_H
#define LLC_APPEND_JSON_H

namespace llc
{
				err_t	appendOpenKey	(asc_t & output, vcst_t key								, bool prependComma = false);
				err_t	appendKeyValue	(asc_t & output, vcst_t key, vcst_t value				, bool prependComma = false);
				err_t	appendKeyObject	(asc_t & output, vcst_t key, vcst_t valuesNotEnclosed	, bool prependComma = false);
				err_t	appendKeyList	(asc_t & output, vcst_t key, vcst_t valuesNotEnclosed	, bool prependComma = false);
				err_t	appendKeyString	(asc_t & output, vcst_t key, vcst_t value				, bool prependComma = false);
	tplN2ustin	err_t	appendKeyString	(asc_t & output, vcst_t key, sc_c (&value)[N]			, bool prependComma = false)	{ return appendKeyString(output, key, vcst_t{value}, prependComma); }
	stin		err_t	appendKeyString	(asc_t & output, vcst_t key, vcsc_c & value				, bool prependComma = false)	{ return appendKeyString(output, key, vcst_t{value}, prependComma); }

} // namespace 

#endif // LLC_APPEND_JSON_H