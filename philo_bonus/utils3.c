/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:37:09 by iantar            #+#    #+#             */
/*   Updated: 2023/06/12 21:58:32 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_free(t_data *data)
{
	free(data->pid);
	free(data);
}

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
		usleep(98);
		gettimeofday(&current_time, NULL);
		end = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	}
}

int	current_time_(t_data *data)
{
	size_t			t;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	t = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (t - data->t0);
}

void	forks_eating(t_data *data, int index)
{
	sem_wait(data->sem);
	sem_wait(data->bin_sem);
	ft_printf("%dms %d has taken a fork\n", current_time_(data), index);
	sem_post(data->bin_sem);
	sem_wait(data->sem);
	sem_wait(data->bin_sem);
	ft_printf("%dms %d has taken a fork\n", current_time_(data), index);
	sem_post(data->bin_sem);
	sem_wait(data->bin_sem);
	ft_printf("%dms %d is eating\n", current_time_(data), index);
	sem_post(data->bin_sem);
	ft_msleep(data->eat_time);
	gettimeofday(&(data->current_time_die), NULL);
	sem_post(data->sem);
	sem_post(data->sem);
	if (data->ac > 5)
	{
		(data->n_times_eat)--;
		if (!data->n_times_eat)
			(ft_free(data), exit(0));
	}
}

void	kill_childes(pid_t *pid, int ph_num)
{
	int	i;

	i = 0;
	while (i < ph_num)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
}
