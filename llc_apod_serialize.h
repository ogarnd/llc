#include "llc_array_pod.h"

#include "llc_keyval.h"

#include "llc_view_serialize.h"

#ifndef LLC_APOD_SERIALIZE_H_23627
#define LLC_APOD_SERIALIZE_H_23627

namespace llc
{
	tpltT	err_t		saveView			(au8 & output, const view<T> & viewToSerialize)	{
		const packedu32					counterValue		= viewToSerialize.size();
		llc_necs(output.append(counterValue.cu8<vcu8>()));
		llc_necs(output.append(viewToSerialize.cu8()));
		return counterValue.ValueWidth() + viewToSerialize.byte_count();
	}
	stainli	err_t		saveView			(au8 & output, const view<i1u_c> & viewToSerialize)	{
		const uint32_t					offset				= output.size();
		const packedu32					counterValue		= viewToSerialize.size();
		llc_necs(output.append(counterValue.cu8<vcu8>()));
		llc_necs(output.append(viewToSerialize.cu8()));
		return output.size() - offset;
	}
	tpltT	stainli	err_t	saveView			(ai8 & output, const view<T> & headerToWrite) { return saveView(*(au8*)&output, headerToWrite); }
	tpltT			err_t	savePOD				(au8 & output, const T & input)	{ llc_necs(output.append((const uint8_t*)&input, sizeof(T))); return sizeof(T); }
	tpltT	stainli	err_t	savePOD				(ai8 & output, const T & input)	{ return savePOD(*(au8*)&output, input); }
	tpltT			err_t	saveUInt			(au8 & output, const T & input)	{ 
		const packed_uint<T>			packedInput			= input; 
		llc_necs(output.append(packedInput.cu8())); 
		return packedInput.ValueWidth(); 
	}
	tpltT	err_t			loadView			(vcu8 & input, apod<T> & output) { 
		view<const T>					readView			= {}; 
		uint32_t						bytesRead			= 0;
		llc_necs(bytesRead = viewRead(readView, input)); 
		llc_necs(input.slice(input, bytesRead));
		output						= readView;// llc_necs(output.append(readView)); 
		return 0;
	}
	tpltT	stainli err_t	loadView			(vci8 & input, apod<T> & output) { return loadView(*(vcu8*)& input, output); }
	tpltT	stainli err_t	loadView			(vcc  & input, apod<T> & output) { return loadView(*(vcu8*)& input, output); }

	err_t						keyValConstStringSerialize	(const view<const TKeyValConstChar> & keyVals, vcvsc_c & keysToSave, au8 & output);
} // namespace

#endif // LLC_APOD_SERIALIZE_H_23627
