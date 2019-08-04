/* *Copyright (c) 2012, 武汉大学密码研究中心* 
   *All rights reserved.* 
   *
   *文件名称：bn.c
   *摘    要：SM2的基本算术运算－模加，模减，模乘，模逆
   *作    者: 孙金龙
   *时    间: 2012.3.14 11:20
   *最新版本: v1.0.0
*/
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "bn.h"
#include "config.h"



Word BNAdd(Word *pwSum,Word *pwX,Word *pwY)
{
    int i;
    DWord carry = 0;

	  for (i = 0; i < BNWORDLEN; i++)
    {
        carry = (DWord)pwX[i] + (DWord)pwY[i] + carry;
        pwSum[i] = (Word)carry;
        carry = carry >> WordBitLen;
    }

    return (Word)carry;
}

Word BNSub(Word *pwDiff,Word *pwX,Word *pwY)
{
    int i;
    DWord borrow = 0;

    for (i = 0; i < BNWORDLEN; i++)
    {
        borrow = (DWord)pwX[i] - (DWord)pwY[i] + borrow;
        pwDiff[i] = (Word)borrow;
        borrow = (DWord)(((SDWord)borrow) >> WordBitLen);
    }

    return (Word)borrow;
}

// T=2^(iBNWordLen*32)  X<T,Y<T,R<T
void BNModAdd(Word *pwResult, Word *pwX, Word *pwY, Word *pwModule)
{
    Word c;

    c = BNAdd(pwResult, pwX, pwY);

    if (c == 0)
        return;
    do
    {
        c = BNSub(pwResult, pwResult, pwModule);
    } while (c==0);

}

// T=2^(BN_Len*32)  X<T,Y<T,R<T
void BNModSub(Word *pwResult, Word *pwX, Word *pwY, Word *pwModule)
{
    Word c;

    c = BNSub(pwResult, pwX, pwY);

    if (c == 0)
        return;
    do
    {
        c = BNAdd(pwResult, pwResult, pwModule);
    } while (c == 0);

}

//Montgomery Modular Mul
void BNMonMul(Word *pwResult, Word *pwX, Word *pwY, Word *pwModule, Word wModuleConst)
{
	int i, j;
	DWord carry;
	Word U;
	Word D[MAXBNWordLen + 2];
	
	for (i = 0; i < BNWORDLEN + 2; i++)
		D[i] = 0;

	for (i = 0; i < BNWORDLEN; i++)
	{
		carry = 0;
		for (j = 0; j < BNWORDLEN; j++)
		{
			carry = (DWord)D[j] + (DWord)pwX[j] * (DWord)pwY[i] + carry;
			D[j] = (Word)carry;
			carry = carry >> WordBitLen;
		}

		carry = (DWord)D[BNWORDLEN] + carry;
		D[BNWORDLEN] = (Word)carry;
		D[BNWORDLEN + 1] = (Word)(carry >> WordBitLen);

		carry = (DWord)D[0] * (DWord)wModuleConst;
		U = (Word)carry;
		carry = (DWord)D[0] + (DWord)U * (DWord)pwModule[0];
		carry = carry >> WordBitLen;
		for (j = 1; j < BNWORDLEN; j++)
		{
			carry = (DWord)D[j] + (DWord)U * (DWord)pwModule[j] + carry;
			D[j - 1] = (Word)carry;
			carry = carry >> WordBitLen;
		}
		carry = (DWord)D[BNWORDLEN] + carry;
		D[BNWORDLEN - 1] = (Word)carry;
		D[BNWORDLEN] = D[BNWORDLEN + 1] + (Word)(carry >> WordBitLen);
	}
	if (D[BNWORDLEN] == 0)
		BNAssign(pwResult,D);
	else
		BNSub(pwResult,D,pwModule);
		
}

//D := S
void BNAssign(Word *pwDest, Word *pwSource)
{
    int i;
		
	for (i = 0; i < BNWORDLEN; i++)
        pwDest[i] = pwSource[i];
}


int Byte2BN(Byte *pbBuf,int ioffset,int iDataLen,Word *pwBN)
{
	int i;
	Byte NewBuf[MAXBNByteLen];

	if(iDataLen>BNWORDLEN*WordByteLen)
		return 0;

	else if(iDataLen<BNWORDLEN*WordByteLen)//in head fill zero
	{
		for(i=0;i<BNWORDLEN*WordByteLen;i++)
			NewBuf[i]=0;
		for(i=0;i<iDataLen;i++)
			NewBuf[BNWORDLEN*WordByteLen-iDataLen+i]=pbBuf[i+ioffset];
	}
	else  //iDataLen=iBNWordLen*WordByteLen
	{
		for(i=0;i<BNWORDLEN*WordByteLen;i++)
			NewBuf[i]=pbBuf[i+ioffset];
	}

	for(i=0;i<BNWORDLEN;i++)
	{
		pwBN[i] =   (Word)(NewBuf[BNWORDLEN*4 - 4 * i - 1]) 
				| (((Word)(NewBuf[BNWORDLEN*4 - 4 * i - 2])) << 8)
				| (((Word)(NewBuf[BNWORDLEN*4 - 4 * i - 3])) << 16)
				| (((Word)(NewBuf[BNWORDLEN*4 - 4 * i - 4])) << 24);
	}
	 return 1;

}





void Byte2Word(Byte *pbBuf,int ioffset,Word *pwWd)
{
	pwWd[0] = (Word)(pbBuf[3+ioffset]) 
				| (((Word)(pbBuf[2+ioffset])) << 8)
				| (((Word)(pbBuf[1+ioffset])) << 16)
				| (((Word)(pbBuf[ioffset])) << 24);
}



//[bits] should be at least the same length with [bn * 32]
//bits[0] is the 0 bit of BN
int BN2Bit(Word *bn, Byte *bits)
{
    int i, j, k, BitLen;
    Word Temp;
    int len = BNWORDLEN;
    BitLen = BNWORDLEN * WordBitLen;
    k = 0;
    for (i = 0; i < len; i++)
    {
        Temp = 1;
        for (j = 0; j < WordBitLen; j++)
        {
            if ((Temp & bn[i]) != 0)
                bits[k] = 1;
            else
                bits[k] = 0;
            Temp = Temp << 1;
            k++;
        }
    }

    for (; ; )
    {
        if (bits[BitLen - 1] == 0)
            BitLen--;
        else
            break;
    }
    return BitLen;

}


int BN2BitBit(Word *bn,Byte *bits)
{
	
	Word newbn[MAXBNWordLen+1];
	int i,j,k,HalfLen,BitLen;
	Word Temp;

	BitLen = BNWORDLEN * 16;
	if(BNWORDLEN%2==1)
	{
		HalfLen=(BNWORDLEN+1)/2;
		for(i=0;i<HalfLen-1;i++)
			newbn[i]=bn[i];
		newbn[HalfLen-1]=bn[HalfLen-1]&0x0000FFFF;
		for(i=HalfLen;i<BNWORDLEN;i++)
			newbn[i]=((bn[i-1]&0xFFFF0000)>>16)|((bn[i]&0x0000FFFF)<<16);
		newbn[BNWORDLEN]=(bn[BNWORDLEN-1]&0xFFFF0000)>>16;
	}
	else
	{
		HalfLen=BNWORDLEN/2;
		for(i=0;i<BNWORDLEN;i++)
			newbn[i]=bn[i];
	}
	
	k=0;
	for(i=0;i<HalfLen;i++)
	{
		Temp=1;
		for(j=0;j<32;j++)
		{
			if((Temp&newbn[i])!=0&&(Temp&newbn[i+HalfLen])!=0)
				bits[k]=3;
			else if((Temp&newbn[i])==0&&(Temp&newbn[i+HalfLen])!=0)
				bits[k]=2;
			else if((Temp&newbn[i])!=0&&(Temp&newbn[i+HalfLen])==0)
				bits[k]=1;
			else
				bits[k]=0;
			Temp=Temp<<1;
			k++;
		}
	}
	

	 for (; ; )
    {
        if (bits[BitLen - 1] == 0)
            BitLen--;
        else
            break;
    }
    return BitLen;
}

int BNBN2BitBit(Word *bnh,Word *bnl,Byte *bits)
{
	
	int i,j,k,BitLen;
	Word Temp;
	BitLen = BNWORDLEN * 32;
	k=0;
	for(i=0;i<BNWORDLEN;i++)
	{
		Temp=1;
		for(j=0;j<32;j++)
		{
			if((Temp&bnh[i])!=0&&(Temp&bnl[i])!=0)
				bits[k]=3;
			else if((Temp&bnh[i])!=0&&(Temp&bnl[i])==0)
				bits[k]=2;
			else if((Temp&bnh[i])==0&&(Temp&bnl[i])!=0)
				bits[k]=1;
			else
				bits[k]=0;
			Temp=Temp<<1;
			k++;
		}
	}
	for (; ; )
    {
        if (bits[BitLen - 1] == 0)
            BitLen--;
        else
            break;
    }
    return BitLen;
}






void BNRightShift(Word *pwBN)
{
	int i;
	for(i = 0; i < BNWORDLEN-1; i++)
	{
		pwBN[i] = pwBN[i] >> 1;
		pwBN[i] = (pwBN[i+1] & LSBOfWord) ? (pwBN[i] | MSBOfWord) : pwBN[i];
	}
	pwBN[i] = pwBN[i] >>1;
}

Word BNLeftShift(Word *pwBN)
{
	int i;
	Word Carry;
	
	Carry = pwBN[BNWORDLEN-1] & MSBOfWord;
	
	for (i=BNWORDLEN-1; i>0; i--)
	{
		pwBN[i] = pwBN[i] << 1;
		pwBN[i] = (pwBN[i-1] & MSBOfWord) ? (pwBN[i] | LSBOfWord) : pwBN[i];
	}
	
	pwBN[0] = pwBN[0] << 1;
	
	return Carry;
}

int BNIsZero(Word *pwBN)
{
	int i;
	for (i = 0; i < BNWORDLEN; i++)		if( pwBN[i] != 0)		return 0;
	return 1;
}


int BNCompare(Word *pwX, Word *pwY)
{
	int i;
	for(i = BNWORDLEN-1; i >= 0; i--)
		if(pwX[i] != pwY[i]) return((pwX[i] > pwY[i]) << 1) - 1;
	return 0;
}


void BNMonInv(Word *pwInv,Word *pwBN,Word *pwModule,Word wModuleConst,Word *pwRRModule)
{
	Word bn_u[MAXBNWordLen+1],bn_v[MAXBNWordLen+1],bn_s[MAXBNWordLen+1];
	Word bn_a[MAXBNWordLen+1],bn_ainv[MAXBNWordLen+1];
	int int_k=0,int_m,i,j,int_cofainv;

	int_m = BNWORDLEN*WordByteLen*8;

	BNAssign(bn_a,pwBN);
//Phase I
	for(i = 0; i < BNWORDLEN; i++)
	{
		bn_u[i] = 0;
		bn_v[i] = 0;
		bn_s[i] = 0;
		bn_ainv[i] = 0;
	}

	BNAssign(bn_u,pwModule);
	BNAssign(bn_v,bn_a);
	bn_s[0] = 1;

	while(!BNIsZero(bn_v))
	{
		if(!(bn_u[0]&LSBOfWord))
		{
			BNRightShift(bn_u);
			BNLeftShift(bn_s);
		}
		else if(!(bn_v[0]&LSBOfWord))
		{
			BNRightShift(bn_v);
			BNLeftShift(bn_ainv);
		}
		else if(BNCompare(bn_u,bn_v)==1)
		{
			BNSub(bn_u,bn_u,bn_v);
			BNRightShift(bn_u);
			BNAdd(bn_ainv,bn_ainv,bn_s);
			BNLeftShift(bn_s);
		}
		else if(!(BNCompare(bn_u,bn_v)==1))
		{
			BNSub(bn_v,bn_v,bn_u);
			BNRightShift(bn_v);
			BNAdd(bn_s,bn_s,bn_ainv);
			int_cofainv=BNLeftShift(bn_ainv);
		}
		int_k++;
	}
	if((!(BNCompare(pwModule,bn_ainv)==1))|int_cofainv)
		BNSub(bn_ainv,bn_ainv,pwModule);
	BNSub(bn_ainv,pwModule,bn_ainv);

//Phase II
	if(int_k <= int_m)
	{
		BNMonMul(bn_ainv,bn_ainv,pwRRModule,pwModule,wModuleConst);
		int_k = int_k + int_m;
	}
	for(i = 0; i < BNWORDLEN; i++)
		bn_u[i] = 0;

	j = (2*int_m -int_k) / (WordByteLen*8);
	bn_u[j] = 1;
	for(i = 0; i < (2*int_m-int_k) % (WordByteLen*8); i++)
		bn_u[j] = bn_u[j] << 1;
	BNMonMul(pwInv,bn_ainv,bn_u,pwModule,wModuleConst);
}




void BN2Byte(Word *bn, Byte *buffer,int offset)
{
	int i;
	int byteLen = WordByteLen * BNWORDLEN;
	for(i = 0; i < BNWORDLEN; i++)
	{
		buffer[offset+byteLen - 4 * i - 1] = (Byte)(bn[i] & 0x000000FF);
		buffer[offset+byteLen - 4 * i - 2] = (Byte)((bn[i] & 0x0000FF00) >> 8);
		buffer[offset+byteLen - 4 * i - 3] = (Byte)((bn[i] & 0x00FF0000) >> 16);
		buffer[offset+byteLen - 4 * i - 4] = (Byte)((bn[i] & 0xFF000000) >> 24);
	}
}



