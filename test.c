# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef	struct s_data
{
	int	t0;
	int	t_check;
	int	ph;
}			t_data;

void	*ft_eat1(t_data *data)
{
	int	t;
	struct timeval current_time;
	while (1)
	{
		gettimeofday(&current_time, NULL);
		t = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;//micro second
		//printf("current_time.tv_sec:%ld, current_time.tv_usec:%d\n", current_time.tv_sec, current_time.tv_usec);
		printf("%dms %d has taken a fork\n", t - data->t0 , data->ph);
		gettimeofday(&current_time, NULL);
		t = current_time.tv_sec + current_time.tv_usec / 1000;//micro second
		printf("%dms %d is eating\n", t - data->t0, data->ph);
		usleep(1000 * 1000);
		gettimeofday(&current_time, NULL);
		t = current_time.tv_sec + current_time.tv_usec / 1000;//micro second
		printf("%dms %d is sleeping\n", t - data->t0, data->ph);
		usleep(1000 * 1000);//time to sleep
		gettimeofday(&current_time, NULL);
		t = current_time.tv_sec + current_time.tv_usec / 1000;//micro second
		printf("%dms %d is thinking\n", t - data->t0, data->ph);
		gettimeofday(&current_time, NULL);
		t = current_time.tv_sec + current_time.tv_usec / 1000;//micro second
		printf("%dms %d is died\n", t - data->t0, data->ph);
	}
	return (NULL);
}

int	lock = 0;

void	*ft_eating(t_data *data)
{
	int	t;
	struct timeval current_time;

	while(1)
	{
		gettimeofday(&current_time, NULL);
		t = current_time.tv_sec + current_time.tv_usec / 1000;
		if (lock == 0)
		{
			lock = 1;
			if ((t - data->t0) - data->t_check > 3)
				return (printf("%dms %d is died\n", t - data->t0, data->ph), exit(0), NULL);
			printf("%dms %d is eating\n", t - data->t0, data->ph);
			usleep(1000 * 1000);
			gettimeofday(&current_time, NULL);
			t = current_time.tv_sec + current_time.tv_usec / 1000;
			data->t_check = t - data->t0;
			lock = 0;
		}
		// gettimeofday(&current_time, NULL);
		// t = current_time.tv_sec + current_time.tv_usec / 1000;
		printf("%dms %d is sleeping\n", t - data->t0, data->ph);
		usleep(1000 * 1000);
	}
	return (NULL);
}

int	main(void)
{
	t_data	*data1;
	t_data	*data2;
	int		t0;
	struct timeval current_time;
	pthread_t	ph1, ph2;//has information about the thread

	data1 = malloc(sizeof(t_data));
	data2 = malloc(sizeof(t_data));
	if (gettimeofday(&current_time, NULL) == -1)
		return (1);
	t0 = current_time.tv_sec + current_time.tv_usec / 1000;//m second
	data1->ph = 1;
	data1->t0 = t0;
	data2->ph = 2;
	data2->t0 = t0;
	pthread_create(&ph1, NULL, (void *)&ft_eating, (void *)data1);
	pthread_create(&ph2, NULL, (void *)&ft_eating, (void *)data2);
	pthread_join(ph1, NULL);
	pthread_join(ph2, NULL);
	// if (gettimeofday(&current_time, NULL) == -1)
	// 	return (1);
	return (0);
}