#include "llc_array_static.h"
#include "llc_array_pod.h"

#ifndef LLC_STRING_COMPOSE
#define LLC_STRING_COMPOSE

namespace llc
{
	tplt<tpnm TArg>	
	llc::err_t			append_string			(::llc::achar & output, const TArg & arg)					{ return output.append_string(arg); }
	tplt<size_t NLen>	
	llc::err_t			append_string			(::llc::achar & output, const char (&arg)[NLen])			{ return output.append_string(arg); }
	tplt<size_t NLen>	
	llc::err_t			append_string			(::llc::achar & output, const ::llc::astchar<NLen> & arg)	{ return output.append_string(arg.Storage); }
	stainli	llc::err_t	append_string			(::llc::achar & output, const ::llc::achar & arg)			{ return output.append_string(arg.cc()); }

	tplt<tpnm... _tArgs>	
	llc::err_t			append_strings			(::llc::achar & output, _tArgs&&... args)	{ 
		err_t				err			= 0;
		const int32_t		results[]	= {err = (failed(err) ? -1 : append_string(output, args))..., 0}; 
		return failed(err) ? err : ::llc::sum(::llc::vci32{results}); 
	}

	tplt<tpnm TSeparator, tpnm... _tArgs>	
	llc::err_t			append_strings_separated(::llc::achar & output, TSeparator separator, _tArgs&&... args)	{
		err_t				err			= 0;
		uint32_t			len			= 0;
		const int32_t		results[]	= {len = err = ((0 == len) ? append_string(output, args) : failed(err) ? -1 : append_string(output, separator) + append_string(output, args))..., 0}; 
		return failed(err) ? err : ::llc::sum(::llc::vci32{results}); 
	}

	typedef ::llc::function<llc::err_t(::llc::achar & )> FAppend;

	llc::err_t			appendNclosd			(::llc::achar & output, ::llc::vcs textToEnclose);
	llc::err_t			appendBraced			(::llc::achar & output, ::llc::vcs textToEnclose);
	llc::err_t			appendQuoted			(::llc::achar & output, ::llc::vcs textToEnclose);
	llc::err_t			appendGtlted			(::llc::achar & output, ::llc::vcs textToEnclose);

	llc::err_t			appendNclosd			(::llc::achar & output, ::llc::vcs textToEnclose, char encloserChar);
	llc::err_t			appendNclosd			(::llc::achar & output, ::llc::vcs textToEnclose, char openChar, char closeChar);
	llc::err_t			appendNclosd			(::llc::achar & output, ::llc::vcs textToEnclose, ::llc::vcs openChars, ::llc::vcs closeChars);
	llc::err_t			appendNclosdPrefixed	(::llc::achar & output, ::llc::vcs textToEnclose, char prefix, char encloserChar);
	llc::err_t			appendNclosdPrefixed	(::llc::achar & output, ::llc::vcs textToEnclose, char prefix, char openChar, char closeChar);

	llc::err_t			appendBracedPrefixed	(::llc::achar & output, ::llc::vcs textToEnclose, bool prependSeparator = false, char separator = ',');
	llc::err_t			appendNclosdPrefixed	(::llc::achar & output, ::llc::vcs textToEnclose, bool prependSeparator = false, char separator = ',');
	llc::err_t			appendQuotedPrefixed	(::llc::achar & output, ::llc::vcs textToEnclose, bool prependSeparator = false, char separator = ',');
	llc::err_t			appendGtltedPrefixed	(::llc::achar & output, ::llc::vcs textToEnclose, bool prependSeparator = false, char separator = ',');
} // namespace

#endif // LLC_STRING_COMPOSE
