#include "llc_array.h"
#include "llc_stdstring.h"

::llc::error_t			llc::filterPostfix	(::llc::view<const ::llc::vcc> input, const ::llc::vcc postfix, ::llc::aobj<::llc::vcc> & filtered, bool nullIncluded) { 
	for(uint32_t iInput = 0; iInput < input.size(); ++iInput) { 
		const ::llc::vcc & currentInput = input[iInput]; 
		if((postfix.size() < currentInput.size() || (nullIncluded && postfix.size() == currentInput.size())) && 0 == strncmp(currentInput.end() - postfix.size(), postfix.begin(), postfix.size())) 
			filtered.push_back(currentInput); 
	} 
	return 0; 
}

::llc::error_t			llc::filterPrefix	(::llc::view<const ::llc::vcc> input, const ::llc::vcc prefix, ::llc::aobj<::llc::vcc> & filtered, bool nullIncluded) { 
	for(uint32_t iInput = 0; iInput < input.size(); ++iInput) { 
		const ::llc::vcc & currentInput = input[iInput]; 
		if((prefix .size() < currentInput.size() || (nullIncluded && prefix .size() == currentInput.size())) && 0 == strncmp(currentInput.begin(), prefix .begin(), prefix .size())) 
			filtered.push_back(currentInput); 
	}
	return 0; 
}

::llc::error_t			llc::camelCase		(::llc::vcc input, ::llc::achar & camelCased) {
	bool						capsNext			= true;
	for(uint32_t i = 0; i < input.size(); ++i) {
		char						current				= input[i];
		if(current == '_' || current == '-')
			capsNext	= true;
		else {
			if(capsNext) {
				::llc::toupper(current);
				capsNext	= false;
			}
			//else
			//	::llc::tolower(::llc::vc{&camelCased[1], camelCased.size() - 1});
			camelCased.push_back(current);
		}
	}
	return 0;
}
