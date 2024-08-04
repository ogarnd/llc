#include "llc_array_base.h"

#include "llc_keyval.h"

#include "llc_view_serialize.h"

#ifndef LLC_ARRAY_POD_H_23627
#define LLC_ARRAY_POD_H_23627

namespace llc
{
	// This class is optimized to contain POD instances and won't work for C++ objects that require calling constructors/destructors.
	tpl_tstct array_pod : public array_base<_t> {
		tdfTTCnst(_t);
		tydf	view<T>			TView					;
		tydf	array_pod<T>	TArray					;

		usng array_base<T>		::Count					;
		usng array_base<T>		::Data					;
		usng array_base<T>		::Size					;
		usng array_base<T>		::alloc_with_reserve	;
		usng array_base<T>		::find					;

		inxp					array_pod			()										noexcept	= default;
								array_pod			(::std::initializer_list<T> init)				{
			gthrow_if(failed(resize((u2_t)init.size())), "init.size() -> %" LLC_FMT_U2 ".", (u2_t)init.size());
			memcpy(Data, init.begin(), Count * szof(T));
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
			memcpy(Data, other, _count * szof(T));
		}
		inxp	oper		view<cnst T>	()									cnst	noexcept	{ return {Data, Count}; }
		TArray&					oper =			(cnst array_pod<T>& other)							{ return oper=((cnst view<T> &) other); }
		TArray&					oper =			(cnst view<cnst T> & other)						{
			gsthrow_if(resize(other.size()) != (s2_t)other.size());
			if(Count)
				memcpy(Data, other.begin(), other.byte_count());
			return *this;
		}
		tplt<size_t sizeStatic>
		TArray&					oper =			(cnst T (&init)[sizeStatic])						{
			gsthrow_if(resize(sizeStatic) != sizeStatic);
			memcpy(Data, init, Count * szof(T));
			*(u1_t*)&Data[Count]		= 0;
			return *this;
		}

		inln	err_t	clear				()										noexcept	{ return Count = 0; }
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
		inln	err_t	append_string		(cnst llc::function<err_t(TArray&)> & funcAppend)	noexcept	{ return funcAppend ? funcAppend(*this) : 0; }
		tplt<size_t _len>
		inln	err_t	append_string		(cnst T (&newChain)[_len])							noexcept	{ return append(::llc::vcs{newChain}); }
		inln	err_t	append_string		(cnst ::llc::vcs & newChain)						noexcept	{ return append(newChain.begin(), newChain.size()); }
		inln	err_t	append_string		(cnst T & element)									noexcept	{ llc_necs(push_back(element)); return 1; }
		inln	err_t	append_strings		(cnst ::llc::view<cnst ::llc::vcs> & newChains)	noexcept	{ 
			s2_t					appended				= 0;
			for(u2_t i = 0, stop = newChains.size(); i < stop; ++i) {
				cnst ::llc::vcs & newChain = newChains[i];
				llc_necs(append(newChain));
				appended += newChain.size();
			}
			return appended;
		}
		tplt<size_t _len>
		inln	err_t	append				(cnst T (&newChain)[_len])									noexcept	{ return append(newChain, (u2_t)_len); }
		inln	err_t	append				(cnst ::llc::view<cnst T> & newChain)						noexcept	{ return append(newChain.begin(), newChain.size());	}
		inln	err_t	append				(cnst ::llc::view<cnst ::llc::view<cnst T>> & newChains)	noexcept	{ 
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
			memcpy(&Data[iFirst], chainToAppend, szof(T) * chainLength);
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
		inln	err_t	resize_bits			(u2_t newBitCount)						noexcept	{
			stxp u2_t					elementBits			= (u2_t)szof(T) * 8U;
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
			ree_if(index > Count, LLC_FMT_GT_U2, index, Count);
			u2_c				newCount			= Count + 1;
			if(Size < newCount) {
				T							* newData			= 0;
				u2_c				newSize				= alloc_with_reserve(newCount, newData);
				rees_if(0 == newData);
				if(Data)
					memcpy(newData, Data, index * szof(T));
				newData[index]			= newValue;
				if(Data)
					memcpy(&newData[index + 1], &Data[index], (Count - index) * szof(T));
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
			ree_if(index > Count, LLC_FMT_GT_U2, index, Count);

			u2_c				newCount			= Count + chainLength;
			if(Size < newCount) {
				T							* newData			= 0;
				u2_c				newSize				= alloc_with_reserve(newCount, newData);
				rees_if(0 == newData);
				if(Data)
					memcpy(newData, Data, index * szof(T));
				memcpy(&newData[index], chainToInsert, chainLength * szof(T));
				if(Data)
					memcpy(&newData[index + chainLength], &Data[index], (Count - index) * szof(T));
				T							* oldData			= Data;
				Data					= newData;
				Size					= newSize;
				::llc::llc_free(oldData);
			}
			else {	// no need to reallocate and copy, just shift rightmost elements and insert in-place
				for(s2_t i = (int)Count - 1; i >= (int)index; --i)
					Data[i + chainLength]	= Data[i];
				memcpy(&Data[index], chainToInsert, chainLength * szof(T));
			}
			*(u1_t*)&Data[newCount]	= 0;
			return Count = newCount;
		}
		tplt<size_t _chainLength>
		inln	err_t	insert				(u2_t index, cnst T (&chainToInsert)[_chainLength])		noexcept	{ return insert(index, chainToInsert, (u2_t)_chainLength); }
		inln	err_t	insert				(u2_t index, ::llc::view<cnst T> chainToInsert)			noexcept	{ return insert(index, chainToInsert.begin(), chainToInsert.size()); }
		// Returns the new size of the list or -1 if the array pointer is not initialized.
		::llc::err_t			remove_unordered	(u2_t index)												noexcept	{
			ree_if(index >= Count, LLC_FMT_GE_U2, index, Count);
			Data[index]				= Data[--Count];
			*(u1_t*)&Data[Count]		= 0;
			return Count;
		}
		// returns the new array size or -1 if failed.
		::llc::err_t			erase				(cnst T * address)												noexcept	{
			cnst ptrdiff_t				ptrDiff				= ptrdiff_t(address) - (ptrdiff_t)Data;
			u2_c				index				= (u2_t)(ptrDiff / (ptrdiff_t)szof(T));
			ree_if(index >= Count, LLC_FMT_GE_U2 ", p: 0x%p", index, Count, address);
			return remove(index);
		}
		// returns the new array size or -1 if failed.
		::llc::err_t			remove				(u2_t index)													noexcept	{
			ree_if(index >= Count, LLC_FMT_GE_U2, index, Count);
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

	tydf	apod<uc_t>	auc_t;	tdcs	auc_t	auc_c;
	tydf	apod<sc_t>	asc_t;	tdcs	asc_t	asc_c;
	tydf	apod<u0_t>	au0_t;	tdcs	au0_t	au0_c;
	tydf	apod<u1_t>	au1_t;	tdcs	au1_t	au1_c;
	tydf	apod<u2_t>	au2_t;	tdcs	au2_t	au2_c;
	tydf	apod<u3_t>	au3_t;	tdcs	au3_t	au3_c;
	tydf	apod<s0_t>	as0_t;	tdcs	as0_t	as0_c;
	tydf	apod<s1_t>	as1_t;	tdcs	as1_t	as1_c;
	tydf	apod<s2_t>	as2_t;	tdcs	as2_t	as2_c;
	tydf	apod<s3_t>	as3_t;	tdcs	as3_t	as3_c;
	tydf	apod<f2_t>	af2_t;	tdcs	af2_t	af2_c;
	tydf	apod<f3_t>	af3_t;	tdcs	af3_t	af3_c;

	llc::asc_t				toString		(cnst ::llc::vcc & strToLog);

	::llc::err_t			camelCase		(::llc::vcc input, ::llc::asc_t & camelCased);

	::llc::err_t			join			(::llc::asc_t & query, char separator, ::llc::vcvsc_t fields);
} // namespace

#endif // LLC_ARRAY_POD_H_23627
