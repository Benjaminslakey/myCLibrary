/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_lib5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 17:08:27 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/10 17:08:35 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			pf_putnbr(intmax_t n)
{
	if (n < 0)
	{
		n *= -1;
		pf_putchar('-');
	}
	if (n / 10)
		pf_putnbr(n / 10);
	pf_putchar((n % 10) + '0');
}

void			pf_putstr(char const *s)
{
	int			i;

	i = -1;
	MEM_GUARD_VR(s);
	while (s[++i])
		write(1, s + i, 1);
}

void			pf_putchar(char c)
{
	write(1, &c, 1);
}

void			pf_putwchar(wchar_t wchr)
{
	int			len;
	char		*utf8;

	len = pf_wchr_len(wchr);
	utf8 = pf_wctombs(wchr);
	write(1, utf8, len);
	free(utf8);
}

void			pf_putwstr(wchar_t *wstr)
{
	int			i;
	int			len;

	i = 0;
	MEM_GUARD_VR(wstr);
	len = pf_w_strlen(wstr);
	while (i < len)
	{
		pf_putwchar(*wstr);
		i += pf_wchr_len(*wstr);
		wstr++;
	}
}
