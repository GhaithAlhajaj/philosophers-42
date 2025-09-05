/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:45:52 by galhajaj          #+#    #+#             */
/*   Updated: 2025/08/24 22:18:19 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long long	ft_atoi(const char *str)
{
	int					i;
	int					flag;
	unsigned long long	nbr;

	i = 0;
	nbr = 0;
	flag = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-')
		flag = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		return (-1);
	if (flag == 1 && nbr >= 9223372036854775807u)
		return (-1);
	if (flag == -1 && nbr >= 9223372036854775808u)
		return (0);
	return (nbr * flag);
}

long long	get_timestamp(void)
{
	struct timeval	t;
	long long		now;

	gettimeofday(&t, NULL);
	now = ((t.tv_sec * 1000) + (t.tv_usec / 1000));
	return (now);
}

int	ft_free(t_table *table)
{
	if (table->philo)
		free(table->philo);
	if (table->fork)
		free(table->fork);
	if (table->thread)
		free(table->thread);
	free(table);
	return (1);
}

void	ft_destroy_mutex(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->count_philo)
		if (pthread_mutex_destroy(&table->fork[i]))
			printf("Error: Destroyed mutex %d.\n", i);
	pthread_mutex_destroy(&table->print);
}

void	ft_usleep(long long time, t_table *table)
{
	long long	start;

	start = get_timestamp();
	while (get_timestamp() - start < time && !check_death(table))
		usleep(100);
}
