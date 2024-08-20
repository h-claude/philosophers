/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:38:10 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/20 13:07:15 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	kill_threads_and_mutex(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_nbr)
	{
		//printf("pthread_join %d\n", data->philos[i].id);
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}

void	*philo_function(void *philo_void)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)philo_void;
	//if (philo->id % 2 != 0)
	//	usleep(25000);
	while (philo->meals_counter < philo->data->nbr_eat_limit || philo->data->nbr_eat_limit == -1)
	{
		if (philo->id % 2 != 0)
		{
			manage_mutex(philo->r_fork->fork, LOCK, philo);
			print_status_philos(philo, FORK);
			manage_mutex(philo->l_fork->fork, LOCK, philo);
			print_status_philos(philo, FORK);
			print_status_philos(philo, EAT);
			manage_mutex(philo->r_fork->fork, UNLOCK, philo);
			manage_mutex(philo->l_fork->fork, UNLOCK, philo);
			print_status_philos(philo, SLEEP);
			print_status_philos(philo, THINK);
		}
		else
		{
			manage_mutex(philo->r_fork->fork, LOCK, philo);
			print_status_philos(philo, FORK);
			manage_mutex(philo->l_fork->fork, LOCK, philo);
			print_status_philos(philo, FORK);
			philo->last_meal_time = get_time_fs(philo);
			if (philo->last_meal_time == -1)
				return (philo->data->philos_die = true, NULL);
			print_status_philos(philo, EAT);
			manage_mutex(philo->r_fork->fork, UNLOCK, philo);
			manage_mutex(philo->l_fork->fork, UNLOCK, philo);
			print_status_philos(philo, SLEEP);
			print_status_philos(philo, THINK);
		}
		philo->meals_counter++;
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
	kill_threads_and_mutex(data);
	return (0);
}