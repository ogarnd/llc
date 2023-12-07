#include "llc_view.h"

#include "llc_packed_int.h"

#ifndef LLC_VIEW_SERIALIZE_H_23627
#define LLC_VIEW_SERIALIZE_H_23627

namespace llc
{
	tplt<tpnm T, tpnm TByte>
	::llc::error_t				viewRead			(::llc::view<T> & headerToRead, ::llc::view<TByte> input)	{
		const packedu32					& header			= *(const packedu32*)input.begin();
		const uint32_t					counterWidth		= header.ValueWidth();
		ree_if(input.size() < counterWidth, LLC_FMT_U32_LT_U32, input.size(), counterWidth);

		const uint32_t					elementCount		= header.Value();
		const uint32_t					dataSize			= sizeof(T) * elementCount;
		ree_if(dataSize > (input.size() - counterWidth), "%" LLC_FMT_U32 " > (%" LLC_FMT_U32 "-%" LLC_FMT_U32 ").", dataSize, input.size(), counterWidth);

		headerToRead				= {(input.size() > counterWidth) ? (T*)&input[counterWidth] : 0, elementCount};
		return counterWidth + dataSize;
	}
	tplt<tpnm T>	stainli	::llc::error_t	viewRead		(::llc::view<const T> & headerToRead, const ::llc::vcu8 & input)	{ return viewRead<const T, const uint8_t>(headerToRead, input); }
	tplt<tpnm T>	stainli	::llc::error_t	viewRead		(::llc::view<const T> & headerToRead, const ::llc::vci8 & input)	{ return viewRead<const T, const int8_t >(headerToRead, input); }
	tplt<tpnm T>	stainli	::llc::error_t	viewRead		(::llc::view<const T> & headerToRead, const ::llc::vcc  & input)	{ return viewRead<const T, const char   >(headerToRead, input); }
	tplt<tpnm T>	stainli	::llc::error_t	viewRead		(::llc::view<T> & headerToRead, ::llc::vu8 input)					{ return viewRead<T, uint8_t>(headerToRead, input); }
	tplt<tpnm T>	stainli	::llc::error_t	viewRead		(::llc::view<T> & headerToRead, ::llc::vi8 input)					{ return viewRead<T, int8_t >(headerToRead, input); }
	tplt<tpnm T>	stainli	::llc::error_t	viewRead		(::llc::view<T> & headerToRead, ::llc::vc  input)					{ return viewRead<T, char   >(headerToRead, input); }

	tplt<tpnm T, tpnm TByte>
	::llc::error_t				viewReadLegacy		(::llc::view<T> & headerToRead, ::llc::view<TByte> input)	{
		const uint32_t					counterWidth		= sizeof(uint32_t);
		ree_if(input.size() < counterWidth, "Invalid input size: %u", input.size());

		const uint32_t					elementCount		= *(const uint32_t*)input.begin();
		const uint32_t					dataSize			= elementCount * sizeof(T);
		ree_if(dataSize > (input.size() - counterWidth), "Invalid input size: %u. Expected: %u", input.size(), dataSize);

		headerToRead				= {(input.size() > counterWidth) ? (T*)&input[counterWidth] : 0, elementCount};
		return counterWidth + dataSize;
	}
	tplt<tpnm T>	stainli	::llc::error_t	viewReadLegacy	(::llc::view<const T> & headerToRead, const ::llc::vcu8 & input)	{ return viewReadLegacy<const T, const uint8_t>(headerToRead, input); }
	tplt<tpnm T>	stainli	::llc::error_t	viewReadLegacy	(::llc::view<const T> & headerToRead, const ::llc::vci8 & input)	{ return viewReadLegacy<const T, const int8_t >(headerToRead, input); }
	tplt<tpnm T>	stainli	::llc::error_t	viewReadLegacy	(::llc::view<const T> & headerToRead, const ::llc::vcc  & input)	{ return viewReadLegacy<const T, const char   >(headerToRead, input); }
	tplt<tpnm T>	stainli	::llc::error_t	viewReadLegacy	(::llc::view<T> & headerToRead, ::llc::vu8 input)					{ return viewReadLegacy<T, uint8_t>(headerToRead, input); }
	tplt<tpnm T>	stainli	::llc::error_t	viewReadLegacy	(::llc::view<T> & headerToRead, ::llc::vi8 input)					{ return viewReadLegacy<T, int8_t >(headerToRead, input); }
	tplt<tpnm T>	stainli	::llc::error_t	viewReadLegacy	(::llc::view<T> & headerToRead, ::llc::vc  input)					{ return viewReadLegacy<T, char   >(headerToRead, input); }

	tplt<tpnm _tPOD> 
	::llc::error_t				loadPOD				(::llc::vcu8 & input, _tPOD & output) { 
		rees_if(input.byte_count() < sizeof(_tPOD));
		memcpy(&output, input.begin(), sizeof(_tPOD));
		llc_necs(input.slice(input, sizeof(_tPOD)));
		return sizeof(_tPOD);
	}
	tplt<tpnm _tPOD>	stainli	::llc::error_t	loadPOD		(::llc::vci8 & input, _tPOD & output) { return loadPOD (*(::llc::vcu8*)& input, output); }
	tplt<tpnm _tPOD>	stainli	::llc::error_t	loadPOD		(::llc::vcc  & input, _tPOD & output) { return loadPOD (*(::llc::vcu8*)& input, output); }

	tplt<tpnm _tPOD> 
	::llc::error_t				loadView			(::llc::vcu8 & input, ::llc::view<const _tPOD> & output) { 
		uint32_t						bytesRead				= 0;
		llc_necs(bytesRead = ::llc::viewRead(output, input)); 
		llc_necs(input.slice(input, bytesRead));
		return 0;
	}
	tplt<tpnm _tPOD>	stainli	::llc::error_t	loadView	(::llc::vci8 & input, ::llc::view<_tPOD> & output) { return loadView(*(::llc::vcu8*)& input, output); }
	tplt<tpnm _tPOD>	stainli	::llc::error_t	loadView	(::llc::vcc  & input, ::llc::view<_tPOD> & output) { return loadView(*(::llc::vcu8*)& input, output); }
} // namespace

#endif // LLC_VIEW_SERIALIZE_H_23627
