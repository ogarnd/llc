#include "llc_sync.h"
#include "llc_log.h"
#include "llc_memory.h"

#ifndef LLC_REF_H_23627
#define LLC_REF_H_23627

namespace llc
{
	tplT struct gref {
		T					* Instance;
		refcount_t			References;
	};

	tplt<tpnm _tNCO>
	::llc::gref<_tNCO>*		ref_acquire				(::llc::gref<_tNCO> * llc_reference)	noexcept	{
		if(llc_reference)
			llc_sync_increment(llc_reference->References);
		return llc_reference;
	};

	tplt<tpnm _tNCO>
	::llc::error_t			ref_release				(::llc::gref<_tNCO>* * llc_reference) {
		typedef	::llc::gref<_tNCO>	TRef;
		TRef						* oldRef				= *llc_reference;
		*llc_reference			= 0;
		if(oldRef)
			switch(llc_sync_decrement(oldRef->References)) {
			case -1: error_printf("%s", "Reference count error!"); return -1;
			case  0:
				if(oldRef->Instance)
					oldRef->Instance->~_tNCO();
				else
					error_printf("%s", "Instance is NULL! At the point of writing this code it wouldn't make any sense.");
				::llc::llc_free(oldRef->Instance);
				::llc::llc_free(oldRef);
				break;
			}
		return 0;
	};

	tplt<tpnm T>
	T*						ref_allocate			(::llc::gref<T>* * llc_reference)	noexcept	{
		typedef	::llc::gref<T>	TRef;
		TRef						* newRef				;
		if_null_ve(0, newRef = ::llc::malloc(newRef));
		if(0 == ::llc::malloc(newRef->Instance)) {
			::llc::llc_free(newRef);
			error_printf("%s", "Out of memory?");
			return 0;
		}
		newRef->References		= 1;
		TRef						* oldRef				= *llc_reference;
		*llc_reference			= newRef;
		::llc::ref_release(&oldRef);
		return (*llc_reference)->Instance;
	};

	tplt<tpnm _tOBJ, tpnm... _tArgs>
	_tOBJ*					ref_create				(::llc::gref<_tOBJ>* * llc_reference, _tArgs&&... argsConstructor)	{
		typedef	::llc::gref<_tOBJ>	TRef;
		TRef						* newRef				= 0;
		retnul_gserror_if(0 == ::llc::ref_allocate(&newRef));
		new (newRef->Instance) _tOBJ{argsConstructor...};

		TRef						* oldRef				= *llc_reference;
		*llc_reference			= newRef;
		::llc::ref_release(&oldRef);
		return (*llc_reference)->Instance;
	};
} // namespace

#endif // LLC_REF_H_23627
