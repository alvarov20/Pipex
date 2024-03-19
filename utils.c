#include "pipex.h"

char	*check_access(t_data *data, char **com)
{
	char	*compath;
	int		x;

	x = 0;
	compath = NULL;
	if (!com[0])
		return ("error");
	if (access(com[0], F_OK | X_OK) == -1)
	{
		if (data->path == NULL)
			return ("error");
		while (data->path[x] != NULL)
		{
			compath = ft_strjoin(data->path[x], com[0]);
			if (access(compath, F_OK) == 0)
				return (compath);
			free(compath);
			x++;
		}
		return ("error");
	}
	return (com[0]);
}

void	get_args(int argc, char **argv, t_data *d)
{
	int	x;

	d->args = malloc(sizeof(char *) * (argc - (3 + d->hc) + 1));
	if (d->args == NULL)
		return ;
	x = 0;
	while (x != argc - (3 + d->hc))
	{
		d->args[x] = argv[x + 2 + d->hc];
		x++;
	}
	d->args[x] = NULL;
}

void	get_path(char **env, t_data *data)
{
	int	x;

	x = 0;
	if (!env || env[x] == NULL)
		return ;
	while (env[x] != NULL)
	{
		if (ft_strnstr(env[x], "PATH=", 5) != NULL)
		{
			if (env[x][0])
				env[x] += 5;
			data->path = ft_split(env[x], ':');
		}
		x++;
	}
	x = 0;
	if (data->path != NULL)
	{
		while (data->path[x] != NULL)
		{
			data->path[x] = ft_strjoin_free(data->path[x], "/");
			x++;
		}
	}
}

void	execute(t_data *data)
{
	char	*str;
	char	**com;

	com = ft_split(data->args[data->n_arg], ' ');
	str = check_access(data, com);
	if (ft_strncmp(str, "error", ft_strlen(str)) == 0)
	{
		perror("Error");
		exit(1);
	}
	else
		execve(str, com, NULL);
}

void	init_variables(t_data *data)
{
	data->n_arg = 0;
	data->args = NULL;
	data->path = NULL;
	data->hc = 0;
}
