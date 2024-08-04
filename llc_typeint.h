#include "llc_debug.h"

#ifdef LLC_WINDOWS
#	include <cstdint>
#else
#	if defined(LLC_ATMEL)
#		include <stddef.h>
#		include <stdint.h>
#	else
#		include <cstddef>
#		include <cstdint>
#	endif
#endif

#ifdef LLC_ATMEL
//#	include "initializer_list.h"
#else
#	include <initializer_list>
#endif

#ifndef LLC_TYPEINT_H_23627
#define LLC_TYPEINT_H_23627

namespace llc
{
	tydf bool		b8_t, b8u_t;
	tydf char		sc_t, c0s_t;
	tydf int8_t		s0_t, i0s_t;
	tydf int16_t	s1_t, i1s_t;
	tydf int32_t	s2_t, i2s_t;
	tydf int64_t	s3_t, i3s_t;
	tydf unsd char	uc_t, c0u_t;
	tydf uint8_t	u0_t, i0u_t;
	tydf uint16_t	u1_t, i1u_t;
	tydf uint32_t	u2_t, i2u_t;
	tydf uint64_t	u3_t, i3u_t;
	tydf float		f2_t, f2s_t;
	tydf double		f3_t, f3s_t;
	tydf size_t		uP_t, iPu_t;
#define	szof(type)																\
	( (sizeof(type) > 0xFFFFU)	? ::llc::u2_t(sizeof(type) & 0xFFFFFFFFU	)	\
	: (sizeof(type) > 0xFFU)	? ::llc::u1_t(sizeof(type) & 0xFFFFU		)	\
	: ::llc::u0_t(sizeof(type) & 0xFFU)											\
	)
	tdcs	b8_t	b8_c, b8u_c;
	tdcs	uc_t	uc_c, c0u_c;
	tdcs	sc_t	sc_c, c0s_c;
	tdcs	u0_t	u0_c, i0u_c;
	tdcs	u1_t	u1_c, i1u_c;
	tdcs	u2_t	u2_c, i2u_c;
	tdcs	u3_t	u3_c, i3u_c;
	tdcs	s0_t	s0_c, i0s_c;
	tdcs	s1_t	s1_c, i1s_c;
	tdcs	s2_t	s2_c, i2s_c;
	tdcs	s3_t	s3_c, i3s_c;
	tdcs	f2_t	f2_c, f2s_c;
	tdcs	f3_t	f3_c, f3s_c;
	tdcs	uP_t	uP_c, iPu_c;

#define tplN0u		tplt<::llc::u0_t N>
#define tplN1u		tplt<::llc::u1_t N>
#define tplN2u		tplt<::llc::u2_t N>
#define tplN3u		tplt<::llc::u3_t N>
#define tplNPu		tplt<::llc::uP_t N>
#define tpl_nu0		tplt<::llc::u0_t _nu0>
#define tpl_nu1		tplt<::llc::u1_t _nu1>
#define tpl_nu2		tplt<::llc::u2_t _nu2>
#define tpl_nu3		tplt<::llc::u3_t _nu3>
#define tpl_nuP		tplt<::llc::uP_t _nuP>
#define tplTIn		tplt<tpnm TIn>
#define tplTOut		tplt<tpnm TOut>
#define tplTN2		tplt<tpnm T		, ::llc::u2_t N>
#define tplTOutN2	tplt<tpnm TOut	, ::llc::u2_t N>
#define tplTInN2	tplt<tpnm TIn	, ::llc::u2_t N>
#define tpl_t_nu2	tplt<tpnm _t		, ::llc::u2_t _nu2>
	
#if defined(LLC_ANDROID) || defined(LLC_CLANG)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wtautological-constant-out-of-range-compare"
#endif
	// -- Returns 0 on little-endian machines
	ndsi	int		test_endianness		()	nxpt	{ stxp u1_c test = 0xFF00U; rtrn (0xFFU == ((sc_c*)&test)[0]) ? 1 : 0; }
#if defined(LLC_ANDROID) || defined(LLC_CLANG)
#	pragma clang diagnostic pop
#endif

	stxp	u0_c	PLATFORM_BYTE_BIT_COUNT					= 8;
#define	LLC_REFCOUNT_T	intptr_t
	tdvl	LLC_REFCOUNT_T	refcount_t;

	tpl_tstct	rm_cnst				{ usng T = _t; };
	tpl_tstct	rm_cnst<cnst _t>	{ usng T = _t; };
	tpl_tstct	rm_vltl				{ usng T = _t; };
	tpl_tstct	rm_vltl<vltl _t>	{ usng T = _t; };
	tpl_tstct	rm_csvl				{ usng T = _t; };
	tpl_tstct	rm_csvl<vltl _t>	{ usng T = _t; };
	tpl_tstct	rm_csvl<cnst _t>	{ usng T = _t; };
	tpl_tstct	rm_csvl<csvl _t>	{ usng T = _t; };
	tpl_tusng	rm_cnst_t			= tpnm rm_cnst<_t>::T;
	tpl_tusng	rm_vltl_t			= tpnm rm_vltl<_t>::T;
	tpl_tusng	rm_csvl_t			= tpnm rm_csvl<_t>::T;
#define llc_rmcnst(type)	tpnm ::llc::rm_cnst_t<type>
#define llc_rmvltl(type)	tpnm ::llc::rm_vltl_t<type>
#define llc_rmcsvl(type)	tpnm ::llc::rm_csvl_t<type>

#define tydfTCnst(type)		tydf llc_rmcnst(type) TCnst
#define tdfTTCnst(type)		tdfT(type); tydfTCnst(type)

	tplTInTOut	sinx	TOut	dim2		(TIn value)				nxpt	{ rtrn {value, value}; }
	tplTInTOut	sinx	TOut	dim3		(TIn value)				nxpt	{ rtrn {value, value, value}; }
	tplT		nsix	u0_t	byte_at		(T value, u0_t index)	nxpt	{ rtrn u0_t((value & (T(0xFFU) << (8 * index))) >> (8 * index)); }
	tplT		nsix	T		byte_to		(u0_t byte, u0_t index)	nxpt	{ rtrn T(byte) << (u2_t(8U) * index); }
	tplT		ndsc	T&		global		()						nxpt	{ sttc T instance = {}; rtrn instance; }

	tpl_tstct srcdst { tdfTTCnst(_t); T src, dst; }; 
	tpl_tstct dstsrc { tdfTTCnst(_t); T dst, src; };
#define LLC_USING_TYPEINT()				\
	usng	::llc::b8_t, ::llc::b8_c	\
		,	::llc::uc_t, ::llc::uc_c	\
		,	::llc::sc_t, ::llc::sc_c	\
		,	::llc::u0_t, ::llc::u0_c	\
		,	::llc::u1_t, ::llc::u1_c	\
		,	::llc::u2_t, ::llc::u2_c	\
		,	::llc::u3_t, ::llc::u3_c	\
		,	::llc::s0_t, ::llc::s0_c	\
		,	::llc::s1_t, ::llc::s1_c	\
		,	::llc::s2_t, ::llc::s2_c	\
		,	::llc::s3_t, ::llc::s3_c	\
		,	::llc::f2_t, ::llc::f2_c	\
		,	::llc::f3_t, ::llc::f3_c;

} // namespace

#if !defined(LLC_ANDROID) && !defined(LLC_ESP32) && !defined(LLC_ARDUINO)
#	define LLC_DEFAULT_OPERATOR_I(rightOperand, statement)	inln	bool	oper==(cnst rightOperand & other) csnx { rtrn statement; }
#	define LLC_DEFAULT_OPERATOR_C(rightOperand, statement)	cxpr	bool	oper==(cnst rightOperand & other) csnx { rtrn statement; }
#	define LLC_DEFAULT_OPERATOR_IC(rightOperand, statement)	inxp	bool	oper==(cnst rightOperand & other) csnx { rtrn statement; }
#	define LLC_DEFAULT_OPERATOR_D(rightOperand, statement)	bool			oper==(cnst rightOperand & other) csnx { rtrn statement; }
#else
#	define LLC_DEFAULT_OPERATOR_I(rightOperand, statement)	inln	bool	oper==(cnst rightOperand & other) csnx { rtrn statement; }	inln	bool	oper!=(cnst rightOperand & other) csnx { rtrn !oper==(other); }	// I had to add this because Clang coming with vs doesn't support C++20
#	define LLC_DEFAULT_OPERATOR_C(rightOperand, statement)	cxpr	bool	oper==(cnst rightOperand & other) csnx { rtrn statement; }	cxpr	bool	oper!=(cnst rightOperand & other) csnx { rtrn !oper==(other); }	// I had to add this because Clang coming with vs doesn't support C++20
#	define LLC_DEFAULT_OPERATOR_IC(rightOperand, statement)	inxp	bool	oper==(cnst rightOperand & other) csnx { rtrn statement; }	inxp	bool	oper!=(cnst rightOperand & other) csnx { rtrn !oper==(other); }	// I had to add this because Clang coming with vs doesn't support C++20
#	define LLC_DEFAULT_OPERATOR_D(rightOperand, statement)	bool			oper==(cnst rightOperand & other) csnx { rtrn statement; }			bool	oper!=(cnst rightOperand & other) csnx { rtrn !oper==(other); }	// I had to add this because Clang coming with vs doesn't support C++20
#endif // LLC_ANDROID

#define LLC_DEFAULT_OPERATOR LLC_DEFAULT_OPERATOR_IC

#ifndef LLC_ATMEL
#	define LLC_FMT_F2		"f"
#	define LLC_FMT_F3		"f"
#	define LLC_FMT_S2		"i"
#	define LLC_FMT_U2		"u"
#	define LLC_FMT_S3		"lli"
#	define LLC_FMT_U3		"llu"
#else
#	define LLC_FMT_F2		"f"
#	define LLC_FMT_F3		"f"
#	define LLC_FMT_S2		"li"
#	define LLC_FMT_U2		"lu"
#	define LLC_FMT_S3		"lli"
#	define LLC_FMT_U3		"llu"
#endif
#define LLC_FMT_SC		"c"
#define LLC_FMT_S0		"i"
#define LLC_FMT_U0		"u"
#define LLC_FMT_S1		"i"
#define LLC_FMT_U1		"u"
#define LLC_FMT_GT_F2	"%" LLC_FMT_F2 " > %" LLC_FMT_F2
#define LLC_FMT_GT_F3	"%" LLC_FMT_F3 " > %" LLC_FMT_F3
#define LLC_FMT_GT_S2	"%" LLC_FMT_S2 " > %" LLC_FMT_S2
#define LLC_FMT_GT_U2	"%" LLC_FMT_U2 " > %" LLC_FMT_U2
#define LLC_FMT_GT_S3	"%" LLC_FMT_S3 " > %" LLC_FMT_S3
#define LLC_FMT_GT_U3	"%" LLC_FMT_U3 " > %" LLC_FMT_U3

#define LLC_FMT_LT_F2	"%" LLC_FMT_F2 " < %" LLC_FMT_F2
#define LLC_FMT_LT_F3	"%" LLC_FMT_F3 " < %" LLC_FMT_F3
#define LLC_FMT_LT_S2	"%" LLC_FMT_S2 " < %" LLC_FMT_S2
#define LLC_FMT_LT_U2	"%" LLC_FMT_U2 " < %" LLC_FMT_U2
#define LLC_FMT_LT_S3	"%" LLC_FMT_S3 " < %" LLC_FMT_S3
#define LLC_FMT_LT_U3	"%" LLC_FMT_U3 " < %" LLC_FMT_U3

#define LLC_FMT_EQ_F2	"%" LLC_FMT_F2 " == %" LLC_FMT_F2
#define LLC_FMT_EQ_F3	"%" LLC_FMT_F3 " == %" LLC_FMT_F3
#define LLC_FMT_EQ_S2	"%" LLC_FMT_S2 " == %" LLC_FMT_S2
#define LLC_FMT_EQ_U2	"%" LLC_FMT_U2 " == %" LLC_FMT_U2
#define LLC_FMT_EQ_S3	"%" LLC_FMT_S3 " == %" LLC_FMT_S3
#define LLC_FMT_EQ_U3	"%" LLC_FMT_U3 " == %" LLC_FMT_U3

#define LLC_FMT_GE_F2	"%" LLC_FMT_F2 " >= %" LLC_FMT_F2
#define LLC_FMT_GE_F3	"%" LLC_FMT_F3 " >= %" LLC_FMT_F3
#define LLC_FMT_GE_S2	"%" LLC_FMT_S2 " >= %" LLC_FMT_S2
#define LLC_FMT_GE_U2	"%" LLC_FMT_U2 " >= %" LLC_FMT_U2
#define LLC_FMT_GE_S3	"%" LLC_FMT_S3 " >= %" LLC_FMT_S3
#define LLC_FMT_GE_U3	"%" LLC_FMT_U3 " >= %" LLC_FMT_U3

#define LLC_FMT_LE_F2	"%" LLC_FMT_F2 " <= %" LLC_FMT_F2
#define LLC_FMT_LE_F3	"%" LLC_FMT_F3 " <= %" LLC_FMT_F3
#define LLC_FMT_LE_S2	"%" LLC_FMT_S2 " <= %" LLC_FMT_S2
#define LLC_FMT_LE_U2	"%" LLC_FMT_U2 " <= %" LLC_FMT_U2
#define LLC_FMT_LE_S3	"%" LLC_FMT_S3 " <= %" LLC_FMT_S3
#define LLC_FMT_LE_U3	"%" LLC_FMT_U3 " <= %" LLC_FMT_U3

#define LLC_FMT_NE_F2	"%" LLC_FMT_F2 " != %" LLC_FMT_F2
#define LLC_FMT_NE_F3	"%" LLC_FMT_F3 " != %" LLC_FMT_F3
#define LLC_FMT_NE_S2	"%" LLC_FMT_S2 " != %" LLC_FMT_S2
#define LLC_FMT_NE_U2	"%" LLC_FMT_U2 " != %" LLC_FMT_U2
#define LLC_FMT_NE_S3	"%" LLC_FMT_S3 " != %" LLC_FMT_S3
#define LLC_FMT_NE_U3	"%" LLC_FMT_U3 " != %" LLC_FMT_U3

#endif // LLC_TYPEINT_H_23627
