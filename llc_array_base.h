#include "llc_view.h"
#include "llc_safe.h"
#include "llc_memory.h"
#include "llc_size.h"

#include "llc_std_initializer_list.h"

#ifndef LLC_ARRAY_BASE_H_23627
#define LLC_ARRAY_BASE_H_23627

namespace llc
{
	tpl_vtArgs	void			clear					(_tArgs&&... args)							{ const int32_t results[] = {args.clear()..., 0}; (void)results; }
	tpl_vtArgs	err_t			resize					(u2_t newSize, _tArgs&&... args)		{
		u2_c					oldSizes	[]			= {args.size	()..., 0};
		const ::llc::error_t			results		[]			= {args.resize	(newSize)..., 0};
		for(u2_t i = 0; i < ::llc::size(results); ++i)
			if_failed(results[i]) {
				error_printf("Failed to set container %" LLC_FMT_S2 " to size: %" LLC_FMT_S2 ". Out of memory?", i, (int32_t)newSize);
				int32_t							j						= 0;
				const int32_t					dummy	[]				= {args.resize(oldSizes[j++])..., 0};
				(void)dummy;
				return -1;
			}
		return newSize;
	}
	tpl_vtArgs	err_t			resize_obj				(u2_t newSize, _tArgs&&... args)		{
		u2_c					oldSizes	[]			= {args.size	()..., 0};
		const ::llc::error_t			results		[]			= {args.resize	(newSize,{})..., 0};
		for(u2_t i = 0; i < ::llc::size(results); ++i)
			if_failed(results[i]) {
				error_printf("Failed to set container %" LLC_FMT_S2 " to size: %" LLC_FMT_S2 ". Out of memory?", i, (int32_t)newSize);
				int32_t							j						= 0;
				const int32_t					dummy	[]				= {args.resize(oldSizes[j++])..., 0};
				(void)dummy;
				return -1;
			}
		return newSize;
	}
	// Base for arrays that keeps track of its actual size.
#pragma pack(push, 1)
	tplT class array_base : public view<T> {
		static	u2_t		calc_reserve_count		(u2_c newCountRequested, u2_t & outCount)	noexcept	{ 
			stxp	u2_t			MAX_COUNT				= 0x3FFFFFFFU;
			if(MAX_COUNT < newCountRequested)
				return (u2_t)-1;
#if defined (LLC_ARDUINO) || defined(LLC_ESP32) || defined(LLC_ESP8266) || defined(ESP32)
			u2_c				desiredCount			= 2 + newCountRequested;//: + (newCountRequested >> 8);
#else
			u2_c				desiredCount			= 2 + newCountRequested + (newCountRequested >> 2);
#endif
			return outCount = (desiredCount > MAX_COUNT || desiredCount < newCountRequested) ? MAX_COUNT : desiredCount; 
		}

	protected:
		using					view<T>::Data;
		tydf					array_base<T>			TArray;

		u2_t				Size					: 30;
		u2_t				NoAlloc					: 2;
//		u2_t				Offset					= 0;

		inline					~array_base				()							noexcept	{ if(0 == NoAlloc) ::llc::safe_llc_free(Data); }

		inxp					array_base				()							noexcept	: Size(0), NoAlloc(0) {}
		inxp					array_base				(const TArray &	 other)		noexcept	= delete;
		inxp					array_base				(const TArray && other)		noexcept	= delete;

		TArray&					oper =				(const TArray &	 other)					= delete;
		TArray&					oper =				(const TArray && other)					= delete;
		// This helper method is used to prevent redundancies. It returns a safe integer of the same or a higher value than the one passed as argument.
		static	::llc::error_t	alloc_with_reserve		(u2_c newCount, T* & reserved)	noexcept	{ 
			u2_t					newSize					= 0;
			llc_necall(calc_reserve_count(newCount, newSize), "Too large. newCount: %" LLC_FMT_S2 ".", newCount);
			u2_c				bytesToAllocate			= 2 + szof(T) * newSize;
			if(bool(reserved = (T*)::llc::llc_malloc(bytesToAllocate)))
				return (::llc::error_t)newSize;
			error_printf("failed to reserve %" LLC_FMT_U2 " bytes.", bytesToAllocate);
			LLC_PLATFORM_CRT_CHECK_MEMORY();
			return -1;
		}
	}; // array_base
#pragma pack(pop)
}

#endif // LLC_ARRAY_BASE_H_23627
