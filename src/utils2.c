/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 02:24:32 by galhajaj          #+#    #+#             */
/*   Updated: 2025/08/25 02:25:19 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	check_death(t_table *table)
{
	int	res;

	pthread_mutex_lock(&table->death);
	res = table->flag_of_death;
	pthread_mutex_unlock(&table->death);
	return (res);
}

void	philo_print(t_table *table, t_philo *philo, char *str)
{
	if (check_death(table))
		return ;
	pthread_mutex_lock(&table->print);
	printf("%lld %d %s\n", get_timestamp() - philo->time_start, philo->id, str);
	pthread_mutex_unlock(&table->print);
}

void	inc_count_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->count_eat);
	philo->count_eat++;
	pthread_mutex_unlock(&philo->table->count_eat);
}

void	lock_first_fork(t_table *table, t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
		pthread_mutex_lock(&table->fork[philo->left_fork]);
	else
		pthread_mutex_lock(&table->fork[philo->right_fork]);
	philo_print(table, philo, "has taken a fork");
}

int	handle_one_philo_case(t_table *table, t_philo *philo)
{
	if (table->count_philo == 1)
	{
		pthread_mutex_unlock(&table->fork[philo->left_fork]);
		return (1);
	}
	return (0);
}
