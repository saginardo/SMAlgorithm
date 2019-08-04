/* *Copyright (c) 2012, 武汉大学密码研究中心* 
   *All rights reserved.* 
   *
   *文件名称：bn.h
   *摘    要：SM2大整数基本运算
   *作    者: 孙金龙
   *时    间: 2012.3.14 11:06
   *最新版本: v1.0.0
*/
#ifndef __HEADER_BN_H
#define __HEADER_BN_H

#include "types.h"
#include "config.h"



#ifdef  __cplusplus
extern "C" {
#endif


//pwDest<=pwSource
void BNAssign(Word *pwDest, Word *pwSource);

// Sum=X+Y,return the carry
Word BNAdd(Word *pwSum,Word *pwX,Word *pwY);

// Diff=X-Y,return the borrow
Word BNSub(Word *pwDiff,Word *pwX,Word *pwY);

// T=2^(BNBitLen)  X<T,Y<T,Result<T
void BNModAdd(Word *pwResult, Word *pwX, Word *pwY, Word *pwModule);

// T=2^(BNBitLen)  X<T,Y<T,Result<T
void BNModSub(Word *pwResult, Word *pwX, Word *pwY, Word *pwModule);

// T=2^(BNBitLen)  X<T,Y<T,Result<T
void BNMonMul(Word *pwResult, Word *pwX, Word *pwY, Word *pwModule, Word wModuleConst);

//Montgomery Modular Inv, X is mon,R=mon X^-1
void BNMonInv(Word *pwInv,Word *pwBN,Word *pwModule,Word wModuleConst,Word *pwRRModule);

int Byte2BN(Byte *pbBuf,int ioffset,int iDataLen,Word *pwBN);

void BN2Byte(Word *bn, Byte *buffer,int ioffset);

void Byte2Word(Byte *pbBuf,int ioffset,Word *pwWd);

int BN2Bit(Word *bn, Byte *bits);

int BN2BitBit(Word *bn,Byte *bits);

int BNBN2BitBit(Word *bnh,Word *bnl,Byte *bits);

int BNCompare(Word *pwX, Word *pwY);

	
#ifdef  __cplusplus
}
#endif


#endif