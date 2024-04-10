#include "llc_cpow.h"
#include "llc_view.h"

#ifndef LLC_ARRAY_STATIC_H_23627
#define LLC_ARRAY_STATIC_H_23627

namespace llc
{
#pragma pack(push, 1)
	tplt<tpnm _tVal, uint32_t _elementCount>
	struct array_static	{
		stacxpr	const uint32_t	SIZE	= _elementCount;

		typedef	_tVal					T;
		typedef array_static<T, SIZE>	TAStatic;
		typedef	view<const T>			TConstView;
		typedef	view<T>					TView;

		T						Storage	[SIZE]	;

		operator				view<T>			()															{ return {Storage, SIZE}; }
		operator				view<const T>	()										const	noexcept	{ return {Storage, SIZE}; }

		inline	const T&		operator[]		(uint32_t index)						const				{ gthrow_if(index >= SIZE, LLC_FMT_U32_GE_U32, (int32_t)index, (int32_t)SIZE); return Storage[index]; }
		inline	T&				operator[]		(uint32_t index)											{ gthrow_if(index >= SIZE, LLC_FMT_U32_GE_U32, (int32_t)index, (int32_t)SIZE); return Storage[index]; }
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
		inlcxpr	uint32_t		byte_count		()										const	noexcept	{ return uint32_t(SIZE * sizeof(T));	}
		inlcxpr	uint32_t		bit_count		()										const	noexcept	{ return byte_count() * 8U;	}

		inline	view<uint8_t>	u8				()												noexcept	{ return {(uint8_t*)Storage, byte_count()};		}
		inlcxpr	view<cuint8_t>	u8				()										const	noexcept	{ return {(const uint8_t*)Storage, byte_count()};	}
		inlcxpr	view<cuint8_t>	cu8				()										const	noexcept	{ return {(const uint8_t*)Storage, byte_count()};	}
		inline	view<char>		c				()												noexcept	{ return {(char*)Storage, byte_count()};			}
		inlcxpr	view<cchar_t>	cc				()										const	noexcept	{ return {(const char*)Storage, byte_count()};		}

		inlcxpr	const uint32_t&	size			()										const	noexcept	{ return SIZE; }

		inline	T*				begin			()												noexcept	{ return Storage;			}
		inline	T*				end				()												noexcept	{ return Storage + SIZE;	}
		inlcxpr	const T*		begin			()										const	noexcept	{ return Storage;			}
		inlcxpr	const T*		end				()										const	noexcept	{ return Storage + SIZE;	}

		::llc::error_t			slice			(TView & out, uint32_t offset, uint32_t count = (uint32_t)-1)				{
			ree_if(offset > SIZE, LLC_FMT_U32_GT_U32, offset, (uint32_t)SIZE);
			const uint32_t				newSize			= SIZE - offset;
			if(count != (uint32_t)-1)
				ree_if(count > newSize, LLC_FMT_U32_GT_U32, count, (uint32_t)newSize);
			out						= {&Storage[offset], ::llc::min(newSize, count)};
			return out.size();
		}
		::llc::error_t			slice			(TConstView & out, uint32_t offset, uint32_t count = (uint32_t)-1)	const	{
			ree_if(offset > SIZE, LLC_FMT_U32_GT_U32, offset, (uint32_t)SIZE);
			const uint32_t				newSize			= SIZE - offset;
			if(count != (uint32_t)-1)
				ree_if(count > newSize, LLC_FMT_U32_GT_U32, count, (uint32_t)newSize);
			out						= {&Storage[offset], ::llc::min(newSize, count)};
			return out.size();
		}
	};
#pragma pack(pop)

	tplt<tpnm T, uint32_t _elementCount>
	using astatic	= ::llc::array_static<T, _elementCount>;

	tplt<uint32_t _count>	using astvcs	= ::llc::astatic<::llc::vcs	, _count>; tplt<uint32_t _count>	using astaticvcs	= ::llc::astvcs	<_count>;
	tplt<uint32_t _count>	using astvs		= ::llc::astatic<::llc::vs	, _count>; tplt<uint32_t _count>	using astaticvs		= ::llc::astvs	<_count>;

	tplt<uint32_t _count>	using astc		= ::llc::astatic<char     , _count>; tplt<uint32_t _count>	using astaticc		= ::llc::astc	<_count>; tplt<uint32_t _count>	using astchar	= ::llc::astatic<char    , _count>;
	tplt<uint32_t _count>	using astuc 	= ::llc::astatic<uchar_t  , _count>; tplt<uint32_t _count>	using astaticuc 	= ::llc::astuc 	<_count>; tplt<uint32_t _count>	using astuchar	= ::llc::astatic<uchar_t , _count>;
	tplt<uint32_t _count>	using astu8 	= ::llc::astatic<uint8_t  , _count>; tplt<uint32_t _count>	using astaticu8 	= ::llc::astu8 	<_count>;
	tplt<uint32_t _count>	using astu16	= ::llc::astatic<uint16_t , _count>; tplt<uint32_t _count>	using astaticu16	= ::llc::astu16	<_count>;
	tplt<uint32_t _count>	using astu32	= ::llc::astatic<uint32_t , _count>; tplt<uint32_t _count>	using astaticu32	= ::llc::astu32	<_count>;
	tplt<uint32_t _count>	using astu64	= ::llc::astatic<uint64_t , _count>; tplt<uint32_t _count>	using astaticu64	= ::llc::astu64	<_count>;
	tplt<uint32_t _count>	using asti8 	= ::llc::astatic<int8_t   , _count>; tplt<uint32_t _count>	using astatici8 	= ::llc::asti8 	<_count>;
	tplt<uint32_t _count>	using asti16	= ::llc::astatic<int16_t  , _count>; tplt<uint32_t _count>	using astatici16	= ::llc::asti16	<_count>;
	tplt<uint32_t _count>	using asti32	= ::llc::astatic<int32_t  , _count>; tplt<uint32_t _count>	using astatici32	= ::llc::asti32	<_count>;
	tplt<uint32_t _count>	using asti64	= ::llc::astatic<int64_t  , _count>; tplt<uint32_t _count>	using astatici64	= ::llc::asti64	<_count>;
	tplt<uint32_t _count>	using astf32	= ::llc::astatic<float32_t, _count>; tplt<uint32_t _count>	using astaticf32	= ::llc::astf32	<_count>;
	tplt<uint32_t _count>	using astf64	= ::llc::astatic<float64_t, _count>; tplt<uint32_t _count>	using astaticf64	= ::llc::astf64	<_count>;

	tplt<uint32_t _count>	using astvcc	= ::llc::astatic<::llc::vcc		, _count>; tplt<uint32_t _count>	using astaticvcc	= ::llc::astvcc  <_count>;
	tplt<uint32_t _count>	using astvcuc 	= ::llc::astatic<::llc::vcuc 	, _count>; tplt<uint32_t _count>	using astaticvcuc 	= ::llc::astvcuc <_count>;
	tplt<uint32_t _count>	using astvcu8 	= ::llc::astatic<::llc::vcu8 	, _count>; tplt<uint32_t _count>	using astaticvcu8 	= ::llc::astvcu8 <_count>;
	tplt<uint32_t _count>	using astvcu16	= ::llc::astatic<::llc::vcu16	, _count>; tplt<uint32_t _count>	using astaticvcu16	= ::llc::astvcu16<_count>;
	tplt<uint32_t _count>	using astvcu32	= ::llc::astatic<::llc::vcu32	, _count>; tplt<uint32_t _count>	using astaticvcu32	= ::llc::astvcu32<_count>;
	tplt<uint32_t _count>	using astvcu64	= ::llc::astatic<::llc::vcu64	, _count>; tplt<uint32_t _count>	using astaticvcu64	= ::llc::astvcu64<_count>;
	tplt<uint32_t _count>	using astvci8 	= ::llc::astatic<::llc::vci8 	, _count>; tplt<uint32_t _count>	using astaticvci8 	= ::llc::astvci8 <_count>;
	tplt<uint32_t _count>	using astvci16	= ::llc::astatic<::llc::vci16	, _count>; tplt<uint32_t _count>	using astaticvci16	= ::llc::astvci16<_count>;
	tplt<uint32_t _count>	using astvci32	= ::llc::astatic<::llc::vci32	, _count>; tplt<uint32_t _count>	using astaticvci32	= ::llc::astvci32<_count>;
	tplt<uint32_t _count>	using astvci64	= ::llc::astatic<::llc::vci64	, _count>; tplt<uint32_t _count>	using astaticvci64	= ::llc::astvci64<_count>;
	tplt<uint32_t _count>	using astvcf32	= ::llc::astatic<::llc::vcf32	, _count>; tplt<uint32_t _count>	using astaticvcf32	= ::llc::astvcf32<_count>;
	tplt<uint32_t _count>	using astvcf64	= ::llc::astatic<::llc::vcf64	, _count>; tplt<uint32_t _count>	using astaticvcf64	= ::llc::astvcf64<_count>;

	tplt <tpnm T, size_t nSize>	stincxp	uint32_t	size		(::llc::astatic<T, nSize> /*viewToTest*/)	noexcept	{ return uint32_t(nSize);				}
	tplt <tpnm T, size_t nSize>	stincxp	uint32_t	byte_count	(::llc::astatic<T, nSize> viewToTest)		noexcept	{ return uint32_t(sizeof(T) * nSize);	}

	// Is this really worth it?
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astc	<_elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	//tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astuc 	<_elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astu8 	<_elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astu16	<_elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astu32	<_elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astu64	<_elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(asti8 	<_elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(asti16	<_elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(asti32	<_elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(asti64	<_elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astf32	<_elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astf64	<_elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }

	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astvcc	 < _elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	//tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astvcuc < _elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astvcu8 < _elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astvcu16< _elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astvcu32< _elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astvcu64< _elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astvci8 < _elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astvci16< _elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astvci32< _elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astvci64< _elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astvcf32< _elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }
	tplt<uint32_t _elementCount>	stincxp	uint32_t	size(astvcf64< _elementCount> /*viewToTest*/)	noexcept	{ return uint32_t(_elementCount); }

	tplt<tpnm T, size_t _nSize>
	::llc::error_t			find		(const T & element, const ::llc::astatic<const T, _nSize>& target, uint32_t offset = 0)	{
		return ::llc::find(element, ::llc::view<const T>{target}, offset);
	}


	stainli llc::astchar<12>	str			(float32_t	arg) { llc::astchar<12> dest = {}; sprintf_s(dest.Storage, "%f", arg); return dest; } 
	stainli llc::astchar<22>	str			(float64_t	arg) { llc::astchar<22> dest = {}; sprintf_s(dest.Storage, "%f", arg); return dest; } 
	stainli llc::astchar<7>		str			(int16_t	arg) { llc::astchar< 7> dest = {}; sprintf_s(dest.Storage, "%i", arg); return dest; } 
	stainli llc::astchar<7>		str			(uint16_t	arg) { llc::astchar< 7> dest = {}; sprintf_s(dest.Storage, "%u", arg); return dest; } 
	stainli llc::astchar<12>	str			(int32_t	arg) { llc::astchar<12> dest = {}; sprintf_s(dest.Storage, "%" LLC_FMT_I32, arg); return dest; } 
	stainli llc::astchar<22>	str			(int64_t	arg) { llc::astchar<22> dest = {}; sprintf_s(dest.Storage, "%" LLC_FMT_I64, arg); return dest; } 
	stainli llc::astchar<12>	str			(uint32_t	arg) { llc::astchar<12> dest = {}; sprintf_s(dest.Storage, "%" LLC_FMT_U32, arg); return dest; } 
	stainli llc::astchar<22>	str			(uint64_t	arg) { llc::astchar<22> dest = {}; sprintf_s(dest.Storage, "%" LLC_FMT_U64, arg); return dest; } 

	stacxpr	llc::astchar<5 >	str			(uint8_t	arg) { 
		return (arg >= 100) ?	llc::astchar<5>{digit<2>(arg), digit<1>(arg), digit<0>(arg), 0}
			:  (arg >=  10) ?	llc::astchar<5>{digit<1>(arg), digit<0>(arg), 0}
			:					llc::astchar<5>{digit<0>(arg), 0}
			;
	}
	stacxpr	llc::astchar<5 >	str			(int8_t		arg) { 
		return	(arg >=    0) ?	str(uint8_t(arg))
			:	(arg <= -100) ?	llc::astchar<5>{'-', digit<2>((int16_t)-arg), digit<1>((int16_t)-arg), digit<0>((int16_t)-arg)}
			:	(arg <=  -10) ?	llc::astchar<5>{'-', digit<1>((int16_t)-arg), digit<0>((int16_t)-arg)}
			:					llc::astchar<5>{'-', digit<0>((int16_t)-arg)}
			;
	}
} // namespace

#endif // LLC_ARRAY_STATIC_H_23627
