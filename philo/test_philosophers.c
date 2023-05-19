/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:33:39 by iantar            #+#    #+#             */
/*   Updated: 2023/05/17 09:39:29 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"
// ./philo   number_of_philosophers       time_to_die      time_to_eat        time_to_sleep        
//   [number_of_times_each_philosopher_must_eat]

//av[0]: ./philo
//av[1]: number_of_philosophers
//av[2]: time_to_die 
//av[3]: time_to_eat -> usleep(time_to_eat)
//av[4]: time_to_sleep -> usleep(time_to_sleep)
//av[5]: [number_of_times_each_philosopher_must_eat]

void	ft_bzero(void *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)str)[i++] = 0;
}

void	*ft_memset(void *buf, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		((unsigned char *) buf)[i++] = (unsigned char)c;
	return (buf);
}

int	current_time_(int t0)
{
	int	t;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	t = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (t - t0);
}

int	min_max(int token, int max)
{
	if (token == max)
		return (0);
	else
		return (token);
}

int	check_eat_time(int last_time, int current_time)
{
	return (current_time - last_time);
}

void	*routine(t_data *data)
{
	//int				i;
	int				id_;

	//i = 0;
	pthread_mutex_lock(&data->mutex[data->ph_num]);
	id_ = data->ph_id;
	pthread_mutex_unlock(&data->mutex[data->ph_num]);
	//printf("in_routine_data->ph_id:%p\n", &data->ph_id);
	while (1)
	{
		printf("data->t0:%p\n", &(data->t0));
		// if (data->count_eat_time[id_] == -1)
		// {
		// 	printf("I REACH here\n");
		// 	pthread_mutex_lock(&data->mutex[data->ph_num + 2]);
		// }
		pthread_mutex_lock(&data->mutex[id_ - 1]);
		printf("%dms %d has taken a fork\n", current_time_(data->t0), id_);
		pthread_mutex_lock(&data->mutex[min_max(id_, data->ph_num)]);
		printf("%dms %d has taken a fork\n", current_time_(data->t0), id_);
		printf("%dms :%d is eating\n\n", current_time_(data->t0), id_);
		usleep(1000);
		pthread_mutex_unlock(&data->mutex[id_ - 1]);

		pthread_mutex_lock(&data->mutex[data->ph_num + 1]);
		printf("data->count_eat_time[%d]:%d\n", id_, data->count_eat_time[id_]);
		data->count_eat_time[id_] = current_time_(data->t0);
		printf("------------>>>>data->count_eat_time[%d]:%d\n", id_, data->count_eat_time[id_]);
		pthread_mutex_unlock(&data->mutex[data->ph_num + 1]);

		pthread_mutex_unlock(&data->mutex[min_max(id_, data->ph_num)]);
		printf("%dms :%d is sleeping\n", current_time_(data->t0), id_);
		usleep(1000);
		printf("%dms :%d is thinking\n", current_time_(data->t0), id_);
		usleep(1000);
	}
	return (NULL);
}

int	main(int ac, char *av[])
{
	t_data			*data;
	struct timeval	current_time;
	int				i;
	int				status;

	if (ac < 5 || ac > 6)
		return (1);
	//max of int
	//if (ft_parce())//check if there is unvalid arg, like in push_swap.
	// return (1);
	//arg = get_num_from_arg(av, ac);  
	status = 0;
	data = malloc(sizeof(t_data));
	data->ph_num = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	data->p_th = malloc((data->ph_num) * sizeof(pthread_t));
	data->mutex = malloc((data->ph_num) * sizeof(pthread_mutex_t));
	data->count_eat_time = malloc((data->ph_num) * sizeof(int));
	ft_bzero(data->count_eat_time, (data->ph_num) * sizeof(int));
	if (!data->p_th)
		return (1);
	i = -1;
	while (++i < data->ph_num + 5)
	{
		if (pthread_mutex_init(&data->mutex[i], NULL))
			return (printf("\n mutex init has failed\n"), 1);
	}
	gettimeofday(&current_time, NULL);
	//pthread_mutex_lock(&data->mutex[data->ph_num]);
	data->t0 = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;//ms
	//pthread_mutex_unlock(&data->mutex[data->ph_num + 1]);
	i = 0;
	printf("I:%p\n", &i);
	sleep(1);
	while (i < data->ph_num)
	{
		pthread_mutex_lock(&data->mutex[data->ph_num]);
		data->ph_id = i + 1;
		pthread_mutex_unlock(&data->mutex[data->ph_num]);
		printf("data->ph_id:%p\n", &data->ph_id);
		if (pthread_create(&data->p_th[i], NULL, (void *)&routine, (void *)data))
			return (printf("Thread can't be created\n"), 1);
		usleep(100);
		i++;
	}
	i = 0;
	while (1)
	{
		if (i == data->ph_num)
			i = 0;
		pthread_mutex_lock(&data->mutex[data->ph_num + 1]);
		usleep(10000);
		if (current_time_(data->t0) - data->count_eat_time[i] >= data->die_time)
		{
			printf("data->count_eat_time[%d]:%d, , ,data->die_time:%d\n",i, data->count_eat_time[i], data->die_time);
			// pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
			// ft_memset(data->count_eat_time, -1, (data->ph_num) * sizeof(int));
			// printf(">>>>>>>>>%d\n", data->count_eat_time[0]);
			// pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);
			// usleep(1000);
			return (printf("\e[0;31m""%dms %d died\n",current_time_(data->t0), data->ph_id), 1);
		}
		i++;
		pthread_mutex_unlock(&data->mutex[data->ph_num + 1]);
	}
	return (0);	
}