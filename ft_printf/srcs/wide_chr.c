/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wCS.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 23:41:58 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/07 00:25:55 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*format_wchar(wchar_t wchr)
{
	char		*str;

	MEM_GUARD((str = pf_wctombs(wchr)));
	return (str);
}

void			handle_widechr(t_format *format, t_outputs *output)
{
	output->out = format_wchar((output->var)->wchr);
	output->len = pf_wchr_len((output->var)->wchr);
	if (!pf_strcmp((const char*)(output->out), "�)"))
		output->err = 1;
	if (format->prec_exists == 1)
	{
		;
	}
}
