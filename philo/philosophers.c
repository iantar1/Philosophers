/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:53:00 by iantar            #+#    #+#             */
/*   Updated: 2023/06/12 21:57:02 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*initialize(char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->ph_num = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	data->p_th = malloc((data->ph_num) * sizeof(pthread_t));
	data->mutex = malloc((data->ph_num + 5) * sizeof(pthread_mutex_t));
	data->count_eat_time = malloc((data->ph_num) * sizeof(size_t));
	ft_bzero(data->count_eat_time, (data->ph_num) * sizeof(size_t));
	data->n_times_eat = malloc((data->ph_num) * sizeof(int));
	ft_bzero(data->n_times_eat, (data->ph_num) * sizeof(int));
	return (data);
}

int	check_death(t_data *data, int ac, char **av)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == data->ph_num)
			i = 0;
		pthread_mutex_lock(&data->mutex[data->ph_num + 1]);
		if (ac == 6)
		{
			if (check_for_n_eat_times(data->n_times_eat, data->ph_num,
					ft_atoi(av[5])))
				return (pthread_mutex_lock(&data->mutex[data->ph_num + 3]), 1);
		}
		if (current_time_(data) - data->count_eat_time[i] > data->die_time)
		{
			pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
			return (ft_printf("%dms %d died\n", current_time_(data),
					i + 1), 1);
		}
		(pthread_mutex_unlock(&data->mutex[data->ph_num + 1]), i++);
	}
	return (0);
}

int	create_thread(t_data *data, int i)
{
	pthread_mutex_lock(&data->mutex[data->ph_num]);
	data->ph_id = i + 1;
	pthread_mutex_unlock(&data->mutex[data->ph_num]);
	if (pthread_create(&data->p_th[i], NULL, (void *)&routine, (void *)data))
		return (ft_printf("Thread can't be created\n"), 1);
	usleep(50);
	pthread_mutex_lock(&data->mutex[data->ph_num + 1]);
	if (current_time_(data) - data->count_eat_time[i] >= data->die_time)
	{
		pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
		return (ft_printf("%dms %d died\n",
				current_time_(data), i + 1), 1);
	}
	pthread_mutex_unlock(&data->mutex[data->ph_num + 1]);
	return (0);
}

int	detach(pthread_t *p_th, int ph_num)
{
	int	i;

	i = 0;
	while (i < ph_num)
	{
		if (pthread_detach(p_th[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_data	*data;
	int		i;

	if (check_valid_args(ac, av))
		return (1);
	data = initialize(av);
	i = -1;
	while (++i < data->ph_num + 5)
	{
		if (pthread_mutex_init(&data->mutex[i], NULL))
			return (ft_printf("mutex init has failed\n"), ft_free(data), 1);
	}
	i = 0;
	while (i < data->ph_num)
	{
		if (create_thread(data, i))
			return (ft_free(data), 1);
		i++;
	}
	if (detach(data->p_th, data->ph_num))
		return (ft_free(data), 1);
	if (check_death(data, ac, av))
		return (ft_free(data), 1);
	return (ft_free(data), 0);
}
