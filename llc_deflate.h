#include "llc_array_obj.h"
#include "llc_array_pod.h"

#ifndef LLC_DEFLATE_H_23627
#define LLC_DEFLATE_H_23627

namespace llc
{
#pragma pack(push, 1)
	struct SPackHeader {
		uint32_t				TotalFileCount					;
		uint32_t				SizeCompressedTableFiles		;
		uint32_t				SizeCompressedContentsPacked	;
		uint32_t				SizeUncompressedTableFiles		;
		uint32_t				SizeUncompressedContentsPacked	;
	};
#pragma pack(pop)

	struct SFolderPackage {
		::llc::SPackHeader 		PackageInfo						= {};
		::llc::au8				CompressedTableFiles			;
		::llc::au8				CompressedContentsPacked		;
	};

	struct SFolderInMemory {
		::llc::au8				DataContents					;
		::llc::au8				DataInfo						;
		::llc::avcu8			Contents						;
		::llc::avcc				Names							;
	};


#if defined(LLC_ESP32) || defined(LLC_ARDUINO)
	stacxpr	uint32_t		DEFLATE_DEFAULT_CHUNK_SIZE		= 1024 * 4;
	stacxpr	uint32_t		INFLATE_DEFAULT_CHUNK_SIZE		= 1024 * 4;
#else
	stacxpr	uint32_t		DEFLATE_DEFAULT_CHUNK_SIZE		= 1024 * 32;
	stacxpr	uint32_t		INFLATE_DEFAULT_CHUNK_SIZE		= 1024 * 32;
#endif	

	::llc::error_t			arrayDeflate			(const ::llc::vcu8 & inflated, ::llc::au8 & deflated, const uint32_t chunkSize = ::llc::DEFLATE_DEFAULT_CHUNK_SIZE);
	::llc::error_t			arrayInflate			(const ::llc::vcu8 & deflated, ::llc::au8 & inflated, const uint32_t chunkSize = ::llc::INFLATE_DEFAULT_CHUNK_SIZE);

	stainli	::llc::error_t	arrayDeflate			(const ::llc::vci8 & inflated, ::llc::au8 & deflated, const uint32_t chunkSize = ::llc::DEFLATE_DEFAULT_CHUNK_SIZE) { return ::llc::arrayDeflate(*(::llc::vcu8*)&inflated, deflated, chunkSize); }
	stainli	::llc::error_t	arrayInflate			(const ::llc::vci8 & deflated, ::llc::au8 & inflated, const uint32_t chunkSize = ::llc::INFLATE_DEFAULT_CHUNK_SIZE) { return ::llc::arrayInflate(*(::llc::vcu8*)&deflated, inflated, chunkSize); }
	stainli	::llc::error_t	arrayDeflate			(const ::llc::vcu8 & inflated, ::llc::ai8 & deflated, const uint32_t chunkSize = ::llc::DEFLATE_DEFAULT_CHUNK_SIZE) { return ::llc::arrayDeflate(inflated, *(::llc::au8*)&deflated, chunkSize); }
	stainli	::llc::error_t	arrayInflate			(const ::llc::vcu8 & deflated, ::llc::ai8 & inflated, const uint32_t chunkSize = ::llc::INFLATE_DEFAULT_CHUNK_SIZE) { return ::llc::arrayInflate(deflated, *(::llc::au8*)&inflated, chunkSize); }
	stainli	::llc::error_t	arrayDeflate			(const ::llc::vci8 & inflated, ::llc::ai8 & deflated, const uint32_t chunkSize = ::llc::DEFLATE_DEFAULT_CHUNK_SIZE) { return ::llc::arrayDeflate(*(::llc::vcu8*)&inflated, *(::llc::au8*)&deflated, chunkSize); }
	stainli	::llc::error_t	arrayInflate			(const ::llc::vci8 & deflated, ::llc::ai8 & inflated, const uint32_t chunkSize = ::llc::INFLATE_DEFAULT_CHUNK_SIZE) { return ::llc::arrayInflate(*(::llc::vcu8*)&deflated, *(::llc::au8*)&inflated, chunkSize); }

	::llc::error_t			folderLoad					
		( const ::llc::vcs	nameFolderSrc 
		, ::llc::au8		& tableFiles				
		, ::llc::au8		& contentsPacked			
		);
	::llc::error_t			folderPack				(::llc::SFolderPackage	& out_packed, const ::llc::vcs nameFolderSrc);
	::llc::error_t			folderUnpack			(::llc::SFolderInMemory	& out_loaded, const ::llc::vcu8 & rawFileInMemory);
	::llc::error_t			folderUnpack			(::llc::SFolderInMemory	& out_loaded, const ::llc::vcs nameFileSrc);
	::llc::error_t			folderToDisk			(const ::llc::SFolderInMemory & virtualFolder, const ::llc::vcs destinationPath);
	::llc::error_t			folderToDisk			(const ::llc::SFolderPackage & folderPackage, const ::llc::vcs nameFileDst);
	::llc::error_t			folderPackToDisk		(const ::llc::vcs nameFileDst, const ::llc::vcs nameFolderSrc);
	::llc::error_t			folderUnpackToDisk		(const ::llc::vcs namePathDst, const ::llc::vcs nameFileSrc);

	::llc::error_t			crcGenerate				(const ::llc::vcu8 & bytes, uint64_t & crc);
	::llc::error_t			crcVerifyAndRemove		(::llc::au8 & bytes);
	::llc::error_t			crcGenerateAndAppend	(::llc::au8 & bytes);

	struct SLoadCache {
		::llc::au8				Deflated;
		::llc::au8				Encrypted;
	};

	::llc::error_t			inflateToMemory  	(::llc::au8 & tempCache, const ::llc::vcc & fileName, ::llc::au8 & output);
	::llc::error_t			deflateFromMemory	(::llc::au8 & tempCache, const ::llc::vcc & fileName, const ::llc::vcu8 & input);

	stainli	::llc::error_t	inflateToMemory			(const ::llc::vcc & fileName, ::llc::au8 & input)			{ ::llc::au8 temp; return ::llc::inflateToMemory  (temp, fileName, input); }
	stainli	::llc::error_t	deflateFromMemory		(const ::llc::vcc & fileName, const ::llc::vcu8 & input)	{ ::llc::au8 temp; return ::llc::deflateFromMemory(temp, fileName, input); }

	::llc::error_t			fileToMemorySecure		(::llc::SLoadCache & recycle, const ::llc::vcc & fileName, const ::llc::vcu8 & key, const bool deflate, ::llc::au8 & output);
	::llc::error_t			fileFromMemorySecure	(::llc::SLoadCache & recycle, const ::llc::vcc & fileName, const ::llc::vcu8 & key, const bool deflate, const ::llc::vcu8 & input);
	stainli	::llc::error_t	fileToMemorySecure		(::llc::SLoadCache & recycle, const ::llc::vcc & fileName, const ::llc::vcu8 & key, const bool deflate, ::llc::achar & output)		{ return ::llc::fileToMemorySecure  (recycle, fileName, key, deflate, *(::llc::au8*)&output); }

	stainli	::llc::error_t	fileToMemorySecure		(const ::llc::vcc & fileName, const ::llc::vcu8 & key, const bool deflate, ::llc::achar & output)		{ ::llc::SLoadCache temp; return ::llc::fileToMemorySecure  (temp, fileName, key, deflate, *(::llc::au8*)&output); }
	stainli	::llc::error_t	fileToMemorySecure		(const ::llc::vcc & fileName, const ::llc::vcu8 & key, const bool deflate, ::llc::au8 & output)			{ ::llc::SLoadCache temp; return ::llc::fileToMemorySecure  (temp, fileName, key, deflate, output); }
	stainli	::llc::error_t	fileFromMemorySecure	(const ::llc::vcc & fileName, const ::llc::vcu8 & key, const bool deflate, const ::llc::vcu8 & input)	{ ::llc::SLoadCache temp; return ::llc::fileFromMemorySecure(temp, fileName, key, deflate, input); }
} // namespace

#endif // LLC_DEFLATE_H_23627
