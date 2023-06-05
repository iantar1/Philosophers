/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:34:25 by iantar            #+#    #+#             */
/*   Updated: 2023/06/05 10:33:34 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	i = 0;
	j = 0;
	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (0);
	while (i < ft_strlen(s1))
	{
		ptr[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = 0;
	return (ptr);
}

static	char	*revstr(char *str)
{
	int		j;
	char	sw;
	int		i;

	j = 0;
	i = 0;
	while (str[i])
		i++;
	i--;
	while (j < i)
	{
		sw = str[j];
		str[j] = str[i];
		str[i] = sw;
		i--;
		j++;
	}
	return (str);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!ptr)
		return (0);
	while (i < ft_strlen(s1))
	{
		ptr[i] = ((char *)s1)[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_itoa(int n)
{
	char	str[13];
	int		i;
	int		check;
	long	new;

	if (n == 0)
		return (ft_strdup("0"));
	check = 1;
	i = 0;
	new = n;
	if (new < 0)
	{
		check *= -1;
		new *= -1;
	}
	while (new > 0)
	{
		str[i++] = (new % 10) + '0';
		new /= 10;
	}
	str[i] = '\0';
	if (check > 0)
		return (ft_strdup(revstr(str)));
	return (ft_strjoin("-", revstr(str)));
}
