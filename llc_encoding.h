#include "llc_array.h"
#include "llc_stdstring.h"

#ifndef LLC_ENCODING_H_23627
#define LLC_ENCODING_H_23627

namespace llc
{
	::llc::error_t						hexEncode				(const ::llc::vcu8 & inputBinary, ::llc::ac  & out_hexed	);
	::llc::error_t						hexDecode				(const ::llc::vcc  & in_hexed   , ::llc::au8 & outputBinary	);
	::llc::error_t						hexDecode				(const ::llc::vcc  & in_hexed   , ::llc::ai8 & outputBinary	);
	stainli	::llc::error_t				hexEncode				(const ::llc::vci8 & inputBinary, ::llc::ac  & out_hexed	)			{ return hexEncode(::llc::vcu8{(const uint8_t*)inputBinary.begin(), inputBinary.size()}, out_hexed); }

	// Based on Gary Ardell's code for VB.
	::llc::error_t						ardellEncode			(::llc::ai32 & cache, const ::llc::vcu8 & input, uint64_t key, bool salt, ::llc::au8 & output);
	::llc::error_t						ardellDecode			(::llc::ai32 & cache, const ::llc::vcu8 & input, uint64_t key, bool salt, ::llc::au8 & output);

	stainli	::llc::error_t				ardellEncode			(const ::llc::vcu8 & input, uint64_t key, bool salt, ::llc::au8 & output)	{ ::llc::ai32 tempCache; return ::llc::ardellEncode(tempCache, input, key, salt, output); }
	stainli	::llc::error_t				ardellDecode			(const ::llc::vcu8 & input, uint64_t key, bool salt, ::llc::au8 & output)	{ ::llc::ai32 tempCache; return ::llc::ardellDecode(tempCache, input, key, salt, output); }
	stainli	::llc::error_t				ardellEncode			(const ::llc::vci8 & input, uint64_t key, bool salt, ::llc::au8 & output)	{ ::llc::ai32 tempCache; return ::llc::ardellEncode(tempCache, *(const ::llc::vcu8*)&input, key, salt, output); }
	stainli	::llc::error_t				ardellDecode			(const ::llc::vcu8 & input, uint64_t key, bool salt, ::llc::ai8 & output)	{ ::llc::ai32 tempCache; return ::llc::ardellDecode(tempCache, input, key, salt, *(::llc::au8*)&output); }
	stainli	::llc::error_t				ardellEncode			(const ::llc::vcc  & input, uint64_t key, bool salt, ::llc::au8 & output)	{ ::llc::ai32 tempCache; return ::llc::ardellEncode(tempCache, *(const ::llc::vcu8*)&input, key, salt, output); }
	stainli	::llc::error_t				ardellDecode			(const ::llc::vcu8 & input, uint64_t key, bool salt, ::llc::ac  & output)	{ ::llc::ai32 tempCache; return ::llc::ardellDecode(tempCache, input, key, salt, *(::llc::au8*)&output); }

	stainli	::llc::error_t				ardellEncode			(::llc::ai32 & cache, const ::llc::vci8 & input, uint64_t key, bool salt, ::llc::au8 & output)	{ return ::llc::ardellEncode(cache, *(const ::llc::vcu8*)&input, key, salt, output); }
	stainli	::llc::error_t				ardellDecode			(::llc::ai32 & cache, const ::llc::vcu8 & input, uint64_t key, bool salt, ::llc::ai8 & output)	{ return ::llc::ardellDecode(cache, input, key, salt, *(::llc::au8*)&output); }
	stainli	::llc::error_t				ardellEncode			(::llc::ai32 & cache, const ::llc::vcc  & input, uint64_t key, bool salt, ::llc::au8 & output)	{ return ::llc::ardellEncode(cache, *(const ::llc::vcu8*)&input, key, salt, output); }
	stainli	::llc::error_t				ardellDecode			(::llc::ai32 & cache, const ::llc::vcu8 & input, uint64_t key, bool salt, ::llc::ac  & output)	{ return ::llc::ardellDecode(cache, input, key, salt, *(::llc::au8*)&output); }

	::llc::error_t						saltDataSalt			(const ::llc::vcu8 & binary, ::llc::au8 & salted);
	::llc::error_t						saltDataUnsalt			(const ::llc::vcu8 & salted, ::llc::au8 & binary);

	tplt<tpnm _tBase>
	::llc::error_t						rleEncode				(const ::llc::view<_tBase> & decoded, ::llc::au8 & encoded) {
		uint32_t								idxLatest				= 0;
		stacxpr	const uint32_t					sizeBlock				= sizeof(_tBase) + 1;
		for(uint32_t iIn = 0; iIn < decoded.size(); ++iIn) {
			const _tBase 							& current				= decoded[iIn];
			const _tBase							& latest				= decoded[idxLatest];
			if(0 == iIn || 0 != memcmp(&current, &latest, sizeof(_tBase)) || 255 == (uint8_t)encoded[encoded.size() - 1]) {
				const uint32_t							newSize					= encoded.size() + sizeBlock;
				llc_necs(encoded.resize(newSize));
				memcpy(&encoded[encoded.size() - sizeBlock], &current, sizeof(_tBase));
				encoded[encoded.size() - 1]			= 0;
				idxLatest							= iIn;
			}
			else
				++encoded[encoded.size() - 1];
		}
		return 0;
	}

	tplt<tpnm _tBase>
	::llc::error_t						rleDecode			(const ::llc::vcu8 & encoded, ::llc::apod<_tBase> & decoded) {
		stacxpr	const uint32_t					sizeBlock			= sizeof(_tBase) + 1;
  		for(uint32_t iIn = 0; iIn < encoded.size(); iIn += sizeBlock) {
			const _tBase 							& current			= *(_tBase*)&encoded[iIn];
			const uint8_t							count				= encoded[iIn + sizeof(_tBase)];
			llc_necs(decoded.push_back(current));
			for(uint32_t iOut = 0; iOut < count; ++iOut)
				llc_necs(decoded.push_back(current));
		}
		return 0;
	}

	// Description at http://en.wikipedia.org/wiki/UTF-8
	::llc::error_t			utf8FromCodePoint	(uint32_t codePoint, ::llc::ac & hexDigits);
	::llc::error_t			digest				(const ::llc::vcu8 & input, ::llc::au32 & digest);
	::llc::error_t			digest				(const ::llc::vcu8 & input, ::llc::ac & digest);
	stainli	::llc::error_t	digest				(const ::llc::vcc & input, ::llc::ac & digest) { return ::llc::digest(*(const ::llc::vcu8*)&input, digest); }
}

#endif // LLC_ENCODING_H_23627
