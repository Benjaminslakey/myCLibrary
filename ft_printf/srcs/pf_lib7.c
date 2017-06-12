/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zlibft7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 01:46:13 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/06 23:05:18 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define CONT_	0x80
#define MASK2_	0xc0
#define MASK3_	0xe0
#define MASK4_	0xf0

int             pf_wchr_len(wchar_t wchr)
{
	int      bytes;

	bytes = 0;
	ERR_GUARD((wchr < 0 || (wchr >= 0xD800 && wchr <= 0xDFFF)), -1);
	else if (wchr <= 0x7F)
		bytes = 1;
	else if (wchr <= 0x7ff)
		bytes = 2;
	else if (wchr <= 0xffff)
		bytes = 3;
	else if (wchr <= 0x1fffff)
		bytes = 4;
	return (bytes);
}

int				pf_w_strlen(wchar_t *wstr)
{
	int			len;

	len = 0;
	while (*wstr)
	{
		len += pf_wchr_len(*wstr);
		wstr++;
	}
	return (len);
}

char			*pf_wctombs(wchar_t wchr)
{
	int				i;
	int				len;
	char			mask[4];
	char			*str;

	mask[0] = CONT_;
	mask[1] = MASK2_;
	mask[2] = MASK3_;
	mask[3] = MASK4_;
	MEM_GUARD((str = pf_strnew((len = pf_wchr_len(wchr)))));
	str[(i = 0)] = (unsigned int)wchr;
	ERR_GUARD((len == 1), str);
	ERR_GUARD((len == -1), pf_strdup("�)"));
	while (len--)
		*str++ = ((!i++) ? mask[len] : mask[0]) | ((wchr >> (len * 6)) & 0x3f);
	return (str - i);
}

char			*pf_wcstombs(wchar_t *wstr)
{
	char			*str;
	char			*temp;

	MEM_GUARD((str = pf_strnew(pf_w_strlen(wstr))));
	while(*wstr)
	{
		if ((temp = pf_wctombs(*wstr++)) != NULL)
		{
			pf_strcat(str, (const char*)temp);
			pf_strdel(&temp);
		}
	}
	return (str);
}
