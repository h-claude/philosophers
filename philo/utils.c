/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:34:52 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/22 12:59:40 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	error_exit(t_data *data)
{
	if (pthread_mutex_lock(&data->die_mutex))
	{
		perror("pthread_mutex_lock");
		data->philos_die = true;
		exit(1);
	}
	printf("Error\n");
	data->philos_die = true;
	if (pthread_mutex_unlock(&data->die_mutex))
	{
		perror("pthread_mutex_unlock");
		exit(1);
	}
	exit(1);
}

void	ft_usleep(long time, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->die_mutex);
	if (philo->data->philos_die)
	{
		pthread_mutex_unlock(&philo->data->die_mutex);
		exit(1);
	}
	pthread_mutex_unlock(&philo->data->die_mutex);
	if (time > philo->data->t_tdie)
	{
		usleep(philo->data->t_tdie - philo->last_meal_time * 1000);
		pthread_mutex_lock(&philo->data->die_mutex);
		if (philo->data->philos_die)
			exit(1);
		philo->data->philos_die = true;
		print_die(philo);
		pthread_mutex_unlock(&philo->data->die_mutex);
		exit(1);
	}
	usleep(time);
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
long	get_time_fs(t_philo *philo)
{
	long			current_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time - philo->data->start_time);
}
