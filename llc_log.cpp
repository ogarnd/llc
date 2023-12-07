#include "llc_log.h"
#include "llc_string.h"
#include "llc_size.h"

#ifdef LLC_ATMEL
#	include <stdio.h>
#else
#	include <cstdio>
#endif

#ifdef LLC_WINDOWS
#	include <Windows.h>
#else
#	include <errno.h>
#	ifdef LLC_ANDROID
#		include <android/log.h>
#		define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO , "llc_app", __VA_ARGS__))
#		define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "llc_app", __VA_ARGS__))
#		ifndef NDEBUG
#			define LOGV(...)  ((void)__android_log_print(ANDROID_LOG_VERBOSE, "llc_app", __VA_ARGS__))
#		else
#			define LOGV(...)  ((void)0)
#		endif
#	endif
#endif

#if (defined(LLC_WINDOWS) || defined(LLC_ANDROID))
static void default_base_log_write(const char * text, uint32_t textLen) {
#if defined(LLC_WINDOWS)
	OutputDebugStringA(text); (void)textLen;
#elif defined(LLC_ANDROID)
	LOGI("%s", text); (void)textLen;
#else
	printf("%s", text); (void)textLen;
#endif
}

static void default_base_log_print(const char * text) {
#if defined(LLC_WINDOWS)
	OutputDebugStringA(text);
#elif defined(LLC_ANDROID)
	LOGI("%s", text);
#else
	printf("%s", text);
#endif
}
::llc::log_write_t		llc_log_write					= default_base_log_write;
::llc::log_print_t		llc_log_print					= default_base_log_print;
#else
::llc::log_write_t		llc_log_write					= {};
::llc::log_print_t		llc_log_print					= {};
#endif

void					llc::_base_log_print			(const char* text)						{ if(llc_log_print && text) ::llc_log_print(text); }
void					llc::_base_log_write			(const char* text, uint32_t textLen)	{ if(llc_log_write && text && textLen) ::llc_log_write(text, textLen); }
#ifdef LLC_LOG_ARDUINO_FLASHSTRINGHELPER
::llc::log_print_P_t	llc_log_print_P					= {};
void					llc::_base_log_print_P			(const __FlashStringHelper* text)		{ if(llc_log_print_P && text) ::llc_log_print_P(text); }
#endif

#ifndef LLC_ARDUINO

static	::llc::error_t	getSystemErrorAsString			(const uint64_t lastError, char* buffer, uint32_t bufferSize)			{	// Get the error message, if any.
#ifdef LLC_WINDOWS
	rees_if(0 == buffer);
	return lastError 
		? ::FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, (DWORD)(lastError & 0xFFFFFFFF), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer, bufferSize, NULL)
		: 0
		;
#else
	(void) bufferSize;
	sprintf(buffer, "%u.", (uint32_t)lastError);
	return 0;
#endif
}

		void					llc::_llc_print_system_errors	(const char* prefix, uint32_t prefixLen)								{
	char								bufferError[256]				= {};
#if defined(LLC_WINDOWS)
	int64_t								lastSystemError					= ::GetLastError() & 0xFFFFFFFFFFFFFFFFLL;
#else
	int64_t								lastSystemError					= -1;
#endif
	if(lastSystemError) {
		base_log_write("\n", 1);
		::llc::error_t						stringLength					= ::getSystemErrorAsString((uint64_t)lastSystemError, bufferError, ::llc::size(bufferError));
		base_log_write(prefix, prefixLen);
		base_log_write(bufferError, (uint32_t)stringLength);
		base_log_write("\n", 1);
	}
	lastSystemError					= errno;
	if(lastSystemError) {
		base_log_write("\n", 1);
#ifdef LLC_WINDOWS
		::strerror_s(bufferError, (int)lastSystemError);
		{
#else
		const char * serr = ::strerror((int)lastSystemError);
		if(serr) {
			strcpy_s(bufferError, serr);
#endif
			char		bufferError2[256]	= {};
#ifdef LLC_WINDOWS
			size_t		stringLength		= ::snprintf(bufferError2, ::llc::size(bufferError2) - 2, "Last system error: 0x%llX '%s'.", lastSystemError, bufferError);
#else
			size_t		stringLength		= ::snprintf(bufferError2, ::llc::size(bufferError2) - 2, "Last system error: 0x%llX '%s'.", (unsigned long long)lastSystemError, bufferError);
#endif
			base_log_write(prefix, prefixLen);
			base_log_write(bufferError2, (uint32_t)stringLength);
			base_log_write("\n", 1);
		}
	}
#ifdef LLC_CLEAR_SYSTEM_ERROR_ON_ERROR_LOG
#	ifdef LLC_WINDOWS
#		define llcClearSystemError() SetLastError(0)
#	else
#		define llcClearSystemError() do{} while(0)
#	endif
#else
#	define llcClearSystemError() do{} while(0)
#endif // LLC_CLEAR_SYSTEM_ERROR_ON_ERROR_LOG

	llcClearSystemError();
}

#endif // LLC_ARDUINO
