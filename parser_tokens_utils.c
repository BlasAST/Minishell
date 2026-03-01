/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 16:29:12 by andtruji          #+#    #+#             */
/*   Updated: 2026/03/01 16:29:12 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_token *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type < PIPE)
	{
		if (tok->type == WORD)
			count++;
		tok = tok->next;
	}
	return (count);	
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->cmd_path = NULL;
	cmd->redir_list = NULL;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->pid = -1;
	cmd->cond_type = END_OF_INPUT;
	cmd->redir_type = END_OF_INPUT;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}
