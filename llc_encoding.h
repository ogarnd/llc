#include "llc_array.h"
#include "llc_stdstring.h"

#ifndef LLC_ENCODING_H_23627
#define LLC_ENCODING_H_23627

namespace llc
{
	::llc::error_t						hexEncode				(const ::llc::vcu0_t & inputBinary, ::llc::asc_t  & out_hexed	);
	::llc::error_t						hexDecode				(const ::llc::vcc  & in_hexed   , ::llc::au0_t & outputBinary	);
	::llc::error_t						hexDecode				(const ::llc::vcc  & in_hexed   , ::llc::as0_t & outputBinary	);
	stainli	::llc::error_t				hexEncode				(const ::llc::vcs0_t & inputBinary, ::llc::asc_t  & out_hexed	)			{ return hexEncode(::llc::vcu0_t{(const uint8_t*)inputBinary.begin(), inputBinary.size()}, out_hexed); }

	// Based on Gary Ardell's code for VB.
	::llc::error_t						ardellEncode			(::llc::as2_t & cache, const ::llc::vcu0_t & input, uint64_t key, bool salt, ::llc::au0_t & output);
	::llc::error_t						ardellDecode			(::llc::as2_t & cache, const ::llc::vcu0_t & input, uint64_t key, bool salt, ::llc::au0_t & output);

	stainli	::llc::error_t				ardellEncode			(const ::llc::vcu0_t & input, uint64_t key, bool salt, ::llc::au0_t & output)	{ ::llc::as2_t tempCache; return ::llc::ardellEncode(tempCache, input, key, salt, output); }
	stainli	::llc::error_t				ardellDecode			(const ::llc::vcu0_t & input, uint64_t key, bool salt, ::llc::au0_t & output)	{ ::llc::as2_t tempCache; return ::llc::ardellDecode(tempCache, input, key, salt, output); }
	stainli	::llc::error_t				ardellEncode			(const ::llc::vcs0_t & input, uint64_t key, bool salt, ::llc::au0_t & output)	{ ::llc::as2_t tempCache; return ::llc::ardellEncode(tempCache, *(const ::llc::vcu0_t*)&input, key, salt, output); }
	stainli	::llc::error_t				ardellDecode			(const ::llc::vcu0_t & input, uint64_t key, bool salt, ::llc::as0_t & output)	{ ::llc::as2_t tempCache; return ::llc::ardellDecode(tempCache, input, key, salt, *(::llc::au0_t*)&output); }
	stainli	::llc::error_t				ardellEncode			(const ::llc::vcc  & input, uint64_t key, bool salt, ::llc::au0_t & output)	{ ::llc::as2_t tempCache; return ::llc::ardellEncode(tempCache, *(const ::llc::vcu0_t*)&input, key, salt, output); }
	stainli	::llc::error_t				ardellDecode			(const ::llc::vcu0_t & input, uint64_t key, bool salt, ::llc::asc_t  & output)	{ ::llc::as2_t tempCache; return ::llc::ardellDecode(tempCache, input, key, salt, *(::llc::au0_t*)&output); }

	stainli	::llc::error_t				ardellEncode			(::llc::as2_t & cache, const ::llc::vcs0_t & input, uint64_t key, bool salt, ::llc::au0_t & output)	{ return ::llc::ardellEncode(cache, *(const ::llc::vcu0_t*)&input, key, salt, output); }
	stainli	::llc::error_t				ardellDecode			(::llc::as2_t & cache, const ::llc::vcu0_t & input, uint64_t key, bool salt, ::llc::as0_t & output)	{ return ::llc::ardellDecode(cache, input, key, salt, *(::llc::au0_t*)&output); }
	stainli	::llc::error_t				ardellEncode			(::llc::as2_t & cache, const ::llc::vcc  & input, uint64_t key, bool salt, ::llc::au0_t & output)	{ return ::llc::ardellEncode(cache, *(const ::llc::vcu0_t*)&input, key, salt, output); }
	stainli	::llc::error_t				ardellDecode			(::llc::as2_t & cache, const ::llc::vcu0_t & input, uint64_t key, bool salt, ::llc::asc_t  & output)	{ return ::llc::ardellDecode(cache, input, key, salt, *(::llc::au0_t*)&output); }

	::llc::error_t						saltDataSalt			(const ::llc::vcu0_t & binary, ::llc::au0_t & salted);
	::llc::error_t						saltDataUnsalt			(const ::llc::vcu0_t & salted, ::llc::au0_t & binary);

	tplt<tpnm _tBase>
	::llc::error_t						rleEncode				(const ::llc::view<_tBase> & decoded, ::llc::au0_t & encoded) {
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
	::llc::error_t						rleDecode			(const ::llc::vcu0_t & encoded, ::llc::apod<_tBase> & decoded) {
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
	::llc::error_t			utf8FromCodePoint	(uint32_t codePoint, ::llc::asc_t & hexDigits);
	::llc::error_t			digest				(const ::llc::vcu0_t & input, ::llc::au2_t & digest);
	::llc::error_t			digest				(const ::llc::vcu0_t & input, ::llc::asc_t & digest);
	stainli	::llc::error_t	digest				(const ::llc::vcc & input, ::llc::asc_t & digest) { return ::llc::digest(*(const ::llc::vcu0_t*)&input, digest); }
}

#endif // LLC_ENCODING_H_23627
