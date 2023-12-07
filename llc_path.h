#include "llc_array.h"

#ifndef LLC_PATH_H_23627
#define LLC_PATH_H_23627

namespace llc
{
	struct SPathContents {
		::llc::aachar						Files					= {};
		::llc::aobj<::llc::SPathContents>	Folders					= {};
	};

	::llc::error_t						pathCreate				(const ::llc::vcc & folderName, const char separator = '/');	// Recursive
	::llc::error_t						pathList				(const ::llc::vcc & pathToList, ::llc::aachar & output, bool listFolders, const ::llc::vcc extension = {});		// Not recursive
	::llc::error_t						pathList				(const ::llc::SPathContents & input, ::llc::aachar & output, const ::llc::vcc extension = {});	// recursively walk over a pathcontents hierarchy and store all the file names into "output"
	::llc::error_t						pathList				(const ::llc::SPathContents & input, ::llc::avcc & output, const ::llc::vcc extension = {});	// recursively walk over a pathcontents hierarchy and store all the file names into "output"
	::llc::error_t						pathList				(const ::llc::vcc & pathToList, SPathContents & out_Contents, const ::llc::vcc extension = {});		// Recursive
	stainli	::llc::error_t				pathList				(const ::llc::vcc & pathToList, ::llc::aachar & output, const ::llc::vcc extension = {}) {
		::llc::SPathContents					tree					= {};
		int32_t									error					= ::llc::pathList(pathToList, tree, extension);
		llc_necs(error |= ::llc::pathList(tree, output, extension));
		return 0;
	}	// Recursive

	// this function was ceated in order to work around the problem of the JSON system returning pointers to the original string, without having the opportunity of processing escaped path slashes.
	//::llc::error_t						pathNameCompose			(::llc::achar & out_composed, ::llc::vcs fileName, ::llc::vcs path = {}, ::llc::vcs extension = {});
	::llc::error_t						pathNameCompose			(const ::llc::vcc & path, const ::llc::vcc & fileName, ::llc::achar & out_composed);
	::llc::error_t						findLastSlash			(const ::llc::vcc & path);

} // namespace

#endif // LLC_PATH_H_23627
