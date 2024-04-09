#include "llc_typeint.h"

/// Copyright 2017 - ogarnd
#ifndef LLC_AUTO_HANDLER_H_23627
#define LLC_AUTO_HANDLER_H_23627

namespace llc
{
	 // I have no idea how to call this type so I'm really sorry. Something about raii maybe?
	tplt<tpnm _tHandle, _tHandle _vDefault>
	struct auto_handler {
		typedef	auto_handler<_tHandle, _vDefault>	TWrapper;

				_tHandle							Handle							= _vDefault;
		stacxpr	const _tHandle						VDefault						= _vDefault;

		inlcxpr										auto_handler					()								noexcept	= default;
		inlcxpr										auto_handler					(const _tHandle & other)		noexcept	= delete;
		inlcxpr										auto_handler					(const TWrapper & other)		noexcept	= delete;

		inlcxpr	operator							const _tHandle&					()						const	noexcept	{ return Handle;		}

		inline	TWrapper							operator=						(const _tHandle & other)		noexcept	= delete;
		inline	_tHandle*							operator&						()								noexcept	{ return &Handle;		}
#if !defined(LLC_ATMEL)
		inlcxpr	const _tHandle*						operator&						()						const	noexcept	{ return &Handle;		}
#endif
	};
} // namespace

#endif // LLC_AUTO_HANDLER_H_23627
