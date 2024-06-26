#include "llc_log.h"
#include "llc_eval.h"

#ifndef LLC_ARRAY_VIEW_BIT_H_23627
#define LLC_ARRAY_VIEW_BIT_H_23627

namespace llc
{
#pragma pack(push, 1)
	tplt <tpnm _tInt>
	struct bit_proxy {
		typedef	_tInt			T;

		T						& Element;
		uint8_t					Offset;

		operator				bool			()				const	{ return Element & (1ULL << Offset); }
		bit_proxy&				operator=		(bool value)			{ value ? Element |= (1ULL << Offset) : Element &= ~(1ULL << Offset); return *this; }
	};

	tplt <tpnm _tInt>
	struct bit_iterator {
		typedef	_tInt			T;

		stacxpr	uint32_t		ELEMENT_BITS	= sizeof(T) * 8;

		const T					& Begin;
		const T					& End;
		T						* Element;
		uint8_t					Offset	: 4;
		uint8_t					Stop	: 4;

		bit_proxy<T>			operator*		()				{
			gthrow_if(Element == &End, "Invalid index: %" LLC_FMT_U32 ".", uint32_t(&Element - &Begin) + Offset);
			return {Element, (uint8_t)Offset};
		}
		
		bool					operator*		()		const	{
			gthrow_if(Element == &End, "Invalid index: %" LLC_FMT_U32 ".", uint32_t(&Element - &Begin) + Offset);
			return (*Element) & (1ULL << Offset);
		}

		inline	operator		bool			()									const				{ gthrow_if(Element == &End, "Invalid index: %" LLC_FMT_U32 ".", uint32_t(&Element - &Begin) + Offset); return (*Element) & (1ULL << Offset); }
		inlcxpr	bool			operator==		(const bit_iterator & other)		const	noexcept	{ return (((1ULL << Offset)) & *Element) == (((1ULL << other.Offset)) & *other.Element); }
		inlcxpr	bool			operator!=		(const bit_iterator & other)		const	noexcept	{ return (((1ULL << Offset)) & *Element) != (((1ULL << other.Offset)) & *other.Element); }

		inline	bit_iterator&	operator=		(bool value)	{ value ? *Element |= (1ULL << Offset)	: *Element &= ~(1ULL << Offset); return *this; }
		bit_iterator&			operator++		()				{ ++Offset; if(Offset >= ELEMENT_BITS)	{ ++Element; Offset = 0;				gthrow_if(Element >= (End   + 1), "Out of range: %" LLC_FMT_U32 ". End: %" LLC_FMT_U32 ".", Element, End  ); } return *this; }
		bit_iterator&			operator--		()				{ --Offset; if(Offset < 0)				{ --Element; Offset = ELEMENT_BITS - 1; gthrow_if(Element <  (Begin - 1), "Out of range: %" LLC_FMT_U32 ". End: %" LLC_FMT_U32 ".", Element, Begin); } return *this; }
		bit_iterator			operator++		(int)			{
			bit_iterator				result			(*this);	// Make a copy.
			++(*this);					// Use the prefix version to do the work.
			return result;				// Return the old value.
		}
		bit_iterator			operator--		(int)			{
			bit_iterator				result			(*this);	// Make a copy.
			--(*this);					// Use the prefix version to do the work.
			return result;				// Return the old value.
		}
	};

	tplt <tpnm _tInt>
	class view_bit {
	protected:
		// Properties / Member Variables
		_tInt					* Data			= 0;
		uint32_t				Count			= 0;
	public:
		typedef	_tInt			T;
		typedef	bit_iterator<T>	TIter;
		typedef	bit_iterator<const T>	TIterConst;
		typedef	TIter			iterator;

		stacxpr	uint8_t			ELEMENT_BITS	= sizeof(T) * 8;
		//stacxpr	uint8_t			SHIFT_VALUE		= ;

		// Constructors
		inlcxpr					view_bit		()							noexcept	= default;
		inline					view_bit		(T * data, uint32_t bitCount)			: Data(data), Count(bitCount) {
			gthrow_if(bitCount && 0 == data, "Invalid parameters. Element count: %" LLC_FMT_U32 ".", bitCount);	// Crash if we received invalid parameters in order to prevent further malfunctioning.
		}

		tplt <size_t _length>
		inlcxpr					view_bit		(T (&data)[_length])		noexcept	: Data(data), Count(_length * ELEMENT_BITS)											{}

		tplt <size_t _length>
		inline					view_bit		(T (&data)[_length], uint32_t bitCount)	: Data(data), Count(::llc::min(uint32_t(_length * ELEMENT_BITS), bitCount))	{
			gthrow_if(bitCount > (_length * ELEMENT_BITS), "Out of range count. Max count: %" LLC_FMT_U32 ". Requested: %" LLC_FMT_U32 ".", _length * ELEMENT_BITS, bitCount);
		}

		// Operators
		bit_proxy<T>			operator[]		(uint32_t index)			{
			gthrow_if(index >= Count, LLC_FMT_U32_GE_U32, index, Count);
			const uint32_t				offsetRow		= index / ELEMENT_BITS;
			const uint32_t				offsetBit		= index % ELEMENT_BITS;
			return {Data[offsetRow], (uint8_t)offsetBit};
		}

		bool					operator[]		(uint32_t index)	const	{
			gthrow_if(index >= Count, LLC_FMT_U32_GE_U32, index, Count);
			const uint32_t				offsetRow		= index / ELEMENT_BITS;
			const uint32_t				offsetBit		= index % ELEMENT_BITS;
			return Data[offsetRow] & (1ULL << offsetBit);
		}

		// Methods
		inline	TIter			begin			()			noexcept	{ return {*Data, *(Data + round_up(Count, ELEMENT_BITS)), Data, 0, Count % ELEMENT_BITS}; }
		inline	TIter			end				()			noexcept	{ return {*Data, *(Data + round_up(Count, ELEMENT_BITS)), Data + round_up(Count, ELEMENT_BITS), 0, Count % ELEMENT_BITS}; }
		//																		  *		 *(									   )  *
		inlcxpr	TIterConst		begin			()	const	noexcept	{ return {*Data, *(Data + round_up(Count, ELEMENT_BITS)), Data, 0, Count % ELEMENT_BITS}; }
		inlcxpr	TIterConst		end				()	const	noexcept	{ return {*Data, *(Data + round_up(Count, ELEMENT_BITS)), Data + round_up(Count, ELEMENT_BITS), 0, Count % ELEMENT_BITS}; }

		inlcxpr	const uint32_t&	size			()	const	noexcept	{ return Count; }
	};
#pragma pack(pop)

	tplt<tpnm T>	using vbit	= ::llc::view_bit<T>;
	typedef	::llc::view_bit<uint8_t>	vbitu8	;
	typedef	::llc::view_bit<uint16_t>	vbitu16	;
	typedef	::llc::view_bit<uint32_t>	vbitu32	;
	typedef	::llc::view_bit<uint64_t>	vbitu64	;

	tplt<tpnm _tField>
	::llc::error_t			reverse_bits		(::llc::view_bit<_tField> toReverse)													{
		const uint32_t				countBits			= toReverse.size() / 2;
		const uint32_t				lastBitIndex		= toReverse.size() - 1;
		for(uint32_t iBit = 0; iBit < countBits; ++iBit) {
			const uint32_t				iRev				= lastBitIndex - iBit;
			const bool					current				= toReverse[iBit];
			toReverse[iBit]			= (bool)toReverse[iRev];
			toReverse[iRev]			= current;
		}
		return 0;
	}

} // namespace

#endif // LLC_ARRAY_VIEW_BIT_H_23627
