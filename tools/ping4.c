#include "base/base_api.h"


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
      printf("%ld:%s\n", infos_index, infos[infos_index].name);
      printf("%ld:%s\n", infos_index, ((infos[infos_index].is_up == X_TRUE)?"up":"down"));
      printf("%ld:%s\n", infos_index, infos[infos_index].mac_addr);
      printf("\n");
    }
    x_net_desroty_interface_info(infos, infos_count);
    infos = NULL;
  } else {
    printf("get local net interface infos fail with %d\n", ret);
  }

error:
  return ret;
}