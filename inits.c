/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiguenc <bsiguenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:18:42 by blas              #+#    #+#             */
/*   Updated: 2026/02/27 14:07:23 by bsiguenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		i;
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
	update_shlvl(mini);
	init_termios();
	init_signals();
}
