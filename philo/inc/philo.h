/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjhin <mjhin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:03:10 by mjhin             #+#    #+#             */
/*   Updated: 2022/03/07 14:35:32 by mjhin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				n_eat;
	long int		t_last_eat;
	pthread_mutex_t	fork;
	struct s_philo	*r_philo;
	struct s_philo	*l_philo;
	struct s_data	*data;
	pthread_t		thread_id;
}	t_philo;

typedef struct s_data
{
	long int		t_dead;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				n_philos;
	int				eat_all;
	int				dead;
	long int		time_all;
	t_philo			*philos;
	pthread_mutex_t	print;
}	t_data;

int			check_init(int argc, char **argv, t_data *data);
long int	ft_time_ms(void);
int			thread_create(t_data *data);
int			ft_exit(char *str, int i);
void		ft_usleep(long int time_in_ms);
void		print_str(char *str, t_philo *philo, int type);

#endif