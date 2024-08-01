#include "llc_view.h"

#include "llc_packed_int.h"

#ifndef LLC_VIEW_SERIALIZE_H_23627
#define LLC_VIEW_SERIALIZE_H_23627

namespace llc
{
	tplT			err_t	loadPOD			(vcu0_t & input, T & output) { 
		rees_if(input.byte_count() < sizeof(T));
		memcpy(&output, input.begin(), sizeof(T));
		llc_necs(input.slice(input, sizeof(T)));
		return sizeof(T);
	}
	tplT	stainli	err_t	loadPOD			(vcs0_t & input, T & output)	{ return loadPOD (*(vcu0_t*)& input, output); }
	tplT	stainli	err_t	loadPOD			(vcc  & input, T & output)	{ return loadPOD (*(vcu0_t*)& input, output); }
	//
	tplT			err_t	loadUInt		(vcu0_t & input, T & output)	{
		const packed_uint<T>		& packedInput	= *(const packed_uint<T>*)input.begin(); 
		if_true_ve(-1, packedInput.ValueWidth() > input.size()); 
		output					= packedInput.Value(); 
		llc_necs(input.slice(input, packedInput.ValueWidth())); 
		return packedInput.ValueWidth();
	}
	tplT	stainli	err_t	loadUInt		(vcs0_t & input, T & output)	{ return loadUInt (*(vcu0_t*)& input, output); }
	tplT	stainli	err_t	loadUInt		(vcc  & input, T & output)	{ return loadUInt (*(vcu0_t*)& input, output); }
	//
	tplt<tpnm T, tpnm TByte>
	err_t					viewRead		(view<T> & headerToRead, view<TByte> input)	{
		const packedu32				& header		= *(const packedu32*)input.begin();
		const uint32_t				counterWidth	= header.ValueWidth();
		ree_if(input.size() < counterWidth, LLC_FMT_LT_U32, input.size(), counterWidth);
		const uint32_t				elementCount	= header.Value();
		const uint32_t				dataSize		= sizeof(T) * elementCount;
		ree_if(dataSize > (input.size() - counterWidth), "%" LLC_FMT_U32 " > (%" LLC_FMT_U32 "-%" LLC_FMT_U32 ").", dataSize, input.size(), counterWidth);
		headerToRead			= {(input.size() > counterWidth) ? (T*)&input[counterWidth] : 0, elementCount};
		return counterWidth + dataSize;
	}
	tplT	stainli	err_t	viewRead		(view<const T> & headerToRead, const vcu0_t & input)	{ return viewRead<const T, const uint8_t>(headerToRead, input); }
	tplT	stainli	err_t	viewRead		(view<const T> & headerToRead, const vcs0_t & input)	{ return viewRead<const T, const int8_t >(headerToRead, input); }
	tplT	stainli	err_t	viewRead		(view<const T> & headerToRead, const vcc  & input)	{ return viewRead<const T, const char   >(headerToRead, input); }
	tplT	stainli	err_t	viewRead		(view<T> & headerToRead, vu8 input)					{ return viewRead<T, uint8_t>(headerToRead, input); }
	tplT	stainli	err_t	viewRead		(view<T> & headerToRead, vi8 input)					{ return viewRead<T, int8_t >(headerToRead, input); }
	tplT	stainli	err_t	viewRead		(view<T> & headerToRead, vc  input)					{ return viewRead<T, char   >(headerToRead, input); }
	//
	tplT			err_t	loadView		(vcu0_t & input, view<const T> & output) { 
		uint32_t					bytesRead		= 0;
		llc_necs(bytesRead = viewRead(output, input)); 
		llc_necs(input.slice(input, bytesRead));
		return 0;
	}
	tplT	stainli	err_t	loadView	(vcs0_t & input, view<T> & output) { return loadView(*(vcu0_t*)& input, output); }
	tplT	stainli	err_t	loadView	(vcc  & input, view<T> & output) { return loadView(*(vcu0_t*)& input, output); }
	//
	tplt<tpnm T, tpnm TByte>
	err_t					viewReadLegacy	(view<T> & headerToRead, view<TByte> input)	{
		const uint32_t				counterWidth	= sizeof(uint32_t);
		ree_if(input.size() < counterWidth, "Invalid input size: %" LLC_FMT_U32 "", input.size());
		const uint32_t				elementCount	= *(const uint32_t*)input.begin();
		const uint32_t				dataSize		= elementCount * sizeof(T);
		ree_if(dataSize > (input.size() - counterWidth), "Invalid input size: %" LLC_FMT_U32 ". Expected: %" LLC_FMT_U32 "", input.size(), dataSize);
		headerToRead			= {(input.size() > counterWidth) ? (T*)&input[counterWidth] : 0, elementCount};
		return counterWidth + dataSize;
	}
	tplT	stainli	err_t	viewReadLegacy	(view<const T> & headerToRead, const vcu0_t & input)	{ return viewReadLegacy<const T, const uint8_t>(headerToRead, input); }
	tplT	stainli	err_t	viewReadLegacy	(view<const T> & headerToRead, const vcs0_t & input)	{ return viewReadLegacy<const T, const int8_t >(headerToRead, input); }
	tplT	stainli	err_t	viewReadLegacy	(view<const T> & headerToRead, const vcc  & input)	{ return viewReadLegacy<const T, const char   >(headerToRead, input); }
	tplT	stainli	err_t	viewReadLegacy	(view<T> & headerToRead, vu8 input)					{ return viewReadLegacy<T, uint8_t>(headerToRead, input); }
	tplT	stainli	err_t	viewReadLegacy	(view<T> & headerToRead, vi8 input)					{ return viewReadLegacy<T, int8_t >(headerToRead, input); }
	tplT	stainli	err_t	viewReadLegacy	(view<T> & headerToRead, vc  input)					{ return viewReadLegacy<T, char   >(headerToRead, input); }
} // namespace

#endif // LLC_VIEW_SERIALIZE_H_23627
