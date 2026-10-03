/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 02:08:05 by nschilli          #+#    #+#             */
/*   Updated: 2026/10/03 14:25:34 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
update death_occured à chaque check
*/
int	has_death_occured(t_philo *philo)
{
	int		death_occured;

	pthread_mutex_lock(&philo->data->death_lock);
	death_occured = philo->data->philo_died;
	pthread_mutex_unlock(&philo->data->death_lock);
	return (death_occured);
}

int	has_eaten_enough(t_philo *philo)
{
	int	n_meals;

	pthread_mutex_lock(&philo->meal_lock);
	n_meals = philo->meals_count;
	pthread_mutex_unlock(&philo->meal_lock);
	if (philo->data->max_meals == -1)
		return (0);
	else if (n_meals >= philo->data->max_meals)
		return (1);
	return (0);
}

/*
we pass it &philo[i]
*/
int	philo_died(t_philo *philo)
{
	long	no_meal_time;
	long	time_to_die;

	pthread_mutex_lock(&philo->meal_lock);
	no_meal_time = (get_time() - philo->data->start_time) - philo->last_meal;
	time_to_die = philo->data->time_to_die;
	pthread_mutex_unlock(&philo->meal_lock);
	if (no_meal_time >= time_to_die)
	{
		return (1);
	}
	return (0);
}

void	declare_end(t_philo *philo, int print)
{
	pthread_mutex_lock(&philo->data->death_lock);
	philo->data->philo_died = 1;
	pthread_mutex_lock(&philo->data->print_lock);
	if (print)
		printf("%ld %d died\n", get_time() - philo->data->start_time,
			philo->id);
	pthread_mutex_unlock(&philo->data->print_lock);
	pthread_mutex_unlock(&philo->data->death_lock);
}

void	monitor(t_philo *philo_tab)
{
	int	i;
	int	how_many_reached_max_meal;

	while (1)
	{
		how_many_reached_max_meal = 0;
		i = 0;
		while (i < philo_tab->data->philo_number)
		{
			if (has_eaten_enough(&philo_tab[i]))
				how_many_reached_max_meal++;
			if (philo_died(&philo_tab[i]) == 1)
				return (declare_end(philo_tab, 1));
			if (how_many_reached_max_meal == philo_tab->data->philo_number)
				return (declare_end(philo_tab, 0));
			i++;
		}
		ft_usleep(1);
	}
}
