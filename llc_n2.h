#include "llc_math.h"

#include "llc_functional.h"

#ifndef LLC_N2_H_23627
#define LLC_N2_H_23627

namespace llc 
{
#pragma pack(push, 1)
	tpl_t struct n2 {
		tydf	_t			T;
		T					x, y;

		tydf	n2<T>		Tn2;

		stincxp	Tn2			from				(T value)					nxpt			{ return {value, value}; }

		//
		LLC_DEFAULT_OPERATOR(Tn2, x == other.x && y == other.y);

		cnstxpr	Tn2			operator+			(cnst Tn2 & other)		cnstnxpt	{ return {T(x + other.x), T(y + other.y)}; }
		cnstxpr	Tn2			operator-			(cnst Tn2 & other)		cnstnxpt	{ return {T(x - other.x), T(y - other.y)}; }
		cnstxpr	Tn2			operator*			(f3_t	scalar)			cnstnxpt	{ return {T(x * scalar), T(y * scalar)}; }
		cnstxpr	Tn2			operator/			(f3_t	scalar)			cnst				{ return {T(x / scalar), T(y / scalar)}; }
		cnstxpr	Tn2			operator*			(s3_t	scalar)			cnstnxpt	{ return {T(x * scalar), T(y * scalar)}; }
		cnstxpr	Tn2			operator/			(s3_t	scalar)			cnst				{ return {T(x / scalar), T(y / scalar)}; }
		cnstxpr	Tn2			operator*			(u3_t	scalar)			cnstnxpt	{ return {T(x * scalar), T(y * scalar)}; }
		cnstxpr	Tn2			operator/			(u3_t	scalar)			cnst				{ return {T(x / scalar), T(y / scalar)}; }
		cnstxpr	Tn2			operator*			(s2_t	scalar)			cnstnxpt	{ return {T(x * scalar), T(y * scalar)}; }
		cnstxpr	Tn2			operator/			(s2_t	scalar)			cnst				{ return {T(x / scalar), T(y / scalar)}; }
		cnstxpr	Tn2			operator*			(u2_t	scalar)			cnstnxpt	{ return {T(x * scalar), T(y * scalar)}; }
		cnstxpr	Tn2			operator/			(u2_t	scalar)			cnst				{ return {T(x / scalar), T(y / scalar)}; }
		//
		Tn2&				operator+=			(cnst Tn2 & other)			nxpt			{ x += other.x; y += other.y; return *this; }
		Tn2&				operator-=			(cnst Tn2 & other)			nxpt			{ x -= other.x; y -= other.y; return *this; }
		Tn2&				operator*=			(f3_t	scalar)				nxpt			{ x = T(x * scalar); y = T(y * scalar);	return *this; }
		Tn2&				operator/=			(f3_t	scalar)								{ x = T(x / scalar); y = T(y / scalar);	return *this; }
		Tn2&				operator*=			(s3_t	scalar)				nxpt			{ x = T(x * scalar); y = T(y * scalar);	return *this; }
		Tn2&				operator/=			(s3_t	scalar)								{ x = T(x / scalar); y = T(y / scalar);	return *this; }
		Tn2&				operator*=			(s2_t	scalar)				nxpt			{ x = T(x * scalar); y = T(y * scalar);	return *this; }
		Tn2&				operator/=			(s2_t	scalar)								{ x = T(x / scalar); y = T(y / scalar);	return *this; }
		Tn2&				operator*=			(u2_t	scalar)				nxpt			{ x = T(x * scalar); y = T(y * scalar);	return *this; }
		Tn2&				operator/=			(u2_t	scalar)								{ x = T(x / scalar); y = T(y / scalar);	return *this; }
		Tn2&				operator*=			(u3_t	scalar)				nxpt			{ x = T(x * scalar); y = T(y * scalar);	return *this; }
		Tn2&				operator/=			(u3_t	scalar)								{ x = T(x / scalar); y = T(y / scalar);	return *this; }

		cnstxpr	Tn2			operator-			()						cnstnxpt	{ return {x * -1, y * -1}; }

		//
		inlcxpr	Tn2			xx					()				cnstnxpt	{ return {x, x}; }
		inlcxpr	Tn2			xy					()				cnstnxpt	{ return {x, y}; }
		inlcxpr	Tn2			yx					()				cnstnxpt	{ return {y, x}; }
		inlcxpr	Tn2			yy					()				cnstnxpt	{ return {y, y}; }

		//
		tpl_t2
		inlcxpr	n2<_t2>		Cast				()				cnstnxpt	{ return {(_t2)x, (_t2)y}; }
		inlcxpr	n2<uc_t> 	uc					()				cnstnxpt	{ return Cast<uc_t>(); }
		inlcxpr	n2<sc_t> 	sc					()				cnstnxpt	{ return Cast<sc_t>(); }
		inlcxpr	n2<u0_t> 	u0					()				cnstnxpt	{ return Cast<u0_t>(); }
		inlcxpr	n2<u1_t> 	u1					()				cnstnxpt	{ return Cast<u1_t>(); }
		inlcxpr	n2<u2_t> 	u2					()				cnstnxpt	{ return Cast<u2_t>(); }
		inlcxpr	n2<u3_t> 	u3					()				cnstnxpt	{ return Cast<u3_t>(); }
		inlcxpr	n2<s0_t> 	s0					()				cnstnxpt	{ return Cast<s0_t>(); }
		inlcxpr	n2<s1_t> 	s1					()				cnstnxpt	{ return Cast<s1_t>(); }
		inlcxpr	n2<s2_t> 	s2					()				cnstnxpt	{ return Cast<s2_t>(); }
		inlcxpr	n2<s3_t> 	s3					()				cnstnxpt	{ return Cast<s3_t>(); }
		inlcxpr	n2<f2_t> 	f2					()				cnstnxpt	{ return Cast<f2_t>(); }
		inlcxpr	n2<f3_t> 	f3					()				cnstnxpt	{ return Cast<f3_t>(); }

		inline	Tn2&		Set					(T value)							nxpt	{ x = y = value; return *this; }
		inline	Tn2&		From				(T value)							nxpt	{ x = y = value; return *this; }

		int					SetAxis				(uint8_t axisIndex, T value)		nxpt	{
			switch(axisIndex) { 
			case 0: x = value; return 0; 
			case 1: y = value; return 1; 
			}
			return -1;
		}
		int					SetOther			(uint8_t axisExcluded, T value)		nxpt	{
			switch(axisExcluded) { 
			case 0: y = value; return 0;
			case 1: x = value; return 1;
			}
			return -1;
		}

		inlcxpr	uint32_t	Index				(uint32_t width) 						cnstnxpt	{ return y * width + x; }
		inlcxpr	T			Area				()										cnstnxpt	{ return x * y; }
		Tn2					Clamp				(cnst Tn2 & min, cnst Tn2 & max)		cnstnxpt	{ return {::llc::clamped(x, min.x, max.x), ::llc::clamped(y, min.y, max.y)}; }
		inlcxpr	Tn2			GetScaled			(f3_t	scalar)							cnstnxpt	{ return {(T)(x * scalar), (T)(y * scalar)}; }
		inlcxpr	Tn2			GetScaled			(f3_t scalarx, f3_t scalary)			cnstnxpt	{ return {(T)(x * scalarx), (T)(y * scalary)}; }
		inlcxpr	Tn2			GetScaled			(cnst Tn2 & scales)						cnstnxpt	{ return {(T)(x * scales.x), (T)(y * scales.y)}; }
		inline	Tn2			GetNormalized		()										cnstnxpt	{ cnst T sqLen = LengthSquared(); if(sqLen) { f3_c len = ::sqrt(sqLen); return {(T)(x / len), (T)(y / len)}; } else return {x, y};	}
		cnstxpr	f3_t		Dot					(cnst Tn2 & other)						cnstnxpt	{ return x * other.x + y * other.y; }
		cnstxpr	T			LengthSquared		()										cnstnxpt	{ return x * x + y * y; }
		cnstxpr	f3_t		Length				()										cnstnxpt	{ cnst T sqLen = LengthSquared(); return sqLen ? ::sqrt(sqLen) : 0; }
		cnstxpr	f3_t		AngleWith			(cnst Tn2 & other)						cnstnxpt	{ f3_t lengthsProduct = Length() * other.Length(); return lengthsProduct ? ::acos(Dot(other) / lengthsProduct) : 0; }
		void				AddScaled			(cnst Tn2 & vectorToScaleAndAdd, f2_t scale)	nxpt	{
			x					+= vectorToScaleAndAdd.x * scale;
			y					+= vectorToScaleAndAdd.y * scale;
		}
		Tn2&				Rotate				(f3_t theta)									nxpt	{
			cnst ::llc::SSinCos	pairSinCos			= ::llc::getSinCos(theta);
			f3_c			px					= x * pairSinCos.Cos - y * pairSinCos.Sin;
			y					= T(x * pairSinCos.Sin + y * pairSinCos.Cos);
			x					= (T)px;
			return *this;	
		}
		inline	Tn2&		InPlaceScale		(f3_t scalar)									nxpt	{ return *this *= scalar; }
		tpl_t2
		inline	Tn2&		InPlaceScale		(_t2 scalarx, _t2 scalary)						nxpt	{ return *this = {(T)(x * scalarx), (T)(y * scalary)}; }
		tpl_t2
		inline	Tn2&		InPlaceScale		(cnst n2<_t2>& other)							nxpt	{ return InPlaceScale(other.x, other.y); }
		inline	Tn2&		InPlaceNormalize	()															{ cnst T sqLen = LengthSquared(); return sqLen ? *this /= ::sqrt(sqLen) : *this; }
		inline	Tn2&		InPlaceClamp		(cnst Tn2 & min, cnst Tn2 & max)				nxpt	{
			x					= ::llc::clamped(x, min.x, max.x);
			y					= ::llc::clamped(y, min.y, max.y);
			return *this;
		}

		tydf	FVoid<Tn2&>				TFuncForEach;
		tydf	FVoid<uint32_t&, Tn2&>	TFuncEnumerate;

		T					for_each			(cnst TFuncForEach & funcForEach, T xStart = 0)			cnst	{
			Tn2						offset				= {};
			for(; offset.y < y; ++offset.y)
			for(offset.x = xStart; offset.x < x; ++offset.x) 
				funcForEach(offset);

			return T(offset.x * offset.y);
		}
		uint32_t			enumerate			(cnst TFuncEnumerate & funcForEach)	cnst {
			uint32_t				index				= 0;
			Tn2						offset				= {};
			for(; offset.y < y; ++offset.y)
			for(offset.x = 0; offset.x < x; ++offset.x, ++index) 
				funcForEach(index, offset);

			return index;
		}
		uint32_t			enumerate			(cnst TFuncEnumerate & funcForEachX, cnst TFuncEnumerate & funcForEachY)	cnst {
			uint32_t				index				= 0;
			Tn2						offset				= {};
			for(; offset.y < y; ++offset.y) {
				for(offset.x = 0; offset.x < x; ++offset.x, ++index) 
					funcForEachX(index, offset);
				
				funcForEachY(index, offset);
			}
			return index;
		}

	};	// struct n2
	tydf	n2<uc_t>	n2uc_t;	tydfcnst	n2uc_t	n2uc_c;
	tydf	n2<sc_t>	n2sc_t;	tydfcnst	n2sc_t	n2sc_c;
	tydf	n2<u0_t>	n2u0_t;	tydfcnst	n2u0_t	n2u0_c;
	tydf	n2<u1_t>	n2u1_t;	tydfcnst	n2u1_t	n2u1_c;
	tydf	n2<u2_t>	n2u2_t;	tydfcnst	n2u2_t	n2u2_c;
	tydf	n2<u3_t>	n2u3_t;	tydfcnst	n2u3_t	n2u3_c;
	tydf	n2<s0_t>	n2s0_t;	tydfcnst	n2s0_t	n2s0_c;
	tydf	n2<s1_t>	n2s1_t;	tydfcnst	n2s1_t	n2s1_c;
	tydf	n2<s2_t>	n2s2_t;	tydfcnst	n2s2_t	n2s2_c;
	tydf	n2<s3_t>	n2s3_t;	tydfcnst	n2s3_t	n2s3_c;
	tydf	n2<f2_t>	n2f2_t;	tydfcnst	n2f2_t	n2f2_c;
	tydf	n2<f3_t>	n2f3_t;	tydfcnst	n2f3_t	n2f3_c;

	tplT	stacxpr	bool	in_range	(cnst ::llc::n2<T> & valueToTest, cnst ::llc::n2<T> & rangeStart, cnst ::llc::n2<T> & rangeStop)	nxpt	{
		return	::llc::in_range(valueToTest.x, rangeStart.x, rangeStop.x)
			&&	::llc::in_range(valueToTest.y, rangeStart.y, rangeStop.y)
			;
	}
#pragma pack(pop)

#define LLC_USING_N2()					\
	using ::llc::n2uc_t, ::llc::n2uc_c	\
		, ::llc::n2sc_t, ::llc::n2sc_c	\
		, ::llc::n2u0_t, ::llc::n2u0_c	\
		, ::llc::n2u1_t, ::llc::n2u1_c	\
		, ::llc::n2u2_t, ::llc::n2u2_c	\
		, ::llc::n2u3_t, ::llc::n2u3_c	\
		, ::llc::n2s0_t, ::llc::n2s0_c	\
		, ::llc::n2s1_t, ::llc::n2s1_c	\
		, ::llc::n2s2_t, ::llc::n2s2_c	\
		, ::llc::n2s3_t, ::llc::n2s3_c	\
		, ::llc::n2f2_t, ::llc::n2f2_c	\
		, ::llc::n2f3_t, ::llc::n2f3_c
		
} // namespace

#define N2_F32	"%f, %f"
#define N2_F64	"%f, %f"
#define N2_I8	"%" LLC_FMT_I8 ", %" LLC_FMT_I8
#define N2_U8	"%" LLC_FMT_U8 ", %" LLC_FMT_U8
#define N2_I16	"%" LLC_FMT_I16 ", %" LLC_FMT_I16
#define N2_U16	"%" LLC_FMT_U16 ", %" LLC_FMT_U16
#define N2_I32	"%" LLC_FMT_I32 ", %" LLC_FMT_I32
#define N2_U32	"%" LLC_FMT_U32 ", %" LLC_FMT_U32
#define N2_I64	"%ll" LLC_FMT_I64 ", %ll" LLC_FMT_I64
#define N2_U64	"%ll" LLC_FMT_U64 ", %ll" LLC_FMT_U64

#define llc_xy(n2var) n2var.x, n2var.y

#endif // LLC_N2_H_23627
