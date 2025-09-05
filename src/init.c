/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 03:53:46 by galhajaj          #+#    #+#             */
/*   Updated: 2025/08/24 21:24:59 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	check(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Error: Wrong number argments!");
		return (1);
	}
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0
		|| ft_atoi(av[4]) <= 0 || (ac == 6 && ft_atoi(av[5]) <= 0))
	{
		printf("Error: Wrong arguments!");
		return (1);
	}
	return (0);
}

t_table	*init_table(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->count_philo = ft_atoi(av[1]);
	if (!table->count_philo)
		return (NULL);
	table->count_of_eat = 0;
	if (ac == 6)
		table->count_of_eat = ft_atoi(av[5]);
	table->flag_of_death = 0;
	table->time_start = 0;
	table->thread = NULL;
	table->fork = NULL;
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->eat, NULL);
	pthread_mutex_init(&table->death, NULL);
	pthread_mutex_init(&table->count_eat, NULL);
	table->philo = NULL;
	return (table);
}

int	malloc_philo(t_table *table)
{
	table->thread = malloc(sizeof(pthread_t) * table->count_philo);
	if (!table->thread)
		return (1);
	table->fork = malloc(sizeof(pthread_mutex_t) * table->count_philo);
	if (!table->fork)
		return (1);
	table->philo = malloc(sizeof(t_philo) * table->count_philo);
	if (!table->philo)
		return (1);
	return (0);
}

int	init_philo(t_table *table, char **av)
{
	int	i;

	i = -1;
	while (++i < table->count_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].time_to_die = ft_atoi(av[2]);
		table->philo[i].time_to_eat = ft_atoi(av[3]);
		table->philo[i].time_to_sleep = ft_atoi(av[4]);
		table->philo[i].count_eat = 0;
		table->philo[i].left_fork = i;
		if (i < table->count_philo - 1)
			table->philo[i].right_fork = i + 1;
		else
			table->philo[i].right_fork = 0;
		table->philo[i].time_start = 0;
		table->philo[i].last_eat = 0;
		table->philo[i].table = table;
	}
	i = -1;
	while (++i < table->count_philo)
		if (pthread_mutex_init(&table->fork[i], NULL))
			return (1);
	return (0);
}
