#include <minishell.h>

int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		tokenize_input(argv[1], NULL);
	}
	return (0);
}