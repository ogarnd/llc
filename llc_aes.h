#include "llc_enum.h"

#ifndef LLC_AES_H_23627
#define LLC_AES_H_23627

namespace llc
{
	GDEFINE_ENUM_TYPE(AES_LEVEL, uint8_t);
	GDEFINE_ENUM_VALUE(AES_LEVEL, 128, 0);
	GDEFINE_ENUM_VALUE(AES_LEVEL, 192, 1);
	GDEFINE_ENUM_VALUE(AES_LEVEL, 256, 2);

	GDEFINE_ENUM_TYPE(AES_MODE, uint8_t);
	GDEFINE_ENUM_VALUE(AES_MODE, ECB, 0);
	GDEFINE_ENUM_VALUE(AES_MODE, CBC, 1);
	GDEFINE_ENUM_VALUE(AES_MODE, CTR, 2);

#pragma pack(push, 1)
	struct SAESLevelProperties {
		int32_t						KeyLength ;
		int32_t						KeyExpSize;
	};
#pragma pack(pop)

	stacxpr	SAESLevelProperties	AES_LEVEL_PROPERTIES	[3]		=
		{ {16, 176}
		, {24, 208}
		, {32, 240}
		};

	stacxpr	uint32_t			AES_SIZEBLOCK					= 16; // Block length in bytes AES is 128b block only
	stacxpr	uint32_t			AES_SIZEIV						= 16;

	struct SAESContext {
		AES_LEVEL					Level							= {};
		::llc::au8					RoundKey						= {};
		uint8_t						Iv			[AES_SIZEBLOCK]		= {};
	};

	void						aesInitCtx						(SAESContext* ctx, const uint8_t* key, ::llc::AES_LEVEL level);
	void						aesInitCtxIV					(SAESContext* ctx, const uint8_t* key, ::llc::AES_LEVEL level, const uint8_t* iv);
	void						aesCtxSetIV						(SAESContext* ctx, const uint8_t* iv);

	// ECB enables the basic ECB 16-byte block algorithm. All can be enabled simultaneously. Buffer size is exactly AES_SIZEBLOCK bytes; you need only AES_init_ctx as IV is not used in ECB.
	// NB: ECB is considered insecure for most uses
	void						aesECBEncrypt					(SAESContext* ctx, uint8_t* buf);
	void						aesECBDecrypt					(SAESContext* ctx, uint8_t* buf);

	// CBC enables AES encryption in CBC-mode of operation.
	// buffer size MUST be mutile of AES_SIZEBLOCK; Suggest https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS7 for padding scheme.
	// NOTES: you need to set IV in ctx via aesInitCtxIV() or aesCtxSetIV() no IV should ever be reused with the same key
	void						aesCBCEncryptBuffer				(SAESContext* ctx, uint8_t* buf, uint32_t length);
	void						aesCBCDecryptBuffer				(SAESContext* ctx, uint8_t* buf, uint32_t length);

	// CTR enables encryption in counter-mode.
	// Symmetrical operation: Same function for encrypting as for decrypting. IV is incremented for every block, and used after encryption as XOR-compliment for output; Suggesting https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS7 for padding scheme.
	// NOTES: you need to set IV in ctx with aesInitCtxIV() or aesCtxSetIV() no IV should ever be reused with the same key
	void						aesCTRXCryptBuffer				(SAESContext* ctx, uint8_t* buf, uint32_t length);

	::llc::error_t				aesEncode		(const ::llc::vcu8 & messageToEncrypt, const ::llc::vcu8 & iv, const ::llc::vcu8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputEncrypted);
	::llc::error_t				aesDecode		(const ::llc::vcu8 & messageEncrypted, const ::llc::vcu8 & iv, const ::llc::vcu8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputDecrypted);
	::llc::error_t				aesEncode		(const ::llc::vcu8 & messageToEncrypt, const ::llc::vcu8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputEncrypted);
	::llc::error_t				aesDecode		(const ::llc::vcu8 & messageEncrypted, const ::llc::vcu8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputDecrypted);

	stainli	::llc::error_t		aesEncode		(const uint8_t * messageToEncrypt, uint32_t dataLength	, const ::llc::vcu8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputEncrypted)							{ return ::llc::aesEncode({messageToEncrypt, dataLength}, encryptionKey, level, outputEncrypted); }
	stainli	::llc::error_t		aesDecode		(const uint8_t * messageEncrypted, uint32_t dataLength	, const ::llc::vcu8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputDecrypted)							{ return ::llc::aesDecode({messageEncrypted, dataLength}, encryptionKey, level, outputDecrypted); }
	stainli	::llc::error_t		aesEncode		(const uint8_t * messageToEncrypt, uint32_t dataLength	, const ::llc::vcu8 & iv, const ::llc::vcu8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputEncrypted)	{ return ::llc::aesEncode({messageToEncrypt, dataLength}, iv, encryptionKey, level, outputEncrypted); }
	stainli	::llc::error_t		aesDecode		(const uint8_t * messageEncrypted, uint32_t dataLength	, const ::llc::vcu8 & iv, const ::llc::vcu8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputDecrypted)	{ return ::llc::aesDecode({messageEncrypted, dataLength}, iv, encryptionKey, level, outputDecrypted); }

	stainli	::llc::error_t		aesEncode		(const ::llc::vcu8 & messageToEncrypt, const ::llc::vci8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputEncrypted)							{ return ::llc::aesEncode(messageToEncrypt, *(const ::llc::vcu8*)&encryptionKey, level, outputEncrypted); }
	stainli	::llc::error_t		aesDecode		(const ::llc::vcu8 & messageEncrypted, const ::llc::vci8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputDecrypted)							{ return ::llc::aesDecode(messageEncrypted, *(const ::llc::vcu8*)&encryptionKey, level, outputDecrypted); }
	stainli	::llc::error_t		aesEncode		(const ::llc::vcu8 & messageToEncrypt, const ::llc::vcu8 & iv, const ::llc::vci8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputEncrypted)	{ return ::llc::aesEncode(messageToEncrypt, iv, *(const ::llc::vcu8*)&encryptionKey, level, outputEncrypted); }
	stainli	::llc::error_t		aesDecode		(const ::llc::vcu8 & messageEncrypted, const ::llc::vcu8 & iv, const ::llc::vci8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputDecrypted)	{ return ::llc::aesDecode(messageEncrypted, iv, *(const ::llc::vcu8*)&encryptionKey, level, outputDecrypted); }

	stainli	::llc::error_t		aesEncode		(const ::llc::vci8 & messageToEncrypt, const ::llc::vci8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputEncrypted)							{ return ::llc::aesEncode(*(const ::llc::vcu8*)&messageToEncrypt, *(::llc::vcu8*)&encryptionKey, level, outputEncrypted); }
	stainli	::llc::error_t		aesDecode		(const ::llc::vcu8 & messageEncrypted, const ::llc::vci8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::ai8 & outputDecrypted)							{ return ::llc::aesDecode(messageEncrypted, *(const ::llc::vcu8*)&encryptionKey, level, *(::llc::au8*)&outputDecrypted); }
	stainli	::llc::error_t		aesEncode		(const ::llc::vci8 & messageToEncrypt, const ::llc::vcu8 & iv, const ::llc::vci8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputEncrypted)	{ return ::llc::aesEncode(*(const ::llc::vcu8*)&messageToEncrypt, iv, *(::llc::vcu8*)&encryptionKey, level, outputEncrypted); }
	stainli	::llc::error_t		aesDecode		(const ::llc::vcu8 & messageEncrypted, const ::llc::vcu8 & iv, const ::llc::vci8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::ai8 & outputDecrypted)	{ return ::llc::aesDecode(messageEncrypted, iv, *(const ::llc::vcu8*)&encryptionKey, level, *(::llc::au8*)&outputDecrypted); }

	stainli	::llc::error_t		aesEncode		(const ::llc::vcc  & messageToEncrypt, const ::llc::vci8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputEncrypted)							{ return ::llc::aesEncode(*(const ::llc::vcu8*)&messageToEncrypt, *(::llc::vcu8*)&encryptionKey, level, outputEncrypted); }
	stainli	::llc::error_t		aesDecode		(const ::llc::vcu8 & messageEncrypted, const ::llc::vci8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::ac & outputDecrypted)							{ return ::llc::aesDecode(messageEncrypted, *(const ::llc::vcu8*)&encryptionKey, level, *(::llc::au8*)&outputDecrypted); }
	stainli	::llc::error_t		aesEncode		(const ::llc::vcc  & messageToEncrypt, const ::llc::vcu8 & iv, const ::llc::vci8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputEncrypted)	{ return ::llc::aesEncode(*(const ::llc::vcu8*)&messageToEncrypt, iv, *(::llc::vcu8*)&encryptionKey, level, outputEncrypted); }
	stainli	::llc::error_t		aesDecode		(const ::llc::vcu8 & messageEncrypted, const ::llc::vcu8 & iv, const ::llc::vci8 & encryptionKey, ::llc::AES_LEVEL level, ::llc::ac & outputDecrypted)	{ return ::llc::aesDecode(messageEncrypted, iv, *(const ::llc::vcu8*)&encryptionKey, level, *(::llc::au8*)&outputDecrypted); }

	stainli	::llc::error_t		aesEncode		(const ::llc::vcu8 & messageToEncrypt, const ::llc::vcc & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputEncrypted)							{ return ::llc::aesEncode(messageToEncrypt, *(const ::llc::vcu8*)&encryptionKey, level, outputEncrypted); }
	stainli	::llc::error_t		aesDecode		(const ::llc::vcu8 & messageEncrypted, const ::llc::vcc & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputDecrypted)							{ return ::llc::aesDecode(messageEncrypted, *(const ::llc::vcu8*)&encryptionKey, level, outputDecrypted); }
	stainli	::llc::error_t		aesEncode		(const ::llc::vcu8 & messageToEncrypt, const ::llc::vcu8 & iv, const ::llc::vcc & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputEncrypted)	{ return ::llc::aesEncode(messageToEncrypt, iv, *(const ::llc::vcu8*)&encryptionKey, level, outputEncrypted); }
	stainli	::llc::error_t		aesDecode		(const ::llc::vcu8 & messageEncrypted, const ::llc::vcu8 & iv, const ::llc::vcc & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputDecrypted)	{ return ::llc::aesDecode(messageEncrypted, iv, *(const ::llc::vcu8*)&encryptionKey, level, outputDecrypted); }

	stainli	::llc::error_t		aesEncode		(const ::llc::vci8 & messageToEncrypt, const ::llc::vcc & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputEncrypted)							{ return ::llc::aesEncode(*(const ::llc::vcu8*)&messageToEncrypt, *(::llc::vcu8*)&encryptionKey, level, outputEncrypted); }
	stainli	::llc::error_t		aesDecode		(const ::llc::vcu8 & messageEncrypted, const ::llc::vcc & encryptionKey, ::llc::AES_LEVEL level, ::llc::ai8 & outputDecrypted)							{ return ::llc::aesDecode(messageEncrypted, *(const ::llc::vcu8*)&encryptionKey, level, *(::llc::au8*)&outputDecrypted); }
	stainli	::llc::error_t		aesEncode		(const ::llc::vci8 & messageToEncrypt, const ::llc::vcu8 & iv, const ::llc::vcc & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputEncrypted)	{ return ::llc::aesEncode(*(const ::llc::vcu8*)&messageToEncrypt, iv, *(::llc::vcu8*)&encryptionKey, level, outputEncrypted); }
	stainli	::llc::error_t		aesDecode		(const ::llc::vcu8 & messageEncrypted, const ::llc::vcu8 & iv, const ::llc::vcc & encryptionKey, ::llc::AES_LEVEL level, ::llc::ai8 & outputDecrypted)	{ return ::llc::aesDecode(messageEncrypted, iv, *(const ::llc::vcu8*)&encryptionKey, level, *(::llc::au8*)&outputDecrypted); }

	stainli	::llc::error_t		aesEncode		(const ::llc::vcc  & messageToEncrypt, const ::llc::vcc & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputEncrypted)							{ return ::llc::aesEncode(*(const ::llc::vcu8*)&messageToEncrypt, *(::llc::vcu8*)&encryptionKey, level, outputEncrypted); }
	stainli	::llc::error_t		aesDecode		(const ::llc::vcu8 & messageEncrypted, const ::llc::vcc & encryptionKey, ::llc::AES_LEVEL level, ::llc::ac & outputDecrypted)							{ return ::llc::aesDecode(messageEncrypted, *(const ::llc::vcu8*)&encryptionKey, level, *(::llc::au8*)&outputDecrypted); }
	stainli	::llc::error_t		aesEncode		(const ::llc::vcc  & messageToEncrypt, const ::llc::vcu8 & iv, const ::llc::vcc & encryptionKey, ::llc::AES_LEVEL level, ::llc::au8 & outputEncrypted)	{ return ::llc::aesEncode(*(const ::llc::vcu8*)&messageToEncrypt, iv, *(::llc::vcu8*)&encryptionKey, level, outputEncrypted); }
	stainli	::llc::error_t		aesDecode		(const ::llc::vcu8 & messageEncrypted, const ::llc::vcu8 & iv, const ::llc::vcc & encryptionKey, ::llc::AES_LEVEL level, ::llc::ac & outputDecrypted)	{ return ::llc::aesDecode(messageEncrypted, iv, *(const ::llc::vcu8*)&encryptionKey, level, *(::llc::au8*)&outputDecrypted); }
}

#endif // LLC_AES_H_23627
