#include "llc_array_pod.h"
#include "llc_array_obj.h"

#ifndef LLC_ARRAY_H_23627
#define LLC_ARRAY_H_23627

namespace llc
{
	tplt <tpnm T>	using aaobj		= ::llc::aobj<::llc::aobj<T>>; 
	tplt <tpnm T>	using aapod		= ::llc::aobj<::llc::apod<T>>; 

	typedef	::llc::aapod<uchar_t	>	aauchar		;
	typedef	::llc::aapod<char		>	aachar		;
	typedef	::llc::aapod<float		>	aafloat		, aaf32;
	typedef	::llc::aapod<double		>	aadouble	, aaf64;
	typedef	::llc::aapod<uint8_t	>	aauint8		, aau8;
	typedef	::llc::aapod<uint16_t	>	aauint16	, aau16;
	typedef	::llc::aapod<uint32_t	>	aauint32	, aau32;
	typedef	::llc::aapod<uint64_t	>	aauint64	, aau64;
	typedef	::llc::aapod<int8_t		>	aaint8		, aai8;
	typedef	::llc::aapod<int16_t	>	aaint16		, aai16;
	typedef	::llc::aapod<int32_t	>	aaint32		, aai32;
	typedef	::llc::aapod<int64_t	>	aaint64		, aai64;
} // namespace 

#endif // LLC_ARRAY_H_23627
