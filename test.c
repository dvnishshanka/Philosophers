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

void print_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].table->nbr_philo)
	{
		printf("Philosopher %d:\n\tmeals_counter %d\n\tis_full %d\n\tlast_meal_time %ld\n\tfirst_fork id %d\n\tsecond_fork id %d\n\tthread_id %ld\n",i, philos[i].meals_counter,
	philos[i].is_full, philos[i].last_meal_time, philos[i].first_fork->fork_id, philos[i].second_fork->fork_id, philos[i].thread_id);
		i ++;
	}
}
