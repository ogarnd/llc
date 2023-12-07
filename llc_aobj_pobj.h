#include "llc_ptr_obj.h"
#include "llc_array_obj.h"

#ifndef LLC_APOBJ_H_23627
#define LLC_APOBJ_H_23627

namespace llc
{
	tplt <tpnm T> using apobj		= ::llc::aobj<::llc::pobj<T>>; 
	tplt <tpnm T> using paobj		= ::llc::pobj<::llc::aobj<T>>; 

	tplt <tpnm T> using vpobj		= ::llc::view<::llc::pobj<T>>; 
	tplt <tpnm T> using vcpobj		= ::llc::view<const ::llc::pobj<T>>; 

	tplt <tpnm T> using apo			= ::llc::apobj<T>; 

	tplt <tpnm T> using apaobj		= ::llc::aobj<::llc::paobj<T>>; 
	tplt <tpnm T> using aapobj		= ::llc::aobj<::llc::apobj<T>>; 
} // namespace

#endif // LLC_APOBJ_H_23627
