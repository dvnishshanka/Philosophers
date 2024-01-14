/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnishsha <dnishsha@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:54:36 by dnishsha          #+#    #+#             */
/*   Updated: 2024/01/09 13:54:39 by dnishsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	error_exit(const char *error_msg)
{
	printf("%s\n", error_msg);
	return (ERROR_CODE);
}

void	free_philos_tables(t_table *table)
{
	free(table->forks);
	free(table->philos);
}

void	clean_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i <table->nbr_philo)
	{
		safe_mutex_handle(&table->forks[i].fork, MTX_DESTROY);
		safe_mutex_handle(&table->philos[i].mtx_philo, MTX_DESTROY);
	}
	safe_mutex_handle(&table->mtx_table, MTX_DESTROY);
	free_philos_tables(table);
}

long	get_timestamp_in_ms(void)
{
	long 	timestamp;
	struct	timeval	tv;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (timestamp);
}

// Wait till all philosopher threads are ready
// get_init is used to avoid data races.
void	wait_till_threads_ready(t_table	*table)
{
	while (get_int(&table->mtx_table, &table->all_threads_ready) == 0);
}