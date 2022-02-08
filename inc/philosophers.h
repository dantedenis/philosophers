#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef unsigned long long uint64_t;
typedef struct	s_info t_info;

typedef enum
{
	TAKE,
	EAT,
	SLEEP,
	THINK,
	DIE,
	NOTHING,
} STATUS_PHILO;

typedef struct
{
	int				id;
	int				count_eat;
	int				status;
	int				die;
	uint64_t		time_start;
	uint64_t		last_eat;
	pthread_mutex_t	*l_hand;
	pthread_mutex_t	*r_hand;
	pthread_mutex_t	message;
	pthread_mutex_t	eat;
	t_info			*info;
} t_philos;

typedef struct s_info
{
	int				count_philo;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		times_eat;
	pthread_mutex_t	died;
	pthread_mutex_t	*forks;
	t_philos		*philos;
} t_info;

/*
**	UTILS
*/

int			is_digit(int num);
int			ft_atoi(const char *str);
uint64_t	get_time();
void		ft_usleep(uint64_t time);
void		print_message(t_philos *p, char *msg, uint64_t time);

/*
**	INIT
*/

int		check_args(char **str);
void	read_arg(char **str, t_info *i);
void	ft_destroy_mutex_error(pthread_mutex_t *m_ptr, int count);
int		init_forks(t_info *ptr);
int		init(t_info *ptr);

/*
**	ACTION
*/

int		philo_start(t_info *ptr);
void	*action(void *ptr);
void	*monitoring(void *ptr);
void	sleeping(t_philos *p);
void	eating(t_philos *p);

#endif