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

	tydf		::llc::SKeyVal<::llc::vcc, ::llc::vcc>
														TKeyValConstChar, TKeyValConstString;

	//tydf		::llc::SKeyVal<::llc::vcs, ::llc::vcs> TKeyValConstString;

				::llc::error_t							token_split						(char token, const ::llc::vcs& input_string, TKeyValConstChar& output_views);
	inline		::llc::error_t							keyval_split					(const ::llc::vcs& input_string, TKeyValConstString& out_keyval) { return ::llc::token_split('=', input_string, out_keyval); }

	tplt<tpnm _tVal>
				::llc::error_t							find			(const ::llc::vcs & keyToFind, const ::llc::view<const ::llc::SKeyVal<::llc::vcc, _tVal>> & keyvals)	{
		for(uint32_t iKeyVal = 0; iKeyVal < keyvals.size(); ++iKeyVal) {
			const ::llc::vcc							& keyCurrent					= keyvals[iKeyVal].Key;
			if(keyToFind == keyCurrent)
				return iKeyVal;
		}
		return -1;
	}

	tplt<tpnm _tVal>
				::llc::error_t							find			(const ::llc::vcs & keyToFind, const ::llc::view<const ::llc::TKeyValConstString> & keyvals, ::llc::view<const _tVal>& out_val)		{
		::llc::error_t					index							= ::llc::find(keyToFind, keyvals);
		out_val								= (-1 == index) ? ::llc::view<const _tVal>{} : ::llc::view<const _tVal>{(const _tVal*)keyvals[index].Val.begin(), keyvals[index].Val.size()};
		return index;
	}

				::llc::error_t							find			(const ::llc::vcs & keyToFind, const ::llc::view<const ::llc::TKeyValConstString> & keyvals, ::llc::vcc & out_val);
				::llc::error_t							keyValVerify					(const ::llc::view<::llc::TKeyValConstString> & environViews, const ::llc::vcc & keyToVerify, const ::llc::vcc & valueToVerify);
				::llc::error_t							keyvalNumeric					(const ::llc::vcs & key, const ::llc::view<const ::llc::TKeyValConstString> keyVals, uint64_t * outputNumber);
	tplt <tpnm _tNumeric>
				::llc::error_t							keyvalNumeric					(const ::llc::vcs & key, const ::llc::view<const ::llc::TKeyValConstString> keyVals, _tNumeric & outputNumber)	{
		uint64_t												value							= 0;
		::llc::error_t					indexKey						= ::llc::keyvalNumeric(key, keyVals, &value);
		if(-1 != indexKey)
			outputNumber										= *(_tNumeric*)&value;
		return indexKey;
	}

	tplt <tpnm... _tArgs>
	::llc::error_t				keyValVerify					(const ::llc::view<::llc::TKeyValConstString> & environViews, const ::llc::vcc & keyToVerify, const ::llc::view<const ::llc::vcc>& valueToVerify)	{
		for(uint32_t iKey = 0; iKey < valueToVerify.size(); ++iKey) {
			const ::llc::error_t			val								= ::llc::keyValVerify(environViews, keyToVerify, valueToVerify[iKey]);
			if(-1 != val)
				return val;
		}
		return -1;
	}


} // namespace

#endif // LLC_KEYVAL_H_23627
