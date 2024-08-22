/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:26:59 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/22 10:32:19 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
	if (!data->forks)
		return (1);
	while (i < data->philo_nbr)
	{
		data->forks[i].fork_id = i;
		if (pthread_mutex_init(&data->forks[i].fork, NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i].fork);
			return (free(data->forks), 1);
		}
		i++;
	}
	return (0);
}

int	if_philo_alone(t_data *data)
{
	if (data->philo_nbr == 1)
	{
		printf("%-10d %-7d has taken a fork\n", 0, 1);
		usleep(data->t_tdie);
		printf("\033[91m%-10ld %-7d died\n\033[0m", data->t_tdie / 1000, 1);
		return (2);
	}
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		data->philos[i].id = i + 1;
		data->philos[i].thread_id = 0;
		data->philos[i].meals_counter = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].done = false;
		data->philos[i].data = data;
		data->philos[i].r_fork = &data->forks[i].fork;
		data->philos[i].l_fork = &data->forks[(i + 1) % data->philo_nbr].fork;
		i++;
	}
}

int	init_philos_and_forks(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philos)
		return (1);
	if (init_forks(data))
		return (free(data->philos), 1);
	if (if_philo_alone(data))
		return (free(data->philos), free(data->forks), 2);
	init_philos(data);
	if (pthread_mutex_init(&data->die_mutex, NULL))
		return (free(data->philos), free(data->forks), 1);
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (free(data->philos), free(data->forks), \
			pthread_mutex_destroy(&data->die_mutex), 1);
	return (0);
}
