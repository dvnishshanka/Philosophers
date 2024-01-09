/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnishsha <dnishsha@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:52:57 by dnishsha          #+#    #+#             */
/*   Updated: 2024/01/09 13:53:01 by dnishsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if ((parse_input(&table, argv)) == ERROR_CODE)
			return (1);
		if (table.nbr_limit_meals == 0)
			return (0);
		if (data_init(&table) == ERROR_CODE)
			return (1);
		print_philos(table.philos);
		free_all(&table);
	}
	else
	{
		error_exit
		("Wrong input.\n
			Correct format: number_of_philosophers time_to_die 
			time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
		return (1);
	}
return (0);
}
