/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_lib2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 01:13:07 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/07 01:13:09 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*pf_strnew(size_t size)
{
	char *new;

	new = (char*)malloc(sizeof(char) * ++size);
	MEM_GUARD(new);
	pf_bzero(new, size);
	return (new);
}

void	pf_strdel(char **as)
{
	MEM_GUARD_VR(as);
	free(*as);
	*as = NULL;
}

void	pf_strclr(char *s)
{
	size_t i;

	i = 0;
	MEM_GUARD_VR(s);
	while (s[i])
		s[i++] = 0;
}

void	*pf_memset(void *b, int c, size_t len)
{
	unsigned char *s;

	s = b;
	while (len--)
		*s++ = (unsigned char)c;
	return (b);
}

void	pf_bzero(void *s, size_t n)
{
	MEM_GUARD_VR(s);
	pf_memset(s, 0, n);
}
