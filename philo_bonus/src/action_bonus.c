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

#include "philosophers_bonus.h"

void	*action(void *ptr)
{
	t_info	*info;

	info = (t_info *)ptr;
	info->philo.time_start = get_time();
	while (1)
	{
		take_forks(info);
		eating(info);
		put_forks(info);
		if (info->philo.count_eat == info->times_eat)
		{
			print_message(info, IS_LEAVE, get_time(), 1);
			exit (0);
		}
		sleeping(info);
	}
	return (NULL);
}

void	*eating_checker(void *ptr)
{
	t_info	*info;
	int		i;

	info = (t_info *)ptr;
	i = -1;
	sem_wait(info->message);
	while (++i < info->count_philo)
	{
		sem_post(info->message);
		sem_wait(info->eat);
		sem_wait(info->message);
	}
	sem_post(info->stop);
	return (NULL);
}

void	*death_checker(void *ptr)
{
	t_info		*info;
	uint64_t	time;

	info = (t_info *) ptr;
	while (info->count_philo)
	{
		time = get_time();
		if (time - info->philo.last_eat > info->time_to_die)
		{
			print_message(info, IS_DIE, get_time(), 0);
			sem_post(info->stop);
			return (NULL);
		}
	}
	return (NULL);
}

void	init_philo(t_info *info)
{
	info->philo.last_eat = get_time();
	if (pthread_create(&info->monitor, NULL, &death_checker, info))
	{
		write(2, "Error pthread\n", 14);
		sem_post(info->stop);
	}
	pthread_detach(info->monitor);
}

int	philo_start(t_info *info)
{
	int			i;

	i = -1;
	while (++i < info->count_philo)
	{
		info->philo.id = i + 1;
		info->pids[i] = fork();
		if (info->pids[i] == -1)
		{
			while (--i >= 0)
				kill(info->pids[i], SIGKILL);
			return (1);
		}
		else if (info->pids[i] == 0)
		{
			init_philo(info);
			action(info);
		}
	}
	sem_wait(info->stop);
	return (0);
}
