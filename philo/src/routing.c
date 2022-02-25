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

#include "philosophers.h"

void	sleeping(t_philos *ph)
{
	uint64_t	time;

	time = get_time();
	print_message(ph, "is sleeping", time, 1);
	ft_usleep(ph->info->time_to_sleep);
	print_message(ph, "is thinking", get_time(), 1);
}

void	eating(t_philos *ph)
{
	uint64_t	time;

	pthread_mutex_lock(&ph->eat);
	time = get_time();
	ph->last_eat = time;
	print_message(ph, "is eating", time, 1);
	ft_usleep(ph->info->time_to_eat);
	if (ph->info->times_eat != -1)
		++ph->count_eat;
	pthread_mutex_unlock(&ph->eat);
}

void	take_forks(t_philos *ph)
{
	pthread_mutex_lock(ph->l_hand);
	print_message(ph, "taken left fork", get_time(), 1);
	pthread_mutex_lock(ph->r_hand);
	print_message(ph, "taken right fork", get_time(), 1);
}

void	put_forks(t_philos *ph)
{
	pthread_mutex_unlock(ph->l_hand);
	pthread_mutex_unlock(ph->r_hand);
}
