/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 01:21:40 by nschilli          #+#    #+#             */
/*   Updated: 2026/09/30 23:50:27 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
valgrind --elgrind
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

		while(i < length)
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

int main(int argc, char **argv)
{
	t_philo			*philo_tab;
	t_data			*data;
	pthread_mutex_t	*forks;

	if (valid_args(argc, argv) == 0)
		return (-1);
	data = data_parsing(argc, argv);
	if (!data)
		return (-1);
	philo_tab = ft_calloc(data->philo_number, sizeof(t_philo));
	forks = ft_calloc(data->philo_number, sizeof(pthread_mutex_t));
	//check if empty et free
	philo_init(philo_tab, data, forks, data->philo_number);
	data->start_time = get_time();
	philo_launch(philo_tab, data->philo_number);
	monitor(philo_tab);
	philo_join(philo_tab, data->philo_number);
	end_simulation(philo_tab, data);

	return (0);
}

/*
int main(int argc, char **argv)
{
	int				N = 3;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	
	int		number_philo = argv[1];
	long	time_to_die = argv[2];
	long	time_to_eat = argv[3];
	long	time_to_sleep = argv[4];

	
	philos = ft_calloc(N, sizeof(t_philo) * N);
	forks = ft_calloc(N, sizeof(pthread_mutex_t) * N);

	if (!philos || !forks)
		return (1);

	philo_init(philos, forks, N);
	philo_launch(philos, N);

	philo_join(philos, N);

	free(philos);
	return 0;
}
	*/