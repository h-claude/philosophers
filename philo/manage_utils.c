/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:51:42 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/27 13:51:34 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	smart_sleep(t_philo *philo)
{
	long	current_time;

	current_time = get_time_fs(philo) - philo->last_meal_time;
	while (current_time <= philo->data->t_tdie / 1000 && \
		!philo->data->philos_die && \
			philo->r_fork->taken && philo->l_fork->taken)
	{
		usleep(50);
		current_time = get_time_fs(philo) - philo->last_meal_time;
	}
	if (is_dead(philo))
		return (1);
	return (0);
}

int	is_dead(t_philo *philo)
{
	long	current_time;

	pthread_mutex_lock(&philo->data->die_mutex);
	current_time = get_time_fs(philo) - philo->last_meal_time;
	if (current_time > philo->data->t_tdie / 1000 || philo->data->philos_die)
	{
		if (philo->data->philos_die)
		{
			pthread_mutex_unlock(&philo->data->die_mutex);
			return (exit_thread_free(philo));
		}
		philo->data->philos_die = true;
		print_die(philo);
		return (exit_thread_free(philo));
	}
	pthread_mutex_unlock(&philo->data->die_mutex);
	return (0);
}

int	manage_mutex(t_fork *fork, t_mutex_code code, t_philo *philo)
{
	if (is_dead(philo))
		return (exit_thread_free(philo));
	if (pthread_mutex_lock(&philo->data->die_mutex))
		return (error_exit(philo));
	if (philo->data->philos_die)
		return (exit_thread_free(philo));
	if (pthread_mutex_unlock(&philo->data->die_mutex))
		return (error_exit(philo));
	if (code == LOCK)
	{
		if (pthread_mutex_lock(&fork->fork))
			return (error_exit(philo));
		fork->taken = true;
	}
	else
	{
		if (pthread_mutex_unlock(&fork->fork))
			return (error_exit(philo));
		fork->taken = false;
	}
	return (0);
}
