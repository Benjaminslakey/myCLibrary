#include "../../includes/libft.h"

void                free_int_2Darr(int ***arrs, int height)
{
    int             i;

    i = -1;
    while (++i < height)
        free((*arrs)[i]);
    free((*arrs));
    arrs = NULL;
}
