/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:33:40 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/25 22:33:40 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
		if (result > INT_MAX && neg == 1)
			return (-1);
		if (result > (INT_MAX + 1L) && neg == -1)
			return (0);
	}
	return (result * neg);
}

uint64_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ft_usleep(uint64_t time)
{
	uint64_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(10);
}

void	print_message(t_info *info, char *msg, uint64_t time, int flag)
{
	sem_wait(info->message);
	printf("\033[34m[%10llu ms]\033[0m ID: %4d %s\n",
		(time - info->philo.time_start), info->philo.id, msg);
	if (flag)
		sem_post(info->message);
}
