/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:46:48 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/13 21:41:47 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	parse_argv(char **argv, t_data *data)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (!ft_isnumber(argv[1]));
		return (free(data), 1);
	data->nbr_philo = ft_atol(argv[1]);
	if (data->nbr_philo < 1)
		return (free(data), 1);
	
}
