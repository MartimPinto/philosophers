/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:19:48 by mcarneir          #+#    #+#             */
/*   Updated: 2023/10/20 14:54:30 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	is_full(t_philo *philo)
{
	if (philo->eat_cont >= philo->data->meals_num
		&& philo->data->meals_num != 0 && !philo->full)
	{
		philo->data->philos_full++;
		philo->full = true;
		if (philo->data->philos_full == philo->data->philo_num)
			philo->data->finished = true;
	}
}

bool	is_dead(t_philo *philo)
{
	bool	dead;

	dead = false;
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(&philo->data->finish_lock);
	if (get_time() >= philo->time_to_die || philo->data->finished)
	{
		if (!philo->data->finished)
			messages(philo, DEATH);
		philo->data->finished = true;
	}
	pthread_mutex_lock(&philo->data->lock);
	is_full(philo);
	dead = philo->data->finished;
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(&philo->data->finish_lock);
	pthread_mutex_unlock(&philo->lock);
	return (dead);
}

bool	is_one(t_philo *philo)
{
	if (philo->data->philo_num == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
		messages(philo, FORK);
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
		messages(philo, THINKING);
		while (!is_dead(philo))
			;
		return (true);
	}
	return (false);
}
