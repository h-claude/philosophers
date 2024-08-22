/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:01:52 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/22 10:33:25 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"
#include "signal.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	if (argc == 5 || argc == 6)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (1);
		if (parse_argv(argv, data))
		{
			printf("Give good values\n");
			return (free(data), 1);
		}
		i = init_philos_and_forks(data);
		if (i == 1)
			return (printf("Error init philos\n"), free(data), 1);
		else if (i == 2)
			return (free(data), 1);
		if (start_simulation(data))
			return (printf("Error start simulation\n"), free(data), 1);
		free(data);
	}
	else
		printf("Wrong number of arguments\n");
}
