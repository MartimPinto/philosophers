/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:44:13 by mcarneir          #+#    #+#             */
/*   Updated: 2023/10/20 14:55:31 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	sleeping(t_philo *philo)
{
	if (!is_dead(philo) && philo->status != SLEEPING)
	{
		philo->status = SLEEPING;
		messages(philo, philo->status);
		ft_usleep(philo, philo->data->sleep_time);
	}
}

void	thinking(t_philo *philo)
{
	if (philo->data->philo_num % 2 != 0 && philo->status != THINKING)
	{
		if (!is_dead(philo))
		{
			philo->status = THINKING;
			messages(philo, philo->status);
			ft_usleep(philo, philo->data->eat_time);
		}
	}
	else if (philo->data->philo_num % 2 == 0 && philo->status != THINKING)
	{
		if (!is_dead(philo))
		{
			philo->status = THINKING;
			messages(philo, philo->status);
			ft_usleep(philo, 5);
		}
	}
}

void	eating(t_philo *philo)
{
	if (!take_forks(philo))
		return ;
	pthread_mutex_lock(&philo->lock);
	philo->time_to_die = get_time() + philo->data->death_time;
	pthread_mutex_unlock(&philo->lock);
	philo->status = EATING;
	messages(philo, philo->status);
	philo->eat_cont++;
	ft_usleep(philo, philo->data->eat_time);
	drop_forks(philo);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->lock);
	philo->time_to_die = philo->data->start_time + philo->data->death_time;
	pthread_mutex_unlock(&philo->lock);
	if (philo->id % 2 == 0 || philo->id == philo->data->philo_num)
		thinking(philo);
	if (is_one(philo))
		return (NULL);
	while (!is_dead(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
