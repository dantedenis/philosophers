/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 00:51:40 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/26 00:51:40 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <string.h>

# define LINE "\n-------------------------------------------------\n"
# define IS_DIE "\033[31mis die\033[0m"
# define IS_LEAVE "\033[32mis leaving\033[0m"

typedef struct s_info	t_info;

typedef struct s_philos
{
	int			id;
	int			count_eat;
	uint64_t	time_start;
	uint64_t	last_eat;
	t_info		*info;
	pthread_t	monitor;
	sem_t		*actions;
}	t_philos;

typedef struct s_info
{
	pthread_t	monitor;
	int			count_philo;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	int			times_eat;
	pid_t		*pids;
	sem_t		*message;
	sem_t		*fork;
	sem_t		*stop;
	sem_t		*eat;
	t_philos	philo;
}	t_info;

/*
**	UTILS
*/

int			is_digit(int num);
int			ft_atoi(const char *str);
uint64_t	get_time(void);
void		ft_usleep(uint64_t time);
void		print_message(t_info *info, char *msg, uint64_t time, int flag);

/*
**	INIT
*/

int			read_arg(char **str, t_info *i);
void		init_philo(t_info *info);
void		*eating_checker(void *arg);
int			philo_start(t_info *ptr);

/*
**	ACTION
*/

void		*action(void *ptr);
void		*death_checker(void *ptr);
void		eating(t_info *info);
void		take_forks(t_info *info);
void		put_forks(t_info *info);
void		sleeping(t_info *info);

#endif