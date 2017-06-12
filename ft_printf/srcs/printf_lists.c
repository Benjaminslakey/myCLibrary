/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 01:01:43 by bslakey           #+#    #+#             */
/*   Updated: 2017/02/16 08:02:09 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_format				*init_formatlst(void)
{
	t_format	*list;
	int			i;

	i = -1;
	list = (t_format*)malloc(sizeof(t_format));
	(list->arg_indices) = (int*)malloc(sizeof(int) * 3);
	while (++i < 3)
		(list->arg_indices)[i] = 0;
	list->m_fwidth = 0;
	list->prec_exists = 0;
	list->prec = 0;
	list->l_mod = 0;
	list->seperator = 0;
	list->alt = 0;
	list->space = 0;
	list->left_align = 0;
	list->showsign = 0;
	list->group = 0;
	list->pad = 0;
	list->c_spec = 0;
	list->base = 0;
	list->inval_spec = 0;
	list->next = NULL;
	return (list);
}

static t_outputs			*init_printlist(void)
{
	t_outputs	*node;

	node = (t_outputs*)malloc(sizeof(t_outputs));
	node->err = 0;
	node->null = 0;
	node->len = 0;
	node->spec_len = 0;
	node->var = NULL;
	node->out = NULL;
	node->next = NULL;
	return (node);
}

t_format					*create_formatlst(const char *f_str)
{
	int			i;
	int			ind;
	char		**conversion_tokens;
	t_format	*format_head;
	t_format	*curr;

	i = 0;
	ind = 1;
	curr = init_formatlst();
	format_head = curr;
	conversion_tokens = fstr_tok(f_str, '%');
	while (conversion_tokens[i])
	{
		curr->next = init_formatlst();
		curr = curr->next;
		parse_format(conversion_tokens[i++], curr, &ind);
	}
	free(conversion_tokens);
	return (format_head);
}

t_outputs					*create_printlst(t_format *f_head, va_list args)
{
	t_format		*f;
	t_outputs		*o;
	t_outputs		*lst_head;
	t_handlers		handler;
	va_list			argz;

	lst_head = init_printlist();
	o = init_printlist();
	lst_head->next = o;
	f = f_head->next;
	while (f)
	{
		va_copy(argz, args);
		o->var = get_var(f, argz);
		o->out = (pf_valid_char(f->c_spec, "aAeEfFgG")) ? "re-route floats" : NULL;
		if ((handler = get_handler(f)) != NULL)
			handler(f, o);
		o->spec_len = (int)pf_strlen(f->conversion_specifier);
		o->next = init_printlist();
		o = o->next;
		f = f->next;
		va_end(argz);
	}
	//clean_flist(f_head);
	free(f_head);
	return (lst_head);
}
