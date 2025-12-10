#include "minishell.h"

int	g_signal_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	*input;
	(void)argc;
	(void)argv;
	init_mini(&mini, envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (input[0] != '\0')
		{
			add_history(input);
			mini.token_list = tokenize_input(input, mini.env_list);
			expander(&mini);
		}
		free(input);
	}
	rl_clear_history();
	free_env_list(mini.env_list);
	return (0);
}