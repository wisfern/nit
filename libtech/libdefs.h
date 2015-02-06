/*
 *  @file libdefs.h
 *  @short common define
 *
 *  Created on: 2013-1-4
 *      Author: Wisfern
 */

#pragma once  // VSʹ�õĶ��壬gccҲ֧��

#ifndef NIT_LIB_DEFS_H  // C++��׼�Ķ��巽��
#define NIT_LIB_DEFS_H

/*
 * ���̿������
 */
#include "libconfig.h"

/*
 * ʹ��<stdint.h>���ṩ��������������
 * �ֱ������µļ�������
 * int8_t��int16_t��int32_t��int64_t;
 * uint8_t��uint16_t��uint32_t��uint64_t;
 * intptr_t��uintptr_t(����ָ������)
 * 
 * �Լ��Ȱ������õ�ͷ�ļ�
 */
#include <stdint.h>

#ifdef __cplusplus
# include <string>
  __USING_STD(string)
#endif

//ͨ�ð���
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>

#ifdef OS_WIN32 //windows���ض�����
# include <conio.h>
# include <windows.h>
# include <process.h>
# include <winsock.h>
#else		 //Linux Unix���ض�����
# include <unistd.h>
# include <pthread.h>
# include <termios.h>
# include <errno.h>
# include <sys/time.h>
#endif

/*
 * �Զ��尲ȫ������
 */
#include "libmissing.h"

/*
 * ƽ̨��������
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
 * ��ƽ̨��
 * WIN32��ʹ���ٽ�����ʵ��
 * LINUX��ʹ�û��������ʵ��
 */
#ifdef OS_WIN32
	//��������������
	#define MUTEX CRITICAL_SECTION
	//�����ʼ�����Ĺ���
	#define MUTEXINIT(m) InitializeCriticalSection(m)
	//�������
	#define MUTEXLOCK(m) EnterCriticalSection(m)
	//���峢�Լ���
	#define MUTEXTRYLOCK(m) TryEnterCriticalSection(m)
	//�������
	#define MUTEXUNLOCK(m) LeaveCriticalSection(m)
	//����ݻ�����������
	#define MUTEXDESTROY(m) DeleteCriticalSection(m)
#else
	//��������������
	#define MUTEX pthread_mutex_t
	//�����ʼ�����Ĺ���
	#define MUTEXINIT(m) pthread_mutex_init(m, NULL) //TODO: check error
	//�������
	#define MUTEXLOCK(m) pthread_mutex_lock(m)
	//���峢�Լ���
	#define MUTEXTRYLOCK(m) pthread_mutex_trylock(m)
	//�������
	#define MUTEXUNLOCK(m) pthread_mutex_unlock(m)
	//����ݻ�����������
	#define MUTEXDESTROY(m) pthread_mutex_destroy(m)
#endif

/*
 * ��ƽ̨�߳�
 * WIN32ƽ̨��LINUXƽ̨�߳�ʵ���ϵĲ��죬���̿���Ҫ���ε�

#ifdef WIN32 //Windows�¶���
	#include <process.h>
	//�߳̾������
	#define THREAD HANDLE
	//�߳�ID����
	#define THREADID unsigned
	//�߳���������ͳһ���ͣ�ע�⺯���ͺ��ʹ��
	#define THREADCREATE(func, args, thread, id) \
	thread = (HANDLE)_beginthreadex(NULL, 0, func, (PVOID)args, 0, &id);
	//�߳�����ʧ�ܺ󷵻ش����붨��
	#define THREADCREATE_ERROR NULL
	//�̺߳�����׼����
	#define THREADFUNCDECL(func,args) unsigned __stdcall func(PVOID args)
	//������ͨ����Ҫ��Ȿ�ο��������ĺ�������Windows��Linux��һ�����˴�����ͳһ��
	#define _GetTimeOfDay GetTickCount
	//Windows����С˯�߾��ȣ���ʵ��Ϊ10ms
	#define MIN_SLEEP 10
#else //Linux�¶���
	//�߳̾������
	#define THREAD pthread_t
	//�߳�ID����
	#define THREADID unsigned //unused for Posix Threads
	//�߳���������ͳһ���ͣ�ע�⺯���ͺ��ʹ��
	#define THREADCREATE(func, args, thread, id) \
	pthread_create(&thread, NULL, func, args);
	//�߳�����ʧ�ܺ󷵻ش����붨��
	#define THREADCREATE_ERROR -1
	//�̺߳�����׼����
	#define THREADFUNCDECL(func,args) void * func(void *args)
	//#define Sleep(ms) usleep((__useconds_t)(ms*1000))
	//������ͨ����Ҫ��Ȿ�ο��������ĺ�������Windows��Linux��һ�����˴�����ͳһ��
	unsigned long GetTickCount(void);
	#include <sys/time.h>
	#define _GetTimeOfDay GetTickCount
	//Linux��û��Sleep������Ϊ�˱���ͳһ��̣�����Windows�¶���ú���
	#define Sleep(ms) usleep(ms*1000)
	#define MIN_SLEEP 1
#endif


#ifdef WIN32 //Windows�¶���
	//Windows���д˺����������ظ�����
#else //Linux�¶���
	//��ñ��ο�������������
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
 * Socket�������

#ifdef WIN32 //Windows�¶���
	#include <winsock.h>
	//����Socket�׽��ֱ�������
	#define Linux_Win_SOCKET SOCKET
	//��׼��Socket�رպ��������������ں�����Դ�ؽӹ��˹رն������˴���ȥ����
	//#define Linux_Win_CloseSocket closesocket
	//Э��������Լ��
	#define Linux_Win_F_INET AF_INET
	//�Ƿ���socket��ʾֵ����
	#define Linux_Win_InvalidSocket INVALID_SOCKET
	//��׼socket���󷵻���
	#define Linux_Win_SocketError SOCKET_ERROR
	//setsockopt��4���������Ͷ���
	#define Linux_Win_SetSockOptArg4UseType const char
	//getsockopt��4���������Ͷ���
	#define Linux_Win_GetSockOptArg4UseType char
	//send recv���������һ����������
	#define Linux_Win_SendRecvLastArg 0
	
	//ע��˴������еĴ��󷵻��붨����Windowsƽ̨�����׼�Ĳ�����socket�淶��£��
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
#else //Linux�¶���
	//����Socket�׽��ֱ�������
	#define Linux_Win_SOCKET int
	//��׼��Socket�رպ��������������ں�����Դ�ؽӹ��˹رն������˴���ȥ����
	//#define Linux_Win_CloseSocket close
	//Э��������Լ��
	#define Linux_Win_F_INET AF_INET
	//�Ƿ���socket��ʾֵ����
	#define Linux_Win_InvalidSocket -1
	//��׼socket���󷵻���
	#define Linux_Win_SocketError -1
	//setsockopt��4���������Ͷ���
	#define Linux_Win_SetSockOptArg4UseType void
	//getsockopt��4���������Ͷ���
	#define Linux_Win_GetSockOptArg4UseType void
	//send recv���������һ����������
	#define Linux_Win_SendRecvLastArg MSG_NOSIGNAL
#endif

 * SOCKET ��ʱ��֧�֣���������0 BUG ���ù���
 */

#endif /* end #ifndef NIT_LIB_DEFS_H */