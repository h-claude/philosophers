/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:46:48 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/14 14:24:40 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	parse_argv(char **argv, t_data *data)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->nbr_philo = get_good_value(argv[1]);
	if (data->nbr_philo < 1)
		return (free(data), 1);
	data->t_tdie = get_good_value(argv[2]);
	if (data->t_tdie < 1)
		return (free(data), 1);
	data->t_teat = get_good_value(argv[3]);
	if (data->t_teat < 1)
		return (free(data), 1);
	data->t_tsleep = get_good_value(argv[4]);
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
	return (0);
}
