#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	// char	*input; <- Variable for reading readline

	(void)argc;
	(void)argv;
	init_mini(&mini, envp);
	if (argc > 1)
	{
		tokenize_input(argv[1], NULL);
	}
	return (0);
}