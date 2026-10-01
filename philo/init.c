/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 15:55:41 by nschilli          #+#    #+#             */
/*   Updated: 2026/09/30 17:08:50 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_init(t_philo *philo_tab, t_data *data, pthread_mutex_t *forks, int num_philo)
{	
	int	i;

	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
			i++;
	}
	i = 0;
	while (i < num_philo)
	{
		philo_tab[i].id = i + 1;
		philo_tab[i].left_fork = &forks[i];
		philo_tab[i].right_fork = &forks[(i + 1) % num_philo];
		philo_tab[i].data = data;
		i++;
	}
}

void	philo_launch(t_philo *philo_tab, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		pthread_create(&philo_tab[i].thread, NULL, routine, &philo_tab[i]);
		i++;
	}
}


void	philo_join(t_philo *philo_tab, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
		pthread_join(philo_tab[i++].thread, NULL);
}