/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tread.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjhin <mjhin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:02:55 by mjhin             #+#    #+#             */
/*   Updated: 2022/03/04 17:09:46 by mjhin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_str("has taken a fork", philo, 0);
	pthread_mutex_lock(&philo->r_philo->fork);
	print_str("has taken a fork", philo, 0);
	print_str("is eating", philo, 1);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->r_philo->fork);
}

void	*philo_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->n_philos == 1)
	{
		print_str("has taken a fork", philo, 0);
		ft_usleep(philo->data->t_dead);
	}
	else
	{
		if (philo->id % 2 == 0)
			usleep(500);
		while (!philo->data->dead && !philo->data->eat_all)
		{
			philo_eat(philo);
			print_str("is sleeping", philo, 0);
			ft_usleep(philo->data->t_sleep);
			print_str("is thinking", philo, 0);
		}
	}
	return (NULL);
}

int	thread_create(t_data *data)
{
	size_t	i;

	i = 0;
	data->time_all = 0;
	data->time_all = ft_time_ms();
	data->dead = 0;
	while (i < data->n_philos)
	{
		data->philos[i].t_last_eat = data->time_all;
		if (pthread_create(&data->philos[i].thread_id, NULL,
				&philo_thread, &data->philos[i]) != 0)
			return (ft_exit("Bad pthread_create!", 1));
		i++;
	}
	return (0);
}
