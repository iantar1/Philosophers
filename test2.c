# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct	s_data
{
	int				t0;
	int				id[3];
	pthread_t		ph[3];
	pthread_mutex_t	mutex[2];
}t_data;

pthread_mutex_t	mutex[2];
int	t0;
static int	die_time[3];

int	time_to_die(int lsat_time, int curent_time)
{
	return (curent_time - lsat_time);
}

int	current_time_(int t0)
{
	int	t;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	t = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (t - t0);
}

void	*fun(int *data)
{
	int	i;
	int	t;
	int	tmp;
	struct timeval current_time;

	i = 0;
	while(++i < 10000)
	{
		pthread_mutex_lock(&mutex[0]);
		pthread_mutex_lock(&mutex[1]);
		printf("%dms %d has taken a fork\n", current_time_(t0), *data);
		// printf("I am here:__die_time[%d]:%d\n", *data - 1, die_time[*data - 1]);
		// printf("before_die_time[0]:%d\n",die_time[0]);
		// printf("before_die_time[1]:%d\n",die_time[1]);
		// printf("before_die_time[2]:%d\n",die_time[2]);
		tmp = die_time[*data - 1];
		die_time[*data - 1] = time_to_die(tmp, current_time_(t0));
		// printf("die_time[0]:%d\n",die_time[0]);
		// printf("die_time[1]:%d\n",die_time[1]);
		// printf("die_time[2]:%d\n",die_time[2]);
		if (die_time[*data - 1] > 20)
		{
			printf("%dms %d died\n, -->>%d\n", current_time_(t0), *data, die_time[*data - 1]);
			exit (0);
		}
		printf("%dms :%d is eating\n\n", current_time_(t0), *data);
		usleep(1000);
		pthread_mutex_unlock(&mutex[0]);
		pthread_mutex_unlock(&mutex[1]);
		printf("%dms :%d is sleeping\n\n", current_time_(t0), *data);
		usleep(1000);
		printf("%dms :%d is thinking\n\n", current_time_(t0), *data);
		usleep(1000);
	}
	return (NULL);
}

int	main(void)
{
	t_data			*data;
	struct timeval current_time_;
	int			x = 0;
	//static	int	die_time[3];

	data = malloc(sizeof(t_data));
	data->id[0] = 1;
	data->id[1] = 2;
	data->id[2] = 3;
	pthread_mutex_init(&mutex[0], NULL);
	pthread_mutex_init(&mutex[1], NULL);
	gettimeofday(&current_time_, NULL);
	t0 = current_time_.tv_sec * 1000 + current_time_.tv_usec / 1000;
	if (pthread_create(&data->ph[0],NULL, (void *)&fun, (void *)(&data->id[0])) != 0)
		return (printf("thread can't create\n"), 1);
	if (pthread_create(&data->ph[1],NULL, (void *)&fun, (void *)(&data->id[1])) != 0)
		return (printf("thread can't create\n"), 1);
	if (pthread_create(&data->ph[2],NULL, (void *)&fun, (void *)(&data->id[2])) != 0)
		return (printf("thread can't create\n"), 1);
	if (pthread_join(data->ph[0], NULL) != 0)
		return (printf("failed to join\n"), 1);
	if (pthread_join(data->ph[1], NULL) != 0)
		return (printf("failed to join\n"), 1);
	if (pthread_join(data->ph[2], NULL) != 0)
		return (printf("failed to join\n"), 1);
	return (0);
}

// void	*fun1(int *data)
// {
// 	(*data)++;
// 	return (NULL);
// }


// int	main(void)
// {
// 	//int	*i = malloc(1);
// 	int	i;
// 	pthread_t	ph[2];

// 	i = 0;
// 	if (pthread_create(&ph[0],NULL, (void *)&fun1, (void *)&i) != 0)
// 		return (printf("thread can't create\n"), 1);
// 	if (pthread_create(&ph[1],NULL, (void *)&fun1,(void *)&i) != 0)
// 		return (printf("thread can't create\n"), 1);
// 	if (pthread_join(ph[0], NULL) != 0)
// 		return (printf("failed to join\n"), 1);
// 	if (pthread_join(ph[1], NULL) != 0)
// 		return (printf("failed to join\n"), 1);
// 	printf("i=%d\n", i);
// 	return (0);
// }
