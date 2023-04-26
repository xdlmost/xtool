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
  cstr_t name;
  bool_t is_up;
  cstr_t mac_addr;
  cstr_t ipv4_addr;
} x_net_interface_info_t;

X_API i32_t x_net_desroty_interface_info(x_net_interface_info_t* infos, u32_t infos_count);


/**
 * @brief 
 * 
 * @return X_API 
 */
X_API i32_t x_net_init();

X_API i32_t x_get_local_net_interface_infos(x_net_interface_info_t **out_infos, u32_t *out_infos_count);

__X_END_DECLS
#endif //__X_NET_H