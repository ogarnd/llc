#include "llc_n2.h"

#ifndef LLC_CIRCLE_H_23627
#define LLC_CIRCLE_H_23627

namespace llc
{
#pragma pack(push, 1)	// You can read about pragma pack() here: https://www.google.com/search?q=pragma+pack
	tpl_t struct circle { 
		tydf	_t		T;
		f3_t			Radius; 
		::llc::n2<T>	Center; 

		LLC_DEFAULT_OPERATOR(circle<T>, Center == other.Center && Radius == other.Radius); 
	};
	tydf	circle<uc_t>	circleuc_t;	tydfcnst circleuc_t	circleuc_c;
	tydf	circle<sc_t>	circlesc_t;	tydfcnst circlesc_t	circlesc_c;
	tydf	circle<u0_t>	circleu0_t;	tydfcnst circleu0_t	circleu0_c;
	tydf	circle<u1_t>	circleu1_t;	tydfcnst circleu1_t	circleu1_c;
	tydf	circle<u2_t>	circleu2_t;	tydfcnst circleu2_t	circleu2_c;
	tydf	circle<u3_t>	circleu3_t;	tydfcnst circleu3_t	circleu3_c;
	tydf	circle<s0_t>	circles0_t;	tydfcnst circles0_t	circles0_c;
	tydf	circle<s1_t>	circles1_t;	tydfcnst circles1_t	circles1_c;
	tydf	circle<s2_t>	circles2_t;	tydfcnst circles2_t	circles2_c;
	tydf	circle<s3_t>	circles3_t;	tydfcnst circles3_t	circles3_c;
	tydf	circle<f2_t>	circlef2_t;	tydfcnst circlef2_t	circlef2_c;
	tydf	circle<f3_t>	circlef3_t;	tydfcnst circlef3_t	circlef3_c;
#pragma pack(pop)
} // namespace

#endif // LLC_CIRCLE_H_23627
