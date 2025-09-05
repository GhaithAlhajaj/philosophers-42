/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 05:39:15 by galhajaj          #+#    #+#             */
/*   Updated: 2025/08/24 22:23:15 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	lock_second_fork(t_table *table, t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
		pthread_mutex_lock(&table->fork[philo->right_fork]);
	else
		pthread_mutex_lock(&table->fork[philo->left_fork]);
	philo_print(table, philo, "has taken a fork");
}

static void	start_eating(t_table *table, t_philo *philo)
{
	philo_print(table, philo, "is eating");
	inc_count_eat(philo);
	pthread_mutex_lock(&philo->table->eat);
	philo->last_eat = get_timestamp();
	pthread_mutex_unlock(&philo->table->eat);
	ft_usleep(philo->time_to_eat, table);
}

int	eating(t_table *table, t_philo *philo)
{
	if (check_death(table))
		return (1);
	lock_first_fork(table, philo);
	if (handle_one_philo_case(table, philo))
		return (1);
	lock_second_fork(table, philo);
	start_eating(table, philo);
	pthread_mutex_unlock(&table->fork[philo->left_fork]);
	pthread_mutex_unlock(&table->fork[philo->right_fork]);
	return (0);
}

void	sleeping(t_table *table, t_philo *philo)
{
	if (check_death(table))
		return ;
	philo_print(table, philo, "is sleeping");
	ft_usleep(philo->time_to_sleep, table);
}

void	thinking(t_table *table, t_philo *philo)
{
	if (check_death(table))
		return ;
	philo_print(table, philo, "is thinking");
}
