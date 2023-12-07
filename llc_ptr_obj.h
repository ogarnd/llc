#include "llc_ptr_nco.h"

#ifndef LLC_PTR_OBJ_H_23627
#define LLC_PTR_OBJ_H_23627

namespace llc
{
	tplt<tpnm _tOBJ>
	class pobj : public ::llc::pnco<_tOBJ> {
	public:
		typedef _tOBJ			T;
		typedef	::llc::pnco<T>	TNCOPtr;
		typedef	::llc::pobj<T>	TOBJPtr;
		typedef	::llc::gref<T>	TRef;

		using	TNCOPtr			::Reference;

		inline	const T*		operator->	()		const	noexcept	{ return Reference->Instance;														}
		inline	T*				operator->	()				noexcept	{ return (0 == Reference) ? ::llc::ref_create(&Reference) : Reference->Instance;	}

		tplt<tpnm... _tArgsConstructor>
		inline	T*				create		(_tArgsConstructor &&... argsConstructor)	noexcept	{ return ::llc::ref_create(&Reference, argsConstructor...);							}
		inline	T*				allocate	()											noexcept	{ return ::llc::ref_allocate(&Reference);											}
	};
	tplt<tpnm T> using po	= ::llc::pobj<T>; 
} // namespace

#endif // LLC_PTR_OBJ_H_23627
