#include "llc_view.h"

#ifndef LLC_KEYVAL_H_23627
#define LLC_KEYVAL_H_23627

namespace llc
{
	tplt<tpnm _tKey, tpnm _tVal>
	struct SKeyVal {
					_tKey									Key;
					_tVal									Val;
	};
	tydf	SKeyVal<vcsc_t, vcsc_t>
														TKeyValConstChar, TKeyValConstString;

	//tydf		SKeyVal<vcs, vcs> TKeyValConstString;

				error_t							token_split						(char token, const vcs& input_string, TKeyValConstChar& output_views);
	inline		error_t							keyval_split					(const vcs& input_string, TKeyValConstString& out_keyval) { return token_split('=', input_string, out_keyval); }

	tplt<tpnm _tVal>
				error_t							find			(const vcs & keyToFind, const view<const SKeyVal<vcsc_t, _tVal>> & keyvals)	{
		for(uint32_t iKeyVal = 0; iKeyVal < keyvals.size(); ++iKeyVal) {
			vcsc_c							& keyCurrent					= keyvals[iKeyVal].Key;
			if(keyToFind == keyCurrent)
				return iKeyVal;
		}
		return -1;
	}

	tplt<tpnm _tVal>
				error_t							find			(const vcs & keyToFind, const view<const TKeyValConstString> & keyvals, view<const _tVal>& out_val)		{
		error_t					index							= find(keyToFind, keyvals);
		out_val								= (-1 == index) ? view<const _tVal>{} : view<const _tVal>{(const _tVal*)keyvals[index].Val.begin(), keyvals[index].Val.size()};
		return index;
	}

				error_t							find			(const vcs & keyToFind, const view<const TKeyValConstString> & keyvals, vcsc_t & out_val);
				error_t							keyValVerify					(const view<TKeyValConstString> & environViews, vcsc_c & keyToVerify, vcsc_c & valueToVerify);
				error_t							keyvalNumeric					(const vcs & key, const view<const TKeyValConstString> keyVals, uint64_t * outputNumber);
	tplt <tpnm _tNumeric>
				error_t							keyvalNumeric					(const vcs & key, const view<const TKeyValConstString> keyVals, _tNumeric & outputNumber)	{
		uint64_t												value							= 0;
		error_t					indexKey						= keyvalNumeric(key, keyVals, &value);
		if(-1 != indexKey)
			outputNumber										= *(_tNumeric*)&value;
		return indexKey;
	}

	tplt <tpnm... _tArgs>
	error_t				keyValVerify					(const view<TKeyValConstString> & environViews, vcsc_c & keyToVerify, const view<vcsc_c>& valueToVerify)	{
		for(uint32_t iKey = 0; iKey < valueToVerify.size(); ++iKey) {
			const error_t			val								= keyValVerify(environViews, keyToVerify, valueToVerify[iKey]);
			if(-1 != val)
				return val;
		}
		return -1;
	}


} // namespace

#endif // LLC_KEYVAL_H_23627
