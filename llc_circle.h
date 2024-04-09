#include "llc_n2.h"

#ifndef LLC_CIRCLE_H_23627
#define LLC_CIRCLE_H_23627

namespace llc
{
#pragma pack(push, 1)	// You can read about pragma pack() here: https://www.google.com/search?q=pragma+pack
	tplt<tpnm T> 
	struct circle { 
		double			Radius; 
		::llc::n2<T>	Center; 

		LLC_DEFAULT_OPERATOR(circle<T>, Center == other.Center && Radius == other.Radius); 
	};
	typedef circle<float>		circlef32, circlef;
	typedef circle<double>		circlef64, circled;
	typedef circle<uint8_t>		circleu8;
	typedef circle<uint16_t>	circleu16;
	typedef circle<uint32_t>	circleu32;
	typedef circle<uint64_t>	circleu64;
	typedef circle<int8_t>		circlei8;
	typedef circle<int16_t>		circlei16;
	typedef circle<int32_t>		circlei32;
	typedef circle<int64_t>		circlei64;
#pragma pack(pop)
} // namespace

#endif // LLC_CIRCLE_H_23627
