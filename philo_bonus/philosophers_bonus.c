/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:56:18 by iantar            #+#    #+#             */
/*   Updated: 2023/06/13 10:42:15 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	eat_check(t_data *data)
{
	struct timeval	current_time;

	while (1)
	{
		gettimeofday(&current_time, NULL);
		if ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
			- (data->current_time_die.tv_sec * 1000
				+ data->current_time_die.tv_usec / 1000)
			> data->die_time)
		{
			sem_wait(data->bin_sem);
			ft_printf("%dms %d died\n",
				current_time_(data), data->ph_id);
			(ft_free(data), exit(1));
		}
	}
}

void	routine(t_data *data, int index)
{
	pthread_t	th;

	data->ph_id = index;
	if (pthread_create(&th, NULL, (void *)&eat_check, data))
		exit(2);
	if (pthread_detach(th))
		exit(2);
	while (1)
	{
		forks_eating(data, index);
		sem_wait(data->bin_sem);
		ft_printf("%dms %d is sleeping\n", current_time_(data), index);
		sem_post(data->bin_sem);
		ft_msleep(data->sleep_time);
		sem_wait(data->bin_sem);
		ft_printf("%dms %d is thinking\n", current_time_(data), index);
		sem_post(data->bin_sem);
	}
}

t_data	*initialize(char **av, int ac)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->ph_num = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	data->pid = malloc((data->ph_num) * sizeof(pid_t));
	if (ac > 5)
		data->n_times_eat = ft_atoi(av[5]);
	return (data);
}

void	check_death(t_data *data)
{
	int	status;

	waitpid(-1, &status, 0);
	if (WEXITSTATUS(status))
	{
		kill_childes(data->pid, data->ph_num);
		(ft_free(data), exit(1));
	}
	while (--(data->ph_num))
		waitpid(-1, &status, 0);
	(ft_free(data), exit(0));
}

int	main(int ac, char *av[])
{
	t_data			*data;
	int				i;
	struct timeval	current_time;

	i = 0;
	if (check_valid_args(ac, av))
		return (1);
	data = initialize(av, ac);
	(sem_unlink("s_e_m"), sem_unlink("_bin_sem_"));
	data->sem = sem_open("s_e_m", O_CREAT | O_EXCL, 0777, data->ph_num);
	data->bin_sem = sem_open("_bin_sem_", O_CREAT | O_EXCL, 0777, 1);
	if (data->sem == SEM_FAILED || data->bin_sem == SEM_FAILED)
		return (ft_printf("sem_open failed\n"), 1);
	gettimeofday(&current_time, NULL);
	gettimeofday(&(data->current_time_die), NULL);
	data->t0 = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	while (i < data->ph_num)
	{
		data->pid[i] = fork();
		if (!data->pid[i])
			routine(data, i + 1);
		(usleep(30), i++);
	}
	check_death(data);
	return (0);
}
