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
		SPackHeader 		PackageInfo						= {};
		au0_t				CompressedTableFiles			;
		au0_t				CompressedContentsPacked		;
	};

	struct SFolderInMemory {
		au0_t				DataContents					;
		au0_t				DataInfo						;
		avcu8			Contents						;
		avcc				Names							;
	};


#if defined(LLC_ESP32) || defined(LLC_ARDUINO)
	stxp	uint32_t		DEFLATE_DEFAULT_CHUNK_SIZE		= 1024 * 4;
	stxp	uint32_t		INFLATE_DEFAULT_CHUNK_SIZE		= 1024 * 4;
#else
	stxp	uint32_t		DEFLATE_DEFAULT_CHUNK_SIZE		= 1024 * 32;
	stxp	uint32_t		INFLATE_DEFAULT_CHUNK_SIZE		= 1024 * 32;
#endif	

	error_t			arrayDeflate			(const vcu0_t & inflated, au0_t & deflated, u2_c chunkSize = DEFLATE_DEFAULT_CHUNK_SIZE);
	error_t			arrayInflate			(const vcu0_t & deflated, au0_t & inflated, u2_c chunkSize = INFLATE_DEFAULT_CHUNK_SIZE);

	stin	error_t	arrayDeflate			(const vcs0_t & inflated, au0_t & deflated, u2_c chunkSize = DEFLATE_DEFAULT_CHUNK_SIZE) { return arrayDeflate(*(vcu0_t*)&inflated, deflated, chunkSize); }
	stin	error_t	arrayInflate			(const vcs0_t & deflated, au0_t & inflated, u2_c chunkSize = INFLATE_DEFAULT_CHUNK_SIZE) { return arrayInflate(*(vcu0_t*)&deflated, inflated, chunkSize); }
	stin	error_t	arrayDeflate			(const vcu0_t & inflated, as0_t & deflated, u2_c chunkSize = DEFLATE_DEFAULT_CHUNK_SIZE) { return arrayDeflate(inflated, *(au0_t*)&deflated, chunkSize); }
	stin	error_t	arrayInflate			(const vcu0_t & deflated, as0_t & inflated, u2_c chunkSize = INFLATE_DEFAULT_CHUNK_SIZE) { return arrayInflate(deflated, *(au0_t*)&inflated, chunkSize); }
	stin	error_t	arrayDeflate			(const vcs0_t & inflated, as0_t & deflated, u2_c chunkSize = DEFLATE_DEFAULT_CHUNK_SIZE) { return arrayDeflate(*(vcu0_t*)&inflated, *(au0_t*)&deflated, chunkSize); }
	stin	error_t	arrayInflate			(const vcs0_t & deflated, as0_t & inflated, u2_c chunkSize = INFLATE_DEFAULT_CHUNK_SIZE) { return arrayInflate(*(vcu0_t*)&deflated, *(au0_t*)&inflated, chunkSize); }

	error_t			folderLoad					
		( const vcs	nameFolderSrc 
		, au0_t		& tableFiles				
		, au0_t		& contentsPacked			
		);
	error_t			folderPack				(SFolderPackage	& out_packed, const vcs nameFolderSrc);
	error_t			folderUnpack			(SFolderInMemory	& out_loaded, const vcu0_t & rawFileInMemory);
	error_t			folderUnpack			(SFolderInMemory	& out_loaded, const vcs nameFileSrc);
	error_t			folderToDisk			(const SFolderInMemory & virtualFolder, const vcs destinationPath);
	error_t			folderToDisk			(const SFolderPackage & folderPackage, const vcs nameFileDst);
	error_t			folderPackToDisk		(const vcs nameFileDst, const vcs nameFolderSrc);
	error_t			folderUnpackToDisk		(const vcs namePathDst, const vcs nameFileSrc);

	error_t			crcGenerate				(const vcu0_t & bytes, uint64_t & crc);
	error_t			crcVerifyAndRemove		(au0_t & bytes);
	error_t			crcGenerateAndAppend	(au0_t & bytes);

	struct SLoadCache {
		au0_t				Deflated;
		au0_t				Encrypted;
	};

	error_t			inflateToMemory  	(au0_t & tempCache, vcsc_c & fileName, au0_t & output);
	error_t			deflateFromMemory	(au0_t & tempCache, vcsc_c & fileName, const vcu0_t & input);
	stin	error_t	inflateToMemory			(vcsc_c & fileName, au0_t & input)			{ au0_t temp; return inflateToMemory  (temp, fileName, input); }
	stin	error_t	deflateFromMemory		(vcsc_c & fileName, const vcu0_t & input)	{ au0_t temp; return deflateFromMemory(temp, fileName, input); }

	error_t			fileToMemorySecure		(SLoadCache & recycle, vcsc_c & fileName, const vcu0_t & key, const bool deflate, au0_t & output);
	error_t			fileFromMemorySecure	(SLoadCache & recycle, vcsc_c & fileName, const vcu0_t & key, const bool deflate, const vcu0_t & input);
	stin	error_t	fileToMemorySecure		(SLoadCache & recycle, vcsc_c & fileName, const vcu0_t & key, const bool deflate, asc_t & output)		{ return fileToMemorySecure  (recycle, fileName, key, deflate, *(au0_t*)&output); }

	stin	error_t	fileToMemorySecure		(vcsc_c & fileName, const vcu0_t & key, const bool deflate, asc_t & output)		{ SLoadCache temp; return fileToMemorySecure  (temp, fileName, key, deflate, *(au0_t*)&output); }
	stin	error_t	fileToMemorySecure		(vcsc_c & fileName, const vcu0_t & key, const bool deflate, au0_t & output)			{ SLoadCache temp; return fileToMemorySecure  (temp, fileName, key, deflate, output); }
	stin	error_t	fileFromMemorySecure	(vcsc_c & fileName, const vcu0_t & key, const bool deflate, const vcu0_t & input)	{ SLoadCache temp; return fileFromMemorySecure(temp, fileName, key, deflate, input); }
} // namespace

#endif // LLC_DEFLATE_H_23627
