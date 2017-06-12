/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:06:32 by bslakey           #+#    #+#             */
/*   Updated: 2016/11/30 14:13:22 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*pf_strcpy(char *dest, const char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	*pf_strncpy(char *dest, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while ((i < len) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}

char	*pf_strdup(const char *s1)
{
	char *copy;

	copy = (char*)malloc(sizeof(char) * (pf_strlen(s1) + 1));
	MEM_GUARD(copy);
	pf_strcpy(copy, s1);
	return (copy);
}

char	*pf_strndup(const char *s1, size_t size)
{
	char *copy;

	copy = pf_strnew(size);
	MEM_GUARD(copy);
	pf_strncpy(copy, s1, size);
	return (copy);
}

int		pf_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while ((s1[i] && s2[i]) && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
