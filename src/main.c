#include "philosophers.h"

int main(int argc, char **argv)
{
	t_info		info;
	pthread_t	monitor;

	if ((argc == 5 || argc == 6) && !check_args(argv + 1))
	{
		read_arg(argv, &info);
		init(&info);
		philo_start(&info);
		pthread_create(&monitor, NULL, monitoring, &info);
		pthread_join(monitor, NULL);
		return (0);
	}
	write(2, "Error args\n", 11);
	return (1);
}
