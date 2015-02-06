/*
 *  @file libmiss.h
 *  @short common define
 *
 *  Created on: 2013-1-17
 *      Author: Wisfern
 */

#pragma once  // VS使用的定义，gcc也支持

#ifndef NIT_LIB_MISSING_H  // C++标准的定义方法
#define NIT_LIB_MISSING_H

#include "libconfig.h"
#include "libdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

__NIT_NAMESPACE_BEGIN

// strncpy的自定义安全版本，nit_strncpy_s
NIT_API char* nit_strncpy_s(char *pDest, char *pFrom, size_t count);

#define strncpy nit_strncpy_s

// vnsprintf的自定义安全版本，nit_vnsprintf_s


//

__NIT_NAMESPACE_END

#ifdef __cplusplus
}
#endif

#endif /* ifndef NIT_LIB_MISSING_H */
