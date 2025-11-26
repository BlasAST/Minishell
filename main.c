#include <minishell.h>

int	g_signal_status = 0;

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1)
	{
		tokenize_input(argv[1], NULL);
	}
	return (0);
}