/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnishsha <dnishsha@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:25:47 by dnishsha          #+#    #+#             */
/*   Updated: 2024/01/17 11:25:51 by dnishsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo)
{
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;

	write_state(THINK, philo->table, philo);
	time_to_die = get_long(&philo->table->mtx_table,
			&philo->table->time_to_die);
	time_to_eat = get_long(&philo->table->mtx_table,
			&philo->table->time_to_eat);
	time_to_sleep = get_long(&philo->table->mtx_table,
			&philo->table->time_to_sleep);
	if (get_int(&philo->table->mtx_table, 
			&philo->table->nbr_philo) % 2 == 1
		&& (time_to_die - (time_to_eat + time_to_sleep) > 30))
	{
		sleep_with_interruption(time_to_die - (time_to_eat
				+ time_to_sleep) - 30, philo->table);
	}
}

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, MTX_LOCK);
	write_state(TOOK_FIRST_FORK, philo->table, philo);
	safe_mutex_handle(&philo->second_fork->fork, MTX_LOCK);
	write_state(TOOK_SECOND_FORK, philo->table, philo);
	set_long(&philo->mtx_philo, &philo->last_meal_time,
		get_timestamp(MILLISEC));
	write_state(EAT, philo->table, philo);
	sleep_with_interruption(philo->table->time_to_eat, philo->table);
	philo->meals_counter ++;
	if (get_int(&philo->table->mtx_table,
			&philo->table->nbr_limit_meals) == philo->meals_counter)
		set_int(&philo->table->mtx_table, &philo->is_full, 1);
	safe_mutex_handle(&philo->first_fork->fork, MTX_UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, MTX_UNLOCK);
}

void	*dinner_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_till_threads_ready(philo->table);
	set_long(&philo->mtx_philo, &philo->last_meal_time,
		philo->table->start_simulation);
	while (simulation_finished(philo->table) == 0
		&& get_int(&philo->mtx_philo, &philo->is_full) == 0)
	{
		eat(philo);
		write_state(SLEEP, philo->table, philo);
		sleep_with_interruption(philo->table->time_to_sleep, philo->table);
		think(philo);
	}
	return (NULL);
}

// Dinner simulation for single person
static void	*dinner_alone(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_till_threads_ready(philo->table);
	set_long(&philo->mtx_philo, &philo->last_meal_time,
		get_timestamp(MILLISEC));
	safe_mutex_handle(&philo->first_fork->fork, MTX_LOCK);
	write_state(TOOK_FIRST_FORK, philo->table, philo);
	while (simulation_finished(philo->table) == 0)
	{
		usleep(500);
	}
	safe_mutex_handle(&philo->first_fork->fork, MTX_UNLOCK);
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
		safe_pthread_handle(&(table->philos[0].thread_id),
			dinner_alone, (void *)&table->philos[0], THREAD_CREATE);
	else
	{
		if (create_phil_thread(table) == ERROR_CODE)
			return (ERROR_CODE);
	}
	safe_pthread_handle(&table->monitor, monitor_philos,
		(void *)table, THREAD_CREATE);
	table->start_simulation = get_timestamp(MILLISEC);
	set_int(&table->mtx_table, &table->all_threads_ready, 1);
	i = -1;
	while (++i < table->nbr_philo)
	{
		if (safe_pthread_handle(&(table->philos[i].thread_id),
				NULL, NULL, THREAD_JOIN) == ERROR_CODE)
			return (ERROR_CODE);
	}
	set_int(&table->mtx_table, &table->is_end_simulation, 1);
	safe_pthread_handle(&(table->monitor), NULL, NULL, THREAD_JOIN);
	return (0);
}
