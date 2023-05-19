/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:07:03 by iantar            #+#    #+#             */
/*   Updated: 2023/05/18 16:47:26 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
 
int	check_arg(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if ((arg[i] == '+' || arg[i] == '-') && !i)
			continue ;
		if (ft_isdigit(arg[i]))
			continue ;
		return (1);
	}
	return (0);
}

int	check_valid_args(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (1);
	if (ft_atoi(av[1]) <= 0)
		return (1);
	i = 0;
	while (++i < ac)
	{
		if (check_arg(av[i]) || ft_atoi(av[i]) < 0)
			return (1);
	}
	return (0);
}