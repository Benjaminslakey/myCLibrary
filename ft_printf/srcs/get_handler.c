/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 20:09:05 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/07 00:25:00 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_handlers		get_handler(t_format *f)
{
	t_handlers		handler;

	if (SPEC('d') || SPEC('D') || SPEC('i'))
		handler = &handle_int;
	else if (SPEC('b') || SPEC('o') || SPEC('O') || SPEC('u') ||
			SPEC('U') || SPEC('x') || SPEC('X'))
		handler = &handle_unsigned;
	else if (SPEC('s') && !LMOD(3))
		handler = &handle_string;
	else if (SPEC('S') || (SPEC('s') && LMOD(3)))
		handler = &handle_widestring;
	else if (SPEC('c') && !LMOD(3))
		handler = &handle_chr;
	else if (SPEC('C') || (SPEC('c') && LMOD(3)))
		handler = &handle_widechr;
	else if (SPEC('%'))
		handler = &handle_percent;
	else if (SPEC('p'))
		handler = &handle_pointer;
	else if (!pf_valid_char(f->c_spec, "aAbBcCdDeEfFgGinoOpsSuUxX"))
		handler = &handle_percent;
	else
		handler = NULL;
	return (handler);
}
