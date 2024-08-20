/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:34:39 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/20 13:18:07 by hclaude          ###   ########.fr       */
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
	t_mtx	*fork;
	long	fork_id;
}	t_fork;

typedef struct	s_philo
{
	int			id;
	pthread_t	thread_id;
	long		meals_counter;
	long		last_meal_time;
	bool		done;
	t_fork		*r_fork;
	t_fork		*l_fork;
	t_data		*data;
}	t_philo;

typedef struct	s_data
{
	long			philo_nbr;
	long			t_tdie;
	long			t_teat;
	long			t_tsleep;
	long			nbr_eat_limit;
	bool			philos_die;
	long			start_time;
	t_philo			*philos;
	struct s_fork	*forks;
}	t_data;

typedef enum	e_mutex_code
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
}	t_mutex_code;

typedef enum e_thread_code
{
	CREATE,
	JOIN,
	DETACH,
}	t_thread_code;

typedef enum e_philo_status
{
	THINK,
	FORK,
	EAT,
	SLEEP,
}	t_philo_status;


void	free_data(t_data *data);
long	get_good_value(char *str);
int		parse_argv(char **argv, t_data *data);
int		init_philos(t_data *data);
void	*philo_function(void *data_void);
int		start_simulation(t_data *data);
void	manage_thread(t_philo *philo, t_thread_code code);
int		print_status_philos(t_philo *philos, t_philo_status code);
int		manage_mutex(t_mtx *mutex, t_mutex_code code, t_philo *philo);
int		is_dead(t_philo *philo);
long	get_current_time(void);
long	get_time_fs(t_philo *philo);
void	ft_usleep(long time, t_philo *philo);

#endif