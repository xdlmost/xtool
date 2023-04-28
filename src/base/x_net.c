#include "base/x_memory.h"
#include "base/x_net.h"
#include <net/if.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/ipv6.h>
#include <dirent.h>

#include "base/log.h"

#include <string.h>
#include <stdio.h>

#define IPV6_ADDR_LOOPBACK	        0x0010
#define IPV6_ADDR_LINKLOCAL	        0x0020
#define IPV6_ADDR_SITELOCAL	        0x0040
#define IPV6_ADDR_COMPATv4	        0x0080
#define IPV6_ADDR_GLOBAL	          0x00f0

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
  {
    DIR *d;
    struct dirent *de;
    int index = 0;
    d = opendir("/sys/class/net/");
    if (d == NULL) {
      ret = X_NET_GET_IFCONF_FAIL;
      goto error;
    }

    while (NULL != (de = readdir(d))) {
    	if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
    		continue;
    	}
      ifc_req_counts++;
    }
    closedir(d);
    get_infos = x_calloc(sizeof(x_net_interface_info_t), ifc_req_counts);

    d = opendir("/sys/class/net/");
    if (d == NULL) {
      ret = X_NET_GET_IFCONF_FAIL;
      goto error;
    }

    while (NULL != (de = readdir(d))) {
    	if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
    		continue;
    	}
      strcpy(get_infos[index++].name, de->d_name);
    }
    closedir(d);
  }

  
  for (i = 0; i < ifc_req_counts; ++i) {
    struct ifreq ifr;
    size_t name_size = 16;
    short flags = 0;

    strcpy(ifr.ifr_name, get_infos[i].name);

    // get flags
    {
      if (ioctl(net_device, SIOCGIFFLAGS, &ifr) == 0) {
        flags = ifr.ifr_flags;
      }
    }

    // get index
    {
      if (ioctl(net_device, SIOCGIFINDEX, &ifr) == 0) {
        get_infos[i].index = ifr.ifr_ifindex;
      }
      get_infos[i].index = ifr.ifr_ifindex;
    }

    // get up
    {
      if (ifr.ifr_flags & IFF_UP == IFF_UP) {
        get_infos[i].is_up = X_TRUE;
      } else {
        get_infos[i].is_up = X_FALSE;
      }
    }

    // mac address
    {
      if (ioctl(net_device, SIOCGIFHWADDR, &ifr) == 0) {
        snprintf(get_infos[i].mac, 18, "%02X:%02X:%02X:%02X:%02X:%02X",
                 (unsigned char)ifr.ifr_hwaddr.sa_data[0],
                 (unsigned char)ifr.ifr_hwaddr.sa_data[1],
                 (unsigned char)ifr.ifr_hwaddr.sa_data[2],
                 (unsigned char)ifr.ifr_hwaddr.sa_data[3],
                 (unsigned char)ifr.ifr_hwaddr.sa_data[4],
                 (unsigned char)ifr.ifr_hwaddr.sa_data[5]);
      }


    }

    // ipv4 address
    {
      str_t ipaddr_string = NULL;
      if (ioctl(net_device, SIOCGIFADDR, &ifr)  == 0) {
        ipaddr_string = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
        strcpy(get_infos[i].ip, ipaddr_string);
      }

    }

    // broadcast address
    {
      str_t ipaddr_string = NULL;
      if (ioctl(net_device, SIOCGIFBRDADDR, &ifr)  == 0) {
        ipaddr_string = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_broadaddr)->sin_addr);
        strcpy(get_infos[i].broadcast, ipaddr_string);
      }

    }

    // mask address
    {
      str_t ipaddr_string = NULL;
      if (ioctl(net_device, SIOCGIFNETMASK, &ifr)  == 0) {
        ipaddr_string = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_netmask)->sin_addr);
        strcpy(get_infos[i].mask, ipaddr_string);
      }

    }

    // mtu
    {
      if (ioctl(net_device, SIOCGIFMTU, &ifr)  == 0) {
        get_infos[i].mtu = ifr.ifr_mtu;
      }
    }

    // ipv6
    {
      FILE *f;
      int index, scope, prefix, flagsv6;
      char dname[IFNAMSIZ];
      unsigned char ipv6[16];

      f = fopen("/proc/net/if_inet6", "r");
      if (f == NULL) {
          return;
      }

      while (19 == fscanf(f,
                          " %2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx %*x %x %x %*x %s",
                          &ipv6[0],
                          &ipv6[1],
                          &ipv6[2],
                          &ipv6[3],
                          &ipv6[4],
                          &ipv6[5],
                          &ipv6[6],
                          &ipv6[7],
                          &ipv6[8],
                          &ipv6[9],
                          &ipv6[10],
                          &ipv6[11],
                          &ipv6[12],
                          &ipv6[13],
                          &ipv6[14],
                          &ipv6[15],
                          &prefix,
                          &scope,
                          dname)) {
        if (strcmp(get_infos[i].name, dname) != 0) {
          continue;
        }

        get_infos[i].ipv6_prefix =prefix;
        if (inet_ntop(AF_INET6, ipv6, get_infos[i].ipv6, 46) == NULL) {
          continue;
        }

        switch (scope) {
        case IPV6_ADDR_GLOBAL:
          strcpy(get_infos[i].ipv6_scope, "Global");
          break;
        case IPV6_ADDR_LINKLOCAL:
          strcpy(get_infos[i].ipv6_scope, "Link");
          break;
        case IPV6_ADDR_SITELOCAL:
          strcpy(get_infos[i].ipv6_scope, "Site");
          break;
        case IPV6_ADDR_COMPATv4:
          strcpy(get_infos[i].ipv6_scope, "Compat");
          break;
        case IPV6_ADDR_LOOPBACK:
          strcpy(get_infos[i].ipv6_scope, "Host");
          break;
        default:
          strcpy(get_infos[i].ipv6_scope, "Unknown");
        }
      }
      fclose(f);
    }
  }

error:
  if (X_NET_OK == ret) {
    *out_infos = get_infos;
    *out_infos_count = ifc_req_counts;
  } else {
    if (get_infos) {
      x_free((pt_t)get_infos);
      get_infos = NULL;
    }
  }

  if (net_device) {
    close(net_device);
    net_device = 0;
  }
  return ret;
}
