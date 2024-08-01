#include "llc_typeint.h"

#ifndef LLC_TRI_H_23627
#define LLC_TRI_H_23627

namespace llc 
{
#pragma pack(push, 1)
	tplt<tpnm _tVertex>
	struct tri { 
		_tVertex	A, B, C; 

		cxpr		tri()															nxpt	= default;
		cxpr		tri(cnst tri & other)											nxpt	= default;
		cxpr		tri(cnst _tVertex & a, cnst _tVertex & b, cnst _tVertex & c)	nxpt	: A(a), B(b), C(c)	{}

		LLC_DEFAULT_OPERATOR(tri<_tVertex>, A == other.A && B == other.B && C == other.C);
	};
	typedef	tri<uc_t>	triuc_t;	typedef	cnst triuc_t	triuc_c;
	typedef	tri<sc_t>	trisc_t;	typedef	cnst trisc_t	trisc_c;
	typedef	tri<u0_t>	triu0_t;	typedef	cnst triu0_t	triu0_c;
	typedef	tri<u1_t>	triu1_t;	typedef	cnst triu1_t	triu1_c;
	typedef	tri<u2_t>	triu2_t;	typedef	cnst triu2_t	triu2_c;
	typedef	tri<u3_t>	triu3_t;	typedef	cnst triu3_t	triu3_c;
	typedef	tri<s0_t>	tris0_t;	typedef	cnst tris0_t	tris0_c;
	typedef	tri<s1_t>	tris1_t;	typedef	cnst tris1_t	tris1_c;
	typedef	tri<s2_t>	tris2_t;	typedef	cnst tris2_t	tris2_c;
	typedef	tri<s3_t>	tris3_t;	typedef	cnst tris3_t	tris3_c;
	typedef	tri<f2_t>	trif2_t;	typedef	cnst trif2_t	trif2_c;
	typedef	tri<f3_t>	trif3_t;	typedef	cnst trif3_t	trif3_c;

#pragma pack(pop)
} // namespace 

#endif // LLC_TRI_H_23627