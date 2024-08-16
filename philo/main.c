/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:01:52 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/16 21:00:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int main(int argc, char **argv)
{
	t_data	*data;
	
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (argc == 5 || argc == 6)
	{
		parse_argv(argv, data);
		if (init_philos(data))
			return (free(data), 1);
		printf("philo_nbr = %li\nt_tdie = %li\nt_teat = %li\nt_tsleep = %li\nnbr_eat_limit = %li\n",
			data->philo_nbr, data->t_tdie, data->t_teat, data->t_tsleep, data->nbr_eat_limit);
		start_simulation(data);
		// free_data(data);
	}
	else
	{
		// not good !
	}
}
