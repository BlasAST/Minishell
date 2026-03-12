/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:27:14 by andtruji          #+#    #+#             */
/*   Updated: 2026/03/12 19:46:58 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*clone_token(t_token *tok)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = tok->type;
	if (tok->value)
		new->value = ft_strdup(tok->value);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

t_token	*copy_subshell_tokens(t_token *tok)
{
	t_subshell	sub;

	sub.head = NULL;
	sub.tail = NULL;
	sub.new = NULL;
	sub.lvl = 1;
	tok = tok->next;
	while (tok && sub.lvl > 0)
	{
		if (tok->type == LPAREN)
			sub.lvl++;
		else if (tok->type == RPAREN)
			sub.lvl--;
		if (sub.lvl == 0)
			break ;
		sub.new = clone_token(tok);
		if (!sub.head)
			sub.head = sub.new;
		else
			sub.tail->next = sub.new;
		sub.tail = sub.new;
		tok = tok->next;
	}
	return (sub.head);
}

int	subshell(t_parse_token *pt)
{
	int		lvl;
	t_token	*sub;

	lvl = 1;
	if (pt->tok->type != LPAREN)
		return (0);
	sub = copy_subshell_tokens(pt->tok);
	pt->cmd->ishell = 1;
	pt->cmd->subshell = parser_tokens(sub);
	pt->tok = pt->tok->next;
	while (pt->tok && lvl > 0)
	{
		if (pt->tok->type == LPAREN)
			lvl++;
		else if (pt->tok->type == RPAREN)
			lvl--;
		pt->tok = pt->tok->next;
	}
	free_token_list(&sub);
	return (1);
}
