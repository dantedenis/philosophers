/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:45:03 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/25 22:45:03 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <string.h>

# define LINE "\n-------------------------------------------------\n"
# define IS_DIE "\033[31mis die\033[0m"
# define IS_LEAVE "\033[32mis leaving\033[0m"

typedef struct s_info	t_info;
typedef pthread_mutex_t	t_pth_mut;

typedef struct s_philos
{
	int			id;
	int			count_eat;
	uint64_t	time_start;
	uint64_t	last_eat;
	t_pth_mut	*l_hand;
	t_pth_mut	*r_hand;
	t_pth_mut	message;
	t_pth_mut	eat;
	t_info		*info;
}	t_philos;

typedef struct s_info
{
	int			count_philo;
	uint64_t	time_to_die;
	int			time_to_eat;
	uint64_t	time_to_sleep;
	int			times_eat;
	t_pth_mut	*forks;
	t_philos	*philos;
}	t_info;

/*
**	UTILS
*/

int			is_digit(int num);
int			ft_atoi(const char *str);
uint64_t	get_time(void);
void		ft_usleep(uint64_t time);
void		print_message(t_philos *p, char *msg, uint64_t time, int flag);

/*
**	INIT
*/

void		read_arg(char **str, t_info *i);
void		ft_destroy_mutex_error(t_pth_mut *m_ptr, int count);
int			init_forks(t_info *ptr);
int			init(t_info *ptr);
void		free_all(t_info *info);

/*
**	ACTION
*/

int			philo_start(t_info *ptr);
void		*action(void *ptr);
void		*monitoring(void *ptr);
void		sleeping(t_philos *p);
void		eating(t_philos *p);
void		take_forks(t_philos *ph);
void		put_forks(t_philos *ph);

#endif