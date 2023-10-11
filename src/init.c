/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:13:58 by mcarneir          #+#    #+#             */
/*   Updated: 2023/10/11 15:38:12 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	alloc(t_data *data)
{
	data->table = malloc(sizeof(pthread_t) * data->philo_num);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->table || !data->forks || !data->philos)
		return (0);
	return (1);
}

void	init_forks(t_data *data)
{
	uint64_t	i;

	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->philo_num - 1];
	i = 1;
	while (i < data->philo_num)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
		i++;
	}
}

void	init_philos(t_data *data)
{
	uint64_t	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = data->death_time;
		data->philos[i].eat_cont = 0;
		data->philos[i].full = false;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->philo_num = ft_atol(argv[1]);
	data->death_time = ft_atol(argv[2]);
	data->eat_time = ft_atol(argv[3]);
	data->sleep_time = ft_atol(argv[4]);
	if (argc == 6)
		data->meals_num = ft_atol(argv[5]);
	else
		data->meals_num = -1;
	data->finished = false;
	data->dead = 0;
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->finish_lock, NULL);
	return (data);
}

t_data	*init(int argc, char **argv)
{
	t_data	*data;

	data = init_data(argc, argv);
	if (!alloc(data))
		return (NULL);
	init_forks(data);
	init_philos(data);
	return (data);
}
