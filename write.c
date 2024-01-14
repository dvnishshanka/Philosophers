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
	struct timeval	tv;

	if ((state == TOOK_FIRST_FORK || state == TOOK_SECOND_FORK) && simulation_finished(table) == 0)
	{
		printf("%ld %d has taken a fork\n", get_timestamp_in_ms(&tv), philo->id);
	}
	else if (state == THINK)
	{
		printf("%ld %d is thinking\n", get_timestamp_in_ms(&tv), philo->id);
	}
	else if (state == EAT)
	{
		printf("%ld %d is eating\n", get_timestamp_in_ms(&tv), philo->id);
	}
	else if (state == SLEEP)
	{
		printf("%ld %d is sleeping\n", get_timestamp_in_ms(&tv), philo->id);
	}
	else if (state == DIED)
	{
		printf("%ld %d died\n", get_timestamp_in_ms(&tv), philo->id);
	}
}
