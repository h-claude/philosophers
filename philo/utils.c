/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:34:52 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/27 17:58:31 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	exit_thread_free(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->die_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
	philo->l_fork->taken = false;
	philo->r_fork->taken = false;
	pthread_mutex_unlock(&philo->r_fork->fork);
	pthread_mutex_unlock(&philo->l_fork->fork);
	pthread_mutex_lock(&philo->data->die_mutex);
	philo->data->philos_die = true;
	pthread_mutex_unlock(&philo->data->die_mutex);
	return (1);
}

int	error_exit(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->die_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
	philo->l_fork->taken = false;
	philo->r_fork->taken = false;
	pthread_mutex_unlock(&philo->r_fork->fork);
	pthread_mutex_unlock(&philo->l_fork->fork);
	printf("Error\n");
	pthread_mutex_lock(&philo->data->die_mutex);
	philo->data->philos_die = true;
	pthread_mutex_unlock(&philo->data->die_mutex);
	return (1);
}

int	ft_usleep(long time, t_philo *philo)
{
	long	time_since_last_meal;
	long	sleep_time;

	pthread_mutex_lock(&philo->data->die_mutex);
	if (philo->data->philos_die)
		return (exit_thread_free(philo));
	pthread_mutex_unlock(&philo->data->die_mutex);
	time_since_last_meal = (get_time_fs(philo) - philo->last_meal_time) * 1000;
	if (time > philo->data->t_tdie || \
		time_since_last_meal + time > philo->data->t_tdie)
	{
		sleep_time = philo->data->t_tdie - time_since_last_meal;
		if (sleep_time > 0)
			usleep(sleep_time);
		pthread_mutex_lock(&philo->data->die_mutex);
		if (philo->data->philos_die)
			return (exit_thread_free(philo));
		philo->data->philos_die = true;
		print_die(philo);
		return (exit_thread_free(philo));
	}
	usleep(time);
	return (0);
}

/*
** Return the current time in milliseconds
*/
long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*
** Return the time since the start of the simulation in milliseconds
*/
inline long	get_time_fs(t_philo *philo)
{
	long			current_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time - philo->data->start_time);
}
