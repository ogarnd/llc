#include "llc_append_json.h"

llc::err_t	llc::appendOpenKey		(::llc::achar & output, ::llc::vcs key)							{ return ::llc::append_strings(output, '"', key, "\":"); }
llc::err_t	llc::appendKeyValue		(::llc::achar & output, ::llc::vcs key, ::llc::vcs value)		{ return ::llc::append_strings(output, '"', key, "\":", value); }
llc::err_t	llc::appendKeyString	(::llc::achar & output, ::llc::vcs key, ::llc::vcs value)		{ return ::llc::append_strings(output, '"', key, "\":", '{',  value, '}'); }
llc::err_t	llc::appendKeyList		(::llc::achar & output, ::llc::vcs key, ::llc::vcs listItems)	{ return ::llc::append_strings(output, '"', key, "\":", '[',  listItems, ']'); }
llc::err_t	llc::appendKeyObject	(::llc::achar & output, ::llc::vcs key, ::llc::vcs listItems)	{ return ::llc::append_strings(output, '"', key, "\":", '{',  listItems, '}'); }
