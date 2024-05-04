/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:47:38 by upolat            #+#    #+#             */
/*   Updated: 2024/05/04 17:35:09 by upolat           ###   ########.fr       */
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
		result = print_d(va_arg(*arg, int));
	if (s == 's')
		result = print_s(va_arg(*arg, char *));
	if (s == 'c')
		result = print_c(va_arg(*arg, int));
	if (s == 'p')
		result = print_p(va_arg(*arg, void *));
	if (s == 'u')
		result = print_u(va_arg(*arg, unsigned int));
	if (s == 'x' || s == 'X')
		result = print_x(va_arg(*arg, int), s);
	if (s == '%')
		result = print_percent(va_arg(*arg, int));
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
				res += print_percent(s[++i]);
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
