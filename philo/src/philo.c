/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 01:21:40 by nschilli          #+#    #+#             */
/*   Updated: 2026/10/03 14:25:41 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
*/
void	*ft_calloc(int nmemb, int size)
{
	void	*out;
	int		length;
	int		i;
	char	*t;

	i = 0;
	length = nmemb * size;
	out = (void *) malloc(length);
	t = (char *)out;
	if (!out)
		return (NULL);
	while (i < length)
	{
		t[i] = 0;
		i++;
	}
	return (out);
}

void	end_simulation(t_philo *philo_tab, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_number)
	{
		pthread_mutex_destroy(&data->forks_tab[i]);
		pthread_mutex_destroy(&philo_tab[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->print_lock);
	free(philo_tab);
	free(data->forks_tab);
	free(data);
}

int	main(int argc, char **argv)
{
	t_philo			*philo_tab;
	t_data			*data;

	if (valid_args(argc, argv) == 0)
		return (-1);
	data = data_parsing(argc, argv);
	if (!data)
		return (-1);
	philo_tab = ft_calloc(data->philo_number, sizeof(t_philo));
	if (!philo_tab)
		return (-1);
	philo_init(philo_tab, data, data->forks_tab, data->philo_number);
	data->start_time = get_time();
	philo_launch(philo_tab, data->philo_number);
	monitor(philo_tab);
	philo_join(philo_tab, data->philo_number);
	end_simulation(philo_tab, data);
	return (0);
}
