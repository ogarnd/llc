#include "llc_typeint.h"

#ifndef LLC_CPOW_H
#define LLC_CPOW_H

namespace llc
{
	tplt<size_t exp>	ndstinx	i0u_t			cpow	(i0u_t base)	{ return base * cpow<exp - 1>(base); }
	tplt<size_t exp>	ndstinx	i1u_t			cpow	(i1u_t base)	{ return base * cpow<exp - 1>(base); }
	tplt<size_t exp>	ndstinx	i2u_t			cpow	(i2u_t base)	{ return base * cpow<exp - 1>(base); }
	tplt<size_t exp>	ndstinx	i3u_t			cpow	(i3u_t base)	{ return base * cpow<exp - 1>(base); }
	tplt<size_t exp>	ndstinx	i0s_t			cpow	(i0s_t base)	{ return base * cpow<exp - 1>(base); }
	tplt<size_t exp>	ndstinx	i1s_t			cpow	(i1s_t base)	{ return base * cpow<exp - 1>(base); }
	tplt<size_t exp>	ndstinx	i2s_t			cpow	(i2s_t base)	{ return base * cpow<exp - 1>(base); }
	tplt<size_t exp>	ndstinx	i3s_t			cpow	(i3s_t base)	{ return base * cpow<exp - 1>(base); }
	tplt<size_t exp>	ndstinx	f2s_t			cpow	(f2s_t base)	{ return base * cpow<exp - 1>(base); }
	tplt<size_t exp>	ndstinx	f3s_t			cpow	(f3s_t base)	{ return base * cpow<exp - 1>(base); }
	tplt<>				ndincxp	i0u_t			cpow<0>	(i0u_t/*base*/)	{ return 1; }
	tplt<>				ndincxp	i1u_t			cpow<0>	(i1u_t/*base*/)	{ return 1; }
	tplt<>				ndincxp	i2u_t			cpow<0>	(i2u_t/*base*/)	{ return 1; }
	tplt<>				ndincxp	i3u_t			cpow<0>	(i3u_t/*base*/)	{ return 1; }
	tplt<>				ndincxp	i0s_t			cpow<0>	(i0s_t/*base*/)	{ return 1; }
	tplt<>				ndincxp	i1s_t			cpow<0>	(i1s_t/*base*/)	{ return 1; }
	tplt<>				ndincxp	i2s_t			cpow<0>	(i2s_t/*base*/)	{ return 1; }
	tplt<>				ndincxp	i3s_t			cpow<0>	(i3s_t/*base*/)	{ return 1; }
	tplt<>				ndincxp	f2s_t			cpow<0>	(f2s_t/*base*/)	{ return 1; }
	tplt<>				ndincxp	f3s_t			cpow<0>	(f3s_t/*base*/)	{ return 1; }

	stacxpr	uint8_t		ASCII_ALPHABET_LENGTH	= 'Z' - 'A';
	stacxpr	uint8_t		ASCII_LETTER_COUNT		= ASCII_ALPHABET_LENGTH * 2;
	stacxpr	uint8_t		ASCII_DIGIT_COUNT		= ASCII_LETTER_COUNT + 10;

	ndstinx char		digit_ascii				(char remainder)								noxcpt	{ return remainder + ((remainder < 10) ? '0' : '7'); }
	ndstinx char		digit_ascii				(uint64_t value, uint8_t base)					noxcpt	{ return digit_ascii(char(value % base)); }
	tplt<uint8_t exp, tpnm TValue>
	ndstinx	char		digit					(const TValue value, const TValue base = 10)	noxcpt	{ return ::llc::digit_ascii(value / ::llc::cpow<exp>(base), (uint8_t)base); }
} // namespace

#endif // LLC_CPOW_H
