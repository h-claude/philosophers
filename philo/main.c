/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:01:52 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/21 17:52:22 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"
#include "signal.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (argc == 5 || argc == 6)
	{
		if (parse_argv(argv, data))
		{
			printf("Give good values\n");
			return (free(data), 1);
		}
		if (init_philos_and_forks(data))
			return (printf("Error init philos\n"), free(data), 1);
		if (start_simulation(data))
			return (printf("Error start simulation\n"), free(data), 1);
		free(data);
	}
	else
		printf("Wrong number of arguments\n");
}
