#include "pipex.h"

void	pipex(int argc, char **argv, char **env, t_data *data)
{
	open_files(argc, argv, data);
	get_args(argc, argv, data);
	get_path(env, data);
	processes(data, argc, argv);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc < 5)
		exit (1);
	init_variables(&data);
	pipex(argc, argv, env, &data);
}
