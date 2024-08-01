#include "llc_typeint.h"

#ifndef LLC_RANGE_H
#define LLC_RANGE_H

namespace llc
{
#pragma pack(push, 1)
	tpl_t struct range {	
		tydf		_t	T;
		T							Offset, Count;	
		LLC_DEFAULT_OPERATOR(range <T>, Offset == other.Offset && Count == other.Count); 

		tpl_t2
		inlcxpr	range<_t2>			Cast		()		const	noexcept	{ return{(_t2)Offset, (_t2)Count}; } 
		inlcxpr	range<uc_t>			uc			()		const	noexcept	{ return Cast<uc_t>(); }
		inlcxpr	range<sc_t>			sc			()		const	noexcept	{ return Cast<sc_t>(); }
		inlcxpr	range<u0_t>			u0			()		const	noexcept	{ return Cast<u0_t>(); }
		inlcxpr	range<u1_t>			u1			()		const	noexcept	{ return Cast<u1_t>(); }
		inlcxpr	range<u2_t>			u2			()		const	noexcept	{ return Cast<u2_t>(); }
		inlcxpr	range<u3_t>			u3			()		const	noexcept	{ return Cast<u3_t>(); }
		inlcxpr	range<s0_t>			s0			()		const	noexcept	{ return Cast<s0_t>(); }
		inlcxpr	range<s1_t>			s1			()		const	noexcept	{ return Cast<s1_t>(); }
		inlcxpr	range<s2_t>			s2			()		const	noexcept	{ return Cast<s2_t>(); }
		inlcxpr	range<s3_t>			s3			()		const	noexcept	{ return Cast<s3_t>(); }
		inlcxpr	range<f2_t>			f2			()		const	noexcept	{ return Cast<f2_t>(); }
		inlcxpr	range<f3_t>			f3			()		const	noexcept	{ return Cast<f3_t>(); }
	};
#pragma pack(pop)

	typedef	range<uc_t>	rangeuc_t;	typedef	const rangeuc_t	rangeuc_c;
	typedef	range<sc_t>	rangesc_t;	typedef	const rangesc_t	rangesc_c;
	typedef	range<u0_t>	rangeu0_t;	typedef	const rangeu0_t	rangeu0_c;
	typedef	range<u1_t>	rangeu1_t;	typedef	const rangeu1_t	rangeu1_c;
	typedef	range<u2_t>	rangeu2_t;	typedef	const rangeu2_t	rangeu2_c;
	typedef	range<u3_t>	rangeu3_t;	typedef	const rangeu3_t	rangeu3_c;
	typedef	range<s0_t>	ranges0_t;	typedef	const ranges0_t	ranges0_c;
	typedef	range<s1_t>	ranges1_t;	typedef	const ranges1_t	ranges1_c;
	typedef	range<s2_t>	ranges2_t;	typedef	const ranges2_t	ranges2_c;
	typedef	range<s3_t>	ranges3_t;	typedef	const ranges3_t	ranges3_c;
	typedef	range<f2_t>	rangef2_t;	typedef	const rangef2_t	rangef2_c;
	typedef	range<f3_t>	rangef3_t;	typedef	const rangef3_t	rangef3_c;
}

#endif // GPK_RANGE_H
