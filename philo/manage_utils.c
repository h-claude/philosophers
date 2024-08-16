/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:51:42 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/16 20:09:10 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	print_status_philos(t_philo *philos, t_philo_status code)
{
	if (code == THINK)
		printf("%s is thinking\n", philos->id);
	else if (code == RIGHT_FORK)
		printf("%s has taken the right fork\n", philos->id);
	else if (code == LEFT_FORK)
		printf("%s has taken the left fork\n", philos->id);
	else if (code == EAT)
		printf("%s is eating\n", philos->id);
	else if (code == SLEEP)
		printf("%s is sleeping\n", philos->id);
	else if (code == DIE)
		printf("%s died\n", philos->id);
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
