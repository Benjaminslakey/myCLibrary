/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:06:37 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/07 01:10:50 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					pf_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	i = 0;
	if (n)
	{
		while ((s1[i] && s2[i]) && (s1[i] == s2[i]) && (i < n))
			i++;
		if (i < n)
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else
			i--;
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	else
		return (0);
}

void				pf_str_tolower(char *str)
{
	char			c;
	int				i;

	i = 0;
	while ((c = str[i]) != 0)
	{
		*(str + i) += (UCASE(c)) ? (32) : (0);
		i++;
	}
}

void				pf_str_toupper(char *str)
{
	char			c;
	int				i;

	i = 0;
	while ((c = str[i]) != 0)
	{
		*(str + i) += (LCASE(c)) ? (-32) : (0);
		i++;
	}
}

intmax_t			pf_atoi(const char *str)
{
	int				i;
	intmax_t		result;
	int				neg;

	i = -1;
	result = 0;
	neg = 1;
	while (str[++i] && (WHT(str[i]) || (ANUM(str[i])) || (ISIGN(str[i]))))
	{
		if (ISIGN(str[i]) || (ANUM(str[i])))
		{
			if (ISIGN(str[i]))
			{
				if (str[i] == '-')
					neg *= -1;
				i++;
			}
			while (ANUM(str[i]))
				result = (result * 10) + (str[i++] - '0');
			return ((result * neg));
		}
	}
	return (0);
}
