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
				gthrow_if(errored(resize((uint32_t)init.size())), "init.size() -> %u.", (uint32_t)init.size());
				memcpy(Data, init.begin(), Count * sizeof(T));
			}
									array_pod			(array_pod<T> && other)					noexcept	{
				Size					= other.Size;
				Count					= other.Count;
				Data					= other.Data;

				other.Size				= other.Count			= 0;
				other.Data				= 0;
			}
			inline					array_pod			(const array_pod<T> & other)						: array_pod((const view<const T>&) other) {}
									array_pod			(const view<const T> & other)						{
				gsthrow_if(resize(other.size()) != (int32_t)other.size());
				memcpy(Data, other.begin(), other.byte_count());
			}
			tplt<size_t _count>
									array_pod			(const T (&other)[_count])							{
				gsthrow_if(resize(_count) != (int32_t)_count);
				memcpy(Data, other, _count * sizeof(T));
			}
			inlcxpr	operator		view<const T>	()									const	noexcept	{ return {Data, Count}; }
			TArray&					operator =			(const array_pod<T>& other)							{ return operator=((const view<T> &) other); }
			TArray&					operator =			(const view<const T> & other)						{
				gsthrow_if(resize(other.size()) != (int32_t)other.size());
				if(Count)
					memcpy(Data, other.begin(), other.byte_count());
				return *this;
			}
			tplt<size_t sizeStatic>
			TArray&					operator =			(const T (&init)[sizeStatic])						{
				gsthrow_if(resize(sizeStatic) != sizeStatic);
				memcpy(Data, init, Count * sizeof(T));
				*(u16*)&Data[Count]		= 0;
				return *this;
			}

			inline	::llc::error_t	clear				()										noexcept	{ return Count = 0; }
			::llc::error_t			clear_pointer		()										noexcept	{ safe_llc_free(Data); Data = 0; return Size = Count = 0; }
			// Returns the new size of the array
			::llc::error_t			pop_back			()										noexcept	{
				rees_if(0 == Count);
				*(u16*)&Data[--Count]		= 0;
				return Count;
			}
			// Returns the new size of the array
			::llc::error_t			pop_back			(T & oldValue)							noexcept	{
				rees_if(0 == Count);
				oldValue				= Data[--Count];
				*(u16*)&Data[Count]		= 0;
				return Count;
			}
			// Returns the index of the pushed value or -1 on failure
			::llc::error_t			push_back			(const T & newValue)					noexcept	{
				const int32_t				oldSize				= Count;
				llc_necs(resize(oldSize + 1, newValue));
				return oldSize;
			}
			inline	::llc::error_t	append_string		(const llc::function<err_t(TArray&)> & funcAppend)	noexcept	{ return funcAppend ? funcAppend(*this) : 0; }
			tplt<size_t _len>
			inline	::llc::error_t	append_string		(const T (&newChain)[_len])							noexcept	{ return append(::llc::vcs{newChain}); }
			inline	::llc::error_t	append_string		(const ::llc::vcs & newChain)						noexcept	{ return append(newChain.begin(), newChain.size()); }
			inline	::llc::error_t	append_string		(const T & element)									noexcept	{ llc_necs(push_back(element)); return 1; }
			inline	::llc::error_t	append_strings		(const ::llc::view<const ::llc::vcs> & newChains)	noexcept	{ 
				int32_t					appended				= 0;
				for(uint32_t i = 0, stop = newChains.size(); i < stop; ++i) {
					const ::llc::vcs & newChain = newChains[i];
					llc_necs(append(newChain));
					appended += newChain.size();
				}
				return appended;
			}
			tplt<size_t 					_len>
			inline	::llc::error_t	append				(const T (&newChain)[_len])									noexcept	{ return append(newChain, (uint32_t)_len); }
			inline	::llc::error_t	append				(const ::llc::view<const T> & newChain)						noexcept	{ return append(newChain.begin(), newChain.size());	}
			inline	::llc::error_t	append				(const ::llc::view<const ::llc::view<const T>> & newChains)	noexcept	{ 
				int32_t count = 0;
				err_t err = 0;
				newChains.for_each([this, &count, &err](const view<const T> &newChain) { if(false == failed(err)) { if_fail_e(err = append(newChain)); count += newChain.size(); } }); 
				return failed(err) ? err : count;
			}
			::llc::error_t			append				(const T * chainToAppend, uint32_t chainLength)				noexcept	{
				if(0 == chainLength)
					return Count;
				const uint32_t				newCount			= Count + chainLength;
				llc_necs(reserve(newCount));
				const uint32_t				iFirst				= Count;
				memcpy(&Data[iFirst], chainToAppend, sizeof(T) * chainLength);
				Count					+= chainLength;
				*(u16*)&Data[Count]		= 0;
				return iFirst;
			}
			::llc::error_t			reserve				(uint32_t newCount)								{
				if(newCount > Size) {
					T							* newData			= 0;
					const uint32_t				newSize				= alloc_with_reserve(newCount, newData);
					rees_if(0 == newData);
					if(Data)
						memcpy(newData, Data, this->byte_count());
						
					*(u16*)&newData[Count]	= 0;
					T							* oldData			= Data;
					Data					= newData;
					Size					= newSize;
					::llc::llc_free(oldData);
				}
				return Size;
			}

			inline	::llc::error_t	resize_bits			(uint32_t newBitCount)						noexcept	{
				stacxpr	uint32_t			elementBits			= (uint32_t)sizeof(T) * 8U;
				return resize(newBitCount / elementBits + one_if(newBitCount % elementBits));
			}

			// Returns the new size of the array.
			::llc::error_t			resize				(uint32_t newCount)						noexcept	{
				llc_necs(reserve(newCount));
				Count					= newCount;
				if(Data)
					*(u16*)&Data[Count]		= 0;
				return Count;
			}
			// Returns the new size of the array.
			::llc::error_t			resize				(uint32_t newCount, const T & newValue)	noexcept	{
				llc_necs(reserve(newCount));
				if(Data) {
					for(; Count < newCount; ++Count)
						Data[Count] = newValue;
					*(u16*)&Data[Count = newCount]	= 0;
				}
				return Count;
			}
			// returns the new size of the list or -1 on failure.
			::llc::error_t			insert				(uint32_t index, const T & newValue)	noexcept	{
				ree_if(index > Count, LLC_FMT_U32_GT_U32, index, Count);
				const uint32_t				newCount			= Count + 1;
				if(Size < newCount) {
					T							* newData			= 0;
					const uint32_t				newSize				= alloc_with_reserve(newCount, newData);
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
					for(int32_t i = (int)Count - 1; i >= (int)index; --i)
						Data[i + 1]				= Data[i];
					Data[index]				= newValue;
				}
				*(u16*)&Data[newCount]	= 0;
				return Count = newCount;
			}
			// returns the new size of the list or -1 on failure.
			::llc::error_t			insert				(uint32_t index, const T * chainToInsert, uint32_t chainLength)	noexcept	{
				ree_if(index > Count, LLC_FMT_U32_GT_U32, index, Count);

				const uint32_t				newCount			= Count + chainLength;
				if(Size < newCount) {
					T							* newData			= 0;
					const uint32_t				newSize				= alloc_with_reserve(newCount, newData);
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
					for(int32_t i = (int)Count - 1; i >= (int)index; --i)
						Data[i + chainLength]	= Data[i];
					memcpy(&Data[index], chainToInsert, chainLength * sizeof(T));
				}
				*(u16*)&Data[newCount]	= 0;
				return Count = newCount;
			}
			tplt<size_t _chainLength>
			inline	::llc::error_t	insert				(uint32_t index, const T (&chainToInsert)[_chainLength])		noexcept	{ return insert(index, chainToInsert, (uint32_t)_chainLength); }
			inline	::llc::error_t	insert				(uint32_t index, ::llc::view<const T> chainToInsert)			noexcept	{ return insert(index, chainToInsert.begin(), chainToInsert.size()); }
			// Returns the new size of the list or -1 if the array pointer is not initialized.
			::llc::error_t			remove_unordered	(uint32_t index)												noexcept	{
				ree_if(index >= Count, LLC_FMT_U32_GE_U32, index, Count);
				Data[index]				= Data[--Count];
				*(u16*)&Data[Count]		= 0;
				return Count;
			}
			// returns the new array size or -1 if failed.
			::llc::error_t			erase				(const T * address)												noexcept	{
				const ptrdiff_t				ptrDiff				= ptrdiff_t(address) - (ptrdiff_t)Data;
				const uint32_t				index				= (uint32_t)(ptrDiff / (ptrdiff_t)sizeof(T));
				ree_if(index >= Count, LLC_FMT_U32_GE_U32 ", p: 0x%p", index, Count, address);
				return remove(index);
			}
			// returns the new array size or -1 if failed.
			::llc::error_t			remove				(uint32_t index)													noexcept	{
				ree_if(index >= Count, LLC_FMT_U32_GE_U32, index, Count);
				--Count;
				while(index < Count) {
					Data[index]				= Data[index + 1];
					++index;
				}
				*(u16*)&Data[Count]		= 0;
				return Count;
			}
		}; // array_pod

		tplt <tpnm T>	using apod		= ::llc::array_pod<T>;
		tplt <tpnm T>	using ap		= ::llc::apod	<T>;

		typedef apod<uchar_t	>	auchar, auc;
		typedef apod<char		>	achar , ac ;
		typedef apod<float		>	af32;
		typedef apod<double		>	af64;
		typedef apod<uint8_t	>	au8	;
		typedef apod<uint16_t	>	au16;
		typedef apod<uint32_t	>	au32;
		typedef apod<uint64_t	>	au64;
		typedef apod<int8_t		>	ai8	;
		typedef apod<int16_t	>	ai16;
		typedef apod<int32_t	>	ai32;
		typedef apod<int64_t	>	ai64;

		llc::achar				toString	(const ::llc::vcc & strToLog);

		::llc::error_t			camelCase		(::llc::vcc input, ::llc::achar & camelCased);

		::llc::error_t			join			(::llc::achar & query, char separator, ::llc::vcvcc fields);
	} // namespace

	#endif // LLC_ARRAY_POD_H_23627
