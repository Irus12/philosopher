/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 15:52:48 by nschilli          #+#    #+#             */
/*   Updated: 2026/10/01 21:47:46 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action("has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
		print_action("has taken a fork", philo);
	}
	else
	{
		if (philo->id == philo->data->philo_number)
		{
			pthread_mutex_lock(philo->left_fork);
			print_action("has taken a fork", philo);
			pthread_mutex_lock(philo->right_fork);
			print_action("has taken a fork", philo);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			print_action("has taken a fork", philo);
			pthread_mutex_lock(philo->left_fork);
			print_action("has taken a fork", philo);
		}
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
	//usleep(0); //chepa
}

void	sleeping(t_philo *philo)
{
	print_action("is sleeping", philo);
	usleep(philo->data->time_to_sleep * 1000);
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while(has_death_occured(philo) == 0)
	{
		eating(philo);
		thinking(philo);
		sleeping(philo);
	}
	return NULL;
}
