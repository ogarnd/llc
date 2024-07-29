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
	typedef	unsigned char	uc_t, c0u_t;
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

	typedef	const b8_t		b8_c, b8u_c;
	typedef	const uc_t		uc_c, c0u_c;
	typedef	const sc_t		sc_c, c0s_c;
	typedef	const u0_t		u0_c, i0u_c;
	typedef	const u1_t		u1_c, i1u_c;
	typedef	const u2_t		u2_c, i2u_c;
	typedef	const u3_t		u3_c, i3u_c;
	typedef	const s0_t		s0_c, i0s_c;
	typedef	const s1_t		s1_c, i1s_c;
	typedef	const s2_t		s2_c, i2s_c;
	typedef	const s3_t		s3_c, i3s_c;
	typedef	const f2_t		f2_c, f2s_c;
	typedef	const f3_t		f3_c, f3s_c;

#if defined(LLC_ANDROID) || defined(LLC_CLANG)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wtautological-constant-out-of-range-compare"
#endif
	// -- Returns 0 on little-endian machines
	ndstain int		test_endianness		()	noexcept	{ stacxpr u1_c test = 0xFF00U; return (0xFFU == ((const  char*)&test)[0]) ? 1 : 0; }
#if defined(LLC_ANDROID) || defined(LLC_CLANG)
#	pragma clang diagnostic pop
#endif

#define tpltN0u     tplt<u0_t N>
#define tpltN1u     tplt<u1_t N>
#define tpltN2u     tplt<u2_t N>
#define tpltN3u     tplt<u3_t N>
#define	tpltTIn     tplt<tpnm TIn>
#define	tpltTOut    tplt<tpnm TOut>
#define	tpltTN2     tplt<tpnm T     , u2_t N>
#define	tpltTOutN2  tplt<tpnm TOut  , u2_t N>
#define	tpltTInN2   tplt<tpnm TIn   , u2_t N>

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
	tplT	struct remove_cv						{ using type = T; };
	tplT	struct remove_cv<const		T>			{ using type = T; };
	tplT	struct remove_cv<vltl		T>			{ using type = T; };
	tplT	struct remove_cv<const vltl	T>			{ using type = T; };
	tplT	using	remove_cv_t			= tpnm remove_cv<T>::type;

	tplT	struct remove_volatile					{ using type = T; };
	tplT	struct remove_volatile<const		T>	{ using type = T; };
	tplT	struct remove_volatile<vltl			T>	{ using type = T; };
	tplT	struct remove_volatile<const vltl	T>	{ using type = T; };
	tplT	using	remove_volatile_t	= tpnm remove_volatile<T>::type;

	tplTInTOut	stincxp	TOut	dim2		(TIn value)				nxpt	{ return {value, value}; }
	tplTInTOut	stincxp	TOut	dim3		(TIn value)				nxpt	{ return {value, value, value}; }
	tplT		ndstinx	u0_t	byte_at		(T value, u0_t index)	nxpt	{ return u0_t((value & (T(0xFFU) << (8 * index))) >> (8 * index)); }
	tplT		ndstinx	T		byte_to		(u0_t byte, u0_t index)	nxpt	{ return T(byte) << (u2_t(8U) * index); }
	tplT		nodscrd	T&		global		()						nxpt	{ static T instance = {}; return instance; }

	tplT	struct srcdst { T src, dst; }; 
	tplT	struct dstsrc { T dst, src; }; 
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
