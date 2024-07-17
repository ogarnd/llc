#include "llc_typeint.h"

#ifndef LLC_SIZE_H_23627
#define LLC_SIZE_H_23627

namespace llc
{
	tplt<tpnm T>										stincxp	uint32_t	size		(const T & sized)										noexcept	{ return sized.size();							}
	tplt<tpnm _t, size_t _arraySize>					stincxp	uint32_t	size		(const _t (&/*staticArray*/)[_arraySize])				noexcept	{ return _arraySize;							}
	tplt<tpnm _t, size_t _sizeDepth, size_t _sizeWidth>	stincxp	uint32_t	size		(const _t (&/*staticArray*/)[_sizeWidth][_sizeDepth])	noexcept	{ return _sizeDepth * _sizeWidth;				}
	tplt<tpnm _t, size_t _arraySize>					stincxp	uint32_t	byte_count	(const _t (&/*staticArray*/)[_arraySize])				noexcept	{ return sizeof(_t) * (_arraySize);				}
	tplt<tpnm _t, size_t _sizeDepth, size_t _sizeWidth>	stincxp	uint32_t	byte_count	(const _t (&/*staticArray*/)[_sizeWidth][_sizeDepth])	noexcept	{ return sizeof(_t) * (_sizeDepth*_sizeWidth);	}
}

#endif // LLC_SIZE_H_23627
