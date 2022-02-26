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

#include "philosophers.h"

void	free_all(t_info *info)
{
	int	i;

	if (info)
	{
		if (info->forks)
			ft_destroy_mutex_error(info->forks, info->count_philo);
		i = -1;
		while (++i < info->count_philo)
		{
			pthread_mutex_destroy(&info->philos[i].eat);
			pthread_mutex_destroy(&info->philos[i].message);
		}
		free(info->philos);
		info->philos = NULL;
	}
}

void	read_arg(char **str, t_info *i)
{
	memset(i, 0, sizeof(t_info));
	i->count_philo = ft_atoi(str[1]);
	i->time_to_die = ft_atoi(str[2]);
	i->time_to_eat = ft_atoi(str[3]);
	i->time_to_sleep = ft_atoi(str[4]);
	if (str[5])
		i->times_eat = ft_atoi(str[5]);
	else
		i->times_eat = -1;
}

void	ft_destroy_mutex_error(t_pth_mut *m_ptr, int count)
{
	while (--count >= 0)
		pthread_mutex_destroy(&m_ptr[count]);
	free(m_ptr);
	m_ptr = NULL;
}

int	init_forks(t_info *info)
{
	int	i;

	info->forks = (t_pth_mut *)malloc(sizeof(t_pth_mut) * info->count_philo);
	if (!info->forks)
		return (1);
	i = -1;
	while (++i < info->count_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
		{
			write(2, "Error mutex init\n", 17);
			ft_destroy_mutex_error(info->forks, i);
			return (1);
		}
	}
	return (0);
}

int	init(t_info *info)
{
	int			i;
	uint64_t	time;

	info->philos = (t_philos *) malloc(sizeof(t_philos) * info->count_philo);
	if (!info->philos || init_forks(info))
		return (1);
	i = -1;
	while (++i < info->count_philo)
	{
		time = get_time();
		info->philos[i].info = info;
		info->philos[i].id = i + 1;
		info->philos[i].count_eat = 0;
		info->philos[i].last_eat = time;
		info->philos[i].time_start = time;
		info->philos[i].l_hand = &info->forks[i];
		info->philos[i].r_hand = &info->forks[(i + 1) % info->count_philo];
		if (pthread_mutex_init(&info->philos[i].eat, NULL)
			|| pthread_mutex_init(&info->philos[i].message, NULL))
		{
			free_all(info);
			return (1);
		}
	}
	return (0);
}
