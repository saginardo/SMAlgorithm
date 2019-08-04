//#include "StdAfx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sms4.h"

//S盒
unsigned char S[][16] = {{0xd6,0x90,0xe9,0xfe,0xcc,0xe1,0x3d,0xb7,0x16,0xb6,0x14,0xc2,0x28,0xfb,0x2c,0x05},
						{0x2b,0x67,0x9a,0x76,0x2a,0xbe,0x04,0xc3,0xaa,0x44,0x13,0x26,0x49,0x86,0x06,0x99},
						{0x9c,0x42,0x50,0xf4,0x91,0xef,0x98,0x7a,0x33,0x54,0x0b,0x43,0xed,0xcf,0xac,0x62},
						{0xe4,0xb3,0x1c,0xa9,0xc9,0x08,0xe8,0x95,0x80,0xdf,0x94,0xfa,0x75,0x8f,0x3f,0xa6},
						{0x47,0x07,0xa7,0xfc,0xf3,0x73,0x17,0xba,0x83,0x59,0x3c,0x19,0xe6,0x85,0x4f,0xa8},
						{0x68,0x6b,0x81,0xb2,0x71,0x64,0xda,0x8b,0xf8,0xeb,0x0f,0x4b,0x70,0x56,0x9d,0x35},
						{0x1e,0x24,0x0e,0x5e,0x63,0x58,0xd1,0xa2,0x25,0x22,0x7c,0x3b,0x01,0x21,0x78,0x87},
						{0xd4,0x00,0x46,0x57,0x9f,0xd3,0x27,0x52,0x4c,0x36,0x02,0xe7,0xa0,0xc4,0xc8,0x9e},
						{0xea,0xbf,0x8a,0xd2,0x40,0xc7,0x38,0xb5,0xa3,0xf7,0xf2,0xce,0xf9,0x61,0x15,0xa1},
						{0xe0,0xae,0x5d,0xa4,0x9b,0x34,0x1a,0x55,0xad,0x93,0x32,0x30,0xf5,0x8c,0xb1,0xe3},
						{0x1d,0xf6,0xe2,0x2e,0x82,0x66,0xca,0x60,0xc0,0x29,0x23,0xab,0x0d,0x53,0x4e,0x6f},
						{0xd5,0xdb,0x37,0x45,0xde,0xfd,0x8e,0x2f,0x03,0xff,0x6a,0x72,0x6d,0x6c,0x5b,0x51},
						{0x8d,0x1b,0xaf,0x92,0xbb,0xdd,0xbc,0x7f,0x11,0xd9,0x5c,0x41,0x1f,0x10,0x5a,0xd8},
						{0x0a,0xc1,0x31,0x88,0xa5,0xcd,0x7b,0xbd,0x2d,0x74,0xd0,0x12,0xb8,0xe5,0xb4,0xb0},
						{0x89,0x69,0x97,0x4a,0x0c,0x96,0x77,0x7e,0x65,0xb9,0xf1,0x09,0xc5,0x6e,0xc6,0x84},
						{0x18,0xf0,0x7d,0xec,0x3a,0xdc,0x4d,0x20,0x79,0xee,0x5f,0x3e,0xd7,0xcb,0x39,0x48}};


//固定参数CK
unsigned int CK[32] = {0x00070e15,0x1c232a31,0x383f464d,0x545b6269,0x70777e85,0x8c939aa1,0xa8afb6bd,0xc4cbd2d9,
			  0xe0e7eef5,0xfc030a11,0x181f262d,0x343b4249,0x50575e65,0x6c737a81,0x888f969d,0xa4abb2b9,
              0xc0c7ced5,0xdce3eaf1,0xf8ff060d,0x141b2229,0x30373e45,0x4c535a61,0x686f767d,0x848b9299,
              0xa0a7aeb5,0xbcc3cad1,0xd8dfe6ed,0xf4fb0209,0x10171e25,0x2c333a41,0x484f565d,0x646b7279};
//void Tt(const unsigned char preS[],unsigned char outS[])
//{
//	int i;
//	unsigned char tmp[4] = {0};
//	for(i= 0 ;i < 4;i++)
//	{
//		tmp[i] = preS[i];
//		int X = tmp & 0xf0;
//		int Y = tmp & 0x0f;
//		outS[i] = S[X][Y];
//	}
//
//}

void print_Hex(unsigned char array[],unsigned int length)
{
	unsigned int i ;
	int countPerLine = 16;
	for (i = 0;i < length;i++)
	{
		if ((i % countPerLine)==0)
		{
			printf("\n");
			printf("0x");
			int discuss = i/countPerLine;
			if (discuss < countPerLine)
			{
				printf("00");
				printf("%x0 ",discuss);

			}
			else if ((16 <= discuss)&&( discuss< 256))
			{
				printf("0");
				printf("%x%x0 ",discuss/countPerLine,discuss%countPerLine);
			}
			/*else if (256 <= discuss <256*16)
			{
				int discuss1 = discuss / 16
				printf("%x%x%x0",)
			}*/

		}
		printf("%02x ",array[i]);
	}
	printf("\n");
}


int Tt(const int preS)
{
	int i,j;
	unsigned char tmp[5] = {0};
	for (j= 0,i = 24; i > -1;i -=8,j++)
	{
		int tmpX = (preS >> (i+4)) & 0x0000000f;
		int tmpY = (preS >> (  i)) & 0x0000000f;
		tmp[j] = S[tmpX][tmpY];
	}
	//int result = atoi(tmp);
	/*int result[1] = {0}; 
	convertIntArray(tmp,4,result);
	return result[0];*/
	int result = 0;
	convertIntArray(tmp,4,&result);
	return result;
}

//int TL(int B)
//{
//	int C = B ^(B << 2) ^ (B << 10) ^ (B << 18) ^(B << 24);
//	return C;
//
//}

int TL(int B)
{
	int B2  = ((B << 2) & 0xfffffffc) | ((B >> 30) & 0x00000003);
	int B10 = ((B <<10) & 0xfffffc00) | ((B >> 22) & 0x000003ff);
	int B18 = ((B <<18) & 0xfffc0000) | ((B >> 14) & 0x0003ffff);
	int B24 = ((B <<24) & 0xff000000) | ((B >> 8 ) & 0x00ffffff);
	int C   = B ^ B2 ^ B10 ^ B18 ^ B24;
	return C;
}

//int TotherL(int B)
//{
//	int C = B ^(B << 13) ^ (B << 23);
//	return C;
//}

int TotherL(int B)
{
	int B13 = ((B << 13) & 0xffffe000) | ((B >> 19) & 0x00001fff);
	int B23 = ((B << 23) & 0xff800000) | ((B >>  9) & 0x007fffff);
	int C   = B ^ B13 ^ B23;
	return C;
}

int T(int input)
{
	int tmp = Tt(input);
	return TL(tmp);
}

int Tother(int input)
{
	int tmp = Tt(input);
	return TotherL(tmp);
}

void Extand(int key[],int extandKey[])
{
	int i ;
	unsigned int K[36] = {0};

	//系统参数
	unsigned int FK0 = 0xA3B1BAC6;
	unsigned int FK1 = 0x56AA3350;
	unsigned int FK2 = 0x677D9197;
	unsigned int FK3 = 0xB27022DC;

	//32字的轮--==
	//int rk[32] = {0};
	K[0] = key[0] ^ FK0;
	K[1] = key[1] ^ FK1;
	K[2] = key[2] ^ FK2;
	K[3] = key[3] ^ FK3;
	for (i = 0;i < 32;i ++)
	{
		int tmp1 = K[i+1] ^ K[i+2] ^ K[i+3] ^ CK[i];
	    int tmp2 = Tother(tmp1);
		extandKey[i] = K[i+4] = K[i] ^ tmp2;
	}
	//extandKey = &(rk[0]);
}

int F(int X0,int X1,int X2,int X3,int rk)
{
	return X0 ^(T(X1 ^ X2 ^ X3 ^ rk ));

}

//void convertIntArray(unsigned char inputData[],unsigned int unInputDataLen,int output[])
//{
//	int tmpLen = unInputDataLen / 4;
//	int tmpIntArray[tmpLen] ;
//	
//	unsigned char tmp[4] = {0};
//	int i;
//	for (i = 0;i < tmpLen;i++)
//	{
//		strncpy(tmp,inputData,sizeof(int));
//		/*inputData += sizeof(int);
//		output[i] = atoi(tmp);*/
//	}
//
//	
//}

void convertIntArray(unsigned char inputData[],unsigned int unInputDataLen,int output[])
{
	int tmpLen = unInputDataLen / 4;
	//int tmpIntArray[tmpLen] ;
	
	char tmp[4] = {0};
	int i,j;
	for (i = 0;i < tmpLen;i++)
	{
		/*strncpy(tmp,inputData,sizeof(int));*/
		for (j =0;j<4;j++)
		{
			tmp[j] = inputData[j];
		}
		inputData += sizeof(int);
		int tmp1 = ((tmp[0] & 0x000000ff) << 24) & 0xff000000;
		int tmp2 = ((tmp[1] & 0x000000ff) << 16) & 0x00ff0000;
		int tmp3 = ((tmp[2] & 0x000000ff) << 8 ) & 0x0000ff00;
		int tmp4 = (tmp[3] & 0x000000ff) & 0x000000ff;
		output[i] = tmp1 | tmp2 | tmp3 | tmp4;
	}
}

void convertCharArray(int input[],int len,unsigned char output[])
{
	int i,j,k;
	char tmp[5] = {0};
	for (i = 0;i < len; i ++)
	{
		tmp[0] = (unsigned char)((input[i] >> 24) & 0x000000ff);
		tmp[1] = (unsigned char)((input[i] >> 16) & 0x000000ff);
		tmp[2] = (unsigned char)((input[i] >> 8) & 0x000000ff);
		tmp[3] = (unsigned char)(input[i] & 0x000000ff);
		for (j = 4*i,k = 0 ;k < 4 ;k++)
		{
			output[j+k] = tmp[k];
		}
	}
	//output[len*4 + 1] = 0;
}

void R(int array[])
{
	int tmp[4] = {0};
	int i;
	for(i = 0;i < 4;i++)
	{
		tmp[i] = array[i];
	}

	for(i = 0;i < 4; i++)
	{
		array[i] = tmp[3-i];
	}

}
unsigned int SMS4_encrypt(unsigned char key[],unsigned int keyLen,unsigned char *inputData,
						  unsigned int unInputDataLen, unsigned char *outputData,unsigned int * outputDataLen)
{
	int i,j,k,l,m,n;
	if (keyLen != 16)
	{
		return KeyLenError;
	}
	//if (((unInputDataLen % 16) != 0) || (unInputDataLen > 8192))
	if ((unInputDataLen % 16) != 0)
	{
		return PlainLenError;
	}
    int intLen = unInputDataLen/(sizeof(int));

	//转换mingw格式，字节数组----整数数组，要释放空间
	int * plainData = (int * )malloc( intLen * sizeof(int));
	convertIntArray(inputData,unInputDataLen,plainData);

	//--文数据缓冲区
	int * encData = (int * )malloc( intLen * sizeof(int));
	int preR[4] = {0};

	//获取扩展--==
	int extandKey[32] = {0};
	int keyInt[4] = {0};
	convertIntArray(key,16,keyInt);
	Extand(keyInt,extandKey);
	int X[36] = {0};
	for(i = 0;i < intLen/4; i++)
	{

		//为X0--X3赋值，即赋值mingw
		for(j = 0;j < 4;j++)
		{
			X[j] = plainData[4*i + j];
		}
		
		//函数迭代
		for (k = 0;k < 32;k ++)
		{
			X[k+4] = F(X[k],X[k+1],X[k+2],X[k+3],extandKey[k]);
		}

		for (l = 0;l < 4;l ++)
		{
			preR[l] = X[l+32];

		}

		R(preR);
		for (m = 4*i,n = 0; n < 4;m ++ ,n ++)
		{
			*encData = preR[n];
			encData ++;	
		}

	}
	encData -= intLen;
	convertCharArray(encData,intLen,outputData);
	

	free(plainData);
	free(encData);
	*outputDataLen = unInputDataLen;
	//print_Hex(outputData,unInputDataLen);
	return 0;

}

unsigned int SMS4_decrypt(unsigned char key[],unsigned int keyLen,
						  unsigned char *inputData,unsigned int unInputDataLen, unsigned char *outputData,unsigned int * outputDataLen)
{
	int i,j,k,l,m,n;
	if (keyLen != 16)
	{
		return KeyLenError;
	}
	//if (((unInputDataLen % 16) != 0) || (unInputDataLen > 8192))
	if ((unInputDataLen % 16) != 0)
	{
		return PlainLenError;
	}
    int intLen = unInputDataLen/(sizeof(int));

	//转换mingw格式，字节数组----整数数组，要释放空间
	int * encData = (int * )malloc( intLen * sizeof(int));
	convertIntArray(inputData,unInputDataLen,encData);

	//--文数据缓冲区
	int * plainData = (int * )malloc( intLen * sizeof(int));
	int preR[4] = {0};

	//获取扩展--==
	int extandKey[32] = {0};
	int keyInt[4] = {0};
	convertIntArray(key,16,keyInt);
	Extand(keyInt,extandKey);
	int X[36] = {0};
	for(i = 0;i < intLen/4; i++)
	{

		//为X0--X3赋值，即赋值mingw
		for(j = 0;j < 4;j++)
		{
			X[j] = encData[4*i + j];
		}
		
		//函数迭代
		for (k = 0;k < 32;k ++)
		{
			X[k+4] = F(X[k],X[k+1],X[k+2],X[k+3],extandKey[31-k]);
		}

		for (l = 0;l < 4;l ++)
		{
			preR[l] = X[l+32];

		}

		R(preR);
		for (m = 4*i,n = 0; n < 4;m ++ ,n ++)
		{
			/*int aaa =  preR[n];*/
			*plainData = preR[n];
			plainData ++;
			/*encData ++;*/

		}

	}
	plainData -= intLen;
	convertCharArray(plainData,intLen,outputData);

	free(plainData);
	free(encData);
	*outputDataLen = unInputDataLen;
	//print_Hex(outputData,unInputDataLen);
	return 0;
}

void Xor(unsigned char *InA, const unsigned char*InB, int len)
{		
		int i;
    for(i=0; i<len; ++i)
        InA[i] ^= InB[i];
}

void ByteToBit(unsigned char *Outbitarray, const unsigned char *Inbytearray, int bits)
{		
		int i;
    for(i=0; i<bits; ++i)
        Outbitarray[i] = (Inbytearray[i>>3]>>(i&7)) & 1;
}

void BitToByte(unsigned char *Outbytearray, const unsigned char *Inbitarray, int bits)
{		
		int i;
    memset(Outbytearray, 0, bits>>3);
    for(i=0; i<bits; ++i)
        Outbytearray[i>>3] |= Inbitarray[i]<<(i&7);
}
void RotateLbit(unsigned char *In, int len, int loop)
{
	unsigned char *Tmp = (unsigned char*)malloc(loop);
    memcpy(Tmp, In, loop);
    memcpy(In, In+loop, len-loop);
    memcpy(In+len-loop, Tmp, loop);
	free(Tmp);
}

void RotateL(unsigned char *In, int len, int loop)
{
	unsigned char* tmpA = (unsigned char*)malloc(8*len);
	ByteToBit(tmpA, In, 8*len);
	RotateLbit(tmpA, 8*len, 8*loop);
	BitToByte(In, tmpA, 8*len);
	free(tmpA);
}

void RotateL_ch(unsigned char *In, int inlen, int rotatelen)
{
// 	for(int i= 0;i<(inlen-rotatelen);i++)
// 	{
// 		*(In+i)=*(In+i+rotatelen);
// 	}
	memcpy(In,In+rotatelen,inlen-rotatelen);
}

unsigned int Mode_SMS4_encrypt(unsigned char key[],unsigned int keyLen,unsigned char iv[],
							   unsigned char *inputData,unsigned int unInputDataLen,
							   unsigned char *outputData,unsigned int * outputDataLen,int mode)
{

	*outputDataLen = 0;
	if (keyLen != 16)
	{
		return KeyLenError;
	}
	if(mode==ALG_MODE_CBC)
	{
		//if (((unInputDataLen % 16) != 0) || (unInputDataLen > 8192))
		if ((unInputDataLen % 16) != 0)
		{
			return PlainLenError;
		}
	}

	unsigned int i = 0;
	unsigned int j = 0;
	int datablocklen = 16;
	int IVlen = 16;
	unsigned char * lpout = outputData;
	unsigned char * lpin = (unsigned char *)malloc(unInputDataLen);
	unsigned char * lpinbackup = lpin;
	memcpy(lpin,inputData,unInputDataLen);
	unsigned int outlen = 0;
	unsigned int tmpoutlen = 0;
	
	switch(mode)
	{
	case ALG_MODE_ECB:
		{
			SMS4_encrypt(key,keyLen,lpin,unInputDataLen,lpout,&tmpoutlen);
		}
		break;
	case ALG_MODE_CBC:
		{
			Xor(lpin, iv, datablocklen);
			for(i=0,j=unInputDataLen/datablocklen; i<j; ++i, lpout+=datablocklen) 
			{
				
				//SMS4_encrypt(Out, In, &SubKey[0], Type);
				SMS4_encrypt(key,keyLen,lpin,datablocklen,lpout,&tmpoutlen);
				lpin += datablocklen;
				if(i<(j-1))
				{
					Xor(lpin, lpout, datablocklen);
				}
			}
		}
		break;
	case ALG_MODE_OFB:
		{
			/*
			unsigned char tmpdata = 0;
			unsigned char tmpiv[16]={0};
			memcpy(tmpiv,iv,sizeof(tmpiv));
			unsigned char ofbtmpout[16]={0};
			for(i=0; i<unInputDataLen; ++i, ++lpout, ++lpin)
			{
				//SDES(Out, IV, &SubKey[0], ENCRYPT);//注意使用的是加密函数!
				SMS4_encrypt(key,keyLen,tmpiv,sizeof(tmpiv),ofbtmpout,&tmpoutlen);
				tmpdata = ofbtmpout[0];
				Xor(ofbtmpout, lpin, 1);
				//Xor(ofbtmpout, lpin, 1);
				*lpout = ofbtmpout[0];
				RotateL_ch(tmpiv, 16, 1);
				tmpiv[15] = tmpdata;
			}
			*/
			unsigned char tmpdata = 0;
			unsigned char tmpiv[16]={0};
			memcpy(tmpiv,iv,sizeof(tmpiv));
			unsigned char ofbtmpout[16]={0};
			int packetlen = 16;
			int looptime = unInputDataLen/packetlen;
			int yuliang = unInputDataLen%packetlen;

			for(i=0; i<looptime; ++i)
			{
				SMS4_encrypt(key,keyLen,tmpiv,sizeof(tmpiv),lpout,&tmpoutlen);
				memcpy(tmpiv, lpout, sizeof(tmpiv));
				Xor(lpout, lpin, packetlen);
				lpout+=packetlen;
				lpin+=packetlen;
			}

			if(yuliang!=0)
			{
				SMS4_encrypt(key,keyLen,tmpiv,sizeof(tmpiv),ofbtmpout,&tmpoutlen);
				Xor(ofbtmpout, lpin, yuliang);
				memcpy(lpout,ofbtmpout,yuliang);
				lpout+=yuliang;
				lpin+=yuliang;
			}
		}
		break;
	default:
		free(lpinbackup);
		return INVALIDATEMODE;
		break;
	}
	*outputDataLen = unInputDataLen;
	free(lpinbackup);
	return 0;
}

unsigned int Mode_SMS4_decrypt(unsigned char key[],unsigned int keyLen,unsigned char iv[],
							   unsigned char *inputData,unsigned int unInputDataLen, 
							   unsigned char *outputData,unsigned int * outputDataLen,int mode)
{
	*outputDataLen = 0;
	if (keyLen != 16)
	{
		return KeyLenError;
	}
	if(mode==ALG_MODE_CBC)
	{
		//if (((unInputDataLen % 16) != 0) || (unInputDataLen > 8192))
		if ((unInputDataLen % 16) != 0)
		{
			return PlainLenError;
		}
	}
	
	unsigned int i = 0;
	unsigned int j = 0;
	int datablocklen = 16;
	int IVlen = 16;
	unsigned char * lpout = outputData;
	unsigned char * lpin = (unsigned char *)malloc(unInputDataLen);
	unsigned char * lpinbackup = lpin;
	memcpy(lpin,inputData,unInputDataLen);
	unsigned int outlen = 0;
	unsigned int tmpoutlen = 0;
	
	switch(mode)
	{
	case ALG_MODE_ECB:
		{
			SMS4_decrypt(key,keyLen,lpin,unInputDataLen,lpout,&tmpoutlen);
		}
		break;
	case ALG_MODE_CBC:
		{
			unsigned char tmpiv[16]={0};
			memcpy(tmpiv,iv,sizeof(tmpiv));
			for(i=0,j=unInputDataLen/datablocklen; i<j; ++i, lpout+=datablocklen,lpin+=datablocklen) 
			{
				SMS4_decrypt(key,keyLen,lpin,datablocklen,lpout,&tmpoutlen);
				Xor(lpout, tmpiv, datablocklen);
				memcpy(tmpiv, lpin, datablocklen);
			}
		}
		break;
	case ALG_MODE_OFB:
		{
			/*
			unsigned char tmpdata = 0;
			unsigned char tmpiv[16]={0};
			memcpy(tmpiv,iv,sizeof(tmpiv));
			unsigned char ofbtmpout[16]={0};
			for(i=0; i<unInputDataLen; ++i, ++lpout, ++lpin)
			{
				SMS4_encrypt(key,keyLen,tmpiv,sizeof(tmpiv),ofbtmpout,&tmpoutlen);
				tmpdata = ofbtmpout[0];
				Xor(ofbtmpout, lpin, 1);
				*lpout = ofbtmpout[0];
				RotateL_ch(tmpiv,16, 1);
				tmpiv[15] = tmpdata;
			}*/
			
			unsigned char tmpdata = 0;
			unsigned char tmpiv[16]={0};
			memcpy(tmpiv,iv,sizeof(tmpiv));
			unsigned char ofbtmpout[16]={0};
			int packetlen = 16;
			int looptime = unInputDataLen/packetlen;
			int yuliang = unInputDataLen%packetlen;
			
			for(i=0; i<looptime; ++i)
			{
				SMS4_encrypt(key,keyLen,tmpiv,sizeof(tmpiv),lpout,&tmpoutlen);
				memcpy(tmpiv, lpout, sizeof(tmpiv));
				Xor(lpout, lpin, packetlen);
				lpout+=packetlen;
				lpin+=packetlen;
			}
			
			if(yuliang!=0)
			{
				SMS4_encrypt(key,keyLen,tmpiv,sizeof(tmpiv),ofbtmpout,&tmpoutlen);
				Xor(ofbtmpout, lpin, yuliang);
				memcpy(lpout,ofbtmpout,yuliang);
				lpout+=yuliang;
				lpin+=yuliang;
			}
			
		}
		break;
	default:
		free(lpinbackup);
		return INVALIDATEMODE;
		break;
	}
	free(lpinbackup);
	*outputDataLen = unInputDataLen;
	return 0;
}
