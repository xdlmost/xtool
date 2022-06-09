#include "xdefs/xdefs.h"
#include "xbase/xarray.h"
#include "xbase/mem/xmalloc.h"

struct xarray
{
    uint32 capacity;
    uint32 value_size;
    uint32 size;
    str* data;
};

xret 
create_array(uint32 capacity, uint32 value_size, xarray **newarray)
{
    xarray* array = (xarray *)xmalloc(sizeof(xarray));
    if (NULL == array) {
        return XRET_CAN_NOT_MALLCO;
    }
    array->capacity = capacity;
    array->size = 0;
    array->value_size = value_size;
    str* data = NULL;
    data = (str*)xmalloc(capacity * value_size * sizeof(char));
    if (NULL == data) {
        if (NULL != array) {
            xfree(array);
        }
        return XRET_CAN_NOT_MALLCO;
    }
    array->data = data;
    (*newarray) = array;
    return XRET_OK;
}

cstr 
get_type(xarray *self) {
    return "array";
}
