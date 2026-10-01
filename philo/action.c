/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 15:52:48 by nschilli          #+#    #+#             */
/*   Updated: 2026/10/01 01:50:27 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	print_action("is eating", philo);
	
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time() - philo->data->start_time;
	philo->meals_count++;
	pthread_mutex_unlock(&philo->meal_lock);
	
	usleep(philo->data->time_to_eat * 1000);
	
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);

}

void	thinking(t_philo *philo)
{
	print_action("is thinking", philo);
	usleep(0); //chepa
}

void	sleeping(t_philo *philo)
{
	print_action("is sleeping", philo);
	usleep(philo->data->time_to_sleep * 1000);
}

/*
update death_occured à chaque check
*/

static int has_death_occured(t_philo *philo)
{
	int		death_occured;

	pthread_mutex_lock(&philo->data->death_lock);
	death_occured = philo->data->philo_died;
	pthread_mutex_unlock(&philo->data->death_lock);
	return (death_occured);
}

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while(has_death_occured(philo) == 0)
	{
		if (has_death_occured(philo) == 1)
			break;
		eating(philo);
		if (has_death_occured(philo) == 1)
			break;
		thinking(philo);
		if (has_death_occured(philo) == 1)
			break;
		sleeping(philo);
	}
	return NULL;
}
