#include "libmissing.h"
#include "libdefs.h"

__USING_NIT_NS

#ifdef __cplusplus
extern "C" {
#endif

char* nit_strncpy_s(char *pDest, char *pFrom, size_t count)
{
	size_t len_d = strlen(pDest) + 1;
	if (len_d > count) len_d = count;	  // 两个大小取小者
	memcpy(pDest, pFrom, len_d);
	*(pDest+len_d - 1) = '\0';
	
	return pDest;
}

#ifdef __cplusplus
}
#endif
