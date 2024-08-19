/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:26:59 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/18 11:41:36 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		free(data->philos[i].r_fork);
		i++;
	}
	free(data->philos);
	free(data);

}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
	while (i < data->philo_nbr)
	{
		data->forks[i].fork_id = i;
		if (pthread_mutex_init(&data->forks[i++].fork, NULL))
			return (1);
	}
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philos)
		return (1);
	init_forks(data);
	while (i < data->philo_nbr)
	{
		data->philos[i].id = i;
		//printf("id = %d\nSon oppose = %ld\n", data->philos[i].id, (i + 1) % data->philo_nbr);
		data->philos[i].thread_id = 0;
		data->philos[i].meals_counter = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].done = false;
		data->philos[i].data = data;
		data->philos[i].r_fork = &data->forks[i];
		data->philos[i].l_fork = &data->forks[(i + 1) % data->philo_nbr];
		if (!data->philos[i].r_fork)
			return (1); // nul car faut free les mallocs avant de return 1
		data->philos[i].r_fork->fork_id = i;
		i++;
	}
	return (0);
}
