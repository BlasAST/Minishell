#include "minishell.h"

// ** File for initialization of the entire mini structure

void	init_signals(void)
{
	struct sigaction	sa;
	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	init_env(t_mini *mini, char **envp)
{
	int	i;
	t_env	*new_node;
	t_env	*current;

	mini->env_list = NULL;
	i = 0;
	if (!envp || !*envp)
		return ;
	while (envp[i])
	{
		new_node = new_env_node(envp[i]);
		if (!new_node)
			return ;
		if (!mini->env_list)
			mini->env_list = new_node;
		else
		{
			current = mini->env_list;
			while (current->next)
				current = current->next;
			current->next = new_node;
		}
		i++;
	}
}

static void	init_fds(t_mini *mini)
{
	mini->stdin_backup = dup(STDIN_FILENO);
	mini->stdout_backup = dup(STDOUT_FILENO);
	if (mini->stdin_backup == -1 || mini->stdout_backup == -1)
	{
		ft_putstr_fd("Error: Could not backup FDs\n", 2);
		exit(1);
	}
}

void	init_termios(void)
{
	struct termios	term_attrs;

	tcgetattr(STDIN_FILENO, &term_attrs);
	term_attrs.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term_attrs);
}

void	init_mini(t_mini *mini, char **envp)
{
	ft_bzero(mini, sizeof(t_mini));
	init_env(mini, envp);
	mini->env_arr = envp;
	init_fds(mini);
	init_termios();
	init_signals();
}