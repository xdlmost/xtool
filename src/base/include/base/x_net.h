/****************************************************
 * Author: xdlmost(xdeliver@163.com)
 * Description: 
 * Note: 
 ****************************************************/
#ifndef __X_NET_H
#define __X_NET_H 1
#include "predefine.h"
__X_BEGIN_DECLS

// x_net status
#define X_NET_OK 0
#define X_NET_SOCKET_CREATE_FAIL 1
#define X_NET_GET_IFCONF_FAIL 2
#define X_NET_NO_IFCONF 3
#define X_NET_OUT_ARG_IS_NULL 4

typedef struct
{
  char name[16];
  int index;
  bool_t is_up;
  char mac[18];
  char ip[16];
  char broadcast[16];
  char mask[16];
  int mtu;
  char ipv6[46];
  int ipv6_prefix;
  char ipv6_scope[8];
} x_net_interface_info_t;

/**
 * @brief 
 * 
 * @return X_API 
 */
X_API(i32_t) x_net_init();

X_API(i32_t) x_get_local_net_interface_infos(x_net_interface_info_t **out_infos, u32_t *out_infos_count);

__X_END_DECLS
#endif //__X_NET_H