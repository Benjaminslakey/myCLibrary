/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fstr_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 07:48:38 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/07 01:05:29 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int				get_var_index(char **v_specifier, int i)
{
	int				j;
	int				index;
	char			*s;
	short			aster;
	char			*index_str;

	aster = 0;
	index = 0;
	j = -1;
	s = *v_specifier;
	while (s[++j])
	{
		aster += (s[j] == '*') ? 1 : 0;
		if (s[j] == '$' && aster)
			break ;
		else if (s[j] == '$' && !aster)
		{
			index_str = pf_strndup(s, (j - 1));
			index = pf_atoi(index_str);
			free(index_str);
			(*v_specifier) += j;
			break ;
		}
	}
	return ((index == 0) ? i : index);
}

static int				prec_exists(char **str)
{
	int prec_bool;

	prec_bool = 0;
	if (**str == '.')
	{
		prec_bool = 1;
		(*str)++;
	}
	return (prec_bool);
}

static void				v_width_prec(t_format *f)
{
	if ((f->m_fwidth) < 0)
	{
		if (f->m_fwidth == -1)
			(f->arg_indices)[1] = (f->arg_indices)[0];
		else
			(f->arg_indices)[1] = (f->m_fwidth) * -1;
	}
	if ((f->prec) < 0)
	{
		if (f->prec == -1)
		{
			(f->arg_indices)[2] = (f->arg_indices)[0];
			if (f->m_fwidth == -1)
				(f->arg_indices)[2] += 1;
		}
		else
			(f->arg_indices)[2] = (f->prec) * -1;
	}
	(f->arg_indices)[0] += (f->m_fwidth == -1) ? 1 : 0;
	(f->arg_indices)[0] += (f->prec == -1) ? 1 : 0;
}

static void				get_base(t_format *f)
{
	if (SPEC('b'))
		f->base = 2;
	else if (SPEC('o') || SPEC('O'))
		f->base = 8;
	else if (SPEC('x') || SPEC('X'))
		f->base = 16;
	else
		f->base = 10;
}

void					parse_format(char *c_str, t_format *f, int *i)
{
	int			j;

	j = -1;
	f->conversion_specifier = c_str;
	set_flags(get_flags(&c_str), f);
	(f->arg_indices)[0] = get_var_index(&c_str, *i);
	f->m_fwidth = get_m_fwidth(&c_str);
	f->prec_exists = prec_exists(&c_str);
	if (f->prec_exists)
		f->prec = get_precision(&c_str);
	f->l_mod = get_length(&c_str);
	f->c_spec = *c_str;
	if (f->prec_exists == 1 || f->left_align == 1)
		f->pad = ' ';
	v_width_prec(f);
	get_base(f);
	if (pf_valid_char(f->c_spec, "aAbcCdDeEfFgGinoOpsSuUxX"))
		(*i)++;
	f->next = NULL;
}
