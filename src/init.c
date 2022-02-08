#include "philosophers.h"

int	check_args(char **str)
{
	int	i;

	while(*str)
	{
		i = 0;
		while((*str)[i])
		{
			if (!is_digit((*str)[i++]))
				return (1);
		}
		++str;
	}
	return (0);
}

void	read_arg(char **str, t_info *i)
{
	i->count_philo = ft_atoi(str[1]);
	if (i->count_philo < 2)
	{
		write(2, "Not enough philosophers\n", 24);
		exit(1);
	}
	i->time_to_die = ft_atoi(str[2]);
	i->time_to_eat = ft_atoi(str[3]);
	i->time_to_sleep = ft_atoi(str[4]);
	if (str[5])
		i->times_eat = ft_atoi(str[5]);
}

void	ft_destroy_mutex_error(pthread_mutex_t *m_ptr, int count)
{
	while (--count >= 0)
		pthread_mutex_destroy(&m_ptr[count]);
}

int	init_forks(t_info *ptr)
{
	int	i;

	ptr->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ptr->count_philo);
	if (!ptr->forks)
		return (1);
	i = -1;
	while (++i < ptr->count_philo)
		if(pthread_mutex_init(&ptr->forks[i], NULL))
		{
			write(2, "Error mutex init\n", 17);
			ft_destroy_mutex_error(ptr->forks, i);
			return (1);
		};
	return (0);
}

int	init(t_info *ptr)
{
	int	i;

	ptr->philos = (t_philos *) malloc(sizeof(t_philos) * ptr->count_philo);
	if (!ptr->philos || init_forks(ptr))
		return (1);
	i = -1;
	pthread_mutex_init(&ptr->died, NULL);
	while (++i < ptr->count_philo)
	{
		ptr->philos[i].info = ptr;
		ptr->philos[i].id = i + 1;
		ptr->philos[i].status = NOTHING;
		ptr->philos[i].die = 0;
		ptr->philos[i].l_hand = &ptr->forks[i];
		ptr->philos[i].r_hand = &ptr->forks[(i + 1) % ptr->count_philo];
		pthread_mutex_init(&ptr->philos[i].eat, NULL);
		pthread_mutex_init(&ptr->philos[i].message, NULL);
	}
	return 0;
}