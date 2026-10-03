/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 15:52:48 by nschilli          #+#    #+#             */
/*   Updated: 2026/10/03 14:25:25 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action("has taken a fork", philo);
	ft_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
	return ;
}

/*

*/
static void	eating(t_philo *philo)
{
	if (philo->data->philo_number == 1)
		return (one_philo(philo));
	else if (philo->id % 2 == 0)
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
	print_action("is eating", philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time() - philo->data->start_time;
	philo->meals_count++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	thinking(t_philo *philo)
{
	print_action("is thinking", philo);
}

static void	sleeping(t_philo *philo)
{
	print_action("is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while ((has_death_occured(philo)) == 0)
	{
		eating(philo);
		if (has_death_occured(philo) == 1)
			break ;
		thinking(philo);
		if (has_death_occured(philo) == 1)
			break ;
		sleeping(philo);
	}
	return (NULL);
}
