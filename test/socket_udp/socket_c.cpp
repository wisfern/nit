/*
 * client.cpp
 *
 *  Created on: 2014年12月27日
 *      Author: wisfern
 */

#include "nsocket.h"
#include "oswrapper.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

extern int errno;

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


int main(int argc, char* argv[])
{
	int on = 1;
	socket_t client;
	struct sockaddr_in addr;
	char for_send[256] = "my name is client, hello server， 你好，服务器!\0";

	if ((client = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1 )
	{
		printf("[E] create socket error : %s\n", strerror(errno));
	}
	setsockopt(client, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));


	addr.sin_port = htons(9999);
	addr.sin_family = AF_INET;
	if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) <= 0)
	{
		close(client);
		return -1;
	}

	if ((connect(client, (const sockaddr *)&addr, sizeof(addr))) == -1) {
		printf("[E] connect server error: %s\n", strerror(errno));
		return -1;
	} else {
		printf("[I] connect server success!\n");
		getSocketInfo(client);
	}

	if (write(client, for_send, strlen(for_send)) == -1) {
		perror("write socket error");
		return -1;
	}

	memset(for_send, 0, sizeof(for_send));

	int ret = 0;
	int len = 0;
	while(1)
	{
		ret = n_read_data(client, for_send+len, sizeof(for_send), 10000000);
		if( ret < 0) {
			perror("read error");
			break;
		}

		if (ret == 0 || (ret > 0 && ret <= (signed int)sizeof(for_send))) {
			printf("read end\n");
			break;
		}

		len += ret;
	}

	printf("client: get data [%s]\n", for_send);

	printf("client process exit!\n");

	return 0;
}
