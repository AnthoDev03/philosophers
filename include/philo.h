#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_table;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
	pthread_t		monitor;
}					t_philo;

typedef struct s_table
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	long			start_time;
	bool			has_dead;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_table;

// actions.c
void				take_forks(t_philo *ph);
void				go_to_sleep(t_philo *ph);
void				leave_forks(t_philo *ph);

// checks.c
bool				did_everyone_eat_enough(t_table *table);
int					ft_atoi(const char *str);
bool				ft_is_valid_atoi(const char *str);
bool				arguments_valid(int argc, char **argv);
void				*check_deaths(void *void_table);

// init.c
void				init_forks(t_table *table);
void				init_philos(t_table *table);
void				init_table(t_table *table, int ac, char **av);

// miscellaneous.c
long				get_time(void);
int					chrono(t_philo *ph);
void				print_usage(void);
void				ft_usleep(int ms);

// status.c
void				print_eating(t_philo *ph);
void				print_dead(t_philo *ph);
void				print_thinking(t_philo *ph);
void				print_sleeping(t_philo *ph);
void				print_forks(t_philo *ph);

#endif
