#include "pipex.h"

void	here_doc(t_data *data, char **argv)
{
	char	*str;

	str = NULL;
	data->infile = open("/tmp/.file", O_RDWR | O_APPEND | O_CREAT, 0644);
	data->hc = 1;
	while (1)
	{
		str = get_next_line(STDIN_FILENO);
		if (ft_strncmp(str, argv[2], ft_strlen(argv[2])) == 0
			&& (ft_strlen(str) - 1) == ft_strlen(argv[2]))
			break ;
		write(data->infile, str, ft_strlen(str));
	}
}

void	processes(t_data *data, int argc, char **argv)
{
	pid_t	pid;

	pid = 0;
	pipe(data->fd);
	dup2(data->infile, STDIN_FILENO);
	close(data->infile);
	first_process(data, argv);
	waitpid(pid, NULL, 0);
	data->n_arg++;
	while (data->args[data->n_arg + 1] != NULL)
	{
		middle_processes(data);
		data->n_arg++;
	}
	if (access("/tmp/.file", F_OK) == 0)
		unlink("/tmp/.file");
	dup2(data->outfile, STDOUT_FILENO);
	close(data->outfile);
	if (access(argv[argc - 1], O_RDONLY != 0))
		perror("Error");
	execute(data);
}

void	middle_processes(t_data *data)
{
	pid_t	pid;

	pid = 0;
	pipe(data->fd);
	pid = fork();
	if (pid == 0)
	{
		close(data->fd[0]);
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[1]);
		execute(data);
	}
	else
	{
		close(data->fd[1]);
		dup2(data->fd[0], STDIN_FILENO);
		close(data->fd[0]);
	}
}

void	first_process(t_data *data, char **argv)
{
	pid_t	pid;

	pid = 0;
	pipe(data->fd);
	pid = fork();
	if (pid == 0)
	{
		if (access(argv[1], O_RDONLY != 0)
			&& access("/tmp/.file", O_RDONLY) != 0)
		{
			perror("Error");
			exit(1);
		}
		close(data->fd[0]);
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[1]);
		execute(data);
	}
	else
	{
		close(data->fd[1]);
		dup2(data->fd[0], STDIN_FILENO);
		close(data->fd[1]);
	}
}

void	open_files(int argc, char **argv, t_data *data)
{
	if (argv[1][0] == '\0' || argv[argc - 1][0] == '\0')
	{
		if (access(argv[1], O_RDONLY != 0))
			perror("Error");
		data->outfile = open(argv[argc - 1], O_WRONLY
				| O_TRUNC | O_CREAT, 0644);
		if (access(argv[argc - 1], O_RDONLY != 0))
			perror("Error");
		exit (1);
	}
	else if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		here_doc(data, argv);
		data->infile = open("/tmp/.file", O_RDWR | O_APPEND | O_CREAT, 0644);
		data->outfile = open(argv[argc - 1], O_WRONLY
				| O_TRUNC | O_CREAT, 0644);
	}
	else
	{
		data->infile = open(argv[1], O_RDONLY);
		data->outfile = open(argv[argc - 1], O_WRONLY
				| O_TRUNC | O_CREAT, 0644);
	}
}
