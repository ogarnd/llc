#include "llc_array.h"

#ifndef LLC_PATH_H_23627
#define LLC_PATH_H_23627

namespace llc
{
	struct SPathContents {
		::llc::aachar						Files					= {};
		::llc::aobj<::llc::SPathContents>	Folders					= {};
	};

	::llc::error_t						pathCreate				(const ::llc::vcs & folderName, sc_c separator = '/');	// Recursive
	::llc::error_t						pathList				(const ::llc::vcs & pathToList, ::llc::aachar & output, bool listFolders, ::llc::vcs extension = {});		// Not recursive
	::llc::error_t						pathList				(const ::llc::SPathContents & input, ::llc::aasc_t & output	, ::llc::vcs extension = {});	// recursively walk over a pathcontents hierarchy and store all the file names into "output"
	::llc::error_t						pathList				(const ::llc::SPathContents & input, ::llc::avcc & output	, ::llc::vcs extension = {});	// recursively walk over a pathcontents hierarchy and store all the file names into "output"
	::llc::error_t						pathList				(const ::llc::vcs & pathToList, SPathContents & out_Contents, ::llc::vcs extension = {});		// Recursive
	stin	::llc::error_t				pathList				(const ::llc::vcs & pathToList, ::llc::aachar & output		, ::llc::vcs extension = {}) {
		::llc::SPathContents					tree					= {};
		int32_t									error					= ::llc::pathList(pathToList, tree, extension);
		llc_necs(error |= ::llc::pathList(tree, output, extension));
		return 0;
	}	// Recursive

	// this function was ceated in order to work around the problem of the JSON system returning pointers to the original string, without having the opportunity of processing escaped path slashes.
	//::llc::error_t						pathNameCompose			(::llc::asc_t & out_composed, ::llc::vcs fileName, ::llc::vcs path = {}, ::llc::vcs extension = {});
	::llc::error_t						pathNameCompose			(::llc::vcsc_c & path, ::llc::vcsc_c & fileName, ::llc::asc_t & out_composed);
	::llc::error_t						findLastSlash			(::llc::vcsc_c & path);

} // namespace

#endif // LLC_PATH_H_23627
