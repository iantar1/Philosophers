/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:01:59 by iantar            #+#    #+#             */
/*   Updated: 2023/06/13 10:56:07 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
		ft_putchar(str[i++]);
	return (i);
}

void	ft_putnbr(long nbr)
{
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr *= -1;
	}
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
	}
	ft_putchar(nbr % 10 + '0');
	return ;
}

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	usleep(100);
	while (i < data->ph_num + 5 && !pthread_mutex_destroy(&data->mutex[i]))
		i++;
	free(data->p_th);
	free(data->mutex);
	free(data->count_eat_time);
	free(data->n_times_eat);
	free(data);
}
