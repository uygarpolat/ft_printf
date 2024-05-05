/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:12:00 by upolat            #+#    #+#             */
/*   Updated: 2024/05/05 13:42:36 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	print_d_i(int d)
{
	char	*nbr;
	int		result;

	result = 0;
	nbr = ft_itoa(d);
	result = ft_strlen(nbr);
	ft_putstr_fd(nbr, 1);
	free(nbr);
	return (result);
}

int	print_s(char *s)
{
	int	result;

	if (s == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	result = ft_strlen(s);
	ft_putstr_fd(s, 1);
	return (result);
}

int	print_c(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	print_u(unsigned int d)
{
	char	*str;
	int		len;

	str = ft_utoa(d);
	len = ft_strlen(str);
	free(str);
	return (len);
}

int	print_p_x(void *voidstr, const char c)
{
	int				len;
	uintptr_t		iptr;
	unsigned int	uint;

	len = 0;
	iptr = (uintptr_t)voidstr;
	uint = (unsigned int)iptr;
	if (c == 'x')
		len = ft_putnbr_base_unsigned(uint, "0123456789abcdef");
	else if (c == 'X')
		len = ft_putnbr_base_unsigned(uint, "0123456789ABCDEF");
	else if (c == 'p')
	{
		ft_putstr_fd("0x", 1);
		len += 2;
		len += ft_putnbr_base_unsigned(iptr, "0123456789abcdef");
	}
	return (len);
}

/*
int	print_p(void *voidstr)
{
	int			len;
	uintptr_t	iptr;

	iptr = (uintptr_t)voidstr;
	ft_putstr_fd("0x", 1);
	len = 2;
	len += ft_putnbr_base_unsigned(iptr, "0123456789abcdef");
	return (len);
}

int	print_x(unsigned int d, const char c)
{
	int	len;

	if (c == 'x')
		len = ft_putnbr_base_unsigned(d, "0123456789abcdef");
	else
		len = ft_putnbr_base_unsigned(d, "0123456789ABCDEF");
	return (len);
}
*/
