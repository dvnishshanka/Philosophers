/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnishsha <dnishsha@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:54:21 by dnishsha          #+#    #+#             */
/*   Updated: 2024/01/09 13:54:23 by dnishsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// We will not write the status if stimulation has been ended
void	write_state(t_philo_state state, t_table *table, t_philo *philo)
{
	long	time_elapsed;

	time_elapsed = get_timestamp_in_ms() - table->start_simulation;
	if (get_int(&philo->mtx_philo, &philo->is_full) == 1)
		return ;
	safe_mutex_handle(&table->mtx_write, MTX_LOCK);
	safe_mutex_handle(&philo->mtx_philo, MTX_LOCK);
	if ((state == TOOK_FIRST_FORK || state == TOOK_SECOND_FORK) && simulation_finished(table) == 0)
	{
		printf("%-8ld %d has taken a fork\n", time_elapsed, philo->id);
	}
	else if (state == THINK && simulation_finished(table) == 0)
	{
		printf("%-8ld %d is thinking\n", time_elapsed, philo->id);
	}
	else if (state == EAT && simulation_finished(table) == 0)
	{
		printf(COLOR_BLUE"%-8ld %d is eating\n"COLOR_RESET, time_elapsed, philo->id);
	}
	else if (state == SLEEP && simulation_finished(table) == 0)
	{
		printf("%-8ld %d is sleeping\n", time_elapsed, philo->id);
	}
	else if (state == DIED && simulation_finished(table) == 0)
	{
		printf(COLOR_RED"%-8ld %d died\n"COLOR_RESET, time_elapsed, philo->id);
	}
	safe_mutex_handle(&table->mtx_write, MTX_UNLOCK);
	safe_mutex_handle(&philo->mtx_philo, MTX_UNLOCK);
}
