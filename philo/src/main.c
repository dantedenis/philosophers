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

#include "philosophers.h"

static int	check_args(char **str);

int	main(int argc, char **argv)
{
	t_info		info;
	pthread_t	monitor;
	uint64_t	start;

	if ((argc == 5 || argc == 6) && !check_args(argv + 1))
	{
		start = get_time();
		read_arg(argv, &info);
		if (init(&info) || philo_start(&info)
			|| pthread_create(&monitor, NULL, monitoring, &info))
			return (1);
		if (pthread_join(monitor, NULL))
			write(2, "Error pthread join\n", 19);
		free_all(&info);
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
