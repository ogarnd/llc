#include "llc_typeint.h"

#ifndef LLC_SAFE_H_23627
#define LLC_SAFE_H_23627

#ifndef llc_safe_free
#	define llc_safe_free(p) do { if(p) { free(p); p = 0; } } while(0)
#endif // llc_safe_free

#ifndef llc_safe_delete
#	define llc_safe_delete(p) do { if(p) { delete(p); p = 0; } } while(0)
#endif // llc_safe_delete

#ifndef llc_safe_assign
#	define llc_safe_assign(p, val) do { if(p) (*p) = (val); } while(0)
#endif // llc_safe_assign

#ifndef llc_safe_podcpy
#	define llc_safe_podcpy(oldValue, val) do { if((oldValue) && (val)) ::llc::podcpy((oldValue), (val)); } while(0)
#endif // llc_safe_podcpy

#ifndef llc_safe_fclose
#	define llc_safe_fclose(p) do { if(p) { fclose(p); p = 0; } } while(0)
#endif // llc_safe_fclose

#ifndef llc_safe_closesocket
#	if defined(LLC_WINDOWS)
#		define llc_safe_closesocket(p) do { if((p) != 0 && (p) != INVALID_SOCKET) { closesocket(p); (p) = INVALID_SOCKET; } } while(0)
#	else
#		define llc_safe_closesocket(p) do { if((p) != 0 && (p) != -1) { ::close(p); (p) = -1; } } while(0)
#	endif
#endif


#if defined(LLC_WINDOWS)
#	ifndef llc_safe_closehandle
#		define WIN32_LEAN_AND_MEAN
#		include <Windows.h>
#		define llc_safe_closehandle(p) do { if(INVALID_HANDLE_VALUE != (p)) { CloseHandle(p); (p) = INVALID_HANDLE_VALUE; } } while(0)
#	endif
#endif

#endif // LLC_SAFE_H_23627
