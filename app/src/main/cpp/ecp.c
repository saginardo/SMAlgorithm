/* *Copyright (c) 2012, 武汉大学密码研究中心* 
   *All rights reserved.* 
   *
   *文件名称：ecp.c
   *摘    要：点运算模块
   *作    者: 孙金龙
   *时    间: 2012.3.16 13:41
   *最新版本: v1.0.0
*/
#include "ecp.h"
#include "config.h"

EC mEC_SM2;


int ECPInitByParameter(BYTE *pbSystemParameter)
{
	int iBNByteLen;
	
	Byte2Word(pbSystemParameter,0, &(mEC_SM2.EC_P_MC));
	Byte2Word(pbSystemParameter,4, &(mEC_SM2.EC_N_MC));
	
	iBNByteLen=4*BNWORDLEN;
	
	Byte2BN(pbSystemParameter,8,               iBNByteLen,mEC_SM2.EC_P       );
	Byte2BN(pbSystemParameter,8+  iBNByteLen,  iBNByteLen,mEC_SM2.EC_RR      );
	Byte2BN(pbSystemParameter,8+2*iBNByteLen,  iBNByteLen,mEC_SM2.EC_N       );
	Byte2BN(pbSystemParameter,8+3*iBNByteLen,  iBNByteLen,mEC_SM2.EC_NRR     );
	Byte2BN(pbSystemParameter,8+4*iBNByteLen,  iBNByteLen,mEC_SM2.EC_mona    );
	Byte2BN(pbSystemParameter,8+5*iBNByteLen,  iBNByteLen,mEC_SM2.TableG[0].X);
	Byte2BN(pbSystemParameter,8+6*iBNByteLen,  iBNByteLen,mEC_SM2.TableG[0].Y);
	Byte2BN(pbSystemParameter,8+7*iBNByteLen,  iBNByteLen,mEC_SM2.TableG[1].X);
	Byte2BN(pbSystemParameter,8+8*iBNByteLen,  iBNByteLen,mEC_SM2.TableG[1].Y);
	Byte2BN(pbSystemParameter,8+9*iBNByteLen,  iBNByteLen,mEC_SM2.TableG[2].X);
	Byte2BN(pbSystemParameter,8+10*iBNByteLen, iBNByteLen,mEC_SM2.TableG[2].Y);

	return 1;
	
}


void   ECPAAddA(pA_Point paSum,pA_Point paAp)
{
	Word bn1[MAXBNWordLen]; 
	Word bn2[MAXBNWordLen];
	Word bn3[MAXBNWordLen];
	Word bn4[MAXBNWordLen];
	Word *EC_P,*EC_RR,EC_P_MC;
	
	int i;
	EC_P=mEC_SM2.EC_P;
	EC_RR=mEC_SM2.EC_RR;
	EC_P_MC=mEC_SM2.EC_P_MC;
	for (i = 0; i < BNWORDLEN; i++)
        bn2[i] = 0;
    bn2[0] = 1;

    
    BNModSub(bn1, paAp->X, paSum->X, EC_P);
    BNMonMul(bn1, bn1, EC_RR, EC_P, EC_P_MC);
   	BNMonMul(bn1, bn1,bn2,EC_P,EC_P_MC);
	BNMonInv(bn1, bn1, EC_P,EC_P_MC,EC_RR);
  	BNModSub(bn2, paAp->Y, paSum->Y, EC_P);
    BNMonMul(bn3, bn1, bn2, EC_P, EC_P_MC);
    BNMonMul(bn4, bn3, EC_RR, EC_P, EC_P_MC);
    BNMonMul(bn1, bn3, bn4, EC_P, EC_P_MC);
    BNModSub(paSum->X, bn1, paSum->X, EC_P);
    BNModSub(paSum->X, paSum->X, paAp->X, EC_P);
    BNModSub(bn1, paAp->X, paSum->X, EC_P);
    BNMonMul(bn1, bn1, bn4, EC_P, EC_P_MC);
    BNModSub(paSum->Y, bn1, paAp->Y, EC_P);
    BNModSub(paSum->X, paSum->X, EC_P, EC_P);
    BNModSub(paSum->Y, paSum->Y, EC_P, EC_P);

}

void ECPDoubleJ(pJ_Point pjJp)
{
	Word bn1[MAXBNWordLen]; 
	Word bn2[MAXBNWordLen];
	Word bn3[MAXBNWordLen];
	Word bn4[MAXBNWordLen];
	Word bn5[MAXBNWordLen];
    Word *bnX,*bnY,*bnZ,*bnP,*bnMona;
	Word MC;
		
	MC=mEC_SM2.EC_P_MC;
	bnP=mEC_SM2.EC_P;
	bnMona=mEC_SM2.EC_mona;
	bnX=pjJp->X;
    bnY=pjJp->Y;
    bnZ=pjJp->Z;

	BNMonMul(bn4,bnY,bnY,bnP,MC);
    BNMonMul(bn1,bn4,bnX,bnP,MC);
    BNModAdd(bn1,bn1,bn1,bnP);
    BNModAdd(bn1,bn1,bn1,bnP);
    BNMonMul(bn2,bn4,bn4,bnP,MC);
    BNModAdd(bn2,bn2,bn2,bnP);
    BNModAdd(bn2,bn2,bn2,bnP);
    BNModAdd(bn2,bn2,bn2,bnP);
    BNMonMul(bn4,bnZ,bnZ,bnP,MC);
    BNMonMul(bn4,bn4,bn4,bnP,MC);
    BNMonMul(bn4,bn4,bnMona,bnP,MC);
    BNMonMul(bn3,bnX,bnX,bnP,MC);
    BNModAdd(bn5,bn3,bn3,bnP);
    BNModAdd(bn3,bn5,bn3,bnP);
    BNModAdd(bn3,bn3,bn4,bnP);
    BNMonMul(bnX,bn3,bn3,bnP,MC);
    BNModSub(bnX,bnX,bn1,bnP);
    BNModSub(bnX,bnX,bn1,bnP);
    BNModSub(bn1,bn1,bnX,bnP);
    BNMonMul(bn1,bn1,bn3,bnP,MC);
    BNMonMul(bnZ,bnY,bnZ,bnP,MC);
    BNModAdd(bnZ,bnZ,bnZ,bnP);
    BNModSub(bnY,bn1,bn2,bnP);
}

void   ECPJAddA(pJ_Point pjJp, pA_Point paAp)
{
	Word bn1[MAXBNWordLen]; 
	Word bn2[MAXBNWordLen];
	Word bn3[MAXBNWordLen];
    Word *bnX1,*bnY1,*bnZ1,*bnP;
	int i;
	Word MC;
	MC=mEC_SM2.EC_P_MC;
	bnX1=pjJp->X;
    bnY1=pjJp->Y;
    bnZ1=pjJp->Z;
	bnP=mEC_SM2.EC_P;

	for (i = 0; i < BNWORDLEN; i++)
			bn1[i] = 0;
	
	if(BNCompare(bnZ1,bnP)==0||BNCompare(bnZ1,bn1)==0)
	{
		BNAssign(bnX1,paAp->X);
		BNAssign(bnY1,paAp->Y);
		bn1[0] = 1;
		BNMonMul(bnZ1, bn1, mEC_SM2.EC_RR, bnP, MC);
		return ;
	}

    BNMonMul(bn3,bnZ1,bnZ1,bnP,MC);
    BNMonMul(bn2,bnZ1,bn3,bnP,MC);
    BNMonMul(bn3,bn3,paAp->X,bnP,MC);
    BNModSub(bn3,bn3,bnX1,bnP);
    BNMonMul(bnZ1,bnZ1,bn3,bnP,MC);
    BNMonMul(bn2,bn2,paAp->Y,bnP,MC);
    BNModSub(bn2,bn2,bnY1,bnP);
    BNMonMul(bn1,bn3,bn3,bnP,MC);
    BNMonMul(bn3,bn3,bn1,bnP,MC);
    BNMonMul(bn1,bn1,bnX1,bnP,MC);
    BNModAdd(bnX1,bn1,bn1,bnP);
    BNModAdd(bnX1,bnX1,bn3,bnP);
    BNMonMul(bnY1,bnY1,bn3,bnP,MC);
    BNMonMul(bn3,bn2,bn2,bnP,MC);
    BNModSub(bnX1,bn3,bnX1,bnP);
    BNModSub(bn1,bn1,bnX1,bnP);
    BNMonMul(bn1,bn1,bn2,bnP,MC);
    BNModSub(bnY1,bn1,bnY1,bnP);

}

void    ECPJToA(pJ_Point pjJp, pA_Point paAp)
{

	Word bn1[MAXBNWordLen]; 
	Word bn2[MAXBNWordLen];
	Word *bnP,*EC_RR;
	Word MC;
	int i;
	
	bnP=mEC_SM2.EC_P;
    MC=mEC_SM2.EC_P_MC;
	EC_RR=mEC_SM2.EC_RR;


    for (i = 0; i < BNWORDLEN; i++)
        bn2[i] = 0;
    bn2[0] = 1;

    BNMonMul(bn1, pjJp->Z, pjJp->Z, bnP, MC);
    BNMonMul(bn1, bn1, pjJp->Z, bnP, MC);
   	BNMonMul(bn1, bn1, bn2,bnP,MC);
	BNMonInv(bn1, bn1, bnP,MC,EC_RR);
   	BNMonMul(paAp->Y,pjJp->Y,bn1,bnP,MC);
    BNMonMul(paAp->Y,paAp->Y,bn2,bnP,MC);
    BNMonMul(bn1, bn1, pjJp->Z, bnP,MC);
    BNMonMul(paAp->X, pjJp->X, bn1, bnP,MC);
    BNMonMul(paAp->X, paAp->X, bn2, bnP,MC);
    BNModSub(paAp->X,paAp->X,bnP,bnP);
    BNModSub(paAp->Y,paAp->Y,bnP,bnP);

}

void  ECPKP(Word *K, pA_Point P,pA_Point KP)
{
    J_Point jp;
    A_Point ap;
    Word *EC_P,*EC_RR;
	Word MC;
	Byte BitBuf[MAXBNBitLen];	
    int i,BitLen;

	
	EC_P=mEC_SM2.EC_P;
	MC=mEC_SM2.EC_P_MC;
	EC_RR=mEC_SM2.EC_RR;

	
    BNMonMul(ap.X, P->X, EC_RR, EC_P, MC);
    BNMonMul(ap.Y, P->Y, EC_RR, EC_P, MC);
    BNAssign(jp.X,ap.X);
    BNAssign(jp.Y,ap.Y);

    for (i = 0; i < BNWORDLEN; i++)
        jp.Z[i] = 0;
    jp.Z[0] = 1;

    BNMonMul(jp.Z, jp.Z, EC_RR, EC_P,MC);
    
    BitLen = BN2Bit(K, BitBuf);

    if(BitLen<2)
        return;
	
    for(i=BitLen-2;i>=0;i--)
    {
        ECPDoubleJ(&jp);
        if(BitBuf[i]==1)
	        ECPJAddA(&jp,&ap);
    }
    ECPJToA(&jp,KP);
}

void  ECPKG(Word *K, pA_Point KG)
{
	Byte bits[MAXBNWordLen*16+16];
	J_Point jp;
	int BitLen;
	int index;
	int i;
	

	BitLen=BN2BitBit(K,bits);
	index=bits[BitLen-1]-1;

	BNAssign(jp.X,mEC_SM2.TableG[index].X);
	BNAssign(jp.Y,mEC_SM2.TableG[index].Y);
	for (i = 0; i < BNWORDLEN; i++)
        jp.Z[i] = 0;
    jp.Z[0] = 1;
    BNMonMul(jp.Z, jp.Z, mEC_SM2.EC_RR, mEC_SM2.EC_P, mEC_SM2.EC_P_MC);

	if(BitLen<2)
        return;
	for(i=BitLen-2;i>=0;i--)
    {
        ECPDoubleJ(&jp);
        if(bits[i]!=0)
	        ECPJAddA(&jp,&(mEC_SM2.TableG[bits[i]-1]));
    }
    ECPJToA(&jp,KG);

}


void ECPKGLQ(Word *K ,Word *L,pA_Point Q,pA_Point KGLQ)
{
	Byte bits[MAXBNBitLen];
	J_Point jp;
	A_Point AG;
	A_Point TableP[3];
	int BitLen;
	int index;
	int i;

	Word *EC_P,*EC_RR;
	Word EC_P_MC;

	EC_P=mEC_SM2.EC_P;
	EC_RR=mEC_SM2.EC_RR;
	EC_P_MC=mEC_SM2.EC_P_MC;

	BitLen=BNBN2BitBit(K,L,bits);

	BNAssign(AG.X,mEC_SM2.TableG[0].X);
	BNAssign(AG.Y,mEC_SM2.TableG[0].Y);
	BNAssign(TableP[1].X,AG.X);
	BNAssign(TableP[1].Y,AG.Y);
	
	for (i = 0; i < BNWORDLEN; i++)
        jp.Z[i] = 0;
    jp.Z[0] = 1;

	BNMonMul(AG.X, AG.X, jp.Z, EC_P, EC_P_MC);
	BNMonMul(AG.Y, AG.Y, jp.Z, EC_P, EC_P_MC);
	ECPAAddA(&AG,Q);
	BNMonMul(TableP[2].X,AG.X,EC_RR,EC_P,EC_P_MC);
	BNMonMul(TableP[2].Y,AG.Y,EC_RR,EC_P,EC_P_MC);
	BNMonMul(TableP[0].X,Q->X,EC_RR,EC_P,EC_P_MC);
	BNMonMul(TableP[0].Y,Q->Y,EC_RR,EC_P,EC_P_MC);


	index=bits[BitLen-1]-1;

	BNAssign(jp.X,TableP[index].X);
	BNAssign(jp.Y,TableP[index].Y);
	
	BNMonMul(jp.Z, jp.Z, EC_RR, EC_P, EC_P_MC);

	if(BitLen<2)
        return;
	for(i=BitLen-2;i>=0;i--)
    {
        ECPDoubleJ(&jp);
        if(bits[i]!=0)
	        ECPJAddA(&jp,&TableP[bits[i]-1]);
    }
    ECPJToA(&jp,KGLQ);


}

