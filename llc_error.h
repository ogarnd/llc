#include "llc_typeint.h"

#ifndef LLC_ERROR_H_23627
#define LLC_ERROR_H_23627

namespace llc
{
	typedef	int32_t	error_t, err_t;

	stincxp	bool	failed		(const error_t errorCode)	noexcept	{ return errorCode < 0;		}
	stincxp	bool	succeeded	(const error_t errorCode)	noexcept	{ return 0 <= errorCode;	}

	stacxpr	::llc::error_t OS_OK                = 0;
	stacxpr	::llc::error_t OS_ERROR             = ::llc::OS_OK                - 1;
	stacxpr	::llc::error_t OS_BUSY              = ::llc::OS_ERROR             - 1;
	stacxpr	::llc::error_t OS_TIMEOUT           = ::llc::OS_BUSY              - 1;
	stacxpr	::llc::error_t OS_FULL              = ::llc::OS_TIMEOUT           - 1;
	stacxpr	::llc::error_t OS_EMPTY             = ::llc::OS_FULL              - 1;
	stacxpr	::llc::error_t OS_OVERRUN           = ::llc::OS_EMPTY             - 1;
	stacxpr	::llc::error_t OS_NOT_AVAILABLE     = ::llc::OS_OVERRUN           - 1;
	stacxpr	::llc::error_t OS_NOT_FOUND         = ::llc::OS_NOT_AVAILABLE     - 1;
	stacxpr	::llc::error_t OS_INVALID_PARAMETER = ::llc::OS_NOT_FOUND         - 1;
	stacxpr	::llc::error_t OS_FORBIDDEN         = ::llc::OS_INVALID_PARAMETER - 1;
	stacxpr	::llc::error_t OS_RESTART           = ::llc::OS_FORBIDDEN         - 1;
	stacxpr	::llc::error_t OS_WAKE_UP           = ::llc::OS_RESTART           - 1;
	stacxpr	::llc::error_t OS_SLEEP             = ::llc::OS_WAKE_UP           - 1;
	stacxpr	::llc::error_t OS_OFFLINE           = ::llc::OS_SLEEP             - 1;
	stacxpr	::llc::error_t OS_CONNECTING        = ::llc::OS_OFFLINE           - 1;
	stacxpr	::llc::error_t OS_CONNECTED         = ::llc::OS_CONNECTING        - 1;
	stacxpr	::llc::error_t OS_MISSING_DATA      = ::llc::OS_CONNECTED         - 1;
	stacxpr	::llc::error_t OS_NO_MEMORY         = ::llc::OS_MISSING_DATA      - 1;
} // namespace

#if !defined(errored)
#	define	errored(errVal)			(::llc::error_t(errVal) < 0)
#endif
#if !defined(not_errored)
#	define	not_errored(errVal)		::llc::succeeded(::llc::error_t(errVal))
#endif

#ifndef if_failed
#	define	if_failed(errVal)		if errored(errVal)
#endif

#ifndef if_succeeded
#	define	if_succeeded(errVal)	if(::llc::error_t(errVal) >= 0)
#endif

#ifdef LLC_ESP32
#	define LLC_CRASH()	do { uint64_t * _tasdas = 0; for(uint32_t i = 0; i < 0xFFFFFFFF; ++i) { for(uint32_t j = 0; j < 1000; ++j) delay(1); base_log_print("I had to do something with this.\n"); } } while(0)	// No throw? Just crash.
#elif defined(LLC_ARDUINO) 
#	define LLC_CRASH()	do { uint64_t * _tasdas = 0; for(uint32_t i = 0; i < 0xFFFFFFFF; ++i) { for(uint32_t j = 0; j < 1000; ++j) delay(1); base_log_print_F("I had to do something with this.\n"); } } while(0)	// No throw? Just crash.
#else
#	define LLC_CRASH()	do { uint64_t * _tasdas = 0; for(uint32_t i = 0; i < 0xFFFFFFFF; ++i) _tasdas[i] = 0xFFFFFFFF00000000ULL; } while(0)	// No throw? Just crash.
#endif

#endif // LLC_ERROR_H_23627
