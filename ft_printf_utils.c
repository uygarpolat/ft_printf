/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:51:54 by upolat            #+#    #+#             */
/*   Updated: 2024/05/05 13:43:48 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

char	*ft_utoa(unsigned int d)
{
	int				digit;
	unsigned int	un_i;
	char			*str;

	un_i = d;
	digit = 0;
	while (un_i > 0)
	{
		un_i = un_i / 10;
		digit++;
	}
	if (digit == 0)
		digit++;
	str = malloc(sizeof(char) * (digit + 1));
	if (str == NULL)
		return (0);
	str[digit] = '\0';
	while (digit > 0)
	{
		str[--digit] = (d % 10) + '0';
		d = d / 10;
	}
	while (str[digit])
		ft_putchar_fd(str[digit++], 1);
	return (str);
}
