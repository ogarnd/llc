#include "llc_deflate.h"

#include "llc_path.h"

#include "llc_file.h"
#include "llc_safe.h"
#include "llc_cstdio.h"
#include "llc_aes.h"
#include "llc_noise.h"
#include "llc_apod_serialize.h"

#if defined(LLC_ESP32) || defined(LLC_ARDUINO)
#	ifdef LLC_ESP32
#	endif
#else
#	include "deflate.h"
#endif

#include "llc_range.h"

stacxpr	const uint32_t	LLC_CRC_CRC_SEED			= 18973;

::llc::error_t			llc::crcGenerate			(const ::llc::vcu8 & bytes, uint64_t & crc)	{
	crc						= 0;
	const uint32_t				lastPos						= bytes.size() - 1;
	for(uint32_t i=0; i < bytes.size(); ++i) {
		crc						+= ::llc::noise1DBase(bytes[i], ::LLC_CRC_CRC_SEED);
		crc						+= ::llc::noise1DBase(bytes[lastPos - i], ::LLC_CRC_CRC_SEED);
	}
	return 0;
}

::llc::error_t			llc::crcGenerateAndAppend	(::llc::au8 & bytes)	{
	uint64_t					crcToStore					= 0;
	::llc::crcGenerate(bytes, crcToStore);
	llc_necs(bytes.append((const uint8_t*)&crcToStore, sizeof(uint64_t)));;
	return 0;
}

::llc::error_t			llc::crcVerifyAndRemove		(::llc::au8 & bytes)	{
	ree_if(bytes.size() < 8, "Invalid input. No CRC can be found in an array of %u bytes.", bytes.size());
	uint64_t					check						= 0;
	const uint32_t				startOfCRC					= bytes.size() - 8;
	::llc::crcGenerate({bytes.begin(), startOfCRC}, check);
	const uint64_t				found						= *(uint64_t*)&bytes[startOfCRC];
	ree_if(check != found, "CRC Check failed: Stored: %llu. Calculated: %llu.", found, check);
	llc_necs(bytes.resize(bytes.size() - 8));
	return 0;
}

::llc::error_t			llc::arrayDeflate		(const ::llc::vcu8 & inflated, ::llc::au8 & deflated, const uint32_t chunkSize)	{
#if defined(LLC_ESP32) || defined(LLC_ARDUINO)
#	ifdef LLC_ESP32
	deflated				= inflated;
#	else
	deflated				= inflated;
#	endif
#else
	z_stream					strm					= {};
	int							ret						= deflateInit(&strm, Z_BEST_COMPRESSION);
	if (ret != Z_OK)
		return ret;

	strm.avail_in			= inflated.size();
	strm.next_in			= (Bytef*)inflated.begin();
	::llc::au8					block;
	llc_necs(block.resize(chunkSize));
	while(true) {
		strm.avail_out			= block.size();
		strm.next_out			= (Bytef*)block.begin();
		ret						= deflate(&strm, Z_FINISH);    // no bad return value
		bef_if(ret == Z_STREAM_ERROR, "Failed to compress: 0x%x.", ret);  // state not clobbered
		const uint32_t				deflatedSize			= (uint32_t)((uint8_t*)strm.next_out - block.begin());
		llc_necs(deflated.append(block.begin(), deflatedSize));
		if(ret == Z_STREAM_END)
			break;
	}
	int							ret_end					= deflateEnd(&strm);
	ef_if(strm.avail_in != 0, "%s", "Not all of the input bytes were consumed.");	// all input will be used
	ree_if(ret < 0, "%s", "Unknown error");												// stream will be complete
	ef_if(ret != Z_STREAM_END && ret != Z_OK, "%s", "Unknown error");				// stream will be complete
	ree_if(ret_end == Z_STREAM_ERROR, "deflateEnd() returned %s", "Z_STREAM_ERROR");
	info_printf("deflateEnd: %u.", (uint32_t)ret);
#endif
	return 0;
}

::llc::error_t			llc::arrayInflate		(const ::llc::vcu8 & deflated, ::llc::au8 & inflated, const uint32_t chunkSize)	{
#if defined(LLC_ESP32) || defined(LLC_ARDUINO)
#	ifdef LLC_ESP32
	inflated				= deflated;
#	else
	inflated				= deflated;
#	endif
#else
	z_stream					strm					= {};
	int							ret						= inflateInit(&strm);	 // allocate inflate state
	if (ret != Z_OK)
		return ret;

	strm.avail_in			= (uint32_t)deflated.size();
	strm.next_in			= (Bytef *)deflated.begin();
	::llc::au8					block;
	llc_necs(block.resize(chunkSize));
	while(true) {
		strm.avail_out			= (uint32_t)block.size();
		strm.next_out			= (Bytef *)block.begin();
		ret						= ::inflate(&strm, Z_NO_FLUSH);
		switch (ret) {
		case Z_NEED_DICT		:
			ret						= Z_DATA_ERROR;	// and fall through
		case Z_VERSION_ERROR	:
		case Z_STREAM_ERROR		:
		case Z_DATA_ERROR		:
		case Z_MEM_ERROR		:
			break;
		}
		ree_if(ret < 0, "Failed to decompress? inflate error: %i.", ret);
		const uint32_t				inflatedSize			= (uint32_t)((const uint8_t*)strm.next_out - block.begin());
		llc_necs(inflated.append(block.begin(), inflatedSize));
		if(ret == Z_STREAM_END)
			break;
	}
	ret						= inflateEnd(&strm);
	ree_if(ret != Z_STREAM_END && ret != Z_OK, "Failed to decompress? inflateEnd error: %i.", ret);
#endif
	return 0;
}

::llc::error_t			llc::folderUnpack			(::llc::SFolderInMemory & out_loaded, const ::llc::vcs nameFileSrc)					{
	::llc::au8					rawFileInMemory				= {};
	llc_necall(llc::fileToMemory(nameFileSrc, rawFileInMemory), "Failed to load pak file: %s.", nameFileSrc);
	llc_necall(llc::folderUnpack(out_loaded, rawFileInMemory), "Failed to unpack pak file: %s.", nameFileSrc);
	return 0;
}

::llc::error_t			llc::folderToDisk			(const ::llc::SFolderPackage & folderPackage, const ::llc::vcs nameFileDst)			{
	const ::llc::SPackHeader 	& fileHeader				= folderPackage.PackageInfo;
	const ::llc::au8			& compressedTableFiles		= folderPackage.CompressedTableFiles		;
	const ::llc::au8			& compressedContentsPacked	= folderPackage.CompressedContentsPacked	;
	{
		FILE						* fp						= 0;
		llc_necall(::llc::fopen_s(&fp, nameFileDst, "wb"), "'%s'", nameFileDst.begin());
		ree_if(0 == fp, "Failed to create file: %s.", ::llc::toString(nameFileDst).begin());
		fwrite(&fileHeader							, 1, sizeof(::llc::SPackHeader)			, fp);
		fwrite(compressedTableFiles		.begin	()	, 1, compressedTableFiles		.size()	, fp);
		fwrite(compressedContentsPacked	.begin	()	, 1, compressedContentsPacked	.size()	, fp);
		fclose(fp);
	}
	return 0;
}

stacxpr	uint32_t		DEFLATE_CHUNK_SIZE			= uint32_t(1024) * 1024 * 4;
::llc::error_t			llc::folderPack				(::llc::SFolderPackage & output, const ::llc::vcs nameFolderSrc) {
	::llc::SPackHeader 			& fileHeader			= output.PackageInfo = {};
	// -- The following two arrays store the file table and the file contents that are going to be compressed and stored on disk
	::llc::ac					finalPathName			= {};
	finalPathName.resize(1024*8);

	::llc::au8					tableFiles				;
	::llc::au8					contentsPacked			;

	llc_necs(llc::folderLoad(nameFolderSrc, tableFiles, contentsPacked));



	fileHeader.SizeUncompressedTableFiles		= tableFiles		.size();
	fileHeader.SizeUncompressedContentsPacked	= contentsPacked	.size();
	::llc::au8					& compressedTableFiles		= output.CompressedTableFiles		;
	::llc::au8					& compressedContentsPacked	= output.CompressedContentsPacked	;
	{	// compress
		llc_necall(llc::arrayDeflate(tableFiles		, compressedTableFiles		, ::DEFLATE_CHUNK_SIZE), "%s", "Unknown error.");
		llc_necall(llc::arrayDeflate(contentsPacked	, compressedContentsPacked	, ::DEFLATE_CHUNK_SIZE), "%s", "Unknown error.");
		fileHeader.SizeCompressedTableFiles		= compressedTableFiles		.size();
		fileHeader.SizeCompressedContentsPacked	= compressedContentsPacked	.size();
	}

	return 0;
}

stacxpr	uint32_t		INFLATE_CHUNK_SIZE			= uint32_t(1024) * 1024 * 4;
::llc::error_t			llc::folderUnpack			(::llc::SFolderInMemory & output, const ::llc::vcu8 & rawFileInMemory)		{
	const ::llc::SPackHeader	& header					= *(::llc::SPackHeader*)&rawFileInMemory[0];
	output.Names	.resize(header.TotalFileCount);
	output.Contents	.resize(header.TotalFileCount);
	output.DataInfo		.clear();
	output.DataContents	.clear();
	llc_necs(llc::arrayInflate({&rawFileInMemory[0] + sizeof(::llc::SPackHeader)									, header.SizeCompressedTableFiles		}, output.DataInfo	, ::INFLATE_CHUNK_SIZE));
	llc_necs(llc::arrayInflate({&rawFileInMemory[0] + sizeof(::llc::SPackHeader) + header.SizeCompressedTableFiles, header.SizeCompressedContentsPacked	}, output.DataContents	, ::INFLATE_CHUNK_SIZE));
	{ // Build access tables.
		uint32_t					offsetInfo					= 0;
		for(uint32_t iFile = 0; iFile < output.Names.size(); ++iFile) {
			const ::llc::rangeu2_t		& fileLocation				= *(const ::llc::rangeu2_t*)&output.DataInfo[offsetInfo];
			offsetInfo				+= sizeof(::llc::rangeu2_t);
			const uint32_t				lenName						= *(uint32_t*)&output.DataInfo[offsetInfo];
			offsetInfo				+= sizeof(uint32_t);
			output.Names[iFile]	= {(const char*)&output.DataInfo[offsetInfo], lenName};
			offsetInfo				+= lenName;
			output.Contents[iFile]	= {&output.DataContents	[fileLocation.Offset], fileLocation.Count};
		}
	}
	return 0;
}

::llc::error_t			llc::folderLoad			
	( const ::llc::vcs	nameFolderSrc 
	, ::llc::au8		& tableFiles				
	, ::llc::au8		& contentsPacked			
	) {
	// -- The following two arrays store the file table and the file contents that are going to be compressed and stored on disk
	uint32_t					totalFileCount			= 0;
	{
		::llc::aobj<::llc::ac>		listFiles				= {};
		llc_necall(llc::pathList(nameFolderSrc, listFiles), "Failed to list folder: %s.", nameFolderSrc.begin());

		::llc::au8					contentsTemp			= {};
		::llc::rangeu2_t			fileLocation			= {0, 0};
		for(uint32_t iFile = 0; iFile < listFiles.size(); ++iFile) {
			fileLocation.Offset		= contentsPacked.size();
			const ::llc::vcs			pathToLoad				= {listFiles[iFile].begin(), listFiles[iFile].size()};
			if(0 == pathToLoad.size())
				continue;

			info_printf("pathToLoad (%u): '%s'.", iFile, ::llc::toString(pathToLoad).begin());
			llc_necall(llc::fileToMemory(pathToLoad, contentsTemp), "Failed to load file: %s.", ::llc::toString(pathToLoad).begin());

			fileLocation.Count		= contentsTemp.size();
			llc_necs(llc::savePOD(tableFiles, fileLocation));
			llc_necs(llc::saveView(tableFiles, pathToLoad));
			llc_necall(contentsPacked.append(contentsTemp.begin(), contentsTemp.size())	, "Failed to append data bytes. Buffer sizes:\ntableFiles     : %u.\ncontentsPacked : %u.", tableFiles.size(), contentsPacked.size());
			contentsTemp.clear();

			++totalFileCount;
		}
	}
	return totalFileCount;
}

// Write folder to disk.
::llc::error_t			llc::folderToDisk			(const ::llc::SFolderInMemory & virtualFolder, ::llc::vcs destinationPath)				{
	char						bufferFormat	[32]		= {};
	::llc::ac					finalPathName				= {};
	finalPathName.resize(8 * 1024);
	finalPathName.fill(0);
	FILE						* fp						= 0;
	for(uint32_t iFile = 0, countFiles = virtualFolder.Names.size(); iFile < countFiles; ++iFile) {
		llc_safe_fclose(fp);
		const ::llc::vcs			& fileName					= virtualFolder.Names		[iFile];
		const ::llc::vcu8			& fileContent				= virtualFolder.Contents	[iFile];
		sprintf_s(bufferFormat, "%%.%us%%.%us", destinationPath.size(), fileName.size());
		snprintf(finalPathName.begin(), finalPathName.size(), bufferFormat, destinationPath.begin(), fileName.begin());
		info_printf("File found (%u):'%s'. Size: %u.", iFile, finalPathName.begin(), fileContent.size());
		uint32_t					lenPath						= (uint32_t)strlen(finalPathName.begin());
		::llc::error_t				indexSlash					= ::llc::findLastSlash(::llc::vcs{finalPathName.begin(), uint32_t(-1)});
		if(-1 != indexSlash) { // Create path if any specified.
			finalPathName[indexSlash]	= 0;
			lenPath						= (uint32_t)strlen(finalPathName.begin());
 			cef_if(errored(::llc::pathCreate({finalPathName.begin(), lenPath})), "Failed to create foder: %s.", finalPathName.begin());
			finalPathName[indexSlash]	= '/';
		}
		llc_necall(::llc::fopen_s(&fp, finalPathName, "wb"), "%s", finalPathName.begin());
		cef_if(0 == fp, "Failed to create file: %s.", finalPathName.begin());
		cef_if(fileContent.size() != fwrite(fileContent.begin(), 1, fileContent.size(), fp), "Failed to write file: %s. Disk full?", finalPathName.begin());
	}
	llc_safe_fclose(fp);
	return 0;
}

::llc::error_t			llc::folderPackToDisk		(const ::llc::vcs nameFileDst,	const ::llc::vcs nameFolderSrc)		{
	::llc::SFolderPackage		folderPackage;
	llc_necall(llc::folderPack(folderPackage, nameFolderSrc), "Failed to pack folder: %s.", nameFolderSrc.begin());
	llc_necall(llc::folderToDisk(folderPackage, nameFileDst), "Failed to pack folder: %s.", nameFolderSrc.begin());
	return 0;
}

::llc::error_t			llc::folderUnpackToDisk		(const ::llc::vcs namePathDst, const ::llc::vcs nameFileSrc)		{
	::llc::SFolderInMemory		virtualFolder				= {};
	llc_necall(llc::folderUnpack(virtualFolder, nameFileSrc), "Failed to unpack file: %s.", nameFileSrc);
	llc_necall(llc::folderToDisk(virtualFolder, namePathDst), "Failed to write folder to disk. Disk full or insufficient permissions. File name: %s. Destionation Path: %s.", nameFileSrc, namePathDst);
	return 0;
}

::llc::error_t			llc::inflateToMemory  		(::llc::au8 & tempCache, const ::llc::vcc & fileName, ::llc::au8 & output) {
	llc_necs(llc::fileToMemory(fileName, tempCache));
	info_printf("File size: %u.", tempCache.size());

	llc_necs(llc::arrayInflate(tempCache, output));
	info_printf("Inflated size: %u.", output.size());
	return 0; 
}

::llc::error_t			llc::deflateFromMemory		(::llc::au8 & tempCache, const ::llc::vcc & fileName, const ::llc::vcu8 & input) {
	info_printf("Input size: %u.", input.size());
	llc_necs(llc::arrayDeflate(input, tempCache));

	info_printf("Deflated size: %u.", tempCache.size());
	return ::llc::fileFromMemory(fileName, tempCache);
}

::llc::error_t			llc::fileFromMemorySecure	(::llc::SLoadCache & recycle, const ::llc::vcc & fileName, const ::llc::vcu8 & key, const bool deflate, const ::llc::vcu8 & blockBytes) {
	if(false == deflate && 0 == key.size())
		recycle.Encrypted		= blockBytes;
	else {
		if(false == deflate)
			llc_necall(llc::aesEncode(blockBytes, key, ::llc::AES_LEVEL_256, recycle.Encrypted), "Failed to encrypt file: %s.", ::llc::toString(fileName).begin());
		else if(0 == key.size())
			llc_necall(llc::arrayDeflate(blockBytes, recycle.Encrypted), "Failed to deflate file: %s.", ::llc::toString(fileName).begin());
		else {
			llc_necall(llc::arrayDeflate(blockBytes, recycle.Deflated), "Failed to deflate file: %s.", ::llc::toString(fileName).begin());
			llc_necall(llc::aesEncode(recycle.Deflated, key, ::llc::AES_LEVEL_256, recycle.Encrypted), "Failed to encrypt file: %s.", ::llc::toString(fileName).begin());
		}
	}
	llc_necall(llc::crcGenerateAndAppend(recycle.Encrypted), "%s", "CRC Check failed!");
	llc_necall(llc::fileFromMemory(fileName, recycle.Encrypted), "Failed to save file: %s.", ::llc::toString(fileName).begin());
	return 0;
}

::llc::error_t			llc::fileToMemorySecure		(::llc::SLoadCache & recycle, const ::llc::vcc & fileName, const ::llc::vcu8 & key, const bool deflate, ::llc::au8 & loadedBytes)								{
	::llc::vcs					strFilename					= {fileName.begin(), fileName.size()};
	if(false == deflate && 0 == key.size()) {
		llc_necall(llc::fileToMemory(strFilename, loadedBytes), "Failed to read file: %s.", ::llc::toString(fileName).begin());
		llc_necs(llc::crcVerifyAndRemove(loadedBytes));
	}
	else {
		llc_necall(llc::fileToMemory(strFilename, recycle.Encrypted), "Failed to read file: %s.", ::llc::toString(fileName).begin());
		llc_necall(llc::crcVerifyAndRemove(recycle.Encrypted), "%s", "CRC Check failed!");
		if(false == deflate)
			llc_necall(llc::aesDecode(recycle.Encrypted, key, ::llc::AES_LEVEL_256, loadedBytes), "Failed to decrypt file: %s.", ::llc::toString(fileName).begin());
		else if(0 == key.size())
			llc_necall(llc::arrayInflate(recycle.Encrypted, loadedBytes), "Failed to inflate file: %s.", ::llc::toString(fileName).begin());
		else {
			llc_necall(llc::aesDecode(recycle.Encrypted, key, ::llc::AES_LEVEL_256, recycle.Deflated), "Failed to decrypt file: %s.", ::llc::toString(fileName).begin());
			llc_necall(llc::arrayInflate(recycle.Deflated, loadedBytes), "Failed to inflate file: %s.", ::llc::toString(fileName).begin());
		}
	}
	return 0;
}
