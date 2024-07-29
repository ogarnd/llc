#include "llc_cstdio.h"

#ifndef LLC_FILE_H_23627
#define LLC_FILE_H_23627

namespace llc
{
	::llc::error_t			with			(vcs filepath, vcs mode, const ::llc::function<::llc::err_t(FILE*&)> & funcFile);	// 

	::llc::error_t			fileJoin		(::llc::vcs fileNameDst);								// Joins a file split into file.split.## parts.
	::llc::error_t			fileSplit		(::llc::vcs fileNameSrc, const uint32_t partSize);		// Splits a file into file.split.## parts.
	int64_t					fileSize		(::llc::vcs fileName);
	::llc::error_t			fileDelete		(::llc::vcs fileName);

	::llc::error_t			fileFromMemory	(::llc::vcs fileName, const ::llc::vcu8 & fileInMemory, bool append = false);
	::llc::error_t			fileToMemory	(::llc::vcs fileName, ::llc::au8 & fileInMemory, uint32_t maxSize = 0xFFFFFFFFU, uint64_t offset = 0);
	::llc::error_t			fileToMemory	(::llc::vcs folderPath, ::llc::vcs fileName, ::llc::au8 & fileBytes, uint32_t maxSize = 0xFFFFFFFFU, uint64_t offset = 0);
	::llc::error_t			fileFromMemory	(::llc::vcs folderPath, ::llc::vcs fileName, const ::llc::vcu8 & fileInMemory, bool append = false);

	stainli	::llc::error_t	fileToMemory	(::llc::vcs fileName, ::llc::ai8 & fileInMemory, uint32_t maxSize = 0xFFFFFFFFU, uint64_t offset = 0)	{ return ::llc::fileToMemory	(fileName, *(::llc::au8*)&fileInMemory, maxSize, offset); }
	stainli	::llc::error_t	fileToMemory	(::llc::vcs fileName, ::llc::ac  & fileInMemory, uint32_t maxSize = 0xFFFFFFFFU, uint64_t offset = 0)	{ return ::llc::fileToMemory	(fileName, *(::llc::au8*)&fileInMemory, maxSize, offset); }
	stainli	::llc::error_t	fileFromMemory	(::llc::vcs fileName, const ::llc::vci8 & fileInMemory, bool append = false)						{ return ::llc::fileFromMemory	(fileName, *(const ::llc::vcu8*)&fileInMemory, append); }
	stainli	::llc::error_t	fileFromMemory	(::llc::vcs fileName, const ::llc::vcc  & fileInMemory, bool append = false)						{ return ::llc::fileFromMemory	(fileName, *(const ::llc::vcu8*)&fileInMemory, append); }

	GDEFINE_ENUM_TYPE(OPEN_MODE, i2u_t);
	GDEFINE_ENUM_VALUE(OPEN_MODE, CLOSE		, 0);												
	GDEFINE_ENUM_VALUE(OPEN_MODE, READ		, 'r' + (i1u_t('b') << 8));							//  1
	GDEFINE_ENUM_VALUE(OPEN_MODE, WRITE		, 'w' + (i1u_t('b') << 8));							//  2
	GDEFINE_ENUM_VALUE(OPEN_MODE, APPEND	, 'a' + (i2u_t('b') << 8) + (i2u_t('+') << 16));	//  3
	// FILE wrapper
	tplT	struct SFile {	
		T							File			{};
		uint64_t					Offset			= {};
		vcs							Name			= {};

		inline						~SFile			()						{ llc_safe_fclose(File); }

		inlcxpr	operatr				T&				()						{ return File; }

		tpltTOut	err_t			read			(view<TOut> output)		{ if(0 == File) llc_necall(::llc::fopen_s(&File, Name.begin(), "rb"), "%s", Name.begin()); auto nread = fread(output.begin(), sizeof(TOut), output.size(), File); fail_if_neu(nread, output.size()); return nread; }
		tpltTOutN2	inline	err_t	read			(TOut (&output)[N])		{ return read<TOut>(output); }
	};

	struct CFile : SFile<FILE*> {};

} // namespace

#endif // LLC_FILE_H_23627
