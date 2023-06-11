/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:17:52 by iantar            #+#    #+#             */
/*   Updated: 2023/06/11 14:48:04 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static char	*revstr(char *str)
{
	size_t		i;
	size_t		j;
	char		tem;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < ft_strlen(str) / 2)
	{
		tem = str[i];
		str[i] = str[j];
		str[j] = tem;
		i++;
		j--;
	}
	return (str);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	new;
	char	str[13];
	int		i;

	if (n == 0)
		ft_putchar_fd(0 + '0', fd);
	else
	{
		new = n;
		i = 0;
		if (new < 0)
		{
			new = new * -1;
			write(fd, "-", 1);
		}
		while (new > 0)
		{
			str[i++] = new % 10 + '0';
			new = new / 10;
		}
		str[i] = '\0';
		ft_putstr_fd(revstr(str), fd);
	}
}
