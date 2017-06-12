/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 09:22:24 by bslakey           #+#    #+#             */
/*   Updated: 2017/02/16 08:00:42 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		print_variable(t_outputs *node, const char **fstr)
{
	int		bytes_printed;

	bytes_printed = 0;
	*node = *(node->next);
	if (node)
	{
		if ((int)pf_strlen(node->out) >= node->len)
			pf_putstr(node->out);
		else
			write(1, (node->out), (node->len));
		bytes_printed = (node->len > (int)pf_strlen(node->out) ? node->len :
				(int)pf_strlen(node->out));
		*fstr += (node->spec_len + 1);
	}
	else
		return (-1);
	return (bytes_printed);
}

static size_t	proccess_printf(va_list argz, const char *fstr)
{
	size_t		bytes;
	t_outputs	*print_list;
	t_outputs	*p_curr;
	int			err;

	bytes = 0;
	print_list = create_printlst(create_formatlst(fstr), argz);
	p_curr = print_list;
	while (*fstr)
	{
		ERR_GUARD(((p_curr->next)->err), -1);
		if (*fstr == '%')
			bytes += (err = print_variable(p_curr, &fstr));
		else
		{
			write(1, fstr++, 1);
			bytes++;
		}
		ERR_GUARD((err == -1), bytes);
	}
	//clean_plist(print_list);
	free(print_list);
	return (bytes);
}

int				ft_printf(const char *format, ...)
{
	int			bytes_printed;
	va_list		args;

	ERR_GUARD((format == NULL), 0);
	va_start(args, format);
	bytes_printed = (int)proccess_printf(args, format);
	va_end(args);
	return (bytes_printed);
}
