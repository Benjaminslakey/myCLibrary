/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 01:13:41 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/10 17:08:59 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_variable		*get_uint(char c, int l, va_list cpy)
{
	t_variable	*var;

	var = (t_variable*)malloc(sizeof(t_variable));
	if (c == 'x' || c == 'X' || c == 'b' || c == 'o' || c == 'u')
	{
		if (l == 0)
			var->ui = (unsigned int)va_arg(cpy, unsigned int);
		else if (l == 1)
			var->uc = (unsigned char)va_arg(cpy, unsigned int);
		else if (l == 2)
			var->us = (unsigned short)va_arg(cpy, unsigned int);
		else if (l == 3)
			var->ul = (unsigned long int)va_arg(cpy, unsigned long int);
		else if (l == 4)
			var->ull = (unsigned long long int)va_arg(cpy,
					unsigned long long int);
		else if (l == 5)
			var->uimax = (uintmax_t)va_arg(cpy, uintmax_t);
		else if (l == 6)
			var->ust = (size_t)va_arg(cpy, size_t);
	}
	else if (c == 'U' || c == 'O')
		var->ull = (unsigned long long int)va_arg(cpy, unsigned long long int);
	return (var);
}

t_variable		*get_int(char c, int l, va_list cpy)
{
	t_variable	*var;

	var = (t_variable*)malloc(sizeof(t_variable));
	if ((c == 'd' || c == 'i'))
	{
		if (l == 0)
			var->i = (int)va_arg(cpy, int);
		else if (l == 1)
			var->c = (char)va_arg(cpy, int);
		else if (l == 2)
			var->s = (short)va_arg(cpy, int);
		else if (l == 3)
			var->l = (long int)va_arg(cpy, long int);
		else if (l == 4)
			var->ll = (long long int)va_arg(cpy, long long int);
		else if (l == 5)
			var->imax = (intmax_t)va_arg(cpy, intmax_t);
		else if (l == 6)
			var->sst = (size_t)va_arg(cpy, size_t);
	}
	else if (c == 'c' && l != 3)
		var->c = (char)va_arg(cpy, int);
	else if (c == 'D')
		var->l = (long int)va_arg(cpy, long int);
	return (var);
}

t_variable		*get_float(char c, int l, va_list cpy)
{
	t_variable	*var;

	var = (t_variable*)malloc(sizeof(t_variable));
	if (c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'f' || c == 'F'
			|| c == 'g' || c == 'G')
	{
		if (l == 7)
			var->ldub = (long double)va_arg(cpy, long double);
		else
			var->dub = (double)va_arg(cpy, double);
	}
	return (var);
}

t_variable		*get_wide(char c, int l, va_list cpy)
{
	t_variable	*var;

	var = (t_variable*)malloc(sizeof(t_variable));
	if (c == 'C' || ((c == 'c') && l == 3))
		var->wchr = (wchar_t)va_arg(cpy, wchar_t);
	else if (c == 'S' || (c == 's' && l == 3))
		var->wstr = (wchar_t*)va_arg(cpy, wchar_t*);
	return (var);
}

t_variable		*get_others(char c, int l, va_list cpy)
{
	t_variable	*var;

	var = (t_variable*)malloc(sizeof(t_variable));
	if (c == 's' && l != 3)
		var->str = (char*)va_arg(cpy, char*);
	else if (c == 'n')
	{
		if (l < 7)
			var->n = (intmax_t*)va_arg(cpy, intmax_t*);
		else
			var->n_st = (size_t*)va_arg(cpy, size_t*);
	}
	else if (c == 'p')
		var->p = (void*)va_arg(cpy, void*);
	return (var);
}
