#include "base/x_memory.h"
#include "base/x_net.h"
#include <net/if.h>
#include <sys/ioctl.h>
// #include <linux/sockios.h>

i32_t 
x_net_desroty_interface_info(x_net_interface_info_t* infos, u32_t infos_count)
{
  if(infos) {
    u32_t i = 0;
    for (i = 0; i < infos_count; ++i) {
      if (infos[i].name) {
        x_free(infos[i].name);
        infos[i].name = NULL;
      }

      if (infos[i].mac_addr) {
        x_free(infos[i].mac_addr);
        infos[i].mac_addr = NULL;
      }

      if (infos[i].ipv4_addr) {
        x_free(infos[i].ipv4_addr);
        infos[i].ipv4_addr = NULL;
      }
    }
    x_free(infos);
  }
  return 0;
}

i32_t 
x_net_init()
{
  return X_NET_OK;
}

i32_t 
x_get_local_net_interface_infos(x_net_interface_info_t **out_infos, u32_t *out_infos_count)
{
  i32_t ret = X_NET_OK;
  int net_device = 0;
  struct ifconf ifc;
  str_t ifreq_buff = NULL;
  u32_t ifc_req_counts = 0;
  x_net_interface_info_t *get_infos = NULL;
  int i = 0;

  // 0- check
  if((!out_infos) || (!out_infos_count)) {
    ret = X_NET_OUT_ARG_IS_NULL;
    goto error;
  }

  // 1- create net device 
  // On success, a file descriptor for the new socket is returned.  
  // On error, -1 is returned, and errno is set to indicate the error.
  // http://man7.org/linux/man-pages/man2/socket.2.html
  if ((net_device = socket(AF_INET, SOCK_DGRAM, 0))< 0) {
    // TODO: get error from errno
    ret = X_NET_SOCKET_CREATE_FAIL;
    goto error;
  }

  // 2- get net interface count
  // Usually, on success zero is returned.  
  // A few ioctl() requests use the return value as an output parameter and return a nonnegative value on success.  
  // On error, -1 is returned, and errno is set to indicate the error.
  x_memzero(&ifc, sizeof(struct ifconf));
  if (ioctl(net_device, SIOCGIFCONF, &ifc) <0) {
    // TODO: get error from errno
    ret = X_NET_GET_IFCONF_FAIL;
    goto error;
  }

  if (0 == ifc.ifc_len){
    ret = X_NET_NO_IFCONF;
    goto error;
  }

  // 3- get net interfaces
  ifreq_buff = x_calloc(ifc.ifc_len, 1);
  ifc.ifc_buf = ifreq_buff;
  if (ioctl(net_device, SIOCGIFCONF, &ifc) <0) {
    // TODO: get error from errno
    ret = X_NET_GET_IFCONF_FAIL;
    goto error;
  }

  ifc_req_counts = ifc.ifc_len / sizeof(struct ifreq);
  get_infos = x_calloc(sizeof(x_net_interface_info_t), ifc_req_counts);

  // copy name
  for (i = 0; i < ifc_req_counts; ++i) {
    struct ifreq ifr;
    size_t name_size = strlen(ifc.ifc_req[i].ifr_name) + 1;
    get_infos[i].name = x_malloc(name_size);
    x_memcpy((pt_t)get_infos[i].name, (pt_t)ifc.ifc_req[i].ifr_name, name_size);

    strcpy(ifr.ifr_name, get_infos[i].name);

    // get flags
    if (ioctl(net_device, SIOCGIFFLAGS, &ifr) <0) {
      // TODO: get error from errno
      ret = X_NET_GET_IFCONF_FAIL;
      goto error;
    }

    if (ifr.ifr_flags & IFF_UP) {
      get_infos[i].is_up = X_TRUE;
    } else {
      get_infos[i].is_up = X_FALSE;
    }

    // mac address
    if (ioctl(net_device, SIOCGIFHWADDR, &ifr) <0) {
      // TODO: get error from errno
      ret = X_NET_GET_IFCONF_FAIL;
      goto error;
    }

    get_infos[i].mac_addr = x_calloc(18,1);
    snprintf(get_infos[i].mac_addr, 18, "%02X:%02X:%02X:%02X:%02X:%02X",
             (unsigned char)ifr.ifr_hwaddr.sa_data[0],
             (unsigned char)ifr.ifr_hwaddr.sa_data[1],
             (unsigned char)ifr.ifr_hwaddr.sa_data[2],
             (unsigned char)ifr.ifr_hwaddr.sa_data[3],
             (unsigned char)ifr.ifr_hwaddr.sa_data[4],
             (unsigned char)ifr.ifr_hwaddr.sa_data[5]);
  }

error:
  if (X_NET_OK == ret) {
    *out_infos = get_infos;
    *out_infos_count = ifc_req_counts;
  } else {
    if (get_infos) {
      x_net_desroty_interface_info(get_infos, ifc_req_counts);
      get_infos = NULL;
    }
  }

  if (ifreq_buff) {
    x_free(ifreq_buff);
  }

  return ret;
}
