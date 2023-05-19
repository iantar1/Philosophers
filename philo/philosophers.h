/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:33:47 by iantar            #+#    #+#             */
/*   Updated: 2023/05/19 11:04:22 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct	s_data
{
	int				ph_num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				t0;
	int				ph_id;
	int				*n_times_eat;
	int				*count_eat_time;
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
void	upgrade_usleep(int tm, int start_t0);

#endif