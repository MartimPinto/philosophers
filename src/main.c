/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:05:09 by mcarneir          #+#    #+#             */
/*   Updated: 2023/10/10 13:17:39 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_threads(t_data *data)
{
	uint64_t	i;

	i = 0;
	data->start_time = get_time();
	if (data->start_time == 0)
		return (1);
	pthread_mutex_lock(&data->lock);
	while (i < data->philo_num)
	{
		if (pthread_create(&data->table[i], NULL, &routine, &data->philos[i]))
			return (1);
		i++;
	}
	pthread_mutex_unlock(&data->lock);
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_join(data->table[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if ((argc != 5 && argc != 6) || parser(argv) != 0)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	data = init(argc, argv);
	if (!data)
	{
		free_data(data);
		return (1);
	}
	init_threads(data);
	free_data(data);
}
