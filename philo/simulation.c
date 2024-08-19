/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:38:10 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/19 16:29:24 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	kill_threads_and_mutex(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_nbr)
	{
		printf("pthread_join %d\n", data->philos[i].id);
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
	while (philo->meals_counter < philo->data->nbr_eat_limit)
	{
		if (philo->id % 2 != 0)
		{
			usleep(250000);
			//sleep(5);
			print_status_philos(philo, THINK);
			manage_mutex(&philo->r_fork->fork, LOCK);
			print_status_philos(philo, RIGHT_FORK);
			manage_mutex(&philo->l_fork->fork, LOCK);
			print_status_philos(philo, LEFT_FORK);
			print_status_philos(philo, EAT);
			manage_mutex(&philo->r_fork->fork, UNLOCK);
			manage_mutex(&philo->l_fork->fork, UNLOCK);
			print_status_philos(philo, SLEEP);
		}
		else
		{
			print_status_philos(philo, THINK);
			manage_mutex(&philo->r_fork->fork, LOCK);
			print_status_philos(philo, RIGHT_FORK);
			manage_mutex(&philo->l_fork->fork, LOCK);
			print_status_philos(philo, LEFT_FORK);
			print_status_philos(philo, EAT);
			manage_mutex(&philo->r_fork->fork, UNLOCK);
			manage_mutex(&philo->l_fork->fork, UNLOCK);
			print_status_philos(philo, SLEEP);
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