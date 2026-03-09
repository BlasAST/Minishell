/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blas <blas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:20:10 by blas              #+#    #+#             */
/*   Updated: 2026/03/09 13:15:27 by blas             ###   ########.fr       */
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

int	subshell(t_parse_token *pt)
{
	t_token	*sub;
	int		lvl;

	// i = 1;
	if (pt->tok->type != LPAREN)
		return (0);
	sub = ft_subshell(pt->tok);
	pt->cmd->ishell = 1;
	pt->cmd->subshell = parser_tokens(sub);
	pt->tok = pt->tok->next;
	while (pt->tok && lvl)
	{
		if (pt->tok->type == LPAREN)
			lvl++;
		else if (pt->tok->type == RPAREN)
			lvl--;
		pt->tok = pt->tok->next;
	}
	return (1);
}

void	parser_tokens1(t_parse_token *pt)
{
	create_cmd(pt);
	if (!pt->cmd->args)
	{
		free(pt->cmd);
		pt->cmd = NULL;
		return ;
	}
	pt->i = 0;
	while (pt->tok && pt->tok->type < PIPE)
	{
		if (subshell(pt))
			continue ;
		if (tok_args(pt) && pt->tok->type >= 1 && pt->tok->type <= 4)
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

static void	linked(t_parse_token *pt)
{
	if (!pt->cmd_list)
		pt->cmd_list = pt->cmd;
	else
	{
		pt->prev->next = pt->cmd;
		pt->cmd->prev = pt->prev;
	}
	pt->prev = pt->cmd;
}

t_cmd	*parser_tokens(t_token *tokens)
{
	t_parse_token	pt;

	pt.cmd_list = NULL;
	pt.prev = NULL;
	pt.tok = tokens;
	while (pt.tok && pt.tok->type != END_OF_INPUT)
	{
		parser_tokens1(&pt);
		if (!pt.cmd)
			return (NULL);
		linked(&pt);
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
/* t_cmd	*parser_tokens(t_token *tokens)
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
		is_operator(&pt);
	}
	return (pt.cmd_list);
} */
