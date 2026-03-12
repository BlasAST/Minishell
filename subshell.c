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

t_token	*ft_subshell(t_token *tok, t_token **next)
{
	int		lvl;
	t_token	*start;
	t_token	*end;

	lvl = 1;
	start = tok->next;
	end = start;
	while (end && lvl > 0)
	{
		if (end->type == LPAREN)
			lvl++;
		else if (end->type == RPAREN)
			lvl--;
		if (lvl > 0)
			end = end->next;
	}
	if (!end)
		return (NULL);
	*next = end->next;
	end->next = NULL;
	return (start);
}

int	subshell(t_parse_token *pt)
{
	t_token	*sub;
	t_token	*next;
	int		lvl;

	lvl = 1;
	next = NULL;
	if (pt->tok->type != LPAREN)
		return (0);
	sub = ft_subshell(pt->tok, &next);
	if (!sub)
		return (0);
	pt->cmd->ishell = 1;
	pt->cmd->subshell = parser_tokens(sub);
	pt->tok = next;
	return (1);
}
