#include "llc_typeint.h"

#ifndef LLC_MINMAX_H
#define LLC_MINMAX_H

namespace llc
{
#pragma pack(push, 1)
	tpl_t struct minmax {
		tydf	_t				T;
		tydf	minmax<T>		TMinMax;

		T						Min, Max;

		LLC_DEFAULT_OPERATOR(minmax<T>, Max == other.Max && Min == other.Min);

		stincxp	TMinMax			from		(T value)			nxpt	{ return {value, value}; }
		inlcxpr	T				Length		()				cnstnxpt	{ return T(Max - Min); }
		inlcxpr	T				Middle		()				cnstnxpt	{ return Min + Length() / 2; }
		inlcxpr	T				Clamp		(T value)		cnstnxpt	{ return ::llc::clamped(value, Min, Max); }
		T						Weighted	(f3_t weight)	cnstnxpt	{ return T(Min + Length() * weight); }
		f3_t					Weight		(T value)		cnstnxpt	{ return 1.0 / Length() * (value - Min); }
		f3_t					WeightClamp	(T value)		cnstnxpt	{ return Weight(Clamp(value)); }

		tpl_t2
		inlcxpr	minmax<_t2> 	Cast		()				cnstnxpt	{ return{(_t2)Min, (_t2)Max}; } 

		inlcxpr	minmax<uc_t> 	uc			()				cnstnxpt	{ return Cast<uc_t>(); }
		inlcxpr	minmax<sc_t> 	sc			()				cnstnxpt	{ return Cast<sc_t>(); }
		inlcxpr	minmax<u0_t> 	u0			()				cnstnxpt	{ return Cast<u0_t>(); }
		inlcxpr	minmax<u1_t> 	u1			()				cnstnxpt	{ return Cast<u1_t>(); }
		inlcxpr	minmax<u2_t> 	u2			()				cnstnxpt	{ return Cast<u2_t>(); }
		inlcxpr	minmax<u3_t> 	u3			()				cnstnxpt	{ return Cast<u3_t>(); }
		inlcxpr	minmax<s0_t> 	s0			()				cnstnxpt	{ return Cast<s0_t>(); }
		inlcxpr	minmax<s1_t> 	s1			()				cnstnxpt	{ return Cast<s1_t>(); }
		inlcxpr	minmax<s2_t> 	s2			()				cnstnxpt	{ return Cast<s2_t>(); }
		inlcxpr	minmax<s3_t> 	s3			()				cnstnxpt	{ return Cast<s3_t>(); }
		inlcxpr	minmax<f2_t> 	f2			()				cnstnxpt	{ return Cast<f2_t>(); }
		inlcxpr	minmax<f3_t> 	f3			()				cnstnxpt	{ return Cast<f3_t>(); }

		inline	TMinMax&		Set			(T value)			nxpt	{ Min = Max = value; return *this; }
		inline	TMinMax&		From		(T value)			nxpt	{ Min = Max = value; return *this; }
	};
#pragma pack(pop)
	tydf	minmax<uc_t>	minmaxuc_t;	tydfcnst	minmaxuc_t	minmaxuc_c;
	tydf	minmax<sc_t>	minmaxsc_t;	tydfcnst	minmaxsc_t	minmaxsc_c;
	tydf	minmax<u0_t>	minmaxu0_t;	tydfcnst	minmaxu0_t	minmaxu0_c;
	tydf	minmax<u1_t>	minmaxu1_t;	tydfcnst	minmaxu1_t	minmaxu1_c;
	tydf	minmax<u2_t>	minmaxu2_t;	tydfcnst	minmaxu2_t	minmaxu2_c;
	tydf	minmax<u3_t>	minmaxu3_t;	tydfcnst	minmaxu3_t	minmaxu3_c;
	tydf	minmax<s0_t>	minmaxs0_t;	tydfcnst	minmaxs0_t	minmaxs0_c;
	tydf	minmax<s1_t>	minmaxs1_t;	tydfcnst	minmaxs1_t	minmaxs1_c;
	tydf	minmax<s2_t>	minmaxs2_t;	tydfcnst	minmaxs2_t	minmaxs2_c;
	tydf	minmax<s3_t>	minmaxs3_t;	tydfcnst	minmaxs3_t	minmaxs3_c;
	tydf	minmax<f2_t>	minmaxf2_t;	tydfcnst	minmaxf2_t	minmaxf2_c;
	tydf	minmax<f3_t>	minmaxf3_t;	tydfcnst	minmaxf3_t	minmaxf3_c;
}

#endif // LLC_MINMAX_H
