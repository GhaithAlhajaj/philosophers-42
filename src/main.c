/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 01:33:41 by galhajaj          #+#    #+#             */
/*   Updated: 2025/08/24 22:18:33 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	check_all_philosophers(t_table *table)
{
	int	i;
	int	is_finished;

	i = -1;
	is_finished = 1;
	while (++i < table->count_philo)
	{
		if (check_philo_eat_count(&table->philo[i], table))
			is_finished = 0;
		if (check_death_condition(table, i))
			return (-1);
	}
	return (is_finished);
}

void	*death(void *data)
{
	t_table	*table;
	int		is_finished;

	table = data;
	is_finished = 1;
	while (is_finished)
	{
		is_finished = check_all_philosophers(table);
		if (is_finished == -1)
			return (NULL);
	}
	return (NULL);
}

void	*philo_life(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = data;
	table = philo->table;
	if (philo->id % 2 == 0)
	{
		philo_print(table, philo, "is thinking");
		ft_usleep(50, table);
	}
	while (!check_death(table))
	{
		if (table->count_of_eat)
			if (philo->count_eat == table->count_of_eat)
				return (NULL);
		if (eating(table, philo))
			return (NULL);
		sleeping(table, philo);
		thinking(table, philo);
	}
	return (NULL);
}

void	start(t_table *table)
{
	int			i;
	pthread_t	check;

	i = -1;
	table->time_start = get_timestamp();
	while (++i < table->count_philo)
	{
		table->philo[i].time_start = table->time_start;
		table->philo[i].last_eat = table->time_start;
	}
	i = -1;
	while (++i < table->count_philo)
		pthread_create(&table->thread[i], NULL, &philo_life, &table->philo[i]);
	pthread_create(&check, NULL, &death, table);
	pthread_join(check, NULL);
	i = -1;
	while (++i < table->count_philo)
		pthread_join(table->thread[i], NULL);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (check(argc, argv))
		return (1);
	table = init_table(argc, argv);
	if (!table)
		return (1);
	if (malloc_philo(table))
		return (ft_free(table));
	if (init_philo(table, argv))
		return (ft_free(table));
	start(table);
	ft_destroy_mutex(table);
	ft_free(table);
	return (0);
}
