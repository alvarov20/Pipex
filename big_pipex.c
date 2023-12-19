#include "pipex.h"

void	big_pipex(int argc, char **argv, char **env, t_data *data)
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		here_doc(data, argv);
		data->infile = open("/tmp/.file", O_RDWR | O_APPEND | O_CREAT, 0644);
		data->outfile = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
	else
	{
		data->infile = open(argv[1], O_RDONLY);
		data->outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	get_args(argc, argv, data);
	printf("NOSE AQUI TODO BIEN\n");
	get_path(env, data);
	printf("NOSE AQUI TODO BIEN22222\n");
	processes(data, argv);
}

void	here_doc(t_data *data, char **argv)
{
	char	*str;

	str = NULL;
	data->infile = open("/tmp/.file", O_RDWR | O_APPEND | O_CREAT, 0644);
	data->hc = 1;
	while (1)
	{
		str = get_next_line(STDIN_FILENO);
		if (ft_strncmp(str, argv[2], ft_strlen(argv[2])) == 0 && (ft_strlen(str) - 1) == ft_strlen(argv[2]))
			break ;
		write(data->infile, str, ft_strlen(str));
	}
}

void	processes(t_data *data, char **argv)
{
	pid_t	pid;

	pipe(data->fd);
	dup2(data->infile, STDIN_FILENO);
	close(data->infile);
	printf("NOSE AQUI TODO BIEN33333\n");
	first_process(data, argv);
	waitpid(pid, NULL, 0);
	data->n_arg++;
	while (data->args[data->n_arg + 1] != NULL)
	{
		middle_processes(data);
		data->n_arg++;
	}
	printf("NOSE AQUI TODO BIEN44444\n");
	dup2(data->outfile, STDOUT_FILENO);
	close(data->outfile);
	execute(data);
}

void	middle_processes(t_data *data)
{
	pid_t	pid;
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

	pipe(data->fd);
	pid = fork();
	if (pid == 0)
	{
		if (access(argv[1], O_RDONLY != 0) && access("/tmp/.file", O_RDONLY) != 0)
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
		//	waitpid(pid, NULL, -1);
		close(data->fd[1]);
		dup2(data->fd[0], STDIN_FILENO);
		close(data->fd[1]);
	}
}
//Un primer fork para una funci´on first_process, desde ahi otra para los procesos de en medio y por ultimo una para el ultimo comando
