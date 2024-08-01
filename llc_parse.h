#include "llc_enum.h"
#include "llc_slice.h"

#ifndef LLC_PARSE_H_23627
#define LLC_PARSE_H_23627

namespace llc
{
	stacxpr	::llc::vcc		DIGITS_HEX						= ::llc::vcc{16, "0123456789abcdef"};
	stacxpr	::llc::vcc		DIGITS_DECIMAL					= ::llc::vcc{10, "0123456789"};
	err_t			parseArbitraryBaseInteger		(u2_t base, const ::llc::vcc & symbolList, const ::llc::vcc & sourceChars, u3_t * number_);
	tplt<tpnm _tInt>	
	inline	err_t	parseIntegerDecimal				(const ::llc::vcc & sourceChars, _tInt & number_)	{ 
		u3_t					number							= 0; 
		err_t				countDigits; 
		llc_necs(countDigits = ::llc::parseArbitraryBaseInteger(10, ::llc::vcs{"0123456789"}, sourceChars, &number)); 
		number_ = (_tInt)number; 
		return countDigits; 
	}

	tplt<tpnm _tInt>	
	inline	err_t	parseIntegerHexadecimal			(const ::llc::vcc & sourceChars, _tInt & number_)	{ 
		u3_t					number							= 0; 
		err_t countDigits;
		llc_necs(countDigits = ::llc::parseArbitraryBaseInteger(16, ::llc::vcs{"0123456789abcdef"}, sourceChars, &number)); 
		number_ = (_tInt)number; 
		return countDigits; 
	}

	GDEFINE_ENUM_TYPE(STRIP_LITERAL_TYPE, int8_t);
	GDEFINE_ENUM_VALUE(STRIP_LITERAL_TYPE, LITERAL	, 0);
	GDEFINE_ENUM_VALUE(STRIP_LITERAL_TYPE, TOKEN	, 1);
	GDEFINE_ENUM_VALUE(STRIP_LITERAL_TYPE, COUNT	, 2);
	GDEFINE_ENUM_VALUE(STRIP_LITERAL_TYPE, UNKNOWN	, -1);
#pragma pack(push, 1)
	struct SStripLiteralType {
		s2_t						ParentIndex;
		STRIP_LITERAL_TYPE			Type;
		::llc::sliceu2_t			Span;
	};

	struct SStripLiteralState {
		u2_t						IndexCurrentChar				= 0;
		s2_t						IndexCurrentElement				= -1;
		::llc::SStripLiteralType	* CurrentElement				= 0;
		s2_t						NestLevel						= 0;
		char						CharCurrent						= 0;
		bool						Escaping						= false;
		bool						InsideToken						= false;
		s2_t						BracketsToSkip					= 0;
	};
#pragma pack(pop)
	err_t				stripLiteralParse				(::llc::SStripLiteralState	& stateReading	, ::llc::apod<::llc::SStripLiteralType> & out_types, const ::llc::vcc & in_format);
	err_t				stripLiteralParseStep			(::llc::SStripLiteralState	& work_state	, ::llc::apod<::llc::SStripLiteralType> & out_types, const ::llc::vcc & in_format);
	err_t				stripLiteralGetViews			(::llc::aobj<::llc::vcc>	& out_views, const ::llc::view<const ::llc::SStripLiteralType> & in_resultOfParser, const ::llc::vcc & in_format);

	bool						isSpaceCharacter				(const char characterToTest);
	err_t				skipToNextCharacter				(u2_t & indexCurrentChar, const ::llc::vcc & expression);

} // namespace

#endif // LLC_PARSE_H_23627
