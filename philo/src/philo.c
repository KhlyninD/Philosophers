/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjhin <mjhin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:04:11 by mjhin             #+#    #+#             */
/*   Updated: 2022/03/07 15:36:32 by mjhin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_dead_eat(t_data *data)
{
	size_t	i;

	while (!data->eat_all)
	{
		i = 0;
		while (!data->dead && i < data->n_philos)
		{
			if (!(ft_time_ms() - data->philos[i].t_last_eat
					< (long int)data->t_dead))
			{
				print_str("died", &data->philos[i], 2);
				break ;
			}
			i++;
			usleep(100);
		}
		if (data->dead)
			break ;
		i = 0;
		while (data->n_eat != -1 && i < data->n_philos
			&& data->philos[i].n_eat >= data->n_eat)
			i++;
		if (i == data->n_philos)
			data->eat_all = 1;
	}
}

void	exit_philo(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (data->philos[i].thread_id)
			pthread_detach(data->philos[i].thread_id);
		i++;
	}
	i = 0;
	while (i < data->n_philos)
		pthread_mutex_destroy(&data->philos[i++].fork);
	pthread_mutex_destroy(&data->print);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_exit("Bad arguments!", 1));
	if (check_init(argc, argv, &data))
		return (ft_exit("Bad init argument!", 2));
	if (thread_create(&data))
	{
		ft_exit("Bad thread create!", 3);
		exit_philo(&data);
		return (3);
	}
	check_dead_eat(&data);
	exit_philo(&data);
	return (0);
}
