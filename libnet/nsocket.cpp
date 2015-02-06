/*
 * nsocket.cpp
 *
 *  Created on: 2014年12月27日
 *      Author: wisfern
 */

#include "nsocket.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

socket_t n_bind(const int port_)
{
	socket_t sock;
	int on = 1;
	struct sockaddr_in server_addr;

	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		return -1;

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_port = htons(port_);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		return -1;

	if (listen(sock, 5) == -1)
		return -1;

	return sock;
}

socket_t n_accept(socket_t fd_listen_, unsigned int timeout, char* o_remote_ip, int* o_port)
{
	int len, ret;
	socket_t fd;
	struct sockaddr_in client;

	if ((ret = n_select_read(fd_listen_, timeout)) != 1)
		return ret;  // -1 出错， 0 超时

	if ((fd = accept(fd_listen_, (struct sockaddr *)&client, &len)) == -1)
		return -1;

	if (o_remote_ip)
		strcpy(o_remote_ip, inet_ntoa(client.sin_addr));

	if (o_port)
		*o_port = ntohs(client.sin_port);

	return fd;
}

/* 返回值： 1：有数据可读取  0: 超时  -1：有错误发生  */
int n_select_read(int fd_, unsigned int timeout)
{
	int n;
	fd_set rfds;
	struct timeval tv;

	FD_ZERO(&rfds);
	FD_SET(fd_, &rfds);
	tv.tv_sec = timeout / 1000000;
	tv.tv_usec = timeout % 1000000;

	if ((n = select(fd_+1, &rfds, NULL, NULL, &tv)) <= 0)
		return n;

	if (FD_ISSET(fd_, &rfds))
		return 1;

	return -1;
}

socket_t n_connect(const char* ip_, const int port_, const unsigned int timeout)
{
	socket_t fd;
	struct sockaddr_in addr;

	if ((fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		return -1;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port_);
	if (inet_pton(AF_INET, ip_, &addr.sin_addr) <= 0 )
	{
		close(fd);
		return -1;
	}

	if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		return -1;

	return fd;
}

int n_read_data(socket_t fd_conn, void* buff, int len, const unsigned int timeout)
{
	int ret = 0;
	if ((ret = n_select_read(fd_conn, timeout)) == 1)
		ret = read(fd_conn, buff, len);

	return ret;
}

int n_sock_info(socket_t fd_conn, char* ip_, int len_, int* port_)
{
	struct sockaddr_in addr;
	socklen_t slen = sizeof(addr);

	if (getsockname(fd_conn, (struct sockaddr*)&addr, &slen) == -1)
		return -1;

	if (ip_)
		inet_ntop(AF_INET, &addr.sin_addr, ip_, len_);

	if (port_)
		*port_ = ntohs(addr.sin_port);

	return 0;
}

int n_peer_info(socket_t fd_conn, char* ip_, int len_, int* port_)
{
	struct sockaddr_in addr;
	socklen_t slen = sizeof(addr);

	if (getpeername(fd_conn, (struct sockaddr*)&addr, &slen) == -1)
		return -1;

	if (ip_)
		inet_ntop(AF_INET, &addr.sin_addr, ip_, len_);

	if (port_)
		*port_ = ntohs(addr.sin_port);

	return 0;
}

