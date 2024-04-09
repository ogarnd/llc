#include "llc_array_pod.h"

#ifndef LLC_FILE_H_23627
#define LLC_FILE_H_23627

namespace llc
{
	::llc::error_t			fileJoin		(::llc::vcs fileNameDst);								// Joins a file split into file.split.## parts.
	::llc::error_t			fileSplit		(::llc::vcs fileNameSrc, const uint32_t partSize);		// Splits a file into file.split.## parts.
	int64_t					fileSize		(::llc::vcs fileName);
	::llc::error_t			fileDelete		(::llc::vcs fileName);
	::llc::error_t			fileFromMemory	(::llc::vcs fileName, const ::llc::vcu8 & fileInMemory, bool append = false);
	::llc::error_t			fileToMemory	(::llc::vcs fileName, ::llc::au8 & fileInMemory);
	::llc::error_t			fileToMemory	(::llc::vcs folderPath, ::llc::vcs fileName, ::llc::au8 & fileBytes);
	::llc::error_t			fileFromMemory	(::llc::vcs folderPath, ::llc::vcs fileName, const ::llc::vcu8 & fileInMemory, bool append = false);

	stainli	::llc::error_t	fileToMemory	(::llc::vcs fileName, ::llc::ai8 & fileInMemory)								{ return ::llc::fileToMemory	(fileName, *(::llc::au8*)&fileInMemory); }
	stainli	::llc::error_t	fileFromMemory	(::llc::vcs fileName, const ::llc::vci8 & fileInMemory, bool append = false)	{ return ::llc::fileFromMemory	(fileName, *(const ::llc::vcu8*)&fileInMemory, append);; }
	stainli	::llc::error_t	fileToMemory	(::llc::vcs fileName, ::llc::ac & fileInMemory)									{ return ::llc::fileToMemory	(fileName, *(::llc::au8*)&fileInMemory); }
	stainli	::llc::error_t	fileFromMemory	(::llc::vcs fileName, const ::llc::vcc & fileInMemory, bool append = false)		{ return ::llc::fileFromMemory	(fileName, *(const ::llc::vcu8*)&fileInMemory, append);; }
} // namespace

#endif // LLC_FILE_H_23627
