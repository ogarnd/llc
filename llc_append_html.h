#include "llc_string_compose.h"

#ifndef LLC_APPEND_HTML_H
#define LLC_APPEND_HTML_H

namespace llc
{
	llc::err_t	appendHtmlHead		(::llc::achar & output, ::llc::vcs tagAttributes = {}, ::llc::vcs innerHtml = {});
	llc::err_t	appendHtmlBody		(::llc::achar & output, ::llc::vcs tagAttributes = {}, ::llc::vcs innerHtml = {});
	llc::err_t	appendHtmlScript	(::llc::achar & output, ::llc::vcs tagAttributes = {}, ::llc::vcs innerHtml = {});
	llc::err_t	appendHtmlTable		(::llc::achar & output, ::llc::vcs tagAttributes = {}, ::llc::vcs innerHtml = {});
	llc::err_t	appendHtmlTableRow	(::llc::achar & output, ::llc::vcs tagAttributes = {}, ::llc::vcs innerHtml = {});
	llc::err_t	appendHtmlTableCol	(::llc::achar & output, ::llc::vcs tagAttributes = {}, ::llc::vcs innerHtml = {});
	llc::err_t	appendHtmlPage		(::llc::achar & output, const ::llc::FAppend & funcAppendCSS, const ::llc::FAppend & funcAppendJS, const ::llc::FAppend & funcAppendBody);
	llc::err_t	appendHtmlPage		(::llc::achar & output, const ::llc::FAppend & funcAppendHead, const ::llc::FAppend & funcAppendBody)	
	llc::err_t	appendHtmlPage		(::llc::achar & output, const ::llc::FAppend & funcAppendBody);
} // namespace 

#endif // LLC_APPEND_HTML_H