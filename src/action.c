#include "philosophers.h"

void	*action(void *ptr)
{
	t_philos	*ph;

	ph = (t_philos *)ptr;
	ph->time_start = get_time();
	if (ph->id % 2 == 0)
		ft_usleep(ph->info->time_to_sleep);
	ph->last_eat = get_time();
	while (1)
	{
		if (ph->die)
			break ;
		eating(ph);
		sleeping(ph);
	}
	return (NULL);
}

void	*monitoring(void *ptr)
{
	t_info		*info;
	int	i;
	uint64_t	time;

	info = (t_info *)ptr;
	while (1)
	{
		i = -1;
		while (++i < info->count_philo)
		{
			time = (get_time() - info->philos[i].last_eat) - 10;
			if (time > info->time_to_die
				&& info->philos[i].status == THINK)
				{
					pthread_mutex_lock(&info->died);
					info->philos[i].die = 1;
					print_message(&info->philos[i], "is die", get_time());
					printf("%llu\n", time);
					return (NULL);
				}
		}
	}
	return (NULL);
}

int	philo_start(t_info *ptr)
{
	int			i;
	pthread_t	thread;

	i = -1;
	while (++i < ptr->count_philo)
	{
		pthread_create(&thread, NULL, action, &ptr->philos[i]);
		pthread_detach(thread);
	}

	return (0);
}

void	sleeping(t_philos *p)
{
	uint64_t	t;

	t = get_time();
	//pthread_mutex_lock(&p->info->died);
	print_message(p, "is sleeping", t);
	ft_usleep(p->info->time_to_sleep);
	print_message(p, "is thinking", get_time());
	p->status = THINK;
	//pthread_mutex_unlock(&p->info->died);
}

void	eating(t_philos *p)
{
	pthread_mutex_lock(&p->info->died);
	p->last_eat = get_time();
	pthread_mutex_lock(p->l_hand);
	print_message(p, "taken left fork", get_time());
	pthread_mutex_lock(p->r_hand);
	print_message(p, "taken right fork", get_time());
	pthread_mutex_lock(&p->eat);
	print_message(p, "is eating", get_time());
	ft_usleep(p->info->time_to_eat);
	p->last_eat = get_time();
	pthread_mutex_unlock(&p->eat);
	pthread_mutex_unlock(p->l_hand);
	pthread_mutex_unlock(p->r_hand);
	pthread_mutex_unlock(&p->info->died);
}