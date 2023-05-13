/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:33:39 by iantar            #+#    #+#             */
/*   Updated: 2023/05/03 22:11:06 by iantar           ###   ########.fr       */
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
 
void	*routine(t_data *data)
{
	int				t;
	struct timeval	current_time;
	int				i;

	i = 0;
	while (i < 20)
	{
		if (!(data->ph_id % 2))
		{
			//printf("HE:%d\n", data->ph_id);
			//printf("i=%d\n", i);
			//while (1);
			usleep(data->eat_time + data->sleep_time);
		}
		// {
			//printf("i=%d\n", i);
			
			pthread_mutex_lock(&(data->mutex[0]));0
			gettimeofday(&current_time, NULL);
			t = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
			// printf("%dms %d has taken a fork\n", t - data->t0, data->ph_id);
			// gettimeofday(&current_time, NULL);
			// t = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;//ms
			printf("%dms %d is eating\n", t - data->t0, data->ph_id);
			usleep(data->eat_time);
			// gettimeofday(&current_time, NULL);
			// t = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
			// printf("%dms %d is sleeping\n", t - data->t0, data->ph_id);
			// usleep(data->sleep_time);
			// gettimeofday(&current_time, NULL);
			// t = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
			// printf("%dms %d is thinking\n", t - data->t0, data->ph_id);
			pthread_mutex_unlock(&(data->mutex[0]));
			//printf("%dms %d died\n");
		//}
	}
	//printf("");
	return (NULL);
}

int	main(int ac, char *av[])
{
	t_data			*data;
	pthread_t		*ph;
	struct timeval	current_time;
	int				i;

	if (ac < 5 || ac > 6)
		return (1);
	//max of int
	//if (ft_parce())//check if there is unvalid arg, like in push_swap.
	// return (1);
	//arg = get_num_from_arg(av, ac);
	data = malloc(sizeof(t_data));
	data->ph_num = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	ph = malloc(data->ph_num * sizeof(pthread_t));
	if (!ph)
		return (1);
	i = 1;
	if (pthread_mutex_init(&data->mutex[0], NULL))
        return (printf("\n mutex init has failed\n"), 1);
	if (pthread_mutex_init(&data->mutex[1], NULL))
        return (printf("\n mutex init has failed\n"), 1);
	gettimeofday(&current_time, NULL);
	data->t0 = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;//ms
	while (i <= data->ph_num)
	{
		data->ph_id = i;
		if (pthread_create(&ph[i - 1], NULL, (void *)&routine, (void *)data))
			return (printf("Thread can't be created\n"), 1);
		i++;
	}
	i = 0;
	while (++i <= data->ph_num)
	{
		if (pthread_join(ph[i], NULL))
			return (printf("thread can't join\n"), 1);
	}
	// i = 0;
	// while (++i <= data->ph_num)
	// 	pthread_detach(ph[i]);
	// //data.n_times_eat = ft_atoi(av[5]);
	// pthread_mutex_destroy(&data->mutex);
	free(ph);
	return (0);	
}