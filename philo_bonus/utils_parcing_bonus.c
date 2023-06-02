/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parcing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:12:02 by iantar            #+#    #+#             */
/*   Updated: 2023/06/02 10:54:53 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers_bonus.h"

void	ft_bzero(void *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)str)[i++] = 0;
}

int	min_max(int token, int max)
{
	if (token == max)
		return (0);
	else
		return (token);
}


void	*ft_memset(void *buf, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		((unsigned char *) buf)[i++] = (unsigned char)c;
	return (buf);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	long			i;
	unsigned long	num;
	long			n;

	i = 0;
	num = 0;
	n = 1;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		num = num * 10 + (str[i] - '0');
		i++;
		if (num > __LONG_MAX__ && n > 0)
			return (-1);
		else if (num > __LONG_MAX__ && n < 0)
			return (0);
	}
	return ((int)(n * num));
}

void	destory_evrything(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->ph_num + 4)
		pthread_mutex_destroy(&data->mutex[i]);
	free(data->p_th);
	free(data->mutex);
	free(data->count_eat_time);
	free(data->n_times_eat);
	free(data);
}