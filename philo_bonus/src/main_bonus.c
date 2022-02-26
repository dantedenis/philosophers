/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:33:44 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/25 22:33:44 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	check_args(char **str);
static void	kill_philo(t_info *info);
static void	free_alloc(t_info *info);

int	main(int argc, char **argv)
{
	t_info		info;
	uint64_t	start;

	if ((argc == 5 || argc == 6) && !check_args(argv + 1))
	{
		start = get_time();
		if (read_arg(argv, &info) || philo_start(&info))
		{
			write(2, "Error init\n", 11);
			free_alloc(&info);
			return (1);
		}
		kill_philo(&info);
		printf("%sEND SIMULATION!\nTIME : %llums\n", LINE, get_time() - start);
		return (0);
	}
	write(2, "Error args\n", 11);
	return (1);
}

static int	check_args(char **str)
{
	int	i;

	while (*str)
	{
		i = 0;
		while ((*str)[i])
		{
			if (!is_digit((*str)[i++]))
				return (1);
		}
		++str;
	}
	return (0);
}

static void	kill_philo(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->count_philo)
		kill(info->pids[i], SIGKILL);
	free_alloc(info);
}

static void	free_alloc(t_info *info)
{
	if (info->pids)
		free (info->pids);
}
