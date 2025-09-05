/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 02:13:02 by galhajaj          #+#    #+#             */
/*   Updated: 2025/08/25 02:13:04 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long	test_func(t_table *table, int i)
{
	long	last_eat;

	pthread_mutex_lock(&table->eat);
	last_eat = table->philo[i].last_eat;
	pthread_mutex_unlock(&table->eat);
	return (last_eat);
}

void	toggle_death(t_table *table)
{
	pthread_mutex_lock(&table->death);
	table->flag_of_death = 1;
	pthread_mutex_unlock(&table->death);
}

int	check_philo_eat_count(t_philo *philo, t_table *table)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&table->count_eat);
	if (philo->count_eat < table->count_of_eat)
		res = 1;
	pthread_mutex_unlock(&table->count_eat);
	return (res);
}

void	print_death_message(t_table *table, int i)
{
	pthread_mutex_lock(&table->print);
	printf("%lld %d is died\n", get_timestamp()
		- table->philo[i].time_start, table->philo[i].id);
	pthread_mutex_unlock(&table->print);
}

int	check_death_condition(t_table *table, int i)
{
	if (get_timestamp() - test_func(table, i) > table->philo[i].time_to_die)
	{
		toggle_death(table);
		print_death_message(table, i);
		return (1);
	}
	return (0);
}
