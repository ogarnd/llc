#include "llc_view.h"
#include "llc_view_serialize.h"

#ifndef LLC_LABEL_H_23627
#define LLC_LABEL_H_23627

namespace llc
{
	struct label_statics;

	class CLabelManager;
	class label : public vcc {
		CLabelManager		* LabelManager	= 0;
	public:
		inlcxpr				label			()								noexcept	= default;
							label			(const label & other)			noexcept	= default;
							label			(const char* str, uint32_t len)	noexcept;

		label&				operator=		(const label & other)			noexcept	= default;

		tplt<size_t _stringLength>
		inline 				label			(const char (&str)[_stringLength], uint32_t count = (uint32_t)-1)	noexcept	: label(&str[0], ::llc::min((uint32_t)_stringLength, count))	{}
		inline 				label			(const ::llc::vcs & other)											noexcept	: label(other.begin(), other.size())							{}

		inline	operator	::llc::vcs		()								const				{ return {Data, Count}; }

				bool		operator==		(const ::llc::vcs & other)		const	noexcept;
				bool		operator==		(const label & other)			const	noexcept;
		inline	bool		operator!=		(const label & other)			const	noexcept	{ return !operator==(other); }
	};

	stainli ::llc::error_t	loadLabel		(::llc::vcu8 & input, ::llc::vcc & output) { 
		uint32_t					bytesRead		= 0;
		llc_necs(bytesRead = ::llc::viewRead(output, input)); 
		llc_necs(input.slice(input, bytesRead));
		output					= ::llc::label(output);
		return bytesRead;
	}
}

#endif // LLC_LABEL_H_23627
