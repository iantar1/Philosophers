/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:42:48 by iantar            #+#    #+#             */
/*   Updated: 2023/05/19 21:40:31 by iantar           ###   ########.fr       */
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

int	min_max(int token, int max)
{
	if (token == max)
		return (0);
	else
		return (token);
}

int	current_time_(int t0)
{
	int	t;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	t = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (t - t0);
}

// void	detach_philo()
// {
	
// }

void	*routine(t_data *data)
{
	int				id_;

	pthread_mutex_lock(&data->mutex[data->ph_num]);
	id_ = data->ph_id;
	pthread_mutex_unlock(&data->mutex[data->ph_num]);
	while (1)
	{
		pthread_mutex_lock(&data->mutex[id_ - 1]);
		pthread_mutex_lock(&data->mutex[data->ph_num + 3]);//when you die stop
		printf("%dms %d has taken a fork\n", current_time_(data->t0), id_);
		pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);//when you die stop*****
		pthread_mutex_lock(&data->mutex[min_max(id_, data->ph_num)]);
		pthread_mutex_lock(&data->mutex[data->ph_num + 3]);//when you die stop
		printf("%dms %d has taken a fork\n", current_time_(data->t0), id_);
		pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);//when you die stop*****
		pthread_mutex_lock(&data->mutex[data->ph_num + 3]);//when you die stop
		printf("%dms :%d is eating\n\n", current_time_(data->t0), id_);
		pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);//when you die stop*****
		upgrade_usleep(data->eat_time, data->t0);
		//usleep(data->eat_time * 1000);
		pthread_mutex_unlock(&data->mutex[id_ - 1]);
		pthread_mutex_unlock(&data->mutex[min_max(id_, data->ph_num)]);
		pthread_mutex_lock(&data->mutex[data->ph_num + 1]);
		data->n_times_eat[id_ - 1] = data->n_times_eat[id_ - 1] + 1;
		data->count_eat_time[id_ - 1] = current_time_(data->t0);
		pthread_mutex_unlock(&data->mutex[data->ph_num + 1]);
		pthread_mutex_lock(&data->mutex[data->ph_num + 3]);//when you die stop
		printf("%dms :%d is sleeping\n", current_time_(data->t0), id_);
		pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);//when you die stop*****
		//upgrade_usleep(data->sleep_time, data->t0);
		usleep(data->sleep_time * 1000);
		pthread_mutex_lock(&data->mutex[data->ph_num + 3]);//when you die stop
		printf("%dms :%d is thinking\n", current_time_(data->t0), id_);
		pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);//when you die stop*****
	}
	return (NULL);
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

t_data	*initialize(char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->ph_num = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	data->p_th = malloc((data->ph_num) * sizeof(pthread_t));
	data->mutex = malloc((data->ph_num) * sizeof(pthread_mutex_t));
	data->count_eat_time = malloc((data->ph_num) * sizeof(int));
	ft_bzero(data->count_eat_time, (data->ph_num) * sizeof(int));
	data->n_times_eat = malloc((data->ph_num) * sizeof(int));
	ft_bzero(data->n_times_eat, (data->ph_num) * sizeof(int));
	return (data);
}

void	upgrade_usleep(int tm, int start_t0)
{
	int	t0;

	t0 = current_time_(start_t0);
	while (current_time_(start_t0) - t0 <= tm)
		usleep(50);
}

// void	upgrade_usleep(int tm, int start_t0)
// {
// 	//int	t0;
// 	int	i;

// 	// t0 = current_time_(start_t0);
// 	// while (current_time_(start_t0) - t0 <= tm)
// 	// 	usleep(1000);
// 	i = 0;
// 	(void)start_t0;
// 	while (i < tm * 10)
// 	{
// 		usleep(10);
// 		usleep(10);
// 		usleep(10);
// 		usleep(10);
// 		usleep(10);
// 		usleep(10);
// 		usleep(10);
// 		usleep(10);
// 		usleep(10);
// 		usleep(10);
		
// 		i++;
// 	}
// }

int	main(int ac, char *av[])
{
	t_data			*data;
	struct timeval	current_time;
	int				i;

	if (check_valid_args(ac, av))
		return (1);
	data = initialize(av);
	i = -1;
	while (++i < data->ph_num + 5)
	{
		if (pthread_mutex_init(&data->mutex[i], NULL))
			return (printf("\n mutex init has failed\n"), 1);
	}
	i = 0;
	gettimeofday(&current_time, NULL);
	data->t0 = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	while (i < data->ph_num)
	{
		pthread_mutex_lock(&data->mutex[data->ph_num]);
		data->ph_id = i + 1;
		pthread_mutex_unlock(&data->mutex[data->ph_num]);
		if (pthread_create(&data->p_th[i], NULL, (void *)&routine, (void *)data))
			return (printf("Thread can't be created\n"), 1);
		i++;
		usleep(100);//why when i sleep 1ms "5 800 200 200" -> no one die.
	}
	i = 0;
	while (1)
	{
		if (i == data->ph_num)
			i = 0;
		//usleep(data->die_time * 1000);
		upgrade_usleep(data->die_time, data->t0);
		pthread_mutex_lock(&data->mutex[data->ph_num + 1]);
		if (ac == 6)
		{
			if (check_for_n_eat_times(data->n_times_eat, data->ph_num, ft_atoi(av[5])))
			{
				pthread_mutex_lock(&data->mutex[data->ph_num + 3]);//when you die stop*****
				return (1);
			}
			//set -1 to all 
		}
		if (current_time_(data->t0) - data->count_eat_time[i] >= data->die_time)
		{
			pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
			//printf("data->count_eat_time[%d]:%d, , ,data->die_time:%d\n",i, data->count_eat_time[i], data->die_time);
			return (printf("\e[0;31m""%dms %d died\n",current_time_(data->t0), i + 1), 1);
		}
		i++;
		pthread_mutex_unlock(&data->mutex[data->ph_num + 1]);
	}
	//destroy_evrything(data);//detach thread, destroy mutex, free what you need to free.
	return (0);	
}
