#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	init_variables(&data);
	big_pipex(argc, argv, env, &data);
}
	