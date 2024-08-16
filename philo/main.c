/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:01:52 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/14 14:37:41 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int main(int argc, char **argv)
{
	t_data	*data;
	if (argc == 5 || argc == 6)
	{
		parse_argv(argv, data);
		if (init_philos(data))
			return (free(data), 1);
		// start_simulation(data);
		// free_data(data);
	}
	else
	{
		// not good !
	}
}
