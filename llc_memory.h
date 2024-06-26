/// Copyright 2010-2017 - ogarnd
#include "llc_eval.h"
#if defined(LLC_ATMEL)
#	include <stdlib.h>
#else
#	include <malloc.h>
#	include <memory.h>
#endif
#include "llc_auto_handler.h"

#ifndef LLC_MEMORY_H__92836409283642038462309846
#define LLC_MEMORY_H__92836409283642038462309846

#ifndef LLC_MALLOC_CUSTOM_ALIGN
#	define LLC_MALLOC_CUSTOM_ALIGN	16
#endif
#ifdef LLC_MALLOC_CUSTOM_ALIGN
#	define LLC_MALLOC_ALIGN			LLC_MALLOC_CUSTOM_ALIGN
#else
#	define LLC_MALLOC_ALIGN			sizeof(void*)
#endif

//#define	llc_calc_align_address		(alignment, address)	((alignment - ((alignment - 1) & (uintptr_t)address)) & (alignment - 1))	// returns the difference between an origin address and the next aligned addres. The alignment must always be a power of two.
//#define	llc_calc_align_address_4	(address)				llc_calc_align_address( 4, address)	// (0x04 - (0x03 & (uintptr_t)address) & 0x03)
//#define	llc_calc_align_address_8	(address)				llc_calc_align_address( 8, address)	// (0x08 - (0x07 & (uintptr_t)address) & 0x07)
//#define	llc_calc_align_address_16	(address)				llc_calc_align_address(16, address)	// (0x10 - (0x0F & (uintptr_t)address) & 0x0F)
//#define	llc_calc_align_address_32	(address)				llc_calc_align_address(32, address)	// (0x20 - (0x1F & (uintptr_t)address) & 0x1F)
//#define	llc_calc_align_address_64	(address)				llc_calc_align_address(64, address)	// (0x40 - (0x3F & (uintptr_t)address) & 0x3F)

namespace llc
{
	stacxpr	uintptr_t					calc_align_address			(uintptr_t alignment, uintptr_t address)	noexcept	{ return (alignment - ((alignment - 1) & address)) & (alignment - 1); }
	stincxp	uintptr_t					calc_align_address_4		(uintptr_t address)							noexcept	{ return calc_align_address( 4, address); }
	stincxp	uintptr_t					calc_align_address_8		(uintptr_t address)							noexcept	{ return calc_align_address( 8, address); }
	stincxp	uintptr_t					calc_align_address_16		(uintptr_t address)							noexcept	{ return calc_align_address(16, address); }
	stincxp	uintptr_t					calc_align_address_32		(uintptr_t address)							noexcept	{ return calc_align_address(32, address); }
	stincxp	uintptr_t					calc_align_address_64		(uintptr_t address)							noexcept	{ return calc_align_address(64, address); }

#if defined(LLC_WINDOWS)
	stainli	void						llc_free					(void* ptr)									noexcept	{ _aligned_free(ptr);									}
	stainli	void*						llc_malloc					(size_t size)								noexcept	{ int8_t* p = (int8_t*)_aligned_malloc(size + 1, LLC_MALLOC_ALIGN); return p; }
#elif defined(LLC_NEWLIB)
	stainli	void						llc_free					(void* ptr)									noexcept	{
		::free(ptr);
	}
	stainli	void*						llc_malloc					(size_t size)								noexcept	{
		int8_t* p = (int8_t*)::memalign(LLC_MALLOC_ALIGN, size + 1);
		return p;
	}
#elif defined(LLC_ATMEL)
	stainli	void						llc_free					(void* ptr)									noexcept	{ ::free(ptr);											}
	stainli	void*						llc_malloc					(size_t size)								noexcept	{ int8_t* p = (int8_t*)::malloc(size + 1); return p; }
#else
	stainli	void						llc_free					(void* ptr)									noexcept	{ ::free(ptr);											}
	stainli	void*						llc_malloc					(size_t size)								noexcept	{ int8_t* p = (int8_t*)::memalign(LLC_MALLOC_ALIGN, size + 1); return p; }
#endif

	tplt<tpnm _typePtr>
	stainli	void						safe_llc_free				(_typePtr &p)								noexcept	{
		_typePtr								_pepe						= p;
		p									= 0;
		llc_free((void*)_pepe);
	}

	struct auto_llc_free : public ::llc::auto_handler<void*, nullptr>	{ using TWrapper::auto_handler; inline ~auto_llc_free() noexcept { close(); } inline void close() noexcept { safe_llc_free(Handle); } };

#define GREF_PAGE_SIZE_MAX (4096)
	tplt<tpnm _tBase>	stincxp	uint32_t	get_page_size				()							noexcept	{ return (uint32_t)(sizeof(_tBase) <= GREF_PAGE_SIZE_MAX) ? GREF_PAGE_SIZE_MAX/sizeof(_tBase) : 1; };
	tplt<tpnm _tBase>	stincxp	uint32_t	get_type_size				()							noexcept	{ return (uint32_t) sizeof(_tBase); }
	tplt<tpnm _tBase>	stincxp	uint32_t	get_type_size				(const _tBase&)				noexcept	{ return (uint32_t) sizeof(_tBase); }
	tplt<tpnm _tBase>	stincxp	uint32_t	get_type_size_padded		(uint32_t paddingInBytes)	noexcept	{ return paddingInBytes ? (uint32_t) ( (sizeof(_tBase) / paddingInBytes) + one_if(sizeof(_tBase) % paddingInBytes) ) * paddingInBytes : sizeof(_tBase); }
	tplt<tpnm _tBase>	stincxp	uint32_t	get_type_align				()							noexcept	{
		return (uint32_t)
			(	(0 == (sizeof(_tBase) % 32))	? 32
			:	(0 == (sizeof(_tBase) % 16))	? 16
			:	(0 == (sizeof(_tBase) % 8 ))	? 8
			:	(0 == (sizeof(_tBase) % 4 ))	? 4
			:	(0 == (sizeof(_tBase) % 2 ))	? 2
			:	1
			);
	}

	tplt <tpnm _tBase>	stincxp	uint32_t	get_type_align_multiplier	()							noexcept	{
		return (uint32_t)
			(	(0 == (sizeof(_tBase) % 32)) ? sizeof(_tBase) / 32
			:	(0 == (sizeof(_tBase) % 16)) ? sizeof(_tBase) / 16
			:	(0 == (sizeof(_tBase) %  8)) ? sizeof(_tBase) /  8
			:	(0 == (sizeof(_tBase) %  4)) ? sizeof(_tBase) /  4
			:	(0 == (sizeof(_tBase) %  2)) ? sizeof(_tBase) /  2
			:	sizeof(_tBase)
			);
	}

	tplt <tpnm _tBase>	stainli	int32_t		podcmp		(const _tBase* pA, const _tBase* pB)							noexcept	{
		if(0 == pA)
			return (0 == pB) ? 0 : 0x7FFFFFFF;
		else if(0 == pB)
			return 0x7FFFFFFF;

		return memcmp(pA, pB, sizeof(_tBase));
	}

	tplt <tpnm _tBase>	stainli	_tBase*		chkcpy						(_tBase* destination, const _tBase* source, uint32_t count)		noexcept	{
			for (uint32_t i = 0; i < count; ++i)
				if (destination[i] != source[i])
					destination[i]  = source[i];
			return destination;
	}

	tplt <tpnm _tBase>			_tBase*		podcpy						(_tBase* dest, const _tBase* source)							noexcept	{
		stacxpr	const uint32_t													dataMultiplier				= (uint32_t)get_type_align_multiplier<_tBase>();
		stacxpr	const uint32_t													typeAlign					= (uint32_t)get_type_align<_tBase>();
		switch (typeAlign) {
		case 32: chkcpy((uint64_t*)dest, (const uint64_t*)source, dataMultiplier * 4);	break;
		case 16: chkcpy((uint64_t*)dest, (const uint64_t*)source, dataMultiplier * 2);	break;
		case  8: chkcpy((uint64_t*)dest, (const uint64_t*)source, dataMultiplier);		break;
		case  4: chkcpy((uint32_t*)dest, (const uint32_t*)source, dataMultiplier);		break;
		case  2: chkcpy((uint16_t*)dest, (const uint16_t*)source, dataMultiplier);		break;
		default:
			if( memcmp(dest, source, sizeof(_tBase)) )
				memcpy(dest, source, sizeof(_tBase));
			break;
		}
		return dest;
	}

	tplt <tpnm _t, size_t _len>	_t*			memcpy_s					(_t (&dest)[_len], const _t (&src)[_len])				noexcept	{ ::memcpy(dest, src, sizeof(_t) * _len); return dest; }
}	// namespace

#endif // LLC_MEMORY_H__92836409283642038462309846
