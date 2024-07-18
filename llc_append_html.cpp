#include "llc_append_html.h"
#include "llc_append_xml.h"

#ifndef LLC_ATMEL
llc::err_t	llc::appendHtmlPage	(::llc::achar & output, const ::llc::FAppend & funcAppendHead, const ::llc::FAppend & funcAppendBody) {
	return ::llc::appendXmlTag(output, "html", vcs{}, [&output, funcAppendHead, funcAppendBody]() {
		return ::llc::appendXmlTag(output, "head", vcs{}, [&output, funcAppendHead]() { return funcAppendHead(output); })
			+  ::llc::appendXmlTag(output, "body", vcs{}, [&output, funcAppendBody]() { return funcAppendBody(output); })
			;
	});
}
llc::err_t	llc::appendHtmlPage	(::llc::achar & output, const ::llc::FAppend & funcAppendCSS, const ::llc::FAppend & funcAppendJS, const ::llc::FAppend & funcAppendBody) {
	return ::llc::appendXmlTag(output, "html", vcs{}, [&output, funcAppendBody, funcAppendCSS, funcAppendJS]() {
		return ::llc::appendXmlTag(output, "head", vcs{}, [&output, funcAppendCSS, funcAppendJS]() {
			return ::llc::appendXmlTag(output, "style" , vcs{}, [&output, funcAppendCSS]() { return funcAppendCSS ? funcAppendCSS(output) : 0; })
				+  ::llc::appendXmlTag(output, "script", vcs{}, [&output, funcAppendJS ]() { return funcAppendJS  ? funcAppendJS (output) : 0; })
				;
		}) + ::llc::appendXmlTag(output, "body", vcs{}, [&output, funcAppendBody]() { return funcAppendBody(output); });
	});
}
llc::err_t	llc::appendHtmlPage	(::llc::achar & output, const ::llc::FAppend & funcAppendBody) {
	return ::llc::appendXmlTag(output, "html", vcs{}, [&output, funcAppendBody]() {
		return ::llc::appendXmlTag(output, "head", vcs{}, [&output]() {
			return ::llc::appendXmlTag(output, "link" , "rel=\"stylesheet\" href=\"/style/main.css\"")
				+  ::llc::appendXmlTag(output, "script", "src=\"/script/main.js\"")
				;
		}) + ::llc::appendXmlTag(output, "body", vcs{}, [&output, funcAppendBody]() { return funcAppendBody(output); });
	});
}
llc::err_t	llc::appendHtmlHead		(::llc::achar & output, ::llc::vcs tagAttributes, ::llc::vcs innerHtml)	{ return ::llc::appendXmlTag(output, "head", tagAttributes, innerHtml); }
llc::err_t	llc::appendHtmlBody		(::llc::achar & output, ::llc::vcs tagAttributes, ::llc::vcs innerHtml)	{ return ::llc::appendXmlTag(output, "body", tagAttributes, innerHtml); }
llc::err_t	llc::appendHtmlScript	(::llc::achar & output, ::llc::vcs tagAttributes, ::llc::vcs innerHtml)	{ return ::llc::appendXmlTag(output, "script", tagAttributes, innerHtml); }
llc::err_t	llc::appendHtmlTable	(::llc::achar & output, ::llc::vcs tagAttributes, ::llc::vcs innerHtml)	{ return ::llc::appendXmlTag(output, "table", tagAttributes, innerHtml); }
llc::err_t	llc::appendHtmlTableRow	(::llc::achar & output, ::llc::vcs tagAttributes, ::llc::vcs innerHtml)	{ return ::llc::appendXmlTag(output, "tr", tagAttributes, innerHtml); }
llc::err_t	llc::appendHtmlTableCol	(::llc::achar & output, ::llc::vcs tagAttributes, ::llc::vcs innerHtml)	{ return ::llc::appendXmlTag(output, "td", tagAttributes, innerHtml); }
#endif