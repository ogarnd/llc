#include "llc_ptr_nco.h"

#ifndef LLC_PTR_POD_H_23627
#define LLC_PTR_POD_H_23627

namespace llc
{
	tplt<tpnm _tPOD>
	class ppod : public ::llc::pnco<_tPOD> {
	public:
		typedef _tPOD			T;
		typedef	::llc::pnco<T>	TNCOPtr;
		typedef	::llc::gref<T>	TRef;

		using	TNCOPtr			::Reference;
								
		inline	const T*		operator->	()		const	noexcept	{ return Reference->Instance;														}
		inline	T*				operator->	()				noexcept	{ return (0 == Reference) ? ::llc::ref_allocate(&Reference) : Reference->Instance;	}

		tplt<tpnm... _tArgsConstructor>
		inline	T*				create		(_tArgsConstructor &&... argsConstructor)	noexcept	{ return ::llc::ref_create(&Reference, argsConstructor...);							}
		inline	T*				allocate	()											noexcept	{ return ::llc::ref_allocate(&Reference);											}
	};
	tplt<tpnm T> using pp	= ::llc::ppod<T>;
} // namespace

#endif // LLC_PTR_POD_H_23627
