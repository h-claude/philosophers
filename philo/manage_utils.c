/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:51:42 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/20 13:17:55 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	is_dead(t_philo *philo)
{
	long	current_time;

	current_time = get_time_fs(philo);
	if (current_time == -1)
		return (perror("gettimeofday"), 1);
	if (current_time - philo->last_meal_time > philo->data->t_tdie)
	{
		printf("%ld %d is dead\n", current_time, philo->id);
		philo->data->philos_die = true;
		return (exit(1), 1);
	}
	return (0);
}

int	print_status_philos(t_philo *philos, t_philo_status code)
{
	long	current_time;

	current_time = get_time_fs(philos);
	if (current_time == -1)
		return (perror("gettimeofday"), 1);
	if (philos->data->philos_die)
		return (exit(1), 1);
	if (is_dead(philos))
		return (1);
	if (code == THINK)
		printf("%ld %d is thinking\n", current_time, philos->id);
	else if (code == FORK)
		printf("%ld %d has taken a fork\n", current_time, philos->id);
	else if (code == EAT)
	{
		philos->last_meal_time = current_time;
		printf("%ld %d is eating\n", current_time, philos->id);
		ft_usleep(philos->data->t_teat, philos);
	}
	else if (code == SLEEP)
	{
		printf("%ld %d is sleeping\n", current_time, philos->id);
		ft_usleep(philos->data->t_tsleep, philos);
	}
	return (0);
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

int	manage_mutex(t_mtx *mutex, t_mutex_code *code, t_philo *philo)
{
	if (philo->data->philos_die)
		return (exit(1), 1);
	if (code == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (code == LOCK)
		pthread_mutex_lock(mutex);
	else if (code == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (code == DESTROY)
		pthread_mutex_destroy(mutex);
	return (0);
}
