/* *Copyright (c) 2012, 武汉大学密码研究中心* 
   *All rights reserved.* 
   *
   *文件名称：ecc.h
   *摘    要：椭圆曲线机制运算模块
   *作    者: 孙金龙
   *时    间: 2012.3.16 13:42
   *最新版本: v1.0.0
*/
#ifndef __HEADER_ECC_H
#define __HEADER_ECC_H

#include "bn.h"
#include "ecp.h"

#ifdef  __cplusplus
extern "C" {
#endif

void ECCGenkey(Word *pwPriKey,
			   Word *pwPubKeyX,
			   Word *pwPubKeyY
			   );

int	ECCSM2SignHash (
					Word *pwRandom,
					Word *pwHash,
					Word *pwPriKey,
					Word *pwSignR,
					Word *pwSignS
					);

int	ECCSM2VerifyHash (Word		*pwHash,
					  Word		*pwPubKeyX,
					  Word		*pwPubKeyY,
					  Word		*pwSignR,
					  Word		*pwSignS
					  );

int	ECCSM2Encrypt (
				   Word *pwRandom,
				   BYTE *pbPlainText,
				   int iPlainTextLen,
				   Word *pwPubKeyX,
				   Word *pwPubKeyY,
				   BYTE *pbC1,
				   BYTE *pbC2,
				   BYTE *pbC3
				   );

int	ECCSM2Decrypt (
				   BYTE *pbC1,
				   BYTE *pbC2,
				   BYTE *pbC3,
				   Word *pwPriKey,
				   BYTE *pbPlainText,
				   int iPlainTextLen
				   );



#ifdef  __cplusplus
}
#endif

#endif