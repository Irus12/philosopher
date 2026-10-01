
#include "philo.h"

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
	
	if(no_meal_time >= time_to_die)
	{
		//end_simulation
		//pthread_mutex_unlock(philo->left_fork);
		//pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	return (0);
}


void	monitor(t_philo *philo_tab)
{
	int	i;

	while(1)
	{
		i = 0;
		while(i < philo_tab->data->philo_number)
		{
			if(philo_died(&philo_tab[i]) == 1)
			{
				print_action("died", &philo_tab[i]);
				pthread_mutex_lock(&philo_tab->data->death_lock);
				philo_tab[i].data->philo_died = 1;
				pthread_mutex_unlock(&philo_tab->data->death_lock);
				return ;
			}
			i++;
		}
	}
	usleep(0);
}