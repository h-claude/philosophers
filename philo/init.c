/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:26:59 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/14 16:09:23 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	free_data(t_data *data)
{
	free(data->philos);
	free(data);

}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nbr_philo);
	if (!data->philos)
		return (1);
	while (i < data->nbr_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_counter = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].firs_fork = i;
		data->philos[i].last_fork = (i + 1) % data->nbr_philo;
		data->philos[i].done = false;
		data->philos[i].data = data;
		data->philos[i].thread_id = 0;
		i++;
	}
	return (0);
}
