*This project has been created as part of the 42 curriculum by nschilli.*

# Philosophers

## Description

This project is a C implementation of the dining philosophers concurrency problem. Philosophers sit around a table and repeatedly think, eat, and sleep. Each philosopher needs two neighboring forks to eat, and each fork is shared with a neighboring philosopher.

The goal is to coordinate philosopher threads and fork mutexes so that the simulation can report each philosopher's actions, detect when a philosopher dies from waiting too long to eat, and optionally stop after every philosopher has eaten a specified number of times.

## Instructions

### Build

From the repository root, run:

```sh
make
```

This builds the `philo` executable with the `-pthread` option. To remove object files, run `make clean`. To remove object files and the executable, run `make fclean`.

### Run

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

All time values are in milliseconds. The final meal-count argument is optional. When supplied, the simulation stops after every philosopher has eaten at least that many times. Without it, the simulation continues until a philosopher dies.

Example:

```sh
./philo 4 410 200 200 5
```

This starts four philosophers with a 410 ms time-to-die, 200 ms eating time, 200 ms sleeping time, and a five-meal limit per philosopher. The program prints elapsed time, philosopher ID, and the current action to standard output.

## Resources

https://github.com/DeRuina/philosophers
https://youtu.be/UGQsvVKwe90?si=dICZi5Me0zNJyff2
https://youtu.be/zOpzGHwJ3MU?si=DSLKN6oH2Nods3Nl
https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2

### AI usage

AI assistance was only used for debug, education purpuses, and to help draft this README.
