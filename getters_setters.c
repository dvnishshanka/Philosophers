/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnishsha <dnishsha@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:27:02 by dnishsha          #+#    #+#             */
/*   Updated: 2024/01/17 12:18:37 by dnishsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// get and set int
void	set_int(t_mtx *mutex, int *dest, int val)
{
	safe_mutex_handle(mutex, MTX_LOCK);
	*dest = val;
	safe_mutex_handle(mutex, MTX_UNLOCK);
}

int	get_int(t_mtx *mutex, int *val)
{
	int	return_val;

	safe_mutex_handle(mutex, MTX_LOCK);
	return_val = *val;
	safe_mutex_handle(mutex, MTX_UNLOCK);
	return (return_val);
}

// get and set long
void	set_long(t_mtx *mutex, long *dest, long val)
{
	safe_mutex_handle(mutex, MTX_LOCK);
	*dest = val;
	safe_mutex_handle(mutex, MTX_UNLOCK);
}

long	get_long(t_mtx *mutex, long *val)
{
	long	return_val;

	safe_mutex_handle(mutex, MTX_LOCK);
	return_val = *val;
	safe_mutex_handle(mutex, MTX_UNLOCK);
	return (return_val);
}

// If simulation is finished will return 1
int	simulation_finished(t_table *table)
{
	return (get_int(&table->mtx_table, &table->is_end_simulation));
}
