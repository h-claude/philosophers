/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:38:10 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/14 16:41:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	philo_function(int flag)
{
	if (flag)
	{
		// do something
	}
	else
	{
		// do something else
	}
}

int start_simulation(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (data->philos->id % 2)
			pthread_create(&data->philos[i].thread_id, NULL, philo_function, 0);
		else
			pthread_create(&data->philos[i].thread_id, NULL, philo_function, 1);
		i++;
	}
	return (0);
}