/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 01:44:01 by galhajaj          #+#    #+#             */
/*   Updated: 2025/08/25 02:20:29 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_eat;
	int				left_fork;
	int				right_fork;
	long long		time_start;
	long long		last_eat;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				count_philo;
	int				count_of_eat;
	int				flag_of_death;
	long long		time_start;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	eat;
	pthread_mutex_t	count_eat;
	pthread_mutex_t	death;
	t_philo			*philo;
}	t_table;

//utils
long long	ft_atoi(const char *str);
long long	get_timestamp(void);
int			ft_free(t_table *table);
void		ft_destroy_mutex(t_table *table);
void		ft_usleep(long long time, t_table *table);

//init
t_table		*init_table(int ac, char **av);
int			check(int ac, char **av);
int			malloc_philo(t_table *table);
int			init_philo(t_table *table, char **av);

//philo
void		philo_print(t_table	*table, t_philo *philo, char *str);
int			eating(t_table *table, t_philo *philo);
void		sleeping(t_table *table, t_philo *philo);
void		thinking(t_table *table, t_philo *philo);

//main
void		start(t_table *table);
void		*philo_life(void *data);
void		*death(void *data);

//lol
int			check_death(t_table *table);
int			check_death_condition(t_table *table, int i);
void		print_death_message(t_table *table, int i);
int			check_philo_eat_count(t_philo *philo, t_table *table);
void		toggle_death(t_table *table);
long		test_func(t_table *table, int i);
void		philo_print(t_table *table, t_philo *philo, char *str);
void		inc_count_eat(t_philo *philo);
void		lock_first_fork(t_table *table, t_philo *philo);
int			handle_one_philo_case(t_table *table, t_philo *philo);

#endif
