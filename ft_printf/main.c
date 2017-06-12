
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 08:01:35 by bslakey           #+#    #+#             */
/*   Updated: 2016/11/21 11:01:33 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <wchar.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <stdint.h>
#include <limits.h>
#include <strings.h>
#include <locale.h>
#include "ft_printf.h"

/*
   int		main(void)
   {
   int		i = 96;
   int		j = 4;
   printf("%2$*3$.*1$i\n, %3$*2$.*1$d", j, i, 10);
   return (0);
   }

   int		main(void)
   {
   int i = 0;
   char *str = "my name\nis ben";
   while (str[i])
   write(1, &str[i++], 1);
   return (0);
   }
   */

int		main(void)
{
	int		lprint = 0;
	int		ftprint = 0;
	setlocale(LC_ALL, "");
	//int *ptr = (int*)malloc(sizeof(int) * 1);
	//*ptr = 312313;
	//long double dub = 3231999999999999.999999999999999;
	//ft_printf("ft_printf:\n");
	//ft_printf("% +15.5d and ben ", 34242321);
	//ft_printf("ft_printf:\nwhat is \nhappening %.5s, %+ld\n", "benjamin", n);
	//ft_printf("ft_printf:\n%.4d\n my name is %.3s\n", 255, "benjamin");
	//printf("printf:\n%.4d\n my name is %.3s\n", 255, "benjamin");

	//ftprint = ft_printf("%x%x%x%x%x", 1, 100, 999, 42, 999988888);
	//lprint = printf("%x%x%x%x%x", 1, 100, 999, 42, 999988888);
	//
	//ftprint = ft_printf("ft_printf: %#.o, %#.0o\n", 0, 0);
	//'lprint = printf("printf: %#.o, %#.0o\n", 0, 0);
	//printf("ftprintf bytes: %d, lprint bytes: %d\n\n", ftprint, lprint);
	//ft_printf("{% c}", 0);printf("{% c}", 0);	
	//ftprint = ft_printf("%#o", 0);
	//ftprint = ft_printf("%C", 0x1f613);
	//ftprint = ft_printf("%S", L"我是一只猫。");
	//ftprint = ft_printf("%S", L"米");
	//ftprint = ft_printf("%lld", LLONG_MIN);
	//lprint = printf("%lld", LLONG_MIN);
	//printf("%zD, %zD", 0, USHRT_MAX);
	/*
	printf("%15.4s", "42");
	printf("%15.4s", "I am 42");
	printf("%15.4s", "42 is the answer");
	printf("%4.15s", "42");
	printf("%ls, %ls", L"暖炉", L"لحم خنزير");
	printf("%15.4S", L"我是一只猫。");
	printf("%4.15S", L"我是一只猫。");
	printf("%4.S", L"我是一只猫。");
	printf("%4.1S", L"Jambon");
	printf("%");
	printf("% Zoooo");
	printf("{%}");
	printf("{%10R}");
	printf("{%30S}", L"我是一只猫。");
	printf("{%-30S}", L"我是一只猫。");
	ftprint = ft_printf("%");
	ftprint = ft_printf("%.4S", L"我是一只猫。");
	lprint = printf("%.4S", L"我是一只猫。");
	lprint = printf("%");
	ft_printf("{%3c}", 0);
	printf("{%S}", NULL);
	ftprint = ft_printf("%lld", LLONG_MAX);
	lprint = printf("%lld", LLONG_MAX);
	lprint = printf("%lc", L'Ж');
	lprint = printf("%C", 0x20ac);
	printf("%s %C %d %p %x %% %S", "bonjour ", L'該', 42, &free, 42, L"لحم خنزير");
	printf("%s%d%p%%%S%D%i%o%O%u%U%x%X%c%C","bonjour", 42, &c, L"暖炉", LONG_MAX, 42, 42, 42, 100000, ULONG_MAX, 42, 42, 'c', L'플');
	ftprint = ft_printf("%s%d%p%%%S%D%i%o%O%u%U%x%X%c%C","bonjour", 42, &c, L"暖炉", LONG_MAX, 42, 42, 42, 100000, ULONG_MAX, 42, 42, 'c', L'플');
	ftprint = ft_printf("{%05.S}", L"42 c est cool");
	*/
	char	c;
	/*
	ftprint = ft_printf("1: %+10.5d", 4242);
	pf_putstr("\n");
	lprint = printf("1: %+10.5d", 4242);
	printf("\nftprintf bytes: %d, lprint bytes: %d\n\n", ftprint, lprint);
	ftprint = ft_printf("2: {%+03d}", 0);
	pf_putstr("\n");
	lprint = printf("2: {%+03d}", 0);
	printf("\nftprintf bytes: %d, lprint bytes: %d\n\n", ftprint, lprint);
	ftprint = ft_printf("3: %#08x", 42);
	pf_putstr("\n");
	lprint = printf("3: %#08x", 42);
	ftprint = ft_printf("%*.*d", 5, 3, 0);
	ftprint = ft_printf("%*d", 5, 42);
	ftprint = ft_printf("{%*d}", -5, 42);
	ftprint = ft_printf("{%*c}", -15, 0);
	printf("{%.*s}", -5, "42");
	printf("{%3*p}", 10, 0);
	ftprint = ft_printf("{%.*s}", -5, "42");
	*/
	//ftprint = ft_printf("{%C}", 0xD800);
	wchar_t wchr = 0xD800;
	ftprint = ft_printf("{%d %C okay}", 3, wchr);
	pf_putstr("\n");
	lprint = printf("{%d %C okay}", 3, wchr);
	printf("\nftprintf bytes: %d, lprint bytes: %d\n\n", ftprint, lprint);
	lprint = printf("a%Sb%sc%S", L"我", "42", L"猫");
	return(0);
}
//four bytes unicode  𩶘
/*
	printf("{%10R}");
	ft_printf("{% c}", 0);
	ft_printf("%hhd%hhd", 1, 42);
	ft_printf("%hhd", CHAR_MAX);
	ft_printf("%hhd", CHAR_MAX + 42);
	ft_printf("%hhd", CHAR_MIN);
	ft_printf("%hhd", CHAR_MIN - 42);
	ft_printf("%hhi%hhi", 0, 42);
	ft_printf("%hhd", CHAR_MAX);
	ft_printf("%hhd", CHAR_MAX + 42);
	ft_printf("%hhi", CHAR_MIN);
	ft_printf("%hhi", CHAR_MIN - 42);
	ft_printf("%hhu, %hhu", 0, UCHAR_MAX);
	ft_printf("%hho, %hho", 0, UCHAR_MAX);
	ft_printf("%hhx, %hhx", 0, UCHAR_MAX);
	ft_printf("%hhX, %hhX", 0, UCHAR_MAX);
	ft_printf("%hhu, %hhu", 0, UCHAR_MAX + 42);
	ft_printf("%hho, %hho", 0, UCHAR_MAX + 42);
	ft_printf("%hhx, %hhx", 0, UCHAR_MAX + 42);
	ft_printf("%hhO, %hhO", 0, USHRT_MAX);
	ft_printf("%hhU, %hhU", 0, USHRT_MAX);
	ft_printf("%hhD, %hhD", 0, USHRT_MAX);
	ft_printf("%hhC, %hhC", 0, L'米');
	ft_printf("%hhS, %hhS", 0, L"米米");
}
	printf("%zd%zd", 0, 42);
	printf("%zd", LLONG_MAX);
	printf("%zi%zi", 0, 42);
	printf("%zD, %zD", 0, USHRT_MAX);
	printf("%zU, %zU", 0, USHRT_MAX);
*/
