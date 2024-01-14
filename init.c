/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnishsha <dnishsha@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:52:21 by dnishsha          #+#    #+#             */
/*   Updated: 2024/01/09 13:52:31 by dnishsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks)
{
	if ((philo->id) % 2 == 0)
	{
		philo->first_fork = &forks[(philo->id) - 1];
		philo->second_fork = &forks[(philo->id) % (philo->table->nbr_philo)];
	}
	else
	{
		philo->first_fork = &forks[(philo->id) % (philo->table->nbr_philo)];
		philo->second_fork = &forks[(philo->id) - 1];
	}
}

static long	philo_init(t_table *table)
{
	int		i;
	t_philo	*philos;

	i = -1;
	philos = table->philos;
	while (++i < table->nbr_philo)
	{
		philos[i].id = i + 1;
		philos[i].meals_counter = 0;
		philos[i].is_full = 0;
		philos[i].table = table;
		safe_mutex_handle(&philos[i].mtx_philo, MTX_INIT);
		assign_forks(&philos[i], table->forks);
	}
	return (0);
}

long	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->is_end_simulation = 0;
	table->forks = (t_fork *)malloc(sizeof (t_fork) * table->nbr_philo);
	if (!table->forks)
		return (error_exit("Malloc Failed"));
	table->philos = (t_philo *)malloc(sizeof (t_philo) * table->nbr_philo);
	if (!table->philos)
	{
		free(table->forks);
		return (error_exit("Malloc Failed"));
	}
	safe_mutex_handle(&table->mtx_table, MTX_INIT);
	safe_mutex_handle(&table->mtx_write, MTX_INIT);
	while (++i < table->nbr_philo)
	{
		if (safe_mutex_handle(&table->forks[i].fork, MTX_INIT) == ERROR_CODE)
		{
			free_philos_tables(table);
			return (ERROR_CODE);
		}
		table->forks[i].fork_id = i;
	}
	philo_init(table);
	return (0);
}
