/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 07:42:47 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/30 07:50:21 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

unsigned long	get_time_elapsed(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - philo->start_time.tv_sec) * 1000
		+ (current_time.tv_usec - philo->start_time.tv_usec) / 1000);
}

static bool	philo_init(t_global *g, t_philo **philos, t_fork **forks)
{
	t_philo	*philo;
	int		i;

	*philos = (t_philo *)malloc(sizeof(t_philo) * g->a.n_philo);
	*forks = (t_fork *)malloc(sizeof(t_fork) * g->a.n_philo);
	if (!philos || !forks)
		return (false);
	i = -1;
	while (++i < g->a.n_philo)
	{
		philo = &(*philos)[i];
		philo->g = g;
		philo->id = i + 1;
		philo->last_meal = get_timestamp();
		philo->loop = 0;
		philo->right_fork = &((*forks)[i]);
		philo->left_fork = &((*forks)[i + 1]);
		if (philo->id == g->a.n_philo)
			philo->left_fork = &((*forks)[0]);
		philo->right_fork_state = DOWN;
		philo->left_fork_state = DOWN;
		pthread_mutex_init(&(philo->left_fork->fork_mutex), NULL);
		gettimeofday(&(philo->start_time), NULL);
	}
	return (true);
}

static bool	global_init(t_global *g, t_args a)
{
	g->a = a;
	g->someone_died = false;
	if (pthread_mutex_init(&(g->philo_mutex), NULL))
		return (false);
	if (pthread_mutex_init(&(g->death_mutex), NULL))
		return (false);
	if (pthread_mutex_init(&(g->print_mutex), NULL))
		return (false);
	return (true);
}

static bool	args_init(t_args *a, int argc, char **argv)
{
	a->n_philo = get_input_value(argv[1]);
	a->time_to_die = get_input_value(argv[2]) * 1000;
	a->time_to_eat = get_input_value(argv[3]) * 1000;
	a->time_to_sleep = get_input_value(argv[4]) * 1000;
	a->n_loop = -2;
	if (argc == 6)
		a->n_loop = get_input_value(argv[5]);
	if (a->n_philo < 0 || a->time_to_die < 0 || a->time_to_eat < 0
		|| a->time_to_sleep < 0 || a->n_loop < -2 || a->n_loop == -1
		|| a->n_loop == 0)
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_args		a;
	t_global	g;
	t_philo		*philos;
	t_fork		*forks;

	if (argc < 5 || argc > 6)
		return (error_handler("Wrong number of args\n", NULL, NULL, NULL));
	if (!args_init(&a, argc, argv))
		return (error_handler("Invalid input\n", &g, NULL, NULL));
	if (!global_init(&g, a))
		return (error_handler("Mutex init failure\n", &g, NULL, NULL));
	if (!philo_init(&g, &philos, &forks))
		return (error_handler("Malloc failure\n", &g, philos, forks));
	if (!thread_handler(&g, &philos))
		return (error_handler("Some errors with threads\n", &g, philos, forks));
	return (clean_exit(&g, philos, forks));
}
