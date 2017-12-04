/******************************************************************************
 * File: TEA_Encrypt.h
 * Author: Bean 
 * Email: notrynohigh@outlook.com
 * Every one can use this file free !
 ******************************************************************************
 ******************************************************************************/


#ifndef __TEA_ENCRYPT__
#define __TEA_ENCRYPT__

/******************************************************************************
 *  basic data type
 ******************************************************************************/
typedef unsigned char  TEA_U8;
typedef signed char    TEA_S8;
typedef unsigned short TEA_U16;
typedef signed short   TEA_S16;
typedef unsigned int   TEA_U32;
typedef signed int     TEA_S32;

typedef unsigned long long int   TEA_U64;
typedef signed long long int     TEA_S64;

#define TEA_NULL    ((void *)0)
/******************************************************************************
 *  define
 ******************************************************************************/
#define TEA_DEBUG_ENABLE      1

#if TEA_DEBUG_ENABLE
#define TEA_DEBUG(...)    printf(__VA_ARGS__)
#else
#define TEA_DEBUG(...) 
#endif

/******************************************************************************
 *  typedef enum
 ******************************************************************************/
typedef enum
{
	TEA_ERROR,
	TEA_SUCCESS,
	TEA_MEMORY_ERROR,
	TEA_OTHERS
}TEA_ErrorCode_t;

/******************************************************************************
 *  typedef struct
 ******************************************************************************/
typedef struct
{
	TEA_U32 n;
	TEA_U32 e;
}TEA_PublicKey_t;

typedef struct
{
	TEA_U32 n;
	TEA_U32 d;
}TEA_PrivateKey_t;


/******************************************************************************
 * public functions
 ******************************************************************************/

TEA_ErrorCode_t TEA_CreateKey(TEA_U32 prime_1, TEA_U32 prime_2, TEA_U32 e);

TEA_ErrorCode_t TEA_ConfigPublicKey(TEA_U32 n, TEA_U32 e);
TEA_ErrorCode_t TEA_ConfigPrivateKey(TEA_U32 n, TEA_U32 d);

/**
 * TEA encrypt
 * text: the data which you want to encrypt.
 * result: the result of this function 
 * Len: the length of text .
 * return : the length of result . 
 *        0 : error 
 */
TEA_U32 TEA_Encrypt(TEA_U8 *text , TEA_U8 *result, TEA_U32 len);

/**
 * TEA decrypt
 * text: the data which you want to decrypt.
 * result: the result of this function 
 * Len: the length of text .
 * return : the length of result . 
 *        0 : error 
 */
TEA_U32 TEA_Decrypt(TEA_U8 *text, TEA_U8 *result, TEA_U32 len);



#endif
/******************************************************************************
 *  Reserved !
 ******************************************************************************/































