/* *Copyright (c) 2012, 武汉大学密码研究中心* 
   *All rights reserved.* 
   *
   *文件名称：Config.h
   *摘    要：配置头文件
   *作    者: 孙金龙
   *时    间: 2012.3.14 11:06
   *最新版本: v1.0.0
*/
#ifndef __HEADER_CONFIG_H
#define __HEADER_CONFIG_H

#ifdef  __cplusplus
extern "C" {
#endif


#define BNWORDLEN			8
#define MAXBNWordLen		8
#define WordByteLen			4
#define WordBitLen			32
#define MAXBNByteLen		MAXBNWordLen*WordByteLen
#define MAXBNBitLen			MAXBNByteLen*8
#define MAXPLAINTEXTLEN		1024
#define MAX2BNByteLen       2*MAXBNByteLen
#define HASHLEN             32


#ifdef  __cplusplus
}
#endif

#endif
