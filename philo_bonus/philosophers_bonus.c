/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:56:18 by iantar            #+#    #+#             */
/*   Updated: 2023/06/08 18:27:27 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers_bonus.h"

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
	size_t	to_rtn;

	if (!one_time)
	{
		gettimeofday(&current_time, NULL);
		data->t0 = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		one_time++;
	}
	gettimeofday(&current_time, NULL);
	t = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	to_rtn = t - data->t0;
	return (to_rtn);
}

// int	check_for_n_eat_times(int *n_times, int num_ph, int need_stop)
// {

// }

// int	is_died(struct timeval current_time_die, )
// {
// }

void	forks_eating(t_data *data, int index)
{
	sem_wait(data->sem);
	sem_wait(data->bin_sem);//////
	printf("%zums %d has taken first fork\n", current_time_(data), index);
	sem_post(data->bin_sem);/////
	sem_wait(data->sem);
	sem_wait(data->bin_sem);
	printf("%zums %d has taken second fork\n", current_time_(data), index);
	sem_post(data->bin_sem);
	sem_wait(data->bin_sem);
	printf("%zums %d is eating\n\n", current_time_(data), index);
	sem_post(data->bin_sem);
	ft_msleep(data->eat_time);
	gettimeofday(&(data->current_time_die), NULL);
	sem_post(data->sem);
	sem_post(data->sem);
}

// void	kill_childes(pid_t *pid, int ph_num, int ph_id)
// {
// 	int	i;

// 	i = 0;
// 	while (i < ph_num)
// 	{
// 		if (i != ph_id - 1)
// 		{
// 			printf("%d\n", ph_id - 1);
// 			kill(pid[i], SIGKILL);
// 		}
// 		i++;
// 	}
// }

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

void	eat_check(t_data *data)
{
	//(void)data;
	struct timeval	current_time;
	long	last_eat;
	long	now;
	while (1)
	{
		last_eat = data->current_time_die.tv_sec * 1000 + data->current_time_die.tv_usec / 1000;
		gettimeofday(&current_time, NULL);
		now = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		//printf("last_eat:%zu, now:%zu\n", last_eat, now);
		
		 if (now - last_eat > data->die_time)//data race
		 {
			exit(1);
			//kill_childes(data->pid, data->ph_num, data->ph_id);
		 }
	}
}

void	routine(t_data *data, int index)
{
	int			i;
	pthread_t	th;

	i = 0;
	data->last_eat = 0;
	data->ph_id = index;
	usleep(1000000);
	//data->t0 = current_time_(data);
	if (pthread_create(&th, NULL, (void *)&eat_check, data))
		exit(2);
	while (1)
	{
		forks_eating(data, index);
		sem_wait(data->bin_sem);
		printf("%zu ms %d is sleeping\n", current_time_(data), index);
		sem_post(data->bin_sem);
		ft_msleep(data->sleep_time);
		sem_wait(data->bin_sem);
		printf("%zu ms %d is thinking\n", current_time_(data), index);
		sem_post(data->bin_sem);
	}
}

// void	print_data(size_t *data, int num_ph)
// {
// 	int	i;

// 	i = 0;
// 	while (i < num_ph)
// 	{
// 		printf("data[%d]:%zu\n", i, data[i]);
// 		i++;
// 	}
// }

t_data	*initialize(char **av)
{
	t_data	*data;
	struct timeval	current_time;

	data = malloc(sizeof(t_data));
	gettimeofday(&current_time, NULL);
	data->t0 = data->current_time_die.tv_sec * 1000 + data->current_time_die.tv_usec / 1000;
	data->ph_num = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	data->pid = malloc((data->ph_num) * sizeof(pid_t));
	data->count_eat_time = malloc((data->ph_num) * sizeof(size_t));
	ft_bzero(data->count_eat_time, (data->ph_num) * sizeof(size_t));
	data->n_times_eat = malloc((data->ph_num) * sizeof(int));
	ft_bzero(data->n_times_eat, (data->ph_num) * sizeof(int));
	return (data);
}


size_t	check_death(t_data *data)
{
	int	i;
	int	status;
	//size_t	time_die;

	i = 0;
	status = 0;
	while (1)
	{
		if (i == data->ph_num)
			i = 0;
		waitpid(-1, &status, 0);
		printf("status:%d\n", status);
		printf("kjk\n");
		if (status)
		{
			//time_die = current_time_(data);
			sem_wait(data->bin_sem);
			kill_childes(data->pid, data->ph_num);
			(printf("\e[0;31m""%zums %d died\n",current_time_(data), i + 1), exit(1));
			//return (i + 1);
		}
	}
	return (0);
}

// int	create_process(t_data *data, int i)
// {
// 	pthread_mutex_lock(&data->mutex[data->ph_num]);
// 	data->ph_id = i + 1;
// 	if (current_time_(data) - data->count_eat_time[i] >= data->die_time)
// 	{
// 		pthread_mutex_lock(&data->mutex[data->ph_num + 3]);
// 		return (printf("\e[0;31m""%zums %d died\n",current_time_(data), i + 1), 1);
// 	}
// 	return (0);
// }

//The wait operation decrements the value of the semaphore
//the signal (post) operation increments the value of the semaphore.
int	main(int ac, char *av[])
{
	//pid_t	*pid;
	//size_t	die_time;
	t_data	*data;
	int		i;
	//int		ph_die;

	i = 0;
	if (check_valid_args(ac, av))
		return (1);
	data = initialize(av);
	sem_unlink("s_e_m");
	sem_unlink("_bin_sem_");
	data->sem = sem_open("s_e_m", O_CREAT | O_EXCL, 0777, data->ph_num);
	data->bin_sem = sem_open("_bin_sem_", O_CREAT | O_EXCL, 0777, 1);
	if (data->sem == SEM_FAILED || data->bin_sem == SEM_FAILED)
		return (printf("sem_open failed\n"), 1);
	//pid = malloc(data->ph_num * sizeof(pid_t));
	while (i < data->ph_num)
	{
		data->pid[i] = fork();
		if (!data->pid[i])
			routine(data, i + 1);
		else
			i++;
	}
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	check_death(data);
	// if (ph_die)
	// 	(printf("\e[0;31m""%zums %d died\n",current_time_(data), ph_die), exit(1));
	//sem_close(sem_);
	return (0);
}