
#include "../../includes/libft.h"

void 					array_reverse_int(int *arr, int size)
{
	int 				i;
	int 				j;
	int 				temp;

	i = -1;
	j = size;
	while (++i < --j)
	{
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
}
