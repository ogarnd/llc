#include "llc_array_pod.h"

#include "llc_keyval.h"

#include "llc_view_serialize.h"

#ifndef LLC_APOD_SERIALIZE_H_23627
#define LLC_APOD_SERIALIZE_H_23627

namespace llc
{
	tplT			err_t	saveView			(au8 & output, cnst view<T> & viewToSerialize)	{
		cnst packedu32				counterValue		= viewToSerialize.size();
		llc_necs(output.append(counterValue.tplt cu8<vcu8>()));
		llc_necs(output.append(viewToSerialize.cu8()));
		return counterValue.ValueWidth() + viewToSerialize.byte_count();
	}
	tplT			err_t	saveUIntView		(au8 & output, cnst view<T> & viewToSerialize)	{
		u2_c						offset				= output.size();
		cnst packedu32				counterValue		= viewToSerialize.size();
		llc_necs(output.append(counterValue.tplt cu8<vcu0_t>()));
		for(cnst packed_uint<T> valpkd : viewToSerialize)
			llc_necs(output.append(valpkd.tplt cu8<vcu0_t>()));
		return output.size() - offset;
	}
	tplt<>	inline	err_t	saveView	<u1_t>	(au8 & output, vu1_c  & viewToSerialize)		{ return saveUIntView(output, viewToSerialize); }
	tplt<>	inline	err_t	saveView	<u2_t>	(au8 & output, vu2_c  & viewToSerialize)		{ return saveUIntView(output, viewToSerialize); }
	tplt<>	inline	err_t	saveView	<u3_t>	(au8 & output, vu3_c  & viewToSerialize)		{ return saveUIntView(output, viewToSerialize); }
	tplt<>	inline	err_t	saveView	<u1_c>	(au8 & output, vcu1_c & viewToSerialize)		{ return saveUIntView(output, viewToSerialize); }
	tplt<>	inline	err_t	saveView	<u2_c>	(au8 & output, vcu2_c & viewToSerialize)		{ return saveUIntView(output, viewToSerialize); }
	tplt<>	inline	err_t	saveView	<u3_c>	(au8 & output, vcu3_c & viewToSerialize)		{ return saveUIntView(output, viewToSerialize); }

	tplT	stainli	err_t	saveView			(ai8 & output, cnst view<T> & headerToWrite)	{ return saveView(*(au8*)&output, headerToWrite); }
	tplT			err_t	savePOD				(au8 & output, cnst T & input)	{ llc_necs(output.append((cnst uint8_t*)&input, sizeof(T))); return sizeof(T); }
	tplT	stainli	err_t	savePOD				(ai8 & output, cnst T & input)	{ return savePOD(*(au8*)&output, input); }
	tplT			err_t	saveUInt			(au8 & output, cnst T & input)	{ 
		cnst packed_uint<T>			packedInput			= input; 
		llc_necs(output.append(packedInput.cu8())); 
		return packedInput.ValueWidth(); 
	}
	tplT	err_t			loadView			(vcu8 & input, apod<T> & output) { 
		view<cnst T>					readView			= {}; 
		uint32_t						bytesRead			= 0;
		llc_necs(bytesRead = viewRead(readView, input)); 
		llc_necs(input.slice(input, bytesRead));
		output						= readView;// llc_necs(output.append(readView)); 
		return 0;
	}
	tplT	stainli err_t	loadView			(vci8 & input, apod<T> & output) { return loadView(*(vcu8*)& input, output); }
	tplT	stainli err_t	loadView			(vcc  & input, apod<T> & output) { return loadView(*(vcu8*)& input, output); }

	err_t						keyValConstStringSerialize	(cnst view<cnst TKeyValConstChar> & keyVals, vcvsc_c & keysToSave, au8 & output);
} // namespace

#endif // LLC_APOD_SERIALIZE_H_23627
