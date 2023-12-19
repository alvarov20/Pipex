#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdio.h> //borrar

typedef struct s_data
{
	int		fd[2];
	int		infile;
	int		outfile;
	int		n_arg;
	char	**args;
	char	**path;
	int		hc;

}			t_data;

void	big_pipex(int argc, char **argv, char **env, t_data *data);
void	processes(t_data *data, char **argv);
void	middle_processes(t_data *data);
void	first_process(t_data *data, char **argv);

char	*check_access(t_data *data, char **com);
void	get_args(int argc, char **argv, t_data *d);
void	get_path(char **env, t_data *data);
void	execute(t_data *data);
void	init_variables(t_data *data);

void	ft_error();
void	here_doc(t_data *data, char **argv);

#endif
