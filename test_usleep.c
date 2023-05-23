# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

void	ft_usleep(long time)
{
	struct timeval	current_time;
	long	start;
	long	end;

	gettimeofday(&current_time, NULL);
	start = current_time.tv_sec / 1000000 + current_time.tv_usec;
	end = start;
	while (end - start <= time)
	{
		gettimeofday(&current_time, NULL);
		end = current_time.tv_sec / 1000000 + current_time.tv_usec;
	}
}

void	ft_msleep2(size_t time)
{
	int	i;

	i = -1;
	while (++i < time * 100)
		usleep(10);
}

int	main(void)
{
	//ft_msleep2(1000);
	usleep(1000000);
	return (0);
}