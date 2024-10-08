/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:29:43 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/27 17:58:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	print_think(t_philo *philos)
{
	if (pthread_mutex_lock(&philos->data->print_mutex))
		return (error_exit(philos));
	if (is_dead(philos))
		return (1);
	printf("%-10ld %-7d is thinking\n", get_time_fs(philos), philos->id);
	if (pthread_mutex_unlock(&philos->data->print_mutex))
		return (error_exit(philos));
	if (smart_sleep(philos))
		return (1);
	return (0);
}

int	print_fork(t_philo *philos)
{
	if (pthread_mutex_lock(&philos->data->print_mutex))
		return (error_exit(philos));
	if (is_dead(philos))
		return (exit_thread_free(philos));
	printf("%-10ld %-7d has taken a fork\n", get_time_fs(philos), philos->id);
	if (pthread_mutex_unlock(&philos->data->print_mutex))
		return (error_exit(philos));
	return (0);
}

int	print_eat(t_philo *philos)
{
	if (pthread_mutex_lock(&philos->data->print_mutex))
		return (error_exit(philos));
	if (is_dead(philos))
		return (exit_thread_free(philos));
	printf("%-10ld %-7d is eating\n", get_time_fs(philos), philos->id);
	if (pthread_mutex_unlock(&philos->data->print_mutex))
		return (error_exit(philos));
	philos->last_meal_time = get_time_fs(philos);
	if (ft_usleep(philos->data->t_teat, philos))
		return (1);
	return (0);
}

int	print_sleep(t_philo *philos)
{
	if (pthread_mutex_lock(&philos->data->print_mutex))
		return (error_exit(philos));
	if (is_dead(philos))
		return (1);
	printf("%-10ld %-7d is sleeping\n", get_time_fs(philos), philos->id);
	if (pthread_mutex_unlock(&philos->data->print_mutex))
		return (error_exit(philos));
	if (ft_usleep(philos->data->t_tsleep, philos))
		return (1);
	return (0);
}

int	print_die(t_philo *philos)
{
	printf("\033[91m%-10ld %-7d died\n\033[0m", \
		get_time_fs(philos), philos->id);
	return (1);
}
