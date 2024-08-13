/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:34:39 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/13 21:39:25 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

typedef pthread_mutex_t	t_mtx;
typedef	struct	s_data	t_data; 


typedef struct	s_fork
{
	t_mtx	fork;
	long 	fork_id;
}	t_fork;

typedef struct	s_philo
{
	int			id;
	pthread_t	thread_id;
	long		meals_counter;
	long		last_meal_time; 
	int			firs_fork;
	int			last_fork;
	bool		done;
	t_data		*data;
}	t_philo;

typedef struct	s_data
{
	long	nbr_philo;
	long	t_tdie;
	long	t_teat;
	long	t_tsleep;
	long	nbr_eat_limit;
	t_fork	*forks;
	t_philo	*philos;
}	t_data;

long	ft_atol(const char *str);
int		ft_isnumber(char *str);

#endif