#include "llc_sync.h"
#include "llc_log.h"
#include "llc_memory.h"

#ifndef LLC_REF_H_23627
#define LLC_REF_H_23627

namespace llc
{
	tplT struct gref {
		T						* Instance = 0;
		refcount_t				References = 0;
	};

	tplT	::llc::gref<T>*	ref_acquire				(::llc::gref<T> * llc_reference)	nxpt	{ if(llc_reference) llc_sync_increment(llc_reference->References); return llc_reference; }
	tplT	::llc::error_t	ref_release				(::llc::gref<T>* * llc_reference) {
		tydf	::llc::gref<T>		TRef;
		TRef						* oldRef				= *llc_reference;
		*llc_reference			= 0;
		if(oldRef)
			switch(llc_sync_decrement(oldRef->References)) {
			case -1: error_printf("%s", "Reference count error!"); return -1;
			case  0:
				if_null_e(oldRef->Instance)
				else {
					oldRef->Instance->~T(); 
					::llc::llc_free(oldRef->Instance);
				}
				::llc::llc_free(oldRef);
				break;
			}
		return 0;
	}
	tplT	T*				ref_allocate			(::llc::gref<T>* * llc_reference)	noexcept	{
		tydf	::llc::gref<T>		TRef;
		TRef						* newRef;
		if_null_ve(0, newRef = ::llc::malloc(newRef));
		if_true_block_log(error_printf, 0 == (newRef->References = one_if(::llc::malloc(newRef->Instance))), ::llc::llc_free(newRef); return 0;);
		1;
		TRef						* oldRef				= *llc_reference;
		*llc_reference			= newRef;
		::llc::ref_release(&oldRef);
		return (*llc_reference)->Instance;
	}
	tplt<tpnm T, tpnm... _tArgs>
	T*							ref_create				(::llc::gref<T>* * llc_reference, _tArgs&&... argsConstructor)	{
		tydf	::llc::gref<T>	TRef;
		TRef						* newRef				= 0;
		retnul_gserror_if(0 == ::llc::ref_allocate(&newRef));
		new (newRef->Instance) T{argsConstructor...};

		TRef						* oldRef				= *llc_reference;
		*llc_reference			= newRef;
		::llc::ref_release(&oldRef);
		return (*llc_reference)->Instance;
	}
} // namespace

#endif // LLC_REF_H_23627
