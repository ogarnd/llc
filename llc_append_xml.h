#include "llc_string_compose.h"

#ifndef LLC_APPEND_XML_H
#define LLC_APPEND_XML_H

namespace llc
{
	llc::err_t	appendXmlAttr		(::llc::asc_t & output, ::llc::vcs attrName, ::llc::vcs attrValue = {});
	llc::err_t	appendXmlOpenTag	(::llc::asc_t & output, ::llc::vcs tagName);
	llc::err_t	appendXmlTagVoid	(::llc::asc_t & output, ::llc::vcs tagName, ::llc::vcs tagAttributes = {});
	llc::err_t	appendXmlTagOpening	(::llc::asc_t & output, ::llc::vcs tagName, ::llc::vcs tagAttributes = {});
	llc::err_t	appendXmlTagClosing	(::llc::asc_t & output, ::llc::vcs tagName);
	llc::err_t	appendXmlTag		(::llc::asc_t & output, ::llc::vcs tagName, ::llc::vcs tagAttributes = {}, ::llc::vcs innerHtml = {});
	llc::err_t	appendXmlTag		(::llc::asc_t & output, ::llc::vcs tagName, ::llc::vcs tagAttributes, const FAppend & funcAppend);
	llc::err_t	appendXmlTag		(::llc::asc_t & output, ::llc::vcs tagName, ::llc::vcs tagAttributes, const ::llc::function<llc::err_t()> & funcAppend);
	llc::err_t	appendXmlTag		(::llc::asc_t & output, ::llc::vcs tagName, const ::llc::function<llc::err_t()> & funcAppendAttributes, const ::llc::function<llc::err_t()> & funcAppend);

} // namespace 

#endif // LLC_APPEND_XML_H