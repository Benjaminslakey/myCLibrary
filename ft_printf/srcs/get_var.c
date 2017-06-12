/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 02:59:52 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/07 00:19:47 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define FLOAT(x) (x == 'a' || x == 'A' || x == 'e' || x == 'E' || XFLOAT(x))
#define XFLOAT(x) (x == 'f' || x == 'F' || x == 'g' || x == 'G')
#define INT(x) (x == 'd' || x == 'D' || x == 'i' || x == 'p' || XINT(x))
#define XINT(x) (x == 'c' || x == 'r')
#define UINT(x) (x == 'x' || x == 'X' || x == 'o' || x == 'O' || XUINT(x))
#define XUINT(x) (x == 'u' || x == 'U' || x == 'b')
#define WIDE(x, y) (x == 'C' || x == 'S' || XWIDE(x, y))
#define XWIDE(x, y) ((x == 'c' && y == 3) || (x == 's' && y == 3))
#define OTHERS(x, y) ((x == 's' && y != 3) || x == 'p' || c == 'n')

static void			set_var_fwidth(t_format *f, va_list argz)
{
	int			var_index;
	int			curr_index;
	int			*ptr;
	va_list		cpy;

	va_copy(cpy, argz);
	curr_index = 1;
	ptr = f->arg_indices;
	var_index = ptr[1];
	while (curr_index++ < var_index)
		va_arg(cpy, void*);
	f->m_fwidth = (int)va_arg(cpy, int);
	va_end(cpy);
}

static void			set_var_prec(t_format *f, va_list argz)
{
	int			var_index;
	int			curr_index;
	int			*ptr;
	va_list		cpy;

	va_copy(cpy, argz);
	curr_index = 1;
	ptr = f->arg_indices;
	var_index = ptr[2];
	while (curr_index++ < var_index)
		va_arg(cpy, void*);
	f->prec = (int)va_arg(cpy, int);
	va_end(cpy);
}

static t_getter		get_type(t_format *f)
{
	t_getter	getter;
	char		c;
	int			l;

	c = f->c_spec;
	l = f->l_mod;
	getter = NULL;
	if (pf_valid_char(c, "aAbcCdDeEfFgGinoOpsSuUxX"))
	{
		if (OTHERS(c, l))
			getter = &get_others;
		else if (WIDE(c, l))
			getter = &get_wide;
		else if (INT(c) && !(c == 'c' && l == 3))
			getter = &get_int;
		else if (UINT(c))
			getter = &get_uint;
		else if (FLOAT(c))
			getter = &get_float;
	}
	else
		f->inval_spec = 1;
	return (getter);
}

t_variable			*get_var(t_format *f, va_list argz)
{
	int				list_index;
	t_variable		*var;
	t_getter		get_variable;
	va_list			cpy;

	list_index = 1;
	va_copy(cpy, argz);
	if ((f->arg_indices)[1] != 0)
		set_var_fwidth(f, cpy);
	if ((f->arg_indices)[2] != 0)
		set_var_prec(f, cpy);
	if (f->m_fwidth < 0)
		(f->m_fwidth) *= (f->left_align = 1) * -1;
	while (list_index++ < (f->arg_indices)[0])
		va_arg(cpy, void*);
	get_variable = get_type(f);
	if (get_variable)
		var = get_variable((f->c_spec), (f->l_mod), cpy);
	else
	{
		var = (t_variable*)malloc(sizeof(t_variable));
		var->c = f->c_spec;
	}
	va_end(cpy);
	return (var);
}
