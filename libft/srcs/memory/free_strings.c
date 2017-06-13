/*
 * =====================================================================================
 *
 *       Filename:  free_strings.c
 *
 *    Description:  
 *    
 *
 *        Version:  1.0
 *        Created:  06/12/2017 07:39:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "../../includes/libft.h"

void            free_strings(char ***strings)
{
    int         i;

    i = -1;
    while ((*strings)[++i])
        free((*strings)[i]);
    free(*strings);
    *strings = NULL;
}
