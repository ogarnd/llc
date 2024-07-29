#include "llc_log.h"

#include "llc_functional.h"

#if defined(LLC_ATMEL)
#	include <string.h>
#	ifdef max
#		undef max
#	endif
#	ifdef min
#		undef min
#	endif
#else
#	include <cstring>
#endif

#ifndef LLC_ARRAY_VIEW_H_23627
#define LLC_ARRAY_VIEW_H_23627

namespace llc
{
#pragma pack(push, 1)
	tplt <tpnm _tVal>
	class view {
	protected:
		// Properties / Member Variables
		_tVal					* Data			= 0;
		uint32_t				Count			= 0;
	public:
		typedef	_tVal			T;
		typedef	view<const T>	TConstView;
		typedef	view<T>			TView;

		// Constructors
		inlcxpr					view			()									noexcept	= default;
		inlcxpr					view			(const view<T> & other)				noexcept	= default;

		tplt<size_t Len>
		inlcxpr					view			(T (&elements)[Len])				noexcept	: Data(elements), Count(Len)										{}

		tplt<size_t Len>
		inlcxpr					view			(uint32_t elementCount, T (&elements)[Len])		: Data(elements), Count(::llc::min((u2_t)Len, elementCount))	{}
		inline					view			(T * elements, uint32_t elementCount)			: Data(elements), Count(elementCount)								{
			gthrow_if(0 == elements && 0 != elementCount, "%" LLC_FMT_U32 " -> 0.", elementCount);	// Crash if we received invalid parameters in order to prevent further malfunctioning.
		}

		tplt <size_t Len>
		inline					view			(T (&elements)[Len], uint32_t elementCount)		: Data(elements), Count(::llc::min((u2_t)Len, elementCount))	{
			gthrow_if(elementCount > Len, LLC_FMT_U32_GT_U32, elementCount, (u2_t)Len);
		}

		// Operators
		inlcxpr	operator		view<const T>	()							const	noexcept	{ return {Data, Count}; }

		T&						operator[]		(uint32_t index)								{
			static T dymmy = {}; 
			rves_if(dymmy, 0 == Data);
			gthrow_if(index >= Count, LLC_FMT_U32_GE_U32, index, Count);
			return Data[index];
		}
		const T&				operator[]		(uint32_t index)			const				{
			gsthrow_if(0 == Data);
			gthrow_if(index >= Count, LLC_FMT_U32_GE_U32, index, Count);
			return Data[index];
		}
		bool					operator!=		(const TConstView & other)	const				{ return  !operator==(other); } // I had to add this for the android build not supporting C++20.
		bool					operator==		(const TConstView & other)	const				{
			if(this->size() != other.size())
				return false;
			if(this->begin() == other.begin())
				return true;
			return ::llc::equal(other.begin(), this->begin(), this->size());
		}

		// Methods
		inlcxpr	uint32_t		byte_count		()							const	noexcept	{ return uint32_t(Count * sizeof(T));	}
		inlcxpr	uint64_t		bit_count		()							const	noexcept	{ return byte_count() * 8ULL;			}

		inline	view<sc_t>		c				()									noexcept	{ return {(sc_t			*)Data, byte_count()}; }
		inline	view<i0u_t>		u8				()									noexcept	{ return {(i0u_t		*)Data, byte_count()}; }
		inlcxpr	view<sc_c>		cc				()							const	noexcept	{ return {(const sc_t	*)Data, byte_count()}; }
		inlcxpr	view<i0u_c>		u8				()							const	noexcept	{ return {(i0u_c		*)Data, byte_count()}; }
		inlcxpr	view<i0u_c>		cu8				()							const	noexcept	{ return {(i0u_c		*)Data, byte_count()}; }

		inlcxpr	const uint32_t&	size			()							const	noexcept	{ return Count;				}
		inlcxpr	const T*		begin			()							const	noexcept	{ return Data;				}
		inlcxpr	const T*		end				()							const	noexcept	{ return begin() + Count;	}
		inline	T*				begin			()									noexcept	{ return Data;				}
		inline	T*				end				()									noexcept	{ return begin() + Count;	}
		::llc::error_t			slice			(TView & out, uint32_t offset, uint32_t count = (u2_t)-1)				{
			reterr_gerror_if(offset > Count, LLC_FMT_U32_GT_U32, offset, (u2_t)Count);
			const uint32_t				newSize			= Count - offset;
			if(count != (u2_t)-1)
				ree_if(count > newSize, LLC_FMT_U32_GT_U32, count, (u2_t)newSize);
			out						= {&Data[offset], ::llc::min(newSize, count)};
			return out.size();
		}
		::llc::error_t			slice			(TConstView & out, uint32_t offset, uint32_t count = (u2_t)-1)	const	{
			ree_if(offset > Count, LLC_FMT_U32_GT_U32, offset, (u2_t)Count);
			const uint32_t				newSize			= Count - offset;
			if(count != (u2_t)-1)
				ree_if(count > newSize, LLC_FMT_U32_GT_U32, count, (u2_t)newSize);
			out						= {&Data[offset], ::llc::min(newSize, count)};
			return out.size();
		}
		::llc::error_t			revert			()																			{
			const uint32_t				lastElement		= Count - 1;
			for(uint32_t i = 0, swapCount = Count / 2; i < swapCount; ++i) {
				T							old				= Data[i];
				Data[i]					= Data[lastElement - i];
				Data[lastElement - i]	= old;
			}
			return 0;
		}

		inline	::llc::error_t	fill			(const T & value, uint32_t offset = 0, uint32_t stop = 0xFFFFFFFFU)		{ for(; offset < ::llc::min(Count, stop); ++offset) Data[offset] = value; return Count; }


		::llc::error_t			for_each		(const ::llc::TFuncForEach       <T> & funcForEach, uint32_t offset = 0)			{ for(; offset < Count; ++offset) funcForEach(Data[offset]); return offset; }
		::llc::error_t			for_each		(const ::llc::TFuncForEachConst  <T> & funcForEach, uint32_t offset = 0)	const	{ for(; offset < Count; ++offset) funcForEach(Data[offset]); return offset; }
		::llc::error_t			enumerate		(const ::llc::TFuncEnumerate     <T> & funcForEach, uint32_t offset = 0)			{ for(; offset < Count; ++offset) funcForEach(offset, Data[offset]); return offset; }
		::llc::error_t			enumerate		(const ::llc::TFuncEnumerateConst<T> & funcForEach, uint32_t offset = 0)	const	{ for(; offset < Count; ++offset) funcForEach(offset, Data[offset]); return offset; }
		//
		::llc::error_t			for_each		(const ::llc::TFuncForEach       <T> & funcForEach, uint32_t offset, uint32_t stop)			{ for(stop = ::llc::min(stop, Count); offset < stop; ++offset) funcForEach(Data[offset]); return offset; }
		::llc::error_t			for_each		(const ::llc::TFuncForEachConst  <T> & funcForEach, uint32_t offset, uint32_t stop)	const	{ for(stop = ::llc::min(stop, Count); offset < stop; ++offset) funcForEach(Data[offset]); return offset; }
		::llc::error_t			enumerate		(const ::llc::TFuncEnumerate     <T> & funcForEach, uint32_t offset, uint32_t stop)			{ for(stop = ::llc::min(stop, Count); offset < stop; ++offset) funcForEach(offset, Data[offset]); return offset; }
		::llc::error_t			enumerate		(const ::llc::TFuncEnumerateConst<T> & funcForEach, uint32_t offset, uint32_t stop)	const	{ for(stop = ::llc::min(stop, Count); offset < stop; ++offset) funcForEach(offset, Data[offset]); return offset; }

		::llc::error_t			find			(const FBool<T&>		& funcForEach, uint32_t offset = 0)			{ for(; offset < Count; ++offset) if(funcForEach(Data[offset])) return (::llc::error_t)offset; return -1; }
		::llc::error_t			find			(const FBool<const T&>	& funcForEach, uint32_t offset = 0)	const	{ for(; offset < Count; ++offset) if(funcForEach(Data[offset])) return (::llc::error_t)offset; return -1; }
		::llc::error_t			find			(const T & value, uint32_t offset = 0)						const	{ for(; offset < Count; ++offset) if(Data[offset] == value) return (::llc::error_t)offset; return -1; }

		tplt<tpnm _tMax> ::llc::error_t	max	(_tMax & maxFound, const FTransform<_tMax, const T &> & funcComparand, uint32_t offset = 0)	const	{ s2_t iMax = 0; for(; offset < Count; ++offset) { _tMax value = funcComparand(Data[offset]); if(value > maxFound) { iMax = offset; maxFound = value; } } return iMax; }
		tplt<tpnm _tMax> ::llc::error_t	min	(_tMax & minFound, const FTransform<_tMax, const T &> & funcComparand, uint32_t offset = 0)	const	{ s2_t iMin = 0; for(; offset < Count; ++offset) { _tMax value = funcComparand(Data[offset]); if(value < minFound) { iMin = offset; minFound = value; } } return iMin; }
		tplt<tpnm _tMax> ::llc::error_t	max	(const FTransform<_tMax, const T &> & funcComparand, uint32_t offset = 0)					const	{ _tMax maxFound; return max(maxFound, funcComparand, offset); }
		tplt<tpnm _tMax> ::llc::error_t	min	(const FTransform<_tMax, const T &> & funcComparand, uint32_t offset = 0)					const	{ _tMax minFound; return min(minFound, funcComparand, offset); }
	}; // view<>

	tplt<tpnm T>	using	view_array	= ::llc::view<T>;
	tplt<tpnm T>	using	view1d		= ::llc::view<T>;
	tplt<tpnm T>	using	v1			= ::llc::view<T>;

	tplt<tpnm T>	ndstinx	uint32_t	size		(const ::llc::view<T> & viewToTest)	noexcept	{ return viewToTest.size();			}
	tplt<tpnm T>	ndstinx	uint32_t	byte_count	(const ::llc::view<T> & viewToTest)	noexcept	{ return viewToTest.byte_count();	}

#pragma pack(pop)

	typedef	::llc::view<uc_t>	vuc_t, vuc, vuchar;
	typedef	::llc::view<sc_t>	vsc_t, vc, vchar;
	typedef	::llc::view<u0_t>	vu0_t, vu8;
	typedef	::llc::view<u1_t>	vu1_t, vu16;
	typedef	::llc::view<u2_t>	vu2_t, vu32;
	typedef	::llc::view<u3_t>	vu3_t, vu64;
	typedef	::llc::view<s0_t>	vs0_t, vi8;
	typedef	::llc::view<s1_t>	vs1_t, vi16;
	typedef	::llc::view<s2_t>	vs2_t, vi32;
	typedef	::llc::view<s3_t>	vs3_t, vi64;
	typedef	::llc::view<f2_t>	vf2_t, vf32;
	typedef	::llc::view<f3_t>	vf3_t, vf64;

	typedef	::llc::view<uc_c>	vcuc_t, vcuc, vcuchar;
	typedef	::llc::view<sc_c>	vcsc_t, vcc, vcchar;
	typedef	::llc::view<u0_c>	vcu0_t, vcu8;
	typedef	::llc::view<u1_c>	vcu1_t, vcu16;
	typedef	::llc::view<u2_c>	vcu2_t, vcu32;
	typedef	::llc::view<u3_c>	vcu3_t, vcu64;
	typedef	::llc::view<s0_c>	vcs0_t, vci8;
	typedef	::llc::view<s1_c>	vcs1_t, vci16;
	typedef	::llc::view<s2_c>	vcs2_t, vci32;
	typedef	::llc::view<s3_c>	vcs3_t, vci64;
	typedef	::llc::view<f2_c>	vcf2_t, vcf32;
	typedef	::llc::view<f3_c>	vcf3_t, vcf64;

	typedef	const vuc_t 		vuc_c;
	typedef	const vsc_t 		vsc_c;
	typedef	const vu0_t 		vu0_c;
	typedef	const vu1_t 		vu1_c;
	typedef	const vu2_t 		vu2_c;
	typedef	const vu3_t 		vu3_c;
	typedef	const vs0_t 		vs0_c;
	typedef	const vs1_t 		vs1_c;
	typedef	const vs2_t 		vs2_c;
	typedef	const vs3_t 		vs3_c;
	typedef	const vf2_t 		vf2_c;
	typedef	const vf3_t 		vf3_c;
	typedef	const vcuc_t 		vcuc_c;
	typedef	const vcsc_t 		vcsc_c;
	typedef	const vcu0_t 		vcu0_c;
	typedef	const vcu1_t 		vcu1_c;
	typedef	const vcu2_t 		vcu2_c;
	typedef	const vcu3_t 		vcu3_c;
	typedef	const vcs0_t 		vcs0_c;
	typedef	const vcs1_t 		vcs1_c;
	typedef	const vcs2_t 		vcs2_c;
	typedef	const vcs3_t 		vcs3_c;
	typedef	const vcf2_t 		vcf2_c;
	typedef	const vcf3_t 		vcf3_c;

// Use this to initialize a constexpr vcs from a string literal
#define LLC_CXS(constexpr_string_literal) ::llc::vcsc_t{::llc::s2_t(sizeof(constexpr_string_literal) - 1), constexpr_string_literal}

	typedef	::llc::view<vuc_t>	vvuc_t;
	typedef	::llc::view<vsc_t>	vvsc_t;
	typedef	::llc::view<vu0_t>	vvu0_t;
	typedef	::llc::view<vu1_t>	vvu1_t;
	typedef	::llc::view<vu2_t>	vvu2_t;
	typedef	::llc::view<vu3_t>	vvu3_t;
	typedef	::llc::view<vs0_t>	vvs0_t;
	typedef	::llc::view<vs1_t>	vvs1_t;
	typedef	::llc::view<vs2_t>	vvs2_t;
	typedef	::llc::view<vs3_t>	vvs3_t;
	typedef	::llc::view<vf2_t>	vvf2_t;
	typedef	::llc::view<vf3_t>	vvf3_t;

	typedef	::llc::view<vuc_c>	vcvuc_t;
	typedef	::llc::view<vsc_c>	vcvsc_t;
	typedef	::llc::view<vu0_c>	vcvu0_t;
	typedef	::llc::view<vu1_c>	vcvu1_t;
	typedef	::llc::view<vu2_c>	vcvu2_t;
	typedef	::llc::view<vu3_c>	vcvu3_t;
	typedef	::llc::view<vs0_c>	vcvs0_t;
	typedef	::llc::view<vs1_c>	vcvs1_t;
	typedef	::llc::view<vs2_c>	vcvs2_t;
	typedef	::llc::view<vs3_c>	vcvs3_t;
	typedef	::llc::view<vf2_c>	vcvf2_t;
	typedef	::llc::view<vf3_c>	vcvf3_t;

	typedef	const vvuc_t	vvuc_c;
	typedef	const vvsc_t	vvsc_c;
	typedef	const vvu0_t	vvu0_c;
	typedef	const vvu1_t	vvu1_c;
	typedef	const vvu2_t	vvu2_c;
	typedef	const vvu3_t	vvu3_c;
	typedef	const vvs0_t	vvs0_c;
	typedef	const vvs1_t	vvs1_c;
	typedef	const vvs2_t	vvs2_c;
	typedef	const vvs3_t	vvs3_c;
	typedef	const vvf2_t	vvf2_c;
	typedef	const vvf3_t	vvf3_c;
	typedef	const vcvuc_t	vcvuc_c;
	typedef	const vcvsc_t	vcvsc_c;
	typedef	const vcvu0_t	vcvu0_c;
	typedef	const vcvu1_t	vcvu1_c;
	typedef	const vcvu2_t	vcvu2_c;
	typedef	const vcvu3_t	vcvu3_c;
	typedef	const vcvs0_t	vcvs0_c;
	typedef	const vcvs1_t	vcvs1_c;
	typedef	const vcvs2_t	vcvs2_c;
	typedef	const vcvs3_t	vcvs3_c;
	typedef	const vcvf2_t	vcvf2_c;
	typedef	const vcvf3_t	vcvf3_c;

	stacxpr	::llc::vcc	VCC_NULL		= {4, "null"};
	stacxpr	::llc::vcc	VCC_TRUE		= {4, "true"};
	stacxpr	::llc::vcc	VCC_FALSE		= {5, "false"};

	ndstinx	::llc::vcc	bool2vcc		(bool b)		{ return b ? ::llc::VCC_TRUE : ::llc::VCC_FALSE; }
	ndstinx	const sc_t*	bool2char		(bool b)		{ return b ? ::llc::VCC_TRUE.begin() : ::llc::VCC_FALSE.begin(); }
	ndstinx	uint8_t		bool2u8			(bool b)		{ return b ? 1 : 0; }
	ndstinx	uint8_t		bool2i8			(bool b)		{ return b ? 1 : 0; }
	stainli	const sc_t*	bool2char		(bool b, ::llc::vcc & output)	{ return (output = b ? ::llc::VCC_TRUE : ::llc::VCC_FALSE).begin(); }
	stainli	bool		vcc2bool		(::llc::vcc b)	{ return b.size() && b != VCC_FALSE; }

	struct view_string : view<sc_t> {
		inlcxpr				view_string				()												= default;
		inlcxpr				view_string				(const view<sc_t> & other)			noexcept	: view(other)				{}
		tplt<u2_t Len>		view_string				(sc_t (&storage)[Len])				noexcept	: view(storage)			{ Count = (u2_t)strnlen(storage, (u2_t)Len);							}
		tplt<u2_t Len>		view_string				(sc_t (&storage)[Len], u2_t length)				: view(storage, length)	{ if(length == (u2_t)-1) Count = (u2_t)strnlen(storage, (u2_t)Len);	}
							view_string				(sc_t * storage, u2_t length)					: view(storage, length)	{ Count = (length == (u2_t)-1) ? (u2_t)strlen(storage) : length;		}

		inlcxpr	sc_c*	begin					()	const	noexcept	{ return (Data && Count) ? Data : ""; }
		inlcxpr	sc_c*	end						()	const	noexcept	{ return (Data && Count) ? Data + Count : begin(); }
		ndinlne operator	const sc_t* 			()  const  	noexcept	{ return begin(); }
	};
	struct view_const_string : view<const sc_t> {
		inlcxpr				view_const_string		()												: view(0, "") 							{}
		inlcxpr				view_const_string		(const view<const sc_t> & other)	noexcept	: view(other)							{}
		tplt<u2_t Len>		view_const_string		(const sc_t (&storage)[Len])		noexcept	: view(storage)							{ Count = (u2_t)strnlen(storage, (u2_t)Len);							}
		tplt<u2_t Len>		view_const_string		(const sc_t (&storage)[Len], u2_t length)		: view(storage, length)					{ if(length == (u2_t)-1) Count = (u2_t)strnlen(storage, (u2_t)Len);	}
							view_const_string		(const sc_t * storage, u2_t length)				: view(storage ? storage : "", length)	{ if(length == (u2_t)-1) Count = (u2_t)strlen(begin());					}

		inlcxpr	sc_c*	begin					()	const	noexcept	{ return (Data && Count) ? Data : ""; }
		inlcxpr	sc_c*	end						()	const	noexcept	{ return (Data && Count) ? Data + Count : begin(); }
		ndinlne operator	const sc_t* 			()  const  	noexcept	{ return begin(); }
	};

	typedef	::llc::view_string					vs;
	typedef	::llc::view_const_string			vcs;

	stainli llc::vcs		str					(const llc::vcs & arg)	{ return arg; } 
	stainli llc::vcs		str					(const llc::vs & arg)	{ return arg.cc(); } 
	// 
	tpltT	ndstinx	::llc::vcs	get_type_namev					()							noexcept	{ return LLC_CXS("unknown"); }
	tpltT	ndstinx	const sc_t*	get_type_namep					()							noexcept	{ return get_type_namev<T>().begin(); }
#define GDEFINE_TYPE_NAME_STR(typeIdentifier)																													\
			ndstinx	::llc::vcs	get_type_namev					(typeIdentifier &)	noexcept	{ return LLC_CXS(#typeIdentifier); }					\
	tplt<>	ndincxp	::llc::vcs	get_type_namev<typeIdentifier>	()					noexcept	{ return LLC_CXS(#typeIdentifier); }					\
			ndstinx	const sc_t*	get_type_namep					(typeIdentifier &)	noexcept	{ return get_type_namev<typeIdentifier>().begin(); }	\
	tplt<>	ndincxp	const sc_t*	get_type_namep<typeIdentifier>	()					noexcept	{ return get_type_namev<typeIdentifier>().begin(); }	
	//GDEFINE_TYPE_NAME_STR(uc_t);
	GDEFINE_TYPE_NAME_STR(sc_t);
	GDEFINE_TYPE_NAME_STR(u0_t);
	GDEFINE_TYPE_NAME_STR(u1_t);
	GDEFINE_TYPE_NAME_STR(u2_t);
	GDEFINE_TYPE_NAME_STR(u3_t);
	GDEFINE_TYPE_NAME_STR(s0_t);
	GDEFINE_TYPE_NAME_STR(s1_t);
	GDEFINE_TYPE_NAME_STR(s2_t);
	GDEFINE_TYPE_NAME_STR(s3_t);
	GDEFINE_TYPE_NAME_STR(f2_t);
	GDEFINE_TYPE_NAME_STR(f3_t);
	//GDEFINE_TYPE_NAME_STR(uc_c);
	GDEFINE_TYPE_NAME_STR(sc_c);
	GDEFINE_TYPE_NAME_STR(u0_c);
	GDEFINE_TYPE_NAME_STR(u1_c);
	GDEFINE_TYPE_NAME_STR(u2_c);
	GDEFINE_TYPE_NAME_STR(u3_c);
	GDEFINE_TYPE_NAME_STR(s0_c);
	GDEFINE_TYPE_NAME_STR(s1_c);
	GDEFINE_TYPE_NAME_STR(s2_c);
	GDEFINE_TYPE_NAME_STR(s3_c);
	GDEFINE_TYPE_NAME_STR(f2_c);
	GDEFINE_TYPE_NAME_STR(f3_c);
	// 
	typedef	::llc::view<::llc::vs			>	vvs;
	typedef	::llc::view<::llc::vcs			>	vvcs;
	typedef	::llc::view<const ::llc::vs		>	vcvs;
	typedef	::llc::view<const ::llc::vcs	>	vcvcs;

	stacxpr	::llc::vcc		TRIM_CHARACTERS		= " \t\b\n\r";

	::llc::error_t			rtrim				(::llc::vcc & trimmed, const ::llc::vcc & original, const ::llc::vcc & characters = ::llc::TRIM_CHARACTERS);
	::llc::error_t			ltrim				(::llc::vcc & trimmed, const ::llc::vcc & original, const ::llc::vcc & characters = ::llc::TRIM_CHARACTERS);
	::llc::error_t			trim				(::llc::vcc & trimmed, const ::llc::vcc & original, const ::llc::vcc & characters = ::llc::TRIM_CHARACTERS);
	stainli	::llc::error_t	rtrim				(::llc::vcc & trimmed) 	{ return rtrim(trimmed, trimmed); }
	stainli	::llc::error_t	ltrim				(::llc::vcc & trimmed) 	{ return ltrim(trimmed, trimmed); }
	stainli	::llc::error_t	trim				(::llc::vcc & trimmed) 	{ return trim(trimmed, trimmed); }
	
	stainli	::llc::error_t	rtrim				(::llc::vc & trimmed, const ::llc::vc & original, const ::llc::vcc & characters = ::llc::TRIM_CHARACTERS)	{ return rtrim	(*(::llc::vcc*)&trimmed, *(const ::llc::vcc*)&original, characters); }
	stainli	::llc::error_t	ltrim				(::llc::vc & trimmed, const ::llc::vc & original, const ::llc::vcc & characters = ::llc::TRIM_CHARACTERS)	{ return ltrim	(*(::llc::vcc*)&trimmed, *(const ::llc::vcc*)&original, characters); }
	stainli	::llc::error_t	trim				(::llc::vc & trimmed, const ::llc::vc & original, const ::llc::vcc & characters = ::llc::TRIM_CHARACTERS)	{ return trim	(*(::llc::vcc*)&trimmed, *(const ::llc::vcc*)&original, characters); }
	stainli	::llc::error_t	rtrim				(::llc::vc & trimmed) 	{ return rtrim(trimmed, trimmed); }
	stainli	::llc::error_t	ltrim				(::llc::vc & trimmed) 	{ return ltrim(trimmed, trimmed); }
	stainli	::llc::error_t	trim				(::llc::vc & trimmed) 	{ return trim(trimmed, trimmed); }

	tplt <tpnm T>
	::llc::error_t			reverse				(::llc::view<T> elements)													{
		const uint32_t				lastElement			= elements.size() - 1;
		for(uint32_t i = 0, swapCount = elements.size() / 2; i < swapCount; ++i) {
			T							old						= elements[i];
			elements[i]					= elements[lastElement - i];
			elements[lastElement - i]	= old;
		}
		return 0;
	}

	tplt<tpnm T>
	::llc::error_t			find					(const T & valueToFind, const ::llc::view<const T> & target, uint32_t offset = 0)		{
		for(uint32_t iOffset = offset, offsetStop = target.size(); iOffset < offsetStop; ++iOffset)
			if(valueToFind == target[iOffset])
				return (s2_t)iOffset;
		return -1;
	}

	tplt<tpnm T>
	::llc::error_t					rfind					(const T & valueToFind, const ::llc::view<const T> & target, s2_t offset = 0)		{
		for(uint32_t iOffset = target.size() - 1 - offset; iOffset < target.size(); --iOffset)
			if(valueToFind == target[iOffset])
				return iOffset;
		return -1;
	}

	tplt<tpnm T>
	::llc::error_t					find_sequence_obj		(const ::llc::view<T> & sequence, const ::llc::view<T> & target, uint32_t offset = 0)	{
		for(s2_t iOffset = (s2_t)offset, offsetStop = ((s2_t)target.size() - sequence.size()) + 1; iOffset < offsetStop; ++iOffset) {
			bool								equal					= true;
			for(uint32_t iSequenceElement = 0; iSequenceElement < sequence.size(); ++iSequenceElement) {
				if(sequence[iSequenceElement] != target[iOffset + iSequenceElement]) {
					equal							= false;
					break;
				}
			}
			if(equal)
				return iOffset;
		}
		return -1;
	}

	tplt<tpnm T>
	::llc::error_t					rfind_sequence_obj		(const ::llc::view<T> & sequence, const ::llc::view<T> & target, uint32_t offset = 0)	{
		for(s2_t iOffset = (s2_t)(target.size() - sequence.size() - offset); iOffset >= 0; --iOffset) {
			bool								equal					= true;
			for(uint32_t iSequenceElement = 0; iSequenceElement < sequence.size(); ++iSequenceElement) {
				if(sequence[iSequenceElement] != target[iOffset + iSequenceElement]) {
					equal							= false;
					break;
				}
			}
			if(equal)
				return iOffset;
		}
		return -1;
	}

	tplt<tpnm T>
	::llc::error_t					find_sequence_pod		(const ::llc::view<T> & sequence, const ::llc::view<T> & target, uint32_t offset = 0)	{
		for(s2_t iOffset = (s2_t)offset, offsetStop = ((s2_t)target.size() - sequence.size()) + 1; iOffset < offsetStop; ++iOffset)
			if(0 == memcmp(sequence.begin(), &target[iOffset], sequence.size() * sizeof(T)))
				return iOffset;
		return -1;
	}

	tplt<tpnm T>
	::llc::error_t					rfind_sequence_pod		(const ::llc::view<T> & sequence, const ::llc::view<T>& target, uint32_t offset = 0)	{
		for(s2_t iOffset = (s2_t)(target.size() - sequence.size() - offset); iOffset >= 0; --iOffset)
			if(0 == memcmp(sequence.begin(), &target[iOffset], sequence.size() * sizeof(T)))
				return iOffset;
		return -1;
	}

	stainli	::llc::error_t			find_string				(const ::llc::vcs & toFind, const ::llc::vcc & target, uint32_t offset = 0) { return ::llc::find_sequence_pod (toFind, target, offset); }
	stainli	::llc::error_t			rfind_string			(const ::llc::vcs & toFind, const ::llc::vcc & target, uint32_t offset = 0) { return ::llc::rfind_sequence_pod(toFind, target, offset); }

	tplt<tpnm T>
	::llc::error_t					split					(const T & valueToFind, const ::llc::view<T> & original, ::llc::view<T> & left, ::llc::view<T> & right) {
		const ::llc::error_t				iValue					= ::llc::find(valueToFind, original);
		if(0 > iValue) {
			left							= original;
			right							= {};
		}
		else {
			llc_necs(original.slice(left, 0, iValue));
			const uint32_t						offsetRight				= iValue + 1;
			llc_necs(original.slice(right, offsetRight, original.size() - offsetRight));
		}
		return iValue;
	}

	tplt<tpnm T>
	::llc::error_t					splitAt					(const T & valueToFind, const ::llc::view<T> & original, ::llc::view<T> & left, ::llc::view<T> & right) {
		const ::llc::error_t				iValue					= ::llc::find(valueToFind, original);
		if(0 > iValue) { // Read until the end unless fragment is found.
			left							= original;
			right							= {};
		}
		else {
			llc_necs(original.slice(left, 0, (u2_t)iValue));
			llc_necs(original.slice(right, iValue, (u2_t)original.size() - iValue));
		}
		return iValue;
	}

	// Returns the index of the start of the sequence if the latter found.
	tplt<tpnm T>
	::llc::error_t					split					(const ::llc::view<T> & sequenceToFind, const ::llc::view<T> & original, ::llc::view<T> & left, ::llc::view<T> & right) {
		const ::llc::error_t				iValue					= ::llc::find_sequence_pod(sequenceToFind, original);
		if(0 > iValue) {
			left							= original;
			right							= {};
		}
		else {
			llc_necs(original.slice(right, iValue + sequenceToFind.size()));
			llc_necs(original.slice(left, 0, iValue));
		}
		return iValue;
	}

	tplt<tpnm T>
	inline	::llc::error_t			split					(const ::llc::view<T> & sequenceToFind, ::llc::view<T> & inputOrLeft, ::llc::view<T> & right) {
		return ::llc::split(sequenceToFind, inputOrLeft, inputOrLeft, right);
	}

	tplt<tpnm T>
	::llc::error_t					splitAt					(const ::llc::view<T> & sequenceToFind, const ::llc::view<T> & original, ::llc::view<T> & left, ::llc::view<T> & right) {
		const ::llc::error_t				iValue					= ::llc::find_sequence_pod(sequenceToFind, original);
		if(0 > iValue) { // Read until the end unless fragment is found.
			left							= original;
			right							= {};
		}
		else {
			llc_necall(original.slice(left, 0, (u2_t)iValue), "%s", "Invalid slice");
			llc_necall(original.slice(right, iValue, (u2_t)original.size() - iValue), "%s", "Invalid slice");
		}
		return iValue;
	}

	tpltT	err_t		max						(::llc::view<T> input, T ** result) {
		ree_if(0 == input.size(), "%s", "Cannot get reference to max element of an empty array.");
		*result				= &input[0];
		s2_t					iMax					= 0;
		for(uint32_t iElement = 1; iElement < input.size(); ++iElement) {
			const T					& currentElement		= input[iElement];
			if(currentElement > **result) {
				*result					= &currentElement;
				iMax					= iElement;
			}
		}
		return iMax;
	}

	tpltT	err_t		min						(::llc::view<T> input, T ** result) {
		ree_if(0 == input.size(), "%s", "Cannot get reference to min element of an empty array.");
		*result				= &input[0];
		s2_t					iMin					= 0;
		for(uint32_t iElement = 1; iElement < input.size(); ++iElement) {
			const T					& currentElement		= input[iElement];
			if(currentElement < **result) {
				*result				= &currentElement;
				iMin				= iElement;
			}
		}
		return iMin;
	}

	tpltT	T&			max		(::llc::view<T> elements)		{ T * rmax	{}; if_fail_e(::llc::max(elements, &rmax));	return *rmax; }
	tpltT	T&			min		(::llc::view<T> elements)		{ T * rmin	{}; if_fail_e(::llc::min(elements, &rmin));	return *rmin; }
	tpltT	T			sum		(::llc::view<const T> elements)	{ T result	{}; for(T element : elements) result += element; return result; }
	tpltT	stainli	T&	be2le	(T & number)					{ ::llc::reverse<i0u_t>({(i0u_t*)&number, sizeof(T)}); return number; }
} // namespace

#endif // LLC_ARRAY_VIEW_H_23627
