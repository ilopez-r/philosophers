/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:53:14 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/26 15:48:46 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arguments(char **s)
{
	int	i;
	int	j;

	i = 0;
	while (s[++i])
	{
		j = -1;
		while (s[i][++j])
			if (s[i][j] < '0' || s[i][j] > '9')
				return (EXIT_FAILURE);
	}
	if (ft_atoi(s[1]) < 1 || ft_atoi(s[1]) > 200 || ft_atoi(s[2]) == 0
		|| ft_atoi(s[3]) == 0 || ft_atoi(s[4]) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	init_structs(t_data *data, t_philo *philos, char **argv, int i)
{
	data->dead_flag = 0;
	data->num_of_philos = ft_atoi(argv[1]);
	data->necessary_meals = -1;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	while (++i < data->num_of_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_current_time();
		philos[i].time_to_die = ft_atoi(argv[2]);
		philos[i].time_to_eat = ft_atoi(argv[3]);
		philos[i].time_to_sleep = ft_atoi(argv[4]);
		philos[i].start_time = get_current_time();
		philos[i].l_fork = &data->forks[i];
		if (i == 0)
			philos[i].r_fork = &data->forks[data->num_of_philos - 1];
		else
			philos[i].r_fork = &data->forks[i - 1];
		philos[i].data = data;
	}
}

void	destroy_mutex(t_philo *p, int flag)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&p->data->write_lock);
	pthread_mutex_destroy(&p->data->meal_lock);
	pthread_mutex_destroy(&p->data->dead_lock);
	while (++i < p->data->num_of_philos)
		pthread_mutex_destroy(&p->data->forks[i]);
	if (flag == 1)
		printf("Error creating thread\n");
	if (flag == 2)
		printf("Error creating threads\n");
	if (flag == 3)
		printf("Error joining threads\n");
	if (flag == 4)
		printf("Error joining thread waiter\n");
}

void	threads(t_philo *p)
{
	pthread_t	waiter;
	int			i;

	i = -1;
	if (pthread_create(&waiter, NULL, &waitering, p) != 0)
		destroy_mutex(p, 1);
	while (++i < p->data->num_of_philos)
		if (pthread_create(&p[i].thread, NULL, &philo_routine, &p[i]) != 0)
			destroy_mutex(p, 2);
	i = -1;
	while (++i < p->data->num_of_philos)
		if (pthread_join(p[i].thread, NULL) != 0)
			destroy_mutex(p, 3);
	if (pthread_join(waiter, NULL) != 0)
		destroy_mutex(p, 4);
}

int	main( int argc, char **argv)
{
	t_data	data;
	t_philo	philos[PHIL_MAX];

	if (argc < 5 || argc > 6 || check_arguments (argv) == 1)
		return (printf ("Error: number of arguments\n"), EXIT_FAILURE);
	init_structs(&data, philos, argv, -1);
	if (argc == 6)
		data.necessary_meals = ft_atoi(argv[5]);
	threads(philos);
	destroy_mutex(philos, 0);
}
