#include "llc_enum.h"
#include "llc_array_ptr.h"
#include "llc_slice.h"

#ifndef LLC_JSON_H_23627
#define LLC_JSON_H_23627

namespace llc
{
#pragma pack(push, 1)
	GDEFINE_ENUM_TYPE(JSON_TYPE, int32_t);
	GDEFINE_ENUM_VALUE(JSON_TYPE, NULL		,  0);
	GDEFINE_ENUM_VALUE(JSON_TYPE, INTEGER	,  1);
	GDEFINE_ENUM_VALUE(JSON_TYPE, DECIMAL	,  2);
	GDEFINE_ENUM_VALUE(JSON_TYPE, BOOLEAN	,  3);
	GDEFINE_ENUM_VALUE(JSON_TYPE, STRING	,  4);
	GDEFINE_ENUM_VALUE(JSON_TYPE, KEY		,  5);
	GDEFINE_ENUM_VALUE(JSON_TYPE, VALUE		,  6);
	GDEFINE_ENUM_VALUE(JSON_TYPE, OBJECT	,  7);
	GDEFINE_ENUM_VALUE(JSON_TYPE, ARRAY		,  8);
	GDEFINE_ENUM_VALUE(JSON_TYPE, CODEPOINT	,  9);
	GDEFINE_ENUM_VALUE(JSON_TYPE, COUNT		, 10);
	GDEFINE_ENUM_VALUE(JSON_TYPE, UNKNOWN	, -1);

	struct SJSONToken {
		int32_t					ParentIndex;
		JSON_TYPE				Type;
		::llc::sliceu32			Span;
		uint64_t				Value;
	};

	struct SJSONNode {
		SJSONToken				* Token					= 0;
		SJSONNode				* Parent				= 0;
		::llc::apobj<SJSONNode>	Children				= {};
		int32_t					ObjectIndex				= -1;
	};

	struct SJSONReaderState {
		uint32_t				IndexCurrentChar		= 0;
		int32_t					IndexCurrentElement		= -1;
		::llc::SJSONToken		* CurrentElement		= 0;
		int32_t					NestLevel				= 0;
		char					CharCurrent				= 0;
		bool					Escaping				: 1;
		bool					InsideString			: 1;
		bool					ExpectingSeparator		: 1;
		bool					DoneReading				: 1;

								SJSONReaderState		()
		: Escaping			(false)
		, InsideString		(false)
		, ExpectingSeparator(false)
		, DoneReading		(false)
		{}
	};
#pragma pack(pop)

	struct SJSONReader {
		::llc::apod<::llc::SJSONToken>	Token;
		::llc::avcc						View;
		::llc::apobj<::llc::SJSONNode>	Tree;
		::llc::SJSONReaderState			StateRead;

		::llc::error_t					Reset					()							{
			Token	.clear();
			View	.clear();
			StateRead						= {};
			return 0;
		}

		const ::llc::pobj<::llc::SJSONNode>&	operator[]				(uint32_t index)	const	{ return Tree[index]; }
	};

	// Reader functions: Populate a SJSONReader structure from an input JSON string.
	::llc::error_t			jsonParse				(::llc::SJSONReader & reader, const ::llc::vcc & jsonAsString);
	::llc::error_t			jsonParseStep			(::llc::SJSONReader & reader, const ::llc::vcc & jsonAsString);
	::llc::error_t			jsonTreeRebuild			(::llc::view<::llc::SJSONToken> & in_object, ::llc::apobj<::llc::SJSONNode> & out_nodes);

	stincxp	::llc::error_t	jsonObjectKeyCount		(const ::llc::SJSONNode & node)		noexcept	{ return node.Children.size() / 2; }
	stincxp	::llc::error_t	jsonArraySize			(const ::llc::SJSONNode & node)		noexcept	{ return node.Children.size(); }	// returns the index of the JSON element corresponding to the index provided as parameter.
	::llc::error_t			jsonArrayValueGet		(const ::llc::SJSONNode & node, uint32_t index);	// returns the index of the JSON element corresponding to the index provided as parameter.
	::llc::error_t			jsonObjectValueGet		(const ::llc::SJSONNode & node, const ::llc::view<::llc::vcc> & views, const ::llc::vcs & key);
	::llc::error_t			jsonObjectKeyList		(const ::llc::SJSONNode & node, ::llc::ai32 & indices);
	::llc::error_t			jsonObjectKeyList		(const ::llc::SJSONNode & node, const ::llc::view<::llc::vcc> & views, ::llc::avcc & keys);
	::llc::error_t			jsonObjectKeyList		(const ::llc::SJSONNode & node, const ::llc::view<::llc::vcc> & views, ::llc::ai32 & indices, ::llc::avcc & keys);
	::llc::error_t			jsonCompareNumber		(const ::llc::SJSONNode & node, const ::llc::view<::llc::vcc> & views, const ::llc::SJSONNode & other, const ::llc::view<::llc::vcc> & otherViews);
	::llc::error_t			jsonCompareArray		(const ::llc::SJSONNode & node, const ::llc::view<::llc::vcc> & views, const ::llc::SJSONNode & other, const ::llc::view<::llc::vcc> & otherViews);
	::llc::error_t			jsonCompareObject		(const ::llc::SJSONNode & node, const ::llc::view<::llc::vcc> & views, const ::llc::SJSONNode & other, const ::llc::view<::llc::vcc> & otherViews);


	// Access functions: Iterate over children looking for keys or values.
	ndstain	::llc::error_t	jsonObjectKeyCount	(const ::llc::SJSONReader & reader, uint32_t iNode)												{ rew_if(iNode >= reader.Tree.size(), "Invalid node index: %" LLC_FMT_I32 ". Total nodes: %" LLC_FMT_U32 "", iNode, reader.Tree.size()); rees_if(!reader.Tree[iNode]); return jsonObjectKeyCount(*reader.Tree[iNode]); }
	ndstain	::llc::error_t	jsonArraySize		(const ::llc::SJSONReader & reader, uint32_t iNode)												{ rew_if(iNode >= reader.Tree.size(), "Invalid node index: %" LLC_FMT_I32 ". Total nodes: %" LLC_FMT_U32 "", iNode, reader.Tree.size()); rees_if(!reader.Tree[iNode]); return jsonArraySize(*reader.Tree[iNode]); }
	ndstain	::llc::error_t	jsonArrayValueGet	(const ::llc::SJSONReader & reader, uint32_t iNode, uint32_t indexOfValueToGet)					{ rew_if(iNode >= reader.Tree.size(), "Invalid node index: %" LLC_FMT_I32 ". Total nodes: %" LLC_FMT_U32 "", iNode, reader.Tree.size()); rees_if(!reader.Tree[iNode]); return jsonArrayValueGet(*reader.Tree[iNode], indexOfValueToGet); }
	ndstain	::llc::error_t	jsonObjectValueGet	(const ::llc::SJSONReader & reader, uint32_t iNode, const ::llc::vcs & key)						{ rew_if(iNode >= reader.Tree.size(), "Invalid node index: %" LLC_FMT_I32 ". Total nodes: %" LLC_FMT_U32 "", iNode, reader.Tree.size()); rees_if(!reader.Tree[iNode]); return jsonObjectValueGet(*reader.Tree[iNode], reader.View, {key.begin(), key.size()}); }
	stainli	::llc::error_t	jsonObjectKeyList	(const ::llc::SJSONReader & reader, uint32_t iNode, ::llc::ai32 & indices)						{ rew_if(iNode >= reader.Tree.size(), "Invalid node index: %" LLC_FMT_I32 ". Total nodes: %" LLC_FMT_U32 "", iNode, reader.Tree.size()); rees_if(!reader.Tree[iNode]); return jsonObjectKeyList(*reader.Tree[iNode], indices); }
	stainli	::llc::error_t	jsonObjectKeyList	(const ::llc::SJSONReader & reader, uint32_t iNode, ::llc::avcc & keys)							{ rew_if(iNode >= reader.Tree.size(), "Invalid node index: %" LLC_FMT_I32 ". Total nodes: %" LLC_FMT_U32 "", iNode, reader.Tree.size()); rees_if(!reader.Tree[iNode]); return jsonObjectKeyList(*reader.Tree[iNode], reader.View, keys); }
	stainli	::llc::error_t	jsonObjectKeyList	(const ::llc::SJSONReader & reader, uint32_t iNode, ::llc::ai32 & indices, ::llc::avcc & keys)	{ rew_if(iNode >= reader.Tree.size(), "Invalid node index: %" LLC_FMT_I32 ". Total nodes: %" LLC_FMT_U32 "", iNode, reader.Tree.size()); rees_if(!reader.Tree[iNode]); return jsonObjectKeyList(*reader.Tree[iNode], reader.View, indices, keys); }
	ndstain	::llc::error_t	jsonCompareArray	(const ::llc::SJSONNode & node, const ::llc::SJSONNode & other, const ::llc::view<::llc::vcc> & views)	{ return ::llc::jsonCompareArray	(node, views, other, views); }
	ndstain	::llc::error_t	jsonCompareObject	(const ::llc::SJSONNode & node, const ::llc::SJSONNode & other, const ::llc::view<::llc::vcc> & views)	{ return ::llc::jsonCompareObject	(node, views, other, views); }
	ndstain	::llc::error_t	jsonCompareNumber	(const ::llc::SJSONNode & node, const ::llc::SJSONNode & other, const ::llc::view<::llc::vcc> & views)	{ return ::llc::jsonCompareNumber	(node, views, other, views); }

	::llc::error_t	jsonObjectGetString (const ::llc::SJSONReader & reader, uint32_t iNode, vcc		& value);
	::llc::error_t	jsonObjectGetBoolean(const ::llc::SJSONReader & reader, uint32_t iNode, bool	& value);
	::llc::error_t	jsonObjectGetInteger(const ::llc::SJSONReader & reader, uint32_t iNode, i64_t	& value);
	::llc::error_t	jsonObjectGetInteger(const ::llc::SJSONReader & reader, uint32_t iNode, i32_t	& value);
	::llc::error_t	jsonObjectGetInteger(const ::llc::SJSONReader & reader, uint32_t iNode, i16_t	& value);
	::llc::error_t	jsonObjectGetInteger(const ::llc::SJSONReader & reader, uint32_t iNode, i8_t	& value);
	::llc::error_t	jsonObjectGetInteger(const ::llc::SJSONReader & reader, uint32_t iNode, u64_t	& value);
	::llc::error_t	jsonObjectGetInteger(const ::llc::SJSONReader & reader, uint32_t iNode, u32_t	& value);
	::llc::error_t	jsonObjectGetInteger(const ::llc::SJSONReader & reader, uint32_t iNode, u16_t	& value);
	::llc::error_t	jsonObjectGetInteger(const ::llc::SJSONReader & reader, uint32_t iNode, u8_t	& value);
	::llc::error_t	jsonObjectGetDecimal(const ::llc::SJSONReader & reader, uint32_t iNode, double	& value);
	::llc::error_t	jsonObjectGetDecimal(const ::llc::SJSONReader & reader, uint32_t iNode, float	& value);

	// TODO: Finish
	//::llc::error_t	jsonObjectGetIntegerAsString (const ::llc::SJSONReader & reader, uint32_t iNode, vcc	& value);
	::llc::error_t	jsonObjectGetIntegerAsBoolean(const ::llc::SJSONReader & reader, uint32_t iNode, bool	& value);
	::llc::error_t	jsonObjectGetIntegerAsDecimal(const ::llc::SJSONReader & reader, uint32_t iNode, double	& value);
	::llc::error_t	jsonObjectGetDecimalAsInteger(const ::llc::SJSONReader & reader, uint32_t iNode, i64_t	& value);
	//::llc::error_t	jsonObjectGetDecimalAsString (const ::llc::SJSONReader & reader, uint32_t iNode, vcc	& value);
	::llc::error_t	jsonObjectGetDecimalAsBoolean(const ::llc::SJSONReader & reader, uint32_t iNode, bool	& value);
	//::llc::error_t	jsonObjectGetStringAsInteger (const ::llc::SJSONReader & reader, uint32_t iNode, i64_t	& value);
	//::llc::error_t	jsonObjectGetStringAsBoolean (const ::llc::SJSONReader & reader, uint32_t iNode, bool	& value);
	//::llc::error_t	jsonObjectGetStringAsDecimal (const ::llc::SJSONReader & reader, uint32_t iNode, double	& value);
	::llc::error_t	jsonObjectGetBooleanAsInteger(const ::llc::SJSONReader & reader, uint32_t iNode, i64_t	& value);
	//::llc::error_t	jsonObjectGetBooleanAsString (const ::llc::SJSONReader & reader, uint32_t iNode, vcc	& value);
	::llc::error_t	jsonObjectGetBooleanAsDecimal(const ::llc::SJSONReader & reader, uint32_t iNode, double	& value);
	// 
	//::llc::error_t	jsonObjectGetAsString	(const ::llc::SJSONReader & reader, uint32_t iNode, vcc		& value);
	//::llc::error_t	jsonObjectGetAsBoolean	(const ::llc::SJSONReader & reader, uint32_t iNode, bool	& value);
	//::llc::error_t	jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, uint32_t iNode, i64_t	& value);
	//::llc::error_t	jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, uint32_t iNode, i32_t	& value);
	//::llc::error_t	jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, uint32_t iNode, i16_t	& value);
	//::llc::error_t	jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, uint32_t iNode, i8_t	& value);
	//::llc::error_t	jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, uint32_t iNode, u64_t	& value);
	//::llc::error_t	jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, uint32_t iNode, u32_t	& value);
	//::llc::error_t	jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, uint32_t iNode, u16_t	& value);
	//::llc::error_t	jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, uint32_t iNode, u8_t	& value);
	//::llc::error_t	jsonObjectGetAsDecimal	(const ::llc::SJSONReader & reader, uint32_t iNode, double	& value);
	//::llc::error_t	jsonObjectGetAsDecimal	(const ::llc::SJSONReader & reader, uint32_t iNode, float	& value);

	::llc::error_t	jsonObjectGetAsString	(const ::llc::SJSONReader & reader, uint32_t iNode, const ::llc::vcs & key, vcc		& value);
	::llc::error_t	jsonObjectGetAsBoolean	(const ::llc::SJSONReader & reader, uint32_t iNode, const ::llc::vcs & key, bool	& value);
	::llc::error_t	jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, uint32_t iNode, const ::llc::vcs & key, i64_t	& value);
	::llc::error_t	jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, uint32_t iNode, const ::llc::vcs & key, i32_t	& value);
	::llc::error_t	jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, uint32_t iNode, const ::llc::vcs & key, i16_t	& value);
	::llc::error_t	jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, uint32_t iNode, const ::llc::vcs & key, i8_t	& value);
	::llc::error_t	jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, uint32_t iNode, const ::llc::vcs & key, u64_t	& value);
	::llc::error_t	jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, uint32_t iNode, const ::llc::vcs & key, u32_t	& value);
	::llc::error_t	jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, uint32_t iNode, const ::llc::vcs & key, u16_t	& value);
	::llc::error_t	jsonObjectGetAsInteger	(const ::llc::SJSONReader & reader, uint32_t iNode, const ::llc::vcs & key, u8_t	& value);
	::llc::error_t	jsonObjectGetAsDecimal	(const ::llc::SJSONReader & reader, uint32_t iNode, const ::llc::vcs & key, double	& value);
	::llc::error_t	jsonObjectGetAsDecimal	(const ::llc::SJSONReader & reader, uint32_t iNode, const ::llc::vcs & key, float	& value);

	struct SJSONFile {
		::llc::achar			Bytes					= {};
		::llc::SJSONReader		Reader					= {};
	};

	typedef ::llc::SKeyVal<::llc::vcc, ::llc::SJSONFile>	TKeyValJSONFile;

	::llc::error_t			jsonFileRead			(::llc::SJSONFile & file, const ::llc::vcc & filename);
	::llc::error_t			jsonWrite				(const ::llc::SJSONNode * node, const ::llc::view<::llc::vcc> & jsonViews, ::llc::apod<char> & output);
	::llc::error_t			jsonArraySplit			(const ::llc::SJSONNode & jsonArrayToSplit, const ::llc::view<::llc::vcc> & jsonViews, const uint32_t blockSize, ::llc::aobj<::llc::apod<char>> & outputJsons);

	struct SJSONFieldBinding {
		::llc::vcc				Field					= {};
		::llc::JSON_TYPE		Type					= {};
	};

	::llc::error_t			jsonMapToFields			(::llc::ai32 & indicesOfFields, const ::llc::view<const ::llc::SJSONFieldBinding> fields, const ::llc::view<const ::llc::TKeyValConstChar> fieldMaps);
	::llc::error_t			jsonFieldsToMap			(::llc::ai32 & indicesOfFields, const ::llc::view<const ::llc::SJSONFieldBinding> fields, const ::llc::view<const ::llc::TKeyValConstChar> fieldMaps);
} // namespace

#endif // LLC_JSON_H_23627
