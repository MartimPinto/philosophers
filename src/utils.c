/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:26:31 by mcarneir          #+#    #+#             */
/*   Updated: 2023/10/20 14:54:14 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_atol(const char *nptr)
{
	long	res;
	long	sign;

	res = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
		sign *= -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + *nptr - '0';
		nptr++;
	}
	return (res * sign);
}

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	messages(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->data->write);
	if (status == DEATH)
		printf("%lu %lu died\n",
			get_time() - philo->data->start_time, philo->id);
	else if (status == EATING)
		printf("%lu %lu is eating\n",
			get_time() - philo->data->start_time, philo->id);
	else if (status == SLEEPING)
		printf("%lu %lu is sleeping\n",
			get_time() - philo->data->start_time, philo->id);
	else if (status == THINKING)
		printf("%lu %lu is thinking\n",
			get_time() - philo->data->start_time, philo->id);
	else if (status == FORK)
		printf("%lu %lu has taken a fork\n",
			get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->write);
}

void	ft_usleep(t_philo *philo, uint64_t time)
{
	if ((get_time() + time) >= philo->time_to_die)
		usleep((philo->time_to_die - get_time()) * 1000);
	else
		usleep(time * 1000);
}
