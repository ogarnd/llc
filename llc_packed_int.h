#include "llc_typeint.h"

#ifndef LLC_PACKED_INT_H
#define LLC_PACKED_INT_H

namespace llc 
{
	tplt<tpnm _tInt>	ndstcxp	u0_t		uint_width_field_size	()		{ 
		return 
			( (sizeof(_tInt) > 4) ? 3
			: (sizeof(_tInt) > 2) ? 2
			: (sizeof(_tInt) > 1) ? 1 
			: 1
			);
	}
	tplt<tpnm _tInt>	ndstcxp	u3_t	uint_tail_mask	()	{
		return
			( (1 == sizeof(_tInt)) ? 0x7FU
			: (2 == sizeof(_tInt)) ? 0x7FU
			: (4 == sizeof(_tInt)) ? 0x3FFFFFU
			: (8 == sizeof(_tInt)) ? 0x1FFFFFFFFFFFFFULL
			: 0xFFFFFFFFFFFFFFULL // 0xFFFFFFFFFFFFFFULL
			);
	}
	tplt<tpnm _tInt>	ndstinx	u3_t	uint_tail_mask	(_tInt)			{ return uint_tail_mask<_tInt>(); }
	tplt<tpnm _tInt>	ndstcxp	u0_t	uint_tail_width	(_tInt value)	{
		return u0_t
			( (1 == sizeof(_tInt)) ? ((u0_t(value) > uint_tail_mask<_tInt>()) ? 1 : 0)
			: (2 == sizeof(_tInt)) ? ((u1_t(value) > uint_tail_mask<_tInt>()) ? 1 : 0)
			: (4 == sizeof(_tInt)) ? 
				( (u2_t(value) > (uint_tail_mask<_tInt>() >> (8 * 0))) ? 3
				: (u2_t(value) > (uint_tail_mask<_tInt>() >> (8 * 1))) ? 2
				: (u2_t(value) > (uint_tail_mask<_tInt>() >> (8 * 2))) ? 1
				: 0
				)
			: (8 == sizeof(_tInt)) ? 
				( (u3_t(value) > (uint_tail_mask<_tInt>() >> (8 * 0))) ? 7
				: (u3_t(value) > (uint_tail_mask<_tInt>() >> (8 * 1))) ? 6
				: (u3_t(value) > (uint_tail_mask<_tInt>() >> (8 * 2))) ? 5
				: (u3_t(value) > (uint_tail_mask<_tInt>() >> (8 * 3))) ? 4
				: (u3_t(value) > (uint_tail_mask<_tInt>() >> (8 * 4))) ? 3
				: (u3_t(value) > (uint_tail_mask<_tInt>() >> (8 * 5))) ? 2
				: (u3_t(value) > (uint_tail_mask<_tInt>() >> (8 * 6))) ? 1
				: 0												  
				)
			: sizeof(_tInt)
			);
	}
	tplt<tpnm _tInt>	ndstinx	u0_t		uint_value_width		(_tInt count)	{ return uint_tail_width(count) + 1; }
	tplt<tpnm _tInt>	ndstcxp	u0_t		uint_tail_multiplier	(_tInt count)	{
		return u0_t
			( (1 == sizeof(_tInt)) ? ((u0_t(count) > uint_tail_mask<_tInt>()) ? byte_at(count, 0) : count)
			: (2 == sizeof(_tInt)) ? ((u1_t(count) > uint_tail_mask<_tInt>()) ? byte_at(count, 1) : count)
			: (4 == sizeof(_tInt)) ? 
				( (u2_t(count) > (uint_tail_mask<_tInt>() >> (0 * 8))) ? byte_at(count, 3)
				: (u2_t(count) > (uint_tail_mask<_tInt>() >> (1 * 8))) ? byte_at(count, 2)
				: (u2_t(count) > (uint_tail_mask<_tInt>() >> (2 * 8))) ? byte_at(count, 1)
				: count																				
				)
			: (8 == sizeof(_tInt)) ? 
				( (u3_t(count) > (uint_tail_mask<_tInt>() >> (0 * 8))) ? byte_at(count, 7)
				: (u3_t(count) > (uint_tail_mask<_tInt>() >> (1 * 8))) ? byte_at(count, 6)
				: (u3_t(count) > (uint_tail_mask<_tInt>() >> (2 * 8))) ? byte_at(count, 5)
				: (u3_t(count) > (uint_tail_mask<_tInt>() >> (3 * 8))) ? byte_at(count, 4)
				: (u3_t(count) > (uint_tail_mask<_tInt>() >> (4 * 8))) ? byte_at(count, 3)
				: (u3_t(count) > (uint_tail_mask<_tInt>() >> (5 * 8))) ? byte_at(count, 2)
				: (u3_t(count) > (uint_tail_mask<_tInt>() >> (6 * 8))) ? byte_at(count, 1)
				: count								
				)
			: count
			);
	}
	tplt<tpnm _tInt>	ndstcxp	_tInt		uint_tail_base			(_tInt count)	{
		return _tInt
			( (1 == sizeof(_tInt)) ? ((u0_t(count) > uint_tail_mask<_tInt>()) ? count & 0xFFU : count)
			: (2 == sizeof(_tInt)) ? ((u1_t(count) > uint_tail_mask<_tInt>()) ? count & 0xFFU : count)
			: (4 == sizeof(_tInt)) ? 
				( (u2_t(count) > (uint_tail_mask<_tInt>() >> (0 * 8))) ? count & (0xFFFFFFFFU >> (1 * 8))
				: (u2_t(count) > (uint_tail_mask<_tInt>() >> (1 * 8))) ? count & (0xFFFFFFFFU >> (2 * 8))
				: (u2_t(count) > (uint_tail_mask<_tInt>() >> (2 * 8))) ? count & (0xFFFFFFFFU >> (3 * 8))
				: count
				)
			: (8 == sizeof(_tInt)) ? 
				( (u3_t(count) > (uint_tail_mask<_tInt>() >> (1 * 8))) ? count & (0xFFFFFFFFFFFFFFFFULL >> (1 * 8))
				: (u3_t(count) > (uint_tail_mask<_tInt>() >> (2 * 8))) ? count & (0xFFFFFFFFFFFFFFFFULL >> (2 * 8))
				: (u3_t(count) > (uint_tail_mask<_tInt>() >> (3 * 8))) ? count & (0xFFFFFFFFFFFFFFFFULL >> (3 * 8))
				: (u3_t(count) > (uint_tail_mask<_tInt>() >> (4 * 8))) ? count & (0xFFFFFFFFFFFFFFFFULL >> (4 * 8))
				: (u3_t(count) > (uint_tail_mask<_tInt>() >> (5 * 8))) ? count & (0xFFFFFFFFFFFFFFFFULL >> (5 * 8))
				: (u3_t(count) > (uint_tail_mask<_tInt>() >> (6 * 8))) ? count & (0xFFFFFFFFFFFFFFFFULL >> (6 * 8))
				: (u3_t(count) > (uint_tail_mask<_tInt>() >> (7 * 8))) ? count & (0xFFFFFFFFFFFFFFFFULL >> (7 * 8))
				: count
				)
			: count
			);
	}

#pragma pack(push, 1)
	tplt<tpnm _tInt = u2_t, u0_t widthField = uint_width_field_size<_tInt>()>
	struct packed_uint { 
		typedef _tInt	T;
		typedef cnst T	TConst;

		TConst		TailWidth		: widthField;
		TConst		Multiplier		: 8 - widthField;
		TConst		Tail			: max((u0_t)1U, u0_t((sizeof(T) - 1) * 8));

		inlcxpr			packed_uint		()												: TailWidth{}, Multiplier{}, Tail{} {}
		inlcxpr			packed_uint		(TConst & value)								: TailWidth{(T)uint_tail_width(value)}, Multiplier{(T)uint_tail_multiplier(value)}, Tail{(T)uint_tail_base(value)} {}
		inlcxpr			packed_uint		(u0_t tailWidth, u0_t multiplier, T tail)	: TailWidth(tailWidth), Multiplier(multiplier), Tail(tail) {}

		tplt<tpnm TView>
		TView			cu8				()	const 				{ return {(u0_c*)(void*)this, ValueWidth()}; }

		ndincxp	u0_t	ValueWidth		()	const	noexcept	{ return u0_t(1 + TailWidth); }
		nodscrd	T		Value			()	const	noexcept	{
			if(0 == TailWidth)
				return Multiplier;

			u3_t			tail			= 0; 
			memcpy(&tail, ((u0_c*)this) + 1, TailWidth); 
			return T((u3_t(Multiplier) << (TailWidth * 8)) + tail); 
		}
	};
#pragma pack(pop)
	typedef packed_uint<u1_t>	pku1_t, packedu16;
	typedef packed_uint<u2_t>	pku2_t, packedu32;
	typedef packed_uint<u3_t>	pku3_t, packedu64;

	//ndstinx ::llc::packedu16	int_pack	(const u1_t value) { return {uint_tail_width(value), uint_tail_multiplier(value), uint_tail_base(value)}; } 
	//ndstinx ::llc::packedu32	int_pack	(const u2_t value) { return {uint_tail_width(value), uint_tail_multiplier(value), uint_tail_base(value)}; } 
	//ndstinx ::llc::packedu64	int_pack	(const u3_t value) { return {uint_tail_width(value), uint_tail_multiplier(value), uint_tail_base(value)}; } 
	//ndstinx ::llc::packedi16	int_pack	(const int16_t  value) { return {uint_tail_width(value), uint_tail_multiplier(value), uint_tail_base(value)}; } 
	//ndstinx ::llc::packedi32	int_pack	(const int32_t  value) { return {uint_tail_width(value), uint_tail_multiplier(value), uint_tail_base(value)}; } 
	//ndstinx ::llc::packedi64	int_pack	(const int64_t  value) { return {uint_tail_width(value), uint_tail_multiplier(value), uint_tail_base(value)}; } 
}

#endif // LLC_PACKED_INT_H
