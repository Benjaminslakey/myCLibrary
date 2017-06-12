/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 14:19:09 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/07 00:11:10 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		format_flags(t_format *f, char **str)
{
	if (f->zero)
	{
		f->pad = '0';
		*str = pf_prepend_str(*str, "0");
	}
}

static void		format_fwidth(t_format *f, char **str)
{
	int			len;
	const char	*pad_str;

	len = 0;
	pad_str = NULL;
	if (f->m_fwidth > (len = (int)pf_strlen(*str)))
	{
		pad_str = new_padstr(f->pad, (f->m_fwidth - len));
		if (f->left_align)
			*str = pf_append_str(*str, pad_str);
		else
			*str = pf_prepend_str(*str, pad_str);
	}
}

char			*format_percent(char c)
{
	char	*str;

	str = pf_strnew(1);
	str[0] = c;
	return (str);
}

void			handle_percent(t_format *f, t_outputs *output)
{
	output->out = format_percent((output->var)->c);
	format_flags(f, &(output->out));
	format_fwidth(f, &(output->out));
}
