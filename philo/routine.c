/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:06:31 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/26 16:04:46 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
}

void	routines(t_philo *philos)
{
	pthread_mutex_lock(philos->r_fork);
	philo_msg("has taken a fork", philos);
	if (philos->data->num_of_philos == 1)
	{
		ft_usleep(philos->time_to_die);
		pthread_mutex_unlock(philos->r_fork);
		return ;
	}
	pthread_mutex_lock(philos->l_fork);
	philo_msg("has taken a fork", philos);
	philo_msg("is eating", philos);
	pthread_mutex_lock(&philos->data->meal_lock);
	philos->last_meal = get_current_time();
	philos->meals_eaten++;
	pthread_mutex_unlock(&philos->data->meal_lock);
	ft_usleep(philos->time_to_eat);
	pthread_mutex_unlock(philos->r_fork);
	pthread_mutex_unlock(philos->l_fork);
	philo_msg("is sleeping", philos);
	ft_usleep(philos->time_to_sleep);
	philo_msg("is thinking", philos);
}

void	*philo_routine(void *philo)
{
	t_philo	*philos;

	philos = philo;
	if (philos->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philos))
		routines(philos);
	return (philo);
}
