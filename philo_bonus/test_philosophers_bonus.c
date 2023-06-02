/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_philosophers_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:42:48 by iantar            #+#    #+#             */
/*   Updated: 2023/06/02 10:54:46 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers_bonus.h"
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

size_t	micro_current_time_(size_t micro_t0)
{
	size_t	t;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	t = current_time.tv_sec / 1000000 + current_time.tv_usec;
	return (t - micro_t0);
}

void	*routine(t_data *data, int ac)
{
	int				id_;

	(void)ac;
	pthread_mutex_lock(&data->mutex[data->ph_num]);
	id_ = data->ph_id;
	pthread_mutex_unlock(&data->mutex[data->ph_num]);
	while (1)
	{
		pthread_mutex_lock(&data->mutex[id_ - 1]);
		pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
		printf("%dms %d has taken a fork\n", current_time_(data->t0), id_);
		pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);
		pthread_mutex_lock(&data->mutex[min_max(id_, data->ph_num)]);
		pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
		printf("%dms %d has taken a fork\n", current_time_(data->t0), id_);
		pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);
		pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
		printf("%dms :%d is eating\n\n", current_time_(data->t0), id_);
		pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);
		//ft_msleep(data->eat_time, data->t0);
		//ft_usleep2(data->eat_time * 1000);
		ft_usleep(data->eat_time * 1000);
	
		pthread_mutex_unlock(&data->mutex[id_ - 1]);
		pthread_mutex_unlock(&data->mutex[min_max(id_, data->ph_num)]);
		//usleep(10);
		pthread_mutex_lock(&data->mutex[data->ph_num + 1]);
		//printf("UPUPUPPUPUPUPUPUPUPU\n");
		data->n_times_eat[id_ - 1] = data->n_times_eat[id_ - 1] + 1;
		data->count_eat_time[id_ - 1] = current_time_(data->t0);
		pthread_mutex_unlock(&data->mutex[data->ph_num + 1]);
		
		pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
		printf("%dms :%d is sleeping\n", current_time_(data->t0), id_);
		pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);
		//ft_msleep(data->sleep_time, data->t0);
		//ft_usleep2(data->sleep_time * 1000);
		ft_usleep(data->sleep_time * 1000);
		pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
		printf("%dms :%d is thinking\n", current_time_(data->t0), id_);
		pthread_mutex_unlock(&data->mutex[data->ph_num + 3]);
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

// void	ft_msleep(int tm, int start_t0)
// {
// 	int	t0;

// 	t0 = current_time_(start_t0);
// 	while (current_time_(start_t0) - t0 <= tm)
// 	;
// }
void	ft_usleep(size_t time)
{
	struct timeval	current_time;
	size_t	start;
	size_t	end;

	gettimeofday(&current_time, NULL);
	start = current_time.tv_sec / 1000000 + current_time.tv_usec;
	end = start;
	while (end - start <= time)
	{
		gettimeofday(&current_time, NULL);
		end = current_time.tv_sec / 1000000 + current_time.tv_usec;
		//printf("end - start:%lu, time:%lu\n", end - start, time);
	}
}

// void	ft_usleep2(int tm)
// {
// 	int	i;

// 	i = 0;
// 	while (i < tm / 10)
// 	{
// 		usleep(10);
// 		i++;
// 	}
// }

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

int	main(int ac, char *av[])
{
	t_data			*data;
	struct timeval	current_time;
	int				i;
	//int		micro_t0;

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
	data->micro_t0 = current_time.tv_sec / 1000000 + current_time.tv_usec;
	while (i < data->ph_num)
	{
		pthread_mutex_lock(&data->mutex[data->ph_num]);
		data->ph_id = i + 1;
		pthread_mutex_unlock(&data->mutex[data->ph_num]);
		if (pthread_create(&data->p_th[i], NULL, (void *)&routine, (void *)data))
			return (printf("Thread can't be created\n"), 1);
		ft_usleep(100);
		pthread_mutex_lock(&data->mutex[data->ph_num + 1]);
		if (current_time_(data->t0) - data->count_eat_time[i] >= data->die_time)
		{
			pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
			return (printf("\e[0;31m""%dms %d died\n",current_time_(data->t0), i + 1), destory_evrything(data), 1);
		}
		pthread_mutex_unlock(&data->mutex[data->ph_num + 1]);
		/////////////
		i++;
	}
	//write(1, "$$$$$$$$$$$\n", 12);
	// i = 0;
	// while (i < data->ph_num)
	// {
	// 	write(1, "************************\n\n", 26);
	// 	pthread_join(data->p_th[i], NULL);
	// 	i++;
	// }
	i = 0;
	while (1)
	{
		//ft_msleep(1, data->t0);
		//ft_usleep(100, data->micro_t0);
		//ft_usleep2(1000);
		//ft_usleep(1000);
		ft_usleep(100);
		if (i == data->ph_num)
			i = 0;
		pthread_mutex_lock(&data->mutex[data->ph_num + 1]);
		if (ac == 6)
		{
			if (check_for_n_eat_times(data->n_times_eat, data->ph_num, ft_atoi(av[5])))
			{
				
				pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
				return (/*, destory_evrything(data)*/1);
			}
		}
		if (micro_current_time_(data->micro_t0)/1000 - data->count_eat_time[i] >= data->die_time)
		{
			pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
			return (printf("\e[0;31m""%dms %d died\n",current_time_(data->t0), i + 1),/*, destory_evrything(data)*/1);
		}
		// if (current_time_(data->t0) - data->count_eat_time[i] >= data->die_time)
		// {
		// 	pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
		// 	return (printf("\e[0;31m""%dms %d died\n",current_time_(data->t0), i + 1),/*, destory_evrything(data)*/1);
		// }
		pthread_mutex_unlock(&data->mutex[data->ph_num + 1]);
		i++;
		//write(1, "|||||||||||||||||||||||||\n\n", 27);
	}
	return (0);	
}
