#include "llc_n3.h"

#ifndef LLC_SLICE_H
#define LLC_SLICE_H

namespace llc
{
#pragma pack(push, 1)
	tpl_t
	struct slice {
		tydf	_t		T;
		T				Begin, End;

		LLC_DEFAULT_OPERATOR(slice <T>, Begin  == other.Begin  && End   == other.End  );

		tpl_t2
		inlcxpr	slice<_t2>		Cast		()		cnstnxpt	{ return{(_t2)Begin , (_t2)End  }; }

		inlcxpr	slice<uc_t>		uc			()		cnstnxpt	{ return Cast<uc_t>(); }
		inlcxpr	slice<sc_t>		sc			()		cnstnxpt	{ return Cast<sc_t>(); }
		inlcxpr	slice<u0_t>		u0			()		cnstnxpt	{ return Cast<u0_t>(); }
		inlcxpr	slice<u1_t>		u1			()		cnstnxpt	{ return Cast<u1_t>(); }
		inlcxpr	slice<u2_t>		u2			()		cnstnxpt	{ return Cast<u2_t>(); }
		inlcxpr	slice<u3_t>		u3			()		cnstnxpt	{ return Cast<u3_t>(); }
		inlcxpr	slice<s0_t>		s0			()		cnstnxpt	{ return Cast<s0_t>(); }
		inlcxpr	slice<s1_t>		s1			()		cnstnxpt	{ return Cast<s1_t>(); }
		inlcxpr	slice<s2_t>		s2			()		cnstnxpt	{ return Cast<s2_t>(); }
		inlcxpr	slice<s3_t>		s3			()		cnstnxpt	{ return Cast<s3_t>(); }
		inlcxpr	slice<f2_t>		f2			()		cnstnxpt	{ return Cast<f2_t>(); }
		inlcxpr	slice<f3_t>		f3			()		cnstnxpt	{ return Cast<f3_t>(); }
	};
#pragma pack(pop)

	typedef	slice<uc_t>		sliceuc_t;	typedef	cnst sliceuc_t	sliceuc_c;
	typedef	slice<sc_t>		slicesc_t;	typedef	cnst slicesc_t	slicesc_c;
	typedef	slice<u0_t>		sliceu0_t;	typedef	cnst sliceu0_t	sliceu0_c;
	typedef	slice<u1_t>		sliceu1_t;	typedef	cnst sliceu1_t	sliceu1_c;
	typedef	slice<u2_t>		sliceu2_t;	typedef	cnst sliceu2_t	sliceu2_c;
	typedef	slice<u3_t>		sliceu3_t;	typedef	cnst sliceu3_t	sliceu3_c;
	typedef	slice<s0_t>		slices0_t;	typedef	cnst slices0_t	slices0_c;
	typedef	slice<s1_t>		slices1_t;	typedef	cnst slices1_t	slices1_c;
	typedef	slice<s2_t>		slices2_t;	typedef	cnst slices2_t	slices2_c;
	typedef	slice<s3_t>		slices3_t;	typedef	cnst slices3_t	slices3_c;
	typedef	slice<f2_t>		slicef2_t;	typedef	cnst slicef2_t	slicef2_c;
	typedef	slice<f3_t>		slicef3_t;	typedef	cnst slicef3_t	slicef3_c;

	typedef	slice<n2uc_t>	slice2uc_t;	typedef	cnst slice2uc_t	slice2uc_c;
	typedef	slice<n2sc_t>	slice2sc_t;	typedef	cnst slice2sc_t	slice2sc_c;
	typedef slice<n2u0_t>	slice2u0_t;	typedef	cnst slice2u0_t	slice2u0_c;
	typedef slice<n2u1_t>	slice2u1_t;	typedef	cnst slice2u1_t	slice2u1_c;
	typedef slice<n2u2_t>	slice2u2_t;	typedef	cnst slice2u2_t	slice2u2_c;
	typedef slice<n2u3_t>	slice2u3_t;	typedef	cnst slice2u3_t	slice2u3_c;
	typedef slice<n2s0_t>	slice2s0_t;	typedef	cnst slice2s0_t	slice2s0_c;
	typedef slice<n2s1_t>	slice2s1_t;	typedef	cnst slice2s1_t	slice2s1_c;
	typedef slice<n2s2_t>	slice2s2_t;	typedef	cnst slice2s2_t	slice2s2_c;
	typedef slice<n2s3_t>	slice2s3_t;	typedef	cnst slice2s3_t	slice2s3_c;
	typedef slice<n2f2_t>	slice2f2_t;	typedef	cnst slice2f2_t	slice2f2_c;
	typedef slice<n2f3_t>	slice2f3_t;	typedef	cnst slice2f3_t	slice2f3_c;

	typedef	slice<n3uc_t>	slice3uc_t;	typedef	cnst slice3uc_t	slice3uc_c;
	typedef	slice<n3sc_t>	slice3sc_t;	typedef	cnst slice3sc_t	slice3sc_c;
	typedef slice<n3u0_t>	slice3u0_t;	typedef	cnst slice3u0_t	slice3u0_c;
	typedef slice<n3u1_t>	slice3u1_t;	typedef	cnst slice3u1_t	slice3u1_c;
	typedef slice<n3u2_t>	slice3u2_t;	typedef	cnst slice3u2_t	slice3u2_c;
	typedef slice<n3u3_t>	slice3u3_t;	typedef	cnst slice3u3_t	slice3u3_c;
	typedef slice<n3s0_t>	slice3s0_t;	typedef	cnst slice3s0_t	slice3s0_c;
	typedef slice<n3s1_t>	slice3s1_t;	typedef	cnst slice3s1_t	slice3s1_c;
	typedef slice<n3s2_t>	slice3s2_t;	typedef	cnst slice3s2_t	slice3s2_c;
	typedef slice<n3s3_t>	slice3s3_t;	typedef	cnst slice3s3_t	slice3s3_c;
	typedef slice<n3f2_t>	slice3f2_t;	typedef	cnst slice3f2_t	slice3f2_c;
	typedef slice<n3f3_t>	slice3f3_t;	typedef	cnst slice3f3_t	slice3f3_c;
}

#endif // LLC_SLICE_H
