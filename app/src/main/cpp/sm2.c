/* *Copyright (c) 2012, 武汉大学密码研究中心* 
   *All rights reserved.* 
   *
   *文件名称：sm2.c
   *摘    要：sm2提供的对外接口
   *作    者: 孙金龙
   *时    间: 2012.3.16 13:41
   *最新版本: v1.0.0
*/
#include <memory.h>
#include "types.h"
#include "bn.h"
#include "ecp.h"
#include "ecc.h"
#include "sm2.h"
#include "curve.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "config.h"
#include "sm3.h"


void BNRandom(Word *bn);


void BNRandom(Word *bn)
{
	int i;
	for(i=0;i<BNWORDLEN;i++)
		bn[i]=(rand()<<16)|rand();

}
int SM2Init()
{
	ECPInitByParameter(SM2_SystemParameter);
	srand( (unsigned)clock());
	return SM2_OK;
}

int SM2GenKey(BYTE   *pbPriKey,
			  int    *piPriKeyLen,
			  BYTE   *pbPubKey,
			  int    *piPubKeyLen
			  )
{
	Word K[MAXBNWordLen];
	Word PubKeyX[MAXBNWordLen];
	Word PubKeyY[MAXBNWordLen];

	int Ret;
	if(pbPriKey==0||pbPubKey==0||*piPriKeyLen!=WordByteLen*BNWORDLEN||*piPubKeyLen!=2*WordByteLen*BNWORDLEN)
	{
		*piPriKeyLen=WordByteLen*BNWORDLEN;
		*piPubKeyLen=2*WordByteLen*BNWORDLEN;
		 Ret=SM2_ERROR;
		 goto END;
	}
	
	BNRandom(K);
	
	ECCGenkey(K,PubKeyX,PubKeyY);
	
	BN2Byte(K,pbPriKey,0);
	
	BN2Byte(PubKeyX,pbPubKey,0);

	BN2Byte(PubKeyY,pbPubKey,WordByteLen*BNWORDLEN);

	Ret=SM2_OK;

END: return Ret;

}

int  SM2SignHash(BYTE *pbHash,
				int   iHashLen,
				BYTE  *pbPriKey,
				int   iPriKeyLen,
				BYTE  *pbSign,
				int   *piSignLen
				)
{

	int Ret;

	Word wRandom[MAXBNWordLen],wHash[MAXBNWordLen],wPriKey[MAXBNWordLen],wR[MAXBNWordLen],wS[MAXBNWordLen];

	if(pbSign==0||*piSignLen!=2*WordByteLen*BNWORDLEN)
	{
		*piSignLen=2*WordByteLen*BNWORDLEN;
		Ret=SM2_ERROR;
		goto END;
	}
	
	Byte2BN(pbHash,0,iHashLen,wHash);
	
	Byte2BN(pbPriKey,0,iPriKeyLen,wPriKey);

	BNRandom(wRandom);
	
	Ret=ECCSM2SignHash(wRandom,wHash,wPriKey,wR,wS);

	BN2Byte(wR,pbSign,0);

	BN2Byte(wS,pbSign,WordByteLen*BNWORDLEN);

END: return Ret;

}


int SM2VerifyHash(BYTE *pbHash,
				int   iHashLen,
				BYTE  *pbPubKey,
				int   iPubKeyLen,
				BYTE  *pbSign,
				int   iSignLen
				)
{
	Word wHash[MAXBNWordLen],wPubKeyX[MAXBNWordLen],wPubKeyY[MAXBNWordLen],wR[MAXBNWordLen],wS[MAXBNWordLen];
	
	int Ret;

	Byte2BN(pbHash,0,iHashLen,wHash);
	Byte2BN(pbPubKey,0,WordByteLen*BNWORDLEN,wPubKeyX);
	Byte2BN(pbPubKey,WordByteLen*BNWORDLEN,WordByteLen*BNWORDLEN,wPubKeyY);
	Byte2BN(pbSign,0,WordByteLen*BNWORDLEN,wR);
	Byte2BN(pbSign,WordByteLen*BNWORDLEN,WordByteLen*BNWORDLEN,wS);

	Ret=ECCSM2VerifyHash(wHash,wPubKeyX,wPubKeyY,wR,wS);

	return Ret;
}


int SM2Encrypt(
			   BYTE		*pbPlainText,
			   int		iPlainTextLen,
			   BYTE		*pbPubKey,
			   int      iPubKeyLen,
			   BYTE     *pbCipherText,
			   int 		*piCipherTextLen
			   )
{
	int i,j;
	int ret;
	Word wRandom[MAXBNWordLen],wPubKeyX[MAXBNWordLen],wPubKeyY[MAXBNWordLen];
	BYTE pbC1[2*MAXBNByteLen],pbC2[MAXPLAINTEXTLEN];
	BYTE C3[HASHLEN];
	int Ret;
	
	if(pbCipherText==0)
	{
		*piCipherTextLen=iPlainTextLen+2*MAXBNWordLen*WordByteLen+HASHLEN;
		Ret=SM2_OK;
		goto END;
	}
	Byte2BN(pbPubKey, 0,			MAXBNByteLen, wPubKeyX);
	Byte2BN(pbPubKey, MAXBNByteLen, MAXBNByteLen, wPubKeyY);
	
	BNRandom(wRandom);	
	

	ret=ECCSM2Encrypt(wRandom,pbPlainText,iPlainTextLen,wPubKeyX,wPubKeyY,pbC1,pbC2,C3);

	if (ret!=1)
	{	
		Ret=SM2_Encrypt_Error;
		goto END;
	}	
	//pbCipherText[1]=0x04;

	i=0;
	for (j=0;j<2*MAXBNWordLen*WordByteLen;i++,j++)
			pbCipherText[i]=pbC1[j];
	for (j=0;j<iPlainTextLen;i++,j++)
			pbCipherText[i]=pbC2[j];
	for (j=0;j<MAXBNByteLen;j++,i++)
			pbCipherText[i]=C3[j];

	*piCipherTextLen=iPlainTextLen+2*MAXBNWordLen*WordByteLen+HASHLEN;

	Ret=SM2_OK;
END: return Ret;
}

int SM2Decrypt(
			   BYTE			*pbCipherText,
			   int			iCipherTextLen,
			   BYTE      	*pbPriKey,
			   int         iPriKeyLen,
			   BYTE        *pbPlainText,
			   int 			*piPlainTextLen
			   )
{
	int i,j;
	int ret;
	Word wPriKey[MAXBNWordLen];
	BYTE pbC1[2*MAXBNByteLen],pbC2[MAXPLAINTEXTLEN];
	BYTE C3[HASHLEN];

	int Ret;
	if(pbPlainText==0)
	{
		*piPlainTextLen=iCipherTextLen-HASHLEN-2*MAXBNWordLen*WordByteLen;
		Ret=SM2_OK;
		goto END;
	}

	Byte2BN(pbPriKey,0,MAXBNByteLen,wPriKey);

	i=0;
	for (j=0;j<2*MAXBNWordLen*WordByteLen;i++,j++)
		pbC1[j]=pbCipherText[i];

	for (j=0;j<(*piPlainTextLen);j++,i++)
		pbC2[j]=pbCipherText[i];

	for (j=0;j<HASHLEN;j++,i++)
		C3[j]=pbCipherText[i];	

    *piPlainTextLen=iCipherTextLen-HASHLEN-2*MAXBNWordLen*WordByteLen;

	ret=ECCSM2Decrypt (pbC1,pbC2,C3,wPriKey,pbPlainText,*piPlainTextLen);
		
	if (ret==1)	
		Ret=SM2_OK;
	else
		Ret=SM2_Decrypt_Error;
END: return Ret;
}

void DotProduct(BYTE *pWorkKey, BYTE *pbPubKey,BYTE *pbPriKey)
{
	A_Point KP,Q;
	Word K[MAXBNWordLen];
	Word wPriKeyX[MAXBNWordLen];
	Word wPubKeyX[MAXBNWordLen],wPubKeyY[MAXBNWordLen];

	//私钥转换为BN 格式(32字节)
	Byte2BN(pbPriKey, 0, MAXBNByteLen, wPriKeyX);

	//公钥转换为BN 格式(64字节)
	Byte2BN(pbPubKey, 0, MAXBNByteLen, wPubKeyX);
	Byte2BN(pbPubKey, MAXBNByteLen, MAXBNByteLen, wPubKeyY);

	//BN 格式的私钥转存至K
	BNAssign(K,wPriKeyX);

	//BN 格式的公钥转存至Q
	BNAssign(Q.X, wPubKeyX);
	BNAssign(Q.Y, wPubKeyY);//Q=Pub

	//调用点乘函数完成BN 格式下的点乘, BN 格式下的结果存KP
	ECPKP(K, &Q, &KP);

	//BN 格式转换为64 字节后存pWorkKey
	BN2Byte(KP.X,pWorkKey,0);
	BN2Byte(KP.Y,pWorkKey+32,0);
}

void GBCombine(BYTE *X,unsigned long bytelen1,BYTE *Y,unsigned long bytelen2,BYTE *XY,unsigned long *bytelen3)
{
    unsigned int len;
    unsigned long j,i;

    len=bytelen1+bytelen2;
    *bytelen3=len;
    for(j=0;j<bytelen1;j++)
        XY[j]=X[j];

    for(i=0;i<bytelen2;i++)
        XY[bytelen1+i]=Y[i];
}

int GBKDF(BYTE *Z,unsigned long bytelen,unsigned long klen,BYTE *ZOut,int Hashlen)
{
    unsigned long ct;
    int bitlen,sl;
    unsigned long Zctlen;
    unsigned char *Zctbyte;
    unsigned char Hashbyte[32];
    unsigned char ctstr[4];
    unsigned long glen,hashblen;
    int i,j,k,len;

    if(klen%8!=0)
        return 0;
    ct=0x1;
    hashblen=Hashlen*8;
    sl=(klen%hashblen==0)?(klen/hashblen):((klen/hashblen)+1);

    Zctbyte=(unsigned char *)malloc(bytelen+4);

    ctstr[0]=(unsigned char)((ct&0xff000000)>>24);
    ctstr[1]=(unsigned char)((ct&0x00ff0000)>>16);
    ctstr[2]=(unsigned char)((ct&0x0000ff00)>>8);
    ctstr[3]=(unsigned char)((ct&0x000000ff));
    glen=0;
    k=0;
    for(i=1;i<=sl;i++)
    {
        memset(Zctbyte,0,bytelen+4);
        GBCombine(Z,bytelen,ctstr,4,Zctbyte,&Zctlen);
        sm3(Zctbyte,Zctlen,Hashbyte);
        //SM3Old_Data(Zctbyte,Zctlen,Hashbyte,Hashlen);
        ct++;
        ctstr[0]=(unsigned char)((ct&0xff000000)>>24);
        ctstr[1]=(unsigned char)((ct&0x00ff0000)>>16);
        ctstr[2]=(unsigned char)((ct&0x0000ff00)>>8);
        ctstr[3]=(unsigned char)((ct&0x000000ff));
        glen=Hashlen*8*i;
        if (glen>klen)
        {
            bitlen=klen-(glen-Hashlen*8);
            len=bitlen/8;
            for (j=0;j<len;j++)
            {
                ZOut[k]=Hashbyte[j];
                k++;
            }
            break;
        }
        else
        {
            for (j=0;j<Hashlen;j++)
            {
                ZOut[k]=Hashbyte[j];
                k++;
            }
        }

    }

    free(Zctbyte);
    return 1;
}


