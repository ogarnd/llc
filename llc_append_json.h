#include "llc_string_compose.h"

#ifndef LLC_APPEND_JSON_H
#define LLC_APPEND_JSON_H

namespace llc
{
	llc::err_t			appendKeyValue			(::llc::achar & output, ::llc::vcs key, ::llc::vcs value);
	llc::err_t			appendKeyString			(::llc::achar & output, ::llc::vcs key, ::llc::vcs value);
	template<size_t nSize>
	stainli	llc::err_t	appendKeyString			(::llc::achar & output, ::llc::vcs key, const char(&value)[nSize])	{ return appendKeyString(output, key, ::llc::vcs{value}); }
	stainli	llc::err_t	appendKeyString			(::llc::achar & output, ::llc::vcs key, const ::llc::vcc & value)	{ return appendKeyString(output, key, ::llc::vcs{value}); }
	llc::err_t			appendKeyObject			(::llc::achar & output, ::llc::vcs key, ::llc::vcs itemsNotEnclosed);
	llc::err_t			appendKeyList			(::llc::achar & output, ::llc::vcs key, ::llc::vcs itemsNotEnclosed);
	llc::err_t			appendOpenKey			(::llc::achar & output, ::llc::vcs key);

} // namespace 

#endif // LLC_APPEND_JSON_H