/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 01:08:25 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/07 01:08:27 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		format_flags(t_format *f, char **str)
{
	if (f->zero && !(f->left_align))
	{
		*str = pf_prepend_str(*str, "0");
		f->pad = '0';
	}
}

static void		format_m_fwidth(t_format *f, char **str)
{
	int				len;
	const char		*pad_str;

	if ((len = (int)pf_strlen(*str)) < (f->m_fwidth))
	{
		pad_str = new_padstr((f->pad), (f->m_fwidth - len));
		if (f->left_align)
			*str = pf_append_str(*str, pad_str);
		else
			*str = pf_prepend_str(*str, pad_str);
	}
}

static void		format_prec(t_format *f, char **str)
{
	size_t		len;

	len = 0;
	if (f->prec_exists)
	{
		if ((f->prec) < (int)(len = pf_strlen(*str)) && !(f->prec < 0))
			*str = pf_strndup(*str, (f->prec));
	}
}

void			handle_string(t_format *format, t_outputs *output)
{
	(output->out) = (((output->var)->str) != NULL) ?
		(output->var)->str : "(null)";
	format_prec(format, &(output->out));
	format_flags(format, &(output->out));
	format_m_fwidth(format, &(output->out));
}
