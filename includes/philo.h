/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <rsibiet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 13:27:22 by rsibiet           #+#    #+#             */
/*   Updated: 2017/05/04 13:35:01 by ksoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
** MAX_LIFE : Le nombre de points de vie maximum des philosophes.
** EAT_T	: Le nombre de SECONDES ques met un philosophe à manger.
** REST_T	: Le nombre de SECONDES pendant lesquels un philosophe se repose.
** THINK_T	: Le nombre de SECONDES pendant lesquels un philosophe réfléchit.
** TIMEOUT	: Le temps en SECONDES après lesquels la simulation s'interrompt en
** affichant "Now, it is time... To DAAAANCE!!!" si aucun philosophe n'est mort
** de faim (le dîner en cours doit rester visible à lécran pour faire le
** bilan). L’appui d’une touche provoque la libération des ressources et l’arrêt
** complet du programme.
*/

# define MAX_LIFE 10
# define EAT_T 1
# define REST_T 1
# define THINK_T 1
# define EAT_M 1 << 4
# define REST_M 1 << 3
# define THINK_M 1 << 2
# define TIMEOUT 60
# define BAG_M	1
# define N_PHILO 7
# define R_MUTEX 1
# define L_MUTEX 2
# define M_MUTEX 4
# define WIDTH 1500
# define HEIGHT 1000
# define IMGPOS HEIGHT / 2 - size[1]
# include "../libft/libft.h"
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <pthread.h>
# include <stdint.h>
# include <limits.h>
# include <mlx.h>

typedef struct			s_philo
{
	pthread_t			thread;
	pthread_mutex_t		mutex;
	struct s_philo		*left;
	struct s_philo		*right;
	uint16_t			stats;
	int16_t				life;
	int					n;
	int					callme;
	int					lastcall;
}						t_philo;

typedef struct			s_mlx
{
	void				*ptr;
	void				*win;
	void				*img;
	int					alive;
	time_t				time;
}						t_mlx;

typedef struct			s_states
{
	char				*status;
	int					mask;
	unsigned int		color;
	char				*stick;
}						t_states;

extern	t_philo			g_tp[7];
extern	t_mlx			g_mlx;
/*
** threads.c
*/
void					*enjoy(void *var);
int						trylocks(t_philo *ph, int mask);
int						is_critical(t_philo *ph);
/*
** init.c
*/
void					init(t_philo *tp, t_mlx *mlx);

/*
** rest.c
*/
int						do_rest(t_philo *ph, time_t *timealive);

/*
** think.c
*/
int						do_think(t_philo *ph, time_t *timealive);

/*
** eat.c
*/
int						do_eat(t_philo *ph, time_t *timealive);

/*
** graphic.c
*/
void					do_images(t_mlx *g_mlx, char **pictures, char *path);
#endif
