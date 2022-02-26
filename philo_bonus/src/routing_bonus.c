/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:54:33 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/25 22:54:33 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	sleeping(t_info *info)
{
	uint64_t	time;

	time = get_time();
	print_message(info, "is sleeping", time, 1);
	ft_usleep(info->time_to_sleep);
	print_message(info, "is thinking", get_time(), 1);
}

void	eating(t_info *info)
{
	uint64_t	time;

	time = get_time();
	info->philo.last_eat = time;
	print_message(info, "is eating", time, 1);
	ft_usleep(info->time_to_eat);
	if (info->times_eat != -1)
		++info->philo.count_eat;
	if (info->times_eat == info->philo.count_eat)
		sem_post(info->eat);
}

void	take_forks(t_info *info)
{
	sem_wait(info->fork);
	print_message(info, "taken left fork", get_time(), 1);
	sem_wait(info->fork);
	print_message(info, "taken right fork", get_time(), 1);
}

void	put_forks(t_info *info)
{
	sem_post(info->fork);
	sem_post(info->fork);
}
