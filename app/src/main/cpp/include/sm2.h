/* *Copyright (c) 2012, 武汉大学密码研究中心* 
   *All rights reserved.* 
   *
   *文件名称：sm2.h
   *摘    要：密码库接口
   *作    者: 孙金龙
   *时    间: 2012.5.30 13:43
   *最新版本: v1.0.0
*/
#ifndef __HEADER_SM2_H
#define __HEADER_SM2_H

#include "types.h"
#include "bn.h"
#include "config.h"
#include "curve.h"
#include "ecc.h"
#include "ecp.h"
#include "sm3.h"

//定义错误列表
#define  SM2_OK									  0   //程序运行正常
#define  SM2_ERROR								  1   //程序运行出错
#define  SM2_Signature_Illeage                    -1  //签名未通过
#define  SM2_Encrypt_Error                        -2 //加密错误
#define  SM2_Decrypt_Error                        -3 //解密错误


#ifdef  __cplusplus
extern "C" {
#endif


int SM2Init();

int SM2GenKey(BYTE   *pbPriKey,
			  int    *piPriKeyLen,
			  BYTE   *pbPubKey,
			  int    *piPubKeyLen
			  );

int  SM2SignHash(BYTE *pbHash,
				int   iHashLen,
				BYTE  *pbPriKey,
				int   iPriKeyLen,
				BYTE  *pbSign,
				int   *piSignLen
				);

int  SM2VerifyHash( 
				BYTE *pbHash,
				int   iHashLen,
				BYTE  *pbPubKey,
				int   iPubKeyLen,
				BYTE  *pbSign,
				int   iSignLen
				);

int SM2Encrypt(
			   BYTE		*pbPlainText,
			   int		iPlainTextLen,
			   BYTE		*pbPubKey,
			   int      iPubKeyLen,
			   BYTE     *pbCipherText,
			   int 		*piCipherTextLen
			   );

int SM2Decrypt(
			   BYTE			*pbCipherText,
			   int			iCipherTextLen,
			   BYTE      	*pbPriKey,
			   int         iPriKeyLen,
			   BYTE        *pbPlainText,
			   int 			*piPlainTextLen
			   );

void DotProduct(BYTE *pWorkKey, BYTE *pbPubKey,BYTE *pbPriKey);


int GBKDF(BYTE *Z,unsigned long bytelen,unsigned long klen,BYTE *ZOut,int Hashlen);
void GBCombine(BYTE *X,unsigned long bytelen1,BYTE *Y,unsigned long bytelen2,BYTE *XY,unsigned long *bytelen3);

#ifdef  __cplusplus
}
#endif

#endif