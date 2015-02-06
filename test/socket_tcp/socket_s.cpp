/*
 * sock.cpp
 *
 *  Created on: 2014Äê12ÔÂ27ÈÕ
 *      Author: wisfern
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "oswrapper.h"
#include "nsocket.h"

void getSocketInfo(socket_t fd)
{
	int lport = 0;
	int rport = 0;
	char lip[16] = {0};
	char rip[16] = {0};

	n_sock_info(fd, lip, sizeof(lip), &lport);
	n_peer_info(fd, rip, sizeof(rip), &rport);

	printf("new connect [L:%s:%d -- R:%s:%d]\n", lip, lport, rip, rport);
}

socket_t socketAccept(socket_t fd)
{
	socket_t client;
	char remote_ip[16] = {0};
	int remote_port = 0;

	if ((client = n_accept(fd, 1000000, remote_ip, &remote_port)) > 0)
		getSocketInfo(client);

	if (client < 0)
		printf("socket accept faile: %d - %s\n", errno, strerror(errno));
	else
		printf("socket accept client(%d)\n", client);

	return client;
}

int main(int argc, char* argv[])
{
	printf("server starting...\n");

	socket_t serv;
	if ((serv = n_bind(9999)) == -1)
	{
		perror("bind error");
		return -1;
	}

	printf("bind(%d) success\n", serv);

	unsigned long count = 0;
	unsigned long c_c = 0;
	socket_t client;
	while(1)
	{
		client = socketAccept(serv);
		if (client>0)
			break;

		if (c_c > 0 && c_c % 10 == 0 )
			break;

		if (count++ % 10 == 0)
			printf("wait(%5ld)¡­¡­\n", count);
	}

	char for_read[1024] = {0};
	int ret = 0;
	int len = 0;
	while(1)
	{
		ret = n_read_data(client, for_read+len, sizeof(for_read), 10000000);
		if( ret < 0) {
			perror("read error");
			break;
		}

		if (ret == 0 || (ret > 0 && ret <= (signed int)sizeof(for_read))) {
			printf("read end\n");
			break;
		}

		len += ret;
	}

	printf("server: get data [%s]\n", for_read);

	memset(for_read, 0, sizeof(for_read));
	strcpy(for_read, "ok, i get!");
	ret = write(client, for_read, strlen(for_read));
	if (ret < 0)
		perror("write socket error");

	printf("server closing! \n");
	close(client);
	close(serv);

	return 0;
}
