/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:51:42 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/19 16:10:55 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	print_status_philos(t_philo *philos, t_philo_status code)
{
	if (code == THINK)
		printf("%d is thinking\n", philos->id);
	else if (code == RIGHT_FORK)
		printf("%d has taken the right fork\n", philos->id);
	else if (code == LEFT_FORK)
		printf("%d has taken the left fork\n", philos->id);
	else if (code == EAT)
		printf("%d is eating\n", philos->id);
	else if (code == SLEEP)
		printf("%d is sleeping\n", philos->id);
	else if (code == DIE)
		printf("%d died\n", philos->id);
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

void	manage_mutex(t_mtx *mutex, t_mutex_code code)
{
	if (code == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (code == LOCK)
		pthread_mutex_lock(mutex);
	else if (code == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (code == DESTROY)
		pthread_mutex_destroy(mutex);
}
