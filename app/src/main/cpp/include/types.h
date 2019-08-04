/* *Copyright (c) 2007, 武汉大学密码研究中心* 
   *All rights reserved.* 
   *
   *文件名称：types.h
   *摘    要：定义基本公共结构
   *作    者: 孙金龙
   *时    间: 2007.5.3 21:05
   *最新版本: v1.0.0
*/
#ifndef __HEADER_TYPES_H
#define __HEADER_TYPES_H

#include "config.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define Byte   unsigned char
#define BYTE   unsigned char
#define Word   unsigned int
#ifdef _WINDOWS_
#define SDWord __int64
#define DWord  unsigned __int64
#else
#define SDWord long long
#define DWord  unsigned long long
#endif
#define MSBOfWord	0x80000000
#define LSBOfWord	0x00000001

#ifdef  __cplusplus
}
#endif


#endif
