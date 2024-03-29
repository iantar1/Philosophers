/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:33:47 by iantar            #+#    #+#             */
/*   Updated: 2023/06/12 21:50:27 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdarg.h>

typedef struct s_data
{
	int				ph_num;
	size_t			die_time;
	int				eat_time;
	int				sleep_time;
	size_t			t0;
	int				micro_t0;
	int				ph_id;
	int				*n_times_eat;
	size_t			*count_eat_time;
	pthread_t		*p_th;
	pthread_mutex_t	*mutex;
}t_data;

void	*routine(t_data *data);
void	forks_eating(t_data *data, int id_);
int		check_for_n_eat_times(int *n_times, int num_ph, int need_stop);
int		current_time_(t_data *data);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
int		check_valid_args(int ac, char **av);
int		check_arg(char *arg);
void	ft_msleep(size_t tm);
void	ft_bzero(void *str, size_t n);
void	ft_usleep2(int tm);
int		ft_printf(const char *str, ...);
int		ft_putchar(char c);
int		ft_putstr(char *str);
void	ft_putnbr(long nbr);
void	ft_free(t_data *data);

#endif