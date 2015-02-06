/*
 * oswrapper.h
 *
 *  Created on: 2014Äê12ÔÂ27ÈÕ
 *      Author: wisfern
 */

#ifndef OSWRAPPER_H_
#define OSWRAPPER_H_


#ifdef _WIN_
# include <winsock2.h>
typedef SOCKET socket_t;
#else
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
typedef int socket_t;
#endif


#endif /* OSWRAPPER_H_ */
