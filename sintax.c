/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:20:32 by blas              #+#    #+#             */
/*   Updated: 2026/02/25 11:54:42 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sintax_error2(t_token *tok)
{
	if (tok->type == PIPE)
		return (sintax_error("|"));
	if (tok->type == AND)
		return (sintax_error("&&"));
	if (tok->type == OR)
		return (sintax_error("||"));
	if (tok->type >= REDIR_IN && tok->type <= HEREDOC)
		return (sintax_error(tok->value));
	return (0);
}

int	check_sintax(t_token *tok)
{
	if (!tok)
		return (0);
	if (tok->type == PIPE || tok->type == AND || tok->type == OR)
		return (sintax_error2(tok));
	while (tok && tok->next)
	{
		if (tok->type == PIPE && (tok->prev->type >= REDIR_IN
				&& tok->prev->type <= OR))
			return (sintax_error("|"));
		if (tok->type == AND || tok->type == OR)
			if (!tok->prev || !tok->next || tok->prev->type >= PIPE
				|| tok->prev->type <= OR)
				return (sintax_error2(tok));
		if (tok->type >= REDIR_IN && tok->type <= HEREDOC)
		{
			if (!tok->next || tok->next->type != WORD)
				return (sintax_error("newline"));
			else if (tok->prev->type >= REDIR_IN && tok->prev->type <= HEREDOC)
				return (sintax_error2(tok));
		}
		tok = tok->next;
	}
	if (tok->type == PIPE || tok->type == AND || tok->type == OR)
		return (sintax_error2(tok));
	return (1);
}
