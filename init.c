#include "philo.h"

long data_init(t_table *table)
{
	table->is_end_simulation = 0;
	table->forks = (*t_fork)malloc(sizeof(*t_fork) * table->nbr_philo);
	if (!table->forks)
		return error_exit("Malloc Failed");
	table->philos = (*t_philo)malloc(sizeof(*t_philo) * table->nbr_philo);
	if (!table->philos)
	{
		free(table->forks)
		return error_exit("Malloc Failed");
	}

	return (0);
}