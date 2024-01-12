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

static void	*dinner_simulation(void *arg)
{
	t_philo	*philo;
	struct	timeval	tv;

	philo = (t_philo *)arg;
	while (philo->table->is_end_simulation == 0 && philo->is_full == 0)
	{
		safe_mutex_handle(&philo->first_fork->fork, MTX_LOCK);
		printf("%lld %d has taken a first fork\n", get_timestamp_in_ms(&tv), philo->id);
		safe_mutex_handle(&philo->second_fork->fork, MTX_LOCK);
		printf("%lld %d has taken a second fork\n", get_timestamp_in_ms(&tv), philo->id);
		printf("%lld %d is eating\n", get_timestamp_in_ms(&tv), philo->id);
		usleep((philo->table->time_to_eat) * 1000);
		philo->last_meal_time = get_timestamp_in_ms(&tv);
		philo->meals_counter ++;
		if (philo->table->nbr_limit_meals == philo->meals_counter)
			philo->is_full = 1;
		safe_mutex_handle(&philo->first_fork->fork, MTX_UNLOCK);
		printf("%lld %d has put down the first fork\n",get_timestamp_in_ms(&tv), philo->id);
		safe_mutex_handle(&philo->second_fork->fork, MTX_UNLOCK);
		printf("%lld %d has put down the second fork\n", get_timestamp_in_ms(&tv), philo->id);
		printf("%lld %d is sleeping\n", get_timestamp_in_ms(&tv), philo->id);
		usleep((philo->table->time_to_sleep) * 1000);
		printf("%lld %d is thinking\n", get_timestamp_in_ms(&tv), philo->id);
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
	struct	timeval	start_time;

	i = -1;
	gettimeofday(&start_time, NULL);
	table->start_simulation = start_time.tv_usec;
	while (++i < table->nbr_philo)
		table->philos[i].last_meal_time = table->start_simulation;
	i = -1;
	while (++i < table->nbr_philo)
	{
		if (safe_pthread_handle(&(table->philos[i].thread_id), dinner_simulation, (void *)&table->philos[i], THREAD_CREATE) == ERROR_CODE)
			return (ERROR_CODE);
	}
	i = -1;
	while (++i < table->nbr_philo)
	{
		if (safe_pthread_handle(&(table->philos[i].thread_id), NULL, NULL, THREAD_JOIN) == ERROR_CODE)
			return (ERROR_CODE);
	}
	// 	i = -1;
	// while (++i < table->nbr_philo)
	// {
	// 	if (safe_pthread_handle(&(table->philos[i].thread_id), NULL, NULL, TH) == ERROR_CODE)
	// 		return (ERROR_CODE);
	// }
	return (0);
}