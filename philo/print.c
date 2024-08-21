/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:29:43 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/21 17:58:00 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	print_think(t_philo *philos)
{
	long	current_time;

	if (pthread_mutex_lock(&philos->data->print_mutex))
		error_exit(philos->data);
	is_dead(philos);
	current_time = get_time_fs(philos);
	printf("%-10ld %-7d is thinking\n", current_time, philos->id);
	if (pthread_mutex_unlock(&philos->data->print_mutex))
		error_exit(philos->data);
}

void	print_fork(t_philo *philos)
{
	long	current_time;

	if (pthread_mutex_lock(&philos->data->print_mutex))
		error_exit(philos->data);
	is_dead(philos);
	current_time = get_time_fs(philos);
	printf("%-10ld %-7d has taken a fork\n", current_time, philos->id);
	if (pthread_mutex_unlock(&philos->data->print_mutex))
		error_exit(philos->data);
}

void	print_eat(t_philo *philos)
{
	long	current_time;

	if (pthread_mutex_lock(&philos->data->print_mutex))
		error_exit(philos->data);
	is_dead(philos);
	current_time = get_time_fs(philos);
	philos->last_meal_time = current_time;
	printf("%-10ld %-7d is eating\n", current_time, philos->id);
	if (pthread_mutex_unlock(&philos->data->print_mutex))
		error_exit(philos->data);
	ft_usleep(philos->data->t_teat, philos);
	philos->last_meal_time = current_time;
}

void	print_sleep(t_philo *philos)
{
	long	current_time;

	if (pthread_mutex_lock(&philos->data->print_mutex))
		error_exit(philos->data);
	is_dead(philos);
	current_time = get_time_fs(philos);
	if (current_time == -1)
		return (perror("gettimeofday"), exit(1));
	printf("%-10ld %-7d is sleeping\n", current_time, philos->id);
	if (pthread_mutex_unlock(&philos->data->print_mutex))
		error_exit(philos->data);
	ft_usleep(philos->data->t_tsleep, philos);
}

void	print_die(t_philo *philos)
{
	long	current_time;

	current_time = get_time_fs(philos);
	if (current_time == -1)
		return (perror("gettimeofday"), exit(1));
	printf("\033[91m%-10ld %-7d died\n\033[0m", current_time, philos->id);
	if (pthread_mutex_unlock(&philos->data->print_mutex))
		error_exit(philos->data);
}
