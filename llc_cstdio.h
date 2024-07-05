#include "llc_log.h"
#include "llc_cstring.h"

#ifdef LLC_ARDUINO
#	include <stdio.h>
#else
#	include <cstdio>
#endif

#ifndef LLC_IO_H_56847984984__
#define LLC_IO_H_56847984984__

namespace llc
{
	stainli ::llc::error_t	fopen_s		(FILE** out_fp, const char* pFilename, const char* mode) {
		ree_if(0 == out_fp, "File pointer cannot be a null pointer. File name: %s.", pFilename);
#if defined(LLC_WINDOWS)
		return ::fopen_s(out_fp, pFilename, mode);
#else
		FILE						* fp		= fopen(pFilename, mode);
		return (0 == (*out_fp = fp)) ? -1:  0;
#endif
	}
} // namespace

#endif // LLC_IO_H_56847984984__
