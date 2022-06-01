/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjhin <mjhin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:18:08 by mjhin             #+#    #+#             */
/*   Updated: 2022/03/09 13:44:58 by mjhin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

long int	ft_time_ms(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_exit(char *str, int i)
{
	printf("%s\n", str);
	return (i);
}

void	ft_usleep(long int time_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = ft_time_ms();
	while ((ft_time_ms() - start_time) < time_ms)
		usleep(100);
}

void	print_str(char *str, t_philo *philo, int type)
{
	long int	time;

	sem_wait(philo->data->print);
	time = ft_time_ms() - philo->data->time_all;
	printf("%ld ms Philo %d %s\n", time, philo->id, str);
	if (type == 1)
	{
		philo->n_eat++;
		philo->t_last_eat = ft_time_ms();
	}
	else if (type == 2)
		return ;
	sem_post(philo->data->print);
}
