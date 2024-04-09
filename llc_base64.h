#include "llc_array_pod.h"

#ifndef LLC_BASE64_H_23627
#define LLC_BASE64_H_23627

namespace llc
{
	stacxpr	::llc::vcc		b64Symbols		= {64, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};
	stacxpr	::llc::vcc		b64SymbolsFS	= {64, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"};

	::llc::error_t			base64Encode	(const ::llc::vcc & base64Symbols, char base64PadSymbol, const ::llc::vcu8 & inputBinary	, ::llc::au8 & out_base64	);
	::llc::error_t			base64Decode	(const ::llc::vcc & base64Symbols, char base64PadSymbol, const ::llc::vcu8 & in_base64	, ::llc::au8 & outputBinary	);

	stainli	::llc::error_t	base64Encode	(const ::llc::vcu8 & inputBinary, ::llc::au8 & out_base64	) { return ::llc::base64Encode(b64Symbols	, '=', inputBinary	, out_base64	); }
	stainli	::llc::error_t	base64Decode	(const ::llc::vcu8 & in_base64  , ::llc::au8 & outputBinary	) { return ::llc::base64Decode(b64Symbols	, '=', in_base64	, outputBinary	); }
	stainli	::llc::error_t	base64EncodeFS	(const ::llc::vcu8 & inputBinary, ::llc::au8 & out_base64	) { return ::llc::base64Encode(b64SymbolsFS	, '=', inputBinary	, out_base64	); }
	stainli	::llc::error_t	base64DecodeFS	(const ::llc::vcu8 & in_base64  , ::llc::au8 & outputBinary	) { return ::llc::base64Decode(b64SymbolsFS	, '=',  in_base64, outputBinary	); }
																						   
	stainli	::llc::error_t	base64Encode	(const ::llc::vci8 & inputBinary, ::llc::au8 & out_base64	) { return ::llc::base64Encode(b64Symbols	, '=', *(::llc::vcu8*)&inputBinary	, out_base64	); }
	stainli	::llc::error_t	base64Decode	(const ::llc::vci8 & in_base64  , ::llc::au8 & outputBinary	) { return ::llc::base64Decode(b64Symbols	, '=', *(::llc::vcu8*)&in_base64	, outputBinary	); }
	stainli	::llc::error_t	base64EncodeFS	(const ::llc::vci8 & inputBinary, ::llc::au8 & out_base64	) { return ::llc::base64Encode(b64SymbolsFS	, '=', *(::llc::vcu8*)&inputBinary	, out_base64	); }
	stainli	::llc::error_t	base64DecodeFS	(const ::llc::vci8 & in_base64  , ::llc::au8 & outputBinary	) { return ::llc::base64Decode(b64SymbolsFS	, '=', *(::llc::vcu8*)& in_base64, outputBinary	); }
																						   
	stainli	::llc::error_t	base64Encode	(const ::llc::vcu8 & inputBinary, ::llc::ai8 & out_base64	) { return ::llc::base64Encode(b64Symbols	, '=', inputBinary	, *(::llc::au8*)&out_base64		); }
	stainli	::llc::error_t	base64Decode	(const ::llc::vcu8 & in_base64  , ::llc::ai8 & outputBinary	) { return ::llc::base64Decode(b64Symbols	, '=', in_base64	, *(::llc::au8*)&outputBinary	); }
	stainli	::llc::error_t	base64EncodeFS	(const ::llc::vcu8 & inputBinary, ::llc::ai8 & out_base64	) { return ::llc::base64Encode(b64SymbolsFS	, '=', inputBinary	, *(::llc::au8*)&out_base64		); }
	stainli	::llc::error_t	base64DecodeFS	(const ::llc::vcu8 & in_base64  , ::llc::ai8 & outputBinary	) { return ::llc::base64Decode(b64SymbolsFS	, '=', in_base64	, *(::llc::au8*)&outputBinary	); }
																						   
	stainli	::llc::error_t	base64Encode	(const ::llc::vci8 & inputBinary, ::llc::ai8 & out_base64	) { return ::llc::base64Encode(b64Symbols	, '=', *(::llc::vcu8*)&inputBinary	, *(::llc::au8*)&out_base64 	); }
	stainli	::llc::error_t	base64Decode	(const ::llc::vci8 & in_base64  , ::llc::ai8 & outputBinary	) { return ::llc::base64Decode(b64Symbols	, '=', *(::llc::vcu8*)&in_base64	, *(::llc::au8*)&outputBinary	); }
	stainli	::llc::error_t	base64EncodeFS	(const ::llc::vci8 & inputBinary, ::llc::ai8 & out_base64	) { return ::llc::base64Encode(b64SymbolsFS	, '=', *(::llc::vcu8*)&inputBinary	, *(::llc::au8*)&out_base64 	); }
	stainli	::llc::error_t	base64DecodeFS	(const ::llc::vci8 & in_base64  , ::llc::ai8 & outputBinary	) { return ::llc::base64Decode(b64SymbolsFS	, '=', *(::llc::vcu8*)&in_base64	, *(::llc::au8*)&outputBinary	); }

	stainli	::llc::error_t	base64Encode	(const ::llc::vcc  & inputBinary, ::llc::au8 & out_base64	) { return ::llc::base64Encode(b64Symbols	, '=', *(::llc::vcu8*)&inputBinary, out_base64	); }
	stainli	::llc::error_t	base64Decode	(const ::llc::vcu8 & in_base64  , ::llc::ac  & outputBinary	) { return ::llc::base64Decode(b64Symbols	, '=', in_base64, *(::llc::au8*)&outputBinary	); }
	stainli	::llc::error_t	base64EncodeFS	(const ::llc::vcc  & inputBinary, ::llc::au8 & out_base64	) { return ::llc::base64Encode(b64SymbolsFS	, '=', *(::llc::vcu8*)&inputBinary, out_base64	); }
	stainli	::llc::error_t	base64DecodeFS	(const ::llc::vcu8 & in_base64  , ::llc::ac  & outputBinary	) { return ::llc::base64Decode(b64SymbolsFS	, '=', in_base64, *(::llc::au8*)&outputBinary	); }

	stainli	::llc::error_t	base64Encode	(const ::llc::vcu8 & inputBinary, ::llc::ac  & out_base64  ) { return ::llc::base64Encode(b64Symbols  , '=', inputBinary	, *(::llc::au8*)&out_base64 	); }
	stainli	::llc::error_t	base64Decode	(const ::llc::vcc  & in_base64  , ::llc::au8 & outputBinary) { return ::llc::base64Decode(b64Symbols  , '=', *(::llc::vcu8*)&in_base64	, outputBinary	); }
	stainli	::llc::error_t	base64EncodeFS	(const ::llc::vcu8 & inputBinary, ::llc::ac  & out_base64  ) { return ::llc::base64Encode(b64SymbolsFS, '=', inputBinary	, *(::llc::au8*)&out_base64 	); }
	stainli	::llc::error_t	base64DecodeFS	(const ::llc::vcc  & in_base64  , ::llc::au8 & outputBinary) { return ::llc::base64Decode(b64SymbolsFS, '=', *(::llc::vcu8*)&in_base64	, outputBinary	); }

	stainli	::llc::error_t	base64Encode	(const ::llc::vcc &  inputBinary, ::llc::ac & out_base64  ) { return ::llc::base64Encode(b64Symbols  , '=', *(::llc::vcu8*)&inputBinary	, *(::llc::au8*)&out_base64 	); }
	stainli	::llc::error_t	base64Decode	(const ::llc::vcc &  in_base64  , ::llc::ac & outputBinary) { return ::llc::base64Decode(b64Symbols  , '=', *(::llc::vcu8*)&in_base64	, *(::llc::au8*)&outputBinary	); }
	stainli	::llc::error_t	base64EncodeFS	(const ::llc::vcc &  inputBinary, ::llc::ac & out_base64  ) { return ::llc::base64Encode(b64SymbolsFS, '=', *(::llc::vcu8*)&inputBinary	, *(::llc::au8*)&out_base64 	); }
	stainli	::llc::error_t	base64DecodeFS	(const ::llc::vcc &  in_base64  , ::llc::ac & outputBinary) { return ::llc::base64Decode(b64SymbolsFS, '=', *(::llc::vcu8*)&in_base64	, *(::llc::au8*)&outputBinary	); }
} // namespace

#endif // LLC_BASE64_H_23627
