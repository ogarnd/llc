#include "llc_append_xml.h"

llc::err_t	llc::appendXmlOpenTag		(::llc::achar & output, ::llc::vcs tagName) 							{ return llc::append_strings(output, '<', tagName); }
llc::err_t	llc::appendXmlTagClosing	(::llc::achar & output, ::llc::vcs tagName) 							{ return llc::append_strings(output, "</", tagName, '>'); }
llc::err_t	llc::appendXmlTagOpening	(::llc::achar & output, ::llc::vcs tagName, ::llc::vcs tagAttributes)	{
	return tagAttributes.size()
		? ::llc::append_strings(output, '<', tagName, ' ', tagAttributes, " >")
		: ::llc::append_strings(output, '<', tagName, '>')
		;
}
llc::err_t	llc::appendXmlTagVoid		(::llc::achar & output, ::llc::vcs tagName, ::llc::vcs tagAttributes) {
	return tagAttributes.size()
		? ::llc::append_strings(output, '<', tagName, ' ', tagAttributes, " >")
		: ::llc::append_strings(output, '<', tagName, " />")
		;
}
llc::err_t	llc::appendXmlTag			(::llc::achar & output, ::llc::vcs tagName, ::llc::vcs tagAttributes, ::llc::vcs innerHtml) {
	return tagAttributes.size()
		? ::llc::append_strings(output, '<', tagName, ' ', tagAttributes, " >", innerHtml, "</", tagName, '>')
		: ::llc::append_strings(output, '<', tagName, '>', innerHtml, "</", tagName, '>')
		;
}
llc::err_t	llc::appendXmlAttr			(::llc::achar & output, ::llc::vcs attrName, ::llc::vcs attrValue)	{
	return attrValue.size()
		? ::llc::append_strings(output, " ", attrName, "=\"", attrValue, '"')
		: ::llc::append_strings(output, " ", attrName)
		;
}
llc::err_t	llc::appendXmlTag			(::llc::achar & output, ::llc::vcs tagName, ::llc::vcs tagAttributes, const ::llc::FAppend & funcAppend) {
	int32_t			result						= 0;

					{ int32_t _result; llc_necs(_result = llc::appendXmlTagOpening(output, tagName, tagAttributes)); 	result += _result; }
	if(funcAppend)	{ int32_t _result; llc_necs(_result = funcAppend(output));											result += _result; }
					{ int32_t _result; llc_necs(_result = llc::appendXmlTagClosing(output, tagName)); 					result += _result; }
	return result;
}
llc::err_t	llc::appendXmlTag			(::llc::achar & output, ::llc::vcs tagName, ::llc::vcs tagAttributes, const ::llc::function<llc::err_t()> & funcAppend) {
	int32_t			result						= 0;

					{ int32_t _result; llc_necs(_result = llc::appendXmlTagOpening(output, tagName, tagAttributes)); 	result += _result; }
	if(funcAppend)	{ int32_t _result; llc_necs(_result = funcAppend());												result += _result; }
					{ int32_t _result; llc_necs(_result = llc::appendXmlTagClosing(output, tagName)); 					result += _result; }
	return result;
}
llc::err_t	llc::appendXmlTag			(::llc::achar & output, ::llc::vcs tagName, const ::llc::function<llc::err_t()> & funcAppendAttrs, const ::llc::function<llc::err_t()> & funcAppend) {
	int32_t			result						= 0;
	if(!funcAppendAttrs)
		return ::llc::appendXmlTag(output, tagName, ::llc::vcs{}, funcAppend);

					{ int32_t _result; llc_necs(_result = llc::append_strings(output, '<', tagName, ' '));	result += _result; }
					{ int32_t _result; llc_necs(_result = funcAppendAttrs());								result += _result; }
					{ int32_t _result; llc_necs(_result = output.append_string(" >"));						result += _result; }
	if(funcAppend)	{ int32_t _result; llc_necs(_result = funcAppend());									result += _result; }
					{ int32_t _result; llc_necs(_result = llc::appendXmlTagClosing(output, tagName));		result += _result; }
	return result;
}
