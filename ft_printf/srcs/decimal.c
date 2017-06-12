/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dDi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 10:28:24 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/09 21:08:15 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				format_prec(t_format *f, char **str)
{
	const char	*pad_str;
	int			i;
	int			diff;

	i = 0;
	pad_str = NULL;
	diff = (f->prec) - (int)pf_strlen(*str);
	diff += ((*str)[i = find_c(*str, 0, '-')] == '-') ? 1 : 0;
	if (diff > 0)
	{
		pad_str = new_padstr('0', diff);
		*str = pf_prepend_str(*str, pad_str);
		if ((*str)[i = find_c(*str, 0, '-')] == '-')
		{
			(*str)[i] = '0';
			(*str)[0] = '-';
		}
	}
}

static void				format_flags(t_format *f, char **str)
{
	size_t		i;

	i = 0;
	if (f->zero && !(f->prec_exists) && (int)(pf_strlen(*str) + 1) <=
			f->m_fwidth && !(f->showsign))
		*str = pf_prepend_str(*str, "0");
	if ((*str)[i = find_c(*str, i, '-')] != '-' && f->showsign == 1)
		*str = pf_prepend_str(*str, "+");
	if (f->space && !(f->left_align) && !(f->showsign) && pf_atoi(*str) >= 0)
		*str = pf_prepend_str(*str, " ");
	if (f->prec_exists)
		f->pad = ' ';
}

static void				format_m_fwidth(t_format *f, char **str)
{
	size_t		i;
	const char	*pad_str;

	i = 0;
	pad_str = NULL;
	if ((f->m_fwidth) > (int)pf_strlen(*str))
	{
		pad_str = new_padstr(f->pad, f->m_fwidth - (int)pf_strlen(*str));
		if (f->left_align == 1)
			*str = pf_append_str(*str, pad_str);
		else
		{
			*str = pf_prepend_str(*str, pad_str);
			if (((*str)[i = find_c(*str, 0, '-')] && !(f->prec_exists)
					&& f->pad == '0') || (f->pad == '0' &&
						(*str)[i = find_c(*str, 0, '+')]))
			{
				(*str)[0] = (*str)[i];
				(*str)[i] = f->pad;
			}
		}
	}
}

static	char			*format_decimal(intmax_t n)
{
	char		*str;
	intmax_t	temp;
	int			length;
	int			i;
	short		min;

	i = 1;
	temp = n;
	min = (n == INTMAX_MIN) ? 1 : 0;
	n = (n == INTMAX_MIN) ? INTMAX_MAX : temp;
	length = pf_nbrlen(n, 10);
	str = (min) ? pf_strnew(++length) : pf_strnew(length);
	n *= (n < 0) ? (i *= -1) : 1;
	while (length)
	{
		str[--length] = ((n % 10) + '0');
		n /= 10;
	}
	if (i < 0 || min)
		str[0] = '-';
	if (min)
		str[(pf_nbrlen(temp, 10) - 1)] = '8';
	return (str);
}

void					handle_int(t_format *f, t_outputs *output)
{
	if ((SPEC('d') || SPEC('i')) && !LMOD(3))
	{
		if (LMOD(0))
			(output->out) = format_decimal((output->var)->i);
		else if (LMOD(1))
			(output->out) = format_decimal((output->var)->c);
		else if (LMOD(2))
			(output->out) = format_decimal((output->var)->s);
		else if (LMOD(4))
			(output->out) = format_decimal((output->var)->ll);
		else if (LMOD(5))
			(output->out) = format_decimal((output->var)->imax);
		else if (LMOD(6))
			(output->out) = format_decimal((output->var)->sst);
	}
	else if (SPEC('D') || LMOD(3))
		(output->out) = format_decimal((output->var)->l);
	if ((!pf_atoi(output->out)) && f->prec_exists && !(f->prec))
		output->out = "";
	format_prec(f, &(output->out));
	format_flags(f, &(output->out));
	format_m_fwidth(f, &(output->out));
}
