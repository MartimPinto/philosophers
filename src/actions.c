/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:44:13 by mcarneir          #+#    #+#             */
/*   Updated: 2023/10/11 15:46:34 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	messages(TAKE_FORKS, philo);
	pthread_mutex_lock(philo->l_fork);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	messages(TAKE_FORKS, philo);
	return (true);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (!is_dead(philo))
	{
		messages(SLEEPING, philo);
		ft_usleep(philo, philo->data->sleep_time);
	}
}

void	eating(t_philo *philo)
{
	if (!take_forks(philo))
		return ;
	if (!is_dead(philo))
	{
		messages(EATING, philo);
		pthread_mutex_lock(&philo->lock);
		philo->eat_cont++;
		philo->time_to_die = get_time() + philo->data->death_time;
		pthread_mutex_unlock(&philo->lock);
		ft_usleep(philo, philo->data->eat_time);
	}
	drop_forks(philo);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->lock);
	philo->time_to_die = philo->data->start_time + philo->data->death_time;
	pthread_mutex_unlock(&philo->lock);
	if (is_one(philo))
		return (NULL);
	if (philo->id % 2 == 0)
	{
		messages(THINKING, philo);
		ft_usleep(philo, 100);
	}
	while (!is_dead(philo))
	{
		eating(philo);
		if (!is_dead(philo))
			messages(THINKING, philo);
	}
	return (NULL);
}
