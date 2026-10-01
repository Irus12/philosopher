/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 18:08:07 by nschilli          #+#    #+#             */
/*   Updated: 2026/09/30 17:02:18 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int valid_argc(int argc)
{
	if ( argc < 5 || argc > 6)
	{
		write(2, "Invalid number of arguments", 27);
		return (0);
	}
	return (1);
}
/*
	argv:
	[0] name
	[1] int num philo
	[2]	long die
	[3] long eat
	[4] long sleep
	[5]	int max meals
*/
int	valid_args(int argc,char **argv)
{
	long tmp;
	int i;

	i = 1;
	if (valid_argc(argc) == 0)
		return (0);
	while(i < argc)
	{
		tmp = pos_long_atoi(argv[i]);
		if (tmp == -1)
		{
			write(2, "Invalid argument", 16);
			return (0);
		}
		if (i == 1 || i == 5)
		{
			if (tmp > INT_MAX)
			{
				write(2, "Invalid argument", 16);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
/*
crée un t_data et le donne à tous les philos
*/
t_data	*data_parsing(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (argc == 5 || argc == 6)
	{
		data->philo_number = pos_int_atoi(argv[1]);
		data->time_to_die = pos_long_atoi(argv[2]);
		data->time_to_eat = pos_long_atoi(argv[3]);
		data->time_to_sleep = pos_long_atoi(argv[4]);
		data->max_meals = -1;
	}
	if (argc == 6)
		data->max_meals = pos_int_atoi(argv[5]);
	data->forks_tab = ft_calloc(data->philo_number, sizeof(pthread_mutex_t));
		if(!data->forks_tab)
			return NULL;
	return data;
}
