/// Copyright 2009-2017 - ogarnd
#include "llc_math.h"

#ifndef LLC_COLOR_H_23627
#define LLC_COLOR_H_23627

namespace llc
{
#pragma pack(push, 1)
#define COLOR_RGBA_OPERATOR_MEMBERS(color_struct_type) \
	cxpr	bool		operator==			(cnst color_struct_type & other)	cnstnxpt	{ return b == other.b && g == other.g && r == other.r && a == other.a; } \
	cxpr	bool		operator!=			(cnst color_struct_type & other)	cnstnxpt	{ return b != other.b || g != other.g || r != other.r || a != other.a; } \

#define COLOR_RGB_OPERATOR_MEMBERS(color_struct_type) \
	cxpr	bool		operator==			(cnst color_struct_type & other)	cnstnxpt	{ return b == other.b && g == other.g && r == other.r; } \
	cxpr	bool		operator!=			(cnst color_struct_type & other)	cnstnxpt	{ return b != other.b || g != other.g || r != other.r; } \

	tplT struct color_a								{ T a; LLC_DEFAULT_OPERATOR(color_a	, a == other.a); };
	tplT struct color_b								{ T b; LLC_DEFAULT_OPERATOR(color_b	, b == other.b); };
	tplT struct color_r								{ T r; LLC_DEFAULT_OPERATOR(color_r	, r == other.r); };

	tplT struct color_ab		: color_a	<T>		{ T b; LLC_DEFAULT_OPERATOR(color_ab	, color_a	<T>::operator==(other) && b == other.b); };
	tplT struct color_abg		: color_ab	<T>		{ T g; LLC_DEFAULT_OPERATOR(color_abg	, color_ab	<T>::operator==(other) && g == other.g); };
	tplT struct color_abgr		: color_abg	<T>		{ T r; LLC_DEFAULT_OPERATOR(color_abgr	, color_abg	<T>::operator==(other) && r == other.r); };

	tplT struct color_ar		: color_a	<T>		{ T r; LLC_DEFAULT_OPERATOR(color_ar	, color_a	<T>::operator==(other) && r == other.r); };
	tplT struct color_arg		: color_ar	<T>		{ T g; LLC_DEFAULT_OPERATOR(color_arg	, color_ar	<T>::operator==(other) && g == other.g); };
	tplT struct color_argb		: color_arg	<T>		{ T b; LLC_DEFAULT_OPERATOR(color_argb	, color_arg	<T>::operator==(other) && b == other.b); };

	tplT struct color_bg		: color_b<T>		{ T g; LLC_DEFAULT_OPERATOR(color_bg	, color_b	<T>::operator==(other) && g == other.g); };
	tplT struct color_bgr		: color_bg<T>		{ T r; LLC_DEFAULT_OPERATOR(color_bgr	, color_bg	<T>::operator==(other) && r == other.r); };
	tplT struct color_bgra		: color_bgr<T>		{ T a; LLC_DEFAULT_OPERATOR(color_bgra	, color_bgr	<T>::operator==(other) && a == other.a); };

	tplT struct color_rg		: color_r<T>		{ T g; LLC_DEFAULT_OPERATOR(color_rg	, color_r	<T>::operator==(other) && g == other.g); };
	tplT struct color_rgb		: color_rg<T>		{ T b; LLC_DEFAULT_OPERATOR(color_rgb	, color_rg	<T>::operator==(other) && b == other.b); };
	tplT struct color_rgba		: color_rgb<T>		{ T a; LLC_DEFAULT_OPERATOR(color_rgba	, color_rgb	<T>::operator==(other) && a == other.a); };

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

	typedef cnst color_bgr <u0_t>	cbgr8 ;
	typedef cnst color_rgb <u0_t>	crgb8 ;
	typedef cnst color_bgra<u0_t>	cbgra8;
	typedef cnst color_rgba<u0_t>	crgba8;
	typedef cnst color_abgr<u0_t>	cabgr8;
	typedef cnst color_argb<u0_t>	cargb8;

	typedef cnst color_bgr <u1_t>	cbgr16 ;
	typedef cnst color_rgb <u1_t>	crgb16 ;
	typedef cnst color_bgra<u1_t>	cbgra16;
	typedef cnst color_rgba<u1_t>	crgba16;
	typedef cnst color_abgr<u1_t>	cabgr16;
	typedef cnst color_argb<u1_t>	cargb16;

	typedef cnst color_bgr <f2_t>	cbgrf32;
	typedef cnst color_rgb <f2_t>	crgbf32;
	typedef cnst color_bgra<f2_t>	cbgraf32;
	typedef cnst color_rgba<f2_t>	crgbaf32;
	typedef cnst color_abgr<f2_t>	cabgrf32;
	typedef cnst color_argb<f2_t>	cargbf32;

	cxpr	f2_c			BYTE_SCALE			= 1.0f / 255.0f;

	// Stores RGBA color channels
	struct SColorRGBA : public ::llc::rgba8 {
								SColorRGBA		()									nxpt	= default;
		cxpr					SColorRGBA		(cnst SColorRGBA &)				nxpt	= default;
		cxpr					SColorRGBA		(u0_t r_, u0_t g_, u0_t b_, u0_t a_=0xff)	nxpt	: color_rgba<u0_t>{{{{r_}, g_}, b_}, a_}						{}
		cxpr					SColorRGBA		(u2_t other)					nxpt	: color_rgba<u0_t>
			{ {{{u0_t(((other & 0x000000FF) >>  0))}
			, u0_t(((other & 0x0000FF00) >>  8))	 }
			, u0_t(((other & 0x00FF0000) >> 16))	 }
			, u0_t(((other & 0xFF000000) >> 24))
			}
		{}

		COLOR_RGBA_OPERATOR_MEMBERS(SColorRGBA); 
		cxpr	operator		u2_t		()							cnstnxpt	{ return (((u2_t)a) << 24) | (((u2_t)b) << 16) | (((u2_t)g) << 8) | (((u2_t)r) << 0);					}


		cxpr	bool			operator ==		(u2_t other)			cnstnxpt	{ return other == *((cnst u2_t*)this);			}
		cxpr	SColorRGBA		operator *		(cnst SColorRGBA & color)	cnstnxpt	{ return {(u0_t)::llc::clamped(r * (int)color.r, 0, 255)	, (u0_t)::llc::clamped(g * (int)color.g, 0, 255), (u0_t)::llc::clamped(b * (int)color.b, 0, 255), a};	}
		cxpr	SColorRGBA		operator +		(cnst SColorRGBA & color)	cnstnxpt	{ return {(u0_t)::llc::clamped(r + (int)color.r, 0, 255)	, (u0_t)::llc::clamped(g + (int)color.g, 0, 255), (u0_t)::llc::clamped(b + (int)color.b, 0, 255), a};	}
		cxpr	SColorRGBA		operator *		(f3_t scalar)				cnstnxpt	{ return {(u0_t)::llc::clamped(r * scalar, 0.0 , 255.0)		, (u0_t)::llc::clamped(g * scalar, 0.0,   255.0), (u0_t)::llc::clamped(b * scalar, 0.0,   255.0), a};	}
		cxpr	SColorRGBA		operator /		(f3_t scalar)				cnst				{ return {(u0_t)::llc::clamped(r / scalar, 0.0 , 255.0)		, (u0_t)::llc::clamped(g / scalar, 0.0,   255.0), (u0_t)::llc::clamped(b / scalar, 0.0,   255.0), a};	}
	};	// struct

	// Stores BGRA color channels
	struct SColorBGRA : public ::llc::bgra8 {
								SColorBGRA		()									nxpt	= default;
		cxpr					SColorBGRA		(cnst SColorBGRA &)				nxpt	= default;
		cxpr					SColorBGRA		(cnst SColorRGBA & other)			nxpt	: color_bgra<u0_t>{{{{other.b}, other.g}, other.r}, other.a} {}
		cxpr					SColorBGRA		(u0_t b_, u0_t g_, u0_t r_, u0_t a_=0xff)	nxpt	: color_bgra<u0_t>{{{{b_}, g_}, r_}, a_} {}
		cxpr					SColorBGRA		(u2_t other)					nxpt	: color_bgra<u0_t>
			{ {{{u0_t(((other & 0x000000FF) >>  0)) }
			, u0_t(((other & 0x0000FF00) >>  8))	  }
			, u0_t(((other & 0x00FF0000) >> 16))	  }
			, u0_t(((other & 0xFF000000) >> 24))
			}
		{}

		COLOR_RGBA_OPERATOR_MEMBERS(SColorBGRA); 
		cxpr	operator		SColorRGBA		()							cnstnxpt	{ return {r, g, b, a};						}
		cxpr	operator		u2_t		()							cnstnxpt	{ return (((u2_t)a) << 24) | (((u2_t)r) << 16) | (((u2_t)g) << 8) | (((u2_t)b) << 0);					}

		cxpr	bool			operator==		(u2_t other)			cnstnxpt	{ return other == *((cnst u2_t*)this);			}
		cxpr	SColorBGRA		operator*		(cnst SColorBGRA & color)	cnstnxpt	{ return {(u0_t)::llc::min(b * (int)color.b, 255)	, (u0_t)::llc::min(g * (int)color.g, 255)	,(u0_t)::llc::min(r * (int)color.r, 255), a};			}
		cxpr	SColorBGRA		operator+		(cnst SColorBGRA & color)	cnstnxpt	{ return {(u0_t)::llc::min(b + (int)color.b, 255)	, (u0_t)::llc::min(g + (int)color.g, 255)	,(u0_t)::llc::min(r + (int)color.r, 255), a};			}
		cxpr	SColorBGRA		operator-		(cnst SColorBGRA & color)	cnstnxpt	{ return {(u0_t)::llc::clamped(b - (int16_t)color.b, 0, 255), (u0_t)::llc::clamped(g - (int16_t)color.g, 0, 255),(u0_t)::llc::clamped(r - (int16_t)color.r, 0, 255), a};	}
		cxpr	SColorBGRA		operator*		(f2_t scalar)				cnstnxpt	{ return {(u0_t)::llc::clamped(b * scalar, 0.0f, 255.0f)	, (u0_t)::llc::clamped(g * scalar, 0.0f, 255.0f)	,(u0_t)::llc::clamped(r * scalar, 0.0f, 255.0f), a};			}
		cxpr	SColorBGRA		operator/		(f2_t scalar)				cnst				{ return {(u0_t)::llc::clamped(b / scalar, 0.0f, 255.0f)	, (u0_t)::llc::clamped(g / scalar, 0.0f, 255.0f)	,(u0_t)::llc::clamped(r / scalar, 0.0f, 255.0f), a};			}
		cxpr	SColorBGRA		operator*		(f3_t scalar)				cnstnxpt	{ return {(u0_t)::llc::clamped(b * scalar, 0.0,  255.0 )	, (u0_t)::llc::clamped(g * scalar, 0.0 , 255.0 )	,(u0_t)::llc::clamped(r * scalar, 0.0, 255.0),	a};				}
		cxpr	SColorBGRA		operator/		(f3_t scalar)				cnst				{ return {(u0_t)::llc::clamped(b / scalar, 0.0,  255.0 )	, (u0_t)::llc::clamped(g / scalar, 0.0 , 255.0 )	,(u0_t)::llc::clamped(r / scalar, 0.0, 255.0),	a};				}
				SColorBGRA&		operator*=		(f2_t scalar)						nxpt	{ b = (u0_t)::llc::clamped(b * scalar, 0.0f, 255.0f); g = (u0_t)::llc::clamped(g * scalar, 0.0f, 255.0f); r = (u0_t)::llc::clamped(r * scalar, 0.0f, 255.0f);	return *this; }
				SColorBGRA&		operator/=		(f2_t scalar)									{ b = (u0_t)::llc::clamped(b / scalar, 0.0f, 255.0f); g = (u0_t)::llc::clamped(g / scalar, 0.0f, 255.0f); r = (u0_t)::llc::clamped(r / scalar, 0.0f, 255.0f);	return *this; }
				SColorBGRA&		operator*=		(f3_t scalar)						nxpt	{ b = (u0_t)::llc::clamped(b * scalar, 0.0,  255.0 ); g = (u0_t)::llc::clamped(g * scalar, 0.0 , 255.0 ); r = (u0_t)::llc::clamped(r * scalar, 0.0, 255.0);		return *this; }
				SColorBGRA&		operator/=		(f3_t scalar)									{ b = (u0_t)::llc::clamped(b / scalar, 0.0,  255.0 ); g = (u0_t)::llc::clamped(g / scalar, 0.0 , 255.0 ); r = (u0_t)::llc::clamped(r / scalar, 0.0, 255.0);		return *this; }

				SColorBGRA&		FromBGR16		(cnst SColor16 & other)			nxpt	{ b = u0_t((other & 0x1F) / f2_t(0x1F) * 255); g = u0_t(((other & 0x07E0) >> 5) / f2_t(0x3F) * 255); r = u0_t(((other & 0xF800) >> 11) / f2_t(0x1F) * 255);	return *this; }
				SColorBGRA&		FromRGB16		(cnst SColor16 & other)			nxpt	{ r = u0_t((other & 0x1F) / f2_t(0x1F) * 255); g = u0_t(((other & 0x07E0) >> 5) / f2_t(0x3F) * 255); b = u0_t(((other & 0xF800) >> 11) / f2_t(0x1F) * 255);	return *this; }
	};	// struct

	// Stores RGB color channels
	struct SColorRGB : public ::llc::rgb8 {
								SColorRGB		()									nxpt	= default;
		cxpr					SColorRGB		(cnst SColorRGB & other)			nxpt	= default;
		cxpr					SColorRGB		(u0_t r_, u0_t g_, u0_t b_)				nxpt	: color_rgb<u0_t>{{{r_}, g_}, b_} {}
		cxpr					SColorRGB		(u2_t other)					nxpt	: color_rgb<u0_t>
			{ {{u0_t(((other & 0x000000FF) >>  0))}
			, u0_t(((other & 0x0000FF00) >>  8))	}
			, u0_t(((other & 0x00FF0000) >> 16))
			}
		{}

		COLOR_RGB_OPERATOR_MEMBERS(SColorRGB); 
		cxpr	operator		u2_t		()							cnstnxpt	{ return  0xFF000000 | (((u2_t)b) << 16) | (((u2_t)g) << 8)	| (((u2_t)r) << 0);  }
		cxpr	operator		SColorRGBA		()							cnstnxpt	{ return {0xFF000000 | (((u2_t)b) << 16) | (((u2_t)g) << 8)	| (((u2_t)r) << 0)}; }
		cxpr	operator		SColor16		()							cnstnxpt	{ return (((u1_t)(r * BYTE_SCALE * 0x001F)) << 0) | (((u1_t)(g * BYTE_SCALE * 0x003F)) << 5) | (((u1_t)(b * BYTE_SCALE * 0x001F)) << 11 );												}
		cxpr	bool			operator ==		(cnst SColorRGBA & other)	cnstnxpt	{ return r == other.r && g == other.g && b == other.b;	}
		cxpr	bool			operator !=		(cnst SColorRGBA & other)	cnstnxpt	{ return r != other.r || g != other.g || b != other.b;	}
		cxpr	bool			operator ==		(cnst SColor16   & other)	cnstnxpt	{ return (SColor16)(*this) == other;					}
		cxpr	bool			operator !=		(cnst SColor16   & other)	cnstnxpt	{ return (SColor16)(*this) != other;					}
		cxpr	SColorRGB		operator *		(f2_t scalar)				cnstnxpt	{ return {(u0_t)::llc::clamped(r * scalar, 0.0f, 255.0f), (u0_t)::llc::clamped(g * scalar, 0.0f, 255.0f),	(u0_t)::llc::clamped(b * scalar, 0.0f, 255.0f)}; }
		cxpr	SColorRGB		operator /		(f2_t scalar)				cnst				{ return {(u0_t)::llc::clamped(r / scalar, 0.0f, 255.0f), (u0_t)::llc::clamped(g / scalar, 0.0f, 255.0f),	(u0_t)::llc::clamped(b / scalar, 0.0f, 255.0f)}; }
		cxpr	SColorRGB		operator *		(f3_t scalar)				cnstnxpt	{ return {(u0_t)::llc::clamped(r * scalar, 0.0,  255.0),  (u0_t)::llc::clamped(g * scalar, 0.0,  255.0),	(u0_t)::llc::clamped(b * scalar, 0.0,  255.0)};  }
		cxpr	SColorRGB		operator /		(f3_t scalar)				cnst				{ return {(u0_t)::llc::clamped(r / scalar, 0.0,  255.0),  (u0_t)::llc::clamped(g / scalar, 0.0,  255.0),	(u0_t)::llc::clamped(b / scalar, 0.0,  255.0)};  }
		cxpr	SColorRGB		operator *		(cnst SColorRGB  & color)	cnstnxpt	{ return {(u0_t)::llc::clamped(r * (int)color.r, 0, 255), (u0_t)::llc::clamped(g * (int)color.g, 0, 255), (u0_t)::llc::clamped(b * (int)color.b, 0, 255)};			}
		cxpr	SColorRGB		operator +		(cnst SColorRGB  & color)	cnstnxpt	{ return {(u0_t)::llc::clamped(r + (int)color.r, 0, 255), (u0_t)::llc::clamped(g + (int)color.g, 0, 255), (u0_t)::llc::clamped(b + (int)color.b, 0, 255)};			}
		cxpr	SColorRGBA		operator *		(cnst SColorRGBA & color)	cnstnxpt	{ return {(u0_t)::llc::clamped(r * (int)color.r, 0, 255), (u0_t)::llc::clamped(g * (int)color.g, 0, 255), (u0_t)::llc::clamped(b * (int)color.b, 0, 255), color.a};	}
		cxpr	SColorRGBA		operator +		(cnst SColorRGBA & color)	cnstnxpt	{ return {(u0_t)::llc::clamped(r + (int)color.r, 0, 255), (u0_t)::llc::clamped(g + (int)color.g, 0, 255), (u0_t)::llc::clamped(b + (int)color.b, 0, 255), color.a};	}
	};	// struct

	// Stores BGR color channels
	struct SColorBGR : public ::llc::color_bgr<u0_t> {
								SColorBGR		()									nxpt	= default;
		cxpr					SColorBGR		(cnst SColorBGR & other)			nxpt	= default;
		cxpr					SColorBGR		(u0_t b_, u0_t g_, u0_t r_)				nxpt	: color_bgr<u0_t>{{{b_}, g_}, r_} {}
		cxpr					SColorBGR		(u2_t other)					nxpt	: color_bgr<u0_t>
			{ {{u0_t(((other & 0x000000FF) >>  0))}
			, u0_t(((other & 0x0000FF00) >>  8))	}
			, u0_t(((other & 0x00FF0000) >> 16))
			}
		{}
		COLOR_RGB_OPERATOR_MEMBERS(SColorBGR); 
		cxpr	operator		u2_t			()							cnstnxpt	{ return 0xFF000000 | (((u2_t)r) << 16)	| (((u2_t)g) << 8) | (((u2_t)b) << 0);																	}
		cxpr	operator		SColorBGRA		()							cnstnxpt	{ return {b, g, r, 0xFF};														}
		cxpr	operator		SColor16		()							cnstnxpt	{ return (((u1_t)(b * BYTE_SCALE * 0x001F)) << 0) | (((u1_t)(g * BYTE_SCALE * 0x003F)) << 5) | (((u1_t)(r * BYTE_SCALE * 0x001F)) << 11 );	}

		cxpr	bool			operator ==		(cnst SColorBGRA & other)	cnstnxpt	{ return r == other.r && g == other.g && b == other.b;	}
		cxpr	bool			operator !=		(cnst SColorBGRA & other)	cnstnxpt	{ return r != other.r || g != other.g || b != other.b;	}
		cxpr	bool			operator ==		(cnst SColor16   & other)	cnstnxpt	{ return (SColor16)(*this) == other;					}
		cxpr	bool			operator !=		(cnst SColor16   & other)	cnstnxpt	{ return (SColor16)(*this) != other;					}
		cxpr	SColorBGR		operator *		(f2_t scalar)				cnstnxpt	{ return {(u0_t)::llc::clamped(b * scalar, 0.0f, 255.0f), (u0_t)::llc::clamped(g * scalar, 0.0f, 255.0f), (u0_t)::llc::clamped(r * scalar, 0.0f, 255.0f)};	}
		cxpr	SColorBGR		operator /		(f2_t scalar)				cnst				{ return {(u0_t)::llc::clamped(b / scalar, 0.0f, 255.0f), (u0_t)::llc::clamped(g / scalar, 0.0f, 255.0f), (u0_t)::llc::clamped(r / scalar, 0.0f, 255.0f)};	}
		cxpr	SColorBGR		operator *		(f3_t scalar)				cnstnxpt	{ return {(u0_t)::llc::clamped(b * scalar, 0.0,  255.0) , (u0_t)::llc::clamped(g * scalar, 0.0,  255.0) , (u0_t)::llc::clamped(r * scalar, 0.0,  255.0)};	}
		cxpr	SColorBGR		operator /		(f3_t scalar)				cnst				{ return {(u0_t)::llc::clamped(b / scalar, 0.0,  255.0) , (u0_t)::llc::clamped(g / scalar, 0.0,  255.0) , (u0_t)::llc::clamped(r / scalar, 0.0,  255.0)};	}
		cxpr	SColorBGR		operator *		(cnst SColorBGR  & color)	cnstnxpt	{ return {(u0_t)::llc::clamped(b * (int)color.b, 0, 255) , (u0_t)::llc::clamped(g * (int)color.g, 0, 255)	, (u0_t)::llc::clamped(r * (int)color.r, 0, 255)};			}
		cxpr	SColorBGR		operator +		(cnst SColorBGR  & color)	cnstnxpt	{ return {(u0_t)::llc::clamped(b + (int)color.b, 0, 255) , (u0_t)::llc::clamped(g + (int)color.g, 0, 255)	, (u0_t)::llc::clamped(r + (int)color.r, 0, 255)};			}
		cxpr	SColorBGRA		operator *		(cnst SColorBGRA & color)	cnstnxpt	{ return {(u0_t)::llc::clamped(b * (int)color.b, 0, 255) , (u0_t)::llc::clamped(g * (int)color.g, 0, 255)	, (u0_t)::llc::clamped(r * (int)color.r, 0, 255), color.a};	}
		cxpr	SColorBGRA		operator +		(cnst SColorBGRA & color)	cnstnxpt	{ return {(u0_t)::llc::clamped(b + (int)color.b, 0, 255) , (u0_t)::llc::clamped(g + (int)color.g, 0, 255)	, (u0_t)::llc::clamped(r + (int)color.r, 0, 255), color.a};	}

				SColorBGR&		FromBGR16		(cnst SColor16   & other)			nxpt	{ b = u0_t((other & 0x1F) / f2_t(0x1F) * 255); g = u0_t(((other & 0x07E0) >> 5) / f2_t(0x3F) * 255); r = u0_t(((other & 0xF800) >> 11) / f2_t(0x1F) * 255);	return *this; }
				SColorBGR&		FromRGB16		(cnst SColor16   & other)			nxpt	{ r = u0_t((other & 0x1F) / f2_t(0x1F) * 255); g = u0_t(((other & 0x07E0) >> 5) / f2_t(0x3F) * 255); b = u0_t(((other & 0xF800) >> 11) / f2_t(0x1F) * 255);	return *this; }
	};	// struct

	// Stores RGBA f2_ting point color channels
	struct SColorFloat : public ::llc::rgbaf32 {
								SColorFloat		()										nxpt	= default;
		cxpr					SColorFloat		(cnst SColorFloat & color)				nxpt	= default;
		cxpr					SColorFloat		(f2_t r_, f2_t g_, f2_t b_, f2_t a_=1.0f)	nxpt	: color_rgba<f2_t>{{{{r_}, g_}, b_}, a_}						{}
		cxpr					SColorFloat		(cnst f2_t* rgbaColor)							: color_rgba<f2_t>{{{{rgbaColor[0]}, rgbaColor[1]}, rgbaColor[2]}, rgbaColor[3]}	{}
		cxpr					SColorFloat		(SColorBGRA color)						nxpt	: color_rgba<f2_t>
			{ {{{color.r * BYTE_SCALE}
			, color.g * BYTE_SCALE	 }
			, color.b * BYTE_SCALE	 }
			, color.a * BYTE_SCALE
			} {}
		cxpr					SColorFloat		(::llc::bgr8 color, uint8_t alpha)		nxpt	: color_rgba<f2_t>
			{ {{{color.r * BYTE_SCALE}
			, color.g * BYTE_SCALE	 }
			, color.b * BYTE_SCALE	 }
			, alpha * BYTE_SCALE
			} {}
		cxpr					SColorFloat		(::llc::rgbf32 color, f2_t alpha)		nxpt	: color_rgba<f2_t>
			{ {{{color.r }
			, color.g }
			, color.b }
			, alpha 
			} {}
		COLOR_RGBA_OPERATOR_MEMBERS(SColorFloat); 
		cxpr	operator		SColorBGRA		()							cnstnxpt	{ return {u0_t(b * 255), u0_t(g * 255), u0_t(r * 255), u0_t(a * 255)};	}
		cxpr	operator		cnst f2_t*	()							cnstnxpt	{ return &r;															}
				SColorFloat&	operator +=		(cnst SColorFloat & color)			nxpt	{ r = r + color.r;					g = g + color.g;				b = b + color.b;				return *this;	}
				SColorFloat&	operator *=		(cnst SColorFloat & color)			nxpt	{ r = r * color.r;					g = g * color.g;				b = b * color.b;				return *this;	}
				SColorFloat&	operator *=		(f3_t scalar)						nxpt	{ r = (f2_t)(r * scalar);			g = (f2_t)(g * scalar);		b = (f2_t)(b * scalar);		return *this;	}
				SColorFloat&	operator /=		(f3_t scalar)									{ r = (f2_t)(r / scalar);			g = (f2_t)(g / scalar);		b = (f2_t)(b / scalar);		return *this;	}
				SColorFloat&	operator *=		(f2_t scalar)						nxpt	{ r = r * scalar;					g = g * scalar;					b = b * scalar;					return *this;	}
				SColorFloat&	operator /=		(f2_t scalar)									{ r = r / scalar;					g = g / scalar;					b = b / scalar;					return *this;	}
				SColorFloat&	operator *=		(cnst SColorBGRA  & color)			nxpt	{ r = r * (color.r * BYTE_SCALE);	g = g * (color.g * BYTE_SCALE);	b = b * (color.b * BYTE_SCALE);	return *this;	}
				SColorFloat&	operator +=		(cnst SColorBGRA  & color)			nxpt	{ r = r + (color.r * BYTE_SCALE);	g = g + (color.g * BYTE_SCALE);	b = b + (color.b * BYTE_SCALE);	return *this;	}
				SColorFloat&	operator *=		(cnst SColorBGR   & color)			nxpt	{ r = r * (color.r * BYTE_SCALE);	g = g * (color.g * BYTE_SCALE);	b = b * (color.b * BYTE_SCALE);	return *this;	}
				SColorFloat&	operator +=		(cnst SColorBGR   & color)			nxpt	{ r = r + (color.r * BYTE_SCALE);	g = g + (color.g * BYTE_SCALE);	b = b + (color.b * BYTE_SCALE);	return *this;	}
				SColorFloat		operator *		(cnst SColorBGRA  & color)	cnstnxpt	{ return {r * (color.r * BYTE_SCALE), g * (color.g * BYTE_SCALE), b * (color.b * BYTE_SCALE), a};	}
				SColorFloat		operator +		(cnst SColorBGRA  & color)	cnstnxpt	{ return {r + (color.r * BYTE_SCALE), g + (color.g * BYTE_SCALE), b + (color.b * BYTE_SCALE), a};	}
				SColorFloat		operator *		(cnst SColorBGR   & color)	cnstnxpt	{ return {r * (color.r * BYTE_SCALE), g * (color.g * BYTE_SCALE), b * (color.b * BYTE_SCALE), a};	}
				SColorFloat		operator +		(cnst SColorBGR   & color)	cnstnxpt	{ return {r + (color.r * BYTE_SCALE), g + (color.g * BYTE_SCALE), b + (color.b * BYTE_SCALE), a};	}
		cxpr	SColorFloat		operator *		(cnst SColorFloat & color)	cnstnxpt	{ return {r * color.r, g * color.g, b * color.b, a};												}
		cxpr	SColorFloat		operator +		(cnst SColorFloat & color)	cnstnxpt	{ return {r + color.r, g + color.g, b + color.b, a};												}
		cxpr	SColorFloat		operator -		(cnst SColorFloat & color)	cnstnxpt	{ return {r - color.r, g - color.g, b - color.b, a};												}
		cxpr	SColorFloat		operator *		(f3_t scalar)				cnstnxpt	{ return {(f2_t)(r * scalar), (f2_t)(g * scalar), (f2_t)(b * scalar), a};						}
		cxpr	SColorFloat		operator *		(f2_t scalar)				cnstnxpt	{ return {(r * scalar), (g * scalar),	(b * scalar)};												}
		cxpr	SColorFloat		operator /		(f3_t scalar)				cnst				{ return {(f2_t)(r / scalar), (f2_t)(g / scalar), (f2_t)(b / scalar), a};						}
		cxpr	SColorFloat		operator /		(f2_t scalar)				cnst				{ return {r / scalar,	g / scalar,	b / scalar};													}

				SColorFloat&	Clamp			()									nxpt	{ r = ::llc::clamped(r, 0.0f, 1.0f); g = ::llc::clamped(g, 0.0f, 1.0f); b = ::llc::clamped(b, 0.0f, 1.0f); return *this;	}

		cxpr	::llc::rgbf32	rgb				()							cnst				{ return {{{r}, g}, b}; }
	};	// struct

	typedef ::llc::SColorFloat					frgba	;
	typedef ::llc::SColorBGRA					u8bgra	;
	typedef ::llc::SColorBGR					u8bgr	;
	typedef ::llc::SColorRGBA					u8rgba	;
	typedef ::llc::SColorRGB					u8rgb	;

	typedef cnst frgba							cfrgba	;
	typedef cnst u8bgra						c8bgra	;
	typedef cnst u8bgr							c8bgr	;
	typedef cnst u8rgba						c8rgba	;
	typedef cnst u8rgb							c8rgb	;

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
