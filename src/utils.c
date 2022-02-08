#include "philosophers.h"

int	is_digit(int num)
{
	return (num >= '0' && num <= '9');
}

int	ft_atoi(const char *str)
{
	uint64_t	result;
	int			neg;

	result = 0;
	neg = 1;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			neg = -1;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str++ - '0';
		if (result > (uint64_t)INT_MAX && neg == 1)
			return (-1);
		if (result > ((uint64_t)INT_MAX + 1L) && neg == -1)
			return (0);
	}
	return (result * neg);
}

uint64_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return(t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ft_usleep(uint64_t time)
{
	uint64_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(time / 10);
}

void	print_message(t_philos *p, char *msg, uint64_t time)
{
	pthread_mutex_lock(&p->message);
	printf("[%10llu ms] ID: %d %s\n", (time - p->time_start), p->id, msg);
	pthread_mutex_unlock(&p->message);
}
