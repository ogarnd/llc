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
	tplt<tpnm _tVal> class view {
	protected:
		// Properties / Member Variables
		_tVal					* Data			= 0;
		u2_t				Count			= 0;
	public:
		typedef	_tVal			T;
		typedef	view<cnst T>	TConstView;
		typedef	view<T>			TView;

		// Constructors
		inlcxpr					view			()									nxpt	= default;
		inlcxpr					view			(cnst view<T> & other)				nxpt	= default;

		tplt<size_t Len>
		inlcxpr					view			(T (&elements)[Len])				nxpt	: Data(elements), Count(Len)										{}

		tplt<size_t Len>
		inlcxpr					view			(u2_t elementCount, T (&elements)[Len])		: Data(elements), Count(::llc::min((u2_t)Len, elementCount))	{}
		inline					view			(T * elements, u2_t elementCount)			: Data(elements), Count(elementCount)								{
			gthrow_if(0 == elements && 0 != elementCount, "%" LLC_FMT_U32 " -> 0.", elementCount);	// Crash if we received invalid parameters in order to prevent further malfunctioning.
		}

		tplt <size_t Len>
		inline					view			(T (&elements)[Len], u2_t elementCount)		: Data(elements), Count(::llc::min((u2_t)Len, elementCount))	{
			gthrow_if(elementCount > Len, LLC_FMT_U32_GT_U32, elementCount, (u2_t)Len);
		}

		// Operators
		inlcxpr	operator		view<cnst T>	()							cnstnxpt	{ return {Data, Count}; }

		T&						operator[]		(u2_t index)								{
			static T dymmy = {}; 
			rves_if(dymmy, 0 == Data);
			gthrow_if(index >= Count, LLC_FMT_U32_GE_U32, index, Count);
			return Data[index];
		}
		cnst T&					operator[]		(u2_t index)			cnst				{
			gsthrow_if(0 == Data);
			gthrow_if(index >= Count, LLC_FMT_U32_GE_U32, index, Count);
			return Data[index];
		}
		bool					operator!=		(cnst TConstView & other)	cnst				{ return  !operator==(other); } // I had to add this for the android build not supporting C++20.
		bool					operator==		(cnst TConstView & other)	cnst				{
			if(this->size() != other.size())
				return false;
			if(this->begin() == other.begin())
				return true;
			return ::llc::equal(other.begin(), this->begin(), this->size());
		}

		// Methods
		inlcxpr	u2_t			byte_count		()							cnstnxpt	{ return u2_t(Count * sizeof(T));	}
		inlcxpr	uint64_t		bit_count		()							cnstnxpt	{ return byte_count() * 8ULL;			}

		inline	view<sc_t>		c				()								nxpt	{ return {(sc_t			*)Data, byte_count()}; }
		inline	view<i0u_t>		u8				()								nxpt	{ return {(i0u_t		*)Data, byte_count()}; }
		inlcxpr	view<sc_c>		cc				()							cnstnxpt	{ return {(cnst sc_t	*)Data, byte_count()}; }
		inlcxpr	view<i0u_c>		u8				()							cnstnxpt	{ return {(i0u_c		*)Data, byte_count()}; }
		inlcxpr	view<i0u_c>		cu8				()							cnstnxpt	{ return {(i0u_c		*)Data, byte_count()}; }

		inlcxpr	u2_c&			size			()							cnstnxpt	{ return Count;				}
		inlcxpr	cnst T*			begin			()							cnstnxpt	{ return Data;				}
		inlcxpr	cnst T*			end				()							cnstnxpt	{ return begin() + Count;	}
		inline	T*				begin			()								nxpt	{ return Data;				}
		inline	T*				end				()								nxpt	{ return begin() + Count;	}
		::llc::error_t			slice			(TView & out, u2_t offset, u2_t count = (u2_t)-1)				{
			reterr_gerror_if(offset > Count, LLC_FMT_U32_GT_U32, offset, (u2_t)Count);
			cnst u2_t					newSize			= Count - offset;
			if(count != (u2_t)-1)
				ree_if(count > newSize, LLC_FMT_U32_GT_U32, count, (u2_t)newSize);
			out						= {&Data[offset], ::llc::min(newSize, count)};
			return out.size();
		}
		::llc::error_t			slice			(TConstView & out, u2_t offset, u2_t count = (u2_t)-1)	cnst	{
			ree_if(offset > Count, LLC_FMT_U32_GT_U32, offset, (u2_t)Count);
			cnst u2_t					newSize			= Count - offset;
			if(count != (u2_t)-1)
				ree_if(count > newSize, LLC_FMT_U32_GT_U32, count, (u2_t)newSize);
			out						= {&Data[offset], ::llc::min(newSize, count)};
			return out.size();
		}
		::llc::error_t			revert			()																			{
			cnst u2_t					lastElement		= Count - 1;
			for(u2_t i = 0, swapCount = Count / 2; i < swapCount; ++i) {
				T							old				= Data[i];
				Data[i]					= Data[lastElement - i];
				Data[lastElement - i]	= old;
			}
			return 0;
		}

		inline	::llc::error_t	fill			(cnst T & value, u2_t offset = 0, u2_t stop = 0xFFFFFFFFU)		{ for(; offset < ::llc::min(Count, stop); ++offset) Data[offset] = value; return Count; }


		::llc::error_t			for_each		(cnst ::llc::TFuncForEach       <T> & funcForEach, u2_t offset = 0)			{ for(; offset < Count; ++offset) funcForEach(Data[offset]); return offset; }
		::llc::error_t			for_each		(cnst ::llc::TFuncForEachConst  <T> & funcForEach, u2_t offset = 0)	cnst	{ for(; offset < Count; ++offset) funcForEach(Data[offset]); return offset; }
		::llc::error_t			enumerate		(cnst ::llc::TFuncEnumerate     <T> & funcForEach, u2_t offset = 0)			{ for(; offset < Count; ++offset) funcForEach(offset, Data[offset]); return offset; }
		::llc::error_t			enumerate		(cnst ::llc::TFuncEnumerateConst<T> & funcForEach, u2_t offset = 0)	cnst	{ for(; offset < Count; ++offset) funcForEach(offset, Data[offset]); return offset; }
		//
		::llc::error_t			for_each		(cnst ::llc::TFuncForEach       <T> & funcForEach, u2_t offset, u2_t stop)			{ for(stop = ::llc::min(stop, Count); offset < stop; ++offset) funcForEach(Data[offset]); return offset; }
		::llc::error_t			for_each		(cnst ::llc::TFuncForEachConst  <T> & funcForEach, u2_t offset, u2_t stop)	cnst	{ for(stop = ::llc::min(stop, Count); offset < stop; ++offset) funcForEach(Data[offset]); return offset; }
		::llc::error_t			enumerate		(cnst ::llc::TFuncEnumerate     <T> & funcForEach, u2_t offset, u2_t stop)			{ for(stop = ::llc::min(stop, Count); offset < stop; ++offset) funcForEach(offset, Data[offset]); return offset; }
		::llc::error_t			enumerate		(cnst ::llc::TFuncEnumerateConst<T> & funcForEach, u2_t offset, u2_t stop)	cnst	{ for(stop = ::llc::min(stop, Count); offset < stop; ++offset) funcForEach(offset, Data[offset]); return offset; }

		::llc::error_t			find			(cnst FBool<T&>		& funcForEach, u2_t offset = 0)			{ for(; offset < Count; ++offset) if(funcForEach(Data[offset])) return (::llc::error_t)offset; return -1; }
		::llc::error_t			find			(cnst FBool<cnst T&>	& funcForEach, u2_t offset = 0)	cnst	{ for(; offset < Count; ++offset) if(funcForEach(Data[offset])) return (::llc::error_t)offset; return -1; }
		::llc::error_t			find			(cnst T & value, u2_t offset = 0)						cnst	{ for(; offset < Count; ++offset) if(Data[offset] == value) return (::llc::error_t)offset; return -1; }

		tplt<tpnm _tMax> ::llc::error_t	max	(_tMax & maxFound, cnst FTransform<_tMax, cnst T &> & funcComparand, u2_t offset = 0)	cnst	{ s2_t iMax = 0; for(; offset < Count; ++offset) { _tMax value = funcComparand(Data[offset]); if(value > maxFound) { iMax = offset; maxFound = value; } } return iMax; }
		tplt<tpnm _tMax> ::llc::error_t	min	(_tMax & minFound, cnst FTransform<_tMax, cnst T &> & funcComparand, u2_t offset = 0)	cnst	{ s2_t iMin = 0; for(; offset < Count; ++offset) { _tMax value = funcComparand(Data[offset]); if(value < minFound) { iMin = offset; minFound = value; } } return iMin; }
		tplt<tpnm _tMax> ::llc::error_t	max	(cnst FTransform<_tMax, cnst T &> & funcComparand, u2_t offset = 0)					cnst	{ _tMax maxFound; return max(maxFound, funcComparand, offset); }
		tplt<tpnm _tMax> ::llc::error_t	min	(cnst FTransform<_tMax, cnst T &> & funcComparand, u2_t offset = 0)					cnst	{ _tMax minFound; return min(minFound, funcComparand, offset); }
	}; // view<>

	tplT			using	view_array	= ::llc::view<T>;
	tplT			using	view1d		= ::llc::view<T>;
	tplT			using	v1			= ::llc::view<T>;

	tplT			ndstinx	u2_t	size		(cnst ::llc::view<T> & viewToTest)	nxpt	{ return viewToTest.size();			}
	tplT			ndstinx	u2_t	byte_count	(cnst ::llc::view<T> & viewToTest)	nxpt	{ return viewToTest.byte_count();	}

#pragma pack(pop)

	typedef	::llc::view<b8_t>	vb8_t;
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

	typedef	::llc::view<b8_c>	vcb8_t;
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

	typedef	cnst vb8_t 		vb8_c;
	typedef	cnst vuc_t 		vuc_c;
	typedef	cnst vsc_t 		vsc_c;
	typedef	cnst vu0_t 		vu0_c;
	typedef	cnst vu1_t 		vu1_c;
	typedef	cnst vu2_t 		vu2_c;
	typedef	cnst vu3_t 		vu3_c;
	typedef	cnst vs0_t 		vs0_c;
	typedef	cnst vs1_t 		vs1_c;
	typedef	cnst vs2_t 		vs2_c;
	typedef	cnst vs3_t 		vs3_c;
	typedef	cnst vf2_t 		vf2_c;
	typedef	cnst vf3_t 		vf3_c;

	typedef	cnst vcb8_t 		vcb8_c;
	typedef	cnst vcuc_t 		vcuc_c;
	typedef	cnst vcsc_t 		vcsc_c;
	typedef	cnst vcu0_t 		vcu0_c;
	typedef	cnst vcu1_t 		vcu1_c;
	typedef	cnst vcu2_t 		vcu2_c;
	typedef	cnst vcu3_t 		vcu3_c;
	typedef	cnst vcs0_t 		vcs0_c;
	typedef	cnst vcs1_t 		vcs1_c;
	typedef	cnst vcs2_t 		vcs2_c;
	typedef	cnst vcs3_t 		vcs3_c;
	typedef	cnst vcf2_t 		vcf2_c;
	typedef	cnst vcf3_t 		vcf3_c;

// Use this to initialize a constexpr vcs from a string literal
#define LLC_CXS(constexpr_string_literal) ::llc::vcsc_t{::llc::u2_t(sizeof(constexpr_string_literal) - 1), constexpr_string_literal}

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

	typedef	cnst vvuc_t	vvuc_c;
	typedef	cnst vvsc_t	vvsc_c;
	typedef	cnst vvu0_t	vvu0_c;
	typedef	cnst vvu1_t	vvu1_c;
	typedef	cnst vvu2_t	vvu2_c;
	typedef	cnst vvu3_t	vvu3_c;
	typedef	cnst vvs0_t	vvs0_c;
	typedef	cnst vvs1_t	vvs1_c;
	typedef	cnst vvs2_t	vvs2_c;
	typedef	cnst vvs3_t	vvs3_c;
	typedef	cnst vvf2_t	vvf2_c;
	typedef	cnst vvf3_t	vvf3_c;
	typedef	cnst vcvuc_t	vcvuc_c;
	typedef	cnst vcvsc_t	vcvsc_c;
	typedef	cnst vcvu0_t	vcvu0_c;
	typedef	cnst vcvu1_t	vcvu1_c;
	typedef	cnst vcvu2_t	vcvu2_c;
	typedef	cnst vcvu3_t	vcvu3_c;
	typedef	cnst vcvs0_t	vcvs0_c;
	typedef	cnst vcvs1_t	vcvs1_c;
	typedef	cnst vcvs2_t	vcvs2_c;
	typedef	cnst vcvs3_t	vcvs3_c;
	typedef	cnst vcvf2_t	vcvf2_c;
	typedef	cnst vcvf3_t	vcvf3_c;

	stacxpr	::llc::vcc	VCC_NULL		= {4, "null"};
	stacxpr	::llc::vcc	VCC_TRUE		= {4, "true"};
	stacxpr	::llc::vcc	VCC_FALSE		= {5, "false"};

	ndstinx	::llc::vcc	bool2vcc		(bool b)		{ return b ? ::llc::VCC_TRUE : ::llc::VCC_FALSE; }
	ndstinx	cnst sc_t*	bool2char		(bool b)		{ return b ? ::llc::VCC_TRUE.begin() : ::llc::VCC_FALSE.begin(); }
	ndstinx	uint8_t		bool2u8			(bool b)		{ return b ? 1 : 0; }
	ndstinx	uint8_t		bool2i8			(bool b)		{ return b ? 1 : 0; }
	stainli	cnst sc_t*	bool2char		(bool b, ::llc::vcc & output)	{ return (output = b ? ::llc::VCC_TRUE : ::llc::VCC_FALSE).begin(); }
	stainli	bool		vcc2bool		(::llc::vcc b)	{ return b.size() && b != VCC_FALSE; }

	struct view_string : view<sc_t> {
		inlcxpr			view_string				()											= default;
		inlcxpr			view_string				(vsc_c & other)						nxpt	: view(other)				{}
		tplN2u			view_string				(sc_t (&storage)[N])				nxpt	: view(storage)			{ Count = (u2_t)strnlen(storage, (u2_t)N);							}
		tplN2u			view_string				(sc_t (&storage)[N], u2_t length)			: view(storage, length)	{ if(length == (u2_t)-1) Count = (u2_t)strnlen(storage, (u2_t)N);	}
						view_string				(sc_t * storage, u2_t length)				: view(storage, length)	{ Count = (length == (u2_t)-1) ? (u2_t)strlen(storage) : length;		}

		inlcxpr	sc_c*	begin					()	cnstnxpt	{ return (Data && Count) ? Data : ""; }
		inlcxpr	sc_c*	end						()	cnstnxpt	{ return (Data && Count) ? Data + Count : begin(); }
		ndinlne oprt	sc_c* 					()  cnstnxpt	{ return begin(); }
	};
	struct view_const_string : view<sc_c> {
		inlcxpr			view_const_string		()											: view(0, "") 							{}
		inlcxpr			view_const_string		(vcsc_c & other)					nxpt	: view(other)							{}
		tplt<u2_t Len>	view_const_string		(sc_c (&storage)[Len])				nxpt	: view(storage)							{ Count = (u2_t)strnlen(storage, (u2_t)Len);							}
		tplt<u2_t Len>	view_const_string		(sc_c (&storage)[Len], u2_t length)			: view(storage, length)					{ if(length == (u2_t)-1) Count = (u2_t)strnlen(storage, (u2_t)Len);	}
						view_const_string		(sc_c * storage, u2_t length)				: view(storage ? storage : "", length)	{ if(length == (u2_t)-1) Count = (u2_t)strlen(begin());					}

		inlcxpr	sc_c*	begin					()	cnstnxpt	{ return (Data && Count) ? Data : ""; }
		inlcxpr	sc_c*	end						()	cnstnxpt	{ return (Data && Count) ? Data + Count : begin(); }
		ndinlne oprt	sc_c* 					()  cnstnxpt	{ return begin(); }
	};

	typedef	::llc::view_string			vstr_t, vs;
	typedef	::llc::view_const_string	vcst_t, vcs;
	typedef	cnst vstr_t					vstr_c;
	typedef	cnst vcst_t					vcst_c;

	stainli			llc::vcs	str				(cnst llc::vcs & arg)	{ return arg; } 
	stainli			llc::vcs	str				(cnst llc::vs & arg)	{ return arg.cc(); } 
	// 
	tplT	ndstinx	::llc::vcs	get_type_namev	()							nxpt	{ return LLC_CXS("unknown"); }
	tplT	ndstinx	cnst sc_t*	get_type_namep	()							nxpt	{ return get_type_namev<T>().begin(); }

#define GDEFINE_TYPE_NAME_STR(typeIdentifier)																													\
			ndstinx	::llc::vcs	get_type_namev					(typeIdentifier &)	nxpt	{ return LLC_CXS(#typeIdentifier); }					\
	tplt<>	ndincxp	::llc::vcs	get_type_namev<typeIdentifier>	()					nxpt	{ return LLC_CXS(#typeIdentifier); }					\
			ndstinx	cnst sc_t*	get_type_namep					(typeIdentifier &)	nxpt	{ return get_type_namev<typeIdentifier>().begin(); }	\
	tplt<>	ndincxp	cnst sc_t*	get_type_namep<typeIdentifier>	()					nxpt	{ return get_type_namev<typeIdentifier>().begin(); }	
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
	typedef	::llc::view<cnst ::llc::vs		>	vcvs;
	typedef	::llc::view<cnst ::llc::vcs	>	vcvcs;

	stacxpr	::llc::vcc		TRIM_CHARACTERS		= " \t\b\n\r";

	::llc::error_t			rtrim				(::llc::vcc & trimmed, cnst ::llc::vcc & original, cnst ::llc::vcc & characters = ::llc::TRIM_CHARACTERS);
	::llc::error_t			ltrim				(::llc::vcc & trimmed, cnst ::llc::vcc & original, cnst ::llc::vcc & characters = ::llc::TRIM_CHARACTERS);
	::llc::error_t			trim				(::llc::vcc & trimmed, cnst ::llc::vcc & original, cnst ::llc::vcc & characters = ::llc::TRIM_CHARACTERS);
	stainli	::llc::error_t	rtrim				(::llc::vcc & trimmed) 	{ return rtrim(trimmed, trimmed); }
	stainli	::llc::error_t	ltrim				(::llc::vcc & trimmed) 	{ return ltrim(trimmed, trimmed); }
	stainli	::llc::error_t	trim				(::llc::vcc & trimmed) 	{ return trim(trimmed, trimmed); }
	
	stainli	::llc::error_t	rtrim				(::llc::vc & trimmed, cnst ::llc::vc & original, cnst ::llc::vcc & characters = ::llc::TRIM_CHARACTERS)	{ return rtrim	(*(::llc::vcc*)&trimmed, *(cnst ::llc::vcc*)&original, characters); }
	stainli	::llc::error_t	ltrim				(::llc::vc & trimmed, cnst ::llc::vc & original, cnst ::llc::vcc & characters = ::llc::TRIM_CHARACTERS)	{ return ltrim	(*(::llc::vcc*)&trimmed, *(cnst ::llc::vcc*)&original, characters); }
	stainli	::llc::error_t	trim				(::llc::vc & trimmed, cnst ::llc::vc & original, cnst ::llc::vcc & characters = ::llc::TRIM_CHARACTERS)	{ return trim	(*(::llc::vcc*)&trimmed, *(cnst ::llc::vcc*)&original, characters); }
	stainli	::llc::error_t	rtrim				(::llc::vc & trimmed) 	{ return rtrim(trimmed, trimmed); }
	stainli	::llc::error_t	ltrim				(::llc::vc & trimmed) 	{ return ltrim(trimmed, trimmed); }
	stainli	::llc::error_t	trim				(::llc::vc & trimmed) 	{ return trim(trimmed, trimmed); }

	tplt <tpnm T>
	::llc::error_t			reverse				(::llc::view<T> elements)													{
		cnst u2_t				lastElement			= elements.size() - 1;
		for(u2_t i = 0, swapCount = elements.size() / 2; i < swapCount; ++i) {
			T							old						= elements[i];
			elements[i]					= elements[lastElement - i];
			elements[lastElement - i]	= old;
		}
		return 0;
	}

	tplT	::llc::error_t			find					(cnst T & valueToFind, cnst ::llc::view<cnst T> & target, u2_t offset = 0)		{
		for(u2_t iOffset = offset, offsetStop = target.size(); iOffset < offsetStop; ++iOffset)
			if(valueToFind == target[iOffset])
				return (s2_t)iOffset;
		return -1;
	}

	tplT	::llc::error_t					rfind					(cnst T & valueToFind, cnst ::llc::view<cnst T> & target, s2_t offset = 0)		{
		for(u2_t iOffset = target.size() - 1 - offset; iOffset < target.size(); --iOffset)
			if(valueToFind == target[iOffset])
				return iOffset;
		return -1;
	}

	tplT	::llc::error_t					find_sequence_obj		(cnst ::llc::view<T> & sequence, cnst ::llc::view<T> & target, u2_t offset = 0)	{
		for(s2_t iOffset = (s2_t)offset, offsetStop = ((s2_t)target.size() - sequence.size()) + 1; iOffset < offsetStop; ++iOffset) {
			bool								equal					= true;
			for(u2_t iSequenceElement = 0; iSequenceElement < sequence.size(); ++iSequenceElement) {
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

	tplT	::llc::error_t					rfind_sequence_obj		(cnst ::llc::view<T> & sequence, cnst ::llc::view<T> & target, u2_t offset = 0)	{
		for(s2_t iOffset = (s2_t)(target.size() - sequence.size() - offset); iOffset >= 0; --iOffset) {
			bool								equal					= true;
			for(u2_t iSequenceElement = 0; iSequenceElement < sequence.size(); ++iSequenceElement) {
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

	tplT	::llc::error_t					find_sequence_pod		(cnst ::llc::view<T> & sequence, cnst ::llc::view<T> & target, u2_t offset = 0)	{
		for(s2_t iOffset = (s2_t)offset, offsetStop = ((s2_t)target.size() - sequence.size()) + 1; iOffset < offsetStop; ++iOffset)
			if(0 == memcmp(sequence.begin(), &target[iOffset], sequence.size() * sizeof(T)))
				return iOffset;
		return -1;
	}

	tplT	::llc::error_t					rfind_sequence_pod		(cnst ::llc::view<T> & sequence, cnst ::llc::view<T>& target, u2_t offset = 0)	{
		for(s2_t iOffset = (s2_t)(target.size() - sequence.size() - offset); iOffset >= 0; --iOffset)
			if(0 == memcmp(sequence.begin(), &target[iOffset], sequence.size() * sizeof(T)))
				return iOffset;
		return -1;
	}

	stainli	::llc::error_t			find_string				(cnst ::llc::vcs & toFind, cnst ::llc::vcc & target, u2_t offset = 0) { return ::llc::find_sequence_pod (toFind, target, offset); }
	stainli	::llc::error_t			rfind_string			(cnst ::llc::vcs & toFind, cnst ::llc::vcc & target, u2_t offset = 0) { return ::llc::rfind_sequence_pod(toFind, target, offset); }

	tplT	::llc::error_t					split					(cnst T & valueToFind, cnst ::llc::view<T> & original, ::llc::view<T> & left, ::llc::view<T> & right) {
		cnst ::llc::error_t				iValue					= ::llc::find(valueToFind, original);
		if(0 > iValue) {
			left							= original;
			right							= {};
		}
		else {
			llc_necs(original.slice(left, 0, iValue));
			cnst u2_t						offsetRight				= iValue + 1;
			llc_necs(original.slice(right, offsetRight, original.size() - offsetRight));
		}
		return iValue;
	}

	tplT	::llc::error_t					splitAt					(cnst T & valueToFind, cnst ::llc::view<T> & original, ::llc::view<T> & left, ::llc::view<T> & right) {
		cnst ::llc::error_t				iValue					= ::llc::find(valueToFind, original);
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
	tplT	::llc::error_t					split					(cnst ::llc::view<T> & sequenceToFind, cnst ::llc::view<T> & original, ::llc::view<T> & left, ::llc::view<T> & right) {
		cnst ::llc::error_t				iValue					= ::llc::find_sequence_pod(sequenceToFind, original);
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
	inline	::llc::error_t			split					(cnst ::llc::view<T> & sequenceToFind, ::llc::view<T> & inputOrLeft, ::llc::view<T> & right) {
		return ::llc::split(sequenceToFind, inputOrLeft, inputOrLeft, right);
	}

	tplT	::llc::error_t					splitAt					(cnst ::llc::view<T> & sequenceToFind, cnst ::llc::view<T> & original, ::llc::view<T> & left, ::llc::view<T> & right) {
		cnst ::llc::error_t				iValue					= ::llc::find_sequence_pod(sequenceToFind, original);
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

	tplT	err_t		max						(::llc::view<T> input, T ** result) {
		ree_if(0 == input.size(), "%s", "Cannot get reference to max element of an empty array.");
		*result				= &input[0];
		s2_t					iMax					= 0;
		for(u2_t iElement = 1; iElement < input.size(); ++iElement) {
			cnst T					& currentElement		= input[iElement];
			if(currentElement > **result) {
				*result					= &currentElement;
				iMax					= iElement;
			}
		}
		return iMax;
	}

	tplT	err_t		min						(::llc::view<T> input, T ** result) {
		ree_if(0 == input.size(), "%s", "Cannot get reference to min element of an empty array.");
		*result				= &input[0];
		s2_t					iMin					= 0;
		for(u2_t iElement = 1; iElement < input.size(); ++iElement) {
			cnst T					& currentElement		= input[iElement];
			if(currentElement < **result) {
				*result				= &currentElement;
				iMin				= iElement;
			}
		}
		return iMin;
	}

	tplT	T&			max		(::llc::view<T> elements)		{ T * rmax	{}; if_fail_e(::llc::max(elements, &rmax));	return *rmax; }
	tplT	T&			min		(::llc::view<T> elements)		{ T * rmin	{}; if_fail_e(::llc::min(elements, &rmin));	return *rmin; }
	tplT	T			sum		(::llc::view<cnst T> elements)	{ T result	{}; for(T element : elements) result += element; return result; }
	tplT	stainli	T&	be2le	(T & number)					{ ::llc::reverse<i0u_t>({(i0u_t*)&number, sizeof(T)}); return number; }
} // namespace

#endif // LLC_ARRAY_VIEW_H_23627
