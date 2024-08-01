#include "llc_cpow.h"
#include "llc_view.h"

#ifndef LLC_ARRAY_STATIC_H_23627
#define LLC_ARRAY_STATIC_H_23627

namespace llc
{
#pragma pack(push, 1)
	tplt<tpnm _tVal, u2_t N>
	struct array_static	{
		stacxpr	const u2_t	SIZE	= N;

		typedef	_tVal					T;
		typedef array_static<T, SIZE>	TAStatic;
		typedef	view<const T>			TConstView;
		typedef	view<T>					TView;

		T					Storage	[SIZE]	;

		operator			view<T>			()															{ return {Storage, SIZE}; }
		operator			view<const T>	()										const	noexcept	{ return {Storage, SIZE}; }

		inline	const T&	operator[]		(u2_t index)							const				{ gthrow_if(index >= SIZE, LLC_FMT_U32_GE_U32, (int32_t)index, (int32_t)SIZE); return Storage[index]; }
		inline	T&			operator[]		(u2_t index)												{ gthrow_if(index >= SIZE, LLC_FMT_U32_GE_U32, (int32_t)index, (int32_t)SIZE); return Storage[index]; }
		LLC_DEFAULT_OPERATOR(TAStatic
			, (this->size() != other.size()) ? false
			: (this->begin() == other.begin()) ? true
			: ::llc::equal(other.begin(), this->begin(), this->size())
			);
		//bool					operator!=		(const ::llc::view<const T>& other)		const				{ return !operator==(other); }
		//bool					operator==		(const ::llc::view<const T>& other)		const				{
		//	return (this->size() != other.size()) ? false
		//		: (this->begin() == other.begin()) ? true
		//		: ::llc::equal(other.begin(), this->begin(), this->size())
		//		;
		//}
		// Methods
		inlcxpr	u2_t		byte_count		()										const	noexcept	{ return u2_t(SIZE * sizeof(T));	}
		inlcxpr	u2_t		bit_count		()										const	noexcept	{ return byte_count() * 8U;	}

		inline	view<u0_t>	u8				()												noexcept	{ return {(u0_t*)Storage, byte_count()};		}
		inlcxpr	view<u0_c>	u8				()										const	noexcept	{ return {(const u0_t*)Storage, byte_count()};	}
		inlcxpr	view<u0_c>	cu8				()										const	noexcept	{ return {(const u0_t*)Storage, byte_count()};	}
		inline	view<sc_t>	c				()												noexcept	{ return {(char*)Storage, byte_count()};			}
		inlcxpr	view<sc_c>	cc				()										const	noexcept	{ return {(const char*)Storage, byte_count()};		}

		inlcxpr	u2_c&		size			()										const	noexcept	{ return SIZE; }

		inline	T*			begin			()												noexcept	{ return Storage;			}
		inline	T*			end				()												noexcept	{ return Storage + SIZE;	}
		inlcxpr	const T*	begin			()										const	noexcept	{ return Storage;			}
		inlcxpr	const T*	end				()										const	noexcept	{ return Storage + SIZE;	}

		::llc::error_t		slice			(TView & out, u2_t offset, u2_t count = (u2_t)-1)				{
			ree_if(offset > SIZE, LLC_FMT_U32_GT_U32, offset, (u2_t)SIZE);
			const u2_t				newSize			= SIZE - offset;
			if(count != (u2_t)-1)
				ree_if(count > newSize, LLC_FMT_U32_GT_U32, count, (u2_t)newSize);
			out						= {&Storage[offset], ::llc::min(newSize, count)};
			return out.size();
		}
		::llc::error_t		slice			(TConstView & out, u2_t offset, u2_t count = (u2_t)-1)	const	{
			ree_if(offset > SIZE, LLC_FMT_U32_GT_U32, offset, (u2_t)SIZE);
			const u2_t				newSize			= SIZE - offset;
			if(count != (u2_t)-1)
				ree_if(count > newSize, LLC_FMT_U32_GT_U32, count, (u2_t)newSize);
			out						= {&Storage[offset], ::llc::min(newSize, count)};
			return out.size();
		}
	};
#pragma pack(pop)

	tplt<tpnm T, u2_t N>
	using astatic	= ::llc::array_static<T, N>;

	tplN2u	using astvcs	= ::llc::astatic<::llc::vcs	, N>;	tplN2u	using astaticvcs	= ::llc::astvcs	<N>;
	tplN2u	using astvs		= ::llc::astatic<::llc::vs	, N>;	tplN2u	using astaticvs		= ::llc::astvs	<N>;

	tplN2u	using astuc_t	= ::llc::astatic<uc_t, N>; tplN2u	using astuc 	= ::llc::astatic<uc_t, N>; tplN2u	using astaticuc 	= ::llc::astuc 	<N>; tplN2u	using astuchar	= ::llc::astatic<uc_t, N>;
	tplN2u	using astsc_t	= ::llc::astatic<sc_t, N>; tplN2u	using astc		= ::llc::astatic<sc_t, N>; tplN2u	using astaticc		= ::llc::astc	<N>; tplN2u	using astchar	= ::llc::astatic<sc_t, N>;
	tplN2u	using astu0_t	= ::llc::astatic<u0_t, N>; tplN2u	using astu8 	= ::llc::astatic<u0_t, N>; tplN2u	using astaticu8 	= ::llc::astu8 	<N>;
	tplN2u	using astu1_t	= ::llc::astatic<u1_t, N>; tplN2u	using astu16	= ::llc::astatic<u1_t, N>; tplN2u	using astaticu16	= ::llc::astu16	<N>;
	tplN2u	using astu2_t	= ::llc::astatic<u2_t, N>; tplN2u	using astu32	= ::llc::astatic<u2_t, N>; tplN2u	using astaticu32	= ::llc::astu32	<N>;
	tplN2u	using astu3_t	= ::llc::astatic<u3_t, N>; tplN2u	using astu64	= ::llc::astatic<u3_t, N>; tplN2u	using astaticu64	= ::llc::astu64	<N>;
	tplN2u	using asts0_t	= ::llc::astatic<s0_t, N>; tplN2u	using asti8 	= ::llc::astatic<s0_t, N>; tplN2u	using astatici8 	= ::llc::asti8 	<N>;
	tplN2u	using asts1_t	= ::llc::astatic<s1_t, N>; tplN2u	using asti16	= ::llc::astatic<s1_t, N>; tplN2u	using astatici16	= ::llc::asti16	<N>;
	tplN2u	using asts2_t	= ::llc::astatic<s2_t, N>; tplN2u	using asti32	= ::llc::astatic<s2_t, N>; tplN2u	using astatici32	= ::llc::asti32	<N>;
	tplN2u	using asts3_t	= ::llc::astatic<s3_t, N>; tplN2u	using asti64	= ::llc::astatic<s3_t, N>; tplN2u	using astatici64	= ::llc::asti64	<N>;
	tplN2u	using astf2_t	= ::llc::astatic<f2_t, N>; tplN2u	using astf32	= ::llc::astatic<f2_t, N>; tplN2u	using astaticf32	= ::llc::astf32	<N>;
	tplN2u	using astf3_t	= ::llc::astatic<f3_t, N>; tplN2u	using astf64	= ::llc::astatic<f3_t, N>; tplN2u	using astaticf64	= ::llc::astf64	<N>;

	tplN2u	using astvcuc 	= ::llc::astatic<::llc::vcuc 	, N>; tplN2u	using astaticvcuc 	= ::llc::astvcuc <N>;
	tplN2u	using astvcc	= ::llc::astatic<::llc::vcc		, N>; tplN2u	using astaticvcc	= ::llc::astvcc  <N>;
	tplN2u	using astvcu8 	= ::llc::astatic<::llc::vcu0_t 	, N>; tplN2u	using astaticvcu8 	= ::llc::astvcu8 <N>;
	tplN2u	using astvcu16	= ::llc::astatic<::llc::vcu16	, N>; tplN2u	using astaticvcu16	= ::llc::astvcu16<N>;
	tplN2u	using astvcu32	= ::llc::astatic<::llc::vcu32	, N>; tplN2u	using astaticvcu32	= ::llc::astvcu32<N>;
	tplN2u	using astvcu64	= ::llc::astatic<::llc::vcu64	, N>; tplN2u	using astaticvcu64	= ::llc::astvcu64<N>;
	tplN2u	using astvci8 	= ::llc::astatic<::llc::vcs0_t 	, N>; tplN2u	using astaticvci8 	= ::llc::astvci8 <N>;
	tplN2u	using astvci16	= ::llc::astatic<::llc::vci16	, N>; tplN2u	using astaticvci16	= ::llc::astvci16<N>;
	tplN2u	using astvci32	= ::llc::astatic<::llc::vci32	, N>; tplN2u	using astaticvci32	= ::llc::astvci32<N>;
	tplN2u	using astvci64	= ::llc::astatic<::llc::vci64	, N>; tplN2u	using astaticvci64	= ::llc::astvci64<N>;
	tplN2u	using astvcf32	= ::llc::astatic<::llc::vcf32	, N>; tplN2u	using astaticvcf32	= ::llc::astvcf32<N>;
	tplN2u	using astvcf64	= ::llc::astatic<::llc::vcf64	, N>; tplN2u	using astaticvcf64	= ::llc::astvcf64<N>;

	tplt <tpnm T, size_t nSize>	stincxp	u2_t	size		(::llc::astatic<T, nSize> /*viewToTest*/)	noexcept	{ return u2_t(nSize);				}
	tplt <tpnm T, size_t nSize>	stincxp	u2_t	byte_count	(::llc::astatic<T, nSize> viewToTest)		noexcept	{ return u2_t(sizeof(T) * nSize);	}

	// Is this really worth it?
	tplN2u	stincxp	u2_t	size(astc	<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	//tplN2u	stincxp	u2_t	size(astuc 	<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(astu8 	<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(astu16	<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(astu32	<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(astu64	<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(asti8 	<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(asti16	<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(asti32	<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(asti64	<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(astf32	<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(astf64	<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }

	tplN2u	stincxp	u2_t	size(astvcc	 <N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	//tplN2u	stincxp	u2_t	size(astvcuc <N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(astvcu8 <N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(astvcu16<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(astvcu32<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(astvcu64<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(astvci8 <N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(astvci16<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(astvci32<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(astvci64<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(astvcf32<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }
	tplN2u	stincxp	u2_t	size(astvcf64<N> /*viewToTest*/)	noexcept	{ return u2_t(N); }

	tplt<tpnm T, size_t _nSize>
	::llc::error_t			find		(const T & element, const ::llc::astatic<const T, _nSize>& target, u2_t offset = 0)	{
		return ::llc::find(element, ::llc::view<const T>{target}, offset);
	}
	stainli llc::astchar< 7>	str			(u1_t arg) { llc::astchar< 7> dest = {}; sprintf_s(dest.Storage, "%u" , arg); return dest; } 
	stainli llc::astchar<12>	str			(u2_t arg) { llc::astchar<12> dest = {}; sprintf_s(dest.Storage, "%" LLC_FMT_U32, arg); return dest; } 
	stainli llc::astchar<22>	str			(u3_t arg) { llc::astchar<22> dest = {}; sprintf_s(dest.Storage, "%" LLC_FMT_U64, arg); return dest; } 
	stainli llc::astchar< 7>	str			(s1_t arg) { llc::astchar< 7> dest = {}; sprintf_s(dest.Storage, "%i", arg); return dest; } 
	stainli llc::astchar<12>	str			(s2_t arg) { llc::astchar<12> dest = {}; sprintf_s(dest.Storage, "%" LLC_FMT_I32, arg); return dest; } 
	stainli llc::astchar<22>	str			(s3_t arg) { llc::astchar<22> dest = {}; sprintf_s(dest.Storage, "%" LLC_FMT_I64, arg); return dest; } 
	stainli llc::astchar<12>	str			(f2_t arg) { llc::astchar<12> dest = {}; sprintf_s(dest.Storage, "%f", arg); return dest; } 
	stainli llc::astchar<22>	str			(f3_t arg) { llc::astchar<22> dest = {}; sprintf_s(dest.Storage, "%f", arg); return dest; } 
	stacxpr	llc::astchar<5 >	str			(u0_t arg) { 
		return (arg >= 100) ?	llc::astchar<5>{digit<2>(arg), digit<1>(arg), digit<0>(arg), 0}
			:  (arg >=  10) ?	llc::astchar<5>{digit<1>(arg), digit<0>(arg), 0}
			:					llc::astchar<5>{digit<0>(arg), 0}
			;
	}
	stacxpr	llc::astchar<5 >	str			(s0_t arg) { 
		return	(arg >=    0) ?	str(u0_t(arg))
			:	(arg <= -100) ?	llc::astchar<5>{'-', digit<2>((int16_t)-arg), digit<1>((int16_t)-arg), digit<0>((int16_t)-arg)}
			:	(arg <=  -10) ?	llc::astchar<5>{'-', digit<1>((int16_t)-arg), digit<0>((int16_t)-arg)}
			:					llc::astchar<5>{'-', digit<0>((int16_t)-arg)}
			;
	}
} // namespace

#endif // LLC_ARRAY_STATIC_H_23627
