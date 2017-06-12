/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wS.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 14:57:28 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/07 00:59:01 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		format_prec(t_format *f, char **str, wchar_t *wstr)
{
	int				i;
	int				n;
	int				len;
	char			*bytes;

	i = 0;
	len = 0;
	MEM_GUARD_VR(str);
	n = pf_w_strlen(wstr);
	bytes = pf_strnew(n);
	while (*wstr)
		bytes[i++] = pf_wchr_len(*wstr++);
	if (f->prec_exists)
	{
		n = 0;
		while (n < f->prec)
		{
			if ((n + *bytes) <= f->prec)
				n += *bytes++;
			else
				break ;
		}
		if (f->prec < (len = (int)pf_strlen(*str)))
			*str = pf_strndup(*str, n);
	}
}

static void		format_fwidth(t_format *f, char **str)
{
	int				len;
	const char		*pad_str;

	pad_str = NULL;
	if (f->m_fwidth > (int)(len = pf_strlen(*str)))
	{
		pad_str = new_padstr(f->pad, (f->m_fwidth - len));
		if (f->left_align)
			*str = pf_append_str(*str, pad_str);
		else
			*str = pf_prepend_str(*str, pad_str);
	}
}

static void		format_flags(t_format *f, char **str)
{
	MEM_GUARD_VR(*str);
	if (f->zero)
		f->pad = '0';
}

void			handle_widestring(t_format *f, t_outputs *output)
{
	if ((f->l_mod > 0 && !LMOD(3) && !SPEC('S'))
			|| ((output->var)->wstr == NULL))
	{
		(output->out) = pf_strdup("(null)");
		return ;
	}
	output->out = pf_wcstombs(((output->var)->wstr));
	format_prec(f, &(output->out), (output->var)->wstr);
	format_flags(f, &(output->out));
	format_fwidth(f, &(output->out));
	output->len = pf_strlen(output->out);
}
