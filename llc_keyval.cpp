#include "llc_keyval.h"
#include "llc_safe.h"
#include "llc_parse.h"
#include "llc_apod_serialize.h"

::llc::error_t			llc::join				(::llc::achar & output, char separator, ::llc::vcvcc fields)	{
	for(uint32_t iField = 0; iField < fields.size();) {
		llc_necall(output.append(fields[iField]), "%i", iField);
		if(++iField < fields.size())
			llc_necall(output.push_back(separator), "%i", iField);
	}
	return 0;
}

::llc::achar		llc::toString			(const ::llc::vcc & strToLog)	{
	::llc::achar			sprintfable				= strToLog;
	if(sprintfable.size() && sprintfable[sprintfable.size() - 1] == 0) { // it already contains a null, so resize it to avoid counting it as part of the array.
		sprintfable.resize(sprintfable.size() - 1);
		return sprintfable;
	}

	es_if(::llc::failed(sprintfable.push_back(0)))
	else
		es_if(::llc::failed(sprintfable.resize(sprintfable.size()-1)));

	return sprintfable;
}

::llc::error_t			llc::token_split		(char token, const ::llc::vcs & input_string, TKeyValConstChar & output_views)	{
	uint32_t					indexToken;
	llc_necall(indexToken = ::llc::find(token, input_string), "'%c' not found.", token);
	output_views.Key		= {input_string.begin(), (uint32_t)indexToken};
	output_views.Val		= (indexToken + 1 < (int32_t)input_string.size())
		? ::llc::vcs{&input_string[indexToken + 1], input_string.size() - (indexToken + 1)}
		: ::llc::vcs{}	// empty view if there's no data after the separator.
		;
	::llc::trim(output_views.Key, output_views.Key);
	::llc::trim(output_views.Val, output_views.Val);
	return 0;
}

::llc::error_t			llc::find				(const ::llc::vcs & keyToFind, const ::llc::view<const ::llc::TKeyValConstString> & keyvals, ::llc::vcc & out_val)		{
	::llc::error_t				index					= ::llc::find(keyToFind, keyvals);
	out_val					= (-1 == index) ? ::llc::vcs{} : keyvals[index].Val;
	return index;
}

::llc::error_t			llc::keyvalNumeric		(const ::llc::vcs & key, const ::llc::view<const ::llc::TKeyValConstString> keyVals, uint64_t * outputNumber)	{
	ree_if(0 == outputNumber, "%s", "Output number cannot point to a null address.");
	::llc::error_t				indexKey				= ::llc::find(key, keyVals);
	if(-1 != indexKey)
		::llc::parseIntegerDecimal(keyVals[indexKey].Val, outputNumber);

	return indexKey;
}

::llc::error_t			llc::keyValVerify		(const ::llc::view<::llc::TKeyValConstString> & environViews, const ::llc::vcc & keyToVerify, const ::llc::vcc & valueToVerify)	{
	for(uint32_t iKey = 0; iKey < environViews.size(); ++iKey) {
		if(environViews[iKey].Key == keyToVerify)
			return (environViews[iKey].Val == valueToVerify) ? iKey : -1;
	}
	return -1;
}

::llc::error_t			llc::keyValConstStringSerialize		(const ::llc::view<const ::llc::TKeyValConstString> & keyVals, const ::llc::vcvcc & keysToSave, ::llc::au8 & output)	{
	::llc::apod<::llc::TKeyValConstString>	keyValsToSave					= {};
	for(uint32_t iKey = 0; iKey < keyVals.size(); ++iKey) {
		for(uint32_t iRef = 0; iRef < keysToSave.size(); ++iRef) {
			const ::llc::TKeyValConstString	& kvToCheck						= keyVals[iKey];
			const ::llc::vcc				& keyToSave						= keysToSave[iRef];
			if(kvToCheck.Key == keyToSave)
				keyValsToSave.push_back(kvToCheck);
		}
	}
	output.append((const uint8_t*)&keyValsToSave.size(), sizeof(uint32_t));
	uint32_t					iOffset								= 0;
	for(uint32_t iKey = 0; iKey < keyValsToSave.size(); ++iKey) {
		iOffset					+= ::llc::saveView(output, keyValsToSave[iKey].Key);
		iOffset					+= ::llc::saveView(output, keyValsToSave[iKey].Val);
	}
	return 0;
}

::llc::error_t			llc::keyValConstStringDeserialize	(const ::llc::vcu8 & input, ::llc::aobj<::llc::TKeyValConstString> & output)	{
	uint32_t					offset								= 0;
	const uint32_t				keysToRead							= *(const uint32_t*)input.begin();
	offset					+= (uint32_t)sizeof(uint32_t);
	output.resize(keysToRead);
	for(uint32_t iKey = 0; iKey < keysToRead; ++iKey) {
		offset					+= ::llc::viewRead(output[iKey].Key, {&input[offset], input.size() - offset});
		offset					+= ::llc::viewRead(output[iKey].Val, {&input[offset], input.size() - offset});
	}
	return 0;
}
