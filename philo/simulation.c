/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:38:10 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/25 11:38:50 by hclaude          ###   ########.fr       */
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
	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_destroy(data->philos[i++].r_fork);
	}
	pthread_mutex_destroy(&data->die_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	free(data->philos);
	free(data->forks);
}

void	*philo_function_odd(t_philo *philo)
{
	while (philo->meals_counter < \
		philo->data->nbr_eat_limit || philo->data->nbr_eat_limit == -1)
	{
		if (manage_mutex(philo->r_fork, LOCK, philo))
			return (NULL);
		if (print_fork(philo))
			return (NULL);
		if (manage_mutex(philo->l_fork, LOCK, philo))
			return (NULL);
		if (print_fork(philo))
			return (NULL);
		if (print_eat(philo))
			return (NULL);
		if (manage_mutex(philo->r_fork, UNLOCK, philo))
			return (NULL);
		if (manage_mutex(philo->l_fork, UNLOCK, philo))
			return (NULL);
		if (print_sleep(philo))
			return (NULL);
		if (print_think(philo))
			return (NULL);
		philo->meals_counter++;
	}
	return (NULL);
}

void	*philo_function_even(t_philo *philo)
{
	while (philo->meals_counter < \
		philo->data->nbr_eat_limit || philo->data->nbr_eat_limit == -1)
	{
		if (manage_mutex(philo->l_fork, LOCK, philo))
			return (NULL);
		if (print_fork(philo))
			return (NULL);
		if (manage_mutex(philo->r_fork, LOCK, philo))
			return (NULL);
		if (print_fork(philo))
			return (NULL);
		if (print_eat(philo))
			return (NULL);
		if (manage_mutex(philo->r_fork, UNLOCK, philo))
			return (NULL);
		if (manage_mutex(philo->l_fork, UNLOCK, philo))
			return (NULL);
		if (print_sleep(philo))
			return (NULL);
		if (print_think(philo))
			return (NULL);
		usleep(2000);
		philo->meals_counter++;
	}
	return (NULL);
}

void	*philo_function(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	if (pthread_mutex_lock(&philo->data->print_mutex))
		error_exit(philo);
	if (pthread_mutex_unlock(&philo->data->print_mutex))
		error_exit(philo);
	pthread_mutex_lock(&philo->data->die_mutex);
	if (philo->data->philos_die)
	{
		pthread_mutex_unlock(&philo->data->die_mutex);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->data->die_mutex);
	if (philo->id % 2 != 0)
	{
		if (philo->data->t_teat < philo->data->t_tdie)
			usleep(philo->data->t_teat / 2);
		return (philo_function_odd(philo));
	}
	else
		return (philo_function_even(philo));
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
			return (pthread_mutex_unlock(&data->print_mutex), \
				join_threads(data), 1);
		}
		i++;
	}
	data->start_time = get_current_time();
	if (pthread_mutex_unlock(&data->print_mutex))
	{
		data->philos_die = true;
		printf("Error: pthread_mutex_unlock\n");
	}
	join_threads(data);
	return (0);
}
