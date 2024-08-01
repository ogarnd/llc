#define LLC_DISABLE_DEBUG_BREAK_ON_ERROR_LOG

#include "llc_json.h"
#include "llc_file.h"
#include "llc_parse.h"
#include "llc_math.h"

LLC_USING_TYPEINT();

#define json_info_printf(...) // info_printf
#define json_error_printf error_printf

::llc::error_t			llc::jsonCompareObject		(const ::llc::SJSONNode & node, const ::llc::view<::llc::vcc> & views, const ::llc::SJSONNode & other, const ::llc::view<::llc::vcc> & otherViews) { if(node.Children.size() != other.Children.size()) return 0; if(node.Children.size() == 0) return 1; for(u2_t iChild = 0; iChild < node.Children.size(); iChild += 2)	if(node.Token->Type != other.Token->Type) return 0; return (views[node.ObjectIndex] == otherViews[other.ObjectIndex]) ? 1 : 0; }
::llc::error_t			llc::jsonCompareNumber		(const ::llc::SJSONNode & node, const ::llc::view<::llc::vcc> & views, const ::llc::SJSONNode & other, const ::llc::view<::llc::vcc> & otherViews) { if(node.Children.size() != other.Children.size()) return 0; if(node.Children.size() == 0) return 1; if(node.Token->Type != other.Token->Type) return 0; return (views[node.ObjectIndex] == otherViews[other.ObjectIndex]) ? 1 : 0; }

::llc::error_t			llc::jsonMapToFields
(	::llc::ai32											& indicesOfFields
,	const ::llc::view<const ::llc::SJSONFieldBinding>	fields
,	const ::llc::view<const ::llc::TKeyValConstChar>	fieldMaps
) {
	for(u2_t iMap = 0; iMap < fieldMaps.size(); ++iMap)
	for(u2_t iField = 0; iField < fields.size(); ++iField) {
		const ::llc::SJSONFieldBinding	& fieldToAdd			= fields[iField];
		if(fieldToAdd.Field.size() && fieldToAdd.Field == fieldMaps[iMap].Key) {
			llc_necs(indicesOfFields.push_back(iField));
			break;
		}
	}
	return indicesOfFields.size();
}

::llc::error_t			llc::jsonFieldsToMap
(	::llc::ai32											& indicesOfMaps
,	const ::llc::view<const ::llc::SJSONFieldBinding>	fields
,	const ::llc::view<const ::llc::TKeyValConstChar>	fieldMaps
) {
	u2_t					countFields					= fields.size();
	for(u2_t iField = 0; iField < countFields; ++iField) {
		bool						bNotAdded					= true;
		for(u2_t iMap = 0; iMap < fieldMaps.size(); ++iMap) {
			const ::llc::SJSONFieldBinding	& fieldToAdd			= fields[iField];
			if(fieldToAdd.Field.size() && fieldToAdd.Field == fieldMaps[iMap].Key) {
				llc_necs(indicesOfMaps.push_back(iMap));
				bNotAdded				= false;
				break;
			}
		}
		if(bNotAdded)
			llc_necs(indicesOfMaps.push_back(-1));
	}
	return indicesOfMaps.size();
}

::llc::error_t			llc::jsonFileRead			(::llc::SJSONFile & file, const ::llc::vcc & filename) {
	json_info_printf("Loading json file: %s.", filename.begin());
	llc_necall(llc::fileToMemory({filename.begin(), filename.size()}, file.Bytes), "Failed to load file: '%s'", filename.begin());
	return ::llc::jsonParse(file.Reader, file.Bytes);
}

::llc::error_t			llc::jsonArraySplit			(const ::llc::SJSONNode & jsonArrayToSplit, const ::llc::view<::llc::vcc> & jsonViews, const u2_t blockSize, ::llc::aobj<::llc::apod<char>> & outputJsons)		{
	const u2_t				remainder					= jsonArrayToSplit.Children.size() % blockSize;
	const u2_t				countParts					= jsonArrayToSplit.Children.size() / blockSize + one_if(remainder);
	llc_necs(outputJsons.resize(countParts));
	u2_t					iSourceRecord						= 0;
	for(u2_t iPart = 0; iPart < outputJsons.size(); ++iPart) {
		::llc::apod<char>			& outputJson				= outputJsons[iPart];
		llc_necs(outputJson.push_back('['));
		for(u2_t iPartRecord = 0, countPartRecords = (remainder && iPart == countParts - 1) ? remainder : blockSize
			; iPartRecord < countPartRecords
			; ++iPartRecord) {
			llc_necs(llc::jsonWrite(jsonArrayToSplit.Children[iSourceRecord++], jsonViews, outputJson));;
			if(iPartRecord < countPartRecords - 1)
				llc_necs(outputJson.push_back(','));
		}
		llc_necs(outputJson.push_back(']'));
	}
	return 0;
}

::llc::error_t			llc::jsonWrite				(const ::llc::SJSONNode* node, const ::llc::view<::llc::vcc> & jsonViews, ::llc::apod<char> & output)			{
	if(node->Token->Type == ::llc::JSON_TYPE_VALUE && node->Children.size())
		node					= node->Children[0];
	switch(node->Token->Type) {
	case ::llc::JSON_TYPE_INTEGER		: {
		char						temp[64];
#if defined(LLC_WINDOWS)
		snprintf(temp, ::llc::size(temp) - 2, "%lli", (uint64_t)node->Token->Value);
#else
		snprintf(temp, ::llc::size(temp) - 2, "%lli", (long long)node->Token->Value);
#endif
		output.append_string(temp);
	}
		break;
	case ::llc::JSON_TYPE_DECIMAL		: {
		double						f							= 0;
		memcpy(&f, &node->Token->Value, sizeof(double));
		char						temp[64]					= {};
		u2_t					lenNum						= snprintf(temp, ::llc::size(temp) - 2, "%.16f", f);
		while(lenNum > 0 && (temp[lenNum] == 0 || temp[lenNum] == '0')) {
			temp[lenNum] = 0;
			--lenNum;
		}
		llc_necs(output.append_string(temp));
	}
		break;
	case ::llc::JSON_TYPE_BOOLEAN			:
		llc_necs(output.append(bool2vcc(node->Token->Value)));
		break;
	case ::llc::JSON_TYPE_NULL			:
		llc_necs(output.append(jsonViews[node->ObjectIndex]));
		break;
	case ::llc::JSON_TYPE_STRING		:
		llc_necs(output.push_back('"'));
		llc_necs(output.append(jsonViews[node->ObjectIndex]));
		llc_necs(output.push_back('"'));
		break;
	case ::llc::JSON_TYPE_OBJECT		:
		llc_necs(output.push_back('{'));
		for(u2_t iChildren = 0; iChildren < node->Children.size(); iChildren += 2) {
			llc_necs(llc::jsonWrite(node->Children[iChildren + 0], jsonViews, output));;
			llc_necs(output.push_back(':'));
			llc_necs(llc::jsonWrite(node->Children[iChildren + 1], jsonViews, output));;
			if(iChildren < node->Children.size() - 2)
				llc_necs(output.push_back(','));
		}
		llc_necs(output.push_back('}'));
		break;
	case ::llc::JSON_TYPE_ARRAY			:
		llc_necs(output.push_back('['));
		for(u2_t iChildren = 0; iChildren < node->Children.size(); ++iChildren) {
			llc_necs(llc::jsonWrite(node->Children[iChildren], jsonViews, output));;
			if(iChildren < node->Children.size() - 1)
				llc_necs(output.push_back(','));
		}
		llc_necs(output.push_back(']'));
	}
	return 0;
}

static	::llc::error_t	jsonCloseElement			(::llc::SJSONReaderState & stateReader, ::llc::apod<::llc::SJSONToken> & tokens, u2_t indexChar) {
	ree_if(tokens.size() <= (u2_t)stateReader.IndexCurrentElement, "Invalid parser state. Cannot close element: %" LLC_FMT_I32 ".", stateReader.IndexCurrentElement);
	::llc::SJSONToken			* closing					= 0;
	closing					= stateReader.CurrentElement; //&object[stateReader.IndexCurrentElement];
	closing->Span.End		= (u2_t)indexChar + 1;
	const ::llc::vcc			labelType				= ::llc::get_value_label(closing->Type);
	const char					* labelText				= labelType.begin();
	(void)labelText;
	json_info_printf("%s closed. Index %.2i. Level: %" LLC_FMT_I32 ". Parent index: %" LLC_FMT_I32 ". Node type: %" LLC_FMT_I32 ". Begin: %" LLC_FMT_I32 ". End: %" LLC_FMT_I32 ".", labelText, stateReader.IndexCurrentElement, stateReader.NestLevel, closing->ParentIndex, closing->Type, closing->Span.Begin, closing->Span.End);
	stateReader.IndexCurrentElement					= closing->ParentIndex;
	--stateReader.NestLevel;
	stateReader.CurrentElement						= ((u2_t)stateReader.IndexCurrentElement < tokens.size()) ? &tokens[stateReader.IndexCurrentElement] : 0;
	if(0 == stateReader.NestLevel)
		stateReader.DoneReading							= true;
	return 0;	// Need to report that a list has been exited
}

static	::llc::error_t	jsonCloseElement			(::llc::SJSONReaderState & stateReader, ::llc::apod<::llc::SJSONToken> & object, u2_t indexChar, ::llc::JSON_TYPE jsonType) {
	const ::llc::SJSONToken		* open						= stateReader.CurrentElement; //&object[stateReader.IndexCurrentElement];
	ree_if(jsonType != open->Type, "Invalid object type: open: %" LLC_FMT_U32 " (%s). closing: %" LLC_FMT_U32 " (%s).", open->Type, ::llc::get_value_label(open->Type).begin(), jsonType, ::llc::get_value_label(jsonType).begin());
	return ::jsonCloseElement(stateReader, object, indexChar);
}

static	::llc::error_t	jsonTestAndCloseValue		(::llc::SJSONReaderState & stateReader, ::llc::apod<::llc::SJSONToken> & object) {
	if(stateReader.CurrentElement && ::llc::JSON_TYPE_VALUE == stateReader.CurrentElement->Type) {
		stateReader.ExpectingSeparator	= true;	// actually we expect the separator AFTER calling jsonCloseElement(). However, such function doesn't care about this value, so we can simplify the code by reversing the operations.
		return ::jsonCloseElement(stateReader, object, stateReader.IndexCurrentChar);
	}
	return 1;
}

#define seterr_break_if(condition, format, ...)	\
	if(condition) {								\
		errVal					= -1;			\
		json_error_printf(format, __VA_ARGS__);		\
		break;									\
	}

#define seterr_if(condition, format, ...)	\
	if(condition) {								\
		errVal					= -1;			\
		json_error_printf(format, __VA_ARGS__);		\
	}

static	::llc::error_t	jsonParseStringCharacter	(::llc::SJSONReaderState & stateReader, ::llc::apod<::llc::SJSONToken> & tokens, const ::llc::vcc & jsonAsString)	{
	::llc::SJSONToken			currentElement				= {};
	::llc::error_t				errVal						= 0;
	switch(stateReader.CharCurrent) {
	default:
		seterr_break_if(((::llc::uc_t)stateReader.CharCurrent) < 0x20 || ((::llc::uc_t)stateReader.CharCurrent) > 0xFE, "Invalid character: %" LLC_FMT_I32 " (%" LLC_FMT_U32 ") '%c'.", stateReader.CharCurrent, (::llc::uc_t)stateReader.CharCurrent, stateReader.CharCurrent);
		seterr_break_if(stateReader.Escaping, "Cannot escape character: %" LLC_FMT_I32 " (%" LLC_FMT_U32 ") '%c'.", stateReader.CharCurrent, (::llc::uc_t)stateReader.CharCurrent, stateReader.CharCurrent);
		break;
	case ' '	: case '\t'	: case '\r'	: case '\n'	: case '\f'	: case '\b'	: // Skip these characters without error.
		::llc::skipToNextCharacter(stateReader.IndexCurrentChar, jsonAsString);
		--stateReader.IndexCurrentChar;
		break;
	case 'b': case 'f': case 'n': case 'r': case 't':
		break;	// these characters are both valid as part of the string and as escapable characters.
	case 'u':
		if(false == stateReader.Escaping)
			break;
		stateReader.IndexCurrentChar	+= 1;	// skip the u to get the next 4 digits.
		seterr_break_if(jsonAsString.size() - stateReader.IndexCurrentChar < 4, "End of stream during unicode code point parsing. JSON length: %s. Current index: %" LLC_FMT_U32 ".", jsonAsString.size(), stateReader.IndexCurrentChar);
		json_info_printf("Unicode code point found: %4.4s", &jsonAsString[stateReader.IndexCurrentChar]);
		currentElement		= {stateReader.IndexCurrentElement, ::llc::JSON_TYPE_CODEPOINT, {stateReader.IndexCurrentChar, stateReader.IndexCurrentChar + 4}};
		seterr_if(errored(tokens.push_back(currentElement)), "token count: %" LLC_FMT_I32 "", tokens.size());
		stateReader.CurrentElement		= &tokens[stateReader.IndexCurrentElement];
		stateReader.IndexCurrentChar	+= 3;	// Parse unicode code point
		break;
	case '\\'	:
		if(false == stateReader.Escaping) {
			stateReader.Escaping			= true;
			return 0;
		}
		break;
	case '"'	:
		if(false == stateReader.Escaping) {
			seterr_if(errored(::jsonCloseElement(stateReader, tokens, stateReader.IndexCurrentChar - 1, ::llc::JSON_TYPE_STRING)), "Failed to close string elment at character %" LLC_FMT_I32 "", stateReader.IndexCurrentChar - 1);//::llc::get_value_namep(tokens));
			stateReader.InsideString		= false;
			::jsonTestAndCloseValue(stateReader, tokens);
			stateReader.ExpectingSeparator	= true;	// actually we expect the separator AFTER calling jsonCloseElement(). However, such function doesn't care about this value, so we can simplify the code by reversing the operations.
		}
	}
	stateReader.Escaping	= false;
	return errVal;
}

static	::llc::error_t	jsonParseKeyword			(const ::llc::vcc & token, ::llc::JSON_TYPE jsonType, ::llc::SJSONReaderState & stateReader, ::llc::apod<::llc::SJSONToken> & object, const ::llc::vcc & jsonAsString)	{
	ree_if(token.size() > jsonAsString.size() - stateReader.IndexCurrentChar, "End of stream while parsing token: %s.", token.begin());
	ree_if(0 != strncmp(token.begin(), &jsonAsString[stateReader.IndexCurrentChar], token.size()), "Unrecognized token found while looking for '%s'.", token.begin());
	json_info_printf("JSON token found: %s.", token.begin());

	::llc::SJSONToken			boolElement					= {stateReader.IndexCurrentElement, jsonType, {stateReader.IndexCurrentChar, stateReader.IndexCurrentChar + token.size()}, ::llc::vcc2bool(token)};
	llc_necall(object.push_back(boolElement), "Failed to push! Out of memory? object count: %" LLC_FMT_U32 ".", object.size());
	stateReader.IndexCurrentChar	+= token.size() - 1;
	stateReader.CurrentElement		= &object[stateReader.IndexCurrentElement];
	return 0;
}

static	::llc::error_t	lengthJsonNumber			(u2_t indexCurrentChar, const ::llc::vcc & jsonAsString)	{
	const u2_t				offset						= indexCurrentChar;
	char						charCurrent					= jsonAsString[indexCurrentChar];
	while(indexCurrentChar < jsonAsString.size() &&
		( ( charCurrent >= '1' && charCurrent <= '9')
		 || charCurrent == '0'
		 || charCurrent == '.'
		 )
		) {
		++indexCurrentChar;
		if(indexCurrentChar >= jsonAsString.size())
			break;
		charCurrent				= jsonAsString[indexCurrentChar];
	}
	return indexCurrentChar - offset;
}

//static	::llc::error_t	parseJsonAbsolutePart		(::llc::SJSONReaderState & stateReader, ::llc::apod<::llc::SJSONToken> & tokens, ::llc::vcc absolutePart, ::llc::SJSONToken & output, const u2_t sizeNum, const bool isFloat, const u2_t index, const int32_t indexCurrentElement, const int32_t indexCurrentChar)	{
//	output					= {indexCurrentElement, isFloat ? ::llc::JSON_TYPE_DECIMAL : ::llc::JSON_TYPE_INTEGER, {(u2_t)indexCurrentChar, indexCurrentChar + sizeNum + (index - indexCurrentChar)}};
//	::llc::error_t				intCount					= ::llc::parseIntegerDecimal(absolutePart, output.Value);
//	if(intCount < (int32_t)sizeNum) {
//		output.Type		= ::llc::JSON_TYPE_DECIMAL;
//		double						finalValue					= (double)output.Value;
//		json_info_printf("Integer part: %f.", finalValue);
//		++intCount;	// Skip dot.
//		const u2_t				offsetStart					= output.Span.Begin + sizeNum - (sizeNum - intCount);
//		const u2_t				lenDec						= sizeNum - intCount;
//		if(lenDec) {
//			double						decValue					= 0;
//			if(absolutePart[0] == '.')
//				llc_necs(absolutePart.slice(absolutePart, offsetStart + 1, lenDec - 1));
//			else
//				llc_necs(absolutePart.slice(absolutePart, offsetStart, lenDec));
//			const ::llc::error_t		decCount					= ::llc::parseIntegerDecimal(absolutePart, decValue);
//			rees_if(errored(decCount));
//			decValue				/= ::llc::powui(10, decCount);
//			json_info_printf("Decimal part: %f.", decValue);
//			finalValue				+= decValue;
//		}
//		memcpy((double*)&output.Value, &finalValue, sizeof(uint64_t));
//	}
//	else {
//		json_info_printf("Integer part: %" LLC_FMT_I32 ".", output.Value);
//	}
//	return 0;
//}

static	::llc::error_t	parseSign					(const ::llc::vcc & strNumber, bool & isNegative, bool & isFloat)	{
	u2_t					index						= 0;
	if(index < strNumber.size() && strNumber[index] == '+')
		++index;
	if((isNegative = index < strNumber.size() && strNumber[index] == '-')) {
		++index;
	}
	if(index < strNumber.size() && strNumber[index] == '+')
		++index;
	if((isFloat = index < strNumber.size() && strNumber[index] == '.')) {
		++index;
	}
	return (::llc::error_t)index;
}

static	::llc::error_t	parseJsonNumber				(::llc::SJSONReaderState & stateReader, ::llc::apod<::llc::SJSONToken> & tokens, const ::llc::vcc & jsonAsString)	{
	const u2_t				offset						= stateReader.IndexCurrentChar;
	char						charCurrent					= jsonAsString[offset];

	bool						isNegative					= false;
	bool						isFloat						= false;
	int							signLength					= parseSign({&jsonAsString[offset], jsonAsString.size() - offset}, isNegative, isFloat);
	u2_t					index						= offset + signLength;
	charCurrent				= jsonAsString[index];
	ree_if(index < jsonAsString.size() && (charCurrent != '0' && (charCurrent < '1' || charCurrent > '9')), "Character '%c' at index %" LLC_FMT_I32 " is not a number.", charCurrent, index);

	const u2_t				sizeNum						= lengthJsonNumber(index, jsonAsString);
	::llc::SJSONToken			currentElement				= {stateReader.IndexCurrentElement, isFloat ? ::llc::JSON_TYPE_DECIMAL : ::llc::JSON_TYPE_INTEGER, {stateReader.IndexCurrentChar, stateReader.IndexCurrentChar + signLength + sizeNum}};
	::llc::vcc					numString					= {};
	llc_necs(jsonAsString.slice(numString, index, sizeNum));

	::llc::error_t				intCount					= ::llc::parseIntegerDecimal(numString, currentElement.Value = 0);
	if(isFloat) { // The number begins with a dot and we already skipped it so calculate decimal places for the fractional part.
		double						valuef64					= currentElement.Value / double(::llc::powui(10, numString.size()));
		if(isNegative) {
			valuef64 	*= -1;
		}
		memcpy(&(currentElement.Value = 0), &valuef64, sizeof(uint64_t));
		json_info_printf("Decimal read: %f.", valuef64);
	}
	else { // there is an integer part so we need to check for decimals
		if(intCount >= (int32_t)sizeNum) // No more digits after the integer part. Leave it this way.
			json_info_printf("Integer read: %lli.", currentElement.Value);
		else { 
			json_info_printf("Integer part: %lli.", currentElement.Value);
			currentElement.Type		= ::llc::JSON_TYPE_DECIMAL;
			double						finalValue					= (double)currentElement.Value;
			++intCount;	// Skip dot.
			int32_t						lenDec						= sizeNum - intCount;
			if(lenDec > 0) { // there are leftover digits after the integer part
				u2_t					offsetStart					= currentElement.Span.Begin + sizeNum - (sizeNum - intCount);
				double						decValue					= 0;
				llc_necs(jsonAsString.slice(numString, offsetStart, lenDec));
				const ::llc::error_t		decCount					= ::llc::parseIntegerDecimal(numString, decValue);
				rees_if_failed(decCount);
				decValue				/= ::llc::powui(10, decCount);
				json_info_printf("Decimal part: %f.", decValue);
				finalValue				+= decValue;
			}
			if(isNegative)
				finalValue *= -1;
			memcpy(&currentElement.Value, &finalValue, sizeof(uint64_t));
		}
	}
	llc_necs(tokens.push_back(currentElement));
	stateReader.CurrentElement						= &tokens[stateReader.IndexCurrentElement];
	json_info_printf("Number found: %s. Length: %" LLC_FMT_U32 ". Negative: %s. Float: %s."
		, ::llc::toString({&jsonAsString[index], sizeNum}).begin()
		, sizeNum
		, isNegative	? "true" : "false"
		, isFloat		? "true" : "false"
	);
	stateReader.IndexCurrentChar					+= sizeNum + (index - offset) - 1;
	if(stateReader.IndexCurrentChar + 1 < jsonAsString.size() - 1) {
		charCurrent										= jsonAsString[stateReader.IndexCurrentChar+1];
		ree_if(charCurrent != ' '
			&& charCurrent != '\t'
			&& charCurrent != '\n'
			&& charCurrent != '\r'
			&& charCurrent != '\n'
			&& charCurrent != ']'
			&& charCurrent != '}'
			&& charCurrent != ','
			, "Invalid number termination: '%c'.", charCurrent);
	}
	return 0;
}

static	::llc::error_t	jsonTestAndCloseKey			(::llc::SJSONReaderState & stateReader, ::llc::apod<::llc::SJSONToken> & tokens) {
	if(stateReader.CurrentElement && ::llc::JSON_TYPE_KEY == stateReader.CurrentElement->Type) {
		stateReader.ExpectingSeparator	= true;	// actually we expect the separator AFTER calling jsonCloseElement(). However, such function doesn't care about this value, so we can simplify the code by reversing the operations.
		return ::jsonCloseElement(stateReader, tokens, stateReader.IndexCurrentChar);
	}
	return 1;
}

static	::llc::error_t	jsonCloseOrDiscardEmptyKOrV	(::llc::SJSONReaderState & stateReader, ::llc::apod<::llc::SJSONToken> & tokens, ::llc::JSON_TYPE containerType) {
	::llc::error_t				errVal						= 0;
	if(tokens[tokens.size() - 1].Type == containerType) {
		json_info_printf("Discarding empty container element at index %" LLC_FMT_I32 " (%s). Level: %" LLC_FMT_I32 "", tokens.size() - 1, ::llc::get_value_label(containerType).begin(), stateReader.NestLevel);
		stateReader.IndexCurrentElement	= tokens[tokens.size() - 1].ParentIndex;
		llc_necs(tokens.pop_back());
		--stateReader.NestLevel;
		if((u2_t)stateReader.IndexCurrentElement < tokens.size())
			stateReader.CurrentElement									= &tokens[stateReader.IndexCurrentElement];
	}
	else {
		json_info_printf("Closing container at index %" LLC_FMT_I32 " (%s).", tokens.size() - 1, ::llc::get_value_label(containerType).begin());
			 if(::llc::JSON_TYPE_VALUE	== containerType) errVal = ::jsonTestAndCloseValue	(stateReader, tokens);
		else if(::llc::JSON_TYPE_KEY	== containerType) errVal = ::jsonTestAndCloseKey	(stateReader, tokens);
	}
	return errVal;
}
static	::llc::error_t	jsonCloseContainer			(::llc::SJSONReaderState & stateReader, ::llc::apod<::llc::SJSONToken> & tokens, ::llc::JSON_TYPE containerType) {
	::llc::error_t				errVal						= 0;
	llc_necall(::jsonCloseOrDiscardEmptyKOrV(stateReader, tokens, (::llc::JSON_TYPE_ARRAY == containerType) ? ::llc::JSON_TYPE_VALUE : ::llc::JSON_TYPE_KEY), "Failed to close container at index %" LLC_FMT_I32 " (%s).", stateReader.IndexCurrentElement, ::llc::get_value_label(containerType).begin());
	errVal					= ::jsonCloseElement(stateReader, tokens, stateReader.IndexCurrentChar, containerType);
	(void)errVal;
	stateReader.ExpectingSeparator	= false;
	if(stateReader.NestLevel > 0) // Root container isn't inside a value. Every other container is.
		return ::jsonTestAndCloseValue(stateReader, tokens);
	return 0;
}

static	::llc::error_t	jsonOpenElement				(::llc::SJSONReaderState & stateReader, ::llc::apod<::llc::SJSONToken> & tokens, ::llc::JSON_TYPE jsonType, u2_t indexChar) {
	::llc::SJSONToken			currentElement				= {stateReader.IndexCurrentElement, jsonType, {indexChar, indexChar}};
	llc_necs(stateReader.IndexCurrentElement = tokens.push_back(currentElement));
	stateReader.CurrentElement	= &tokens[stateReader.IndexCurrentElement];
	const ::llc::vcc			labelType					= ::llc::get_value_label(currentElement.Type);
	(void)labelType;
	++stateReader.NestLevel;
	json_info_printf("%s open. Index %.2i. Level: %" LLC_FMT_I32 ". Parent index: %" LLC_FMT_I32 ". Node type: %" LLC_FMT_I32 ". Begin: %" LLC_FMT_I32 ".", labelType.begin(), stateReader.IndexCurrentElement, stateReader.NestLevel, currentElement.ParentIndex, currentElement.Type, currentElement.Span.Begin);
	return 0;
}

static	::llc::error_t	jsonParseDocumentCharacter	(::llc::SJSONReaderState & stateReader, ::llc::apod<::llc::SJSONToken> & tokens, const ::llc::vcc & jsonAsString)	{
	::llc::error_t				errVal						= 0;
	::llc::error_t				nextMatch					= -1;
#define LLC_JSON_EXPECTS_SEPARATOR()		\
	if (stateReader.ExpectingSeparator) {	\
		errVal					= -1; 		\
		json_error_printf("Expected separator, found '%c'.", stateReader.CharCurrent); 	\
		break; 								\
	}

#define test_first_position()	ree_if(0 == stateReader.CharCurrent, "Character found at invalid position. Index: %" LLC_FMT_U32 ". Character: %c.", stateReader.IndexCurrentChar, stateReader.CharCurrent);

	switch(stateReader.CharCurrent) {
	case ' '	: case '\t'	: case '\r'	: case '\n'	: case '\f'	: case '\b'	: // Skip these characters without error.
		break;
	default: // Fallback error for every character that is not recognized by the parser.
		LLC_JSON_EXPECTS_SEPARATOR();
		errVal		= -1;
		json_error_printf("Invalid character at index %" LLC_FMT_I32 ". '%c'", stateReader.IndexCurrentChar, stateReader.CharCurrent);
		break;
	case '/':
		seterr_break_if(stateReader.IndexCurrentChar >= jsonAsString.size() || '/' != jsonAsString[stateReader.IndexCurrentChar + 1], "Invalid character at index %" LLC_FMT_I32 ". '%c'", stateReader.IndexCurrentChar, stateReader.CharCurrent);
		if(-1 != (nextMatch = ::llc::find('\n', jsonAsString, stateReader.IndexCurrentChar)))
			stateReader.IndexCurrentChar	= nextMatch - 1;
		else
			stateReader.IndexCurrentChar	= jsonAsString.size() - 1;
	break;
	case 'f': LLC_JSON_EXPECTS_SEPARATOR(); if(-1 == stateReader.IndexCurrentElement) ree_if(errored(::jsonOpenElement(stateReader, tokens, ::llc::JSON_TYPE_VALUE, stateReader.IndexCurrentChar)), "Failed to open element at index %" LLC_FMT_I32 ".", tokens.size()); errVal = ::jsonParseKeyword(::llc::VCC_FALSE	, ::llc::JSON_TYPE_BOOLEAN, stateReader, tokens, jsonAsString); ::jsonTestAndCloseValue(stateReader, tokens); break;
	case 't': LLC_JSON_EXPECTS_SEPARATOR(); if(-1 == stateReader.IndexCurrentElement) ree_if(errored(::jsonOpenElement(stateReader, tokens, ::llc::JSON_TYPE_VALUE, stateReader.IndexCurrentChar)), "Failed to open element at index %" LLC_FMT_I32 ".", tokens.size()); errVal = ::jsonParseKeyword(::llc::VCC_TRUE	, ::llc::JSON_TYPE_BOOLEAN, stateReader, tokens, jsonAsString); ::jsonTestAndCloseValue(stateReader, tokens); break;
	case 'n': LLC_JSON_EXPECTS_SEPARATOR(); if(-1 == stateReader.IndexCurrentElement) ree_if(errored(::jsonOpenElement(stateReader, tokens, ::llc::JSON_TYPE_VALUE, stateReader.IndexCurrentChar)), "Failed to open element at index %" LLC_FMT_I32 ".", tokens.size()); errVal = ::jsonParseKeyword(::llc::VCC_NULL	, ::llc::JSON_TYPE_NULL, stateReader, tokens, jsonAsString); ::jsonTestAndCloseValue(stateReader, tokens); break;
	case '0': case '1'	: case '2'	: case '3'	: case '4'	: case '5'	: case '6'	: case '7'	: case '8'	: case '9'	:
	case '.': case '-'	: case '+'	: //case 'x'	: // parse int or float accordingly
		LLC_JSON_EXPECTS_SEPARATOR();
		if(-1 == stateReader.IndexCurrentElement)
			ree_if(errored(::jsonOpenElement(stateReader, tokens, ::llc::JSON_TYPE_VALUE, stateReader.IndexCurrentChar)), "Failed to open element at index %" LLC_FMT_I32 ".", tokens.size());
		seterr_break_if(stateReader.Escaping, "Invalid character found at index %" LLC_FMT_U32 ": %c.", stateReader.IndexCurrentChar, stateReader.CharCurrent);	// Set an error or something and skip this character.
		seterr_break_if(::llc::JSON_TYPE_VALUE != stateReader.CurrentElement->Type, "%s", "Number found outside a value.");
		seterr_break_if(errored(::parseJsonNumber(stateReader, tokens, jsonAsString)), "%s", "Error parsing JSON number.");
		::jsonTestAndCloseValue(stateReader, tokens);
		break;
	case ',':
		test_first_position();
		seterr_break_if(false == stateReader.ExpectingSeparator, "Separator found when not expected at index %" LLC_FMT_I32 ".", stateReader.IndexCurrentChar);
		if(::llc::JSON_TYPE_OBJECT == stateReader.CurrentElement->Type)
			errVal	= ::jsonOpenElement(stateReader, tokens, ::llc::JSON_TYPE_KEY, stateReader.IndexCurrentChar + 1);
		else if(::llc::JSON_TYPE_ARRAY == stateReader.CurrentElement->Type) // Test
			errVal	= ::jsonOpenElement(stateReader, tokens, ::llc::JSON_TYPE_VALUE, stateReader.IndexCurrentChar + 1);
		stateReader.ExpectingSeparator	= false;
		break;
	case ':':
		test_first_position();
		seterr_break_if(false == stateReader.ExpectingSeparator && ::llc::JSON_TYPE_KEY != stateReader.CurrentElement->Type, "Separator found when not expected at index %" LLC_FMT_I32 ".", stateReader.IndexCurrentChar); // Test if we should be expecting this separator or not.
		stateReader.ExpectingSeparator	= false;
		seterr_break_if(errored(::jsonCloseElement(stateReader, tokens, stateReader.IndexCurrentChar - 1, ::llc::JSON_TYPE_KEY) ), "Failed to close key. %s", "Unknown error.");	// close the key before the : character
		seterr_break_if(errored(::jsonOpenElement(stateReader, tokens, ::llc::JSON_TYPE_VALUE, stateReader.IndexCurrentChar + 1)), "Failed to open element at index %" LLC_FMT_I32 ".", tokens.size()); // open the value after the : character
		break;
	case ']': test_first_position(); errVal = ::jsonCloseContainer(stateReader, tokens, ::llc::JSON_TYPE_ARRAY); break;
	case '}': test_first_position(); seterr_break_if(::llc::JSON_TYPE_KEY == stateReader.CurrentElement->Type && tokens.size() - 1 != (u2_t)stateReader.IndexCurrentElement, "Invalid format: %s", "Keys cannot be left without a value."); errVal = ::jsonCloseContainer(stateReader, tokens, ::llc::JSON_TYPE_OBJECT); break;
	case '{': LLC_JSON_EXPECTS_SEPARATOR(); errVal = ::jsonOpenElement(stateReader, tokens, ::llc::JSON_TYPE_OBJECT	, stateReader.IndexCurrentChar); if(0 <= errVal) { errVal = jsonOpenElement(stateReader, tokens, ::llc::JSON_TYPE_KEY	, stateReader.IndexCurrentChar + 1); } break;
	case '[': LLC_JSON_EXPECTS_SEPARATOR(); errVal = ::jsonOpenElement(stateReader, tokens, ::llc::JSON_TYPE_ARRAY	, stateReader.IndexCurrentChar); if(0 <= errVal) { errVal = jsonOpenElement(stateReader, tokens, ::llc::JSON_TYPE_VALUE	, stateReader.IndexCurrentChar + 1); } break;
	case '"': LLC_JSON_EXPECTS_SEPARATOR(); errVal = ::jsonOpenElement(stateReader, tokens, ::llc::JSON_TYPE_STRING	, stateReader.IndexCurrentChar + 1);	// skip the " character in order to set the begin the string
		stateReader.InsideString	= true;
		break;
	}
	stateReader.Escaping	= false;
	return errVal;
}

::llc::error_t			llc::jsonParseStep			(::llc::SJSONReader & reader, const ::llc::vcc & jsonAsString)	{
	reader.StateRead.CharCurrent	= jsonAsString[reader.StateRead.IndexCurrentChar];
	::llc::error_t				errVal						= (reader.StateRead.InsideString)
		? ::jsonParseStringCharacter	(reader.StateRead, reader.Token, jsonAsString)
		: ::jsonParseDocumentCharacter	(reader.StateRead, reader.Token, jsonAsString)
		;
	if (errored(errVal)) {
		const bool					validElement				= (u2_t)reader.StateRead.IndexCurrentElement < reader.Token.size();
		const ::llc::SJSONToken		* currentElement			= validElement ? &reader.Token[reader.StateRead.IndexCurrentElement] : 0;
		json_error_printf("Error during read step. Malformed JSON?"
			"\nPosition  : %" LLC_FMT_I32 "."
			"\nCharacter : '%c' (0x%x)."
			"\nElement   : %" LLC_FMT_I32 "."
			"\nString    : %s."
			"\nEscaping  : %s."
			"\nNestLevel : %" LLC_FMT_I32 "."
			"\nParent    : %" LLC_FMT_I32 "."
			"\nType      : %" LLC_FMT_I32 " (%s)."
			"\nOffset    : %" LLC_FMT_I32 "."
			, reader.StateRead.IndexCurrentChar
			, reader.StateRead.CharCurrent, reader.StateRead.CharCurrent
			, reader.StateRead.IndexCurrentElement
			, reader.StateRead.InsideString ? "true" : "false"
			, reader.StateRead.Escaping		? "true" : "false"
			, reader.StateRead.NestLevel
			, validElement ? currentElement->ParentIndex					: -1
			, validElement ? currentElement->Type							: -1
			, validElement ? ::llc::get_value_namep(currentElement->Type)	: "N/A"
			, validElement ? currentElement->Span.Begin						: -1
		);
	}
	return errVal;
}

::llc::error_t			llc::jsonTreeRebuild		(::llc::view<::llc::SJSONToken>& in_object, ::llc::apobj<::llc::SJSONNode> & out_nodes)								{
	::llc::apobj<::llc::SJSONNode>	& tree					= out_nodes;
	llc_necs(tree.resize(in_object.size()));

	// -- Build all nodes linearly, without assigning the children
	for(u2_t iObject = 0; iObject < tree.size(); ++iObject) {
		::llc::pobj<::llc::SJSONNode>	& nodeCurrent		= tree[iObject];
		if(!nodeCurrent) {
			rees_if(0 == nodeCurrent.create());
		}
		nodeCurrent->Token			= &in_object[iObject];
		nodeCurrent->Parent			= ((u2_t)nodeCurrent->Token->ParentIndex < tree.size()) ? (llc::SJSONNode*)tree[nodeCurrent->Token->ParentIndex] : nullptr;
		nodeCurrent->ObjectIndex	= iObject;
		nodeCurrent->Children.clear();
		if(nodeCurrent->Parent)
			llc_necs(nodeCurrent->Parent->Children.push_back(nodeCurrent));
	}

	// -- Remove the key/value wrappers from objects.
	for(u2_t iObject = 0, countNodes = tree.size(); iObject < countNodes; ++iObject) {
		::llc::pobj<::llc::SJSONNode>				& nodeCurrent										= tree[iObject];
		rees_if(!nodeCurrent);
		if( ::llc::JSON_TYPE_ARRAY	!= nodeCurrent->Token->Type
		 && ::llc::JSON_TYPE_OBJECT	!= nodeCurrent->Token->Type
		)
			continue;
		::llc::apobj<::llc::SJSONNode>	newChildren;
		llc_necs(newChildren.resize(nodeCurrent->Children.size()));
		for(u2_t iChild = 0, countChild = newChildren.size(); iChild < countChild; ++iChild)
			newChildren[iChild]						= nodeCurrent->Children[iChild]->Children[0];
		nodeCurrent->Children					= newChildren;
	}
	return 0;
}

#define json_bi_if(condition, format, ...) if(condition) break; //

::llc::error_t			llc::jsonParse				(::llc::SJSONReader & reader, const ::llc::vcc & jsonAsString)	{
	::llc::SJSONReaderState		& stateReader				= reader.StateRead;
	for(stateReader.IndexCurrentChar = 0; stateReader.IndexCurrentChar < jsonAsString.size(); ++stateReader.IndexCurrentChar) {
		llc_necs(llc::jsonParseStep(reader, jsonAsString));
		json_bi_if(reader.StateRead.DoneReading, "%" LLC_FMT_I32 " json characters read.", stateReader.IndexCurrentChar + 1);
	}
	ree_if(stateReader.NestLevel, "Nest level: %" LLC_FMT_I32 " (Needs to be zero).", stateReader.NestLevel);
	llc_necs(reader.View.resize(reader.Token.size()));
	for(u2_t iView = 0; iView < reader.View.size(); ++iView) {
		const ::llc::SJSONToken		& currentElement									= reader.Token[iView];
		llc_necs(jsonAsString.slice(reader.View[iView], currentElement.Span.Begin, currentElement.Span.End - currentElement.Span.Begin));
	}
	return ::llc::jsonTreeRebuild(reader.Token, reader.Tree);
}

::llc::error_t			llc::jsonObjectKeyList		(const ::llc::SJSONNode & node_object, const ::llc::view<::llc::vcc> & views, ::llc::ai32 & indices, ::llc::avcc & keys)	{
	ree_if(::llc::JSON_TYPE_OBJECT != node_object.Token->Type, "Invalid node type: %" LLC_FMT_I32 " (%s). Only objects are allowed to be accessed by key.", node_object.Token->Type, ::llc::get_value_label(node_object.Token->Type).begin());
	for(u2_t iNode = 0, countNodes = node_object.Children.size(); iNode < countNodes; iNode += 2) {
		const ::llc::SJSONNode		* node					= node_object.Children[iNode];
		ree_if(::llc::JSON_TYPE_STRING != node->Token->Type, "Invalid node type: %" LLC_FMT_U32 " (%s). Only string types (%" LLC_FMT_U32 ") can be keys of JSON objects.", node->Token->Type, ::llc::get_value_label(node->Token->Type).begin(), ::llc::JSON_TYPE_STRING);
		const ::llc::vcc			& view					= views[node->ObjectIndex];
		llc_necs(indices.push_back(node->ObjectIndex));
		llc_necs(keys	.push_back(view));
	}
	return indices.size();
}

::llc::error_t			llc::jsonObjectKeyList		(const ::llc::SJSONNode & node_object, ::llc::ai32 & indices)	{
	ree_if(::llc::JSON_TYPE_OBJECT != node_object.Token->Type, "Invalid node type: %" LLC_FMT_I32 " (%s). Only objects are allowed to be accessed by key.", node_object.Token->Type, ::llc::get_value_label(node_object.Token->Type).begin());
	for(u2_t iNode = 0, countNodes = node_object.Children.size(); iNode < countNodes; iNode += 2) {
		const ::llc::SJSONNode		* node						= node_object.Children[iNode];
		ree_if(::llc::JSON_TYPE_STRING != node->Token->Type, "Invalid node type: %" LLC_FMT_U32 " (%s). Only string types (%" LLC_FMT_U32 ") can be keys of JSON objects.", node->Token->Type, ::llc::get_value_label(node->Token->Type).begin(), ::llc::JSON_TYPE_STRING);
		llc_necs(indices.push_back(node->ObjectIndex));
	}
	return indices.size();
}

::llc::error_t			llc::jsonObjectKeyList		(const ::llc::SJSONNode & node_object, const ::llc::view<::llc::vcc> & views, ::llc::avcc & keys)	{
	ree_if(::llc::JSON_TYPE_OBJECT != node_object.Token->Type, "Invalid node type: %" LLC_FMT_I32 " (%s). Only objects are allowed to be accessed by key.", node_object.Token->Type, ::llc::get_value_label(node_object.Token->Type).begin());
	for(u2_t iNode = 0, countNodes = node_object.Children.size(); iNode < countNodes; iNode += 2) {
		const ::llc::SJSONNode		* node						= node_object.Children[iNode];
		ree_if(::llc::JSON_TYPE_STRING != node->Token->Type, "Invalid node type: %" LLC_FMT_U32 " (%s). Only string types (%" LLC_FMT_U32 ") can be keys of JSON objects.", node->Token->Type, ::llc::get_value_label(node->Token->Type).begin(), ::llc::JSON_TYPE_STRING);
		const ::llc::vcc			& view						= views[node->ObjectIndex];
		llc_necs(keys.push_back(view));
	}
	return keys.size();
}

::llc::error_t			llc::jsonObjectValueGet		(const ::llc::SJSONNode & node_object, const ::llc::view<::llc::vcc> & views, const ::llc::vcs & key)	{
	ree_if(::llc::JSON_TYPE_OBJECT != node_object.Token->Type, "Invalid node type: %" LLC_FMT_I32 " (%s). Only objects are allowed to be accessed by key.", node_object.Token->Type, ::llc::get_value_label(node_object.Token->Type).begin());
	for(u2_t iNode = 0, countNodes = node_object.Children.size(); iNode < countNodes; iNode += 2) {
		const ::llc::SJSONNode		* node						= node_object.Children[iNode];
		ree_if(::llc::JSON_TYPE_STRING != node->Token->Type, "Invalid node type: %" LLC_FMT_U32 " (%s). Only string types (%" LLC_FMT_U32 ") can be keys of JSON objects.", node->Token->Type, ::llc::get_value_label(node->Token->Type).begin(), ::llc::JSON_TYPE_STRING);
		const ::llc::vcc			& view						= views[node->ObjectIndex];
		if(key == view)
			return (::llc::error_t)node->ObjectIndex + 2; // one for value and other for the actual element
	}
	return -1;
}

::llc::error_t			llc::jsonArrayValueGet		(const ::llc::SJSONNode& tree, u2_t index)				{
	ree_if(::llc::JSON_TYPE_ARRAY != tree.Token->Type, "Invalid node type: %" LLC_FMT_I32 " (%s). Only arrays are allowed to be accessed by index.", tree.Token->Type, ::llc::get_value_label(tree.Token->Type).begin());
	ree_if(index >= tree.Children.size(), "Index out of range: %" LLC_FMT_I32 ". Max index: %" LLC_FMT_I32 ".", index, tree.Children.size() - 1);
	const ::llc::SJSONNode		* node						= tree.Children[index];	// Get the
	ree_if(0 == node, "Invalid or corrupt tree. %s", "Nodes cannot be null.");
	return node->ObjectIndex;
}

::llc::error_t			llc::jsonCompareArray		(const ::llc::SJSONNode & node, const ::llc::view<::llc::vcc>& views, const ::llc::SJSONNode& other, const ::llc::view<::llc::vcc>& otherViews) {
	if(node.Children.size() != other.Children.size())
		return 0;
	if(node.Children.size() == 0)
		return 1;
	for(u2_t iChild = 0; iChild < node.Children.size(); ++iChild) {
		const ::llc::SJSONNode		& childNode					= *node	.Children[iChild];
		const ::llc::SJSONNode		& childOther				= *other.Children[iChild];
		const ::llc::JSON_TYPE		typeNode					= childNode	.Token->Type;
		const ::llc::JSON_TYPE		typeOther					= childOther.Token->Type;
		if(typeNode != typeOther)
			return 0;
		::llc::error_t				result						= -1;
		switch(typeNode) {
		case ::llc::JSON_TYPE_ARRAY		: result = ::llc::jsonCompareArray	(childNode, views, childOther, otherViews); break;
		case ::llc::JSON_TYPE_OBJECT	: result = ::llc::jsonCompareObject	(childNode, views, childOther, otherViews); break;
		case ::llc::JSON_TYPE_DECIMAL	:
		case ::llc::JSON_TYPE_INTEGER	: result = ::llc::jsonCompareNumber	(childNode, views, childOther, otherViews); break;
		default:
			result					= views[node.ObjectIndex] == otherViews[other.ObjectIndex];
		}
		if(0 == result)
			return 0;
	}
	if(views[node.ObjectIndex] == otherViews[other.ObjectIndex])
		return 1;
	return 1;
}

// Get the codepoint from characters of an unicode escape sequence
//	For input "\u c1 c2 c3 c4" the codepoint is:
//		(c1 * 0x1000)	+ (c2 * 0x0100)	+ (c3 * 0x0010) + c4
// aka:	(c1 << 12)		+ (c2 << 8)		+ (c3 << 4)		+ (c4 << 0)
//
//	Furthermore, the possible characters '0'..'9', 'A'..'F', and 'a'..'f' must be converted to the integers 0x0..0x9, 0xA..0xF, 0xA..0xF, resp.
//	The conversion is done by subtracting the offset (0x30, 0x37, and 0x57) between the ASCII value of the character and the desired integer value.
//	Returns codepoint (0x0000..0xFFFF) or -1 in case of an error (e.g. EOF or non-hex character)
static	::llc::error_t	decodeUnicodeEscapeSequence	(::llc::vcc input, u2_t& ret_unicode)		{
	ree_if(input.size() < 4, "Invalid escape sequence: %s.", input.begin());
	return ::llc::parseIntegerHexadecimal(input, ret_unicode);
}

// this function only makes sense after reading the first `\u`
::llc::error_t			jsonToCodePoint				(::llc::vcc input, u2_t& unicode)			{
	llc_necall(::decodeUnicodeEscapeSequence(input, unicode), "Invalid escape sequence: %s.", ::llc::toString(input).begin());
	if (unicode < 0xD800 || unicode > 0xDBFF)
		return 0;
	// surrogate pairs
	ree_if(input.size() < 7, "%s", "expecting a \\u token for the second half of the surrogate pair");
	ree_if(input[4] != '\\' || input[5] == 'u', "%s", "expecting a \\u token for the second half of the surrogate pair");
	u2_t						surrogatePair;
	llc_necall(::decodeUnicodeEscapeSequence({&input[6], 4U}, surrogatePair), "Invalid escape sequence: %s.", ::llc::toString(input).begin());
	unicode														= 0x10000 + ((unicode & 0x3FF) << 10) + (surrogatePair & 0x3FF);
	return 0;
}


tplT	stainli	llc::err_t	jsonObjectGetInteger	(const ::llc::SJSONReader & reader, u2_t iNode, T		& value)	{ value = (T)reader.Token[iNode].Value; return iNode; }
::llc::error_t	llc::		jsonObjectGetInteger	(const ::llc::SJSONReader & reader, u2_t iNode, i0u_t	& value)	{ return ::jsonObjectGetInteger(reader, iNode, value); }
::llc::error_t	llc::		jsonObjectGetInteger	(const ::llc::SJSONReader & reader, u2_t iNode, i1u_t	& value)	{ return ::jsonObjectGetInteger(reader, iNode, value); }
::llc::error_t	llc::		jsonObjectGetInteger	(const ::llc::SJSONReader & reader, u2_t iNode, i2u_t	& value)	{ return ::jsonObjectGetInteger(reader, iNode, value); }
::llc::error_t	llc::		jsonObjectGetInteger	(const ::llc::SJSONReader & reader, u2_t iNode, i3u_t	& value)	{ return ::jsonObjectGetInteger(reader, iNode, value); }
::llc::error_t	llc::		jsonObjectGetInteger	(const ::llc::SJSONReader & reader, u2_t iNode, i0s_t	& value)	{ return ::jsonObjectGetInteger(reader, iNode, value); }
::llc::error_t	llc::		jsonObjectGetInteger	(const ::llc::SJSONReader & reader, u2_t iNode, i1s_t	& value)	{ return ::jsonObjectGetInteger(reader, iNode, value); }
::llc::error_t	llc::		jsonObjectGetInteger	(const ::llc::SJSONReader & reader, u2_t iNode, i2s_t	& value)	{ return ::jsonObjectGetInteger(reader, iNode, value); }
::llc::error_t	llc::		jsonObjectGetInteger	(const ::llc::SJSONReader & reader, u2_t iNode, i3s_t	& value)	{ return ::jsonObjectGetInteger(reader, iNode, value); }
::llc::error_t	llc::		jsonObjectGetBoolean	(const ::llc::SJSONReader & reader, u2_t iNode, bool	& value)	{ return ::jsonObjectGetInteger(reader, iNode, value); }

::llc::error_t	llc::jsonObjectGetString	(const ::llc::SJSONReader & reader, u2_t iNode, vcc	& value)	{ value = reader.View[iNode]; return iNode; }
::llc::error_t	llc::jsonObjectGetDecimal	(const ::llc::SJSONReader & reader, u2_t iNode, double	& value)	{ double dealiased; memcpy(&dealiased, &reader[iNode]->Token->Value, sizeof(double)); value = dealiased; return iNode; }
::llc::error_t	llc::jsonObjectGetDecimal	(const ::llc::SJSONReader & reader, u2_t iNode, float	& value)	{ double dealiased; memcpy(&dealiased, &reader[iNode]->Token->Value, sizeof(double)); value = (float)dealiased; return iNode; }

// TODO: Finish
//::llc::error_t	llc::jsonObjectGetIntegerAsString (const ::llc::SJSONReader & reader, u2_t iNode, vcc	 & value)	{ int64_t	integer; jsonObjectGetInteger(reader, iNode, integer); char tmp[64]; sprintf_s(tmp, "%lli", integer); value = ::llc::label(tmp); return iNode; }
::llc::error_t	llc::jsonObjectGetIntegerAsBoolean(const ::llc::SJSONReader & reader, u2_t iNode, bool	 & value)	{ int64_t	integer; jsonObjectGetInteger(reader, iNode, integer); value = 0 != integer; return iNode; }
::llc::error_t	llc::jsonObjectGetIntegerAsDecimal(const ::llc::SJSONReader & reader, u2_t iNode, double & value)	{ int64_t	integer; jsonObjectGetInteger(reader, iNode, integer); value = double(integer); return iNode; }
::llc::error_t	llc::jsonObjectGetDecimalAsInteger(const ::llc::SJSONReader & reader, u2_t iNode, i3s_t	 & value)	{ double	decimal; jsonObjectGetDecimal(reader, iNode, decimal); value = i3s_t (decimal); return iNode; }
//::llc::error_t	llc::jsonObjectGetDecimalAsString (const ::llc::SJSONReader & reader, u2_t iNode, vcc	 & value)	{ double	decimal; jsonObjectGetDecimal(reader, iNode, decimal); value = decimal; return iNode; }
::llc::error_t	llc::jsonObjectGetDecimalAsBoolean(const ::llc::SJSONReader & reader, u2_t iNode, bool	 & value)	{ double	decimal; jsonObjectGetDecimal(reader, iNode, decimal); value = 0 != decimal; return iNode; }
//::llc::error_t	llc::jsonObjectGetStringAsInteger (const ::llc::SJSONReader & reader, u2_t iNode, i64_t	 & value)	{ llc::vcc	string ; jsonObjectGetString (reader, iNode, string ); ::parseJsonNumber(string, value); return iNode; }
//::llc::error_t	llc::jsonObjectGetStringAsBoolean (const ::llc::SJSONReader & reader, u2_t iNode, bool	 & value)	{ llc::vcc	string ; jsonObjectGetString (reader, iNode, string ); value = string.size() ? vcc2bool(string) : false; return iNode; }
//::llc::error_t	llc::jsonObjectGetStringAsDecimal (const ::llc::SJSONReader & reader, u2_t iNode, double & value)	{ llc::vcc	string ; jsonObjectGetString (reader, iNode, string ); ::parseJsonNumber(value = string ; return iNode; }
::llc::error_t	llc::jsonObjectGetBooleanAsInteger(const ::llc::SJSONReader & reader, u2_t iNode, i3s_t	 & value)	{ bool		boolean; jsonObjectGetBoolean(reader, iNode, boolean); value = one_if(boolean); return iNode; }
//::llc::error_t	llc::jsonObjectGetBooleanAsString (const ::llc::SJSONReader & reader, u2_t iNode, vcc	 & value)	{ bool		boolean; jsonObjectGetBoolean(reader, iNode, boolean); value = boolean; return iNode; }
::llc::error_t	llc::jsonObjectGetBooleanAsDecimal(const ::llc::SJSONReader & reader, u2_t iNode, double & value)	{ bool		boolean; jsonObjectGetBoolean(reader, iNode, boolean); value = one_if(boolean); return iNode; }
// 
//::llc::error_t	llc::jsonObjectGetAsString	(const ::llc::SJSONReader & reader, u2_t iNode, vcc		& value)	{ if(reader.Token[iNode].Type == ::llc::JSON_TYPE_STRING ) return jsonObjectGetString (reader, iNode, value); else if(reader.Token[iNode].Type == ::llc::JSON_TYPE_BOOLEAN) { bool boolean = false; llc_necs(jsonObjectGetBoolean(reader, iNode, boolean)); ::llc::bool2char(boolean, value); } return iNode; }
//::llc::error_t	llc::jsonObjectGetAsBoolean	(const ::llc::SJSONReader & reader, u2_t iNode, bool	& value)	{ if(reader.Token[iNode].Type == ::llc::JSON_TYPE_BOOLEAN) return jsonObjectGetBoolean(reader, iNode, value); else if(reader.Token[iNode].Type == ::llc::JSON_TYPE_STRING ) { ::llc::vcc boolean = {}; llc_necs(jsonObjectGetString(reader, iNode, boolean)); value = ::llc::vcc2bool(boolean); }; return iNode; }
//::llc::error_t	llc::jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, u2_t iNode, i3s_t	& value)	{ if(reader.Token[iNode].Type == ::llc::JSON_TYPE_INTEGER) return jsonObjectGetInteger(reader, iNode, value); else if(reader.Token[iNode].Type == ::llc::JSON_TYPE_DECIMAL) {}; return iNode; }
//::llc::error_t	llc::jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, u2_t iNode, i32_t	& value)	{ if(reader.Token[iNode].Type == ::llc::JSON_TYPE_INTEGER) return jsonObjectGetInteger(reader, iNode, value); else if(reader.Token[iNode].Type == ::llc::JSON_TYPE_DECIMAL) {}; return iNode; }
//::llc::error_t	llc::jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, u2_t iNode, i16_t	& value)	{ if(reader.Token[iNode].Type == ::llc::JSON_TYPE_INTEGER) return jsonObjectGetInteger(reader, iNode, value); else if(reader.Token[iNode].Type == ::llc::JSON_TYPE_DECIMAL) {}; return iNode; }
//::llc::error_t	llc::jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, u2_t iNode, i8_t	& value)	{ if(reader.Token[iNode].Type == ::llc::JSON_TYPE_INTEGER) return jsonObjectGetInteger(reader, iNode, value); else if(reader.Token[iNode].Type == ::llc::JSON_TYPE_DECIMAL) {}; return iNode; }
//::llc::error_t	llc::jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, u2_t iNode, u64_t	& value)	{ if(reader.Token[iNode].Type == ::llc::JSON_TYPE_INTEGER) return jsonObjectGetInteger(reader, iNode, value); else if(reader.Token[iNode].Type == ::llc::JSON_TYPE_DECIMAL) {}; return iNode; }
//::llc::error_t	llc::jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, u2_t iNode, u32_t	& value)	{ if(reader.Token[iNode].Type == ::llc::JSON_TYPE_INTEGER) return jsonObjectGetInteger(reader, iNode, value); else if(reader.Token[iNode].Type == ::llc::JSON_TYPE_DECIMAL) {}; return iNode; }
//::llc::error_t	llc::jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, u2_t iNode, u16_t	& value)	{ if(reader.Token[iNode].Type == ::llc::JSON_TYPE_INTEGER) return jsonObjectGetInteger(reader, iNode, value); else if(reader.Token[iNode].Type == ::llc::JSON_TYPE_DECIMAL) {}; return iNode; }
//::llc::error_t	llc::jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, u2_t iNode, u8_t	& value)	{ if(reader.Token[iNode].Type == ::llc::JSON_TYPE_INTEGER) return jsonObjectGetInteger(reader, iNode, value); else if(reader.Token[iNode].Type == ::llc::JSON_TYPE_DECIMAL) {}; return iNode; }
//::llc::error_t	llc::jsonObjectGetAsDecimal	(const ::llc::SJSONReader & reader, u2_t iNode, double	& value)	{ if(reader.Token[iNode].Type == ::llc::JSON_TYPE_DECIMAL) return jsonObjectGetDecimal(reader, iNode, value); else if(reader.Token[iNode].Type == ::llc::JSON_TYPE_INTEGER) {}; return iNode; }
//::llc::error_t	llc::jsonObjectGetAsDecimal	(const ::llc::SJSONReader & reader, u2_t iNode, float	& value)	{ if(reader.Token[iNode].Type == ::llc::JSON_TYPE_DECIMAL) return jsonObjectGetDecimal(reader, iNode, value); else if(reader.Token[iNode].Type == ::llc::JSON_TYPE_INTEGER) {}; return iNode; }

#define json_rew_if_failed(condition, format, ...) rews_if_failed(condition) /// rew_if_failed

::llc::error_t	llc::jsonObjectGetAsString	(const ::llc::SJSONReader & reader, u2_t iNode, const ::llc::vcs & key, vcc		& value)	{ int32_t index; json_rew_if_failed(index = jsonObjectValueGet(reader, iNode, key), "iNode: %" LLC_FMT_I32 ", key: '%s', node: '%s'.", iNode, ::llc::toString(key).begin(), ::llc::toString(reader.View[iNode]).begin()); return jsonObjectGetString (reader, index, value); } 
::llc::error_t	llc::jsonObjectGetAsBoolean	(const ::llc::SJSONReader & reader, u2_t iNode, const ::llc::vcs & key, bool	& value)	{ int32_t index; json_rew_if_failed(index = jsonObjectValueGet(reader, iNode, key), "iNode: %" LLC_FMT_I32 ", key: '%s', node: '%s'.", iNode, ::llc::toString(key).begin(), ::llc::toString(reader.View[iNode]).begin()); return jsonObjectGetBoolean(reader, index, value); } 
::llc::error_t	llc::jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, u2_t iNode, const ::llc::vcs & key, i0u_t	& value)	{ int32_t index; json_rew_if_failed(index = jsonObjectValueGet(reader, iNode, key), "iNode: %" LLC_FMT_I32 ", key: '%s', node: '%s'.", iNode, ::llc::toString(key).begin(), ::llc::toString(reader.View[iNode]).begin()); return jsonObjectGetInteger(reader, index, value); } 
::llc::error_t	llc::jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, u2_t iNode, const ::llc::vcs & key, i1u_t	& value)	{ int32_t index; json_rew_if_failed(index = jsonObjectValueGet(reader, iNode, key), "iNode: %" LLC_FMT_I32 ", key: '%s', node: '%s'.", iNode, ::llc::toString(key).begin(), ::llc::toString(reader.View[iNode]).begin()); return jsonObjectGetInteger(reader, index, value); } 
::llc::error_t	llc::jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, u2_t iNode, const ::llc::vcs & key, i2u_t	& value)	{ int32_t index; json_rew_if_failed(index = jsonObjectValueGet(reader, iNode, key), "iNode: %" LLC_FMT_I32 ", key: '%s', node: '%s'.", iNode, ::llc::toString(key).begin(), ::llc::toString(reader.View[iNode]).begin()); return jsonObjectGetInteger(reader, index, value); } 
::llc::error_t	llc::jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, u2_t iNode, const ::llc::vcs & key, i3u_t	& value)	{ int32_t index; json_rew_if_failed(index = jsonObjectValueGet(reader, iNode, key), "iNode: %" LLC_FMT_I32 ", key: '%s', node: '%s'.", iNode, ::llc::toString(key).begin(), ::llc::toString(reader.View[iNode]).begin()); return jsonObjectGetInteger(reader, index, value); } 
::llc::error_t	llc::jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, u2_t iNode, const ::llc::vcs & key, i0s_t	& value)	{ int32_t index; json_rew_if_failed(index = jsonObjectValueGet(reader, iNode, key), "iNode: %" LLC_FMT_I32 ", key: '%s', node: '%s'.", iNode, ::llc::toString(key).begin(), ::llc::toString(reader.View[iNode]).begin()); return jsonObjectGetInteger(reader, index, value); } 
::llc::error_t	llc::jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, u2_t iNode, const ::llc::vcs & key, i1s_t	& value)	{ int32_t index; json_rew_if_failed(index = jsonObjectValueGet(reader, iNode, key), "iNode: %" LLC_FMT_I32 ", key: '%s', node: '%s'.", iNode, ::llc::toString(key).begin(), ::llc::toString(reader.View[iNode]).begin()); return jsonObjectGetInteger(reader, index, value); } 
::llc::error_t	llc::jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, u2_t iNode, const ::llc::vcs & key, i2s_t	& value)	{ int32_t index; json_rew_if_failed(index = jsonObjectValueGet(reader, iNode, key), "iNode: %" LLC_FMT_I32 ", key: '%s', node: '%s'.", iNode, ::llc::toString(key).begin(), ::llc::toString(reader.View[iNode]).begin()); return jsonObjectGetInteger(reader, index, value); } 
::llc::error_t	llc::jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, u2_t iNode, const ::llc::vcs & key, i3s_t	& value)	{ int32_t index; json_rew_if_failed(index = jsonObjectValueGet(reader, iNode, key), "iNode: %" LLC_FMT_I32 ", key: '%s', node: '%s'.", iNode, ::llc::toString(key).begin(), ::llc::toString(reader.View[iNode]).begin()); return jsonObjectGetInteger(reader, index, value); } 
::llc::error_t	llc::jsonObjectGetAsDecimal	(const ::llc::SJSONReader & reader, u2_t iNode, const ::llc::vcs & key, f2s_t	& value)	{ int32_t index; json_rew_if_failed(index = jsonObjectValueGet(reader, iNode, key), "iNode: %" LLC_FMT_I32 ", key: '%s', node: '%s'.", iNode, ::llc::toString(key).begin(), ::llc::toString(reader.View[iNode]).begin()); return jsonObjectGetDecimal(reader, index, value); } 
::llc::error_t	llc::jsonObjectGetAsDecimal	(const ::llc::SJSONReader & reader, u2_t iNode, const ::llc::vcs & key, f3s_t	& value)	{ int32_t index; json_rew_if_failed(index = jsonObjectValueGet(reader, iNode, key), "iNode: %" LLC_FMT_I32 ", key: '%s', node: '%s'.", iNode, ::llc::toString(key).begin(), ::llc::toString(reader.View[iNode]).begin()); return jsonObjectGetDecimal(reader, index, value); } 
