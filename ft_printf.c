/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:47:38 by upolat            #+#    #+#             */
/*   Updated: 2024/05/03 16:12:49 by upolat           ###   ########.fr       */
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
	return(result);
}

int	print_s(char *s)
{
	int	result;
	int	i;

	i = 0;
	result = ft_strlen(s);
	while(s[i])
		ft_putchar_fd(s[i++], 1);
	return(result);
}

int	caster(va_list arg, const char s)
{
	int	result;

	result = 0;
	if (s == 'd')
		result += print_d(va_arg(arg, int));
	if (s == 's')
		result += print_s(va_arg(arg, char*));
	return (result);
}

int ft_printf(const char *s, ...)
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
			res += caster(arg, s[i + 1]);
			i++;
		}
		else
		{
			ft_putchar_fd(s[i], 1);
			res++;
		}
		i++;
	}
	va_end(arg);
	printf("\nRes is: %d", res);
	return (res);
}

int main()
{
	ft_printf("1234567%d%s", 89012345, "67890");
	return (0);
}
