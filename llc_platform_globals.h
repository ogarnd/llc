/// Copyright 2010-2023 - ogarnd
#ifndef LLC_PLATFORM_GLOBALS_H_23627
#define LLC_PLATFORM_GLOBALS_H_23627

#if(!defined(LLC_ESPIDF)) && (defined(ESP32) || defined(ESP_PLATFORM) || defined(ARDUINO_ARCH_ESP32))
#	define LLC_ESPIDF
#endif

#if (!defined(LLC_ARDUINO)) && (defined(__ARDUINO__) || defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266))
#	define LLC_ARDUINO
#endif

#if (!defined(LLC_ATMEL)) && defined(__ATMEGA__)
#	define LLC_ATMEL
#elif (!defined(LLC_ESP32)) && (defined(ESP32) || defined(ARDUINO_ARCH_ESP32))
#	define LLC_ESP32
#elif(!defined(LLC_ESP8266)) && (defined(ESP8266) || defined(ARDUINO_ARCH_ESP8266))
#	define LLC_ESP8266
#elif (!defined(LLC_ANDROID)) && (defined(ANDROID) || defined(__ANDROID__))
#	define LLC_ANDROID
#elif (!defined(LLC_LINUX)) && defined(__linux__)
#	define LLC_LINUX
#elif (!defined(LLC_WINDOWS)) && (defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64))
#	define LLC_WINDOWS
#endif

#if (!defined(LLC_ST)) && !defined(LLC_CMSIS) && !defined(LLC_ESP32) && !defined(LLC_ATMEL) && !defined(LLC_ARDUINO) && !defined(LLC_WINDOWS) && !defined(LLC_LINUX) && !defined(LLC_ANDROID)
#	error "Unsupported platform."
#	define LLC_UNKNOWN
#endif

#if (defined(DEBUG) || defined(_DEBUG)) && (!defined(LLC_DISABLE_DEBUG)) && !defined(LLC_DEBUG_ENABLED)
#	define LLC_DEBUG_ENABLED
#	if !defined(USE_DEBUG_BREAK_ON_ERROR_LOG)
#		define USE_DEBUG_BREAK_ON_ERROR_LOG
#	endif
#endif	// _DEBUG

#if (!defined(LLC_MTSUPPORT)) && !defined(LLC_DISABLE_MTSUPPORT)
#	define LLC_MTSUPPORT
#endif


#ifdef __GNUC__
#	define UNUSED __attribute__((__unused__))
#elif defined(LLC_WINDOWS)
#	ifdef _DEBUG
#		define UNUSED
#	else
#		define UNUSED
#	endif
#else
#	define UNUSED
#endif

#if defined(LLC_WINDOWS)
//#	pragma warning(disable : 4592)		// We needed this because of a bug in the compiler causing our static const variables to throw a warning as if its constructor was defined as constexpr.
//#	pragma warning(disable : 6326)		// Bogus potential comparison of a constant with another constant for static tplt functionality.
#	pragma warning(disable : 4706)		// Enable assignment within conditional expression. We do this constantly inside our macros in a completely valid way.
#endif

#if defined(LLC_WINDOWS)
#	if !defined(NOMINMAX)
#		define NOMINMAX
#	endif
#	if !defined(WIN32_LEAN_AND_MEAN)
#		define WIN32_LEAN_AND_MEAN
#	endif
#	define LLC_DYNAMIC_LIBRARY_EXTENSION "dll"
#else
#	define LLC_DYNAMIC_LIBRARY_EXTENSION "os"
#endif

#if defined LLC_ANDROID
#	define LLC_DISABLE_CPP_EXCEPTIONS
#endif

// These aliases make keyword width to be consistent and makes the code less verbose.
#define tydf			typedef
#define cnst			const
#define tdcs			tydf cnst
#define vltl			volatile
#define tdvl			tydf vltl
#define csvl			cnst vltl
#define tdcv			tydf csvl
#define nxpt			noexcept
#define csnx			cnst nxpt
#define sttc			static
#define inln			inline
#define stin			sttc inln
#define cxpr			constexpr
#define stxp			sttc cxpr
#define inxp			inln cxpr
#define sinx			stin cxpr
#define ndsc			[[nodiscard]]
#define ndcs			ndsc cnst
#define ndst			ndsc sttc
#define ndin			ndsc inln
#define ndsi			ndsc stin
#define ndxp			ndsc cxpr
#define ndsx			ndsc stxp
#define ndix			ndsc inxp
#define nsix			ndsc sinx
#define rtrn			return
#define oper			operator
#define tplt			template
#define tpnm			typename
#define sgnd			signed
#define unsd			unsigned
#define usng			using
#define stct			struct
#define clss			class
#define pblc			public
#define prtc			protected
#define priv			private

#define tpl(typeName)	tplt<tpnm typeName>
#define tdfT(type)		tydf	type	T
#define tplT			tpl(T)
#define tplT2			tpl(T2)
#define tpl_t			tpl(_t)
#define tpl_t2			tpl(_t2)
#define tplTstct		tplT	stct
#define tplTusng		tplT	usng
#define tplTndsx		tplT	ndsx
#define tplTsinx		tplT	sinx
#define tplTstxp		tplT	stxp
#define tplTnsix		tplT	nsix
#define tpl_tstct		tpl_t	stct
#define tpl_tusng		tpl_t	usng
#define tpl_tndsx		tpl_t	ndsx
#define tpl_tsinx		tpl_t	sinx
#define tpl_tstxp		tpl_t	stxp
#define tpl_tnsix		tpl_t	nsix 

#define tplTInTOut		tplt<tpnm TIn, tpnm TOut>
#define tpl_vtArgs		tplt<tpnm... _tArgs>

#define cxpr_if(condition)		if cxpr(condition)
#define cxpr_if_not(condition)	if cxpr(not(condition))
#define if_not(condition)		if(not(condition))

#define	LLC_STRINGIFY(x) #x
#define	LLC_TOSTRING(x)  LLC_STRINGIFY(x)


#define LLCREP0(param)			  (param)
#define LLCREP1(param)			  LLCREP0(param), (param)
#define LLCREP2(param)			  LLCREP1(param), (param)
#define LLCREP3(param)			  LLCREP2(param), (param)
#define LLCREP4(param)			  LLCREP3(param), (param)
#define LLCREP5(param)			  LLCREP4(param), (param)
#define LLCREP6(param)			  LLCREP5(param), (param)
#define LLCREP7(param)			  LLCREP6(param), (param)

#endif // LLC_PLATFORM_GLOBALS_H_23627
