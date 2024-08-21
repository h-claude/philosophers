/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:38:10 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/21 17:51:53 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_join(data->philos[i++].thread_id, NULL);
	}
}

void	philo_function_odd(t_philo *philo)
{
	while (philo->meals_counter < philo->data->nbr_eat_limit
		|| philo->data->nbr_eat_limit == -1)
	{
		manage_mutex(philo->r_fork, LOCK, philo);
		print_fork(philo);
		manage_mutex(philo->l_fork, LOCK, philo);
		print_fork(philo);
		print_eat(philo);
		manage_mutex(philo->r_fork, UNLOCK, philo);
		manage_mutex(philo->l_fork, UNLOCK, philo);
		print_sleep(philo);
		print_think(philo);
		philo->meals_counter++;
	}
}

void	philo_function_even(t_philo *philo)
{
	while (philo->meals_counter < philo->data->nbr_eat_limit
		|| philo->data->nbr_eat_limit == -1)
	{
		manage_mutex(philo->l_fork, LOCK, philo);
		print_fork(philo);
		manage_mutex(philo->r_fork, LOCK, philo);
		print_fork(philo);
		print_eat(philo);
		manage_mutex(philo->r_fork, UNLOCK, philo);
		manage_mutex(philo->l_fork, UNLOCK, philo);
		print_sleep(philo);
		print_think(philo);
		usleep(2500);
		philo->meals_counter++;
	}
}

void	*philo_function(void *philo_void)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)philo_void;
	if (pthread_mutex_lock(&philo->data->print_mutex))
		error_exit(philo->data);
	if (pthread_mutex_unlock(&philo->data->print_mutex))
		error_exit(philo->data);
	if (philo->data->philos_die)
		exit(1);
	if (philo->id % 2 != 0)
	{
		usleep(philo->data->t_teat / 2);
		philo_function_odd(philo);
	}
	else
		philo_function_even(philo);
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->print_mutex);
	while (i < data->philo_nbr)
	{
		if (pthread_create(&data->philos[i].thread_id,
				NULL, philo_function, (void *)&data->philos[i]))
		{
			data->philos_die = true;
			printf("Error: pthread_create\n");
		}
		i++;
	}
	if (pthread_mutex_unlock(&data->print_mutex))
	{
		data->philos_die = true;
		printf("Error: pthread_mutex_unlock\n");
	}
	join_threads(data);
	return (0);
}
