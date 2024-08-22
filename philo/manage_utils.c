/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:51:42 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/22 12:37:25 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	is_dead(t_philo *philo)
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
			exit(1);
		}
		philo->data->philos_die = true;
		print_die(philo);
		pthread_mutex_unlock(&philo->data->die_mutex);
		exit(1);
	}
	pthread_mutex_unlock(&philo->data->die_mutex);
}

void	manage_thread(t_philo *philo, t_thread_code code)
{
	if (code == CREATE)
		pthread_create(&philo->thread_id, NULL, philo_function, philo);
	else if (code == JOIN)
		pthread_join(philo->thread_id, NULL);
	else if (code == DETACH)
		pthread_detach(philo->thread_id);
}

void	manage_mutex(t_mtx *mutex, t_mutex_code code, t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->die_mutex))
		error_exit(philo->data);
	if (philo->data->philos_die)
		exit(1);
	if (pthread_mutex_unlock(&philo->data->die_mutex))
		error_exit(philo->data);
	if (code == LOCK)
	{
		if (pthread_mutex_lock(mutex))
			error_exit(philo->data);
	}
	else
	{
		if (pthread_mutex_unlock(mutex))
			error_exit(philo->data);
	}
}
