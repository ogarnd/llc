#include "llc_n2.h"

#ifndef LLC_N3_H_23627
#define LLC_N3_H_23627

namespace llc 
{
#pragma pack(push, 1)	// You can read about pragma pack() here: https://www.google.com/search?q=pragma+pack
	tpl_t struct n3 {
		tydf	_t			T;
		T					x, y, z;

		tydf	n3<T>		Tn3;
		tydf	n2<T>		Tn2;

		sinx	Tn3			from				(T value)								nxpt	{ return {value, value, value}; }

		//
		LLC_DEFAULT_OPERATOR(Tn3, x == other.x && y == other.y && z == other.z);

		//
		cxpr	Tn3			oper+			(cnst Tn3 & other)					csnx	{ return {x + other.x, y + other.y, z + other.z}; }
		cxpr	Tn3			oper-			(cnst Tn3 & other)					csnx	{ return {x - other.x, y - other.y, z - other.z}; }
		cxpr	Tn3			oper*			(double scalar)						csnx	{ return {T(x * scalar), T(y * scalar), T(z * scalar)}; }
		cxpr	Tn3			oper/			(double scalar)						cnst		{ return {T(x / scalar), T(y / scalar), T(z / scalar)}; }
		cxpr	Tn3			oper*			(int64_t scalar)					csnx	{ return {T(x * scalar), T(y * scalar), T(z * scalar)}; }
		cxpr	Tn3			oper/			(int64_t scalar)					cnst		{ return {T(x / scalar), T(y / scalar), T(z / scalar)}; }
		cxpr	Tn3			oper*			(uint64_t scalar)					csnx	{ return {T(x * scalar), T(y * scalar), T(z * scalar)}; }
		cxpr	Tn3			oper/			(uint64_t scalar)					cnst		{ return {T(x / scalar), T(y / scalar), T(z / scalar)}; }
		cxpr	Tn3			oper*			(int32_t scalar)					csnx	{ return {T(x * scalar), T(y * scalar), T(z * scalar)}; }
		cxpr	Tn3			oper/			(int32_t scalar)					cnst		{ return {T(x / scalar), T(y / scalar), T(z / scalar)}; }
		cxpr	Tn3			oper*			(uint32_t scalar)					csnx	{ return {T(x * scalar), T(y * scalar), T(z * scalar)}; }
		cxpr	Tn3			oper/			(uint32_t scalar)					cnst		{ return {T(x / scalar), T(y / scalar), T(z / scalar)}; }
		//
		Tn3&				oper+=			(cnst Tn3 & other)						nxpt	{ x += other.x; y += other.y; z += other.z;	return *this; }
		Tn3&				oper-=			(cnst Tn3 & other)						nxpt	{ x -= other.x; y -= other.y; z -= other.z;	return *this; }
		Tn3&				oper*=			(double scalar)							nxpt	{ x = T(x * scalar); y = T(y * scalar); z = T(z * scalar); return *this; }
		Tn3&				oper/=			(double scalar)									{ x = T(x / scalar); y = T(y / scalar); z = T(z / scalar); return *this; }
		Tn3&				oper*=			(s3_t scalar)							nxpt	{ x = T(x * scalar); y = T(y * scalar); z = T(z * scalar); return *this; }
		Tn3&				oper/=			(s3_t scalar)									{ x = T(x / scalar); y = T(y / scalar); z = T(z / scalar); return *this; }
		Tn3&				oper*=			(s2_t scalar)							nxpt	{ x = T(x * scalar); y = T(y * scalar); z = T(z * scalar); return *this; }
		Tn3&				oper/=			(s2_t scalar)									{ x = T(x / scalar); y = T(y / scalar); z = T(z / scalar); return *this; }
		Tn3&				oper*=			(u2_t scalar)							nxpt	{ x = T(x * scalar); y = T(y * scalar); z = T(z * scalar); return *this; }
		Tn3&				oper/=			(u2_t scalar)									{ x = T(x / scalar); y = T(y / scalar); z = T(z / scalar); return *this; }
		Tn3&				oper*=			(u3_t scalar)							nxpt	{ x = T(x * scalar); y = T(y * scalar); z = T(z * scalar); return *this; }
		Tn3&				oper/=			(u3_t scalar)									{ x = T(x / scalar); y = T(y / scalar); z = T(z / scalar); return *this; }
		//
		cxpr	Tn3			oper-			()									csnx	{ return {T(x*-1), T(y*-1), T(z*-1)}; }
		//
		inxp	Tn2			xx					()									csnx	{ return {x, x}; }
		inxp	Tn2			xy					()									csnx	{ return {x, y}; }
		inxp	Tn2			xz					()									csnx	{ return {x, z}; }
		inxp	Tn2			yx					()									csnx	{ return {y, x}; }
		inxp	Tn2			yy					()									csnx	{ return {y, y}; }
		inxp	Tn2			yz					()									csnx	{ return {y, z}; }
		inxp	Tn2			zx					()									csnx	{ return {z, x}; }
		inxp	Tn2			zy					()									csnx	{ return {z, y}; }
		inxp	Tn2			zz					()									csnx	{ return {z, z}; }

		inxp	Tn3			xxx					()									csnx	{ return {x, x, x}; }
		inxp	Tn3			xxy					()									csnx	{ return {x, x, y}; }
		inxp	Tn3			xxz					()									csnx	{ return {x, x, z}; }
		inxp	Tn3			xyx					()									csnx	{ return {x, y, x}; }
		inxp	Tn3			xyy					()									csnx	{ return {x, y, y}; }
		inxp	Tn3			xyz					()									csnx	{ return {x, y, z}; }
		inxp	Tn3			xzx					()									csnx	{ return {x, z, x}; }
		inxp	Tn3			xzy					()									csnx	{ return {x, z, y}; }
		inxp	Tn3			xzz					()									csnx	{ return {x, z, z}; }

		inxp	Tn3			yxx					()									csnx	{ return {y, x, x}; }
		inxp	Tn3			yxy					()									csnx	{ return {y, x, y}; }
		inxp	Tn3			yxz					()									csnx	{ return {y, x, z}; }
		inxp	Tn3			yyx					()									csnx	{ return {y, y, x}; }
		inxp	Tn3			yyy					()									csnx	{ return {y, y, y}; }
		inxp	Tn3			yyz					()									csnx	{ return {y, y, z}; }
		inxp	Tn3			yzx					()									csnx	{ return {y, z, x}; }
		inxp	Tn3			yzy					()									csnx	{ return {y, z, y}; }
		inxp	Tn3			yzz					()									csnx	{ return {y, z, z}; }

		inxp	Tn3			zxx					()									csnx	{ return {z, x, x}; }
		inxp	Tn3			zxy					()									csnx	{ return {z, x, y}; }
		inxp	Tn3			zxz					()									csnx	{ return {z, x, z}; }
		inxp	Tn3			zyx					()									csnx	{ return {z, y, x}; }
		inxp	Tn3			zyy					()									csnx	{ return {z, y, y}; }
		inxp	Tn3			zyz					()									csnx	{ return {z, y, z}; }
		inxp	Tn3			zzx					()									csnx	{ return {z, z, x}; }
		inxp	Tn3			zzy					()									csnx	{ return {z, z, y}; }
		inxp	Tn3			zzz					()									csnx	{ return {z, z, z}; }

		tpl_t2
		inxp	n3<_t2>		Cast				()									csnx	{ return {(_t2)x, (_t2)y, (_t2)z}; }

		inxp	n3<u0_t>	u8					()									csnx	{ return Cast<u0_t>(); }
		inxp	n3<u1_t>	u16					()									csnx	{ return Cast<u1_t>(); }
		inxp	n3<u2_t>	u32					()									csnx	{ return Cast<u2_t>(); }
		inxp	n3<u3_t>	u64					()									csnx	{ return Cast<u3_t>(); }
		inxp	n3<s0_t>	i8					()									csnx	{ return Cast<s0_t>(); }
		inxp	n3<s1_t>	i16					()									csnx	{ return Cast<s1_t>(); }
		inxp	n3<s2_t>	i32					()									csnx	{ return Cast<s2_t>(); }
		inxp	n3<s3_t>	i64					()									csnx	{ return Cast<s3_t>(); }
		inxp	n3<f2_t>	f32					()									csnx	{ return Cast<f2_t>(); }
		inxp	n3<f3_t>	f64					()									csnx	{ return Cast<f3_t>(); }

		//
		inxp	Tn3&		Area				()									csnx	{ return x * y * z; }
		inxp	Tn3			Clamp				(cnst Tn3 & min, cnst Tn3 & max)	csnx	{ return {::llc::clamped(x, min.x, max.x), ::llc::clamped(y, min.y, max.y), ::llc::clamped(z, min.z, max.z)}; }
		inline	Tn3&		Set					(T value)								nxpt	{ x = y = z = value; return *this; }
		inline	Tn3&		From				(T value)								nxpt	{ x = y = z = value; return *this; }

		int					SetAxis				(uint32_t axisIndex, T value) {
			switch(axisIndex) { 
			case 0: x = value; return 0; 
			case 1: y = value; return 1; 
			case 2: z = value; return 2; 
			}
			return -1;
		}
		int					SetOthers			(uint32_t axisExcluded, T value) {
			switch(axisExcluded) { 
			case 0: y = z = value; break; 
			case 1: x = z = value; break; 
			case 2: x = y = value; break; 
			}
			return -1;
		}

		inline	Tn3&		Scale				(double scalar)								nxpt	{ return *this *= scalar; }
		inline	Tn3&		Scale				(cnst Tn3 & other)							nxpt	{ x *= other.x; y *= other.y; z *= other.z; return *this; }
		inxp	Tn3&		Normalize			()														{ cnst T sqLen = LengthSquared(); return sqLen ? *this /= ::sqrt(sqLen) : *this; }

		inline	Tn3			Scaled				(double scalar)						csnx	{ return Tn3{*this}.Scale(scalar); }
		inline	Tn3			Scaled				(cnst Tn3 & other)					csnx	{ return {x * other.x, y * other.y, z * other.z }; }
		inxp	Tn3			Normalized			()									cnst				{ cnst T sqLen = LengthSquared(); return sqLen ? *this / ::sqrt(sqLen) : *this; }

		cxpr	double		Dot					(cnst Tn3 & other)					csnx	{ return x * other.x + y * other.y + z * other.z; }
		cxpr	T			LengthSquared		()									csnx	{ return x * x + y * y + z * z; }
		cxpr	double		Length				()									cnst				{ cnst T sqLen = LengthSquared(); return sqLen ? ::sqrt(sqLen) : 0; }
		cxpr	double		AngleWith			(cnst Tn3 & other)					cnst				{ cnst double lengthsProduct = Length() * other.Length(); return lengthsProduct ? ::acos(Dot(other) / lengthsProduct) : 0; }
		void				AddScaled			(cnst Tn3 & toScaleAndAdd, double scale)	nxpt	{
			x					+= (T)(toScaleAndAdd.x * scale);
			y					+= (T)(toScaleAndAdd.y * scale);
			z					+= (T)(toScaleAndAdd.z * scale);
		}
		cxpr	Tn3			Reflect				(cnst Tn3 & direction)				csnx	{ return direction - *this * 2 * Dot(direction);	}
		cxpr	Tn3			Cross				(cnst Tn3 & right)					csnx	{ return {y * right.z - z * right.y, z * right.x - x * right.z, x * right.y - y * right.x };	}
				Tn3&		Cross				(cnst Tn3 & vector1, cnst Tn3 & vector2)	nxpt	{
			x					= vector1.y * vector2.z - vector1.z * vector2.y;
			y					= vector1.z * vector2.x - vector1.x * vector2.z;
			z					= vector1.x * vector2.y - vector1.y * vector2.x;
			return *this;
		}
		Tn3&				CrossAndNormalize	(cnst Tn3 & in_vLeft, cnst Tn3 & in_vRight)			{
			x					= in_vLeft.y * in_vRight.z - in_vLeft.z * in_vRight.y;
			y					= in_vLeft.z * in_vRight.x - in_vLeft.x * in_vRight.z;
			z					= in_vLeft.x * in_vRight.y - in_vLeft.y * in_vRight.x;
			Normalize();
			return *this;
		};

		// TODO: Likely Y and Z are inverted. Please fix.
		Tn3&				RotateX				(double theta)											{
			cnst ::llc::SSinCos	pairSinCos			= ::llc::getSinCos(theta);
			cnst double			pz					= y * pairSinCos.Cos - z * pairSinCos.Sin;
			y					= (T)(y * pairSinCos.Sin + z * pairSinCos.Cos);
			z					= (T)pz;
			return *this;
		}

		Tn3&				RotateY				(double theta)											{
			cnst ::llc::SSinCos	pairSinCos			= ::llc::getSinCos(theta);
			cnst double			px					= x * pairSinCos.Cos - z * pairSinCos.Sin;
			z					= (T)(x * pairSinCos.Sin + z * pairSinCos.Cos);
			x					= (T)px;
			return *this;
		}

		Tn3&				RotateZ				(double theta)											{
			cnst ::llc::SSinCos	pairSinCos			= ::llc::getSinCos(theta);
			cnst double			px					= x * pairSinCos.Cos - y * pairSinCos.Sin;
			y					= (T)(x * pairSinCos.Sin + y * pairSinCos.Cos);
			x					= (T)px;
			return *this;
		}
	};	// struct n3
	tydf	n3<uc_t>	n3uc_t;	tdcs	n3uc_t	n3uc_c;
	tydf	n3<sc_t>	n3sc_t;	tdcs	n3sc_t	n3sc_c;
	tydf	n3<u0_t>	n3u0_t;	tdcs	n3u0_t	n3u0_c;
	tydf	n3<u1_t>	n3u1_t;	tdcs	n3u1_t	n3u1_c;
	tydf	n3<u2_t>	n3u2_t;	tdcs	n3u2_t	n3u2_c;
	tydf	n3<u3_t>	n3u3_t;	tdcs	n3u3_t	n3u3_c;
	tydf	n3<s0_t>	n3s0_t;	tdcs	n3s0_t	n3s0_c;
	tydf	n3<s1_t>	n3s1_t;	tdcs	n3s1_t	n3s1_c;
	tydf	n3<s2_t>	n3s2_t;	tdcs	n3s2_t	n3s2_c;
	tydf	n3<s3_t>	n3s3_t;	tdcs	n3s3_t	n3s3_c;
	tydf	n3<f2_t>	n3f2_t;	tdcs	n3f2_t	n3f2_c;
	tydf	n3<f3_t>	n3f3_t;	tdcs	n3f3_t	n3f3_c;
#pragma pack(pop)	// You can read about pragma pack() here: https://www.google.com/search?q=pragma+pack


#define LLC_USING_N3()					\
	using ::llc::n3uc_t, ::llc::n3uc_c	\
		, ::llc::n3sc_t, ::llc::n3sc_c	\
		, ::llc::n3u0_t, ::llc::n3u0_c	\
		, ::llc::n3u1_t, ::llc::n3u1_c	\
		, ::llc::n3u2_t, ::llc::n3u2_c	\
		, ::llc::n3u3_t, ::llc::n3u3_c	\
		, ::llc::n3s0_t, ::llc::n3s0_c	\
		, ::llc::n3s1_t, ::llc::n3s1_c	\
		, ::llc::n3s2_t, ::llc::n3s2_c	\
		, ::llc::n3s3_t, ::llc::n3s3_c	\
		, ::llc::n3f2_t, ::llc::n3f2_c	\
		, ::llc::n3f3_t, ::llc::n3f3_c
		} // namespace

#define N3_F2 "{%f, %f, %f}"
#define N3_F3 "{%g, %g, %g}"
#define N3_S2 "{%" LLC_FMT_S2 ", %" LLC_FMT_S2 ", %" LLC_FMT_S2 "}"
#define N3_U2 "{%" LLC_FMT_U2 ", %" LLC_FMT_U2 ", %" LLC_FMT_U2 "}"
#define N3_S3 "{%lli, %lli, %lli}"
#define N3_U3 "{%llu, %llu, %llu}"

#define llc_xyz(n3var) n3var.x, n3var.y, n3var.z

#endif // LLC_N3_H_23627
