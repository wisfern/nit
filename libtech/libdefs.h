/*
 *  @file libdefs.h
 *  @short common define
 *
 *  Created on: 2013-1-4
 *      Author: Wisfern
 */

#pragma once  // VS使用的定义，gcc也支持

#ifndef NIT_LIB_DEFS_H  // C++标准的定义方法
#define NIT_LIB_DEFS_H

/*
 * 工程库的配置
 */
#include "libconfig.h"

/*
 * 使用<stdint.h>来提供定长的整型数字
 * 分别是如下的几个类型
 * int8_t、int16_t、int32_t、int64_t;
 * uint8_t、uint16_t、uint32_t、uint64_t;
 * intptr_t、uintptr_t(整形指针类型)
 * 
 * 以及先包含常用的头文件
 */
#include <stdint.h>

#ifdef __cplusplus
# include <string>
  __USING_STD(string)
#endif

//通用包含
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>

#ifdef OS_WIN32 //windows下特定包含
# include <conio.h>
# include <windows.h>
# include <process.h>
# include <winsock.h>
#else		 //Linux Unix下特定包含
# include <unistd.h>
# include <pthread.h>
# include <termios.h>
# include <errno.h>
# include <sys/time.h>
#endif

/*
 * 自定义安全函数集
 */
#include "libmissing.h"

/*
 * 平台函数差异
 */
#ifdef WIN32
//template class NIT_API std::allocator<char>;   
  template class NIT_API std::basic_string<char>; // C4251
# define snprintf _snprintf
//# define vsnprintf vsnprintf
# define stricmp _stricmp
//# define localtime localtim
#else
# define stricmp strcasecmp
#endif

/*
 * 跨平台锁
 * WIN32，使用临界区来实现
 * LINUX，使用互斤变量来实现
 */
#ifdef OS_WIN32
	//定义锁变量类型
	#define MUTEX CRITICAL_SECTION
	//定义初始化锁的功能
	#define MUTEXINIT(m) InitializeCriticalSection(m)
	//定义加锁
	#define MUTEXLOCK(m) EnterCriticalSection(m)
	//定义尝试加锁
	#define MUTEXTRYLOCK(m) TryEnterCriticalSection(m)
	//定义解锁
	#define MUTEXUNLOCK(m) LeaveCriticalSection(m)
	//定义摧毁锁变量操作
	#define MUTEXDESTROY(m) DeleteCriticalSection(m)
#else
	//定义锁变量类型
	#define MUTEX pthread_mutex_t
	//定义初始化锁的功能
	#define MUTEXINIT(m) pthread_mutex_init(m, NULL) //TODO: check error
	//定义加锁
	#define MUTEXLOCK(m) pthread_mutex_lock(m)
	//定义尝试加锁
	#define MUTEXTRYLOCK(m) pthread_mutex_trylock(m)
	//定义解锁
	#define MUTEXUNLOCK(m) pthread_mutex_unlock(m)
	//定义摧毁锁变量操作
	#define MUTEXDESTROY(m) pthread_mutex_destroy(m)
#endif

/*
 * 跨平台线程
 * WIN32平台与LINUX平台线程实现上的差异，工程库需要屏蔽掉

#ifdef WIN32 //Windows下定义
	#include <process.h>
	//线程句柄类型
	#define THREAD HANDLE
	//线程ID类型
	#define THREADID unsigned
	//线程启动函数统一构型，注意函数型宏的使用
	#define THREADCREATE(func, args, thread, id) \
	thread = (HANDLE)_beginthreadex(NULL, 0, func, (PVOID)args, 0, &id);
	//线程启动失败后返回错误码定义
	#define THREADCREATE_ERROR NULL
	//线程函数标准构型
	#define THREADFUNCDECL(func,args) unsigned __stdcall func(PVOID args)
	//工程中通常需要检测本次开机以来的毫秒数，Windows和Linux不一样，此处予以统一。
	#define _GetTimeOfDay GetTickCount
	//Windows下最小睡眠精度，经实测为10ms
	#define MIN_SLEEP 10
#else //Linux下定义
	//线程句柄类型
	#define THREAD pthread_t
	//线程ID类型
	#define THREADID unsigned //unused for Posix Threads
	//线程启动函数统一构型，注意函数型宏的使用
	#define THREADCREATE(func, args, thread, id) \
	pthread_create(&thread, NULL, func, args);
	//线程启动失败后返回错误码定义
	#define THREADCREATE_ERROR -1
	//线程函数标准构型
	#define THREADFUNCDECL(func,args) void * func(void *args)
	//#define Sleep(ms) usleep((__useconds_t)(ms*1000))
	//工程中通常需要检测本次开机以来的毫秒数，Windows和Linux不一样，此处予以统一。
	unsigned long GetTickCount(void);
	#include <sys/time.h>
	#define _GetTimeOfDay GetTickCount
	//Linux下没有Sleep函数，为了便于统一编程，仿照Windows下定义该函数
	#define Sleep(ms) usleep(ms*1000)
	#define MIN_SLEEP 1
#endif


#ifdef WIN32 //Windows下定义
	//Windows下有此函数，无需重复定义
#else //Linux下定义
	//获得本次开机以来毫秒数
	Inline unsigned long GetTickCount(void)
	{
		unsigned long lRet=0;
		struct timeval tv;
		gettimeofday(&tv,null);
		lRet=tv.tv_usec/1000;
		return lRet;
	}
#endif
 *
 */

/*
 * Socket传输相关

#ifdef WIN32 //Windows下定义
	#include <winsock.h>
	//定义Socket套接字变量类型
	#define Linux_Win_SOCKET SOCKET
	//标准的Socket关闭函数，不过，由于后文资源池接管了关闭动作，此处隐去定义
	//#define Linux_Win_CloseSocket closesocket
	//协议族命名约定
	#define Linux_Win_F_INET AF_INET
	//非法的socket表示值定义
	#define Linux_Win_InvalidSocket INVALID_SOCKET
	//标准socket错误返回码
	#define Linux_Win_SocketError SOCKET_ERROR
	//setsockopt第4个变量类型定义
	#define Linux_Win_SetSockOptArg4UseType const char
	//getsockopt第4个变量类型定义
	#define Linux_Win_GetSockOptArg4UseType char
	//send recv函数的最后一个参数类型
	#define Linux_Win_SendRecvLastArg 0
	
	//注意此处，所有的错误返回码定名，Windows平台向向标准的伯克利socket规范靠拢。
	#define EWOULDBLOCK WSAEWOULDBLOCK //10035
	#define EINPROGRESS WSAEINPROGRESS
	#define EALREADY WSAEALREADY
	#define ENOTSOCK WSAENOTSOCK
	#define EDESTADDRREQ WSAEDESTADDRREQ
	#define EMSGSIZE WSAEMSGSIZE
	#define EPROTOTYPE WSAEPROTOTYPE
	#define ENOPROTOOPT WSAENOPROTOOPT
	#define EPROTONOSUPPORT WSAEPROTONOSUPPORT
	#define ESOCKTNOSUPPORT WSAESOCKTNOSUPPORT
	#define EOPNOTSUPP WSAEOPNOTSUPP
	#define EPFNOSUPPORT WSAEPFNOSUPPORT
	#define EAFNOSUPPORT WSAEAFNOSUPPORT
	#define EADDRINUSE WSAEADDRINUSE
	#define EADDRNOTAVAIL WSAEADDRNOTAVAIL
	#define ENETDOWN WSAENETDOWN
	#define ENETUNREACH WSAENETUNREACH
	#define ENETRESET WSAENETRESET
	#define ECONNABORTED WSAECONNABORTED //10053
	#define ECONNRESET WSAECONNRESET     //10054
	#define ENOBUFS WSAENOBUFS
	#define EISCONN WSAEISCONN
	#define ENOTCONN WSAENOTCONN
	#define ESHUTDOWN WSAESHUTDOWN
	#define ETOOMANYREFS WSAETOOMANYREFS
	#define ETIMEDOUT WSAETIMEDOUT
	#define ECONNREFUSED WSAECONNREFUSED
	#define ELOOP WSAELOOP
	#define EHOSTDOWN WSAEHOSTDOWN
	#define EHOSTUNREACH WSAEHOSTUNREACH
	#define EPROCLIM WSAEPROCLIM
	#define EUSERS WSAEUSERS
	#define EDQUOT WSAEDQUOT
	#define ESTALE WSAESTALE
	#define EREMOTE WSAEREMOTE
#else //Linux下定义
	//定义Socket套接字变量类型
	#define Linux_Win_SOCKET int
	//标准的Socket关闭函数，不过，由于后文资源池接管了关闭动作，此处隐去定义
	//#define Linux_Win_CloseSocket close
	//协议族命名约定
	#define Linux_Win_F_INET AF_INET
	//非法的socket表示值定义
	#define Linux_Win_InvalidSocket -1
	//标准socket错误返回码
	#define Linux_Win_SocketError -1
	//setsockopt第4个变量类型定义
	#define Linux_Win_SetSockOptArg4UseType void
	//getsockopt第4个变量类型定义
	#define Linux_Win_GetSockOptArg4UseType void
	//send recv函数的最后一个参数类型
	#define Linux_Win_SendRecvLastArg MSG_NOSIGNAL
#endif

 * SOCKET 暂时不支持，代码来自0 BUG 商用工程
 */

#endif /* end #ifndef NIT_LIB_DEFS_H */