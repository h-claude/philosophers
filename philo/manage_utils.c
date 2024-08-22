/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:51:42 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/22 18:08:21 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	is_dead(t_philo *philo)
{
	long	current_time;

	current_time = get_time_fs(philo);
	current_time = current_time - philo->last_meal_time;
	pthread_mutex_lock(&philo->data->die_mutex);
	if (current_time >= philo->data->t_tdie / 1000 || philo->data->philos_die)
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

int	manage_mutex(t_mtx *mutex, t_mutex_code code, t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->die_mutex))
		return (error_exit(philo));
	if (philo->data->philos_die)
		return (exit_thread_free(philo));
	if (pthread_mutex_unlock(&philo->data->die_mutex))
		return (error_exit(philo));
	if (code == LOCK)
	{
		if (pthread_mutex_lock(mutex))
			return (error_exit(philo));
	}
	else
	{
		if (pthread_mutex_unlock(mutex))
			return (error_exit(philo));
	}
	return (0);
}
