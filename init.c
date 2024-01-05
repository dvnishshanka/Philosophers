#include "philo.h"

static void assign_forks(t_philo *philo)
{
	philo->first_fork->fork_id = (philo->id) - 1;
	philo->second_fork->fork_id = (philo->table->nbr_philo) % (philo->id);
}

static long philo_init(t_table *table)
{
	int i;
	t_philo *philos;

	i = -1;
	philos = table->philos;
	while (++i < table->nbr_philo)
	{
		philos[i].id = i + 1;
		philos[i].meals_counter = 0;
		philos[i].is_full = 0;
		philos[i].first_fork = 0;
		philos[i].second_fork = 0;
		// philos[i]->thread_id = ;
		philos[i].table = table;
		assign_forks(&philos[i]);
	}

	return (0);
}

long data_init(t_table *table)
{
	int	i;

	i = -1;
	table->is_end_simulation = 0;
	table->forks = (t_fork*)malloc(sizeof(t_fork) * table->nbr_philo);
	if (!table->forks)
		return error_exit("Malloc Failed");
	table->philos = (t_philo*)malloc(sizeof(t_philo) * table->nbr_philo);
	if (!table->philos)
	{
		free(table->forks);
		return error_exit("Malloc Failed");
	}
	while (++i < table->nbr_philo)
	{
		if (safe_mutex_handle(&table->forks[i].fork, MTX_INIT) == ERROR_CODE)
		{	
			free(table->forks);
			free(table->philos);
			return (ERROR_CODE);
		}
		table->forks[i].fork_id = i;
	}
	philo_init(table);

	return (0);
}