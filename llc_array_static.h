#include "llc_cpow.h"
#include "llc_view.h"

#ifndef LLC_ARRAY_STATIC_H_23627
#define LLC_ARRAY_STATIC_H_23627

namespace llc
{
#pragma pack(push, 1)
	tplt<tpnm _tVal, u2_t N>
	stct array_static	{
		stxp	u2_c				SIZE	= N;
		tydf	_tVal				T;
		tdcs	T					TCnst;
		tydf	array_static<T, N>	TAStatic;
		tydf	view<TCnst>			VCnst;
		tydf	view<T>				V;
		T		Storage	[N]			;

		inln	oper		view<T>			()								{ return {Storage, SIZE}; }
		inxp	oper		view<TCnst>		()						csnx	{ return {Storage, SIZE}; }

		inln	TCnst&		oper[]			(u2_t index)			cnst	{ gthrow_if(index >= N, LLC_FMT_GE_U2, (s2_t)index, (s2_t)N); return Storage[index]; }
		inln	T&			oper[]			(u2_t index)					{ gthrow_if(index >= N, LLC_FMT_GE_U2, (s2_t)index, (s2_t)N); return Storage[index]; }
		LLC_DEFAULT_OPERATOR(TAStatic
			, (this->size() != other.size()) ? false
			: (this->begin() == other.begin()) ? true
			: ::llc::equal(other.begin(), this->begin(), this->size())
			);
		inxp	u2_t		byte_count		()						csnx	{ rtrn N * szof(T);	}
		inxp	u2_t		bit_count		()						csnx	{ rtrn byte_count() * 8U;	}
		inln	view<u0_t>	u8				()						nxpt	{ rtrn {(u0_t*)Storage, byte_count()};		}
		inxp	view<u0_c>	u8				()						csnx	{ rtrn {(u0_c*)Storage, byte_count()};	}
		inxp	view<u0_c>	cu8				()						csnx	{ rtrn {(u0_c*)Storage, byte_count()};	}
		inln	view<sc_t>	c				()						nxpt	{ rtrn {(sc_t*)Storage, byte_count()};			}
		inxp	view<sc_c>	cc				()						csnx	{ rtrn {(sc_c*)Storage, byte_count()};		}
		inxp	u2_c&		size			()						csnx	{ rtrn N; }
		inln	T*			begin			()						nxpt	{ rtrn Storage;			}
		inln	T*			end				()						nxpt	{ rtrn Storage + N;	}
		inxp	TCnst*		begin			()						csnx	{ rtrn Storage;			}
		inxp	TCnst*		end				()						csnx	{ rtrn Storage + N;	}

		err_t				slice			(V & out, u2_t offset, u2_t count = (u2_t)-1)				{
			ree_if(offset > N, LLC_FMT_GT_U2, offset, N);
			u2_c					newSize			= N - offset;
			if(count != (u2_t)-1)
				ree_if(count > newSize, LLC_FMT_GT_U2, count, newSize);
			out						= {&Storage[offset], ::llc::min(newSize, count)};
			return out.size();
		}
		err_t				slice			(VCnst & out, u2_t offset, u2_t count = (u2_t)-1)	cnst	{
			ree_if(offset > N, LLC_FMT_GT_U2, offset, N);
			u2_c					newSize			= N - offset;
			if(count != (u2_t)-1)
				ree_if(count > newSize, LLC_FMT_GT_U2, count, newSize);
			out						= {&Storage[offset], ::llc::min(newSize, count)};
			return out.size();
		}
	};
#pragma pack(pop)

	tplTN2	usng astatic	= ::llc::array_static<T, N>;

	tplN2u	usng astvcs		= ::llc::astatic<::llc::vcs	, N>;	tplN2u	usng astaticvcs	= ::llc::astvcs	<N>;
	tplN2u	usng astvs		= ::llc::astatic<::llc::vs	, N>;	tplN2u	usng astaticvs		= ::llc::astvs	<N>;

	tplN2u	usng astuc_t	= ::llc::astatic<uc_t, N>; tplN2u	usng astuc 	= ::llc::astatic<uc_t, N>; tplN2u	usng astaticuc 	= ::llc::astuc 	<N>; tplN2u	usng astuchar	= ::llc::astatic<uc_t, N>;
	tplN2u	usng astsc_t	= ::llc::astatic<sc_t, N>; tplN2u	usng astc	= ::llc::astatic<sc_t, N>; tplN2u	usng astaticc		= ::llc::astc	<N>; tplN2u	usng astchar	= ::llc::astatic<sc_t, N>;
	tplN2u	usng astu0_t	= ::llc::astatic<u0_t, N>; tplN2u	usng astu8 	= ::llc::astatic<u0_t, N>; tplN2u	usng astaticu8 	= ::llc::astu8 	<N>;
	tplN2u	usng astu1_t	= ::llc::astatic<u1_t, N>; tplN2u	usng astu16	= ::llc::astatic<u1_t, N>; tplN2u	usng astaticu16	= ::llc::astu16	<N>;
	tplN2u	usng astu2_t	= ::llc::astatic<u2_t, N>; tplN2u	usng astu32	= ::llc::astatic<u2_t, N>; tplN2u	usng astaticu32	= ::llc::astu32	<N>;
	tplN2u	usng astu3_t	= ::llc::astatic<u3_t, N>; tplN2u	usng astu64	= ::llc::astatic<u3_t, N>; tplN2u	usng astaticu64	= ::llc::astu64	<N>;
	tplN2u	usng asts0_t	= ::llc::astatic<s0_t, N>; tplN2u	usng asti8 	= ::llc::astatic<s0_t, N>; tplN2u	usng astatici8 	= ::llc::asti8 	<N>;
	tplN2u	usng asts1_t	= ::llc::astatic<s1_t, N>; tplN2u	usng asti16	= ::llc::astatic<s1_t, N>; tplN2u	usng astatici16	= ::llc::asti16	<N>;
	tplN2u	usng asts2_t	= ::llc::astatic<s2_t, N>; tplN2u	usng asti32	= ::llc::astatic<s2_t, N>; tplN2u	usng astatici32	= ::llc::asti32	<N>;
	tplN2u	usng asts3_t	= ::llc::astatic<s3_t, N>; tplN2u	usng asti64	= ::llc::astatic<s3_t, N>; tplN2u	usng astatici64	= ::llc::asti64	<N>;
	tplN2u	usng astf2_t	= ::llc::astatic<f2_t, N>; tplN2u	usng astf32	= ::llc::astatic<f2_t, N>; tplN2u	usng astaticf32	= ::llc::astf32	<N>;
	tplN2u	usng astf3_t	= ::llc::astatic<f3_t, N>; tplN2u	usng astf64	= ::llc::astatic<f3_t, N>; tplN2u	usng astaticf64	= ::llc::astf64	<N>;

	tplN2u	usng astvcuc 	= ::llc::astatic<::llc::vcuc 	, N>; tplN2u	usng astaticvcuc 	= ::llc::astvcuc <N>;
	tplN2u	usng astvcc		= ::llc::astatic<::llc::vcc		, N>; tplN2u	usng astaticvcc		= ::llc::astvcc  <N>;
	tplN2u	usng astvcu8 	= ::llc::astatic<::llc::vcu0_t 	, N>; tplN2u	usng astaticvcu8 	= ::llc::astvcu8 <N>;
	tplN2u	usng astvcu16	= ::llc::astatic<::llc::vcu16	, N>; tplN2u	usng astaticvcu16	= ::llc::astvcu16<N>;
	tplN2u	usng astvcu32	= ::llc::astatic<::llc::vcu32	, N>; tplN2u	usng astaticvcu32	= ::llc::astvcu32<N>;
	tplN2u	usng astvcu64	= ::llc::astatic<::llc::vcu64	, N>; tplN2u	usng astaticvcu64	= ::llc::astvcu64<N>;
	tplN2u	usng astvci8 	= ::llc::astatic<::llc::vcs0_t 	, N>; tplN2u	usng astaticvci8 	= ::llc::astvci8 <N>;
	tplN2u	usng astvci16	= ::llc::astatic<::llc::vci16	, N>; tplN2u	usng astaticvci16	= ::llc::astvci16<N>;
	tplN2u	usng astvci32	= ::llc::astatic<::llc::vci32	, N>; tplN2u	usng astaticvci32	= ::llc::astvci32<N>;
	tplN2u	usng astvci64	= ::llc::astatic<::llc::vci64	, N>; tplN2u	usng astaticvci64	= ::llc::astvci64<N>;
	tplN2u	usng astvcf32	= ::llc::astatic<::llc::vcf32	, N>; tplN2u	usng astaticvcf32	= ::llc::astvcf32<N>;
	tplN2u	usng astvcf64	= ::llc::astatic<::llc::vcf64	, N>; tplN2u	usng astaticvcf64	= ::llc::astvcf64<N>;

	tplt <tpnm T, size_t nSize>	sinx	u2_t	size		(::llc::astatic<T, nSize> /*viewToTest*/)	nxpt	{ return u2_t(nSize);				}
	tplt <tpnm T, size_t nSize>	sinx	u2_t	byte_count	(::llc::astatic<T, nSize> viewToTest)		nxpt	{ return u2_t(sizeof(T) * nSize);	}

	// Is this really worth it?
	tplN2u	sinx	u2_t	size(astc	<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	//tplN2u	sinx	u2_t	size(astuc 	<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(astu8 	<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(astu16	<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(astu32	<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(astu64	<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(asti8 	<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(asti16	<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(asti32	<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(asti64	<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(astf32	<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(astf64	<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }

	tplN2u	sinx	u2_t	size(astvcc	 <N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	//tplN2u	sinx	u2_t	size(astvcuc <N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(astvcu8 <N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(astvcu16<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(astvcu32<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(astvcu64<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(astvci8 <N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(astvci16<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(astvci32<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(astvci64<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(astvcf32<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }
	tplN2u	sinx	u2_t	size(astvcf64<N> /*viewToTest*/)	nxpt	{ return u2_t(N); }

	tplt<tpnm T, size_t _nSize>
	err_t			find		(cnst T & element, cnst ::llc::astatic<cnst T, _nSize>& target, u2_t offset = 0)	{
		return ::llc::find(element, ::llc::view<cnst T>{target}, offset);
	}
	stin llc::astchar< 7>	str			(u1_t arg) { llc::astchar< 7> dest = {}; sprintf_s(dest.Storage, "%u" , arg); return dest; } 
	stin llc::astchar<12>	str			(u2_t arg) { llc::astchar<12> dest = {}; sprintf_s(dest.Storage, "%" LLC_FMT_U2, arg); return dest; } 
	stin llc::astchar<22>	str			(u3_t arg) { llc::astchar<22> dest = {}; sprintf_s(dest.Storage, "%" LLC_FMT_U3, arg); return dest; } 
	stin llc::astchar< 7>	str			(s1_t arg) { llc::astchar< 7> dest = {}; sprintf_s(dest.Storage, "%i", arg); return dest; } 
	stin llc::astchar<12>	str			(s2_t arg) { llc::astchar<12> dest = {}; sprintf_s(dest.Storage, "%" LLC_FMT_S2, arg); return dest; } 
	stin llc::astchar<22>	str			(s3_t arg) { llc::astchar<22> dest = {}; sprintf_s(dest.Storage, "%" LLC_FMT_U3, arg); return dest; } 
	stin llc::astchar<12>	str			(f2_t arg) { llc::astchar<12> dest = {}; sprintf_s(dest.Storage, "%f", arg); return dest; } 
	stin llc::astchar<22>	str			(f3_t arg) { llc::astchar<22> dest = {}; sprintf_s(dest.Storage, "%f", arg); return dest; } 
	stxp	llc::astchar<5 >	str			(u0_t arg) { 
		return (arg >= 100) ?	llc::astchar<5>{digit<2>(arg), digit<1>(arg), digit<0>(arg), 0}
			:  (arg >=  10) ?	llc::astchar<5>{digit<1>(arg), digit<0>(arg), 0}
			:					llc::astchar<5>{digit<0>(arg), 0}
			;
	}
	stxp	llc::astchar<5 >	str			(s0_t arg) { 
		return	(arg >=    0) ?	str(u0_t(arg))
			:	(arg <= -100) ?	llc::astchar<5>{'-', digit<2>((int16_t)-arg), digit<1>((int16_t)-arg), digit<0>((int16_t)-arg)}
			:	(arg <=  -10) ?	llc::astchar<5>{'-', digit<1>((int16_t)-arg), digit<0>((int16_t)-arg)}
			:					llc::astchar<5>{'-', digit<0>((int16_t)-arg)}
			;
	}
} // namespace

#endif // LLC_ARRAY_STATIC_H_23627
