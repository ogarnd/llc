#include "llc_array_pod.h"

#include "llc_keyval.h"

#include "llc_view_serialize.h"

#ifndef LLC_APOD_SERIALIZE_H_23627
#define LLC_APOD_SERIALIZE_H_23627

namespace llc
{
	tplt<tpnm T>
	::llc::error_t				saveView			(::llc::au8 & output, const ::llc::view<T> & viewToSerialize)	{
		::llc::packedu32				counterValue		= viewToSerialize.size();
		const uint32_t					counterWidth		= counterValue.ValueWidth();
		llc_necs(output.append(counterValue.cu8<vcu8>()));
		llc_necs(output.append(viewToSerialize.cu8()));
		return counterWidth + viewToSerialize.byte_count();
	}
	tplt<tpnm T> ::llc::error_t	saveView(::llc::ai8 & output, const ::llc::view<T> & headerToWrite) { return ::llc::saveView(*(::llc::au8*)&output, headerToWrite); }

	tplt<tpnm T> ::llc::error_t			savePOD	(::llc::au8 & output, const T & input)	{ llc_necs(output.append((const uint8_t*)&input, sizeof(T))); return sizeof(T); }
	tplt<tpnm T> stainli ::llc::error_t	savePOD	(::llc::ai8 & output, const T & input)	{ return ::llc::savePOD(*(::llc::au8*)&output, input); }

	tplt<tpnm T> 
	::llc::error_t				loadView			(::llc::vcu8 & input, ::llc::apod<T> & output) { 
		::llc::view<const T>			readView			= {}; 
		uint32_t						bytesRead			= 0;
		llc_necs(bytesRead = ::llc::viewRead(readView, input)); 
		llc_necs(input.slice(input, bytesRead));
		output						= readView;// llc_necs(output.append(readView)); 
		return 0;
	}
	tplt<tpnm T> ::llc::error_t	loadView			(::llc::vci8 & input, ::llc::apod<T> & output) { return loadView(*(::llc::vcu8*)& input, output); }
	tplt<tpnm T> ::llc::error_t	loadView			(::llc::vcc  & input, ::llc::apod<T> & output) { return loadView(*(::llc::vcu8*)& input, output); }

	::llc::error_t				keyValConstStringSerialize		(const ::llc::view<const ::llc::TKeyValConstChar> & keyVals, const ::llc::vcvcc & keysToSave, ::llc::au8 & output);
} // namespace

#endif // LLC_APOD_SERIALIZE_H_23627
