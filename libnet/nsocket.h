/*
 * nsocket.h
 *
 *  Created on: 2014��12��27��
 *      Author: wisfern
 */

#ifndef NSOCKET_H_
#define NSOCKET_H_

#include <stddef.h>
#include "oswrapper.h"

/**
 * �������port�˿ڣ���ַΪ0.0.0.0
 * @param port ���󶨵Ķ˿�
 * @return >0 �󶨳ɹ���socket -1 ��ʧ�ܣ�ʧ��ԭ�򣺼�¼��errno��
 */
socket_t n_bind(const int port);

/**
 * ����socket����
 * @param fd_listen_ ����״̬��socket fd
 * @param timeout ��ʱʱ�䣬��λ��us
 * @param o_remote_ip  ���Զ�̿ͻ���char*��ip��ַ��0.0.0.0����
 * @param o_port ����Զ�����ӵĶ˿ں�
 * @return �ɹ��򷵻��µ�socket fd��ʧ�ܷ���-1��ʧ��ԭ�����errno�С�
 */
socket_t n_accept(socket_t fd_listen_, unsigned int timeout=3000000, char* o_remote_ip=NULL, int* o_port=NULL);

/**
 * @brief �ж�fd_�Ƿ������ݿɶ�������ʱ����
 * @param timout ��ʱʱ�䣬��λ��us
 * @return 1 ������  0 ��ʱ  -1 �д��������������¼��errno��
 */
int n_select_read(socket_t fd_, unsigned int timeout);

/**
 * ����ip_��port_
 * @param ip_
 * @param port_
 * @param timeout
 * @return �ɹ������µ�socket��ʧ�ܷ���-1��
 */
socket_t n_connect(const char* ip_, const int port_, const unsigned int timeout);

/**
 * @brief ��ȡ����
 * @param fd_conn socket fd
 * @param buff ���buffer
 * @param len  ��Ҫ��ȡ�����len�ֽ�
 * @param timeout ��ʱ����λ��us
 * @return >0 ʵ�ʶ�ȡ����  0 ������  <0 ���󣬴�����洢��errno��
 */
int n_read_data(socket_t fd_conn, void* buff, int len, const unsigned int timeout);

/**
 * ��ȡsocket���ص�������Ϣ������ip�Ͷ˿�
 * @param fd_conn
 * @param ip_ �洢char* ���͵�ip��ַ
 * @param len_ ip_�ĳ��ȣ���λ���ֽ�
 * @param port_ �˿ڴ洢
 * @return �ɹ��򷵻�0��ʧ�ܷ���-1������ԭ�����errno
 */
int n_sock_info(socket_t fd_conn, char* ip_, int len_, int* port_);

/**
 * ��ȡsocket��������Ϣ��Զ��ip�Ͷ˿�
 * @param fd_conn
 * @param ip_ �洢char* ���͵�ip��ַ
 * @param len_ ip_�ĳ��ȣ���λ���ֽ�
 * @param port_ �˿ڴ洢
 * @return �ɹ��򷵻�0��ʧ�ܷ���-1������ԭ�����errno
 */
int n_peer_info(socket_t fd_conn, char* ip_, int len_, int* port_);


#endif /* NSOCKET_H_ */
