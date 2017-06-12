/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zlibft6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:38:51 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/07 01:12:16 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*pf_append_str(char *orig, const char *to_append)
{
	char		*new_str;

	new_str = pf_strnew(pf_strlen(orig) + pf_strlen(to_append));
	pf_strcpy(new_str, orig);
	pf_strcat(new_str, to_append);
	return (new_str);
}

char		*pf_prepend_str(char *orig, const char *to_prepend)
{
	char		*new_str;

	new_str = pf_strnew(pf_strlen(orig) + pf_strlen(to_prepend));
	pf_strcpy(new_str, to_prepend);
	pf_strcat(new_str, orig);
	return (new_str);
}

const char	*new_padstr(char pad, int len)
{
	int			i;
	char		*str;

	i = 0;
	str = pf_strnew(len);
	while (i < len)
		str[i++] = pad;
	return ((const char*)str);
}

char		*pf_strcat(char *s1, const char *s2)
{
	char		*ret;

	ret = s1;
	while (*s1)
		s1++;
	while ((*s1++ = (char)*s2++))
		;
	return (ret);
}

char		*pf_itoa_base(intmax_t value, int base)
{
	short		neg;
	int			len;
	char		*str;
	const char	*radix;

	radix = "0123456789abcdef";
	neg = (value < 0) ? 1 : 0;
	len = pf_nbrlen(value, base);
	MEM_GUARD((str = pf_strnew(len)));
	while (len--)
	{
		str[len] = radix[value % 16];
		value /= 16;
	}
	if (neg)
		str[0] = '-';
	return (str);
}
