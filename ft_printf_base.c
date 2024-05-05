/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:11:46 by upolat            #+#    #+#             */
/*   Updated: 2024/05/05 12:32:32 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int	duplicate_character_checker(char *base)
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

static int	base_checker(char *base)
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
/*
static void	special_case(int nb, int len, char *base)
{
	ft_putnbr_base(nb / len, base);
	ft_putnbr_base(-(nb % len), base);
}
*/
/*
int	ft_putnbr_base(unsigned int nb, char *base)
{
	char			c;
	unsigned int	len;
	int				total_length;

	total_length = 0;
	len = base_checker(base);
	if (base_checker(base) > 0)
	{
		if (nb < len)
		{
			c = base[nb];
			ft_putchar_fd(c, 1);
			total_length++;
		}
		else
		{
			total_length += ft_putnbr_base((nb / len), base);
			c = base[nb % len];
			ft_putchar_fd(c, 1);
			total_length++;
		}
	}
	return (total_length);
}
*/

int	ft_putnbr_base_unsigned(uintptr_t nb, char *base)
{
	char			c;
	unsigned int	len;
	int				total_length;

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
			total_length += ft_putnbr_base_unsigned(nb / len, base);
			c = base[nb % len];
			ft_putchar_fd(c, 1);
			total_length++;
		}
	}
	return (total_length);
}
