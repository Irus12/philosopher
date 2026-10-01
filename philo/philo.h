#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <limits.h>

/*
	the whole data needed to represent the table
	all philosopher shares the same t_data adress
	so we use mutex to uptade it to prevent race condition
*/
typedef struct s_data
{
	int				philo_number;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				max_meals;
	long			start_time ;
	int				philo_died;
	pthread_mutex_t	death_lock; //protège philo_died
	pthread_mutex_t	*forks_tab;
	pthread_mutex_t	print_lock; //sortie global, tout les threads qui affichent
} t_data;

/*
	each philo has their own attributes so each one
	use a different mutex to uptate their values safely
*/
typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meals_count;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock; //protège meal_count et last_meal
	t_data			*data;
} t_philo;

void	*routine(void *arg);

long	get_time(void);

/* init */
void philo_init(t_philo *philo_tab, t_data *data,
	pthread_mutex_t *forks, int num_philo);
void	philo_launch(t_philo *philo_tab, int num_philo);
void	philo_join(t_philo *philo_tab, int num_philo);

/*	action */
void	eating(t_philo *philo);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	*routine(void *arg);

/* monitor */
void	monitor(t_philo *philo_tab);
int has_death_occured(t_philo *philo);

/* parsing */
int		valid_args(int argc,char **argv);
t_data	*data_parsing(int argc, char **argv);

/* utils*/
long	pos_long_atoi(char *str);
int		pos_int_atoi(char *str);
void	print_action(char *msg, t_philo *philo);
void	*ft_calloc(int nmemb, int size);


#endif
