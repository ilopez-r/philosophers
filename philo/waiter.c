/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:01:47 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/26 15:50:36 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_necessary_meals(t_philo *philos)
{
	int	i;
	int	philos_finished_eating;

	i = 0;
	philos_finished_eating = 0;
	if (philos->data->necessary_meals == -1)
		return (EXIT_SUCCESS);
	while (i < philos->data->num_of_philos)
	{
		pthread_mutex_lock(&philos->data->meal_lock);
		if (philos[i].meals_eaten >= philos->data->necessary_meals)
			philos_finished_eating++;
		pthread_mutex_unlock(&philos->data->meal_lock);
		i++;
	}
	if (philos_finished_eating == philos->data->num_of_philos)
	{
		pthread_mutex_lock(&philos->data->dead_lock);
		philos->data->dead_flag = 1;
		pthread_mutex_unlock(&philos->data->dead_lock);
		return (1);
	}
	return (0);
}

int	check_if_dead(t_philo *philos)
{
	int	i;
	int	flag;

	i = 0;
	while (i < philos->data->num_of_philos)
	{
		flag = 0;
		pthread_mutex_lock(&philos->data->meal_lock);
		if (get_current_time() - philos[i].last_meal >= philos[i].time_to_die)
			flag = 1;
		pthread_mutex_unlock(&philos->data->meal_lock);
		if (flag == 1)
		{
			philo_msg("died", philos);
			pthread_mutex_lock(&philos->data->dead_lock);
			philos->data->dead_flag = 1;
			pthread_mutex_unlock(&philos->data->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*waitering(void *philo)
{
	t_philo	*philos;

	philos = philo;
	while (69)
		if (check_if_dead(philos) == 1 || check_necessary_meals (philos) == 1)
			break ;
	return (philo);
}
