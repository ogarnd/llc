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

	typedef bool			b8_t, b8u_t;
	typedef	unsgnd char		uc_t, c0u_t;
	typedef	char			sc_t, c0s_t;
	typedef uint8_t			u0_t, i0u_t;
	typedef uint16_t		u1_t, i1u_t;
	typedef uint32_t		u2_t, i2u_t;
	typedef uint64_t		u3_t, i3u_t;
	typedef int8_t			s0_t, i0s_t;
	typedef int16_t			s1_t, i1s_t;
	typedef int32_t			s2_t, i2s_t;
	typedef int64_t			s3_t, i3s_t;
	typedef float			f2_t, f2s_t;
	typedef double			f3_t, f3s_t;

	typedef	cnst b8_t		b8_c, b8u_c;
	typedef	cnst uc_t		uc_c, c0u_c;
	typedef	cnst sc_t		sc_c, c0s_c;
	typedef	cnst u0_t		u0_c, i0u_c;
	typedef	cnst u1_t		u1_c, i1u_c;
	typedef	cnst u2_t		u2_c, i2u_c;
	typedef	cnst u3_t		u3_c, i3u_c;
	typedef	cnst s0_t		s0_c, i0s_c;
	typedef	cnst s1_t		s1_c, i1s_c;
	typedef	cnst s2_t		s2_c, i2s_c;
	typedef	cnst s3_t		s3_c, i3s_c;
	typedef	cnst f2_t		f2_c, f2s_c;
	typedef	cnst f3_t		f3_c, f3s_c;

#define tplN0u     tplt<u0_t N>
#define tplN1u     tplt<u1_t N>
#define tplN2u     tplt<u2_t N>
#define tplN3u     tplt<u3_t N>
#define	tplTIn     tplt<tpnm TIn>
#define	tplTOut    tplt<tpnm TOut>
#define	tplTN2     tplt<tpnm T     , u2_t N>
#define	tplTOutN2  tplt<tpnm TOut  , u2_t N>
#define	tplTInN2   tplt<tpnm TIn   , u2_t N>

#if defined(LLC_ANDROID) || defined(LLC_CLANG)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wtautological-constant-out-of-range-compare"
#endif
	// -- Returns 0 on little-endian machines
	ndstain int		test_endianness		()	noexcept	{ stacxpr u1_c test = 0xFF00U; return (0xFFU == ((const  char*)&test)[0]) ? 1 : 0; }
#if defined(LLC_ANDROID) || defined(LLC_CLANG)
#	pragma clang diagnostic pop
#endif

	stacxpr	u0_c	PLATFORM_BYTE_BIT_COUNT					= 8;
#if defined LLC_WINDOWS
#	if defined(_WIN64) || defined(WIN64)
#		define	LLC_REFCOUNT_T		long long
		typedef vltl	LLC_REFCOUNT_T	refcount_t;
#	else
#		define	LLC_REFCOUNT_T		long
		typedef vltl	LLC_REFCOUNT_T	refcount_t;
#	endif
#else
#	define	LLC_REFCOUNT_T	intptr_t
	typedef vltl	LLC_REFCOUNT_T	refcount_t;
#endif
	tplTstruct remove_cv						{ using type = T; };
	tplTstruct remove_cv<cnst		T>			{ using type = T; };
	tplTstruct remove_cv<vltl		T>			{ using type = T; };
	tplTstruct remove_cv<cnstvltl	T>			{ using type = T; };
	tplT	using	remove_cv_t			= tpnm remove_cv<T>::type;

	tplTstruct remove_volatile					{ using type = T; };
	tplTstruct remove_volatile<cnst		T>		{ using type = T; };
	tplTstruct remove_volatile<vltl		T>		{ using type = T; };
	tplTstruct remove_volatile<cnstvltl	T>		{ using type = T; };
	tplT	using	remove_volatile_t	= tpnm remove_volatile<T>::type;

	tpl_t	struct rm_cnst							{ using T = _t; };
	tpl_t	struct rm_cnst<cnst _t>					{ using T = _t; };
	tpl_t	struct rm_vltl							{ using T = _t; };
	tpl_t	struct rm_vltl<vltl _t>					{ using T = _t; };
	tpl_t	struct rm_csvl							{ using T = _t; };
	tpl_t	struct rm_csvl<vltl		_t>				{ using T = _t; };
	tpl_t	struct rm_csvl<cnst		_t>				{ using T = _t; };
	tpl_t	struct rm_csvl<cnstvltl	_t>				{ using T = _t; };
	tpl_t	using	rm_cnst_t			= tpnm rm_cnst<_t>::T;
	tpl_t	using	rm_vltl_t			= tpnm rm_vltl<_t>::T;
	tpl_t	using	rm_csvl_t			= tpnm rm_csvl<_t>::T;

	tplTInTOut	stincxp	TOut	dim2		(TIn value)				nxpt	{ return {value, value}; }
	tplTInTOut	stincxp	TOut	dim3		(TIn value)				nxpt	{ return {value, value, value}; }
	tplT		ndstinx	u0_t	byte_at		(T value, u0_t index)	nxpt	{ return u0_t((value & (T(0xFFU) << (8 * index))) >> (8 * index)); }
	tplT		ndstinx	T		byte_to		(u0_t byte, u0_t index)	nxpt	{ return T(byte) << (u2_t(8U) * index); }
	tplT		nodscrd	T&		global		()						nxpt	{ static T instance = {}; return instance; }

	tplT	struct srcdst { T src, dst; }; 
	tplT	struct dstsrc { T dst, src; };
#define LLC_USING_TYPEINT()				\
	using	::llc::b8_t, ::llc::b8_c	\
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
#	define LLC_DEFAULT_OPERATOR_I(_otherType, statement)	inline	bool	operator==(const _otherType & other) const noexcept { return statement; }
#	define LLC_DEFAULT_OPERATOR_C(_otherType, statement)	cnstxpr	bool	operator==(const _otherType & other) const noexcept { return statement; }
#	define LLC_DEFAULT_OPERATOR_IC(_otherType, statement)	inlcxpr	bool	operator==(const _otherType & other) const noexcept { return statement; }
#	define LLC_DEFAULT_OPERATOR_D(_otherType, statement)	bool			operator==(const _otherType & other) const noexcept { return statement; }
#else
#	define LLC_DEFAULT_OPERATOR_I(_otherType, statement)	inline	bool	operator==(const _otherType & other) const noexcept { return statement; } inline	bool	operator!=(const _otherType & other) const noexcept { return !operator==(other); }	// I had to add this because Clang coming with vs doesn't support C++20
#	define LLC_DEFAULT_OPERATOR_C(_otherType, statement)	cnstxpr	bool	operator==(const _otherType & other) const noexcept { return statement; } cnstxpr	bool	operator!=(const _otherType & other) const noexcept { return !operator==(other); }	// I had to add this because Clang coming with vs doesn't support C++20
#	define LLC_DEFAULT_OPERATOR_IC(_otherType, statement)	inlcxpr	bool	operator==(const _otherType & other) const noexcept { return statement; } inlcxpr	bool	operator!=(const _otherType & other) const noexcept { return !operator==(other); }	// I had to add this because Clang coming with vs doesn't support C++20
#	define LLC_DEFAULT_OPERATOR_D(_otherType, statement)	bool	bool	operator==(const _otherType & other) const noexcept { return statement; } bool		bool	operator!=(const _otherType & other) const noexcept { return !operator==(other); }	// I had to add this because Clang coming with vs doesn't support C++20
#endif // LLC_ANDROID

#define LLC_DEFAULT_OPERATOR LLC_DEFAULT_OPERATOR_IC

#endif // LLC_TYPEINT_H_23627
