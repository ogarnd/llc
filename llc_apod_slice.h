#include "llc_array_pod.h"
#include "llc_slice.h"

#ifndef LLC_APOD_SLICE_H
#define LLC_APOD_SLICE_H

namespace llc
{
	tplT using	aslice	= ::llc::apod<::llc::slice<T>>;

	tydf	::llc::aslice<sc_t>	aslicesc_t;	tydfcnst	aslicesc_t	aslicesc_c;
	tydf	::llc::aslice<uc_t>	asliceuc_t;	tydfcnst	asliceuc_t	asliceuc_c;
	tydf	::llc::aslice<u0_t>	asliceu0_t;	tydfcnst	asliceu0_t	asliceu0_c;
	tydf	::llc::aslice<u1_t>	asliceu1_t;	tydfcnst	asliceu1_t	asliceu1_c;
	tydf	::llc::aslice<u2_t>	asliceu2_t;	tydfcnst	asliceu2_t	asliceu2_c;
	tydf	::llc::aslice<u3_t>	asliceu3_t;	tydfcnst	asliceu3_t	asliceu3_c;
	tydf	::llc::aslice<s0_t>	aslices0_t;	tydfcnst	aslices0_t	aslices0_c;
	tydf	::llc::aslice<s1_t>	aslices1_t;	tydfcnst	aslices1_t	aslices1_c;
	tydf	::llc::aslice<s2_t>	aslices2_t;	tydfcnst	aslices2_t	aslices2_c;
	tydf	::llc::aslice<s3_t>	aslices3_t;	tydfcnst	aslices3_t	aslices3_c;
	tydf	::llc::aslice<f2_t>	aslicef2_t;	tydfcnst	aslicef2_t	aslicef2_c;
	tydf	::llc::aslice<f3_t>	aslicef3_t;	tydfcnst	aslicef3_t	aslicef3_c;
}

#endif // LLC_APOD_SLICE_H