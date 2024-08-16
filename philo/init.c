/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:26:59 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/16 21:54:46 by hclaude          ###   ########.fr       */
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
		free(data->philos[i].l_fork);
		i++;
	}	
	free(data->philos);
	free(data);

}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_nbr + 1);
	if (!data->philos)
		return (1);
	while (i < data->philo_nbr)
	{
		data->philos[i].id = i + 1;
		data->philos[i].thread_id = 0;
		data->philos[i].meals_counter = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].done = false;
		data->philos[i].data = data;
		data->philos[i].r_fork = malloc(sizeof(t_fork));
		data->philos[i].l_fork = malloc(sizeof(t_fork));
		if (!data->philos[i].r_fork || !data->philos[i].l_fork)
			return (1); // nul car faut free les mallocs avant de return 1
		data->philos[i].r_fork->fork_id = i;
		data->philos[i].l_fork->fork_id = (i + 1) % data->philo_nbr;
		pthread_mutex_init(&data->philos[i].r_fork->fork, NULL);
		pthread_mutex_init(&data->philos[i].l_fork->fork, NULL);
		i++;
	}
	return (0);
}
