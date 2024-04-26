/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:52:48 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/26 15:50:09 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define PHIL_MAX 200

typedef struct s_data
{
	int				dead_flag;
	int				num_of_philos;
	int				necessary_meals;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	forks[PHIL_MAX];
}				t_data;

typedef struct s_philo
{
	int				meals_eaten;
	int				id;
	int				eating;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_data			*data;
	pthread_t		thread;
}				t_philo;

int		ft_atoi(const char *s);
void	*waitering(void *philo);
void	philo_msg(char *s, t_philo *philos);
size_t	get_current_time(void);
int		dead_loop(t_philo *philos);
void	*philo_routine(void *philo);

#endif