/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 23:13:10 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/25 23:13:10 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*action(void *ptr)
{
	t_philos	*ph;

	ph = (t_philos *)ptr;
	if (ph->id % 2 == 0)
		ft_usleep(ph->info->time_to_sleep);
	while (ph->count_eat != ph->info->times_eat)
	{
		take_forks(ph);
		eating(ph);
		if (ph->count_eat == ph->info->times_eat)
		{
			print_message(ph, IS_LEAVE, get_time(), 0);
			--ph->info->count_philo;
		}
		put_forks(ph);
		sleeping(ph);
	}
	return (NULL);
}

void	*monitoring(void *ptr)
{
	t_info		*info;
	int			i;
	uint64_t	time;

	info = (t_info *)ptr;
	while (info->count_philo)
	{
		i = -1;
		while (++i < info->count_philo)
		{
			time = (get_time() - info->philos[i].last_eat);
			if (time > info->time_to_die)
			{
				print_message(&info->philos[i], IS_DIE, get_time(), 0);
				return (NULL);
			}
		}
	}
	return (NULL);
}

int	philo_start(t_info *info)
{
	int			i;
	pthread_t	thread;

	i = -1;
	while (++i < info->count_philo)
	{
		if (pthread_create(&thread, NULL, action, &info->philos[i]))
		{
			write(2, "Error start threads\n", 20);
			free_all(info);
			return (1);
		}
		if (pthread_detach(thread))
		{
			write(2, "Error detach\n", 13);
			free_all(info);
			return (1);
		}
	}
	return (0);
}
