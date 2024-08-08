#include "llc_cstdio.h"

#ifndef LLC_FILE_H_23627
#define LLC_FILE_H_23627

namespace llc
{
	err_t			with			(vcs filepath, vcs mode, const ::llc::function<::llc::err_t(FILE*&)> & funcFile);	// 

	err_t			fileJoin		(::llc::vcst_t fileNameDst);								// Joins a file split into file.split.## parts.
	err_t			fileSplit		(::llc::vcst_t fileNameSrc, u2_c partSize);		// Splits a file into file.split.## parts.
	s3_t			fileSize		(::llc::vcst_t fileName);
	err_t			fileDelete		(::llc::vcst_t fileName);

	err_t			fileFromMemory	(::llc::vcst_t fileName, vcu0_c & fileInMemory, bool append = false);
	err_t			fileToMemory	(::llc::vcst_t fileName, ::llc::au0_t & fileInMemory, uint32_t maxSize = 0xFFFFFFFFU, uint64_t offset = 0);
	err_t			fileToMemory	(::llc::vcst_t folderPath, ::llc::vcst_t fileName, ::llc::au0_t & fileBytes, uint32_t maxSize = 0xFFFFFFFFU, uint64_t offset = 0);
	err_t			fileFromMemory	(::llc::vcst_t folderPath, ::llc::vcst_t fileName, vcu0_c & fileInMemory, bool append = false);

	stin	err_t	fileToMemory	(::llc::vcst_t fileName, ::llc::as0_t & fileInMemory, uint32_t maxSize = 0xFFFFFFFFU, uint64_t offset = 0)	{ return ::llc::fileToMemory	(fileName, *(::llc::au0_t*)&fileInMemory, maxSize, offset); }
	stin	err_t	fileToMemory	(::llc::vcst_t fileName, ::llc::asc_t  & fileInMemory, uint32_t maxSize = 0xFFFFFFFFU, uint64_t offset = 0)	{ return ::llc::fileToMemory	(fileName, *(::llc::au0_t*)&fileInMemory, maxSize, offset); }
	stin	err_t	fileFromMemory	(::llc::vcst_t fileName, vcs0_c & fileInMemory, bool append = false)						{ return ::llc::fileFromMemory	(fileName, *(vcu0_c*)&fileInMemory, append); }
	stin	err_t	fileFromMemory	(::llc::vcst_t fileName, ::llc::vcsc_c  & fileInMemory, bool append = false)						{ return ::llc::fileFromMemory	(fileName, *(vcu0_c*)&fileInMemory, append); }

	GDEFINE_ENUM_TYPE(OPEN_MODE, i2u_t);
	GDEFINE_ENUM_VALUE(OPEN_MODE, CLOSE		, 0);												
	GDEFINE_ENUM_VALUE(OPEN_MODE, READ		, 'r' + (i1u_t('b') << 8));							//  1
	GDEFINE_ENUM_VALUE(OPEN_MODE, WRITE		, 'w' + (i1u_t('b') << 8));							//  2
	GDEFINE_ENUM_VALUE(OPEN_MODE, APPEND	, 'a' + (i2u_t('b') << 8) + (i2u_t('+') << 16));	//  3
	// FILE wrapper
	tpl_t struct SFile {	
		tydf	_t					T;
		T							File			{};
		uint64_t					Offset			= {};
		vcs							Name			= {};

		inline						~SFile			()						{ llc_safe_fclose(File); }

		inxp		oper			T&				()						{ return File; }

		tplTOut		err_t			read			(view<TOut> output)		{ if(0 == File) llc_necall(::llc::fopen_s(&File, Name.begin(), "rb"), "%s", Name.begin()); auto nread = fread(output.begin(), szof(TOut), output.size(), File); fail_if_neu(nread, output.size()); return nread; }
		tplTOutN2	inline	err_t	read			(TOut (&output)[N])		{ return read<TOut>(output); }
	};

	struct CFile : SFile<FILE*> {};

} // namespace

#endif // LLC_FILE_H_23627
