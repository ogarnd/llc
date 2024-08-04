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
		tydf	_tVal			T;
		tydf	view<cnst T>	TConstView;
		tydf	view<T>			TView;

		// Constructors
		inxp					view			()									nxpt	= default;
		inxp					view			(cnst view<T> & other)				nxpt	= default;

		tplt<size_t Len>
		inxp					view			(T (&elements)[Len])				nxpt	: Data(elements), Count(Len)										{}

		tplt<size_t Len>
		inxp					view			(u2_t elementCount, T (&elements)[Len])		: Data(elements), Count(::llc::min((u2_t)Len, elementCount))	{}
		inln					view			(T * elements, u2_t elementCount)			: Data(elements), Count(elementCount)								{
			gthrow_if(0 == elements && 0 != elementCount, "%" LLC_FMT_U2 " -> 0.", elementCount);	// Crash if we received invalid parameters in order to prevent further malfunctioning.
		}

		tplt <size_t Len>
		inln					view			(T (&elements)[Len], u2_t elementCount)		: Data(elements), Count(::llc::min((u2_t)Len, elementCount))	{
			gthrow_if(elementCount > Len, LLC_FMT_GT_U2, elementCount, (u2_t)Len);
		}

		// Operators
		inxp	operator		view<cnst T>	()							csnx	{ return {Data, Count}; }

		T&						operator[]		(u2_t index)								{
			static T dymmy = {}; 
			rves_if(dymmy, 0 == Data);
			gthrow_if(index >= Count, LLC_FMT_GE_U2, index, Count);
			return Data[index];
		}
		cnst T&					operator[]		(u2_t index)			cnst				{
			gsthrow_if(0 == Data);
			gthrow_if(index >= Count, LLC_FMT_GE_U2, index, Count);
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
		inxp	u2_t			byte_count		()														csnx	{ return u2_t(Count * sizeof(T));	}
		inxp	uint64_t		bit_count		()														csnx	{ return byte_count() * 8ULL;			}
		inln	view<sc_t>		c				()														nxpt	{ return {(sc_t			*)Data, byte_count()}; }
		inln	view<i0u_t>		u8				()														nxpt	{ return {(i0u_t		*)Data, byte_count()}; }
		inxp	view<sc_c>		cc				()														csnx	{ return {(cnst sc_t	*)Data, byte_count()}; }
		inxp	view<i0u_c>		u8				()														csnx	{ return {(i0u_c		*)Data, byte_count()}; }
		inxp	view<i0u_c>		cu8				()														csnx	{ return {(i0u_c		*)Data, byte_count()}; }
		inxp	u2_c&			size			()														csnx	{ return Count;				}
		inxp	cnst T*			begin			()														csnx	{ return Data;				}
		inxp	cnst T*			end				()														csnx	{ return begin() + Count;	}
		inln	T*				begin			()														nxpt	{ return Data;				}
		inln	T*				end				()														nxpt	{ return begin() + Count;	}
		::llc::error_t			slice			(TView & out, u2_t offset, u2_t count = (u2_t)-1)				{
			reterr_gerror_if(offset > Count, LLC_FMT_GT_U2, offset, (u2_t)Count);
			u2_c					newSize			= Count - offset;
			if(count != (u2_t)-1)
				ree_if(count > newSize, LLC_FMT_GT_U2, count, (u2_t)newSize);
			out						= {&Data[offset], ::llc::min(newSize, count)};
			return out.size();
		}
		::llc::error_t			slice			(TConstView & out, u2_t offset, u2_t count = (u2_t)-1)	cnst	{
			ree_if(offset > Count, LLC_FMT_GT_U2, offset, (u2_t)Count);
			u2_c					newSize			= Count - offset;
			if(count != (u2_t)-1)
				ree_if(count > newSize, LLC_FMT_GT_U2, count, (u2_t)newSize);
			out						= {&Data[offset], ::llc::min(newSize, count)};
			return out.size();
		}
		::llc::error_t			revert			()																			{
			u2_c					lastElement		= Count - 1;
			for(u2_t i = 0, swapCount = Count / 2; i < swapCount; ++i) {
				T							old				= Data[i];
				Data[i]					= Data[lastElement - i];
				Data[lastElement - i]	= old;
			}
			return 0;
		}

		inln	::llc::error_t	fill			(cnst T & value, u2_t offset = 0, u2_t stop = 0xFFFFFFFFU)		{ for(; offset < ::llc::min(Count, stop); ++offset) Data[offset] = value; return Count; }


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

	tplT			nsix	u2_t	size		(cnst ::llc::view<T> & viewToTest)	nxpt	{ return viewToTest.size();			}
	tplT			nsix	u2_t	byte_count	(cnst ::llc::view<T> & viewToTest)	nxpt	{ return viewToTest.byte_count();	}

#pragma pack(pop)

	tydf	::llc::view<b8_t>	vb8_t;
	tydf	::llc::view<uc_t>	vuc_t, vuc, vuchar;
	tydf	::llc::view<sc_t>	vsc_t, vc, vchar;
	tydf	::llc::view<u0_t>	vu0_t, vu8;
	tydf	::llc::view<u1_t>	vu1_t, vu16;
	tydf	::llc::view<u2_t>	vu2_t, vu32;
	tydf	::llc::view<u3_t>	vu3_t, vu64;
	tydf	::llc::view<s0_t>	vs0_t, vi8;
	tydf	::llc::view<s1_t>	vs1_t, vi16;
	tydf	::llc::view<s2_t>	vs2_t, vi32;
	tydf	::llc::view<s3_t>	vs3_t, vi64;
	tydf	::llc::view<f2_t>	vf2_t, vf32;
	tydf	::llc::view<f3_t>	vf3_t, vf64;

	tydf	::llc::view<b8_c>	vcb8_t;
	tydf	::llc::view<uc_c>	vcuc_t, vcuc, vcuchar;
	tydf	::llc::view<sc_c>	vcsc_t, vcc, vcchar;
	tydf	::llc::view<u0_c>	vcu0_t, vcu0_t;
	tydf	::llc::view<u1_c>	vcu1_t, vcu16;
	tydf	::llc::view<u2_c>	vcu2_t, vcu32;
	tydf	::llc::view<u3_c>	vcu3_t, vcu64;
	tydf	::llc::view<s0_c>	vcs0_t, vcs0_t;
	tydf	::llc::view<s1_c>	vcs1_t, vci16;
	tydf	::llc::view<s2_c>	vcs2_t, vci32;
	tydf	::llc::view<s3_c>	vcs3_t, vci64;
	tydf	::llc::view<f2_c>	vcf2_t, vcf32;
	tydf	::llc::view<f3_c>	vcf3_t, vcf64;

	tdcs	 vb8_t 	vb8_c;
	tdcs	 vuc_t 	vuc_c;
	tdcs	 vsc_t 	vsc_c;
	tdcs	 vu0_t 	vu0_c;
	tdcs	 vu1_t 	vu1_c;
	tdcs	 vu2_t 	vu2_c;
	tdcs	 vu3_t 	vu3_c;
	tdcs	 vs0_t 	vs0_c;
	tdcs	 vs1_t 	vs1_c;
	tdcs	 vs2_t 	vs2_c;
	tdcs	 vs3_t 	vs3_c;
	tdcs	 vf2_t 	vf2_c;
	tdcs	 vf3_t 	vf3_c;

	tdcs	 vcb8_t vcb8_c;
	tdcs	 vcuc_t vcuc_c;
	tdcs	 vcsc_t vcsc_c;
	tdcs	 vcu0_t vcu0_c;
	tdcs	 vcu1_t vcu1_c;
	tdcs	 vcu2_t vcu2_c;
	tdcs	 vcu3_t vcu3_c;
	tdcs	 vcs0_t vcs0_c;
	tdcs	 vcs1_t vcs1_c;
	tdcs	 vcs2_t vcs2_c;
	tdcs	 vcs3_t vcs3_c;
	tdcs	 vcf2_t vcf2_c;
	tdcs	 vcf3_t vcf3_c;
// Use this to initialize a constexpr vcs from a string literal
#define LLC_CXS(constexpr_string_literal) ::llc::vcsc_t{::llc::u2_t(sizeof(constexpr_string_literal) - 1), constexpr_string_literal}
	tydf	::llc::view<vuc_t>	vvuc_t;
	tydf	::llc::view<vsc_t>	vvsc_t;
	tydf	::llc::view<vu0_t>	vvu0_t;
	tydf	::llc::view<vu1_t>	vvu1_t;
	tydf	::llc::view<vu2_t>	vvu2_t;
	tydf	::llc::view<vu3_t>	vvu3_t;
	tydf	::llc::view<vs0_t>	vvs0_t;
	tydf	::llc::view<vs1_t>	vvs1_t;
	tydf	::llc::view<vs2_t>	vvs2_t;
	tydf	::llc::view<vs3_t>	vvs3_t;
	tydf	::llc::view<vf2_t>	vvf2_t;
	tydf	::llc::view<vf3_t>	vvf3_t;
	tydf	::llc::view<vuc_c>	vcvuc_t;
	tydf	::llc::view<vsc_c>	vcvsc_t;
	tydf	::llc::view<vu0_c>	vcvu0_t;
	tydf	::llc::view<vu1_c>	vcvu1_t;
	tydf	::llc::view<vu2_c>	vcvu2_t;
	tydf	::llc::view<vu3_c>	vcvu3_t;
	tydf	::llc::view<vs0_c>	vcvs0_t;
	tydf	::llc::view<vs1_c>	vcvs1_t;
	tydf	::llc::view<vs2_c>	vcvs2_t;
	tydf	::llc::view<vs3_c>	vcvs3_t;
	tydf	::llc::view<vf2_c>	vcvf2_t;
	tydf	::llc::view<vf3_c>	vcvf3_t;
	tdcs	vvuc_t	vvuc_c;
	tdcs	vvsc_t	vvsc_c;
	tdcs	vvu0_t	vvu0_c;
	tdcs	vvu1_t	vvu1_c;
	tdcs	vvu2_t	vvu2_c;
	tdcs	vvu3_t	vvu3_c;
	tdcs	vvs0_t	vvs0_c;
	tdcs	vvs1_t	vvs1_c;
	tdcs	vvs2_t	vvs2_c;
	tdcs	vvs3_t	vvs3_c;
	tdcs	vvf2_t	vvf2_c;
	tdcs	vvf3_t	vvf3_c;
	tdcs	vcvuc_t	vcvuc_c;
	tdcs	vcvsc_t	vcvsc_c;
	tdcs	vcvu0_t	vcvu0_c;
	tdcs	vcvu1_t	vcvu1_c;
	tdcs	vcvu2_t	vcvu2_c;
	tdcs	vcvu3_t	vcvu3_c;
	tdcs	vcvs0_t	vcvs0_c;
	tdcs	vcvs1_t	vcvs1_c;
	tdcs	vcvs2_t	vcvs2_c;
	tdcs	vcvs3_t	vcvs3_c;
	tdcs	vcvf2_t	vcvf2_c;
	tdcs	vcvf3_t	vcvf3_c;

	stxp	::llc::vcc	VCC_NULL		= {4, "null"};
	stxp	::llc::vcc	VCC_TRUE		= {4, "true"};
	stxp	::llc::vcc	VCC_FALSE		= {5, "false"};

	nsix	::llc::vcc	bool2vcc		(bool b)		{ return b ? ::llc::VCC_TRUE : ::llc::VCC_FALSE; }
	nsix	cnst sc_t*	bool2char		(bool b)		{ return b ? ::llc::VCC_TRUE.begin() : ::llc::VCC_FALSE.begin(); }
	nsix	uint8_t		bool2u8			(bool b)		{ return b ? 1 : 0; }
	nsix	uint8_t		bool2i8			(bool b)		{ return b ? 1 : 0; }
	stin	cnst sc_t*	bool2char		(bool b, ::llc::vcc & output)	{ return (output = b ? ::llc::VCC_TRUE : ::llc::VCC_FALSE).begin(); }
	stin	bool		vcc2bool		(::llc::vcc b)	{ return b.size() && b != VCC_FALSE; }

	struct view_string : view<sc_t> {
		inxp			view_string				()											= default;
		inxp			view_string				(vsc_c & other)						nxpt	: view(other)				{}
		tplN2u			view_string				(sc_t (&storage)[N])				nxpt	: view(storage)			{ Count = (u2_t)strnlen(storage, (u2_t)N);							}
		tplN2u			view_string				(sc_t (&storage)[N], u2_t length)			: view(storage, length)	{ if(length == (u2_t)-1) Count = (u2_t)strnlen(storage, (u2_t)N);	}
						view_string				(sc_t * storage, u2_t length)				: view(storage, length)	{ Count = (length == (u2_t)-1) ? (u2_t)strlen(storage) : length;		}

		inxp	sc_c*	begin					()	csnx	{ return (Data && Count) ? Data : ""; }
		inxp	sc_c*	end						()	csnx	{ return (Data && Count) ? Data + Count : begin(); }
		ndin	oper	sc_c* 					()  csnx	{ return begin(); }
	};
	struct view_const_string : view<sc_c> {
		inxp			view_const_string		()											: view(0, "") 							{}
		inxp			view_const_string		(vcsc_c & other)					nxpt	: view(other)							{}
		tplt<u2_t Len>	view_const_string		(sc_c (&storage)[Len])				nxpt	: view(storage)							{ Count = (u2_t)strnlen(storage, (u2_t)Len);							}
		tplt<u2_t Len>	view_const_string		(sc_c (&storage)[Len], u2_t length)			: view(storage, length)					{ if(length == (u2_t)-1) Count = (u2_t)strnlen(storage, (u2_t)Len);	}
						view_const_string		(sc_c * storage, u2_t length)				: view(storage ? storage : "", length)	{ if(length == (u2_t)-1) Count = (u2_t)strlen(begin());					}

		inxp	sc_c*	begin					()	csnx	{ return (Data && Count) ? Data : ""; }
		inxp	sc_c*	end						()	csnx	{ return (Data && Count) ? Data + Count : begin(); }
		ndin	oper	sc_c* 					()  csnx	{ return begin(); }
	};

	tydf	::llc::view_string			vstr_t, vs;
	tydf	::llc::view_const_string	vcst_t, vcs;
	tydf	cnst vstr_t					vstr_c;
	tydf	cnst vcst_t					vcst_c;

	stin			llc::vcs	str				(cnst llc::vcs & arg)	{ return arg; } 
	stin			llc::vcs	str				(cnst llc::vs & arg)	{ return arg.cc(); } 
	// 
	tplTnsix		::llc::vcs	get_type_namev	()							nxpt	{ return LLC_CXS("unknown"); }
	tplTnsix		sc_c*		get_type_namep	()							nxpt	{ return get_type_namev<T>().begin(); }

#define GDEFINE_TYPE_NAME_STR(typeIdentifier)																													\
			nsix	::llc::vcs	get_type_namev					(typeIdentifier &)	nxpt	{ return LLC_CXS(#typeIdentifier); }					\
	tplt<>	ndix	::llc::vcs	get_type_namev<typeIdentifier>	()					nxpt	{ return LLC_CXS(#typeIdentifier); }					\
			nsix	sc_c*		get_type_namep					(typeIdentifier &)	nxpt	{ return get_type_namev<typeIdentifier>().begin(); }	\
	tplt<>	ndix	sc_c*		get_type_namep<typeIdentifier>	()					nxpt	{ return get_type_namev<typeIdentifier>().begin(); }	
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
	tydf	::llc::view<::llc::vs			>	vvs;
	tydf	::llc::view<::llc::vcs			>	vvcs;
	tydf	::llc::view<cnst ::llc::vs		>	vcvs;
	tydf	::llc::view<cnst ::llc::vcs	>	vcvcs;

	stxp	::llc::vcc		TRIM_CHARACTERS		= " \t\b\n\r";

	::llc::error_t			rtrim				(::llc::vcc & trimmed, cnst ::llc::vcc & original, cnst ::llc::vcc & characters = ::llc::TRIM_CHARACTERS);
	::llc::error_t			ltrim				(::llc::vcc & trimmed, cnst ::llc::vcc & original, cnst ::llc::vcc & characters = ::llc::TRIM_CHARACTERS);
	::llc::error_t			trim				(::llc::vcc & trimmed, cnst ::llc::vcc & original, cnst ::llc::vcc & characters = ::llc::TRIM_CHARACTERS);
	stin	::llc::error_t	rtrim				(::llc::vcc & trimmed) 	{ return rtrim(trimmed, trimmed); }
	stin	::llc::error_t	ltrim				(::llc::vcc & trimmed) 	{ return ltrim(trimmed, trimmed); }
	stin	::llc::error_t	trim				(::llc::vcc & trimmed) 	{ return trim(trimmed, trimmed); }
	
	stin	::llc::error_t	rtrim				(::llc::vc & trimmed, cnst ::llc::vc & original, cnst ::llc::vcc & characters = ::llc::TRIM_CHARACTERS)	{ return rtrim	(*(::llc::vcc*)&trimmed, *(cnst ::llc::vcc*)&original, characters); }
	stin	::llc::error_t	ltrim				(::llc::vc & trimmed, cnst ::llc::vc & original, cnst ::llc::vcc & characters = ::llc::TRIM_CHARACTERS)	{ return ltrim	(*(::llc::vcc*)&trimmed, *(cnst ::llc::vcc*)&original, characters); }
	stin	::llc::error_t	trim				(::llc::vc & trimmed, cnst ::llc::vc & original, cnst ::llc::vcc & characters = ::llc::TRIM_CHARACTERS)	{ return trim	(*(::llc::vcc*)&trimmed, *(cnst ::llc::vcc*)&original, characters); }
	stin	::llc::error_t	rtrim				(::llc::vc & trimmed) 	{ return rtrim(trimmed, trimmed); }
	stin	::llc::error_t	ltrim				(::llc::vc & trimmed) 	{ return ltrim(trimmed, trimmed); }
	stin	::llc::error_t	trim				(::llc::vc & trimmed) 	{ return trim(trimmed, trimmed); }

	tplt <tpnm T>
	::llc::error_t			reverse				(::llc::view<T> elements)													{
		u2_c				lastElement			= elements.size() - 1;
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

	stin	::llc::error_t			find_string				(cnst ::llc::vcs & toFind, cnst ::llc::vcc & target, u2_t offset = 0) { return ::llc::find_sequence_pod (toFind, target, offset); }
	stin	::llc::error_t			rfind_string			(cnst ::llc::vcs & toFind, cnst ::llc::vcc & target, u2_t offset = 0) { return ::llc::rfind_sequence_pod(toFind, target, offset); }

	tplT	::llc::error_t					split					(cnst T & valueToFind, cnst ::llc::view<T> & original, ::llc::view<T> & left, ::llc::view<T> & right) {
		cnst ::llc::error_t				iValue					= ::llc::find(valueToFind, original);
		if(0 > iValue) {
			left							= original;
			right							= {};
		}
		else {
			llc_necs(original.slice(left, 0, iValue));
			u2_c						offsetRight				= iValue + 1;
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
	inln	::llc::error_t			split					(cnst ::llc::view<T> & sequenceToFind, ::llc::view<T> & inputOrLeft, ::llc::view<T> & right) {
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
	tplT	stin	T&	be2le	(T & number)					{ ::llc::reverse<i0u_t>({(i0u_t*)&number, sizeof(T)}); return number; }

#define LLC_USING_VIEW()												\
	using	::llc::vb8_t, ::llc::vb8_c, ::llc::vcb8_t, ::llc::vcb8_c	\
		,	::llc::vuc_t, ::llc::vuc_c, ::llc::vcuc_t, ::llc::vcuc_c	\
		,	::llc::vsc_t, ::llc::vsc_c, ::llc::vcsc_t, ::llc::vcsc_c	\
		,	::llc::vu0_t, ::llc::vu0_c, ::llc::vcu0_t, ::llc::vcu0_c	\
		,	::llc::vu1_t, ::llc::vu1_c, ::llc::vcu1_t, ::llc::vcu1_c	\
		,	::llc::vu2_t, ::llc::vu2_c, ::llc::vcu2_t, ::llc::vcu2_c	\
		,	::llc::vu3_t, ::llc::vu3_c, ::llc::vcu3_t, ::llc::vcu3_c	\
		,	::llc::vs0_t, ::llc::vs0_c, ::llc::vcs0_t, ::llc::vcs0_c	\
		,	::llc::vs1_t, ::llc::vs1_c, ::llc::vcs1_t, ::llc::vcs1_c	\
		,	::llc::vs2_t, ::llc::vs2_c, ::llc::vcs2_t, ::llc::vcs2_c	\
		,	::llc::vs3_t, ::llc::vs3_c, ::llc::vcs3_t, ::llc::vcs3_c	\
		,	::llc::vf2_t, ::llc::vf2_c, ::llc::vcf2_t, ::llc::vcf2_c	\
		,	::llc::vf3_t, ::llc::vf3_c, ::llc::vcf3_t, ::llc::vcf3_c

} // namespace

#endif // LLC_ARRAY_VIEW_H_23627
