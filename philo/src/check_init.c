/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjhin <mjhin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 13:24:47 by mjhin             #+#    #+#             */
/*   Updated: 2022/03/07 14:36:24 by mjhin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_atoi(const char *str)
{
	size_t	i;
	int		p;
	long	chislo;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	p = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			p = -1;
		i++;
	}
	chislo = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (chislo * 10 + (str[i] - '0') < chislo && p == -1)
			return (0);
		else if (chislo * 10 + (str[i] - '0') < chislo && p == 1)
			return (-1);
		chislo = chislo * 10 + (str[i] - '0');
		i++;
	}
	return (p * chislo);
}

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (c);
	return (0);
}

static int	check_arg(char *str)
{
	size_t			i;
	unsigned long	result;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			if (str[i] != '0')
				return (1);
	if (!str[i])
		return (1);
	result = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		if (result * 10 + (str[i] - '0') > 2147483647)
			return (1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (0);
}

static void	init_data(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].thread_id = NULL;
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].n_eat = 0;
		if (i + 1 == data->n_philos)
			data->philos[i].r_philo = &data->philos[0];
		else
			data->philos[i].r_philo = &data->philos[i + 1];
		if (i == 0)
			data->philos[i].l_philo = &data->philos[data->n_philos - 1];
		else
			data->philos[i].l_philo = &data->philos[i - 1];
		pthread_mutex_init(&data->philos[i].fork, NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
}

int	check_init(int argc, char **argv, t_data *data)
{
	size_t	i;

	i = 0;
	while (argv[++i])
	{
		if (check_arg(argv[i]))
			return (ft_exit("Bad check arg!", 1));
	}
	data->n_philos = ft_atoi(argv[1]);
	data->t_dead = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->eat_all = 0;
	data->dead = 0;
	data->n_eat = -1;
	if (argc == 6)
		data->n_eat = ft_atoi(argv[5]);
	data->philos = (t_philo *)malloc(data->n_philos * sizeof(t_philo));
	if (!data->philos)
		return (ft_exit("Bad malloc data->philos!", 1));
	init_data(data);
	return (0);
}
