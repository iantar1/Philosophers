/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:42:34 by iantar            #+#    #+#             */
/*   Updated: 2023/06/12 21:43:27 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_msleep(size_t time)
{
	struct timeval	current_time;
	size_t			start;
	size_t			end;

	gettimeofday(&current_time, NULL);
	start = current_time.tv_sec * 1000 + current_time.tv_usec / 1000 ;
	end = start;
	while (end - start < time)
	{
		usleep(100);
		gettimeofday(&current_time, NULL);
		end = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	}
}

int	current_time_(t_data *data)
{
	size_t			t;
	static int		one_time;
	struct timeval	current_time;

	if (!one_time)
	{
		gettimeofday(&current_time, NULL);
		data->t0 = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		one_time++;
	}
	gettimeofday(&current_time, NULL);
	t = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (t - data->t0);
}

int	check_for_n_eat_times(int *n_times, int num_ph, int need_stop)
{
	int	i;

	i = 0;
	while (i < num_ph)
	{
		if (n_times[i] < need_stop)
			return (0);
		i++;
	}
	return (1);
}

void	forks_eating(t_data *data, int id_)
{
	pthread_mutex_lock(&data->mutex[id_ - 1]);
	pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
	ft_printf("%dms %d has taken a fork\n", current_time_(data), id_);
	pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);
	pthread_mutex_lock(&data->mutex[id_ % data->ph_num]);
	pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
	ft_printf("%dms %d has taken a fork\n", current_time_(data), id_);
	pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);
	pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
	ft_printf("%dms %d is eating\n", current_time_(data), id_);
	pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);
	ft_msleep(data->eat_time);
	pthread_mutex_lock(&data->mutex[data->ph_num + 1]);
	data->n_times_eat[id_ - 1] = data->n_times_eat[id_ - 1] + 1;
	data->count_eat_time[id_ - 1] = current_time_(data);
	pthread_mutex_unlock(&data->mutex[data->ph_num + 1]);
	pthread_mutex_unlock(&data->mutex[id_ - 1]);
	pthread_mutex_unlock(&data->mutex[id_ % data->ph_num]);
}

void	*routine(t_data *data)
{
	int				id_;

	pthread_mutex_lock(&data->mutex[data->ph_num]);
	id_ = data->ph_id;
	pthread_mutex_unlock(&data->mutex[data->ph_num]);
	while (1)
	{
		forks_eating(data, id_);
		pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
		ft_printf("%dms %d is sleeping\n", current_time_(data), id_);
		pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);
		ft_msleep(data->sleep_time);
		pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
		ft_printf("%dms %d is thinking\n", current_time_(data), id_);
		pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);
	}
}
