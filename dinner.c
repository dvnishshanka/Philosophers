#include "philo.h"

static void	think(t_philo *philo)
{
	write_state(THINK, philo->table, philo);
}

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, MTX_LOCK);
	write_state(TOOK_FIRST_FORK, philo->table, philo);
	safe_mutex_handle(&philo->second_fork->fork, MTX_LOCK);
	write_state(TOOK_SECOND_FORK, philo->table, philo);
	set_long(&philo->mtx_philo, &philo->last_meal_time, get_timestamp(MILLISEC));
	write_state(EAT, philo->table, philo);
	sleep_with_interruption(philo->table->time_to_eat, philo->table);
	philo->meals_counter ++;
	if (get_int(&philo->table->mtx_table, &philo->table->nbr_limit_meals) == philo->meals_counter)
		set_int(&philo->table->mtx_table, &philo->is_full, 1);
	safe_mutex_handle(&philo->first_fork->fork, MTX_UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, MTX_UNLOCK);
}

static void	*dinner_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_till_threads_ready(philo->table);
	set_long(&philo->mtx_philo, &philo->last_meal_time, get_timestamp(MILLISEC));
	while (simulation_finished(philo->table) == 0 && philo->is_full == 0)
	{
		eat(philo);
		write_state(SLEEP, philo->table, philo);
		sleep_with_interruption(philo->table->time_to_sleep, philo->table);
		think(philo);
	}
	return (NULL);
}

/*
The timeval structure is declared as below in "sys/time.h"
struct    timeval  {
  time_t        tv_sec ;   //used for seconds
  suseconds_t       tv_usec ;   //used for microseconds
}
*/
int	dinner(t_table *table)
{
	int		i;

	i = -1;
	if (table->nbr_philo == 1)
	{}
	// TODO
	else
	{
		while (++i < table->nbr_philo)
		{
			if (safe_pthread_handle(&(table->philos[i].thread_id), dinner_simulation, (void *)&table->philos[i], THREAD_CREATE) == ERROR_CODE)
				return (ERROR_CODE);
		}
	}
	safe_pthread_handle(&table->monitor, monitor_philos, (void *)table, THREAD_CREATE);
	table->start_simulation = get_timestamp(MILLISEC);
	set_int(&table->mtx_table, &table->all_threads_ready, 1);
	i = -1;
	while (++i < table->nbr_philo)
	{
		if (safe_pthread_handle(&(table->philos[i].thread_id), NULL, NULL, THREAD_JOIN) == ERROR_CODE)
			return (ERROR_CODE);
	}
	set_int(&table->mtx_table, &table->is_end_simulation, 1);
	return (0);
}