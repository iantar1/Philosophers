/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:33:47 by iantar            #+#    #+#             */
/*   Updated: 2023/05/03 17:51:06 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef	struct s_data
{
	int	ph_num;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	n_times_eat;
	int	t0;
	int	ph_id;
	pthread_mutex_t mutex[2];
}t_data;


// typedef	struct s_data
// {
// 	int	t0;
// 	int	ph;
// }			t_data;

int		ft_isdigit(int c);
size_t	ft_strlen(const char *str);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

#endif