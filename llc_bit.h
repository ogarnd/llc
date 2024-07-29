/// Copyright 2010-2024 - asm128
#include "llc_typeint.h"

#ifndef LLC_BIT_H
#define LLC_BIT_H

namespace llc
{
	tplT ndstcxp	T		bit_clear		(cnst T state, cnst T bitsToClear)					nxpt	{ return (state & bitsToClear)				? state & ~bitsToClear	: state; }
	tplT ndstcxp	T		bit_set			(cnst T state, cnst T bitsToSet  )					nxpt	{ return ((state & bitsToSet) != bitsToSet)	? state | bitsToSet	: state; }
	tplT ndstcxp	T		bit_set			(cnst T state, cnst T bitsToSet, cnst bool value)	nxpt	{ return value ? bit_set(state, bitsToSet) : bit_clear(state, bitsToSet); }
	tplT stacxpr	T		bit_test		(cnst T state, cnst T bitsToTest)						nxpt	{ return ((state & bitsToTest) == bitsToTest) ? state : (T)0; }

	tplT ndstcxp	T		bit_set_masked	(cnst T state, cnst T mask, cnst T bitsToSet, cnst bool value)	nxpt	{ return (mask & bitsToSet) ? bit_set(state, mask & bitsToSet, value) : state; }
	tplT stincxp	T		bit_test_masked	(cnst T state, cnst T mask, cnst T value)						nxpt	{ return (mask & value) ? bit_test(state, mask & value) : (T)0; }
	tplT stincxp	T		bit_true		(cnst T state, cnst T bitsToTest)									nxpt	{ return bit_test(state, bitsToTest); }
	tplT stacxpr	T		bit_false		(cnst T state, cnst T bitsToTest)									nxpt	{
		cnst T		bitsThatMatch		= (state & bitsToTest);
		return T((bitsThatMatch == bitsToTest) ? 0 : (state | bitsToTest) ? state | bitsToTest : -1);
	}
	tplT ndstinx	u2_t	bitsof			(cnst T&)	nxpt	{ return sizeof(T); }
	tplT ndstinx	u2_t	bitsof			()			nxpt	{ return sizeof(T); }
#ifdef LLC_DEBUG_ENABLED
	tplT 			T		bit_make		(u0_t bitIndex)	nxpt	{
		rve_if((T)-1LL, bitIndex >= (sizeof(T) * PLATFORM_BYTE_BIT_COUNT), "Invalid bit index: %i", bitIndex);
#else
	tplT ndcnxpr	T		bit_make		(u0_t bitIndex)	nxpt	{
#endif
		return (T)(((T)1) << bitIndex);
	}

//#ifdef LLC_BIGENDIAN
//	stincxp	u0_t		le_byte_at		(uint32_t bytes, u0_t byteIndex)	nxpt	{ return ((0xFF000000 >> (byteIndex * 8)) & bytes) >> ((sizeof(bytes) - byteIndex) * 8); }
//#else
//	stincxp	u0_t		le_byte_at		(uint32_t bytes, u0_t byteIndex)	nxpt	{ return ((0xFF << (byteIndex * 8)) & bytes) >> (byteIndex * 8); }
//#endif

	tplT	static	T	reverse_bitfield	(T input, s2_c bitDepth)	{
		u2_c					sizeType			= u2_t(sizeof(T) * 8);
		cnst T					mask				= ((T)(-1)) >> (sizeType - bitDepth);
		T						result				= 0;
		for(uint32_t iBit = 0; iBit < sizeType; iBit += bitDepth) {
			result				|= (input & mask) << (sizeType - bitDepth - iBit);
			input				>>= bitDepth;
		}
		return result;
	}
}

#endif // LLC_BIT_H
