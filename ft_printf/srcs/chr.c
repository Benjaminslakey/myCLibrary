/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 01:13:20 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/07 01:13:21 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			format_fwidth(t_format *f, char **str)
{
	const char		*pad_str;

	if (f->m_fwidth > 0)
	{
		pad_str = new_padstr((f->pad), ((f->m_fwidth) - 1));
		if (f->left_align == 1)
			*str = pf_append_str(*str, pad_str);
		else
			*str = pf_prepend_str(*str, pad_str);
	}
}

static void			format_flags(t_format *f, char **str)
{
	if (f->zero)
		f->pad = '0';
	if (*str)
		return ;
}

static char			*format_char(unsigned char ch)
{
	char		*str;

	str = pf_strnew(1);
	str[0] = ch;
	return (str);
}

void				handle_chr(t_format *f, t_outputs *output)
{
	(output->out) = format_char((output->var)->c);
	format_flags(f, &(output->out));
	format_fwidth(f, &(output->out));
	output->len = pf_strlen(output->out);
	if ((output->var)->c == 0)
	{
		(output->len)++;
		if (f->left_align)
		{
			(output->out) = pf_append_str((output->out), new_padstr(f->pad, 1));
			(output->out)[0] = 0;
		}
	}
}
