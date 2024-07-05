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
		inlcxpr					view			(uint32_t elementCount, T (&elements)[Len])		: Data(elements), Count(::llc::min((uint32_t)Len, elementCount))	{}
		inline					view			(T * elements, uint32_t elementCount)			: Data(elements), Count(elementCount)								{
			gthrow_if(0 == elements && 0 != elementCount, "%" LLC_FMT_U32 " -> 0.", elementCount);	// Crash if we received invalid parameters in order to prevent further malfunctioning.
		}

		tplt <size_t Len>
		inline					view			(T (&elements)[Len], uint32_t elementCount)		: Data(elements), Count(::llc::min((uint32_t)Len, elementCount))	{
			gthrow_if(elementCount > Len, LLC_FMT_U32_GT_U32, elementCount, (uint32_t)Len);
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
		inlcxpr	uint32_t		bit_count		()							const	noexcept	{ return byte_count() * 8U;	}

		inline	view<uint8_t>	u8				()									noexcept	{ return {(uint8_t*)Data, byte_count()};		}
		inlcxpr	view<cuint8_t>	u8				()							const	noexcept	{ return {(const uint8_t*)Data, byte_count()};	}
		inlcxpr	view<cuint8_t>	cu8				()							const	noexcept	{ return {(const uint8_t*)Data, byte_count()};	}
		inline	view<char>		c				()									noexcept	{ return {(char*)Data, byte_count()};			}
		inlcxpr	view<cchar_t>	cc				()							const	noexcept	{ return {(const char*)Data, byte_count()};		}

		inlcxpr	const T*		begin			()							const	noexcept	{ return Data;			}
		inlcxpr	const T*		end				()							const	noexcept	{ return Data + Count;	}
		inlcxpr	const uint32_t&	size			()							const	noexcept	{ return Count;			}

		inline	T*				begin			()									noexcept	{ return Data;			}
		inline	T*				end				()									noexcept	{ return Data + Count;	}

		::llc::error_t			slice			(TView & out, uint32_t offset, uint32_t count = (uint32_t)-1)				{
			reterr_gerror_if(offset > Count, LLC_FMT_U32_GT_U32, offset, (uint32_t)Count);
			const uint32_t				newSize			= Count - offset;
			if(count != (uint32_t)-1)
				ree_if(count > newSize, LLC_FMT_U32_GT_U32, count, (uint32_t)newSize);
			out						= {&Data[offset], ::llc::min(newSize, count)};
			return out.size();
		}
		::llc::error_t			slice			(TConstView & out, uint32_t offset, uint32_t count = (uint32_t)-1)	const	{
			ree_if(offset > Count, LLC_FMT_U32_GT_U32, offset, (uint32_t)Count);
			const uint32_t				newSize			= Count - offset;
			if(count != (uint32_t)-1)
				ree_if(count > newSize, LLC_FMT_U32_GT_U32, count, (uint32_t)newSize);
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

		tplt<tpnm _tMax> ::llc::error_t	max	(_tMax & maxFound, const FTransform<_tMax, const T &> & funcComparand, uint32_t offset = 0)	const	{ int32_t iMax = 0; for(; offset < Count; ++offset) { _tMax value = funcComparand(Data[offset]); if(value > maxFound) { iMax = offset; maxFound = value; } } return iMax; }
		tplt<tpnm _tMax> ::llc::error_t	min	(_tMax & minFound, const FTransform<_tMax, const T &> & funcComparand, uint32_t offset = 0)	const	{ int32_t iMin = 0; for(; offset < Count; ++offset) { _tMax value = funcComparand(Data[offset]); if(value < minFound) { iMin = offset; minFound = value; } } return iMin; }
		tplt<tpnm _tMax> ::llc::error_t	max	(const FTransform<_tMax, const T &> & funcComparand, uint32_t offset = 0)					const	{ _tMax maxFound; return max(maxFound, funcComparand, offset); }
		tplt<tpnm _tMax> ::llc::error_t	min	(const FTransform<_tMax, const T &> & funcComparand, uint32_t offset = 0)					const	{ _tMax minFound; return min(minFound, funcComparand, offset); }
	}; // view<>

	tplt<tpnm T>	using	view_array	= ::llc::view<T>;
	tplt<tpnm T>	using	view1d		= ::llc::view<T>;
	tplt<tpnm T>	using	v1			= ::llc::view<T>;

	tplt<tpnm T>	ndstinx	uint32_t	size		(const ::llc::view<T> & viewToTest)	noexcept	{ return viewToTest.size();			}
	tplt<tpnm T>	ndstinx	uint32_t	byte_count	(const ::llc::view<T> & viewToTest)	noexcept	{ return viewToTest.byte_count();	}

#pragma pack(pop)

	typedef	::llc::view<::llc::uchar_t		>	vuc, vuchar;
	typedef	::llc::view<char				>	vc, vchar;
	typedef	::llc::view<float				>	vf32;
	typedef	::llc::view<double				>	vf64;
	typedef	::llc::view<uint8_t				>	vu8;
	typedef	::llc::view<uint16_t			>	vu16;
	typedef	::llc::view<uint32_t			>	vu32;
	typedef	::llc::view<uint64_t			>	vu64;
	typedef	::llc::view<int8_t				>	vi8;
	typedef	::llc::view<int16_t				>	vi16;
	typedef	::llc::view<int32_t				>	vi32;
	typedef	::llc::view<int64_t				>	vi64;

	typedef	::llc::view<const ::llc::uchar_t>	vcuc, vcuchar;
	typedef	::llc::view<const char			>	vcc, vcchar;
	typedef	::llc::view<const float			>	vcf32;
	typedef	::llc::view<const double		>	vcf64;
	typedef	::llc::view<const uint8_t		>	vcu8;
	typedef	::llc::view<const uint16_t		>	vcu16;
	typedef	::llc::view<const uint32_t		>	vcu32;
	typedef	::llc::view<const uint64_t		>	vcu64;
	typedef	::llc::view<const int8_t		>	vci8;
	typedef	::llc::view<const int16_t		>	vci16;
	typedef	::llc::view<const int32_t		>	vci32;
	typedef	::llc::view<const int64_t		>	vci64;

// Use this to initialize a constexpr vcs from a string literal
#define LLC_CXS(constexpr_string_literal) ::llc::vcc{uint32_t(sizeof(constexpr_string_literal) - 1), constexpr_string_literal}

	typedef	::llc::view<vuc		>	vvuc;
	typedef	::llc::view<vc		>	vvc;
	typedef	::llc::view<vu8		>	vvu8;
	typedef	::llc::view<vu16	>	vvu16;
	typedef	::llc::view<vu32	>	vvu32;
	typedef	::llc::view<vu64	>	vvu64;
	typedef	::llc::view<vi8		>	vvi8;
	typedef	::llc::view<vi16	>	vvi16;
	typedef	::llc::view<vi32	>	vvi32;
	typedef	::llc::view<vi64	>	vvi64;
	typedef	::llc::view<vf32	>	vvf32;
	typedef	::llc::view<vf64	>	vvf64;

	typedef	::llc::view<const vcuc	>	vcvcuc;
	typedef	::llc::view<const vcc	>	vcvcc;
	typedef	::llc::view<const vcu8	>	vcvcu8;
	typedef	::llc::view<const vcu16	>	vcvcu16;
	typedef	::llc::view<const vcu32	>	vcvcu32;
	typedef	::llc::view<const vcu64	>	vcvcu64;
	typedef	::llc::view<const vci8	>	vcvci8;
	typedef	::llc::view<const vci16	>	vcvci16;
	typedef	::llc::view<const vci32	>	vcvci32;
	typedef	::llc::view<const vci64	>	vcvci64;
	typedef	::llc::view<const vcf32	>	vcvcf32;
	typedef	::llc::view<const vcf64	>	vcvcf64;

	typedef	::llc::view<vcuc	>	vvcuc;
	typedef	::llc::view<vcc		>	vvcc;
	typedef	::llc::view<vcu8	>	vvcu8;
	typedef	::llc::view<vcu16	>	vvcu16;
	typedef	::llc::view<vcu32	>	vvcu32;
	typedef	::llc::view<vcu64	>	vvcu64;
	typedef	::llc::view<vci8	>	vvci8;
	typedef	::llc::view<vci16	>	vvci16;
	typedef	::llc::view<vci32	>	vvci32;
	typedef	::llc::view<vci64	>	vvci64;
	typedef	::llc::view<vcf32	>	vvcf32;
	typedef	::llc::view<vcf64	>	vvcf64;

	stacxpr	::llc::vcc	VCC_NULL		= {4, "null"};
	stacxpr	::llc::vcc	VCC_TRUE		= {4, "true"};
	stacxpr	::llc::vcc	VCC_FALSE		= {5, "false"};

	ndstinx	::llc::vcc	bool2vcc		(bool b)		{ return b ? ::llc::VCC_TRUE : ::llc::VCC_FALSE; }
	ndstinx	const char*	bool2char		(bool b)		{ return b ? ::llc::VCC_TRUE.begin() : ::llc::VCC_FALSE.begin(); }
	ndstinx	uint8_t		bool2u8			(bool b)		{ return b ? 1 : 0; }
	ndstinx	uint8_t		bool2i8			(bool b)		{ return b ? 1 : 0; }
	stainli	const char*	bool2char		(bool b, ::llc::vcc & output)	{ return (output = b ? ::llc::VCC_TRUE : ::llc::VCC_FALSE).begin(); }
	stainli	bool		vcc2bool		(::llc::vcc b)	{ return b.size() && b != VCC_FALSE; }


	struct view_string : public view<char> {
		inlcxpr			view_string				()													= default;
		inlcxpr			view_string				(const view<char> & other)				noexcept	: view(other)				{}
						view_string				(char * inputString, uint32_t length)				: view(inputString, length)	{ Count = (length == (uint32_t)-1) ? (uint32_t)strlen(inputString) : length;					}
		tplt<u32 Len>	view_string				(char (&inputString)[Len])				noexcept	: view(inputString)			{ Count = (uint32_t)strnlen(inputString, (uint32_t)Len);								}
		tplt<u32 Len>	view_string				(char (&inputString)[Len], uint32_t length)			: view(inputString, length)	{ if(length == (uint32_t)-1) Count = (uint32_t)strnlen(inputString, (uint32_t)Len);	}
	};

	struct view_const_string : public view<const char> {
		inlcxpr				view_const_string		()													: view(0, "") 				{}
		inlcxpr				view_const_string		(const view<const char> & other)		noexcept	: view(other)				{}
		tplt<u32 Len>		view_const_string		(const char (&inputString)[Len])		noexcept	: view(inputString)			{ Count = (uint32_t)strnlen(inputString, (uint32_t)Len);								}
		tplt<u32 Len>		view_const_string		(const char (&inputString)[Len], uint32_t length)	: view(inputString, length)	{ if(length == (uint32_t)-1) Count = (uint32_t)strnlen(inputString, (uint32_t)Len);	}
							view_const_string		(const char* inputString, uint32_t length)			: view(inputString ? inputString : "", length)	{
			if(length == (uint32_t)-1) 
				Count 				= (uint32_t)strlen(begin());
		}

		inlcxpr	cchar_t*	begin					()	const	noexcept	{ return (Data && Count) ? Data : ""; }
		inlcxpr	cchar_t*	end						()	const	noexcept	{ return (Data && Count) ? Data + Count : begin() + 1; }
		ndinlne operator	const char* 			()  const  	noexcept	{ return begin(); }
	};

	typedef	::llc::view_string					vs;
	typedef	::llc::view_const_string			vcs;

	stainli llc::vcs		str					(const llc::vcs & arg)	{ return arg; } 
	stainli llc::vcs		str					(const llc::vs & arg)	{ return arg.cc(); } 

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
				return (int32_t)iOffset;
		return -1;
	}

	tplt<tpnm T>
	::llc::error_t					rfind					(const T & valueToFind, const ::llc::view<const T> & target, int32_t offset = 0)		{
		for(uint32_t iOffset = target.size() - 1 - offset; iOffset < target.size(); --iOffset)
			if(valueToFind == target[iOffset])
				return iOffset;
		return -1;
	}

	tplt<tpnm T>
	::llc::error_t					find_sequence_obj		(const ::llc::view<T> & sequence, const ::llc::view<T> & target, uint32_t offset = 0)	{
		for(int32_t iOffset = (int32_t)offset, offsetStop = ((int32_t)target.size() - sequence.size()) + 1; iOffset < offsetStop; ++iOffset) {
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
		for(int32_t iOffset = (int32_t)(target.size() - sequence.size() - offset); iOffset >= 0; --iOffset) {
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
		for(int32_t iOffset = (int32_t)offset, offsetStop = ((int32_t)target.size() - sequence.size()) + 1; iOffset < offsetStop; ++iOffset)
			if(0 == memcmp(sequence.begin(), &target[iOffset], sequence.size() * sizeof(T)))
				return iOffset;
		return -1;
	}

	tplt<tpnm T>
	::llc::error_t					rfind_sequence_pod		(const ::llc::view<T> & sequence, const ::llc::view<T>& target, uint32_t offset = 0)	{
		for(int32_t iOffset = (int32_t)(target.size() - sequence.size() - offset); iOffset >= 0; --iOffset)
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
			llc_necs(original.slice(left, 0, (uint32_t)iValue));
			llc_necs(original.slice(right, iValue, (uint32_t)original.size() - iValue));
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
			llc_necall(original.slice(left, 0, (uint32_t)iValue), "%s", "Invalid slice");
			llc_necall(original.slice(right, iValue, (uint32_t)original.size() - iValue), "%s", "Invalid slice");
		}
		return iValue;
	}

	tplt<tpnm T>
	::llc::error_t					max						(::llc::view<T> input, T ** result) {
		ree_if(0 == input.size(), "%s", "Cannot get reference to max element of an empty array.");
		*result							= &input[0];
		int32_t								iMax					= 0;
		for(uint32_t iElement = 1; iElement < input.size(); ++iElement) {
			const T						& currentElement		= input[iElement];
			if(currentElement > **result) {
				*result							= &currentElement;
				iMax							= iElement;
			}
		}
		return iMax;
	}

	tplt<tpnm T>
	::llc::error_t					min						(::llc::view<T> input, T ** result) {
		ree_if(0 == input.size(), "%s", "Cannot get reference to max element of an empty array.");
		*result							= &input[0];
		int32_t								iMin					= 0;
		for(uint32_t iElement = 1; iElement < input.size(); ++iElement) {
			const T						& currentElement		= input[iElement];
			if(currentElement < **result) {
				*result							= &currentElement;
				iMin							= iElement;
			}
		}
		return iMin;
	}

	tplt<tpnm T>
	T&							max						(::llc::view<T> input) {
		T								* result				= 0;
		gthrow_if(errored(::llc::max(input, &result)), "%s", "");
		return *result;
	}

	tplt<tpnm T>
	T&							min						(::llc::view<T> input) {
		T								* result				= 0;
		gthrow_if(errored(::llc::min(input, &result)), "%s", "");
		return *result;
	}

	tplt<tpnm TNumber>	
	TNumber					sum						(::llc::view<const TNumber> input)			{
		TNumber 				result 					= 0;
		input.for_each([&result](TNumber number) { result += number; });
		return result;
	}
	

#define be2le_16(number) ::llc::reverse<uint8_t>({(uint8_t*)&number, 2})
#define be2le_32(number) ::llc::reverse<uint8_t>({(uint8_t*)&number, 4})
#define be2le_64(number) ::llc::reverse<uint8_t>({(uint8_t*)&number, 8})
} // namespace

#endif // LLC_ARRAY_VIEW_H_23627
