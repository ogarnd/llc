#include "llc_aobj_pobj.h"
#include "llc_aobj_ppod.h"
#include "llc_array_pod.h"

#ifndef LLC_ARRAY_PTR_H_23627
#define LLC_ARRAY_PTR_H_23627

namespace llc
{
	tplt<tpnm T> using papod	= ::llc::pobj<::llc::apod<T>>;
	tplt<tpnm T> using apapod	= ::llc::aobj<::llc::papod<T>>;

	typedef	::llc::papod<uc_t	>	pauchar;
	typedef	::llc::papod<char		>	pachar;
	typedef	::llc::papod<float		>	paf32;
	typedef	::llc::papod<double		>	paf64;
	typedef	::llc::papod<uint8_t	>	pau8;
	typedef	::llc::papod<uint16_t	>	pau16;
	typedef	::llc::papod<uint32_t	>	pau32;
	typedef	::llc::papod<uint64_t	>	pau64;
	typedef	::llc::papod<int8_t		>	pai8;
	typedef	::llc::papod<int16_t	>	pai16;
	typedef	::llc::papod<int32_t	>	pai32;
	typedef	::llc::papod<int64_t	>	pai64;

	typedef	::llc::aobj<::llc::pauchar	>	apauchar;
	typedef	::llc::aobj<::llc::pachar	>	apachar;
	typedef	::llc::aobj<::llc::paf32	>	apaf32;
	typedef	::llc::aobj<::llc::paf64	>	apaf64;
	typedef	::llc::aobj<::llc::pau8		>	apau8;
	typedef	::llc::aobj<::llc::pau16	>	apau16;
	typedef	::llc::aobj<::llc::pau32	>	apau32;
	typedef	::llc::aobj<::llc::pau64	>	apau64;
	typedef	::llc::aobj<::llc::pai8		>	apai8;
	typedef	::llc::aobj<::llc::pai16	>	apai16;
	typedef	::llc::aobj<::llc::pai32	>	apai32;
	typedef	::llc::aobj<::llc::pai64	>	apai64;
} // namespace

#endif // LLC_ARRAY_PTR_H_23627
