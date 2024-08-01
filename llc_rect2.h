#include "llc_n2.h"

#ifndef LLC_RECT2_H
#define LLC_RECT2_H

namespace llc
{
#pragma pack(push, 1)
	tplt<tpnm T>
	struct rect2 {
		::llc::n2<T>			Offset, Size;

		LLC_DEFAULT_OPERATOR(rect2<T>, Offset	== other.Offset	&& Size == other.Size);

		tpl_t	
		inlcxpr	rect2<_t>	Cast		()	const	noexcept	{ return {Offset.tplt Cast<_t>(), Size.tplt Cast<_t>()}; }

		inlcxpr	rect2<u0_t>	u8			()	const	noexcept	{ return Cast<u0_t>(); }
		inlcxpr	rect2<u1_t>	u16			()	const	noexcept	{ return Cast<u1_t>(); }
		inlcxpr	rect2<u2_t>	u32			()	const	noexcept	{ return Cast<u2_t>(); }
		inlcxpr	rect2<u3_t>	u64			()	const	noexcept	{ return Cast<u3_t>(); }
		inlcxpr	rect2<s0_t>	i8			()	const	noexcept	{ return Cast<s0_t>(); }
		inlcxpr	rect2<s1_t>	i16			()	const	noexcept	{ return Cast<s1_t>(); }
		inlcxpr	rect2<s2_t>	i32			()	const	noexcept	{ return Cast<s2_t>(); }
		inlcxpr	rect2<s3_t>	i64			()	const	noexcept	{ return Cast<s3_t>(); }
		inlcxpr	rect2<f2_t>	f32			()	const	noexcept	{ return Cast<f2_t>(); }
		inlcxpr	rect2<f3_t>	f64			()	const	noexcept	{ return Cast<f3_t>(); }

		inline	::llc::n2<T>	Limit		()	const	noexcept	{ return Offset + Size; }
	};
	typedef rect2<uc_t>	rect2uc_t;	typedef	const rect2uc_t	rect2uc_c;	
	typedef rect2<sc_t>	rect2sc_t;	typedef	const rect2sc_t	rect2sc_c;	
	typedef rect2<u0_t>	rect2u0_t;	typedef	const rect2u0_t	rect2u0_c;	
	typedef rect2<u1_t>	rect2u1_t;	typedef	const rect2u1_t	rect2u1_c;	
	typedef rect2<u2_t>	rect2u2_t;	typedef	const rect2u2_t	rect2u2_c;	
	typedef rect2<u3_t>	rect2u3_t;	typedef	const rect2u3_t	rect2u3_c;	
	typedef rect2<s0_t>	rect2s0_t;	typedef	const rect2s0_t	rect2s0_c;	
	typedef rect2<s1_t>	rect2s1_t;	typedef	const rect2s1_t	rect2s1_c;	
	typedef rect2<s2_t>	rect2s2_t;	typedef	const rect2s2_t	rect2s2_c;	
	typedef rect2<s3_t>	rect2s3_t;	typedef	const rect2s3_t	rect2s3_c;	
	typedef rect2<f2_t>	rect2f2_t;	typedef	const rect2f2_t	rect2f2_c;	
	typedef rect2<f3_t>	rect2f3_t;	typedef	const rect2f3_t	rect2f3_c;	

#pragma pack(pop)

	tplt<tpnm T>
	stacxpr	bool	in_range	(const ::llc::n2<T>& pointToTest, const ::llc::rect2<T>& area)	noexcept	{
		return	::llc::in_range(pointToTest.x, area.Offset.x, (T)(area.Offset.x + area.Size.x))
			&&	::llc::in_range(pointToTest.y, area.Offset.y, (T)(area.Offset.y + area.Size.y))
			;
	}
} // namespace

#endif // LLC_RECT2_H
