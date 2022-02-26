/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:53:17 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/25 22:53:17 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	init_sem(t_info *i)
{
	sem_unlink("fork");
	sem_unlink("message");
	sem_unlink("stop");
	sem_unlink("eat");
	i->fork = sem_open("fork", O_CREAT | O_EXCL, S_IRWXU, i->count_philo);
	i->message = sem_open("message", O_CREAT | O_EXCL, S_IRWXU, 1);
	i->stop = sem_open("stop", O_CREAT | O_EXCL, S_IRWXU, 0);
	if (i->times_eat != -1)
		i->eat = sem_open("eat", O_CREAT | O_EXCL, S_IRWXU, 0);
	return (0);
}

static int	init_monitor_eat(t_info *info)
{
	pthread_t	eat_m;

	if (info->times_eat != -1)
	{
		if (pthread_create(&eat_m, NULL, &eating_checker, info))
		{
			printf("Error pthread");
			return (1);
		}
		pthread_detach(eat_m);
	}
	return (0);
}

int	read_arg(char **str, t_info *info)
{
	memset(info, 0, sizeof(t_info));
	info->count_philo = ft_atoi(str[1]);
	info->time_to_die = ft_atoi(str[2]);
	info->time_to_eat = ft_atoi(str[3]);
	info->time_to_sleep = ft_atoi(str[4]);
	if (str[5])
	{
		info->times_eat = ft_atoi(str[5]);
		if (info->times_eat < 1)
			return (1);
	}
	else
		info->times_eat = -1;
	info->pids = (pid_t *)malloc(sizeof(pid_t) * info->count_philo);
	if (!info->pids)
		return (1);
	memset(info->pids, 0, sizeof(pid_t) * info->count_philo);
	init_sem(info);
	init_monitor_eat(info);
	return (0);
}
