/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 16:29:12 by andtruji          #+#    #+#             */
/*   Updated: 2026/03/12 18:30:12 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_cmd(t_parse_token *pt)
{
	pt->cmd = new_cmd();
	pt->arg_count = count_args(pt->tok);
	pt->cmd->args = malloc(sizeof(char *) * (pt->arg_count + 1));
}

void	is_operator(t_parse_token *pt)
{
	if (pt->tok && (pt->tok->type == AND || pt->tok->type == OR))
	{
		pt->cmd->cond_type = pt->tok->type;
		pt->tok = pt->tok->next;
	}
	else if (pt->tok && pt->tok->type == PIPE)
		pt->tok = pt->tok->next;
}

int	count_args(t_token *tok)
{
	int	count;
	int	lvl;

	count = 0;
	while (tok && tok->type < PIPE)
	{
		if (tok->type == WORD)
			count++;
		else if (tok->type == LPAREN)
		{
			lvl = 1;
			tok = tok->next;
			while (tok && lvl > 0)
			{
				if (tok->type == LPAREN)
					lvl++;
				else if (tok->type == RPAREN)
					lvl--;
				tok = tok->next;
			}
			continue ;
		}
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
	cmd->ishell = 0;
	cmd->subshell = NULL;
	return (cmd);
}
