/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fstr_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 01:04:15 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/07 01:04:17 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				pf_valid_char(char c, const char *allowed)
{
	int			i;

	i = -1;
	while (allowed[++i])
		ERR_GUARD((allowed[i] == c), 1);
	return (0);
}

static char		*new_tok(const char *s, int *i)
{
	char	*token;
	int		tok_size;
	int		len;
	int		temp;

	len = 0;
	tok_size = 0;
	temp = *i;
	while (pf_valid_char(s[temp++], "$* +-#0123456789.hlLjz"))
		tok_size++;
	token = pf_strnew(++tok_size);
	while (s[(*i) + len] && len < tok_size)
	{
		token[len] = s[(*i) + len];
		len++;
	}
	*i += len;
	return (token);
}

char			**fstr_tok(const char *fstr, const char start)
{
	char	**tokens;
	int		nth_token;
	int		i;
	int		len;

	len = 0;
	nth_token = 0;
	i = -1;
	while (fstr[++i])
		nth_token += (fstr[i] == start) ? 1 : 0;
	tokens = (char**)malloc(sizeof(char*) * (nth_token + 1));
	while (nth_token > -1)
		tokens[nth_token--] = 0;
	i = 0;
	while (fstr[i])
	{
		if (fstr[i++] == start)
		{
			tokens[++nth_token] = new_tok(fstr, &i);
		}
	}
	i = -1;
	return (tokens);
}
