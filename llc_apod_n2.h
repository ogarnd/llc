/// Copyright 2009-2023 - ogarnd
#include "llc_n2.h"
#include "llc_array_pod.h"

#ifndef LLC_APOD_N2_3973498373423617
#define LLC_APOD_N2_3973498373423617

namespace llc
{
#pragma pack(push, 1)
	tplt<tpnm _tDimension>	
	using		an2		= ::llc::apod<::llc::n2<_tDimension>>;

	typedef	::llc::an2<char	>	an2c	, an2char		;
	typedef	::llc::an2<uchar>	an2uc	, an2uchar		;
	typedef	::llc::an2<f32	>	an2f32	;
	typedef	::llc::an2<f64	>	an2f64	;
	typedef	::llc::an2<u8	>	an2u8	;
	typedef	::llc::an2<u16	>	an2u16	;
	typedef	::llc::an2<u32	>	an2u32	;
	typedef	::llc::an2<u64	>	an2u64	;
	typedef	::llc::an2<i8	>	an2i8	;
	typedef	::llc::an2<i16	>	an2i16	;
	typedef	::llc::an2<i32	>	an2i32	;
	typedef	::llc::an2<i64	>	an2i64	;
#pragma pack(pop)
} // namespace

#endif // LLC_APOD_N2_3973498373423617
