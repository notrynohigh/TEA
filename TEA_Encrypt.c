/******************************************************************************
 * File: TEA_Encrypt.c
 * Author: Bean 
 * Email: notrynohigh@outlook.com
 * Every one can use this file free !
 ******************************************************************************
 ******************************************************************************/
 /** Include -----------------------------------------------------------------*/
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "TEA_Encrypt.h"

/** defined -----------------------------------------------------------------*/
#define TEA_DELTA                  0x9e3779b9
#define TEA_KEY_LEN                (16)

/** global variable --------------------------------------------------------*/
static TEA_U8 TEA_EncryptTimes = 16;
static const  TEA_U8 TEA_FillData[8] = {0x12,0x23,0x34,0x45,0x56,0x67,0x78,0x89};
static TEA_U8 TEA_KeyBuf[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

/** public functions -------------------------------------------------------*/
TEA_ErrorCode_t TEA_Config128bitsKey(TEA_U8 *key)
{
	TEA_U8 i = 0;
	if(key == TEA_NULL)
	{
		return TEA_ERROR;
	}
	for(i = 0;i < TEA_KEY_LEN;i++)
	{
		TEA_KeyBuf[i] = key[i];
	}
	return TEA_SUCCESS;
}


static TEA_ErrorCode_t TEA_EncryptGroup(uint32_t *text, uint32_t *key)
{
	uint32_t sum = 0, v0 = text[0], v1 = text[1];
	uint32_t k0 = key[0], k1 = key[1], k2 = key[2], k3 = key[3];
	TEA_U8 i = 0;

	for(i = 0;i < TEA_ENCRYPT_TIMES;i++)
	{
		sum += TEA_DELTA;
		v0 += (v1 << 4) + k0 ^ v1 + sum ^ (v1 >> 5) + k1;
		v1 += (v0 << 4) + k2 ^ v0 + sum ^ (v0 >> 5) + k3;
	}
	text[0] = v0;
	text[1] = v1;
	return 0;
}

static int tea_decrypt_group(uint32_t *text, uint32_t *key)
{
	uint32_t sum = TEA_DELTA * TEA_ENCRYPT_TIMES, v0 = text[0], v1 = text[1];
	uint32_t k0 = key[0], k1 = key[1], k2 = key[2], k3 = key[3];
	TEA_U8 i = 0;

	for(i = 0;i < TEA_ENCRYPT_TIMES;i++)
	{
		v1 -= (v0 << 4) + k2 ^ v0 + sum ^ (v0 >> 5) + k3;
		v0 -= (v1 << 4) + k0 ^ v1 + sum ^ (v1 >> 5) + k1;
		sum -= TEA_DELTA;
	}
	text[0] = v0;
	text[1] = v1;
	return 0;
}

int tea_encrypt(TEA_U8 *text, uint32_t size)
{
	uint32_t number = size >> 3;
	TEA_U8  i = 0;
	
	if(text == NULL || (size & 0x7) != 0)
	{
		printf("param invalid %d ....",(TEA_U8)(size & 0x7));
		return -1;
	}
	for(i = 0;i < number;i++)
	{
		tea_encrypt_group(&(((uint32_t *)text)[i * 2]), (uint32_t *)tea_key);
	}
	return 0;
}


int tea_decrypt(TEA_U8 *text, uint32_t size)
{
	uint32_t number = size >> 3;
	TEA_U8  i = 0;
	
	if(text == NULL || (size & 0x7) != 0)
	{
		printf("param invalid %d ....",(TEA_U8)(size & 0x7));
		return -1;
	}
	for(i = 0;i < number;i++)
	{
		tea_decrypt_group(&(((uint32_t *)text)[i * 2]), (uint32_t *)tea_key);
	}
	return 0;
}



int main()
{
	TEA_U8 sel;
	TEA_U8 tmp_buf[128];
	uint32_t count, i;
	printf("*********************************************\n\r");
	printf("******TEA encryption and decryption *********\n\r");
	printf("*********************************************\n\r");
	while(1)
	{
		printf("***1. enter your key \n\r");
		printf("***2. data encryption \n\r");
		printf("***3. data decryption \n\r");
		printf("***enter number : \n\r");
		scanf("%d", &sel);
		switch(sel)
		{
			case 1: 
				if(0 != tea_set_key())
				{
					printf("fail to create key ... \n\r");
				}
				break;
			case 2:
				printf("enter your information: \n\r");
				scanf("%s", (char *)tmp_buf);
				count = strlen((char *)tmp_buf);
				count = tea_fill_buff(tmp_buf, count);
				printf("::::\n\r");
				tea_encrypt(tmp_buf, count);
				for(i = 0;i < count;i++)
				{
					printf("%d ", tmp_buf[i]);
				}
				printf("\n\r");
				break;
			case 3:
				printf("enter your data len: \n\r");
				scanf("%d", &count);
				printf("please enter %d numbers: \n\r", count);
				for(i = 0;i < count; i++)
				{
					scanf("%d", &tmp_buf[i]);
				}
				printf("::::\n\r");
				tea_decrypt(tmp_buf, count);
				for(i = 0;i <= count;i++)
				{
					printf("%c", tmp_buf[i]);
				}
				printf("\n\r");				
				break;
			default: 
				return 0;
		}
	}
}

