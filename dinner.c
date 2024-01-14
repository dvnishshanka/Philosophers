#include "philo.h"

// Philosopher is dead or All philosophers are full.
static	void monitor_end_simulation(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->table->nbr_philo && philo->table->philos[i].is_full == 1)
	{
		if (i == (philo->table->nbr_philo - 1))
			philo->table->is_end_simulation = 1;
		i++;
	}
}

static void	eat(t_philo *philo, struct	timeval *tv)
{
	safe_mutex_handle(&philo->first_fork->fork, MTX_LOCK);
	write_state(TOOK_FIRST_FORK, philo->table, philo);
	safe_mutex_handle(&philo->second_fork->fork, MTX_LOCK);
	write_state(TOOK_SECOND_FORK, philo->table, philo);
	write_state(EAT, philo->table, philo);
	philo->last_meal_time = get_timestamp_in_ms(tv);
	usleep((philo->table->time_to_eat) * 1000);
	philo->last_meal_time = get_timestamp_in_ms(tv);
	philo->meals_counter ++;
	if (philo->table->nbr_limit_meals == philo->meals_counter)
		set_int(&philo->table->mtx_table, &philo->is_full, 1);
	safe_mutex_handle(&philo->first_fork->fork, MTX_UNLOCK);
	// Not required by subject
	// printf("%ld %d has put down the 1st fork\n",get_timestamp_in_ms(tv), philo->id);
	safe_mutex_handle(&philo->second_fork->fork, MTX_UNLOCK);
		// Not required by subject
	// printf("%ld %d has put down the 2nd fork\n", get_timestamp_in_ms(tv), philo->id);
}

static void	*dinner_simulation(void *arg)
{
	t_philo	*philo;
	struct	timeval	tv;

	philo = (t_philo *)arg;
	wait_till_threads_ready(philo->table);
	set_long(&philo->mtx_philo, &philo->last_meal_time, get_timestamp_in_ms(&tv));
	while (simulation_finished(philo->table) == 0 && philo->is_full == 0)
	{
		eat(philo, &tv);
		write_state(SLEEP, philo->table, philo);
		usleep((philo->table->time_to_sleep) * 1000);
		write_state(THINK, philo->table, philo);
		monitor_end_simulation(philo);
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
	struct	timeval	time;

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
	table->start_simulation = get_timestamp_in_ms(&time);
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