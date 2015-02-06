/*
 *  @file libmiss.h
 *  @short common define
 *
 *  Created on: 2013-1-17
 *      Author: Wisfern
 */

#pragma once  // VSʹ�õĶ��壬gccҲ֧��

#ifndef NIT_LIB_MISSING_H  // C++��׼�Ķ��巽��
#define NIT_LIB_MISSING_H

#include "libconfig.h"
#include "libdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

__NIT_NAMESPACE_BEGIN

// strncpy���Զ��尲ȫ�汾��nit_strncpy_s
NIT_API char* nit_strncpy_s(char *pDest, char *pFrom, size_t count);

#define strncpy nit_strncpy_s

// vnsprintf���Զ��尲ȫ�汾��nit_vnsprintf_s


//

__NIT_NAMESPACE_END

#ifdef __cplusplus
}
#endif

#endif /* ifndef NIT_LIB_MISSING_H */
