#include "llc_array_base.h"

#include "llc_keyval.h"

#ifndef LLC_ARRAY_OBJ_H_23627
#define LLC_ARRAY_OBJ_H_23627

namespace llc
{
	tplt<tpnm _tObj>
	struct array_obj : public array_base<_tObj> {
		tydf	_tObj			T						;
		tydf	view<T>			TView					;
		tydf	array_obj<T>	TArray					;

		using array_base<T>		::Count					;
		using array_base<T>		::Data					;
		using array_base<T>		::Size					;
		using array_base<T>		::alloc_with_reserve	;

		inline					~array_obj			()			{ for(uint32_t i = 0; i < Count; ++i) Data[i].~T(); }	// dtor

		inxp					array_obj			()			= default;
		inline					array_obj			(TArray&& other)											noexcept	{
			Size					= other.Size;
			Count					= other.Count;
			Data					= other.Data;

			other.Size = other.Count	= 0;
			other.Data				= 0;
		}	// move ctor
								array_obj			(const TArray & other)			: array_obj((const view<const T>&) other)	{}
								array_obj			(const view<const T> & other)										{
			uint32_t					newCount			= other.size();
			if(newCount) {
				gthrow_if(errored(reserve(newCount)), "Requested size: %" LLC_FMT_U2 ". ", (uint32_t)newCount);
				for(; Count < newCount; ++Count)
					new (&Data[Count]) T(other.begin()[Count]);
			}
		}
								array_obj			(const view<T> & other)												{
			uint32_t					newCount			= other.size();
			if(newCount) {
				gthrow_if(errored(reserve(newCount)), "Requested size: %" LLC_FMT_U2 ". ", (uint32_t)newCount);
				for(; Count < newCount; ++Count)
					new (&Data[Count]) T(other.begin()[Count]);
			}
		}
								array_obj			(::std::initializer_list<T> init)				{
			gthrow_if(errored(append(init.begin(), (uint32_t)init.size())), "Failed to resize array! Why? Initializer list size: %" LLC_FMT_U2 ".", (uint32_t)init.size());
		}
		tplt<size_t _count>
								array_obj			(const T (&other)[_count])							{
			gthrow_if(errored(append(other, (uint32_t)_count)), "Failed to resize array! Why? Initializer list size: %" LLC_FMT_U2 ".", (uint32_t)_count);
		}
		inxp	oper		view<const T>		()									const	noexcept	{ return {Data, Count}; }
		inline	TArray&			oper=			(const TArray & other)									{
			gsthrow_if(resize(other.size()) != (int32_t)other.size());
			for(uint32_t iElement = 0; iElement < Count; ++iElement)
				Data[iElement]			= other[iElement];
			return *this;
		}
		::llc::error_t			clear				()														{ for(uint32_t i = 0; i < Count; ++i) Data[i].~T(); return Count = 0; }
		::llc::error_t			clear_pointer		()											noexcept	{ clear(); safe_llc_free(Data); return Size = 0; }

		::llc::error_t			reserve				(uint32_t newCount)										{
			if(newCount > Size) {
				T							* newData			= 0;
				u2_c				newSize				= alloc_with_reserve(newCount, newData);
				ree_if(0 == newData, "newCount: %" LLC_FMT_S2 ", newSize: %" LLC_FMT_S2 "", newCount, newSize);
				for(uint32_t iElement = 0; iElement < Count; ++iElement) {
					new (&newData[iElement]) T(Data[iElement]);
					Data[iElement].~T();
				}
				T						* oldData			= Data;
				Data					= newData;
				Size					= newSize;
				::llc::llc_free(oldData);
			}
			return Size;
		}

		// Returns the new size of the array.
		::llc::error_t			resize				(uint32_t newCount)															noexcept	{
			llc_necs(reserve(newCount));
			for(; Count < newCount; ++Count)
				new (&Data[Count]) T{};
			for(; Count > newCount; --Count)
				Data[Count - 1].~T();
			return Count;
		}

		// Returns the new size of the array.
		::llc::error_t			resize				(uint32_t newCount, const T & newValue)									noexcept	{
			llc_necs(reserve(newCount));
			for(; Count < newCount; ++Count)
				new (&Data[Count]) T{newValue};
			for(; Count > newCount; --Count)
				Data[Count - 1].~T();
			return Count;
		}

		// Returns the new size of the array.
		tplt <tpnm... _tArgs>
		::llc::error_t			resize				(uint32_t newCount, _tArgs&&... constructorArgs)											{
			llc_necs(reserve(newCount));
			for(; Count < newCount; ++Count)
				new (&Data[Count]) T{constructorArgs...};
			for(; Count > newCount; --Count)
				Data[Count - 1].~T();
			return Count;
		}

		// Returns the new size of the array
		inline	::llc::error_t	pop_back			()											noexcept	{
			ree_if(0 == Count, "%s", "Cannot pop elements of an empty array.");
			Data[--Count].~T();
			return Count;
		}

		// Returns the new size of the array
		inline	::llc::error_t	pop_back			(T & oldValue)								noexcept	{
			ree_if(0 == Count, "%s", "Cannot pop elements of an empty array.");
			oldValue				= Data[--Count];
			Data[Count].~T();
			return Count;
		}

		// Returns the index of the pushed value or -1 on failure
		::llc::error_t			push_back			(const T & newValue)														noexcept	{
			const int32_t				oldSize				= Count;
			llc_necs(resize(oldSize + 1, newValue));
			return oldSize;
		}

		// returns the new array size or -1 if failed.
		inline	::llc::error_t	erase				(const T * address)																	{
			ree_if(0 == Data, "Uninitialized array pointer! Invalid address to erase: %p.", address);
			const ptrdiff_t				ptrDiff				= ptrdiff_t(address) - (ptrdiff_t)Data;
			u2_c				index				= (uint32_t)(ptrDiff / (ptrdiff_t)szof(T));
			ree_if(index >= Count, LLC_FMT_GE_U2, index, Count);
			return remove(index);
		}

		::llc::error_t			remove				(uint32_t index)																		{
			ree_if(0 == Data, "Uninitialized array pointer! Invalid index to erase: %" LLC_FMT_U2 ".", index);
			ree_if(index >= Count, LLC_FMT_GE_U2, index, Count);
			--Count;
			while(index < Count) {
				Data[index].~T();							// Destroy old
				new (&Data[index]) T(Data[index + 1]);		// Placement new
				++index;
			}
			Data[index].~T();							// Destroy last
			return Count;
		}

		// Returns the new size of the list or -1 if the array pointer is not initialized.
		::llc::error_t			remove_unordered	(uint32_t index)																		{
			ree_if(0 == Data, "Uninitialized array pointer! Invalid index to erase: %" LLC_FMT_U2 ".", index);
			ree_if(index >= Count, LLC_FMT_GE_U2, index, Count);
			Data[index].~T();							// Destroy old
			if(1 == Count || index == (Count - 1))
				--Count;
			else {
				new (&Data[index]) T(Data[--Count]);	// Placement new
				Data[Count].~T();						// Destroy reordered
			}

			return Count;
		}
		tplt<size_t _len>
		inline	::llc::error_t	append				(const T (&newChain)[_len])							noexcept	{ return append(newChain, (uint32_t)_len); }
		inline	::llc::error_t	append				(const ::llc::view<const T> & newChain)				noexcept	{ return append(newChain.begin(), newChain.size());	}
		::llc::error_t			append				(const T * chainToAppend, uint32_t chainLength)		noexcept	{
			if(0 == chainLength)
				return Count;

			llc_necs(reserve(Count + chainLength));
			u2_c				iFirst				= Count;
			for(uint32_t i = 0; i < chainLength; ++i)
				new (&Data[Count++]) T{chainToAppend[i]};
			return iFirst;
		}

		// returns the new size of the list or -1 on failure.
		::llc::error_t			insert				(uint32_t index, const T & newValue)										noexcept	{
			ree_if(index > Count, "Invalid index: %" LLC_FMT_U2 ".", index);
			u2_c				newCount			= Count + 1;
			if(Size < newCount) {
				T							* newData			= 0;
				u2_c				newSize				= alloc_with_reserve(newCount, newData);
				rees_if(0 == newData);
				for(uint32_t i = 0; i < index; ++i) {
					new (&newData[i]) T(Data[i]);
					Data[i].~T();
				}
				new (&newData[index]) T(newValue);
				for(uint32_t i = index; i < Count; ++i) {
					new (&newData[i + 1]) T(Data[i]);
					Data[i].~T();
				}
				T							* oldData			= Data;
				Data					= newData;
				Size					= newSize;
				::llc::llc_free(oldData);
			}
			else {
				for(int32_t i = (int)Count - 1; i >= (int)index; --i) {
					new (&Data[i + 1]) T(Data[i]);
					Data[i].~T();
				}
				new (&Data[index]) T(newValue);
			}
			return Count = newCount;
		}

		// returns the new size of the list or -1 on failure.
		::llc::error_t			insert				(uint32_t index, const T * chainToInsert, uint32_t chainLength)			noexcept	{
			ree_if(index > Count, "Invalid index: %" LLC_FMT_U2 ".", index);

			u2_c				newCount			= Count + chainLength;
			if(Size < newCount) {
				T							* newData			= 0;
				u2_c				newSize				= alloc_with_reserve(newCount, newData);
				rees_if(0 == newData);
				for(uint32_t i = 0; i < index; ++i) {
					new (&newData[i]) T(Data[i]);
					Data[i].~T();
				}

				for(uint32_t i = 0; i < chainLength; ++i) 
					new (&newData[index + i]) T(chainToInsert[i]);

				for(uint32_t i = index; i < Count; ++i) {
					new (&newData[i + chainLength]) T(Data[i]);
					Data[i].~T();
				}
				T							* oldData			= Data;
				Data					= newData;
				Size					= newSize;
				::llc::llc_free(oldData);
			}
			else {	// no need to reallocate and copy, just shift rightmost elements and insert in-place
				for(int32_t i = (int)Count - 1; i >= (int)index; --i) {
					new (&Data[i + chainLength]) T(Data[i]);
					Data[i].~T();
				}

				for(uint32_t i = 0; i < chainLength; ++i) 
					new (&Data[index + i]) T(chainToInsert[i]);
			}
			return Count = newCount;
		}

		tplt<size_t _chainLength>
		inline	::llc::error_t	insert				(uint32_t index, const T* (&chainToInsert)[_chainLength])		noexcept	{ return insert(index, chainToInsert, (uint32_t)_chainLength); }
		inline	::llc::error_t	insert				(uint32_t index, ::llc::view<const T> chainToInsert)			noexcept	{ return insert(index, chainToInsert.begin(), chainToInsert.size()); }

	}; // array_obj

	tplT	using aobj		= ::llc::array_obj<T>; 
	tplT	using ao		= ::llc::aobj<T>; 

	tplT	using aview		= ::llc::aobj	<::llc::view<T>>; 
	tplT	using av		= ::llc::aview	<T>; 

	tydf	::llc::aview<uc_t	>	avuc;
	tydf	::llc::aview<char		>	avc;
	tydf	::llc::aview<float		>	avf32, avf;
	tydf	::llc::aview<double		>	avf64, avd;
	tydf	::llc::aview<uint8_t	>	avu8;
	tydf	::llc::aview<uint16_t	>	avu16;
	tydf	::llc::aview<uint32_t	>	avu32;
	tydf	::llc::aview<uint64_t	>	avu64;
	tydf	::llc::aview<int8_t		>	avi8;
	tydf	::llc::aview<int16_t	>	avi16;
	tydf	::llc::aview<int32_t	>	avi32;
	tydf	::llc::aview<int64_t	>	avi64;

	// view<const> common typedefs
	tydf	::llc::aview<const uc_t	>	avcuc;
	tydf	::llc::aview<const char		>	avcc;
	tydf	::llc::aview<const float	>	avcf32, avcf;
	tydf	::llc::aview<const double	>	avcf64, avcd;
	tydf	::llc::aview<const uint8_t	>	avcu8;
	tydf	::llc::aview<const uint16_t	>	avcu16;
	tydf	::llc::aview<u2_c	>	avcu32;
	tydf	::llc::aview<const uint64_t	>	avcu64;
	tydf	::llc::aview<const int8_t	>	avci8;
	tydf	::llc::aview<const int16_t	>	avci16;
	tydf	::llc::aview<const int32_t	>	avci32;
	tydf	::llc::aview<const int64_t	>	avci64;


	tplT	::llc::error_t							split					(const ::llc::view<const T> & target, const T & separator, ::llc::aobj<::llc::view<const T>> & split)	{
		uint32_t									lastOffset				= 0;
		for(uint32_t iChar = 0; iChar < target.size(); ++iChar) {
			if(target[iChar] == separator) {
				const ::llc::view<const T>			newView					= {&target[lastOffset], iChar - lastOffset};
				++iChar;
				llc_necs(split.push_back(newView));
				lastOffset								= iChar;
			}
		}
		if(lastOffset < target.size())
			llc_necs(split.push_back({&target[lastOffset], target.size() - lastOffset}));
		return (int32_t)split.size();
	}

	tplT	::llc::error_t							split					(const ::llc::view<const T> & target, const ::llc::view<const T>& separators, ::llc::aobj<::llc::view<const T>> & split)	{
		uint32_t									lastOffset				= 0;
		for(uint32_t iChar = 0; iChar < target.size(); ++iChar) {
			for(uint32_t iSeparator = 0; iSeparator < separators.size(); ++iSeparator) {
				if(target[iChar] == separators[iSeparator]) {
					const ::llc::view<const T>			newView					= {&target[lastOffset], iChar - lastOffset};
					++iChar;
					llc_necs(split.push_back(newView));
					lastOffset								= iChar;
				}
			}
		}
		if(lastOffset < target.size())
			llc_necs(split.push_back({&target[lastOffset], target.size() - lastOffset}));
		return (int32_t)split.size();
	}

	tplT	::llc::error_t							split					(const ::llc::vcs & target, const T & separator, ::llc::aobj<::llc::vcs> & split)	{
		int32_t										lastOffset				= 0;
		for(int32_t iChar = 0, countChars = target.size(); iChar < countChars; ++iChar) {
			if(target[iChar] == separator) {
				const ::llc::vcs							newView					= {&target[lastOffset], (uint32_t)::llc::max((int32_t)0, int32_t(iChar - lastOffset))};
				++iChar;
				llc_necs(split.push_back(newView));
				lastOffset								= iChar;
			}
		}
		if(lastOffset < (int32_t)target.size()) {
			llc_necs(split.push_back({&target[lastOffset], target.size() - lastOffset}));
			//if(split[split.size()-1][] == separator)
		}
		return (int32_t)split.size();
	}



	tydf ::llc::SKeyVal<::llc::vcs, ::llc::aobj<::llc::vcs>>	TKeyValConstStringArray;
	//------------------------------------------------------------------------------------------------------------
	::llc::error_t							keyValConstStringDeserialize	(vcu0_c & input, ::llc::aobj<::llc::TKeyValConstChar> & output);

	::llc::error_t							filterPrefix					(::llc::view<::llc::vcsc_c> input, ::llc::vcsc_c prefix, ::llc::aobj<::llc::vcsc_t> & filtered, bool nullIncluded = false);
	::llc::error_t							filterPostfix					(::llc::view<::llc::vcsc_c> input, ::llc::vcsc_c prefix, ::llc::aobj<::llc::vcsc_t> & filtered, bool nullIncluded = false);
}
#endif // LLC_ARRAY_OBJ_H_23627
