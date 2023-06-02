/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:33:47 by iantar            #+#    #+#             */
/*   Updated: 2023/06/02 10:54:32 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct	s_data
{
	int				ph_num;
	size_t				die_time;
	int				eat_time;
	int				sleep_time;
	size_t				t0;
	int				micro_t0;
	int				ph_id;
	int				*n_times_eat;
	size_t			*count_eat_time;
	pthread_t		*p_th;
	pthread_mutex_t	*mutex;
}t_data;


// typedef	struct s_data
// {
// 	int	t0;
// 	int	ph;
// }			t_data;

int		ft_isdigit(int c);
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
int		check_valid_args(int ac, char **av);
int		check_arg(char *arg);
void	ft_msleep(size_t tm);
void	ft_usleep(size_t time);
size_t	micro_current_time_(size_t micro_t0);
void	ft_bzero(void *str, size_t n);
int		min_max(int token, int max);
void	ft_usleep2(int tm);

#endif