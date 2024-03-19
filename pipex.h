/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdejo <averdejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:11:00 by averdejo          #+#    #+#             */
/*   Updated: 2024/03/19 19:11:01 by averdejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
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

void	pipex(int argc, char **argv, char **env, t_data *data);
void	processes(t_data *data, int argc, char **argv);
void	middle_processes(t_data *data);
void	first_process(t_data *data, char **argv);

char	*check_access(t_data *data, char **com);
void	get_args(int argc, char **argv, t_data *d);
void	get_path(char **env, t_data *data);
void	execute(t_data *data);
void	init_variables(t_data *data);

void	open_files(int argc, char **argv, t_data *data);
void	here_doc(t_data *data, char **argv);

#endif
