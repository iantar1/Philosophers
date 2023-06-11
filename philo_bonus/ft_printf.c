/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:02:32 by iantar            #+#    #+#             */
/*   Updated: 2023/06/11 15:02:51 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	len(long nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

int	ft_putnbr_dui(long nbr)
{
	ft_putnbr(nbr);
	return (len(nbr));
}

int	inc(int *i)
{
	*i = *i + 2;
	return (1);
}

int	ft_putarg(va_list ptr, char c, int *i)
{
	if ((c == 'd') && inc(i))
		return (ft_putnbr_dui(va_arg(ptr, int)));
	else if (c == 'u' && inc(i))
		return (ft_putnbr_dui(va_arg(ptr, unsigned int)));
	else if (c == '%' && inc(i))
		return (ft_putchar('%'));
	else
		(*i)++;
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	ptr;
	int		i;
	int		n;

	i = 0;
	n = 0;
	va_start(ptr, str);
	if (str[0] == '%' && !str[1])
		return (0);
	while (str[i])
	{
		if (str[i + 1] && str[i] == '%')
			n = ft_putarg(ptr, str[i + 1], &i) + n;
		else
			n = ft_putchar(str[i++]) + n;
	}
	return (n);
}
