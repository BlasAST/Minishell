/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blas <blas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:20:32 by blas              #+#    #+#             */
/*   Updated: 2026/03/04 14:35:05 by andtruji         ###   ########.fr       */
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

int	check_sintax2(t_token *tok)
{
	if (tok->type >= REDIR_IN && tok->type <= HEREDOC)
		{
			if (tok->prev && tok->prev->type >= 1 && tok->prev->type <= 4)
				return (sintax_error2(tok));
			else if (!tok->next || tok->next->type != WORD)
				return (sintax_error("newline"));
		}
	if (tok->type == LPAREN)
		if (tok->prev && tok->prev->type >= 1 && tok->prev->type <= 4)
			return (sintax_error("("));
	if (tok->type == RPAREN)
		if (tok->prev && ((tok->prev->type >= 1 && tok->prev->type <= 4)
			|| (tok->prev->type >= PIPE && tok->prev->type <= OR)))
			return (sintax_error(")"));
	return (0);
}

int	check_sintax(t_token *tok)
{
	if (!tok)
		return (0);
	if (tok->type == PIPE || tok->type == AND || tok->type == OR || tok->type == RPAREN)
		return (sintax_error2(tok));
	while (tok && tok->next)
	{
		if (tok->type == 7 && ((tok->prev->type >= 1 && tok->prev->type <= 5)
			|| (tok->prev->type >= PIPE && tok->prev->type <= OR)))
			return (sintax_error("|"));
		if (tok->type == AND || tok->type == OR)
			if ((tok->prev->type >= 1 && tok->prev->type <= 5)
			|| (tok->prev->type >= PIPE && tok->prev->type <= OR))
				return (sintax_error2(tok));
		if (check_sintax2(tok))
			return (2);
		tok = tok->next;
	}
	if (tok->type == PIPE || tok->type == AND || tok->type == OR || tok->type == LPAREN)
		return (sintax_error2(tok));
	return (0);
}
