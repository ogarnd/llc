#include "llc_view.h"
#include "llc_safe.h"
#include "llc_memory.h"
#include "llc_size.h"

#include "llc_std_initializer_list.h"

#ifndef LLC_ARRAY_BASE_H_23627
#define LLC_ARRAY_BASE_H_23627

namespace llc
{
	tplt<tpnm... _tArgs>	
	void						clear					(_tArgs&&... args)							{ const int32_t results[] = {args.clear()..., 0}; (void)results; }

	tplt<tpnm... _tArgs>
	::llc::error_t				resize					(uint32_t newSize, _tArgs&&... args)		{
		const uint32_t					oldSizes	[]			= {args.size	()..., 0};
		const ::llc::error_t			results		[]			= {args.resize	(newSize)..., 0};
		for(uint32_t i = 0; i < ::llc::size(results); ++i)
			if(errored(results[i])) {
				error_printf("Failed to set container %i to size: %i. Out of memory?", i, (int32_t)newSize);
				int32_t							j						= 0;
				const int32_t					dummy	[]				= {args.resize(oldSizes[j++])..., 0};
				(void)dummy;
				return -1;
			}
		return newSize;
	}

	tplt<tpnm... _tArgs>
	::llc::error_t				resize_obj				(uint32_t newSize, _tArgs&&... args)		{
		const uint32_t					oldSizes	[]			= {args.size	()..., 0};
		const ::llc::error_t			results		[]			= {args.resize	(newSize,{})..., 0};
		for(uint32_t i = 0; i < ::llc::size(results); ++i)
			if(errored(results[i])) {
				error_printf("Failed to set container %i to size: %i. Out of memory?", i, (int32_t)newSize);
				int32_t							j						= 0;
				const int32_t					dummy	[]				= {args.resize(oldSizes[j++])..., 0};
				(void)dummy;
				return -1;
			}
		return newSize;
	}

	// Base for arrays that keeps track of its actual size.
#pragma pack(push, 1)
	tplt<tpnm T>
	class array_base : public view<T> {
		static	uint32_t		calc_reserve_count		(const uint32_t newCountRequested, uint32_t & outCount)	noexcept	{ 
			stacxpr	uint32_t			MAX_COUNT				= 0x7FFFFFFFU;
			if(MAX_COUNT < newCountRequested)
				return (uint32_t)-1;

			const uint32_t				desiredCount			= newCountRequested + (newCountRequested >> 2);
			return outCount = (desiredCount > MAX_COUNT || desiredCount < newCountRequested) ? MAX_COUNT : desiredCount; 
		}

	protected:
		using					view<T>::Data;

		typedef					array_base<T>			TArray;
		uint32_t				Size					: 31;
		uint32_t				NoAlloc					: 1;
//		uint32_t				Offset					= 0;

		inline					~array_base				()							noexcept	{ if(0 == NoAlloc) ::llc::safe_llc_free(Data); }

		inlcxpr					array_base				()							noexcept	: Size(0), NoAlloc(0) {}
		inlcxpr					array_base				(const TArray &	 other)		noexcept	= delete;
		inlcxpr					array_base				(const TArray && other)		noexcept	= delete;

		TArray&					operator =				(const TArray &	 other)					= delete;
		TArray&					operator =				(const TArray && other)					= delete;
		// This helper method is used to prevent redundancies. It returns a safe integer of the same or a higher value than the one passed as argument.
		static	::llc::error_t	alloc_with_reserve		(const uint32_t newCount, T* & reserved)	noexcept	{ 
			uint32_t					newSize					= 0;
			llc_necall(calc_reserve_count(newCount, newSize), "Too large. newCount: %" LLC_FMT_I32 ".", newCount);
			const uint32_t				bytesToAllocate			= ::llc::size<T>(newSize) + 2;
			if(bool(reserved = (T*)::llc::llc_malloc(bytesToAllocate)))
				return (::llc::error_t)newSize;

			error_printf("failed to reserve %" LLC_FMT_U32 " bytes.", bytesToAllocate);
			LLC_PLATFORM_CRT_CHECK_MEMORY();
			return -1;
		}
	}; // array_base
#pragma pack(pop)
}

#endif // LLC_ARRAY_BASE_H_23627
