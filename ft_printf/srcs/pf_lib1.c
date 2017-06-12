/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:00:04 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/09 21:06:24 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				pf_nbrlen(intmax_t nbr, int base)
{
	int		len;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0 && base == 10)
		len++;
	while (nbr)
	{
		nbr /= base;
		len++;
	}
	return (len);
}

size_t			dstr_strlen(char *s, int i, const char *delims)
{
	int		len;
	int		j;

	j = 0;
	len = 0;
	while (s[i + len])
	{
		j = 0;
		while (delims[j])
		{
			if (s[i + len] == delims[j])
				return (len + 1);
			j++;
		}
		len++;
	}
	return (len);
}

size_t			find_c(char *s, int index, int delim)
{
	size_t length;

	length = 0;
	while (s[index] && s[index] != delim)
	{
		index++;
		length++;
	}
	return (length);
}

size_t			pf_strlen(const char *s)
{
	size_t length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}
