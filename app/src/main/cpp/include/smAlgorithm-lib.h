//
// Created by admin on 2019/4/22.
//

#ifndef SMALGORITHM_SMALGORITHM_LIB_H
#define SMALGORITHM_SMALGORITHM_LIB_H
extern "C" {
#include "sm2.h"
#include "sm3.h"
#include "sms4.h"
};


#define RC_U8 unsigned char
#define RC_U32 unsigned int

#define SM3_KEY_LEN_ERROR 10

#define SM4_KEY_LEN_ERROR 12
#define SM4_INPUT_IS_NULL 13
#define SM4_CBC_LEN_ERROR 14

#define SM2_PUBLIC_KEY_LEN_ERROR 15
#define SM2_PRIVATE_KEY_LEN_ERROR 16
#define SM2_SIGN_LEN_ERROR 17

#define SM2_PRIVATE_KEY_LEN 32
#define SM2_PUBLIC_KEY_LEN 64
#define SM2_SIGN_LEN 64
#define SM3_KEY_LEN 32

#endif
