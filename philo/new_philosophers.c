/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:53:00 by iantar            #+#    #+#             */
/*   Updated: 2023/05/24 14:08:46 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void	ft_msleep(size_t time)
{
	struct timeval	current_time;
	size_t	start;
	size_t	end;

	gettimeofday(&current_time, NULL);
	start = current_time.tv_sec * 1000 + current_time.tv_usec / 1000 ;
	end = start;
	while (end - start < time)
	{
		usleep(50);
		gettimeofday(&current_time, NULL);
		end = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	}
}


size_t	current_time_(t_data *data)
{
	size_t	t;
	static int	one_time;
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

void	forks_eating(t_data *data, int id_, int ac)
{
	(void)ac;
	pthread_mutex_lock(&data->mutex[id_ - 1]);//take fork1
	//pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
	printf("%zums %d has taken a fork\n", current_time_(data), id_);
	//pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);
	
	pthread_mutex_lock(&data->mutex[id_ % data->ph_num]);//take fork2 (id_ + 1) % data->ph_num
	//pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
	printf("%zums %d has taken a fork\n", current_time_(data), id_);
	//pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);
	//pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
	printf("%zums :%d is eating\n\n", current_time_(data), id_);
	//pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);
	//usleep(data->eat_time * 1000);
	ft_msleep(data->eat_time);
	pthread_mutex_lock(&data->mutex[data->ph_num + 1]);
	data->n_times_eat[id_ - 1] = data->n_times_eat[id_ - 1] + 1;
	data->count_eat_time[id_ - 1] = current_time_(data);
	//printf("%zu\n\n\n", data->count_eat_time[id_ - 1]);

	pthread_mutex_unlock(&data->mutex[data->ph_num + 1]);
	pthread_mutex_unlock(&data->mutex[id_ - 1]);//release fork2
	pthread_mutex_unlock(&data->mutex[id_ % data->ph_num]);//release fork2
}

void	*routine(t_data *data, int ac)
{
	int				id_;

	pthread_mutex_lock(&data->mutex[data->ph_num]);
	id_ = data->ph_id;
	pthread_mutex_unlock(&data->mutex[data->ph_num]);
	while (1)
	{
		// if (id_ % 2)
		// 	usleep(50);
		forks_eating(data, id_, ac);
		//pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
		printf("%zu ms :%d is sleeping\n", current_time_(data), id_);
		//pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);
		//usleep(data->sleep_time * 1000 - 10);
		ft_msleep(data->sleep_time);
		//pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
		printf("%zu ms :%d is thinking\n", current_time_(data), id_);
		//pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);
	}
}

void	print_data(size_t *data, int num_ph)
{
	int	i;

	i = 0;
	while (i < num_ph)
	{
		printf("data[%d]:%zu\n", i, data[i]);
		i++;
	}
}

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
	//printf("data->mutex: %p, size: %zu ", data->mutex, sizeof(pthread_t) * (data->ph_num + 5));
	data->count_eat_time = malloc((data->ph_num) * sizeof(size_t));
	//printf("data->eat: %p, size: %zu ", data->count_eat_time, sizeof(size_t) * data->ph_num);

	ft_bzero(data->count_eat_time, (data->ph_num) * sizeof(size_t));
	data->n_times_eat = malloc((data->ph_num) * sizeof(int));
	ft_bzero(data->n_times_eat, (data->ph_num) * sizeof(int));
	//print_data(data->count_eat_time, data->ph_num);
	return (data);
}

int	check_death(t_data *data, int ac, char **av)
{
	int	i;

	i = 0;
	//print_data(data->count_eat_time, data->ph_num);
	//while (1);
	while (1)
	{
		if (i == data->ph_num)
			i = 0;
		pthread_mutex_lock(&data->mutex[data->ph_num + 1]);
		//usleep(100);
		if (ac == 6)
		{
			if (check_for_n_eat_times(data->n_times_eat, data->ph_num, ft_atoi(av[5])))
			{
				pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
				return (1);
			}
		}
		//print_data(data->count_eat_time, data->ph_num);
		if (current_time_(data) - data->count_eat_time[i] >= data->die_time)
		{
			//printf("current_time_(data):%zu - data->count_eat_time[%d]:%zu==%zu\n",current_time_(data),i, data->count_eat_time[i], current_time_(data) - data->count_eat_time[i]);
			//printf("data->die_time:%zu\n", data->die_time);
			//pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
			return (printf("\e[0;31m""%zums %d died\n",current_time_(data), i + 1), 1);
		}
		pthread_mutex_unlock(&data->mutex[data->ph_num + 1]);
		i++;
		//write(1, "**************************\n", 27);
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_data			*data;
	int				i; 

	if (check_valid_args(ac, av))
		return (1);
	data = initialize(av);
	//print_data(data->count_eat_time, data->ph_num);
	i = -1;
	while (++i < data->ph_num + 5)
	{
		if (pthread_mutex_init(&data->mutex[i], NULL))
			return (printf("mutex init has failed\n"), 1);
	}
	i = 0;
	//print_data(data->count_eat_time, data->ph_num);
	while (i < data->ph_num)
	{
		pthread_mutex_lock(&data->mutex[data->ph_num]);
		data->ph_id = i + 1;
		pthread_mutex_unlock(&data->mutex[data->ph_num]);
		if (pthread_create(&data->p_th[i], NULL, (void *)&routine, (void *)data))
			return (printf("Thread can't be created\n"), 1);
		usleep(100);
		pthread_mutex_lock(&data->mutex[data->ph_num + 1]);
		if (current_time_(data) - data->count_eat_time[i] >= data->die_time)
		{
			pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
			return (printf("\e[0;31m""%zums %d died\n",current_time_(data), i + 1), 1);
		}
		pthread_mutex_unlock(&data->mutex[data->ph_num + 1]);
		i++;
	}
	if (check_death(data, ac, av))
		return (1);
	return (0);	
}
