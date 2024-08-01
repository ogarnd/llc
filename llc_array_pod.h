#include "llc_array_base.h"

#include "llc_keyval.h"

#include "llc_view_serialize.h"

#ifndef LLC_ARRAY_POD_H_23627
#define LLC_ARRAY_POD_H_23627

namespace llc
{
	// This class is optimized to contain POD instances and won't work for C++ objects that require calling constructors/destructors.
	tplt<tpnm _tPOD>
	struct array_pod : public array_base<_tPOD> {
		typedef	_tPOD			T						;
		typedef	view<T>			TView					;
		typedef	array_pod<T>	TArray					;

		using array_base<T>		::Count					;
		using array_base<T>		::Data					;
		using array_base<T>		::Size					;
		using array_base<T>		::alloc_with_reserve	;
		using array_base<T>		::find					;

		inlcxpr					array_pod			()										noexcept	= default;
								array_pod			(::std::initializer_list<T> init)				{
			gthrow_if(errored(resize((u2_t)init.size())), "init.size() -> %" LLC_FMT_U32 ".", (u2_t)init.size());
			memcpy(Data, init.begin(), Count * sizeof(T));
		}
								array_pod			(array_pod<T> && other)					noexcept	{
			Size					= other.Size;
			Count					= other.Count;
			Data					= other.Data;

			other.Size				= other.Count			= 0;
			other.Data				= 0;
		}
		inline					array_pod			(cnst array_pod<T> & other)						: array_pod((cnst view<cnst T>&) other) {}
								array_pod			(cnst view<cnst T> & other)						{
			gsthrow_if(resize(other.size()) != (s2_t)other.size());
			memcpy(Data, other.begin(), other.byte_count());
		}
		tplt<size_t _count>
								array_pod			(cnst T (&other)[_count])							{
			gsthrow_if(resize(_count) != (s2_t)_count);
			memcpy(Data, other, _count * sizeof(T));
		}
		inlcxpr	operator		view<cnst T>	()									cnst	noexcept	{ return {Data, Count}; }
		TArray&					operator =			(cnst array_pod<T>& other)							{ return operator=((cnst view<T> &) other); }
		TArray&					operator =			(cnst view<cnst T> & other)						{
			gsthrow_if(resize(other.size()) != (s2_t)other.size());
			if(Count)
				memcpy(Data, other.begin(), other.byte_count());
			return *this;
		}
		tplt<size_t sizeStatic>
		TArray&					operator =			(cnst T (&init)[sizeStatic])						{
			gsthrow_if(resize(sizeStatic) != sizeStatic);
			memcpy(Data, init, Count * sizeof(T));
			*(u1_t*)&Data[Count]		= 0;
			return *this;
		}

		inline	::llc::err_t	clear				()										noexcept	{ return Count = 0; }
		::llc::err_t			clear_pointer		()										noexcept	{ safe_llc_free(Data); Data = 0; return Size = Count = 0; }
		// Returns the new size of the array
		::llc::err_t			pop_back			()										noexcept	{
			rees_if(0 == Count);
			*(u1_t*)&Data[--Count]		= 0;
			return Count;
		}
		// Returns the new size of the array
		::llc::err_t			pop_back			(T & oldValue)							noexcept	{
			rees_if(0 == Count);
			oldValue				= Data[--Count];
			*(u1_t*)&Data[Count]		= 0;
			return Count;
		}
		// Returns the index of the pushed value or -1 on failure
		::llc::err_t			push_back			(cnst T & newValue)					noexcept	{
			cnst s2_t				oldSize				= Count;
			llc_necs(resize(oldSize + 1, newValue));
			return oldSize;
		}
		inline	::llc::err_t	append_string		(cnst llc::function<err_t(TArray&)> & funcAppend)	noexcept	{ return funcAppend ? funcAppend(*this) : 0; }
		tplt<size_t _len>
		inline	::llc::err_t	append_string		(cnst T (&newChain)[_len])							noexcept	{ return append(::llc::vcs{newChain}); }
		inline	::llc::err_t	append_string		(cnst ::llc::vcs & newChain)						noexcept	{ return append(newChain.begin(), newChain.size()); }
		inline	::llc::err_t	append_string		(cnst T & element)									noexcept	{ llc_necs(push_back(element)); return 1; }
		inline	::llc::err_t	append_strings		(cnst ::llc::view<cnst ::llc::vcs> & newChains)	noexcept	{ 
			s2_t					appended				= 0;
			for(u2_t i = 0, stop = newChains.size(); i < stop; ++i) {
				cnst ::llc::vcs & newChain = newChains[i];
				llc_necs(append(newChain));
				appended += newChain.size();
			}
			return appended;
		}
		tplt<size_t _len>
		inline	::llc::err_t	append				(cnst T (&newChain)[_len])									noexcept	{ return append(newChain, (u2_t)_len); }
		inline	::llc::err_t	append				(cnst ::llc::view<cnst T> & newChain)						noexcept	{ return append(newChain.begin(), newChain.size());	}
		inline	::llc::err_t	append				(cnst ::llc::view<cnst ::llc::view<cnst T>> & newChains)	noexcept	{ 
			s2_t count = 0;
			err_t err = 0;
			newChains.for_each([this, &count, &err](cnst view<cnst T> &newChain) { if(false == failed(err)) { if_fail_e(err = append(newChain)); count += newChain.size(); } }); 
			return failed(err) ? err : count;
		}
		::llc::err_t			append				(cnst T * chainToAppend, u2_t chainLength)				noexcept	{
			if(0 == chainLength)
				return Count;
			u2_c				newCount			= Count + chainLength;
			llc_necs(reserve(newCount));
			u2_c				iFirst				= Count;
			memcpy(&Data[iFirst], chainToAppend, sizeof(T) * chainLength);
			Count					+= chainLength;
			*(u1_t*)&Data[Count]		= 0;
			return iFirst;
		}
		::llc::err_t			reserve				(u2_t newCount)								{
			if(newCount > Size) {
				T							* newData			= 0;
				u2_c				newSize				= alloc_with_reserve(newCount, newData);
				rees_if(0 == newData);
				if(Data)
					memcpy(newData, Data, this->byte_count());
					
				*(u1_t*)&newData[Count]	= 0;
				T							* oldData			= Data;
				Data					= newData;
				Size					= newSize;
				::llc::llc_free(oldData);
			}
			return Size;
		}
		inline	::llc::err_t	resize_bits			(u2_t newBitCount)						noexcept	{
			stacxpr	u2_t			elementBits			= (u2_t)sizeof(T) * 8U;
			return resize(newBitCount / elementBits + one_if(newBitCount % elementBits));
		}
		// Returns the new size of the array.
		::llc::err_t			resize				(u2_t newCount)						noexcept	{
			llc_necs(reserve(newCount));
			Count					= newCount;
			if(Data)
				*(u1_t*)&Data[Count]		= 0;
			return Count;
		}
		// Returns the new size of the array.
		::llc::err_t			resize				(u2_t newCount, cnst T & newValue)	noexcept	{
			llc_necs(reserve(newCount));
			if(Data) {
				for(; Count < newCount; ++Count)
					Data[Count] = newValue;
				*(u1_t*)&Data[Count = newCount]	= 0;
			}
			return Count;
		}
		// returns the new size of the list or -1 on failure.
		::llc::err_t			insert				(u2_t index, cnst T & newValue)	noexcept	{
			ree_if(index > Count, LLC_FMT_U32_GT_U32, index, Count);
			u2_c				newCount			= Count + 1;
			if(Size < newCount) {
				T							* newData			= 0;
				u2_c				newSize				= alloc_with_reserve(newCount, newData);
				rees_if(0 == newData);
				if(Data)
					memcpy(newData, Data, index * sizeof(T));
				newData[index]			= newValue;
				if(Data)
					memcpy(&newData[index + 1], &Data[index], (Count - index) * sizeof(T));
				T							* oldData			= Data;
				Data					= newData;
				Size					= newSize;
				::llc::llc_free(oldData);
			}
			else {
				for(s2_t i = (int)Count - 1; i >= (int)index; --i)
					Data[i + 1]				= Data[i];
				Data[index]				= newValue;
			}
			*(u1_t*)&Data[newCount]	= 0;
			return Count = newCount;
		}
		// returns the new size of the list or -1 on failure.
		::llc::err_t			insert				(u2_t index, cnst T * chainToInsert, u2_t chainLength)	noexcept	{
			ree_if(index > Count, LLC_FMT_U32_GT_U32, index, Count);

			u2_c				newCount			= Count + chainLength;
			if(Size < newCount) {
				T							* newData			= 0;
				u2_c				newSize				= alloc_with_reserve(newCount, newData);
				rees_if(0 == newData);
				if(Data)
					memcpy(newData, Data, index * sizeof(T));
				memcpy(&newData[index], chainToInsert, chainLength * sizeof(T));
				if(Data)
					memcpy(&newData[index + chainLength], &Data[index], (Count - index) * sizeof(T));
				T							* oldData			= Data;
				Data					= newData;
				Size					= newSize;
				::llc::llc_free(oldData);
			}
			else {	// no need to reallocate and copy, just shift rightmost elements and insert in-place
				for(s2_t i = (int)Count - 1; i >= (int)index; --i)
					Data[i + chainLength]	= Data[i];
				memcpy(&Data[index], chainToInsert, chainLength * sizeof(T));
			}
			*(u1_t*)&Data[newCount]	= 0;
			return Count = newCount;
		}
		tplt<size_t _chainLength>
		inline	::llc::err_t	insert				(u2_t index, cnst T (&chainToInsert)[_chainLength])		noexcept	{ return insert(index, chainToInsert, (u2_t)_chainLength); }
		inline	::llc::err_t	insert				(u2_t index, ::llc::view<cnst T> chainToInsert)			noexcept	{ return insert(index, chainToInsert.begin(), chainToInsert.size()); }
		// Returns the new size of the list or -1 if the array pointer is not initialized.
		::llc::err_t			remove_unordered	(u2_t index)												noexcept	{
			ree_if(index >= Count, LLC_FMT_U32_GE_U32, index, Count);
			Data[index]				= Data[--Count];
			*(u1_t*)&Data[Count]		= 0;
			return Count;
		}
		// returns the new array size or -1 if failed.
		::llc::err_t			erase				(cnst T * address)												noexcept	{
			cnst ptrdiff_t				ptrDiff				= ptrdiff_t(address) - (ptrdiff_t)Data;
			u2_c				index				= (u2_t)(ptrDiff / (ptrdiff_t)sizeof(T));
			ree_if(index >= Count, LLC_FMT_U32_GE_U32 ", p: 0x%p", index, Count, address);
			return remove(index);
		}
		// returns the new array size or -1 if failed.
		::llc::err_t			remove				(u2_t index)													noexcept	{
			ree_if(index >= Count, LLC_FMT_U32_GE_U32, index, Count);
			--Count;
			while(index < Count) {
				Data[index]				= Data[index + 1];
				++index;
			}
			*(u1_t*)&Data[Count]		= 0;
			return Count;
		}
	}; // array_pod

	tplt <tpnm T>	using apod		= ::llc::array_pod<T>;
	tplt <tpnm T>	using ap		= ::llc::apod	<T>;

	typedef	apod<uc_t>	auc_t;	tydfcnst	auc_t	auc_c;
	typedef	apod<sc_t>	asc_t;	tydfcnst	asc_t	asc_c;
	typedef	apod<u0_t>	au0_t;	tydfcnst	au0_t	au0_c;
	typedef	apod<u1_t>	au1_t;	tydfcnst	au1_t	au1_c;
	typedef	apod<u2_t>	au2_t;	tydfcnst	au2_t	au2_c;
	typedef	apod<u3_t>	au3_t;	tydfcnst	au3_t	au3_c;
	typedef	apod<s0_t>	as0_t;	tydfcnst	as0_t	as0_c;
	typedef	apod<s1_t>	as1_t;	tydfcnst	as1_t	as1_c;
	typedef	apod<s2_t>	as2_t;	tydfcnst	as2_t	as2_c;
	typedef	apod<s3_t>	as3_t;	tydfcnst	as3_t	as3_c;
	typedef	apod<f2_t>	af2_t;	tydfcnst	af2_t	af2_c;
	typedef	apod<f3_t>	af3_t;	tydfcnst	af3_t	af3_c;

	llc::asc_t				toString		(cnst ::llc::vcc & strToLog);

	::llc::err_t			camelCase		(::llc::vcc input, ::llc::asc_t & camelCased);

	::llc::err_t			join			(::llc::asc_t & query, char separator, ::llc::vcvsc_t fields);
} // namespace

#endif // LLC_ARRAY_POD_H_23627
