/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 07:43:27 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/30 07:43:31 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

time_t	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	someone_died(t_philo *philo)
{
	bool	state;

	pthread_mutex_lock(&(philo->g->death_mutex));
	state = philo->g->someone_died;
	pthread_mutex_unlock(&(philo->g->death_mutex));
	return (state);
}

int	get_input_value(char *str)
{
	int	neg;
	int	num;
	int	i;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] <= ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			neg *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

int	clean_exit(t_global *g, t_philo *philo, t_fork *forks)
{
	if (g)
	{
		if (pthread_mutex_destroy(&g->death_mutex))
			return (EXIT_FAILURE);
		if (pthread_mutex_destroy(&g->philo_mutex))
			return (EXIT_FAILURE);
	}
	if (philo)
		free(philo);
	if (forks)
	{
		if (pthread_mutex_destroy(&forks->fork_mutex))
			return (EXIT_FAILURE);
		free(forks);
	}
	return (EXIT_SUCCESS);
}

int	error_handler(char *msg, t_global *g, t_philo *philo, t_fork *forks)
{
	while (*msg)
		write(2, &*msg++, 1);
	clean_exit(g, philo, forks);
	return (EXIT_FAILURE);
}
