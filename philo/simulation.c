/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:38:10 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/16 22:00:40 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	*philo_function(void *philo_void)
{
	t_philo	*philo;
	
	philo = (t_philo *)philo_void;
	while (philo->data->philos_die == false)
	{
		if (philo->id % 2 != 0)
		{
			printf("IMPAIR :\n%d pense\n", philo->id);
			pthread_mutex_lock(&philo->r_fork->fork);
			printf("%d a pris la fourchette droite\n", philo->id);
			pthread_mutex_lock(&philo->l_fork->fork);
			printf("%d a pris la fourchette gauche\n", philo->id);
			printf("%d mange\n", philo->id);
			pthread_mutex_unlock(&philo->r_fork->fork);
			pthread_mutex_unlock(&philo->l_fork->fork);
			printf("%d dort\n", philo->id);
		}
		else
		{
			printf("PAIR :\n%d pense\n", philo->id);
			pthread_mutex_lock(&philo->r_fork->fork);
			printf("%d a pris la fourchette droite\n", philo->id);
			pthread_mutex_lock(&philo->l_fork->fork);
			printf("%d a pris la fourchette gauche\n", philo->id);
			printf("%d mange\n", philo->id);
			pthread_mutex_unlock(&philo->r_fork->fork);
			pthread_mutex_unlock(&philo->l_fork->fork);
			printf("%d dort\n", philo->id);
		}
	}
	return (NULL);
}

void	*monitor_thread(void *data_void)
{
	int i;
	t_data *data;

	i = 0;
	data = (t_data *)data_void;
	while (i < data->philo_nbr)
	{
		if (data->philos[i].done)
		{
			data->philos_die = true;
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

int start_simulation(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_create(&data->philos[i].thread_id, NULL, philo_function, (void *)&data->philos[i]);
		i++;
	}
	pthread_create(&data->monitor, NULL, monitor_thread, (void *)data->philos);
	pthread_detach(data->monitor);
	return (0);
}