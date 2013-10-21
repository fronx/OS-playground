#include <stdio.h>
#include "osp_structs.h"

void
print_foo(Foo *f)
{
    printf("%s\n", __FUNCTION__);
    printf("f->a: %i\n", f->a);
    printf("f->b: %i\n", f->b);
}
