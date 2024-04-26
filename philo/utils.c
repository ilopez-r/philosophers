/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:09:16 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/26 15:44:14 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philos)
{
	pthread_mutex_lock(&philos->data->dead_lock);
	if (philos->data->dead_flag == 1)
		return (pthread_mutex_unlock(&philos->data->dead_lock), 1);
	pthread_mutex_unlock(&philos->data->dead_lock);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	philo_msg(char *s, t_philo *philos)
{
	size_t	time;

	pthread_mutex_lock(&philos->data->write_lock);
	time = get_current_time() - philos->start_time;
	if (!dead_loop(philos))
		printf("%zu %d %s\n", time, philos->id, s);
	pthread_mutex_unlock(&philos->data->write_lock);
}

int	ft_atoi(const char *s)
{
	long int	i;
	long int	num;

	i = 0;
	num = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		num = num * 10 + (s[i] - 48);
		i++;
	}
	return (num);
}
