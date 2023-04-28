#include "base/base_api.h"
#include <stdio.h>

int 
main(int argc, char **argv) {
  i32_t ret = 0;
  x_net_interface_info_t *infos = NULL;
  u32_t infos_count = 0;
  u32_t infos_index = 0;

  ret = x_get_local_net_interface_infos(&infos, &infos_count);
  if ( 0 == ret) {
    printf("list all net interface:\n");
    for (infos_index = 0; infos_index < infos_count; ++infos_index) {
      printf("network device[%d]\n", infos[infos_index].index);
      printf("  name:        %s\n", infos[infos_index].name);
      printf("  stauts:      %s\n", ((infos[infos_index].is_up == X_TRUE)?"up":"down"));
      printf("  mac:         %s\n", infos[infos_index].mac);
      printf("  ip:          %s\n", infos[infos_index].ip);
      printf("  broadcast:   %s\n", infos[infos_index].broadcast);
      printf("  mask:        %s\n", infos[infos_index].mask);
      printf("  mtu:         %d\n", infos[infos_index].mtu);
      printf("  ipv6:        %s\n", infos[infos_index].ipv6);
      printf("  ipv6_prefix: %d\n", infos[infos_index].ipv6_prefix);
      printf("  ipv6_scope:  %s\n", infos[infos_index].ipv6_scope);
      printf("\n");
    }
      int ipv6_prefix;
  char ipv6_scope[8];
    x_free((pt_t)infos);
    infos = NULL;
  } else {
    printf("get local net interface infos fail with %d\n", ret);
  }

error:
  return ret;
}