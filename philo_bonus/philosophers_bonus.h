/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:33:47 by iantar            #+#    #+#             */
/*   Updated: 2023/06/12 21:51:20 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <stdarg.h>

typedef struct s_data
{
	size_t			t0;
	int				die_time;
	int				ph_num;
	int				eat_time;
	int				sleep_time;
	int				ac;
	int				ph_id;
	int				n_times_eat;
	pid_t			*pid;
	sem_t			*sem;
	sem_t			*bin_sem;
	struct timeval	current_time_die;
}	t_data;

void	kill_childes(pid_t *pid, int ph_num);
void	forks_eating(t_data *data, int index);
int		current_time_(t_data *data);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
int		check_valid_args(int ac, char **av);
int		check_arg(char *arg);
void	ft_msleep(size_t tm);
void	ft_bzero(void *str, size_t n);
int		min_max(int token, int max);
void	ft_usleep2(int tm);
char	*ft_itoa(int n);
void	ft_free(t_data *data);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_printf(const char *str, ...);
void	ft_putnbr(long nbr);
int		ft_putstr(char *str);
int		ft_putchar(char c);

#endif