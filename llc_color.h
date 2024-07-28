/// Copyright 2009-2017 - ogarnd
#include "llc_math.h"

#ifndef LLC_COLOR_H_23627
#define LLC_COLOR_H_23627

namespace llc
{
#pragma pack(push, 1)
#define COLOR_RGBA_OPERATOR_MEMBERS(color_struct_type) \
	cnstxpr	bool		operator==			(const color_struct_type & other)	const	noexcept	{ return b == other.b && g == other.g && r == other.r && a == other.a; } \
	cnstxpr	bool		operator!=			(const color_struct_type & other)	const	noexcept	{ return b != other.b || g != other.g || r != other.r || a != other.a; } \

#define COLOR_RGB_OPERATOR_MEMBERS(color_struct_type) \
	cnstxpr	bool		operator==			(const color_struct_type & other)	const	noexcept	{ return b == other.b && g == other.g && r == other.r; } \
	cnstxpr	bool		operator!=			(const color_struct_type & other)	const	noexcept	{ return b != other.b || g != other.g || r != other.r; } \

	tplt <tpnm _tBase> struct color_a								{ _tBase a; LLC_DEFAULT_OPERATOR(color_a	, a == other.a); };
	tplt <tpnm _tBase> struct color_b								{ _tBase b; LLC_DEFAULT_OPERATOR(color_b	, b == other.b); };
	tplt <tpnm _tBase> struct color_r								{ _tBase r; LLC_DEFAULT_OPERATOR(color_r	, r == other.r); };

	tplt <tpnm _tBase> struct color_ab		: color_a	<_tBase>	{ _tBase b; LLC_DEFAULT_OPERATOR(color_ab	, color_a	<_tBase>::operator==(other) && b == other.b); };
	tplt <tpnm _tBase> struct color_abg		: color_ab	<_tBase>	{ _tBase g; LLC_DEFAULT_OPERATOR(color_abg	, color_ab	<_tBase>::operator==(other) && g == other.g); };
	tplt <tpnm _tBase> struct color_abgr	: color_abg	<_tBase>	{ _tBase r; LLC_DEFAULT_OPERATOR(color_abgr	, color_abg	<_tBase>::operator==(other) && r == other.r); };

	tplt <tpnm _tBase> struct color_ar		: color_a	<_tBase>	{ _tBase r; LLC_DEFAULT_OPERATOR(color_ar	, color_a	<_tBase>::operator==(other) && r == other.r); };
	tplt <tpnm _tBase> struct color_arg		: color_ar	<_tBase>	{ _tBase g; LLC_DEFAULT_OPERATOR(color_arg	, color_ar	<_tBase>::operator==(other) && g == other.g); };
	tplt <tpnm _tBase> struct color_argb	: color_arg	<_tBase>	{ _tBase b; LLC_DEFAULT_OPERATOR(color_argb	, color_arg	<_tBase>::operator==(other) && b == other.b); };

	tplt <tpnm _tBase> struct color_bg		: color_b<_tBase>		{ _tBase g; LLC_DEFAULT_OPERATOR(color_bg	, color_b	<_tBase>::operator==(other) && g == other.g); };
	tplt <tpnm _tBase> struct color_bgr		: color_bg<_tBase>		{ _tBase r; LLC_DEFAULT_OPERATOR(color_bgr	, color_bg	<_tBase>::operator==(other) && r == other.r); };
	tplt <tpnm _tBase> struct color_bgra	: color_bgr<_tBase>		{ _tBase a; LLC_DEFAULT_OPERATOR(color_bgra	, color_bgr	<_tBase>::operator==(other) && a == other.a); };

	tplt <tpnm _tBase> struct color_rg		: color_r<_tBase>		{ _tBase g; LLC_DEFAULT_OPERATOR(color_rg	, color_r	<_tBase>::operator==(other) && g == other.g); };
	tplt <tpnm _tBase> struct color_rgb		: color_rg<_tBase>		{ _tBase b; LLC_DEFAULT_OPERATOR(color_rgb	, color_rg	<_tBase>::operator==(other) && b == other.b); };
	tplt <tpnm _tBase> struct color_rgba	: color_rgb<_tBase>		{ _tBase a; LLC_DEFAULT_OPERATOR(color_rgba	, color_rgb	<_tBase>::operator==(other) && a == other.a); };

	typedef	u1_t		SColor16;

	typedef color_bgr <u0_t>	bgr8 ;
	typedef color_rgb <u0_t>	rgb8 ;
	typedef color_bgra<u0_t>	bgra8;
	typedef color_rgba<u0_t>	rgba8;
	typedef color_abgr<u0_t>	abgr8;
	typedef color_argb<u0_t>	argb8;

	typedef color_bgr <u1_t>	bgr16 ;
	typedef color_rgb <u1_t>	rgb16 ;
	typedef color_bgra<u1_t>	bgra16;
	typedef color_rgba<u1_t>	rgba16;
	typedef color_abgr<u1_t>	abgr16;
	typedef color_argb<u1_t>	argb16;

	typedef color_bgr <f2_t>	bgrf32;
	typedef color_rgb <f2_t>	rgbf32;
	typedef color_bgra<f2_t>	bgraf32;
	typedef color_rgba<f2_t>	rgbaf32;
	typedef color_abgr<f2_t>	abgrf32;
	typedef color_argb<f2_t>	argbf32;

	typedef const color_bgr <u0_t>	cbgr8 ;
	typedef const color_rgb <u0_t>	crgb8 ;
	typedef const color_bgra<u0_t>	cbgra8;
	typedef const color_rgba<u0_t>	crgba8;
	typedef const color_abgr<u0_t>	cabgr8;
	typedef const color_argb<u0_t>	cargb8;

	typedef const color_bgr <u1_t>	cbgr16 ;
	typedef const color_rgb <u1_t>	crgb16 ;
	typedef const color_bgra<u1_t>	cbgra16;
	typedef const color_rgba<u1_t>	crgba16;
	typedef const color_abgr<u1_t>	cabgr16;
	typedef const color_argb<u1_t>	cargb16;

	typedef const color_bgr <f2_t>	cbgrf32;
	typedef const color_rgb <f2_t>	crgbf32;
	typedef const color_bgra<f2_t>	cbgraf32;
	typedef const color_rgba<f2_t>	crgbaf32;
	typedef const color_abgr<f2_t>	cabgrf32;
	typedef const color_argb<f2_t>	cargbf32;

	cnstxpr	float			BYTE_SCALE			= 1.0f / 255.0f;

	// Stores RGBA color channels
	struct SColorRGBA : public ::llc::rgba8 {
								SColorRGBA		()									noexcept	= default;
		cnstxpr					SColorRGBA		(const SColorRGBA &)				noexcept	= default;
		cnstxpr					SColorRGBA		(u0_t r_, u0_t g_, u0_t b_, u0_t a_=0xff)	noexcept	: color_rgba<u0_t>{{{{r_}, g_}, b_}, a_}						{}
		cnstxpr					SColorRGBA		(u2_t other)					noexcept	: color_rgba<u0_t>
			{ {{{u0_t(((other & 0x000000FF) >>  0))}
			, u0_t(((other & 0x0000FF00) >>  8))	 }
			, u0_t(((other & 0x00FF0000) >> 16))	 }
			, u0_t(((other & 0xFF000000) >> 24))
			}
		{}

		COLOR_RGBA_OPERATOR_MEMBERS(SColorRGBA); 
		cnstxpr	operator		u2_t		()							const	noexcept	{ return (((u2_t)a) << 24) | (((u2_t)b) << 16) | (((u2_t)g) << 8) | (((u2_t)r) << 0);					}


		cnstxpr	bool			operator ==		(u2_t other)			const	noexcept	{ return other == *((const u2_t*)this);			}
		cnstxpr	SColorRGBA		operator *		(const SColorRGBA & color)	const	noexcept	{ return {(u0_t)::llc::clamped(r * (int)color.r, 0, 255)	, (u0_t)::llc::clamped(g * (int)color.g, 0, 255), (u0_t)::llc::clamped(b * (int)color.b, 0, 255), a};	}
		cnstxpr	SColorRGBA		operator +		(const SColorRGBA & color)	const	noexcept	{ return {(u0_t)::llc::clamped(r + (int)color.r, 0, 255)	, (u0_t)::llc::clamped(g + (int)color.g, 0, 255), (u0_t)::llc::clamped(b + (int)color.b, 0, 255), a};	}
		cnstxpr	SColorRGBA		operator *		(double scalar)				const	noexcept	{ return {(u0_t)::llc::clamped(r * scalar, 0.0 , 255.0)		, (u0_t)::llc::clamped(g * scalar, 0.0,   255.0), (u0_t)::llc::clamped(b * scalar, 0.0,   255.0), a};	}
		cnstxpr	SColorRGBA		operator /		(double scalar)				const				{ return {(u0_t)::llc::clamped(r / scalar, 0.0 , 255.0)		, (u0_t)::llc::clamped(g / scalar, 0.0,   255.0), (u0_t)::llc::clamped(b / scalar, 0.0,   255.0), a};	}
	};	// struct

	// Stores BGRA color channels
	struct SColorBGRA : public ::llc::bgra8 {
								SColorBGRA		()									noexcept	= default;
		cnstxpr					SColorBGRA		(const SColorBGRA &)				noexcept	= default;
		cnstxpr					SColorBGRA		(const SColorRGBA & other)			noexcept	: color_bgra<u0_t>{{{{other.b}, other.g}, other.r}, other.a} {}
		cnstxpr					SColorBGRA		(u0_t b_, u0_t g_, u0_t r_, u0_t a_=0xff)	noexcept	: color_bgra<u0_t>{{{{b_}, g_}, r_}, a_} {}
		cnstxpr					SColorBGRA		(u2_t other)					noexcept	: color_bgra<u0_t>
			{ {{{u0_t(((other & 0x000000FF) >>  0)) }
			, u0_t(((other & 0x0000FF00) >>  8))	  }
			, u0_t(((other & 0x00FF0000) >> 16))	  }
			, u0_t(((other & 0xFF000000) >> 24))
			}
		{}

		COLOR_RGBA_OPERATOR_MEMBERS(SColorBGRA); 
		cnstxpr	operator		SColorRGBA		()							const	noexcept	{ return {r, g, b, a};						}
		cnstxpr	operator		u2_t		()							const	noexcept	{ return (((u2_t)a) << 24) | (((u2_t)r) << 16) | (((u2_t)g) << 8) | (((u2_t)b) << 0);					}

		cnstxpr	bool			operator==		(u2_t other)			const	noexcept	{ return other == *((const u2_t*)this);			}
		cnstxpr	SColorBGRA		operator*		(const SColorBGRA & color)	const	noexcept	{ return {(u0_t)::llc::min(b * (int)color.b, 255)	, (u0_t)::llc::min(g * (int)color.g, 255)	,(u0_t)::llc::min(r * (int)color.r, 255), a};			}
		cnstxpr	SColorBGRA		operator+		(const SColorBGRA & color)	const	noexcept	{ return {(u0_t)::llc::min(b + (int)color.b, 255)	, (u0_t)::llc::min(g + (int)color.g, 255)	,(u0_t)::llc::min(r + (int)color.r, 255), a};			}
		cnstxpr	SColorBGRA		operator-		(const SColorBGRA & color)	const	noexcept	{ return {(u0_t)::llc::clamped(b - (int16_t)color.b, 0, 255), (u0_t)::llc::clamped(g - (int16_t)color.g, 0, 255),(u0_t)::llc::clamped(r - (int16_t)color.r, 0, 255), a};	}
		cnstxpr	SColorBGRA		operator*		(float scalar)				const	noexcept	{ return {(u0_t)::llc::clamped(b * scalar, 0.0f, 255.0f)	, (u0_t)::llc::clamped(g * scalar, 0.0f, 255.0f)	,(u0_t)::llc::clamped(r * scalar, 0.0f, 255.0f), a};			}
		cnstxpr	SColorBGRA		operator/		(float scalar)				const				{ return {(u0_t)::llc::clamped(b / scalar, 0.0f, 255.0f)	, (u0_t)::llc::clamped(g / scalar, 0.0f, 255.0f)	,(u0_t)::llc::clamped(r / scalar, 0.0f, 255.0f), a};			}
		cnstxpr	SColorBGRA		operator*		(double scalar)				const	noexcept	{ return {(u0_t)::llc::clamped(b * scalar, 0.0,  255.0 )	, (u0_t)::llc::clamped(g * scalar, 0.0 , 255.0 )	,(u0_t)::llc::clamped(r * scalar, 0.0, 255.0),	a};				}
		cnstxpr	SColorBGRA		operator/		(double scalar)				const				{ return {(u0_t)::llc::clamped(b / scalar, 0.0,  255.0 )	, (u0_t)::llc::clamped(g / scalar, 0.0 , 255.0 )	,(u0_t)::llc::clamped(r / scalar, 0.0, 255.0),	a};				}
				SColorBGRA&		operator*=		(float scalar)						noexcept	{ b = (u0_t)::llc::clamped(b * scalar, 0.0f, 255.0f); g = (u0_t)::llc::clamped(g * scalar, 0.0f, 255.0f); r = (u0_t)::llc::clamped(r * scalar, 0.0f, 255.0f);	return *this; }
				SColorBGRA&		operator/=		(float scalar)									{ b = (u0_t)::llc::clamped(b / scalar, 0.0f, 255.0f); g = (u0_t)::llc::clamped(g / scalar, 0.0f, 255.0f); r = (u0_t)::llc::clamped(r / scalar, 0.0f, 255.0f);	return *this; }
				SColorBGRA&		operator*=		(double scalar)						noexcept	{ b = (u0_t)::llc::clamped(b * scalar, 0.0,  255.0 ); g = (u0_t)::llc::clamped(g * scalar, 0.0 , 255.0 ); r = (u0_t)::llc::clamped(r * scalar, 0.0, 255.0);		return *this; }
				SColorBGRA&		operator/=		(double scalar)									{ b = (u0_t)::llc::clamped(b / scalar, 0.0,  255.0 ); g = (u0_t)::llc::clamped(g / scalar, 0.0 , 255.0 ); r = (u0_t)::llc::clamped(r / scalar, 0.0, 255.0);		return *this; }

				SColorBGRA&		FromBGR16		(const SColor16 & other)			noexcept	{ b = u0_t((other & 0x1F) / float(0x1F) * 255); g = u0_t(((other & 0x07E0) >> 5) / float(0x3F) * 255); r = u0_t(((other & 0xF800) >> 11) / float(0x1F) * 255);	return *this; }
				SColorBGRA&		FromRGB16		(const SColor16 & other)			noexcept	{ r = u0_t((other & 0x1F) / float(0x1F) * 255); g = u0_t(((other & 0x07E0) >> 5) / float(0x3F) * 255); b = u0_t(((other & 0xF800) >> 11) / float(0x1F) * 255);	return *this; }
	};	// struct

	// Stores RGB color channels
	struct SColorRGB : public ::llc::rgb8 {
								SColorRGB		()									noexcept	= default;
		cnstxpr					SColorRGB		(const SColorRGB & other)			noexcept	= default;
		cnstxpr					SColorRGB		(u0_t r_, u0_t g_, u0_t b_)				noexcept	: color_rgb<u0_t>{{{r_}, g_}, b_} {}
		cnstxpr					SColorRGB		(u2_t other)					noexcept	: color_rgb<u0_t>
			{ {{u0_t(((other & 0x000000FF) >>  0))}
			, u0_t(((other & 0x0000FF00) >>  8))	}
			, u0_t(((other & 0x00FF0000) >> 16))
			}
		{}

		COLOR_RGB_OPERATOR_MEMBERS(SColorRGB); 
		cnstxpr	operator		u2_t		()							const	noexcept	{ return  0xFF000000 | (((u2_t)b) << 16) | (((u2_t)g) << 8)	| (((u2_t)r) << 0);  }
		cnstxpr	operator		SColorRGBA		()							const	noexcept	{ return {0xFF000000 | (((u2_t)b) << 16) | (((u2_t)g) << 8)	| (((u2_t)r) << 0)}; }
		cnstxpr	operator		SColor16		()							const	noexcept	{ return (((u1_t)(r * BYTE_SCALE * 0x001F)) << 0) | (((u1_t)(g * BYTE_SCALE * 0x003F)) << 5) | (((u1_t)(b * BYTE_SCALE * 0x001F)) << 11 );												}
		cnstxpr	bool			operator ==		(const SColorRGBA & other)	const	noexcept	{ return r == other.r && g == other.g && b == other.b;	}
		cnstxpr	bool			operator !=		(const SColorRGBA & other)	const	noexcept	{ return r != other.r || g != other.g || b != other.b;	}
		cnstxpr	bool			operator ==		(const SColor16   & other)	const	noexcept	{ return (SColor16)(*this) == other;					}
		cnstxpr	bool			operator !=		(const SColor16   & other)	const	noexcept	{ return (SColor16)(*this) != other;					}
		cnstxpr	SColorRGB		operator *		(float scalar)				const	noexcept	{ return {(u0_t)::llc::clamped(r * scalar, 0.0f, 255.0f), (u0_t)::llc::clamped(g * scalar, 0.0f, 255.0f),	(u0_t)::llc::clamped(b * scalar, 0.0f, 255.0f)}; }
		cnstxpr	SColorRGB		operator /		(float scalar)				const				{ return {(u0_t)::llc::clamped(r / scalar, 0.0f, 255.0f), (u0_t)::llc::clamped(g / scalar, 0.0f, 255.0f),	(u0_t)::llc::clamped(b / scalar, 0.0f, 255.0f)}; }
		cnstxpr	SColorRGB		operator *		(double scalar)				const	noexcept	{ return {(u0_t)::llc::clamped(r * scalar, 0.0,  255.0),  (u0_t)::llc::clamped(g * scalar, 0.0,  255.0),	(u0_t)::llc::clamped(b * scalar, 0.0,  255.0)};  }
		cnstxpr	SColorRGB		operator /		(double scalar)				const				{ return {(u0_t)::llc::clamped(r / scalar, 0.0,  255.0),  (u0_t)::llc::clamped(g / scalar, 0.0,  255.0),	(u0_t)::llc::clamped(b / scalar, 0.0,  255.0)};  }
		cnstxpr	SColorRGB		operator *		(const SColorRGB  & color)	const	noexcept	{ return {(u0_t)::llc::clamped(r * (int)color.r, 0, 255), (u0_t)::llc::clamped(g * (int)color.g, 0, 255), (u0_t)::llc::clamped(b * (int)color.b, 0, 255)};			}
		cnstxpr	SColorRGB		operator +		(const SColorRGB  & color)	const	noexcept	{ return {(u0_t)::llc::clamped(r + (int)color.r, 0, 255), (u0_t)::llc::clamped(g + (int)color.g, 0, 255), (u0_t)::llc::clamped(b + (int)color.b, 0, 255)};			}
		cnstxpr	SColorRGBA		operator *		(const SColorRGBA & color)	const	noexcept	{ return {(u0_t)::llc::clamped(r * (int)color.r, 0, 255), (u0_t)::llc::clamped(g * (int)color.g, 0, 255), (u0_t)::llc::clamped(b * (int)color.b, 0, 255), color.a};	}
		cnstxpr	SColorRGBA		operator +		(const SColorRGBA & color)	const	noexcept	{ return {(u0_t)::llc::clamped(r + (int)color.r, 0, 255), (u0_t)::llc::clamped(g + (int)color.g, 0, 255), (u0_t)::llc::clamped(b + (int)color.b, 0, 255), color.a};	}
	};	// struct

	// Stores BGR color channels
	struct SColorBGR : public ::llc::color_bgr<u0_t> {
								SColorBGR		()									noexcept	= default;
		cnstxpr					SColorBGR		(const SColorBGR & other)			noexcept	= default;
		cnstxpr					SColorBGR		(u0_t b_, u0_t g_, u0_t r_)				noexcept	: color_bgr<u0_t>{{{b_}, g_}, r_} {}
		cnstxpr					SColorBGR		(u2_t other)					noexcept	: color_bgr<u0_t>
			{ {{u0_t(((other & 0x000000FF) >>  0))}
			, u0_t(((other & 0x0000FF00) >>  8))	}
			, u0_t(((other & 0x00FF0000) >> 16))
			}
		{}
		COLOR_RGB_OPERATOR_MEMBERS(SColorBGR); 
		cnstxpr	operator		u2_t			()							const	noexcept	{ return 0xFF000000 | (((u2_t)r) << 16)	| (((u2_t)g) << 8) | (((u2_t)b) << 0);																	}
		cnstxpr	operator		SColorBGRA		()							const	noexcept	{ return {b, g, r, 0xFF};														}
		cnstxpr	operator		SColor16		()							const	noexcept	{ return (((u1_t)(b * BYTE_SCALE * 0x001F)) << 0) | (((u1_t)(g * BYTE_SCALE * 0x003F)) << 5) | (((u1_t)(r * BYTE_SCALE * 0x001F)) << 11 );	}

		cnstxpr	bool			operator ==		(const SColorBGRA & other)	const	noexcept	{ return r == other.r && g == other.g && b == other.b;	}
		cnstxpr	bool			operator !=		(const SColorBGRA & other)	const	noexcept	{ return r != other.r || g != other.g || b != other.b;	}
		cnstxpr	bool			operator ==		(const SColor16   & other)	const	noexcept	{ return (SColor16)(*this) == other;					}
		cnstxpr	bool			operator !=		(const SColor16   & other)	const	noexcept	{ return (SColor16)(*this) != other;					}
		cnstxpr	SColorBGR		operator *		(float scalar)				const	noexcept	{ return {(u0_t)::llc::clamped(b * scalar, 0.0f, 255.0f), (u0_t)::llc::clamped(g * scalar, 0.0f, 255.0f), (u0_t)::llc::clamped(r * scalar, 0.0f, 255.0f)};	}
		cnstxpr	SColorBGR		operator /		(float scalar)				const				{ return {(u0_t)::llc::clamped(b / scalar, 0.0f, 255.0f), (u0_t)::llc::clamped(g / scalar, 0.0f, 255.0f), (u0_t)::llc::clamped(r / scalar, 0.0f, 255.0f)};	}
		cnstxpr	SColorBGR		operator *		(double scalar)				const	noexcept	{ return {(u0_t)::llc::clamped(b * scalar, 0.0,  255.0) , (u0_t)::llc::clamped(g * scalar, 0.0,  255.0) , (u0_t)::llc::clamped(r * scalar, 0.0,  255.0)};	}
		cnstxpr	SColorBGR		operator /		(double scalar)				const				{ return {(u0_t)::llc::clamped(b / scalar, 0.0,  255.0) , (u0_t)::llc::clamped(g / scalar, 0.0,  255.0) , (u0_t)::llc::clamped(r / scalar, 0.0,  255.0)};	}
		cnstxpr	SColorBGR		operator *		(const SColorBGR  & color)	const	noexcept	{ return {(u0_t)::llc::clamped(b * (int)color.b, 0, 255) , (u0_t)::llc::clamped(g * (int)color.g, 0, 255)	, (u0_t)::llc::clamped(r * (int)color.r, 0, 255)};			}
		cnstxpr	SColorBGR		operator +		(const SColorBGR  & color)	const	noexcept	{ return {(u0_t)::llc::clamped(b + (int)color.b, 0, 255) , (u0_t)::llc::clamped(g + (int)color.g, 0, 255)	, (u0_t)::llc::clamped(r + (int)color.r, 0, 255)};			}
		cnstxpr	SColorBGRA		operator *		(const SColorBGRA & color)	const	noexcept	{ return {(u0_t)::llc::clamped(b * (int)color.b, 0, 255) , (u0_t)::llc::clamped(g * (int)color.g, 0, 255)	, (u0_t)::llc::clamped(r * (int)color.r, 0, 255), color.a};	}
		cnstxpr	SColorBGRA		operator +		(const SColorBGRA & color)	const	noexcept	{ return {(u0_t)::llc::clamped(b + (int)color.b, 0, 255) , (u0_t)::llc::clamped(g + (int)color.g, 0, 255)	, (u0_t)::llc::clamped(r + (int)color.r, 0, 255), color.a};	}

				SColorBGR&		FromBGR16		(const SColor16   & other)			noexcept	{ b = u0_t((other & 0x1F) / float(0x1F) * 255); g = u0_t(((other & 0x07E0) >> 5) / float(0x3F) * 255); r = u0_t(((other & 0xF800) >> 11) / float(0x1F) * 255);	return *this; }
				SColorBGR&		FromRGB16		(const SColor16   & other)			noexcept	{ r = u0_t((other & 0x1F) / float(0x1F) * 255); g = u0_t(((other & 0x07E0) >> 5) / float(0x3F) * 255); b = u0_t(((other & 0xF800) >> 11) / float(0x1F) * 255);	return *this; }
	};	// struct

	// Stores RGBA floating point color channels
	struct SColorFloat : public ::llc::rgbaf32 {
								SColorFloat		()										noexcept	= default;
		cnstxpr					SColorFloat		(const SColorFloat & color)				noexcept	= default;
		cnstxpr					SColorFloat		(f2_t r_, f2_t g_, f2_t b_, f2_t a_=1.0f)	noexcept	: color_rgba<float>{{{{r_}, g_}, b_}, a_}						{}
		cnstxpr					SColorFloat		(const float* rgbaColor)							: color_rgba<float>{{{{rgbaColor[0]}, rgbaColor[1]}, rgbaColor[2]}, rgbaColor[3]}	{}
		cnstxpr					SColorFloat		(SColorBGRA color)						noexcept	: color_rgba<float>
			{ {{{color.r * BYTE_SCALE}
			, color.g * BYTE_SCALE	 }
			, color.b * BYTE_SCALE	 }
			, color.a * BYTE_SCALE
			} {}
		cnstxpr					SColorFloat		(::llc::bgr8 color, uint8_t alpha)		noexcept	: color_rgba<float>
			{ {{{color.r * BYTE_SCALE}
			, color.g * BYTE_SCALE	 }
			, color.b * BYTE_SCALE	 }
			, alpha * BYTE_SCALE
			} {}
		cnstxpr					SColorFloat		(::llc::rgbf32 color, float alpha)		noexcept	: color_rgba<float>
			{ {{{color.r }
			, color.g }
			, color.b }
			, alpha 
			} {}
		COLOR_RGBA_OPERATOR_MEMBERS(SColorFloat); 
		cnstxpr	operator		SColorBGRA		()							const	noexcept	{ return {u0_t(b * 255), u0_t(g * 255), u0_t(r * 255), u0_t(a * 255)};	}
		cnstxpr	operator		const float*	()							const	noexcept	{ return &r;															}
				SColorFloat&	operator +=		(const SColorFloat & color)			noexcept	{ r = r + color.r;					g = g + color.g;				b = b + color.b;				return *this;	}
				SColorFloat&	operator *=		(const SColorFloat & color)			noexcept	{ r = r * color.r;					g = g * color.g;				b = b * color.b;				return *this;	}
				SColorFloat&	operator *=		(double scalar)						noexcept	{ r = (float)(r * scalar);			g = (float)(g * scalar);		b = (float)(b * scalar);		return *this;	}
				SColorFloat&	operator /=		(double scalar)									{ r = (float)(r / scalar);			g = (float)(g / scalar);		b = (float)(b / scalar);		return *this;	}
				SColorFloat&	operator *=		(float scalar)						noexcept	{ r = r * scalar;					g = g * scalar;					b = b * scalar;					return *this;	}
				SColorFloat&	operator /=		(float scalar)									{ r = r / scalar;					g = g / scalar;					b = b / scalar;					return *this;	}
				SColorFloat&	operator *=		(const SColorBGRA  & color)			noexcept	{ r = r * (color.r * BYTE_SCALE);	g = g * (color.g * BYTE_SCALE);	b = b * (color.b * BYTE_SCALE);	return *this;	}
				SColorFloat&	operator +=		(const SColorBGRA  & color)			noexcept	{ r = r + (color.r * BYTE_SCALE);	g = g + (color.g * BYTE_SCALE);	b = b + (color.b * BYTE_SCALE);	return *this;	}
				SColorFloat&	operator *=		(const SColorBGR   & color)			noexcept	{ r = r * (color.r * BYTE_SCALE);	g = g * (color.g * BYTE_SCALE);	b = b * (color.b * BYTE_SCALE);	return *this;	}
				SColorFloat&	operator +=		(const SColorBGR   & color)			noexcept	{ r = r + (color.r * BYTE_SCALE);	g = g + (color.g * BYTE_SCALE);	b = b + (color.b * BYTE_SCALE);	return *this;	}
				SColorFloat		operator *		(const SColorBGRA  & color)	const	noexcept	{ return {r * (color.r * BYTE_SCALE), g * (color.g * BYTE_SCALE), b * (color.b * BYTE_SCALE), a};	}
				SColorFloat		operator +		(const SColorBGRA  & color)	const	noexcept	{ return {r + (color.r * BYTE_SCALE), g + (color.g * BYTE_SCALE), b + (color.b * BYTE_SCALE), a};	}
				SColorFloat		operator *		(const SColorBGR   & color)	const	noexcept	{ return {r * (color.r * BYTE_SCALE), g * (color.g * BYTE_SCALE), b * (color.b * BYTE_SCALE), a};	}
				SColorFloat		operator +		(const SColorBGR   & color)	const	noexcept	{ return {r + (color.r * BYTE_SCALE), g + (color.g * BYTE_SCALE), b + (color.b * BYTE_SCALE), a};	}
		cnstxpr	SColorFloat		operator *		(const SColorFloat & color)	const	noexcept	{ return {r * color.r, g * color.g, b * color.b, a};												}
		cnstxpr	SColorFloat		operator +		(const SColorFloat & color)	const	noexcept	{ return {r + color.r, g + color.g, b + color.b, a};												}
		cnstxpr	SColorFloat		operator -		(const SColorFloat & color)	const	noexcept	{ return {r - color.r, g - color.g, b - color.b, a};												}
		cnstxpr	SColorFloat		operator *		(double scalar)				const	noexcept	{ return {(float)(r * scalar), (float)(g * scalar), (float)(b * scalar), a};						}
		cnstxpr	SColorFloat		operator *		(float scalar)				const	noexcept	{ return {(r * scalar), (g * scalar),	(b * scalar)};												}
		cnstxpr	SColorFloat		operator /		(double scalar)				const				{ return {(float)(r / scalar), (float)(g / scalar), (float)(b / scalar), a};						}
		cnstxpr	SColorFloat		operator /		(float scalar)				const				{ return {r / scalar,	g / scalar,	b / scalar};													}

				SColorFloat&	Clamp			()									noexcept	{ r = ::llc::clamped(r, 0.0f, 1.0f); g = ::llc::clamped(g, 0.0f, 1.0f); b = ::llc::clamped(b, 0.0f, 1.0f); return *this;	}

		cnstxpr	::llc::rgbf32	rgb				()							const				{ return {{{r}, g}, b}; }
	};	// struct

	typedef ::llc::SColorFloat					frgba	;
	typedef ::llc::SColorBGRA					u8bgra	;
	typedef ::llc::SColorBGR					u8bgr	;
	typedef ::llc::SColorRGBA					u8rgba	;
	typedef ::llc::SColorRGB					u8rgb	;

	typedef const frgba							cfrgba	;
	typedef const u8bgra						c8bgra	;
	typedef const u8bgr							c8bgr	;
	typedef const u8rgba						c8rgba	;
	typedef const u8rgb							c8rgb	;

	typedef frgba								rgbaf	;
	typedef u8bgra								bgra	;
	typedef u8bgr								bgr		;
	typedef u8rgba								rgba	;
	typedef u8rgb								rgb		;


	stacxpr	::llc::rgbaf	BLACK			= {0.0f , 0.0f               , 0.00f, 1.0f};
	stacxpr	::llc::rgbaf	WHITE			= {1.0f , 1.0f               , 1.0f , 1.0f};
	stacxpr	::llc::rgbaf	RED				= {1.0f , 0.0f               , 0.0f , 1.0f};
	stacxpr	::llc::rgbaf	GREEN			= {0.0f , 1.0f               , 0.0f , 1.0f};
	stacxpr	::llc::rgbaf	BLUE			= {0.0f , 0.0f               , 1.0f , 1.0f};
	stacxpr	::llc::rgbaf	YELLOW			= {1.0f , 1.0f               , 0.0f , 1.0f};
	stacxpr	::llc::rgbaf	MAGENTA			= {1.0f , 0.0f               , 1.0f , 1.0f};
	stacxpr	::llc::rgbaf	CYAN			= {0.0f , 1.0f               , 1.0f , 1.0f};
	stacxpr	::llc::rgbaf	ORANGE			= {1.0f , 0.647f             , 0.0f , 1.0f};
	stacxpr	::llc::rgbaf	PANOCHE			= {0.25f, 0.5f               , 1.0f , 1.0f};
	stacxpr	::llc::rgbaf	PURPLE			= {0.5f , 0.1f               , 1.0f , 1.0f};
	stacxpr	::llc::rgbaf	TURQUOISE		= {0.2f , 1.0                , 0.65f, 1.0f};
	stacxpr	::llc::rgbaf	BROWN			= {0.4f , 0.223f             , 0.0f , 1.0f};
	stacxpr	::llc::rgbaf	GRAY			= {0.5f , 0.5f               , 0.5f , 1.0f};
	stacxpr	::llc::rgbaf	LIGHTGRAY		= {0.75f, 0.75f              , 0.75f, 1.0f};
	stacxpr	::llc::rgbaf	LIGHTRED		= {1.0f , 0.25f              , 0.25f, 1.0f};
	stacxpr	::llc::rgbaf	LIGHTGREEN		= {0.5f , 1.0f               , 0.5f , 1.0f};
	stacxpr	::llc::rgbaf	LIGHTBLUE		= {0.25f, 0.25f              , 1.0f , 1.0f};
	stacxpr	::llc::rgbaf	LIGHTYELLOW		= {1.0f , 1.0f               , 0.25f, 1.0f};
	stacxpr	::llc::rgbaf	LIGHTMAGENTA	= {1.0f , 0.25f              , 1.0f , 1.0f};
	stacxpr	::llc::rgbaf	LIGHTCYAN		= {0.25f, 1.0f               , 1.0f , 1.0f};
	stacxpr	::llc::rgbaf	LIGHTORANGE		= {1.0f , 0.780f             , 0.25f, 1.0f};
	stacxpr	::llc::rgbaf	DARKGRAY		= {0.25f, 0.25f              , 0.25f, 1.0f};
	stacxpr	::llc::rgbaf	DARKRED			= {0.5f , 0.0f               , 0.0f , 1.0f};
	stacxpr	::llc::rgbaf	DARKGREEN		= {0.0f , 0.5f               , 0.0f , 1.0f};
	stacxpr	::llc::rgbaf	DARKBLUE		= {0.0f , 0.0f               , 0.5f , 1.0f};
	stacxpr	::llc::rgbaf	DARKYELLOW		= {0.5f , 0.5f               , 0.0f , 1.0f};
	stacxpr	::llc::rgbaf	DARKMAGENTA		= {0.5f , 0.0f               , 0.5f , 1.0f};
	stacxpr	::llc::rgbaf	DARKCYAN		= {0.0f , 0.5f               , 0.5f , 1.0f};
	stacxpr	::llc::rgbaf	DARKORANGE		= {1.0f , 0.5490196078431373f, 0.00f, 1.0f};
#pragma pack(pop)
} // namespace

#endif // LLC_COLOR_H_23627
