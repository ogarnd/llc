/// Copyright 2009-2023 - ogarnd
#include "llc_n2.h"
#include "llc_minmax.h"

#ifndef LLC_MINMAX_N2
#define LLC_MINMAX_N2

namespace llc
{
#pragma pack(push, 1)
	tydf	minmax<n2uc_t>	minmax2uc_t;	tydfcnst	minmax2uc_t	minmax2uc_c;
	tydf	minmax<n2sc_t>	minmax2sc_t;	tydfcnst	minmax2sc_t	minmax2sc_c;
	tydf	minmax<n2u0_t>	minmax2u0_t;	tydfcnst	minmax2u0_t	minmax2u0_c;
	tydf	minmax<n2u1_t>	minmax2u1_t;	tydfcnst	minmax2u1_t	minmax2u1_c;
	tydf	minmax<n2u2_t>	minmax2u2_t;	tydfcnst	minmax2u2_t	minmax2u2_c;
	tydf	minmax<n2u3_t>	minmax2u3_t;	tydfcnst	minmax2u3_t	minmax2u3_c;
	tydf	minmax<n2s0_t>	minmax2s0_t;	tydfcnst	minmax2s0_t	minmax2s0_c;
	tydf	minmax<n2s1_t>	minmax2s1_t;	tydfcnst	minmax2s1_t	minmax2s1_c;
	tydf	minmax<n2s2_t>	minmax2s2_t;	tydfcnst	minmax2s2_t	minmax2s2_c;
	tydf	minmax<n2s3_t>	minmax2s3_t;	tydfcnst	minmax2s3_t	minmax2s3_c;
	tydf	minmax<n2f2_t>	minmax2f2_t;	tydfcnst	minmax2f2_t	minmax2f2_c;
	tydf	minmax<n2f3_t>	minmax2f3_t;	tydfcnst	minmax2f3_t	minmax2f3_c;
#pragma pack(pop)
} // namespace

#endif // LLC_MINMAX_N2
