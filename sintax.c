/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiguenc <bsiguenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:20:32 by blas              #+#    #+#             */
/*   Updated: 2026/03/13 11:21:27 by bsiguenc         ###   ########.fr       */
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

int	check_sintax3(t_token *tok, int *lvl)
{
	if (tok->type == LPAREN)
		(*lvl)++;
	else if (tok->type == RPAREN)
		(*lvl)--;
	if (tok->next->type == 10 && *lvl > 0)
		return (sintax_error("newline"));
	if (tok->next->type == 10 && *lvl < 0)
		return (sintax_error(")"));
	return (0);
}

int	check_sintax2(t_token *tok, int *lvl)
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
				|| (tok->prev->type >= PIPE && tok->prev->type <= OR)
				|| tok->prev->type == LPAREN))
			return (sintax_error(")"));
	if (tok->next && tok->next->type == 10
		&& (tok->type == PIPE || tok->type == AND
			|| tok->type == OR || tok->type == LPAREN))
		return (sintax_error2(tok));
	return (check_sintax3(tok, lvl));
}

int	check_sintax(t_token *tok)
{
	int	lvl;

	lvl = 0;
	if (!tok)
		return (0);
	if (tok->type == PIPE || tok->type == AND
		|| tok->type == OR || tok->type == RPAREN)
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
		if (check_sintax2(tok, &lvl))
			return (2);
		tok = tok->next;
	}
	return (0);
}
