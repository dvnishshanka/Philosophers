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

void	free_all(t_table *table)
{
	free(table->forks);
	free(table->philos);
}
