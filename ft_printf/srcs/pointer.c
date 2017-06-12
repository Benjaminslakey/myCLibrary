/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 01:05:56 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/07 01:05:58 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			format_prec(t_format *f, char **str)
{
	int len;

	len = 0;
	if (f->prec_exists)
	{
		if (f->prec == 0 && pf_atoi(*str) == 0)
			*str = pf_strdup("");
		else if (f->prec > (len = (int)pf_strlen(*str)))
			*str = pf_prepend_str(*str, new_padstr('0', (f->prec - len)));
	}
}

static void			format_fwidth(t_format *f, char **str)
{
	int		len;

	if (f->m_fwidth > (len = (int)pf_strlen(*str)))
	{
		if (f->left_align || f->zero)
			*str = pf_append_str(*str, new_padstr(f->pad, f->m_fwidth - len));
		else
			*str = pf_prepend_str(*str, new_padstr(f->pad, f->m_fwidth - len));
	}
}

static char			*format_pointer(void *p)
{
	intmax_t	cast;
	int			len;
	char		*str;

	cast = (intmax_t)p;
	len = pf_nbrlen(cast, 16);
	MEM_GUARD((str = pf_itoa_base(cast, 16)));
	return (str);
}

void				handle_pointer(t_format *f, t_outputs *output)
{
	(output->out) = format_pointer((output->var)->p);
	format_prec(f, &(output->out));
	(output->out) = pf_prepend_str((output->out), "0x");
	format_fwidth(f, &(output->out));
}
