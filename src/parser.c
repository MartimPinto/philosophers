/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:51:13 by mcarneir          #+#    #+#             */
/*   Updated: 2023/10/10 13:19:35 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

static int	check_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (1);
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	check_value(char *str)
{
	long	tmp;

	tmp = ft_atol(str);
	if (check_number(str) != 0)
		return (1);
	if (tmp <= 0 || tmp > 4294967295)
		return (1);
	return (0);
}

int	parser(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (check_value(argv[i]) != 0)
			return (1);
		i++;
	}
	if (argv[2][0] == '0' && !argv[2][1])
		return (1);
	return (0);
}
