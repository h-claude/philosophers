/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:46:48 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/16 20:18:25 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	parse_argv(char **argv, t_data *data)
{
	data->philo_nbr = get_good_value(argv[1]);
	if (data->philo_nbr < 1)
		return (free(data), 1);
	data->t_tdie = get_good_value(argv[2]) * 1000;
	if (data->t_tdie < 1)
		return (free(data), 1);
	data->t_teat = get_good_value(argv[3]) * 1000;
	if (data->t_teat < 1)
		return (free(data), 1);
	data->t_tsleep = get_good_value(argv[4]) * 1000;
	if (data->t_tsleep < 1)
		return (free(data), 1);
	if (argv[5])
	{
		data->nbr_eat_limit = get_good_value(argv[5]);
		if (data->nbr_eat_limit < 1)
			return (free(data), 1);
	}
	else
		data->nbr_eat_limit = -1;
	data->philos_die = false;
	return (0);
}
