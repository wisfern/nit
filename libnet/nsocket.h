/*
 * nsocket.h
 *
 *  Created on: 2014年12月27日
 *      Author: wisfern
 */

#ifndef NSOCKET_H_
#define NSOCKET_H_

#include <stddef.h>
#include "oswrapper.h"

/**
 * 服务绑定在port端口，地址为0.0.0.0
 * @param port 被绑定的端口
 * @return >0 绑定成功的socket -1 绑定失败，失败原因：记录在errno中
 */
socket_t n_bind(const int port);

/**
 * 接受socket连线
 * @param fd_listen_ 监听状态的socket fd
 * @param timeout 超时时间，单位：us
 * @param o_remote_ip  存放远程客户端char*的ip地址，0.0.0.0类似
 * @param o_port 存在远程连接的端口号
 * @return 成功则返回新的socket fd，失败返回-1，失败原因存于errno中。
 */
socket_t n_accept(socket_t fd_listen_, unsigned int timeout=3000000, char* o_remote_ip=NULL, int* o_port=NULL);

/**
 * @brief 判断fd_是否有数据可读，带超时返回
 * @param timout 超时时间，单位：us
 * @return 1 有数据  0 超时  -1 有错误发生，错误码记录在errno中
 */
int n_select_read(socket_t fd_, unsigned int timeout);

/**
 * 连接ip_：port_
 * @param ip_
 * @param port_
 * @param timeout
 * @return 成功返回新的socket，失败返回-1，
 */
socket_t n_connect(const char* ip_, const int port_, const unsigned int timeout);

/**
 * @brief 读取数据
 * @param fd_conn socket fd
 * @param buff 输出buffer
 * @param len  需要读取的最大len字节
 * @param timeout 超时，单位：us
 * @return >0 实际读取长度  0 无数据  <0 错误，错误码存储在errno中
 */
int n_read_data(socket_t fd_conn, void* buff, int len, const unsigned int timeout);

/**
 * 获取socket本地的连接信息，本地ip和端口
 * @param fd_conn
 * @param ip_ 存储char* 类型的ip地址
 * @param len_ ip_的长度，单位：字节
 * @param port_ 端口存储
 * @return 成功则返回0，失败返回-1，错误原因存于errno
 */
int n_sock_info(socket_t fd_conn, char* ip_, int len_, int* port_);

/**
 * 获取socket相连端信息，远端ip和端口
 * @param fd_conn
 * @param ip_ 存储char* 类型的ip地址
 * @param len_ ip_的长度，单位：字节
 * @param port_ 端口存储
 * @return 成功则返回0，失败返回-1，错误原因存于errno
 */
int n_peer_info(socket_t fd_conn, char* ip_, int len_, int* port_);


#endif /* NSOCKET_H_ */
