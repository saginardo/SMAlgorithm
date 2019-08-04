
#ifndef XYSSL_SMS4_H
#define XYSSL_SMS4_H


#define  KeyLenError  -1
#define  PlainLenError -2
#define	 INVALIDATEMODE -3

#define ALG_MODE_CBC 0x01
#define ALG_MODE_OFB 0x02
#define ALG_MODE_ECB 0x03


int Tt(const int preS);
int TL(int B);
int TotherL(int B);
int T(int input);
int Tother(int input);
void Extand(int key[],int extandKey[]);
int F(int X0,int X1,int X2,int X3,int rk);
void convertIntArray(unsigned char inputData[],unsigned int unInputDataLen,int output[]);
void convertCharArray(int input[],int len,unsigned char output[]);
void R(int array[]);
unsigned int SMS4_encrypt(unsigned char key[],unsigned int keyLen,unsigned char *inputData,unsigned int unInputDataLen,unsigned char *outputData,unsigned int * outputDataLen);
unsigned int SMS4_decrypt(unsigned char key[],unsigned int keyLen,unsigned char *inputData,unsigned int unInputDataLen, unsigned char *outputData,unsigned int * outputDataLen);
void print_Hex(unsigned char array[],unsigned int length);


unsigned int Mode_SMS4_encrypt(unsigned char key[],unsigned int keyLen,unsigned char iv[],unsigned char *inputData,unsigned int unInputDataLen,unsigned char *outputData,unsigned int * outputDataLen,int mode);
unsigned int Mode_SMS4_decrypt(unsigned char key[],unsigned int keyLen,unsigned char iv[],unsigned char *inputData,unsigned int unInputDataLen, unsigned char *outputData,unsigned int * outputDataLen,int mode);

#endif