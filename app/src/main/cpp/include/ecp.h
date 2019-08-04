/* *Copyright (c) 2012, 武汉大学密码研究中心* 
   *All rights reserved.* 
   *
   *文件名称：ecp.h
   *摘    要：点运算模块
   *作    者: 孙金龙
   *时    间: 2012.3.16 10:36
   *最新版本: v1.0.0
*/
#ifndef __HEADER_ECP_H
#define __HEADER_ECP_H

#include "bn.h"

#ifdef  __cplusplus
extern "C" {
#endif

typedef	struct _J_Point
{
    Word X[MAXBNWordLen];
    Word Y[MAXBNWordLen];
    Word Z[MAXBNWordLen];
}J_Point, *pJ_Point;

typedef struct _A_Point
{
    Word X[MAXBNWordLen];
    Word Y[MAXBNWordLen];
}A_Point, *pA_Point;

typedef struct _EC
{
	Word EC_P[MAXBNWordLen];
    Word EC_RR[MAXBNWordLen];
	Word EC_P_MC;
	Word EC_N[MAXBNWordLen];
	Word EC_NRR[MAXBNWordLen];
	Word EC_N_MC;
	Word EC_mona[MAXBNWordLen];
	A_Point TableG[3];
}EC, *pEC;

int   ECPInitByParameter(BYTE *pbSystemParameter);
void  ECPAAddA(pA_Point paSum, pA_Point paAp);
void  ECPKP(Word *K, pA_Point P,pA_Point KP);
void  ECPDoubleJ(pJ_Point pjJp);
void  ECPJAddA(pJ_Point pjJp, pA_Point paAp);
void  ECPJToA(pJ_Point pjJp, pA_Point paAp);
void  ECPKG(Word *K, pA_Point KG);
void  ECPKGLQ(Word *K ,Word *L,pA_Point Q,pA_Point KGLQ);



#ifdef  __cplusplus
}
#endif

#endif