#include "minishell.h"

int	g_signal_status = 0;

int	main2(t_mini *mini, char *input)
{
	add_history(input);
	mini->token_list = tokenize_input(input);
	if (!check_sintax(mini->token_list))
		return (handle_sintax_error(mini, input));
	expander(mini);
	mini->cmd_list = parser_tokens(mini->token_list);
	if (!handle_heredoc(&mini->cmd_list))
		return (handle_heredoc_error(mini, input));
	executor(mini);
	free_all(mini);
	return (1);
}

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
		if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (input[0] != '\0')
			if (!main2(&mini, input))
				continue ;
		free(input);
	}
	rl_clear_history();
	free_env_list(mini.env_list);
	return (0);
}
