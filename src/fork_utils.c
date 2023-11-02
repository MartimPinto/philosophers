/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:10:00 by mcarneir          #+#    #+#             */
/*   Updated: 2023/10/20 14:53:13 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
	}
}

bool	take_fork_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
		return (false);
	}
	messages(philo, FORK);
	pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
	if (is_dead(philo))
	{
		drop_forks(philo);
		return (false);
	}
	messages(philo, FORK);
	return (true);
}

bool	take_fork_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
		return (false);
	}
	messages(philo, FORK);
	pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
	if (is_dead(philo))
	{
		drop_forks(philo);
		return (false);
	}
	messages(philo, FORK);
	return (true);
}

bool	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (!take_fork_even(philo))
			return (false);
	}
	else
	{
		if (!take_fork_odd(philo))
			return (false);
	}
	return (true);
}
