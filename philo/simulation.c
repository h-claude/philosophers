/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:38:10 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/16 15:01:45 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	philo_function(t_data *data)
{
	if (data->philos->id % 2)
	{
		pthread_mutex_lock(&data->philos->last_fork);
		printf("Philo %d has taken a fork\n", data->philos->id);
		pthread_mutex_unlock(&data->philos->last_fork);
	}
	else
	{
		pthread_mutex_lock(&data->philos->firs_fork);
		pthread_mutex_unlock(&data->philos->firs_fork);
	}
}

int start_simulation(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (data->philos->id % 2)
			pthread_create(&data->philos[i].thread_id, NULL, philo_function, data);
		else
			pthread_create(&data->philos[i].thread_id, NULL, philo_function, data);
		i++;
	}
	return (0);
}