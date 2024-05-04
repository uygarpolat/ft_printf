/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:47:38 by upolat            #+#    #+#             */
/*   Updated: 2024/05/04 15:23:48 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include <stdio.h>
#include <unistd.h>

int	print_d(int d)
{
	char	*nbr;
	int		result;
	int		i;

	i = 0;
	result = 0;
	nbr = ft_itoa(d);
	result = ft_strlen(nbr);
	while (nbr[i])
	{
		ft_putchar_fd(nbr[i], 1);
		i++;
	}
	free(nbr);
	return (result);
}

int	print_s(char *s)
{
	int	result;
	int	i;

	i = 0;
	result = ft_strlen(s);
	while (s[i])
	{
		ft_putchar_fd(s[i], 1);
		i++;
	}
	return (result);
}

int	print_c(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	duplicate_character_checker(char *base)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (base[i] != 0)
	{
		j = i + 1;
		while (base[j] != 0)
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	base_checker(char *base)
{
	int	i;

	i = 0;
	while (base[i] != 0)
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	if (i < 2 || duplicate_character_checker(base) == 0)
		return (0);
	return (i);
}

int	ft_putnbr_base(uintptr_t nb, char *base)
{
	int		len;
	char	c;
	int		total_length;

	total_length = 0;
	len = base_checker(base);
	if (len > 0)
	{
		if (nb < (uintptr_t)len)
		{
			c = base[nb];
			ft_putchar_fd(c, 1);
			total_length++;
		}
		else
		{
			total_length += ft_putnbr_base(nb / len, base);
			c = base[nb % len];
			ft_putchar_fd(c, 1);
			total_length++;
		}
	}
	return (total_length);
}

int	print_p(void *voidstr)
{
	int			len;
	uintptr_t	iptr;

	iptr = (uintptr_t)voidstr;
	ft_putstr_fd("0x", 1);
	len = 2;
	len += ft_putnbr_base(iptr, "0123456789abcdef");
	return (len);
}

int	print_u(unsigned int ud)
{
	char	*nbr;
	int		i;
	int		len;

	i = 0;
	nbr = ft_itoa(ud);
	len = ft_strlen(nbr);
	while (nbr[i])
	{
		ft_putchar_fd(nbr[i], 1);
		i++;
	}
	free(nbr);
	return (len);
}

int	print_x(int d, const char s)
{
	int	len;

	if (s == 'x')
		len = ft_putnbr_base(d, "0123456789abcdef");
	else
		len = ft_putnbr_base(d, "0123456789ABCDEF");
	return (len);
}

int	print_percent(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	caster(va_list *arg, const char s)
{
	int	result;

	result = 0;
	if (s == 'd' || s == 'i')
		result += print_d(va_arg(*arg, int));
	if (s == 's')
		result += print_s(va_arg(*arg, char *));
	if (s == 'c')
		result += print_c(va_arg(*arg, int));
	if (s == 'p')
		result += print_p(va_arg(*arg, void *));
	if (s == 'u')
		result += print_u(va_arg(*arg, unsigned int));
	if (s == 'x' || s == 'X')
		result += print_x(va_arg(*arg, int), s);
	//if (s == '%')
	//	result += print_percent(va_arg(*arg, int));
	return (result);
}

int	ft_printf(const char *s, ...)
{
	va_list	arg;
	int		res;
	int		i;

	i = 0;
	res = 0;
	va_start(arg, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			if (s[i + 1] == '%')
			{
				ft_putchar_fd(s[++i], 1);
				res++;
			}
			else
				res += caster(&arg, s[++i]);
		}
		else
		{
			ft_putchar_fd(s[i], 1);
			res++;
		}
		i++;
	}
	va_end(arg);
	return (res);
}

int main(void)
{
	int printf_result;
	int ft_printf_result;
	char *str = "890123456";
	int nbr = 67890;
	char c = 'L';
	int nbr2 = 1234567;
	unsigned int unint = 23423523;

	printf_result = printf("1234567%s%d%c%i-%%%p-%%%u-%x-%X", str, nbr, c, nbr2, &str, unint, nbr2, nbr2);
	printf("\n");
	ft_printf_result = ft_printf("1234567%s%d%c%i-%%%p-%%%u-%x-%X", str, nbr, c, nbr2, &str, unint, nbr2, nbr2);
	if (printf_result == ft_printf_result)
		printf("\nReturn value of printf is equal to ft_printf (%d vs %d).", printf_result, ft_printf_result);
	else
		printf("\nReturn value of printf is NOT equal to ft_printf (%d vs %d).", printf_result, ft_printf_result);
	return (0);
}

/*
int main(void)
{
	char *str1 = "324tg234g";
	char *str2 = "324tg234g";
	char *str3 = "324tg234g";
	char *str4 = "324tg234g";
	char *str5 = "324tg234g";
	char *str6 = "324tg234g";
	char *str7 = "324tg234g";
	char *str8 = "324tg234g";
	char *str9 = "324tg234g";
	char *str0 = "324tg234g";

	printf("%p\n", &str1);
	ft_printf("%p", &str1);
	printf("\n-----\n");
	printf("%p\n", &str2);
	ft_printf("%p", &str2);
	printf("\n-----\n");
	printf("%p\n", &str3);
	ft_printf("%p", &str3);
	printf("\n-----\n");
	printf("%p\n", &str4);
	ft_printf("%p", &str4);
	printf("\n-----\n");
	printf("%p\n", &str5);
	ft_printf("%p", &str5);
	printf("\n-----\n");
	printf("%p\n", &str6);
	ft_printf("%p", &str6);
	printf("\n-----\n");
	printf("%p\n", &str7);
	ft_printf("%p", &str7);
	printf("\n-----\n");
	printf("%p\n", &str8);
	ft_printf("%p", &str8);
	printf("\n-----\n");
	printf("%p\n", &str9);
	ft_printf("%p", &str9);
	printf("\n-----\n");
	printf("%p\n", &str0);
	ft_printf("%p", &str0);
	printf("\n-----\n");
	return (0);
}
*/
