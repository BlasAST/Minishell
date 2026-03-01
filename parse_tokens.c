/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:20:10 by blas              #+#    #+#             */
/*   Updated: 2026/02/25 11:52:59 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redir(t_cmd *cmd, t_token_type redir_type, char *target)
{
	t_redir	*new_r;
	t_redir	*temp;

	new_r = malloc(sizeof(t_redir));
	if (!new_r)
		return ;
	new_r->redir_type = redir_type;
	new_r->target = ft_strdup(target);
	if (new_r->target == NULL)
	{
		free(new_r);
		return ;
	}
	new_r->next = NULL;
	if (!cmd->redir_list)
		cmd->redir_list = new_r;
	else
	{
		temp = cmd->redir_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_r;
	}
}

int	tok_args(t_parse_token *pt)
{
	if (pt->tok->type == WORD)
	{
		pt->cmd->args[pt->i] = ft_strdup(pt->tok->value);
		if (!pt->cmd->args[pt->i])
		{
			while (pt->i-- >= 0)
				free(pt->cmd->args[pt->i]);
			free(pt->cmd->args);
			free(pt->cmd);
			pt->cmd = NULL;
			return (0);
		}
		pt->i++;
	}
	else
		return (1);
	return (0);
}

void	parser_tokens2(t_parse_token *pt)
{
	pt->cmd = new_cmd();
	pt->arg_count = count_args(pt->tok);
	pt->cmd->args = malloc(sizeof(char *) * (pt->arg_count + 1));
	if (!pt->cmd->args)
	{
		free(pt->cmd);
		pt->cmd = NULL;
		return ;
	}
	pt->i = 0;
	while (pt->tok && pt->tok->type < PIPE)
	{
		if (tok_args(pt) && pt->tok->type >= REDIR_IN && pt->tok->type <= HEREDOC)
		{
			pt->cmd->redir_type = pt->tok->type;
			if (pt->tok->next && pt->tok->next->type == WORD)
			{
				pt->tok = pt->tok->next;
				add_redir(pt->cmd, pt->cmd->redir_type, pt->tok->value);
			}
		}
		pt->tok = pt->tok->next;
	}
	pt->cmd->args[pt->i] = NULL;
}

t_cmd	*parser_tokens(t_token *tokens)
{
	t_parse_token	pt;

	pt.cmd_list = NULL;
	pt.prev = NULL;
	pt.tok = tokens;
	while (pt.tok && pt.tok->type != END_OF_INPUT)
	{
		parser_tokens2(&pt);
		if (!pt.cmd)
			return (NULL);
		if (!pt.cmd_list)
			pt.cmd_list = pt.cmd;
		else
		{
			pt.prev->next = pt.cmd;
			pt.cmd->prev = pt.prev;
		}
		pt.prev = pt.cmd;
		if (pt.tok && (pt.tok->type == AND || pt.tok->type == OR))
		{
			pt.cmd->cond_type = pt.tok->type;
			pt.tok = pt.tok->next;
		}
		else if (pt.tok && pt.tok->type == PIPE)
			pt.tok = pt.tok->next;
	}
	return (pt.cmd_list);
}
