/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blas <blas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:20:32 by blas              #+#    #+#             */
/*   Updated: 2026/02/25 01:20:33 by blas             ###   ########.fr       */
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
		if (tok->type == PIPE && tok->next->type == PIPE)
			return (sintax_error("|"));
		if (tok->type == AND || tok->type == OR)
			if (!tok->prev || !tok->next || tok->next->type == AND
				|| tok->next->type == OR || tok->next->type == PIPE
				|| (tok->prev->type == AND || tok->prev->type == OR
					|| tok->prev->type == PIPE))
				return (sintax_error2(tok));
		if (tok->type == REDIR_IN || tok->type == REDIR_OUT
			|| tok->type == REDIR_APPEND || tok->type == HEREDOC)
			if (!tok->next || tok->next->type != WORD)
				return (sintax_error("newline"));
		tok = tok->next;
	}
	if (tok->type == PIPE || tok->type == AND || tok->type == OR)
		return (sintax_error2(tok));
	return (1);
}
