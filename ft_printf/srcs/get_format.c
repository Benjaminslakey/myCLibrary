/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formats.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 08:00:46 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/09 21:06:55 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_flags(char **v_specifier)
{
	int		i;
	char	*flag_str;
	char	c;
	char	*temp;

	i = -1;
	temp = pf_strnew(pf_strlen(*v_specifier));
	while (((c = (**v_specifier)) != 0) && (c == '#' || c == '0' || c == '-'
				|| c == ' ' || c == '+' || c == 39))
	{
		temp[++i] = c;
		(*v_specifier)++;
	}
	flag_str = pf_strndup(temp, (i + 1));
	free(temp);
	return (flag_str);
}

void		set_flags(char *flag_str, t_format *f)
{
	int		i;

	i = find_c(flag_str, 0, '#');
	f->alt = (flag_str[i] == '#') ? 1 : 0;
	i = find_c(flag_str, 0, '-');
	f->left_align = (flag_str[i] == '-') ? 1 : 0;
	i = find_c(flag_str, 0, '0');
	f->zero = (flag_str[i] == '0' && f->left_align == 0) ? 1 : 0;
	i = find_c(flag_str, 0, '+');
	f->showsign = (flag_str[i] == '+') ? 1 : 0;
	i = find_c(flag_str, 0, ' ');
	f->space = (flag_str[i] == ' ' && f->showsign == 0) ? 1 : 0;
	i = find_c(flag_str, 0, 39);
	f->group = (flag_str[i] == 39) ? 1 : 0;
	f->pad = (f->zero == 1 && f->left_align == 0) ? '0' : ' ';
	f->seperator = (f->group) ? ',' : 0;
}

int			get_m_fwidth(char **v_specifier)
{
	size_t	i;
	int		l;
	char	*s;

	l = 0;
	i = 0;
	s = *v_specifier;
	while ((s[l] != 0) && (s[l] == '*' || s[l] == '$' || ANUM(s[l])))
		l++;
	ERR_GUARD((l == 0), 0);
	(*v_specifier) += l;
	if (s[find_c(s, 0, '*')])
	{
		if ((find_c(s, 0, '*') < (i = find_c(s, 0, '.'))) || !s[i])
		{
			ERR_GUARD((!(s[(i = find_c(s, 0, '$'))]) || (s[i]
			&& (i > find_c(s, 0, '.') || i < find_c(s, 0, '*')))), -1);
			return (pf_atoi(pf_strndup(s + find_c(s, 0, '*'),
					find_c(s + find_c(s, 0, '*'), 0, '$'))) * -1);
		}
	}
	return ((l > 0) ? pf_atoi(pf_strndup(s, l)) : 0);
}

int			get_precision(char **v_specifier)
{
	int		l;
	int		precision;
	char	*s;

	l = 0;
	precision = 0;
	s = *v_specifier;
	while ((s[l] != 0) && (s[l] == '*' || s[l] == '$' || ANUM(s[l])))
		l++;
	(*v_specifier) += l;
	if (s[0] == '*')
		l -= ((++s)[l] == '$') ? 2 : 1;
	if (*(s - 1) == '*' && s[l + 1] != '$')
		return (-1);
	precision = pf_atoi(pf_strndup(s, l));
	if (*(s - 1) == '*' && s[l + 1] == '$')
		precision *= -1;
	return (precision);
}

int			get_length(char **v_specifier)
{
	char	c;
	char	*str;
	int		l_mod;

	str = *v_specifier;
	l_mod = 0;
	if (((c = *str) != 0) && (c == 'h' || c == 'l' || c == 'L'
				|| c == 't' || c == 'j' || c == 'z'))
	{
		if (c == 'h')
			l_mod = (*(str + 1) == 'h') ? 1 : 2;
		else if (c == 'l')
			l_mod = (*(str + 1) == 'l') ? 4 : 3;
		else if (c == 'L')
			l_mod = 4;
		else if (c == 'j')
			l_mod = 5;
		else if (c == 'z')
			l_mod = 6;
	}
	if (l_mod == 0)
		return (0);
	(*v_specifier) += ((l_mod == 1 || l_mod == 4)) ? 2 : 1;
	return (l_mod);
}
