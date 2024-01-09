/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnishsha <dnishsha@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:53:30 by dnishsha          #+#    #+#             */
/*   Updated: 2024/01/09 13:53:37 by dnishsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(const char c)
{
	if ((c >= 9 && c <= 13) || (c == ' '))
		return (1);
	return (0);
}

static long	ft_atoi(char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (*str && (is_space(*str) > 0))
		str ++;
	if (*str == '+')
		str ++;
	else if (*str == '-')
	{
		sign = -1;
		str ++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (error_exit("Input contains non-numerical values"));
		num = num * 10 + (*str++ - '0');
		if (((num * sign) > 2147483647) || ((num * sign) < -2147483648))
			return (error_exit("Input value exceeds max/min number limits"));
	}
	return (sign * num);
}

long	parse_input(t_table *table, char **argv)
{
	table->nbr_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (table->nbr_philo == ERROR_CODE || table->time_to_die == ERROR_CODE || 
		table->time_to_eat == ERROR_CODE || table->time_to_sleep == ERROR_CODE)
		return (ERROR_CODE);
	if (table->nbr_philo < 1 || table->nbr_philo > 200)
		return (error_exit("No of philosophers should be between 1 - 200."));
	if (table->time_to_die < 60 || table->time_to_eat < 60 || 
		table->time_to_sleep < 60)
		return (error_exit("time_to_eat/die/sleep shall be greater 60ms."));
	if (argv[5])
	{
		table->nbr_limit_meals = ft_atoi(argv[5]);
		if (table->nbr_limit_meals == ERROR_CODE)
			return (ERROR_CODE);
	}
	else
		table->nbr_limit_meals = -1;
	if (argv[5] && table->nbr_limit_meals < 0)
		return (error_exit("each_philo_must_eat 0 or more times."));
	return (0);
}
