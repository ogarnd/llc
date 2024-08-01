#include "llc_array_ptr.h"
#include "llc_array_static.h"
#include "llc_apod_serialize.h"

#ifndef LLC_BLOCK_CONTAINER_NTS_230522
#define LLC_BLOCK_CONTAINER_NTS_230522

namespace llc
{
	tplt<size_t _size>
	class block_container_nts {
		::llc::apobj<::llc::astaticc<_size>>	Blocks;
		::llc::au2_t								RemainingSpace;

	public:	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		::llc::error_t						clear						()								{ return ::llc::clear(Blocks, RemainingSpace); }
		::llc::error_t						Save						(::llc::au0_t & output)	const	{
			llc_necs(llc::saveView(output, RemainingSpace));
			for(uint32_t iArray = 0; iArray < RemainingSpace.size(); ++iArray)
				llc_necs(llc::saveView(output, *Blocks[iArray]));
			return 0;
		}

		::llc::error_t						Load						(::llc::vcu0_t & input)			{
			clear();
			llc_necs(llc::loadView(input, RemainingSpace));
			llc_necs(Blocks.resize(RemainingSpace.size()));
			for(uint32_t iArray = 0; iArray < Blocks.size(); ++iArray)
				llc_necs(llc::loadView(input, Blocks[iArray]->Storage));
			return 0;
		}

		::llc::error_t						push_sequence				(const char* sequence, uint32_t length, ::llc::vcc & out_view)	{
			const uint32_t							lengthPlusOne				= length + 1;
			for(uint32_t iBlock = 0; iBlock < Blocks.size(); ++iBlock) {
				uint32_t								& blkRemainingSpace			= RemainingSpace[iBlock];
				if(blkRemainingSpace >= lengthPlusOne) {
					char									* sequenceStart				= &Blocks[iBlock]->operator[](_size - blkRemainingSpace);
					out_view							= {sequenceStart, length};
					memcpy(sequenceStart, sequence, length);
					sequenceStart[lengthPlusOne]		= 0;
					blkRemainingSpace					-= lengthPlusOne;
					return iBlock;
				}
			}
			int32_t									indexNewBlock				= Blocks.size();
			llc_necs(Blocks			.resize(Blocks.size() + 1));
			llc_necs(RemainingSpace	.resize(Blocks.size() + 1, _size - length - 1));
			out_view							= {&Blocks[indexNewBlock]->operator[](0), length};
			memcpy(Blocks[indexNewBlock]->Storage, sequence, length);
			return indexNewBlock;
		}
	};
} // namespace

#endif // LLC_BLOCK_CONTAINER_NTS_230522