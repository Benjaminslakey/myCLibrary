/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 06:55:02 by bslakey           #+#    #+#             */
/*   Updated: 2016/12/09 21:05:56 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <wchar.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>

# define SPEC(x) (f->c_spec == x)
# define LMOD(x) (f->l_mod == x)
# define WHT(x) (x == ' ' || x == '\t' || x == '\r' || x == '\v' || XWHT(x))
# define XWHT(x) (x == '\f' || x == '\n' )
# define ANUM(x) (x >= '0' && x <= '9')
# define UCASE(x) (x >= 'A' && x <= 'Z')
# define LCASE(x) (x  >= 'a' && x <= 'z')
# define ALPHA(x) (UCASE(x) || LCASE(x))
# define ISIGN(x) (x == '-' || x == '+')
# define ERR_GUARD(x, y) if (x) return (y)
# define MEM_GUARD(x) if (x == NULL) return (NULL)
# define MEM_GUARD_VR(x) if (x == NULL) return

typedef union				u_variable
{
	char					c;
	short					s;
	int						i;
	long int				l;
	long long int			ll;
	size_t					sst;
	intmax_t				imax;
	unsigned char			uc;
	unsigned short			us;
	unsigned int			ui;
	unsigned long int		ul;
	unsigned long long int	ull;
	size_t					ust;
	uintmax_t				uimax;
	double					dub;
	long double				ldub;
	wchar_t					wchr;
	wchar_t					*wstr;
	char					*str;
	void					*p;
	intmax_t				*n;
	size_t					*n_st;
}							t_variable;

typedef struct				s_p_info
{
	int						*arg_indices;
	int						m_fwidth;
	char					prec_exists;
	int						prec;
	char					l_mod;
	char					seperator;
	char					alt;
	char					space;
	char					left_align;
	char					showsign;
	char					group;
	char					zero;
	char					pad;
	char					c_spec;
	int						base;
	char					*conversion_specifier;
	char					inval_spec;
	struct s_p_info			*next;
}							t_format;

typedef struct				s_outputs
{
	char					err;
	int						len;
	int						spec_len;
	short					null;
	t_variable				*var;
	char					*out;
	struct s_outputs		*next;
}							t_outputs;

typedef t_variable			*(*t_getter)(char, int, va_list);
typedef void				(*t_handlers)(t_format*, t_outputs*);

int							ft_printf(const char *format, ...);
t_outputs					*create_printlst(t_format *head, va_list args);
t_format					*create_formatlst(const char *fstr);
void						clear_lists(t_format **f_head, t_outputs **p_head);
void						print_format_node(t_format *curr);
t_variable					*get_var(t_format *node, va_list argz);
t_handlers					get_handler(t_format *node);
void						parse_format(char *c_str, t_format *format, int *i);
char						**fstr_tok(const char *fstr, const char start);
void						set_flags(char *flag_str, t_format *node);
char						*get_flags(char **fstr_chunk);
int							get_precision(char **fstr_chunk);
int							get_m_fwidth(char **fstr_chunk);
int							get_length(char **fstr_chunk);
t_variable					*get_uint(char c, int l, va_list cpy);
t_variable					*get_int(char c, int l, va_list cpy);
t_variable					*get_float(char c, int l, va_list cpy);
t_variable					*get_wide(char c, int l, va_list cpy);
t_variable					*get_others(char c, int l, va_list cpy);

void						handle_int(t_format *format, t_outputs *output);
void						handle_unsigned(t_format *format,
												t_outputs *output);
void						handle_chr(t_format *format, t_outputs *output);
void						handle_string(t_format *format, t_outputs *output);
void						handle_widechr(t_format *format, t_outputs *output);
void						handle_widestring(t_format *format,
												t_outputs *output);
void						handle_r(t_format *format, t_outputs *output);
void						handle_k(t_format *format, t_outputs *output);
void						handle_pointer(t_format *format, t_outputs *output);
void						handle_percent(t_format *format, t_outputs *output);
void						handle_floats(t_format *format, t_outputs *output);
size_t						handle_n(t_format *format, t_outputs *output);

const char					*new_padstr(char pad, int len);
char						*pf_append_str(char *orig, const char *to_append);
char						*pf_prepend_str(char *orig, const char *to_prepend);
int							pf_valid_char(char c, const char *allowed);
int							pf_nbrlen(intmax_t nbr, int base);
size_t						find_c(char *s, int index, int delim);
size_t						dstr_strlen(char *s, int index, const char *delims);
size_t						pf_strlen(const char *s);
int							pf_wchr_len(wchar_t wchr);
int							pf_w_strlen(wchar_t *wstr);
char						*pf_wctombs(wchar_t wchr);
char						*pf_wcstombs(wchar_t *wstr);
void						pf_putwchar(wchar_t wchr);
void						pf_putwstr(wchar_t *wstr);
void						pf_putchar(char c);
void						pf_putstr(char const *s);
void						pf_putnbr(intmax_t n);
char						*pf_strnew(size_t size);
void						pf_strclr(char *s);
void						pf_strdel(char **as);
void						*pf_memset(void *b, int c, size_t len);
void						pf_bzero(void *s, size_t n);
char						*pf_strcat(char *s1, const char *s2);
char						*pf_strcpy(char *dst, const char *src);
char						*pf_strncpy(char *dst, const char *src, size_t len);
char						*pf_strdup(const char *s1);
char						*pf_strndup(const char *s1, size_t size);
int							pf_strcmp(const char *s1, const char *s2);
int							pf_strncmp(const char *s1, const char *s2,
										size_t n);
void						pf_str_tolower(char *str);
void						pf_str_toupper(char *str);
char						*pf_itoa_base(intmax_t value, int base);
intmax_t					pf_atoi(const char *str);

#endif
