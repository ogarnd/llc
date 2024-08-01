#include "llc_n2.h"

#ifndef LLC_N3_H_23627
#define LLC_N3_H_23627

namespace llc 
{
#pragma pack(push, 1)	// You can read about pragma pack() here: https://www.google.com/search?q=pragma+pack
	tpl_t struct n3 {
		typedef	_t			T;
		T					x, y, z;

		typedef	n3<T>		Tn3;
		typedef	n2<T>		Tn2;

		stincxp	Tn3			from				(T value)								nxpt	{ return {value, value, value}; }

		//
		LLC_DEFAULT_OPERATOR(Tn3, x == other.x && y == other.y && z == other.z);

		//
		cnstxpr	Tn3			operator+			(cnst Tn3 & other)					cnstnxpt	{ return {x + other.x, y + other.y, z + other.z}; }
		cnstxpr	Tn3			operator-			(cnst Tn3 & other)					cnstnxpt	{ return {x - other.x, y - other.y, z - other.z}; }
		cnstxpr	Tn3			operator*			(double scalar)						cnstnxpt	{ return {T(x * scalar), T(y * scalar), T(z * scalar)}; }
		cnstxpr	Tn3			operator/			(double scalar)						cnst		{ return {T(x / scalar), T(y / scalar), T(z / scalar)}; }
		cnstxpr	Tn3			operator*			(int64_t scalar)					cnstnxpt	{ return {T(x * scalar), T(y * scalar), T(z * scalar)}; }
		cnstxpr	Tn3			operator/			(int64_t scalar)					cnst		{ return {T(x / scalar), T(y / scalar), T(z / scalar)}; }
		cnstxpr	Tn3			operator*			(uint64_t scalar)					cnstnxpt	{ return {T(x * scalar), T(y * scalar), T(z * scalar)}; }
		cnstxpr	Tn3			operator/			(uint64_t scalar)					cnst		{ return {T(x / scalar), T(y / scalar), T(z / scalar)}; }
		cnstxpr	Tn3			operator*			(int32_t scalar)					cnstnxpt	{ return {T(x * scalar), T(y * scalar), T(z * scalar)}; }
		cnstxpr	Tn3			operator/			(int32_t scalar)					cnst		{ return {T(x / scalar), T(y / scalar), T(z / scalar)}; }
		cnstxpr	Tn3			operator*			(uint32_t scalar)					cnstnxpt	{ return {T(x * scalar), T(y * scalar), T(z * scalar)}; }
		cnstxpr	Tn3			operator/			(uint32_t scalar)					cnst		{ return {T(x / scalar), T(y / scalar), T(z / scalar)}; }
		//
		Tn3&				operator+=			(cnst Tn3 & other)						nxpt	{ x += other.x; y += other.y; z += other.z;	return *this; }
		Tn3&				operator-=			(cnst Tn3 & other)						nxpt	{ x -= other.x; y -= other.y; z -= other.z;	return *this; }
		Tn3&				operator*=			(double scalar)							nxpt	{ x = T(x * scalar); y = T(y * scalar); z = T(z * scalar); return *this; }
		Tn3&				operator/=			(double scalar)									{ x = T(x / scalar); y = T(y / scalar); z = T(z / scalar); return *this; }
		Tn3&				operator*=			(s3_t scalar)							nxpt	{ x = T(x * scalar); y = T(y * scalar); z = T(z * scalar); return *this; }
		Tn3&				operator/=			(s3_t scalar)									{ x = T(x / scalar); y = T(y / scalar); z = T(z / scalar); return *this; }
		Tn3&				operator*=			(s2_t scalar)							nxpt	{ x = T(x * scalar); y = T(y * scalar); z = T(z * scalar); return *this; }
		Tn3&				operator/=			(s2_t scalar)									{ x = T(x / scalar); y = T(y / scalar); z = T(z / scalar); return *this; }
		Tn3&				operator*=			(u2_t scalar)							nxpt	{ x = T(x * scalar); y = T(y * scalar); z = T(z * scalar); return *this; }
		Tn3&				operator/=			(u2_t scalar)									{ x = T(x / scalar); y = T(y / scalar); z = T(z / scalar); return *this; }
		Tn3&				operator*=			(u3_t scalar)							nxpt	{ x = T(x * scalar); y = T(y * scalar); z = T(z * scalar); return *this; }
		Tn3&				operator/=			(u3_t scalar)									{ x = T(x / scalar); y = T(y / scalar); z = T(z / scalar); return *this; }
		//
		cnstxpr	Tn3			operator-			()									cnstnxpt	{ return {T(x*-1), T(y*-1), T(z*-1)}; }
		//
		inlcxpr	Tn2			xx					()									cnstnxpt	{ return {x, x}; }
		inlcxpr	Tn2			xy					()									cnstnxpt	{ return {x, y}; }
		inlcxpr	Tn2			xz					()									cnstnxpt	{ return {x, z}; }
		inlcxpr	Tn2			yx					()									cnstnxpt	{ return {y, x}; }
		inlcxpr	Tn2			yy					()									cnstnxpt	{ return {y, y}; }
		inlcxpr	Tn2			yz					()									cnstnxpt	{ return {y, z}; }
		inlcxpr	Tn2			zx					()									cnstnxpt	{ return {z, x}; }
		inlcxpr	Tn2			zy					()									cnstnxpt	{ return {z, y}; }
		inlcxpr	Tn2			zz					()									cnstnxpt	{ return {z, z}; }

		inlcxpr	Tn3			xxx					()									cnstnxpt	{ return {x, x, x}; }
		inlcxpr	Tn3			xxy					()									cnstnxpt	{ return {x, x, y}; }
		inlcxpr	Tn3			xxz					()									cnstnxpt	{ return {x, x, z}; }
		inlcxpr	Tn3			xyx					()									cnstnxpt	{ return {x, y, x}; }
		inlcxpr	Tn3			xyy					()									cnstnxpt	{ return {x, y, y}; }
		inlcxpr	Tn3			xyz					()									cnstnxpt	{ return {x, y, z}; }
		inlcxpr	Tn3			xzx					()									cnstnxpt	{ return {x, z, x}; }
		inlcxpr	Tn3			xzy					()									cnstnxpt	{ return {x, z, y}; }
		inlcxpr	Tn3			xzz					()									cnstnxpt	{ return {x, z, z}; }

		inlcxpr	Tn3			yxx					()									cnstnxpt	{ return {y, x, x}; }
		inlcxpr	Tn3			yxy					()									cnstnxpt	{ return {y, x, y}; }
		inlcxpr	Tn3			yxz					()									cnstnxpt	{ return {y, x, z}; }
		inlcxpr	Tn3			yyx					()									cnstnxpt	{ return {y, y, x}; }
		inlcxpr	Tn3			yyy					()									cnstnxpt	{ return {y, y, y}; }
		inlcxpr	Tn3			yyz					()									cnstnxpt	{ return {y, y, z}; }
		inlcxpr	Tn3			yzx					()									cnstnxpt	{ return {y, z, x}; }
		inlcxpr	Tn3			yzy					()									cnstnxpt	{ return {y, z, y}; }
		inlcxpr	Tn3			yzz					()									cnstnxpt	{ return {y, z, z}; }

		inlcxpr	Tn3			zxx					()									cnstnxpt	{ return {z, x, x}; }
		inlcxpr	Tn3			zxy					()									cnstnxpt	{ return {z, x, y}; }
		inlcxpr	Tn3			zxz					()									cnstnxpt	{ return {z, x, z}; }
		inlcxpr	Tn3			zyx					()									cnstnxpt	{ return {z, y, x}; }
		inlcxpr	Tn3			zyy					()									cnstnxpt	{ return {z, y, y}; }
		inlcxpr	Tn3			zyz					()									cnstnxpt	{ return {z, y, z}; }
		inlcxpr	Tn3			zzx					()									cnstnxpt	{ return {z, z, x}; }
		inlcxpr	Tn3			zzy					()									cnstnxpt	{ return {z, z, y}; }
		inlcxpr	Tn3			zzz					()									cnstnxpt	{ return {z, z, z}; }

		tpl_t2
		inlcxpr	n3<_t2>		Cast				()									cnstnxpt	{ return {(_t2)x, (_t2)y, (_t2)z}; }

		inlcxpr	n3<u0_t>	u8					()									cnstnxpt	{ return Cast<u0_t>(); }
		inlcxpr	n3<u1_t>	u16					()									cnstnxpt	{ return Cast<u1_t>(); }
		inlcxpr	n3<u2_t>	u32					()									cnstnxpt	{ return Cast<u2_t>(); }
		inlcxpr	n3<u3_t>	u64					()									cnstnxpt	{ return Cast<u3_t>(); }
		inlcxpr	n3<s0_t>	i8					()									cnstnxpt	{ return Cast<s0_t>(); }
		inlcxpr	n3<s1_t>	i16					()									cnstnxpt	{ return Cast<s1_t>(); }
		inlcxpr	n3<s2_t>	i32					()									cnstnxpt	{ return Cast<s2_t>(); }
		inlcxpr	n3<s3_t>	i64					()									cnstnxpt	{ return Cast<s3_t>(); }
		inlcxpr	n3<f2_t>	f32					()									cnstnxpt	{ return Cast<f2_t>(); }
		inlcxpr	n3<f3_t>	f64					()									cnstnxpt	{ return Cast<f3_t>(); }

		//
		inlcxpr	Tn3&		Area				()									cnstnxpt	{ return x * y * z; }
		inlcxpr	Tn3			Clamp				(cnst Tn3 & min, cnst Tn3 & max)	cnstnxpt	{ return {::llc::clamped(x, min.x, max.x), ::llc::clamped(y, min.y, max.y), ::llc::clamped(z, min.z, max.z)}; }
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
		inlcxpr	Tn3&		Normalize			()														{ cnst T sqLen = LengthSquared(); return sqLen ? *this /= ::sqrt(sqLen) : *this; }

		inline	Tn3			Scaled				(double scalar)						cnstnxpt	{ return Tn3{*this}.Scale(scalar); }
		inline	Tn3			Scaled				(cnst Tn3 & other)					cnstnxpt	{ return {x * other.x, y * other.y, z * other.z }; }
		inlcxpr	Tn3			Normalized			()									cnst				{ cnst T sqLen = LengthSquared(); return sqLen ? *this / ::sqrt(sqLen) : *this; }

		cnstxpr	double		Dot					(cnst Tn3 & other)					cnstnxpt	{ return x * other.x + y * other.y + z * other.z; }
		cnstxpr	T			LengthSquared		()									cnstnxpt	{ return x * x + y * y + z * z; }
		cnstxpr	double		Length				()									cnst				{ cnst T sqLen = LengthSquared(); return sqLen ? ::sqrt(sqLen) : 0; }
		cnstxpr	double		AngleWith			(cnst Tn3 & other)					cnst				{ cnst double lengthsProduct = Length() * other.Length(); return lengthsProduct ? ::acos(Dot(other) / lengthsProduct) : 0; }
		void				AddScaled			(cnst Tn3 & toScaleAndAdd, double scale)	nxpt	{
			x					+= (T)(toScaleAndAdd.x * scale);
			y					+= (T)(toScaleAndAdd.y * scale);
			z					+= (T)(toScaleAndAdd.z * scale);
		}
		cnstxpr	Tn3			Reflect				(cnst Tn3 & direction)				cnstnxpt	{ return direction - *this * 2 * Dot(direction);	}
		cnstxpr	Tn3			Cross				(cnst Tn3 & right)					cnstnxpt	{ return {y * right.z - z * right.y, z * right.x - x * right.z, x * right.y - y * right.x };	}
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
	tydf	n3<uc_t>	n3uc_t;	tydfcnst	n3uc_t	n3uc_c;
	tydf	n3<sc_t>	n3sc_t;	tydfcnst	n3sc_t	n3sc_c;
	tydf	n3<u0_t>	n3u0_t;	tydfcnst	n3u0_t	n3u0_c;
	tydf	n3<u1_t>	n3u1_t;	tydfcnst	n3u1_t	n3u1_c;
	tydf	n3<u2_t>	n3u2_t;	tydfcnst	n3u2_t	n3u2_c;
	tydf	n3<u3_t>	n3u3_t;	tydfcnst	n3u3_t	n3u3_c;
	tydf	n3<s0_t>	n3s0_t;	tydfcnst	n3s0_t	n3s0_c;
	tydf	n3<s1_t>	n3s1_t;	tydfcnst	n3s1_t	n3s1_c;
	tydf	n3<s2_t>	n3s2_t;	tydfcnst	n3s2_t	n3s2_c;
	tydf	n3<s3_t>	n3s3_t;	tydfcnst	n3s3_t	n3s3_c;
	tydf	n3<f2_t>	n3f2_t;	tydfcnst	n3f2_t	n3f2_c;
	tydf	n3<f3_t>	n3f3_t;	tydfcnst	n3f3_t	n3f3_c;
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

#define N3_F32 "{%f, %f, %f}"
#define N3_F64 "{%g, %g, %g}"
#define N3_I32 "{%" LLC_FMT_I32 ", %" LLC_FMT_I32 ", %" LLC_FMT_I32 "}"
#define N3_U32 "{%" LLC_FMT_U32 ", %" LLC_FMT_U32 ", %" LLC_FMT_U32 "}"
#define N3_I64 "{%lli, %lli, %lli}"
#define N3_U64 "{%llu, %llu, %llu}"

#define llc_xyz(n3var) n3var.x, n3var.y, n3var.z

#endif // LLC_N3_H_23627
