#include "llc_n2.h"

#ifndef LLC_RECT2_H
#define LLC_RECT2_H

namespace llc
{
#pragma pack(push, 1)
	tplt<tpnm T>
	struct rect2 {
		::llc::n2<T>			Offset, Size;

		LLC_DEFAULT_OPERATOR(rect2<T>, Offset	== other.Offset	&& Size == other.Size);

		tplt <tpnm _t>
		inlcxpr	rect2<_t>		Cast		()	const	noexcept	{ return {Offset.tplt Cast<_t>(), Size.tplt Cast<_t>()}; }

		inlcxpr	rect2<uint8_t>	u8			()	const	noexcept	{ return Cast<uint8_t	>(); }
		inlcxpr	rect2<uint16_t>	u16			()	const	noexcept	{ return Cast<uint16_t	>(); }
		inlcxpr	rect2<uint32_t>	u32			()	const	noexcept	{ return Cast<uint32_t	>(); }
		inlcxpr	rect2<uint64_t>	u64			()	const	noexcept	{ return Cast<uint64_t	>(); }
		inlcxpr	rect2<int8_t>	i8			()	const	noexcept	{ return Cast<int8_t	>(); }
		inlcxpr	rect2<int16_t>	i16			()	const	noexcept	{ return Cast<int16_t	>(); }
		inlcxpr	rect2<int32_t>	i32			()	const	noexcept	{ return Cast<int32_t	>(); }
		inlcxpr	rect2<int64_t>	i64			()	const	noexcept	{ return Cast<int64_t	>(); }
		inlcxpr	rect2<float>	f32			()	const	noexcept	{ return Cast<float		>(); }
		inlcxpr	rect2<double>	f64			()	const	noexcept	{ return Cast<double	>(); }

		inline	::llc::n2<T>	Limit		()	const	noexcept	{ return Offset + Size; }
	};
	typedef rect2<float>	rect2f32, rect2f;
	typedef rect2<double>	rect2f64, rect2d;
	typedef rect2<uint8_t>	rect2u8;
	typedef rect2<uint16_t>	rect2u16;
	typedef rect2<uint32_t>	rect2u32;
	typedef rect2<uint64_t>	rect2u64;
	typedef rect2<int8_t>	rect2i8;
	typedef rect2<int16_t>	rect2i16;
	typedef rect2<int32_t>	rect2i32;
	typedef rect2<int64_t>	rect2i64;
#pragma pack(pop)

	tplt<tpnm T>
	stacxpr	bool	in_range	(const ::llc::n2<T>& pointToTest, const ::llc::rect2<T>& area)	noexcept	{
		return	::llc::in_range(pointToTest.x, area.Offset.x, (T)(area.Offset.x + area.Size.x))
			&&	::llc::in_range(pointToTest.y, area.Offset.y, (T)(area.Offset.y + area.Size.y))
			;
	}
} // namespace

#endif // LLC_RECT2_H
