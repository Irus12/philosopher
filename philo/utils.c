/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 18:19:26 by nschilli          #+#    #+#             */
/*   Updated: 2026/10/01 21:23:59 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_action(char *msg, t_philo *philo)
{
	if(has_death_occured(philo) == 0) //TODO OK POUR L'INSTANT
	{
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%ld %d %s \n",
		get_time() - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
	}
}
