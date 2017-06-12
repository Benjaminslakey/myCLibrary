/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boOuUxX.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 02:01:01 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/07 00:34:32 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			format_prec(t_format *f, char **str)
{
	size_t		len;
	size_t		diff;
	const char	*prec_str;

	prec_str = NULL;
	len = pf_strlen(*str);
	if (f->prec_exists)
	{
		if ((int)len < f->prec)
		{
			diff = ((f->prec) - (int)len);
			*str = pf_prepend_str(*str, new_padstr('0', diff));
		}
	}
}

static void			format_flags(t_format *f, char **str)
{
	if (f->alt && pf_atoi(*str))
	{
		if ((SPEC('x') || SPEC('X')))
			*str = pf_prepend_str(*str, "0x");
		else if ((SPEC('o') || SPEC('O')) && f->prec < (int)pf_strlen(*str))
		{
			*str = pf_prepend_str(*str, "0");
		}
		else if (SPEC('b'))
			*str = pf_prepend_str(*str, "0b");
	}
	if (f->alt && !pf_atoi(*str) && (f->prec_exists) && !(f->prec) &&
			(SPEC('o') || SPEC('O')))
		*str = pf_prepend_str(*str, "0");
	if (f->zero && !(f->left_align) && !(f->alt) && !(f->prec_exists))
		f->pad = '0';
	if (SPEC('X'))
		pf_str_toupper(*str);
}

static void			format_m_fwidth(t_format *f, char **str)
{
	int			i;
	int			len;
	const char	*pad_str;

	pad_str = NULL;
	i = 0;
	if ((f->m_fwidth) > (int)(len = pf_strlen(*str)))
	{
		if (f->prec_exists && f->pad == '0')
			return ;
		pad_str = new_padstr(f->pad, (f->m_fwidth - len));
		if (f->left_align)
			*str = pf_append_str(*str, pad_str);
		else
			*str = pf_prepend_str(*str, pad_str);
		if (!(f->left_align) && f->alt && f->zero)
		{
			(*str)[1] = (*str)[(dstr_strlen(*str, 0, "bxX") - 1)];
			(*str)[dstr_strlen(*str, 0, "bxX") - 1] = '0';
		}
	}
}

static char			*format_unsigned(uintmax_t num, unsigned int base)
{
	int				length;
	uintmax_t		temp;
	char			*str;
	char			*radix;

	length = 0;
	temp = num;
	radix = "0123456789abcdef";
	if (num == 0)
		return (pf_strdup("0"));
	while (temp)
	{
		temp /= base;
		length++;
	}
	str = pf_strnew((length));
	while (num)
	{
		str[--length] = radix[num % base];
		num /= base;
	}
	return (str);
}

void				handle_unsigned(t_format *f, t_outputs *output)
{
	if ((!SPEC('O') && !SPEC('U')) && (!LMOD(3)))
	{
		if (LMOD(0))
			(output->out) = format_unsigned((output->var)->ui, f->base);
		else if (LMOD(1))
			(output->out) = format_unsigned((output->var)->uc, f->base);
		else if (LMOD(2))
			(output->out) = format_unsigned((output->var)->us, f->base);
		else if (LMOD(4))
			(output->out) = format_unsigned((output->var)->ull, f->base);
		else if (LMOD(5))
			(output->out) = format_unsigned((output->var)->uimax, f->base);
		else if (LMOD(6))
			(output->out) = format_unsigned((output->var)->ust, f->base);
	}
	else if (SPEC('O') || SPEC('U') || (LMOD(3)))
		(output->out) = format_unsigned((output->var)->ul, f->base);
	if ((pf_atoi(output->out) == 0) && f->prec_exists
			&& !(f->prec))
		output->out = "";
	format_prec(f, &(output->out));
	format_flags(f, &(output->out));
	format_m_fwidth(f, &(output->out));
	output->len = (int)pf_strlen(output->out);
}
