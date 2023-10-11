/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:57:42 by mcarneir          #+#    #+#             */
/*   Updated: 2023/10/11 12:40:29 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdint.h>
# include <stdbool.h>

# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	uint64_t		id;
	uint64_t		eat_cont;
	bool			full;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*table;
	t_philo			*philos;
	uint64_t		philo_num;
	uint64_t		meals_num;
	bool			finished;
	uint64_t		dead;
	uint64_t		death_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	uint64_t		start_time;
	uint64_t		philos_full;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	pthread_mutex_t	finish_lock;
}	t_data;

//utils//
long		ft_atol(const char *nptr);
uint64_t	get_time(void);
void		messages(char *str, t_philo *philo);
void		ft_usleep(t_philo *philo, uint64_t time);

//checks//
bool		is_dead(t_philo *philo);
bool		is_one(t_philo *philo);
int			parser(char **argv);

//actions//
void		*routine(void *philo_ptr);

//memory//
t_data		*init(int argc, char **argv);
void		free_data(t_data *data);

#endif