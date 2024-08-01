#include "llc_tri.h"
#include "llc_n2.h"
#include "llc_minmax.h"

#ifndef LLC_TRI2_H_23627
#define LLC_TRI2_H_23627

namespace llc 
{
#pragma pack(push, 1)
	tpl_t struct tri2 : public tri<::llc::n2<_t>>		{
		tydf	_t				T;
		tydf	::llc::n2<T>	TVertex;

		using	tri<TVertex>	::A;
		using	tri<TVertex>	::B;
		using	tri<TVertex>	::C;
		using	tri<TVertex>	::tri;

		inlcxpr	tri2<uc_t>		uc		()	cnstnxpt	{ return {A.uc(), B.uc(), C.uc()}; }
		inlcxpr	tri2<sc_t>		sc		()	cnstnxpt	{ return {A.sc(), B.sc(), C.sc()}; }
		inlcxpr	tri2<u0_t>		u0		()	cnstnxpt	{ return {A.u0(), B.u0(), C.u0()}; }
		inlcxpr	tri2<u1_t>		u1		()	cnstnxpt	{ return {A.u1(), B.u1(), C.u1()}; }
		inlcxpr	tri2<u2_t>		u2		()	cnstnxpt	{ return {A.u2(), B.u2(), C.u2()}; }
		inlcxpr	tri2<u3_t>		u3		()	cnstnxpt	{ return {A.u3(), B.u3(), C.u3()}; }
		inlcxpr	tri2<s0_t>		s0		()	cnstnxpt	{ return {A.s0(), B.s0(), C.s0()}; }
		inlcxpr	tri2<s1_t>		s1		()	cnstnxpt	{ return {A.s1(), B.s1(), C.s1()}; }
		inlcxpr	tri2<s2_t>		s2		()	cnstnxpt	{ return {A.s2(), B.s2(), C.s2()}; }
		inlcxpr	tri2<s3_t>		s3		()	cnstnxpt	{ return {A.s3(), B.s3(), C.s3()}; }
		inlcxpr	tri2<f2_t>		f2		()	cnstnxpt	{ return {A.f2(), B.f2(), C.f2()}; }
		inlcxpr	tri2<f3_t>		f3		()	cnstnxpt	{ return {A.f3(), B.f3(), C.f3()}; }

		tpl_t2	tri2<_t2>		Cast	()	cnstnxpt	{
			return
				{ A.tplt Cast<_t2>()
				, B.tplt Cast<_t2>()
				, C.tplt Cast<_t2>()
				};
		}
		cxpr	bool			CulledX		(cnst ::llc::minmax<T>& minMax)	cnstnxpt	{
			return ((A.x  < minMax.Min) && (B.x  < minMax.Min) && (C.x  < minMax.Min))
				|| ((A.x >= minMax.Max) && (B.x >= minMax.Max) && (C.x >= minMax.Max))
				;
		}
		cxpr	bool			CulledY		(cnst ::llc::minmax<T>& minMax)	cnstnxpt	{
			return ((A.y  < minMax.Min) && (B.y  < minMax.Min) && (C.y  < minMax.Min))
				|| ((A.y >= minMax.Max) && (B.y >= minMax.Max) && (C.y >= minMax.Max))
				;
		}
	};
	tydf	tri2<uc_t>	tri2uc_t;	tydf	cnst tri2uc_t	tri2uc_c;
	tydf	tri2<sc_t>	tri2sc_t;	tydf	cnst tri2sc_t	tri2sc_c;
	tydf	tri2<u0_t>	tri2u0_t;	tydf	cnst tri2u0_t	tri2u0_c;
	tydf	tri2<u1_t>	tri2u1_t;	tydf	cnst tri2u1_t	tri2u1_c;
	tydf	tri2<u2_t>	tri2u2_t;	tydf	cnst tri2u2_t	tri2u2_c;
	tydf	tri2<u3_t>	tri2u3_t;	tydf	cnst tri2u3_t	tri2u3_c;
	tydf	tri2<s0_t>	tri2s0_t;	tydf	cnst tri2s0_t	tri2s0_c;
	tydf	tri2<s1_t>	tri2s1_t;	tydf	cnst tri2s1_t	tri2s1_c;
	tydf	tri2<s2_t>	tri2s2_t;	tydf	cnst tri2s2_t	tri2s2_c;
	tydf	tri2<s3_t>	tri2s3_t;	tydf	cnst tri2s3_t	tri2s3_c;
	tydf	tri2<f2_t>	tri2f2_t;	tydf	cnst tri2f2_t	tri2f2_c;
	tydf	tri2<f3_t>	tri2f3_t;	tydf	cnst tri2f3_t	tri2f3_c;

	tydf	minmax<tri2uc_t>	minmaxtri2uc_t;	tydf	cnst minmaxtri2uc_t	minmaxtri2uc_c;
	tydf	minmax<tri2sc_t>	minmaxtri2sc_t;	tydf	cnst minmaxtri2sc_t	minmaxtri2sc_c;
	tydf	minmax<tri2u0_t>	minmaxtri2u0_t;	tydf	cnst minmaxtri2u0_t	minmaxtri2u0_c;
	tydf	minmax<tri2u1_t>	minmaxtri2u1_t;	tydf	cnst minmaxtri2u1_t	minmaxtri2u1_c;
	tydf	minmax<tri2u2_t>	minmaxtri2u2_t;	tydf	cnst minmaxtri2u2_t	minmaxtri2u2_c;
	tydf	minmax<tri2u3_t>	minmaxtri2u3_t;	tydf	cnst minmaxtri2u3_t	minmaxtri2u3_c;
	tydf	minmax<tri2s0_t>	minmaxtri2s0_t;	tydf	cnst minmaxtri2s0_t	minmaxtri2s0_c;
	tydf	minmax<tri2s1_t>	minmaxtri2s1_t;	tydf	cnst minmaxtri2s1_t	minmaxtri2s1_c;
	tydf	minmax<tri2s2_t>	minmaxtri2s2_t;	tydf	cnst minmaxtri2s2_t	minmaxtri2s2_c;
	tydf	minmax<tri2s3_t>	minmaxtri2s3_t;	tydf	cnst minmaxtri2s3_t	minmaxtri2s3_c;
	tydf	minmax<tri2f2_t>	minmaxtri2f2_t;	tydf	cnst minmaxtri2f2_t	minmaxtri2f2_c;
	tydf	minmax<tri2f3_t>	minmaxtri2f3_t;	tydf	cnst minmaxtri2f3_t	minmaxtri2f3_c;
#pragma pack(pop)

	tplT	::llc::n2<T>	triangleWeight	(cnst ::llc::tri<T> & weights, cnst ::llc::tri2<T> & values)	nxpt	{ return values.A * weights.A + values.B * weights.B + values.C * weights.C; }
	tplT	::llc::tri2<T>&	translate		(::llc::tri2<T> & triangle, cnst ::llc::n2<T> & translation)	nxpt	{
		triangle.A			+= translation;
		triangle.B			+= translation;
		triangle.C			+= translation;
		return triangle;
	}
} // namespace 

#endif // LLC_TRI2_H_23627