/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:34:52 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/20 11:58:40 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	ft_usleep(long time, t_philo *philo)
{
	long	start_time;

	if (philo->data->philos_die)
		exit(1);
	start_time = get_time_fs(philo);
	if (start_time == -1)
		return (perror("gettimeofday"), exit(1));
	if (time > philo->data->t_tdie + 5000)
	{
		philo->data->philos_die = true;
		printf("%ld %d is dead\n", start_time, philo->id);
		exit(1);
	}
	else
		usleep(time);
}

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (perror("gettimeofday"), -1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	get_time_fs(t_philo *philo)
{
	long	time;
	long	current_time;

	current_time = get_current_time();
	if (current_time == -1)
		return (perror("gettimeofday"), -1);
	time = current_time - philo->data->start_time;
	return (time);
}
