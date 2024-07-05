#include "llc_log_core.h"

#include "llc_chrono.h" 
#include "llc_size.h"

#include "llc_cstring.h"

#ifdef LLC_ATMEL
#	include <stdio.h>
#	include <string.h>
#else
#	include <cstdio>
#endif

#ifndef LLC_LOG_LEVEL_H
#define LLC_LOG_LEVEL_H


namespace llc
{
#ifndef LLC_ARDUINO
	void				_llc_print_system_errors		(const char * prefix, uint32_t prefixLen);
#endif


	error_t				debug_print_prefix				(int severity, const char * path, uint32_t line, const char * function);

#ifndef LLC_ATMEL
	tplt<size_t fmtLen, tpnm... TArgs>
	static	void		_llc_debug_printf				(int severity, const char * path, uint32_t line, const char * function, const char (&format)[fmtLen], const TArgs... args)			{
		debug_print_prefix(severity, path, line, function);
#else
	tplt<tpnm... TArgs>
	static	void		_llc_debug_printf				(const char* function, const __FlashStringHelper* format, const TArgs... args)			{
		base_log_print_F("{");
		base_log_print(function);
		base_log_print_F("}:");
#endif

#ifdef LLC_ESP32 // Use dynamic string buffer to save flash space.
		if(format) {
			const uint32_t bufferSize = uint32_t(strlen(format) + 1024 * 2);
			if(char * customDynamicString = (char*)malloc(bufferSize)) {
				const	size_t 	stringLength	= snprintf(customDynamicString, bufferSize - 2, format, args...);
				customDynamicString[::llc::min(stringLength, size_t(bufferSize - 2))] = '\n';
				customDynamicString[::llc::min(stringLength + 1, size_t(bufferSize - 1))] = 0;
				base_log_write(customDynamicString, (int)::llc::min(stringLength + 1U, size_t(bufferSize - 1)));
				free(customDynamicString);
			}
		}
#else
#	ifdef LLC_ATMEL
		char					customDynamicString	[128]		= {};
		const	size_t 			stringLength					= snprintf_P(customDynamicString, sizeof(customDynamicString) - 1, (const char*)format, args...);
		customDynamicString[min(stringLength, (size_t)sizeof(customDynamicString)-1)] = '\n';
	#else
		char					customDynamicString	[fmtLen + 1024 * 32]	= {};
		const	size_t 			stringLength					= ::llc::sprintf_s(customDynamicString, format, args...);
		customDynamicString[min(stringLength, sizeof(customDynamicString)-2)] = '\n';
		if(2 >= severity)
			::llc::_llc_print_system_errors("", 0);
#	endif
		base_log_write(customDynamicString, (uint32_t)min(sizeof(customDynamicString), stringLength + 1));
#endif
	}

	tplt<tpnm... _tArgs>
	stincxp	void*		nully				(_tArgs&&...)		{ return 0; }

}

#ifdef LLC_WINDOWS
#	define llc_debug_printf(severity, format, ...)	::llc::_llc_debug_printf(severity, __FILE__, __LINE__, __FUNCTION__, format, __VA_ARGS__)
#else
#	ifdef LLC_ATMEL
#		define llc_debug_printf(severity, format, ...)	do{ /*base_log_print_F(__FILE__ "(" LLC_TOSTRING(__LINE__) ")");*/ ::llc::_llc_debug_printf(__func__, F(format), ##__VA_ARGS__); } while(0) //::llc::_llc_debug_printf("(" LLC_TOSTRING(__LINE__) ")", "")
#	else
#		define llc_debug_printf(severity, format, ...)	::llc::_llc_debug_printf(severity, __FILE__, __LINE__, __func__, format, ##__VA_ARGS__)
#	endif
#endif

#ifndef always_printf
#ifndef logf_always
#if !defined(LLC_WINDOWS)
#	define always_printf(format, ...)					llc_debug_printf(3, format, ##__VA_ARGS__)
#else
#	define always_printf(format, ...)					llc_debug_printf(3, format, __VA_ARGS__)
#endif
#endif
#endif

#ifndef error_printf
#ifndef logf_error
#	if defined (LLC_ERROR_PRINTF_ENABLED)
#ifndef LLC_WINDOWS
#		define error_printf(format, ...)					do { llc_debug_printf(1, format, ##__VA_ARGS__); LLC_PLATFORM_CRT_BREAKPOINT(); } while(0)
#else
#		define error_printf(format, ...)					do { llc_debug_printf(1, format, __VA_ARGS__); LLC_PLATFORM_CRT_BREAKPOINT(); } while(0)
#endif
#	else
#		define error_printf(format, ...)					do { ::llc::dummy(__VA_ARGS__); LLC_PLATFORM_CRT_BREAKPOINT(); } while(0)
#	endif
#endif
#endif

#ifndef warning_printf
#ifndef logf_warning
#	if defined (LLC_WARNING_PRINTF_ENABLED)
#ifndef LLC_WINDOWS
#		define warning_printf(format, ...)					llc_debug_printf(2, format, ##__VA_ARGS__)
#else
#		define warning_printf(format, ...)					llc_debug_printf(2, format, __VA_ARGS__)
#endif
#	else
#		define warning_printf(format, ...)					do { ::llc::dummy(__VA_ARGS__); } while(0)
#	endif
#endif
#endif

#ifndef info_printf
#ifndef logf_info
#	if defined (LLC_INFO_PRINTF_ENABLED)
#ifndef LLC_WINDOWS
#		define info_printf(format, ...)						llc_debug_printf(3, format, ##__VA_ARGS__)
#else
#		define info_printf(format, ...)						llc_debug_printf(3, format, __VA_ARGS__)
#endif
#	else
#		define info_printf(format, ...)						do { ::llc::dummy(__VA_ARGS__); } while(0)
#	endif
#endif
#endif

#ifndef success_printf
#ifndef logf_success
#	if defined (LLC_SUCCESS_PRINTF_ENABLED)
#ifndef LLC_WINDOWS
#		define success_printf(format, ...)					llc_debug_printf(4, format, ##__VA_ARGS__)
#else
#		define success_printf(format, ...)					llc_debug_printf(4, format, __VA_ARGS__)
#endif
#	else
#		define success_printf(format, ...)					do { ::llc::dummy(__VA_ARGS__); } while(0)
#	endif
#endif
#endif

#ifndef verbose_printf
#ifndef logf_verbose
#	if defined (LLC_VERBOSE_PRINTF_ENABLED)
#ifndef LLC_WINDOWS
#		define verbose_printf(format, ...)					llc_debug_printf(4, format, ##__VA_ARGS__)
#else
#		define verbose_printf(format, ...)					llc_debug_printf(4, format, __VA_ARGS__)
#endif
#	else
#		define verbose_printf(format, ...)					do { ::llc::dummy(__VA_ARGS__); } while(0)
#	endif
#endif
#endif

//
#define llc_rv_hrcall(retVal, hr_call)					do { ::HRESULT errCall_ = (hr_call); if FAILED(errCall_) { llc_debug_printf(0, "%s -> %" LLC_FMT_I32 " (0x%X): '%s'.", #hr_call, errCall_, ::llc::getWindowsErrorAsString(errCall_).begin()); return retVal; } } while(0)
#define llc_rve_hrcall(retVal, hr_call, format, ...)	do { ::HRESULT errCall_ = (hr_call); if FAILED(errCall_) { llc_debug_printf(0, "%s -> %" LLC_FMT_I32 " (0x%X): '%s' " format, #hr_call, errCall_, ::llc::getWindowsErrorAsString(errCall_).begin(), __VA_ARGS__); return retVal; } } while(0)

#define llc_hrcall(hr_call)				do { llc_rv_hrcall (-1, hr_call)				; } while(0)		// HRESULT call.
#define llc_hrecall(hr_call, ...)		do { llc_rve_hrcall(-1, hr_call, __VA_ARGS__)	; } while(0)		// HRESULT call.

#define llc_necs(llcl_call)					do { const auto _grr_rslt_val = llcl_call; if(0 > ::llc::error_t(_grr_rslt_val)) { error_printf("%s -> %" LLC_FMT_I32 "", #llcl_call, _grr_rslt_val); return -1; } } while(0) // Non-		propagable error call string.
#ifdef LLC_WINDOWS
#	define llc_necall(llcl_call, format, ...)	do { const auto _grr_rslt_val = llcl_call; if(0 > ::llc::error_t(_grr_rslt_val)) { error_printf("%s -> %" LLC_FMT_I32 ": " format, #llcl_call, _grr_rslt_val, __VA_ARGS__); return -1; } } while(0)		// Non-propagable error call.
#else
#	define llc_necall(llcl_call, format, ...)	do { const auto _grr_rslt_val = llcl_call; if(0 > ::llc::error_t(_grr_rslt_val)) { error_printf("%s -> %" LLC_FMT_I32 ": " format, #llcl_call, _grr_rslt_val, ##__VA_ARGS__); return -1; } } while(0)		// Non-propagable error call.
#endif

#ifndef gthrow_if
#	define gsthrow_if(condition)	if_true_log_and_throw(error_printf, (condition))
#	ifndef LLC_WINDOWS
#		define gthrow_if(condition, format, ...)	if_true_logf_and_throw(error_printf, (condition), format, ##__VA_ARGS__)
#	else
#		ifndef LLC_ANDROID
#			define gthrow_if(condition, format, ...)	if_true_logf_and_throw(error_printf, (condition), format, ##__VA_ARGS__)
#		else
#			define gthrow_if(condition, format, ...)	if_true_logf_and_throw(error_printf, (condition), format, __VA_ARGS__)
#		endif
#	endif
#endif

// -- Helpers for the different log levels set during build or runtime.

// - Conditional log
#define if_true_log_always(condition)								if_true_log						(always_printf , (condition))
#define if_true_log_error(condition)								if_true_log						(error_printf  , (condition))
#define if_true_log_warning(condition)								if_true_log						(warning_printf, (condition))
#define if_true_log_info(condition)									if_true_log						(info_printf   , (condition))
#define if_true_log_verbose(condition)								if_true_log						(verbose_printf, (condition))
#define if_fail_log_always(condition)								if_fail_log						(always_printf , (condition))
#define if_fail_log_error(condition)								if_fail_log						(error_printf  , (condition))
#define if_fail_log_warning(condition)								if_fail_log						(warning_printf, (condition))
#define if_fail_log_info(condition)									if_fail_log						(info_printf   , (condition))
#define if_fail_log_verbose(condition)								if_fail_log						(verbose_printf, (condition))
#define if_zero_log_always(condition)								if_zero_log						(always_printf , (condition))
#define if_zero_log_error(condition)								if_zero_log						(error_printf  , (condition))
#define if_zero_log_warning(condition)								if_zero_log						(warning_printf, (condition))
#define if_zero_log_info(condition)									if_zero_log						(info_printf   , (condition))
#define if_zero_log_verbose(condition)								if_zero_log						(verbose_printf, (condition))
#define if_true_log_and_break_always(condition)						if_true_log_and_break			(always_printf , (condition))
#define if_true_log_and_break_error(condition)						if_true_log_and_break			(error_printf  , (condition))
#define if_true_log_and_break_warning(condition)					if_true_log_and_break			(warning_printf, (condition))
#define if_true_log_and_break_info(condition)						if_true_log_and_break			(info_printf   , (condition))
#define if_true_log_and_break_verbose(condition)					if_true_log_and_break			(verbose_printf, (condition))
#define if_fail_log_and_break_always(condition)						if_fail_log_and_break			(always_printf , (condition))
#define if_fail_log_and_break_error(condition)						if_fail_log_and_break			(error_printf  , (condition))
#define if_fail_log_and_break_warning(condition)					if_fail_log_and_break			(warning_printf, (condition))
#define if_fail_log_and_break_info(condition)						if_fail_log_and_break			(info_printf   , (condition))
#define if_fail_log_and_break_verbose(condition)					if_fail_log_and_break			(verbose_printf, (condition))
#define if_zero_log_and_break_always(condition)						if_zero_log_and_break			(always_printf , (condition))
#define if_zero_log_and_break_error(condition)						if_zero_log_and_break			(error_printf  , (condition))
#define if_zero_log_and_break_warning(condition)					if_zero_log_and_break			(warning_printf, (condition))
#define if_zero_log_and_break_info(condition)						if_zero_log_and_break			(info_printf   , (condition))
#define if_zero_log_and_break_verbose(condition)					if_zero_log_and_break			(verbose_printf, (condition))
#define if_true_log_and_continue_always(condition)					if_true_log_and_continue		(always_printf , (condition))
#define if_true_log_and_continue_error(condition)					if_true_log_and_continue		(error_printf  , (condition))
#define if_true_log_and_continue_warning(condition)					if_true_log_and_continue		(warning_printf, (condition))
#define if_true_log_and_continue_info(condition)					if_true_log_and_continue		(info_printf   , (condition))
#define if_true_log_and_continue_verbose(condition)					if_true_log_and_continue		(verbose_printf, (condition))
#define if_fail_log_and_continue_always(condition)					if_fail_log_and_continue		(always_printf , (condition))
#define if_fail_log_and_continue_error(condition)					if_fail_log_and_continue		(error_printf  , (condition))
#define if_fail_log_and_continue_warning(condition)					if_fail_log_and_continue		(warning_printf, (condition))
#define if_fail_log_and_continue_info(condition)					if_fail_log_and_continue		(info_printf   , (condition))
#define if_fail_log_and_continue_verbose(condition)					if_fail_log_and_continue		(verbose_printf, (condition))
#define if_zero_log_and_continue_always(condition)					if_zero_log_and_continue		(always_printf , (condition))
#define if_zero_log_and_continue_error(condition)					if_zero_log_and_continue		(error_printf  , (condition))
#define if_zero_log_and_continue_warning(condition)					if_zero_log_and_continue		(warning_printf, (condition))
#define if_zero_log_and_continue_info(condition)					if_zero_log_and_continue		(info_printf   , (condition))
#define if_zero_log_and_continue_verbose(condition)					if_zero_log_and_continue		(verbose_printf, (condition))
#define if_true_log_and_throw_always(condition)						if_true_log_and_throw			(always_printf , (condition))
#define if_true_log_and_throw_error(condition)						if_true_log_and_throw			(error_printf  , (condition))
#define if_true_log_and_throw_warning(condition)					if_true_log_and_throw			(warning_printf, (condition))
#define if_true_log_and_throw_info(condition)						if_true_log_and_throw			(info_printf   , (condition))
#define if_true_log_and_throw_verbose(condition)					if_true_log_and_throw			(verbose_printf, (condition))
#define if_fail_log_and_throw_always(condition)						if_fail_log_and_throw			(always_printf , (condition))
#define if_fail_log_and_throw_error(condition)						if_fail_log_and_throw			(error_printf  , (condition))
#define if_fail_log_and_throw_warning(condition)					if_fail_log_and_throw			(warning_printf, (condition))
#define if_fail_log_and_throw_info(condition)						if_fail_log_and_throw			(info_printf   , (condition))
#define if_fail_log_and_throw_verbose(condition)					if_fail_log_and_throw			(verbose_printf, (condition))
#define if_zero_log_and_throw_always(condition)						if_zero_log_and_throw			(always_printf , (condition))
#define if_zero_log_and_throw_error(condition)						if_zero_log_and_throw			(error_printf  , (condition))
#define if_zero_log_and_throw_warning(condition)					if_zero_log_and_throw			(warning_printf, (condition))
#define if_zero_log_and_throw_info(condition)						if_zero_log_and_throw			(info_printf   , (condition))
#define if_zero_log_and_throw_verbose(condition)					if_zero_log_and_throw			(verbose_printf, (condition))
#define if_true_log_and_return_always(condition)					if_true_log_and_return			(always_printf , (condition))
#define if_true_log_and_return_error(condition)						if_true_log_and_return			(error_printf  , (condition))
#define if_true_log_and_return_warning(condition)					if_true_log_and_return			(warning_printf, (condition))
#define if_true_log_and_return_info(condition)						if_true_log_and_return			(info_printf   , (condition))
#define if_true_log_and_return_verbose(condition)					if_true_log_and_return			(verbose_printf, (condition))
#define if_fail_log_and_return_always(condition)					if_fail_log_and_return			(always_printf , (condition))
#define if_fail_log_and_return_error(condition)						if_fail_log_and_return			(error_printf  , (condition))
#define if_fail_log_and_return_warning(condition)					if_fail_log_and_return			(warning_printf, (condition))
#define if_fail_log_and_return_info(condition)						if_fail_log_and_return			(info_printf   , (condition))
#define if_fail_log_and_return_verbose(condition)					if_fail_log_and_return			(verbose_printf, (condition))
#define if_zero_log_and_return_always(condition)					if_zero_log_and_return			(always_printf , (condition))
#define if_zero_log_and_return_error(condition)						if_zero_log_and_return			(error_printf  , (condition))
#define if_zero_log_and_return_warning(condition)					if_zero_log_and_return			(warning_printf, (condition))
#define if_zero_log_and_return_info(condition)						if_zero_log_and_return			(info_printf   , (condition))
#define if_zero_log_and_return_verbose(condition)					if_zero_log_and_return			(verbose_printf, (condition))
#define if_true_log_and_return_value_always(value, condition)		if_true_log_and_return_value	(always_printf , (value), (condition))
#define if_true_log_and_return_value_error(value, condition)		if_true_log_and_return_value	(error_printf  , (value), (condition))
#define if_true_log_and_return_value_warning(value, condition)		if_true_log_and_return_value	(warning_printf, (value), (condition))
#define if_true_log_and_return_value_info(value, condition)			if_true_log_and_return_value	(info_printf   , (value), (condition))
#define if_true_log_and_return_value_verbose(value, condition)		if_true_log_and_return_value	(verbose_printf, (value), (condition))
#define if_fail_log_and_return_value_always(value, condition)		if_fail_log_and_return_value	(always_printf , (value), (condition))
#define if_fail_log_and_return_value_error(value, condition)		if_fail_log_and_return_value	(error_printf  , (value), (condition))
#define if_fail_log_and_return_value_warning(value, condition)		if_fail_log_and_return_value	(warning_printf, (value), (condition))
#define if_fail_log_and_return_value_info(value, condition)			if_fail_log_and_return_value	(info_printf   , (value), (condition))
#define if_fail_log_and_return_value_verbose(value, condition)		if_fail_log_and_return_value	(verbose_printf, (value), (condition))
#define if_zero_log_and_return_value_always(value, condition)		if_zero_log_and_return_value	(always_printf , (value), (condition))
#define if_zero_log_and_return_value_error(value, condition)		if_zero_log_and_return_value	(error_printf  , (value), (condition))
#define if_zero_log_and_return_value_warning(value, condition)		if_zero_log_and_return_value	(warning_printf, (value), (condition))
#define if_zero_log_and_return_value_info(value, condition)			if_zero_log_and_return_value	(info_printf   , (value), (condition))
#define if_zero_log_and_return_value_verbose(value, condition)		if_zero_log_and_return_value	(verbose_printf, (value), (condition))


#define if_true_logf_always(condition, format, ...)								if_true_logf					(always_printf  , (condition), format, __VA_ARGS__)
#define if_true_logf_error(condition, format, ...)								if_true_logf					(error_printf   , (condition), format, __VA_ARGS__)
#define if_true_logf_warning(condition, format, ...)							if_true_logf					(warning_printf , (condition), format, __VA_ARGS__)
#define if_true_logf_info(condition, format, ...)								if_true_logf					(info_printf    , (condition), format, __VA_ARGS__)
#define if_true_logf_verbose(condition, format, ...)							if_true_logf					(verbose_printf , (condition), format, __VA_ARGS__)
#define if_fail_logf_always(condition, format, ...)								if_fail_logf					(always_printf  , (condition), format, __VA_ARGS__)
#define if_fail_logf_error(condition, format, ...)								if_fail_logf					(error_printf   , (condition), format, __VA_ARGS__)
#define if_fail_logf_warning(condition, format, ...)							if_fail_logf					(warning_printf , (condition), format, __VA_ARGS__)
#define if_fail_logf_info(condition, format, ...)								if_fail_logf					(info_printf    , (condition), format, __VA_ARGS__)
#define if_fail_logf_verbose(condition, format, ...)							if_fail_logf					(verbose_printf , (condition), format, __VA_ARGS__)
#define if_zero_logf_always(condition, format, ...)								if_zero_logf					(always_printf  , (condition), format, __VA_ARGS__)
#define if_zero_logf_error(condition, format, ...)								if_zero_logf					(error_printf   , (condition), format, __VA_ARGS__)
#define if_zero_logf_warning(condition, format, ...)							if_zero_logf					(warning_printf , (condition), format, __VA_ARGS__)
#define if_zero_logf_info(condition, format, ...)								if_zero_logf					(info_printf    , (condition), format, __VA_ARGS__)
#define if_zero_logf_verbose(condition, format, ...)							if_zero_logf					(verbose_printf , (condition), format, __VA_ARGS__)
#define if_true_logf_and_break_always(condition, format, ...)					if_true_logf_and_break			(always_printf  , (condition), format, __VA_ARGS__)
#define if_true_logf_and_break_error(condition, format, ...)					if_true_logf_and_break			(error_printf   , (condition), format, __VA_ARGS__)
#define if_true_logf_and_break_warning(condition, format, ...)					if_true_logf_and_break			(warning_printf , (condition), format, __VA_ARGS__)
#define if_true_logf_and_break_info(condition, format, ...)						if_true_logf_and_break			(info_printf    , (condition), format, __VA_ARGS__)
#define if_true_logf_and_break_verbose(condition, format, ...)					if_true_logf_and_break			(verbose_printf , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_break_always(condition, format, ...)					if_fail_logf_and_break			(always_printf  , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_break_error(condition, format, ...)					if_fail_logf_and_break			(error_printf   , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_break_warning(condition, format, ...)					if_fail_logf_and_break			(warning_printf , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_break_info(condition, format, ...)						if_fail_logf_and_break			(info_printf    , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_break_verbose(condition, format, ...)					if_fail_logf_and_break			(verbose_printf , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_break_always(condition, format, ...)					if_zero_logf_and_break			(always_printf  , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_break_error(condition, format, ...)					if_zero_logf_and_break			(error_printf   , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_break_warning(condition, format, ...)					if_zero_logf_and_break			(warning_printf , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_break_info(condition, format, ...)						if_zero_logf_and_break			(info_printf    , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_break_verbose(condition, format, ...)					if_zero_logf_and_break			(verbose_printf , (condition), format, __VA_ARGS__)
#define if_true_logf_and_continue_always(condition, format, ...)				if_true_logf_and_continue		(always_printf  , (condition), format, __VA_ARGS__)
#define if_true_logf_and_continue_error(condition, format, ...)					if_true_logf_and_continue		(error_printf   , (condition), format, __VA_ARGS__)
#define if_true_logf_and_continue_warning(condition, format, ...)				if_true_logf_and_continue		(warning_printf , (condition), format, __VA_ARGS__)
#define if_true_logf_and_continue_info(condition, format, ...)					if_true_logf_and_continue		(info_printf    , (condition), format, __VA_ARGS__)
#define if_true_logf_and_continue_verbose(condition, format, ...)				if_true_logf_and_continue		(verbose_printf , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_continue_always(condition, format, ...)				if_fail_logf_and_continue		(always_printf  , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_continue_error(condition, format, ...)					if_fail_logf_and_continue		(error_printf   , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_continue_warning(condition, format, ...)				if_fail_logf_and_continue		(warning_printf , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_continue_info(condition, format, ...)					if_fail_logf_and_continue		(info_printf    , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_continue_verbose(condition, format, ...)				if_fail_logf_and_continue		(verbose_printf , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_continue_always(condition, format, ...)				if_zero_logf_and_continue		(always_printf  , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_continue_error(condition, format, ...)					if_zero_logf_and_continue		(error_printf   , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_continue_warning(condition, format, ...)				if_zero_logf_and_continue		(warning_printf , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_continue_info(condition, format, ...)					if_zero_logf_and_continue		(info_printf    , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_continue_verbose(condition, format, ...)				if_zero_logf_and_continue		(verbose_printf , (condition), format, __VA_ARGS__)
#define if_true_logf_and_throw_always(condition, format, ...)					if_true_logf_and_throw			(always_printf  , (condition), format, __VA_ARGS__)
#define if_true_logf_and_throw_error(condition, format, ...)					if_true_logf_and_throw			(error_printf   , (condition), format, __VA_ARGS__)
#define if_true_logf_and_throw_warning(condition, format, ...)					if_true_logf_and_throw			(warning_printf , (condition), format, __VA_ARGS__)
#define if_true_logf_and_throw_info(condition, format, ...)						if_true_logf_and_throw			(info_printf    , (condition), format, __VA_ARGS__)
#define if_true_logf_and_throw_verbose(condition, format, ...)					if_true_logf_and_throw			(verbose_printf , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_throw_always(condition, format, ...)					if_fail_logf_and_throw			(always_printf  , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_throw_error(condition, format, ...)					if_fail_logf_and_throw			(error_printf   , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_throw_warning(condition, format, ...)					if_fail_logf_and_throw			(warning_printf , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_throw_info(condition, format, ...)						if_fail_logf_and_throw			(info_printf    , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_throw_verbose(condition, format, ...)					if_fail_logf_and_throw			(verbose_printf , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_throw_always(condition, format, ...)					if_zero_logf_and_throw			(always_printf  , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_throw_error(condition, format, ...)					if_zero_logf_and_throw			(error_printf   , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_throw_warning(condition, format, ...)					if_zero_logf_and_throw			(warning_printf , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_throw_info(condition, format, ...)						if_zero_logf_and_throw			(info_printf    , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_throw_verbose(condition, format, ...)					if_zero_logf_and_throw			(verbose_printf , (condition), format, __VA_ARGS__)
#define if_true_logf_and_return_always(condition, format, ...)					if_true_logf_and_return			(always_printf  , (condition), format, __VA_ARGS__)
#define if_true_logf_and_return_error(condition, format, ...)					if_true_logf_and_return			(error_printf   , (condition), format, __VA_ARGS__)
#define if_true_logf_and_return_warning(condition, format, ...)					if_true_logf_and_return			(warning_printf , (condition), format, __VA_ARGS__)
#define if_true_logf_and_return_info(condition, format, ...)					if_true_logf_and_return			(info_printf    , (condition), format, __VA_ARGS__)
#define if_true_logf_and_return_verbose(condition, format, ...)					if_true_logf_and_return			(verbose_printf , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_return_always(condition, format, ...)					if_fail_logf_and_return			(always_printf  , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_return_error(condition, format, ...)					if_fail_logf_and_return			(error_printf   , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_return_warning(condition, format, ...)					if_fail_logf_and_return			(warning_printf , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_return_info(condition, format, ...)					if_fail_logf_and_return			(info_printf    , (condition), format, __VA_ARGS__)
#define if_fail_logf_and_return_verbose(condition, format, ...)					if_fail_logf_and_return			(verbose_printf , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_return_always(condition, format, ...)					if_zero_logf_and_return			(always_printf  , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_return_error(condition, format, ...)					if_zero_logf_and_return			(error_printf   , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_return_warning(condition, format, ...)					if_zero_logf_and_return			(warning_printf , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_return_info(condition, format, ...)					if_zero_logf_and_return			(info_printf    , (condition), format, __VA_ARGS__)
#define if_zero_logf_and_return_verbose(condition, format, ...)					if_zero_logf_and_return			(verbose_printf , (condition), format, __VA_ARGS__)
#define if_true_logf_and_return_value_always(value, condition, format, ...)		if_true_logf_and_return_value	(always_printf  , (value), (condition), format, __VA_ARGS__)
#define if_true_logf_and_return_value_error(value, condition, format, ...)		if_true_logf_and_return_value	(error_printf   , (value), (condition), format, __VA_ARGS__)
#define if_true_logf_and_return_value_warning(value, condition, format, ...)	if_true_logf_and_return_value	(warning_printf , (value), (condition), format, __VA_ARGS__)
#define if_true_logf_and_return_value_info(value, condition, format, ...)		if_true_logf_and_return_value	(info_printf    , (value), (condition), format, __VA_ARGS__)
#define if_true_logf_and_return_value_verbose(value, condition, format, ...)	if_true_logf_and_return_value	(verbose_printf , (value), (condition), format, __VA_ARGS__)
#define if_fail_logf_and_return_value_always(value, condition, format, ...)		if_fail_logf_and_return_value	(always_printf  , (value), (condition), format, __VA_ARGS__)
#define if_fail_logf_and_return_value_error(value, condition, format, ...)		if_fail_logf_and_return_value	(error_printf   , (value), (condition), format, __VA_ARGS__)
#define if_fail_logf_and_return_value_warning(value, condition, format, ...)	if_fail_logf_and_return_value	(warning_printf , (value), (condition), format, __VA_ARGS__)
#define if_fail_logf_and_return_value_info(value, condition, format, ...)		if_fail_logf_and_return_value	(info_printf    , (value), (condition), format, __VA_ARGS__)
#define if_fail_logf_and_return_value_verbose(value, condition, format, ...)	if_fail_logf_and_return_value	(verbose_printf , (value), (condition), format, __VA_ARGS__)
#define if_zero_logf_and_return_value_always(value, condition, format, ...)		if_zero_logf_and_return_value	(always_printf  , (value), (condition), format, __VA_ARGS__)
#define if_zero_logf_and_return_value_error(value, condition, format, ...)		if_zero_logf_and_return_value	(error_printf   , (value), (condition), format, __VA_ARGS__)
#define if_zero_logf_and_return_value_warning(value, condition, format, ...)	if_zero_logf_and_return_value	(warning_printf , (value), (condition), format, __VA_ARGS__)
#define if_zero_logf_and_return_value_info(value, condition, format, ...)		if_zero_logf_and_return_value	(info_printf    , (value), (condition), format, __VA_ARGS__)
#define if_zero_logf_and_return_value_verbose(value, condition, format, ...)	if_zero_logf_and_return_value	(verbose_printf , (value), (condition), format, __VA_ARGS__)

#define if_null_log_always							if_zero_log_always
#define if_null_log_error							if_zero_log_error
#define if_null_log_warning							if_zero_log_warning
#define if_null_log_info							if_zero_log_info
#define if_null_log_verbose							if_zero_log_verbose
#define if_null_log_and_break_always				if_zero_log_and_break_always
#define if_null_log_and_break_error					if_zero_log_and_break_error
#define if_null_log_and_break_warning				if_zero_log_and_break_warning
#define if_null_log_and_break_info					if_zero_log_and_break_info
#define if_null_log_and_break_verbose				if_zero_log_and_break_verbose
#define if_null_log_and_continue_always				if_zero_log_and_continue_always
#define if_null_log_and_continue_error				if_zero_log_and_continue_error
#define if_null_log_and_continue_warning			if_zero_log_and_continue_warning
#define if_null_log_and_continue_info				if_zero_log_and_continue_info
#define if_null_log_and_continue_verbose			if_zero_log_and_continue_verbose
#define if_null_log_and_throw_always				if_zero_log_and_throw_always
#define if_null_log_and_throw_error					if_zero_log_and_throw_error
#define if_null_log_and_throw_warning				if_zero_log_and_throw_warning
#define if_null_log_and_throw_info					if_zero_log_and_throw_info
#define if_null_log_and_throw_verbose				if_zero_log_and_throw_verbose
#define if_null_log_and_return_always				if_zero_log_and_return_always
#define if_null_log_and_return_error				if_zero_log_and_return_error
#define if_null_log_and_return_warning				if_zero_log_and_return_warning
#define if_null_log_and_return_info					if_zero_log_and_return_info
#define if_null_log_and_return_verbose				if_zero_log_and_return_verbose
#define if_null_log_and_return_value_always			if_zero_log_and_return_value_always
#define if_null_log_and_return_value_error			if_zero_log_and_return_value_error
#define if_null_log_and_return_value_warning		if_zero_log_and_return_value_warning
#define if_null_log_and_return_value_info			if_zero_log_and_return_value_info
#define if_null_log_and_return_value_verbose		if_zero_log_and_return_value_verbose

#define if_null_logf_always						if_zero_logf_always
#define if_null_logf_error						if_zero_logf_error
#define if_null_logf_warning					if_zero_logf_warning
#define if_null_logf_info						if_zero_logf_info
#define if_null_logf_verbose					if_zero_logf_verbose
#define if_null_logf_and_break_always			if_zero_logf_and_break_always
#define if_null_logf_and_break_error			if_zero_logf_and_break_error
#define if_null_logf_and_break_warning			if_zero_logf_and_break_warning
#define if_null_logf_and_break_info				if_zero_logf_and_break_info
#define if_null_logf_and_break_verbose			if_zero_logf_and_break_verbose
#define if_null_logf_and_continue_always		if_zero_logf_and_continue_always
#define if_null_logf_and_continue_error			if_zero_logf_and_continue_error
#define if_null_logf_and_continue_warning		if_zero_logf_and_continue_warning
#define if_null_logf_and_continue_info			if_zero_logf_and_continue_info
#define if_null_logf_and_continue_verbose		if_zero_logf_and_continue_verbose
#define if_null_logf_and_throw_always			if_zero_logf_and_throw_always
#define if_null_logf_and_throw_error			if_zero_logf_and_throw_error
#define if_null_logf_and_throw_warning			if_zero_logf_and_throw_warning
#define if_null_logf_and_throw_info				if_zero_logf_and_throw_info
#define if_null_logf_and_throw_verbose			if_zero_logf_and_throw_verbose
#define if_null_logf_and_return_always			if_zero_logf_and_return_always
#define if_null_logf_and_return_error			if_zero_logf_and_return_error
#define if_null_logf_and_return_warning			if_zero_logf_and_return_warning
#define if_null_logf_and_return_info			if_zero_logf_and_return_info
#define if_null_logf_and_return_value_always	if_zero_logf_and_return_value_always
#define if_null_logf_and_return_value_error		if_zero_logf_and_return_value_error
#define if_null_logf_and_return_value_warning	if_zero_logf_and_return_value_warning
#define if_null_logf_and_return_value_info		if_zero_logf_and_return_value_info
#define if_null_logf_and_return_value_verbose	if_zero_logf_and_return_value_verbose

//
#define if_true_a  if_true_log_always
#define if_true_e  if_true_log_error
#define if_true_w  if_true_log_warning
#define if_true_i  if_true_log_info
#define if_true_v  if_true_log_verbose
#define if_fail_a  if_fail_log_always
#define if_fail_e  if_fail_log_error
#define if_fail_w  if_fail_log_warning
#define if_fail_i  if_fail_log_info
#define if_fail_v  if_fail_log_verbose
#define if_zero_a  if_zero_log_always
#define if_zero_e  if_zero_log_error
#define if_zero_w  if_zero_log_warning
#define if_zero_i  if_zero_log_info
#define if_zero_v  if_zero_log_verbose
#define if_null_a  if_null_log_always
#define if_null_e  if_null_log_error
#define if_null_w  if_null_log_warning
#define if_null_i  if_null_log_info
#define if_null_v  if_null_log_verbose
#define if_true_af if_true_logf_always
#define if_true_ef if_true_logf_error
#define if_true_wf if_true_logf_warning
#define if_true_if if_true_logf_info
#define if_true_vf if_true_logf_verbose
#define if_fail_af if_fail_logf_always
#define if_fail_ef if_fail_logf_error
#define if_fail_wf if_fail_logf_warning
#define if_fail_if if_fail_logf_info
#define if_fail_vf if_fail_logf_verbose
#define if_zero_af if_zero_logf_always
#define if_zero_ef if_zero_logf_error
#define if_zero_wf if_zero_logf_warning
#define if_zero_if if_zero_logf_info
#define if_zero_vf if_zero_logf_verbose
#define if_null_af if_null_logf_always
#define if_null_ef if_null_logf_error
#define if_null_wf if_null_logf_warning
#define if_null_if if_null_logf_info
#define if_null_vf if_null_logf_verbose

//
#define if_true_ba  if_true_log_and_break_always
#define if_true_be  if_true_log_and_break_error
#define if_true_bw  if_true_log_and_break_warning
#define if_true_bi  if_true_log_and_break_info
#define if_true_bv  if_true_log_and_break_verbose
#define if_fail_ba  if_fail_log_and_break_always
#define if_fail_be  if_fail_log_and_break_error
#define if_fail_bw  if_fail_log_and_break_warning
#define if_fail_bi  if_fail_log_and_break_info
#define if_fail_bv  if_fail_log_and_break_verbose
#define if_zero_ba  if_zero_log_and_break_always
#define if_zero_be  if_zero_log_and_break_error
#define if_zero_bw  if_zero_log_and_break_warning
#define if_zero_bi  if_zero_log_and_break_info
#define if_zero_bv  if_zero_log_and_break_verbose
#define if_null_ba  if_null_log_and_break_always
#define if_null_be  if_null_log_and_break_error
#define if_null_bw  if_null_log_and_break_warning
#define if_null_bi  if_null_log_and_break_info
#define if_null_bv  if_null_log_and_break_verbose
#define if_true_baf if_true_logf_and_break_always
#define if_true_bef if_true_logf_and_break_error
#define if_true_bwf if_true_logf_and_break_warning
#define if_true_bif if_true_logf_and_break_info
#define if_true_bvf if_true_logf_and_break_verbose
#define if_fail_baf if_fail_logf_and_break_always
#define if_fail_bef if_fail_logf_and_break_error
#define if_fail_bwf if_fail_logf_and_break_warning
#define if_fail_bif if_fail_logf_and_break_info
#define if_fail_bvf if_fail_logf_and_break_verbose
#define if_zero_baf if_zero_logf_and_break_always
#define if_zero_bef if_zero_logf_and_break_error
#define if_zero_bwf if_zero_logf_and_break_warning
#define if_zero_bif if_zero_logf_and_break_info
#define if_zero_bvf if_zero_logf_and_break_verbose
#define if_null_baf if_null_logf_and_break_always
#define if_null_bef if_null_logf_and_break_error
#define if_null_bwf if_null_logf_and_break_warning
#define if_null_bif if_null_logf_and_break_info
#define if_null_bvf if_null_logf_and_break_verbose
//
#define if_true_ca  if_true_log_and_continue_always
#define if_true_ce  if_true_log_and_continue_error
#define if_true_cw  if_true_log_and_continue_warning
#define if_true_ci  if_true_log_and_continue_info
#define if_true_cv  if_true_log_and_continue_verbose
#define if_fail_ca  if_fail_log_and_continue_always
#define if_fail_ce  if_fail_log_and_continue_error
#define if_fail_cw  if_fail_log_and_continue_warning
#define if_fail_ci  if_fail_log_and_continue_info
#define if_fail_cv  if_fail_log_and_continue_verbose
#define if_zero_ca  if_zero_log_and_continue_always
#define if_zero_ce  if_zero_log_and_continue_error
#define if_zero_cw  if_zero_log_and_continue_warning
#define if_zero_ci  if_zero_log_and_continue_info
#define if_zero_cv  if_zero_log_and_continue_verbose
#define if_null_ca  if_null_log_and_continue_always
#define if_null_ce  if_null_log_and_continue_error
#define if_null_cw  if_null_log_and_continue_warning
#define if_null_ci  if_null_log_and_continue_info
#define if_null_cv  if_null_log_and_continue_verbose
#define if_true_caf if_true_logf_and_continue_always
#define if_true_cef if_true_logf_and_continue_error
#define if_true_cwf if_true_logf_and_continue_warning
#define if_true_cif if_true_logf_and_continue_info
#define if_true_cvf if_true_logf_and_continue_verbose
#define if_fail_caf if_fail_logf_and_continue_always
#define if_fail_cef if_fail_logf_and_continue_error
#define if_fail_cwf if_fail_logf_and_continue_warning
#define if_fail_cif if_fail_logf_and_continue_info
#define if_fail_cvf if_fail_logf_and_continue_verbose
#define if_zero_caf if_zero_logf_and_continue_always
#define if_zero_cef if_zero_logf_and_continue_error
#define if_zero_cwf if_zero_logf_and_continue_warning
#define if_zero_cif if_zero_logf_and_continue_info
#define if_zero_cvf if_zero_logf_and_continue_verbose
#define if_null_caf if_null_logf_and_continue_always
#define if_null_cef if_null_logf_and_continue_error
#define if_null_cwf if_null_logf_and_continue_warning
#define if_null_cif if_null_logf_and_continue_info
#define if_null_cvf if_null_logf_and_continue_verbose
//
#define if_true_va  if_true_log_and_return_value_always
#define if_true_ve  if_true_log_and_return_value_error
#define if_true_vw  if_true_log_and_return_value_warning
#define if_true_vi  if_true_log_and_return_value_info
#define if_true_vv  if_true_log_and_return_value_verbose
#define if_fail_va  if_fail_log_and_return_value_always
#define if_fail_ve  if_fail_log_and_return_value_error
#define if_fail_vw  if_fail_log_and_return_value_warning
#define if_fail_vi  if_fail_log_and_return_value_info
#define if_fail_vv  if_fail_log_and_return_value_verbose
#define if_zero_va  if_zero_log_and_return_value_always
#define if_zero_ve  if_zero_log_and_return_value_error
#define if_zero_vw  if_zero_log_and_return_value_warning
#define if_zero_vi  if_zero_log_and_return_value_info
#define if_zero_vv  if_zero_log_and_return_value_verbose
#define if_null_va  if_null_log_and_return_value_always
#define if_null_ve  if_null_log_and_return_value_error
#define if_null_vw  if_null_log_and_return_value_warning
#define if_null_vi  if_null_log_and_return_value_info
#define if_null_vv  if_null_log_and_return_value_verbose
#define if_true_vaf if_true_logf_and_return_value_always
#define if_true_vef if_true_logf_and_return_value_error
#define if_true_vwf if_true_logf_and_return_value_warning
#define if_true_vif if_true_logf_and_return_value_info
#define if_true_vvf if_true_logf_and_return_value_verbose
#define if_fail_vaf if_fail_logf_and_return_value_always
#define if_fail_vef if_fail_logf_and_return_value_error
#define if_fail_vwf if_fail_logf_and_return_value_warning
#define if_fail_vif if_fail_logf_and_return_value_info
#define if_fail_vvf if_fail_logf_and_return_value_verbose
#define if_zero_vaf if_zero_logf_and_return_value_always
#define if_zero_vef if_zero_logf_and_return_value_error
#define if_zero_vwf if_zero_logf_and_return_value_warning
#define if_zero_vif if_zero_logf_and_return_value_info
#define if_zero_vvf if_zero_logf_and_return_value_verbose
#define if_null_vaf if_null_logf_and_return_value_always
#define if_null_vef if_null_logf_and_return_value_error
#define if_null_vwf if_null_logf_and_return_value_warning
#define if_null_vif if_null_logf_and_return_value_info
#define if_null_vvf if_null_logf_and_return_value_verbose //
#define a_if       if_true_a 
#define e_if       if_true_e 
#define w_if       if_true_w 
#define i_if       if_true_i 
#define v_if       if_true_v 
#define a_if_fail  if_fail_a 
#define e_if_fail  if_fail_e 
#define w_if_fail  if_fail_w 
#define i_if_fail  if_fail_i 
#define v_if_fail  if_fail_v 
#define a_if_zero  if_zero_a 
#define e_if_zero  if_zero_e 
#define w_if_zero  if_zero_w 
#define i_if_zero  if_zero_i 
#define v_if_zero  if_zero_v 
#define a_if_null  if_null_a 
#define e_if_null  if_null_e 
#define w_if_null  if_null_w 
#define i_if_null  if_null_i 
#define v_if_null  if_null_v 
#define af_if      if_true_af 
#define ef_if      if_true_ef 
#define wf_if      if_true_wf 
#define if_if      if_true_if 
#define vf_if      if_true_vf 
#define af_if_fail if_fail_af 
#define ef_if_fail if_fail_ef 
#define wf_if_fail if_fail_wf 
#define if_if_fail if_fail_if 
#define vf_if_fail if_fail_vf 
#define af_if_zero if_zero_af 
#define ef_if_zero if_zero_ef 
#define wf_if_zero if_zero_wf 
#define if_if_zero if_zero_if 
#define vf_if_zero if_zero_vf 
#define af_if_null if_null_af 
#define ef_if_null if_null_ef 
#define wf_if_null if_null_wf 
#define if_if_null if_null_if 
#define vf_if_null if_null_vf 
//
#define va_if       if_true_va 
#define ve_if       if_true_ve 
#define vw_if       if_true_vw 
#define vi_if       if_true_vi 
#define vv_if       if_true_vv 
#define va_if_fail  if_fail_va 
#define ve_if_fail  if_fail_ve 
#define vw_if_fail  if_fail_vw 
#define vi_if_fail  if_fail_vi 
#define vv_if_fail  if_fail_vv 
#define va_if_zero  if_zero_va 
#define ve_if_zero  if_zero_ve 
#define vw_if_zero  if_zero_vw 
#define vi_if_zero  if_zero_vi 
#define vv_if_zero  if_zero_vv 
#define va_if_null  if_null_va 
#define ve_if_null  if_null_ve 
#define vw_if_null  if_null_vw 
#define vi_if_null  if_null_vi 
#define vv_if_null  if_null_vv 
#define vaf_if      if_true_vaf 
#define vef_if      if_true_vef 
#define vwf_if      if_true_vwf 
#define vif_if      if_true_vif 
#define vvf_if      if_true_vvf 
#define vaf_if_fail if_fail_vaf 
#define vef_if_fail if_fail_vef 
#define vwf_if_fail if_fail_vwf 
#define vif_if_fail if_fail_vif 
#define vvf_if_fail if_fail_vvf 
#define vaf_if_zero if_zero_vaf 
#define vef_if_zero if_zero_vef 
#define vwf_if_zero if_zero_vwf 
#define vif_if_zero if_zero_vif 
#define vvf_if_zero if_zero_vvf 
#define vaf_if_null if_null_vaf 
#define vef_if_null if_null_vef 
#define vwf_if_null if_null_vwf 
#define vif_if_null if_null_vif 
#define vvf_if_null if_null_vvf 
//
#define ba_if       if_true_ba 
#define be_if       if_true_be 
#define bw_if       if_true_bw 
#define bi_if       if_true_bi 
#define bv_if       if_true_bv 
#define ba_if_fail  if_fail_ba 
#define be_if_fail  if_fail_be 
#define bw_if_fail  if_fail_bw 
#define bi_if_fail  if_fail_bi 
#define bv_if_fail  if_fail_bv 
#define ba_if_zero  if_zero_ba 
#define be_if_zero  if_zero_be 
#define bw_if_zero  if_zero_bw 
#define bi_if_zero  if_zero_bi 
#define bv_if_zero  if_zero_bv 
#define ba_if_null  if_null_ba 
#define be_if_null  if_null_be 
#define bw_if_null  if_null_bw 
#define bi_if_null  if_null_bi 
#define bv_if_null  if_null_bv 
#define baf_if      if_true_baf 
#define bef_if      if_true_bef 
#define bwf_if      if_true_bwf 
#define bif_if      if_true_bif 
#define bvf_if      if_true_bvf 
#define baf_if_fail if_fail_baf 
#define bef_if_fail if_fail_bef 
#define bwf_if_fail if_fail_bwf 
#define bif_if_fail if_fail_bif 
#define bvf_if_fail if_fail_bvf 
#define baf_if_zero if_zero_baf 
#define bef_if_zero if_zero_bef 
#define bwf_if_zero if_zero_bwf 
#define bif_if_zero if_zero_bif 
#define bvf_if_zero if_zero_bvf 
#define baf_if_null if_null_baf 
#define bef_if_null if_null_bef 
#define bwf_if_null if_null_bwf 
#define bif_if_null if_null_bif 
#define bvf_if_null if_null_bvf 
//
#define ca_if       if_true_ca 
#define ce_if       if_true_ce 
#define cw_if       if_true_cw 
#define ci_if       if_true_ci 
#define cv_if       if_true_cv 
#define ca_if_fail  if_fail_ca 
#define ce_if_fail  if_fail_ce 
#define cw_if_fail  if_fail_cw 
#define ci_if_fail  if_fail_ci 
#define cv_if_fail  if_fail_cv 
#define ca_if_zero  if_zero_ca 
#define ce_if_zero  if_zero_ce 
#define cw_if_zero  if_zero_cw 
#define ci_if_zero  if_zero_ci 
#define cv_if_zero  if_zero_cv 
#define ca_if_null  if_null_ca 
#define ce_if_null  if_null_ce 
#define cw_if_null  if_null_cw 
#define ci_if_null  if_null_ci 
#define cv_if_null  if_null_cv 
#define caf_if      if_true_caf 
#define cef_if      if_true_cef 
#define cwf_if      if_true_cwf 
#define cif_if      if_true_cif 
#define cvf_if      if_true_cvf 
#define caf_if_fail if_fail_caf 
#define cef_if_fail if_fail_cef 
#define cwf_if_fail if_fail_cwf 
#define cif_if_fail if_fail_cif 
#define cvf_if_fail if_fail_cvf 
#define caf_if_zero if_zero_caf 
#define cef_if_zero if_zero_cef 
#define cwf_if_zero if_zero_cwf 
#define cif_if_zero if_zero_cif 
#define cvf_if_zero if_zero_cvf 
#define caf_if_null if_null_caf 
#define cef_if_null if_null_cef 
#define cwf_if_null if_null_cwf 
#define cif_if_null if_null_cif 
#define cvf_if_null if_null_cvf 
//
#define a_ecall  if_fail_a
#define e_ecall  if_fail_e
#define w_ecall  if_fail_w
#define i_ecall  if_fail_i
#define v_ecall  if_fail_v
#define va_ecall if_fail_va
#define ve_ecall if_fail_ve
#define vw_ecall if_fail_vw
#define vi_ecall if_fail_vi
#define vv_ecall if_fail_vv
#define ba_ecall if_fail_ba
#define be_ecall if_fail_be
#define bw_ecall if_fail_bw
#define bi_ecall if_fail_bi
#define bv_ecall if_fail_bv
#define ca_ecall if_fail_ca
#define ce_ecall if_fail_ce
#define cw_ecall if_fail_cw
#define ci_ecall if_fail_ci
#define cv_ecall if_fail_cv

#define a_ecallf  if_fail_af
#define e_ecallf  if_fail_ef
#define w_ecallf  if_fail_wf
#define i_ecallf  if_fail_if
#define v_ecallf  if_fail_vf
#define va_ecallf if_fail_vaf
#define ve_ecallf if_fail_vef
#define vw_ecallf if_fail_vwf
#define vi_ecallf if_fail_vif
#define vv_ecallf if_fail_vvf
#define ba_ecallf if_fail_baf
#define be_ecallf if_fail_bef
#define bw_ecallf if_fail_bwf
#define bi_ecallf if_fail_bif
#define bv_ecallf if_fail_bvf
#define ca_ecallf if_fail_caf
#define ce_ecallf if_fail_cef
#define cw_ecallf if_fail_cwf
#define ci_ecallf if_fail_cif
#define cv_ecallf if_fail_cvf

#endif // LLC_LOG_LEVEL_H
