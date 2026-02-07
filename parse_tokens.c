#include "minishell.h"

int	count_args(t_token *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type != PIPE && tok->type != END_OF_INPUT
		&& tok->type != AND && tok->type != OR)
	{
		if (tok->type == WORD)
			count++;
		tok = tok->next;
	}
	return (count);
}

static t_cmd	*new_cmd(void)
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
	return (cmd);
}

void	add_redir(t_cmd *cmd, t_token_type redir_type, char *target)
{
	t_redir	*new_r;
	t_redir	*temp;

	new_r = malloc(sizeof(t_redir));
	if (!new_r)
		return ;
	new_r->redir_type = redir_type;
	new_r->target = ft_strdup(target);
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

void	parser_tokens2(t_parse_token *pt)
{
	pt->cmd = new_cmd();
	pt->arg_count = count_args(pt->tok);
	pt->cmd->args = malloc(sizeof(char *) * (pt->arg_count + 1));
	if (!pt->cmd->args)
		return ;
	pt->i = 0;
	printf("🧱 [PARSER] New command:\n");
	while (pt->tok && pt->tok->type != PIPE && pt->tok->type != END_OF_INPUT
		&& pt->tok->type != AND && pt->tok->type != OR)
	{
		if (pt->tok->type == WORD)
		{
			pt->cmd->args[pt->i++] = ft_strdup(pt->tok->value);
			printf("   ➜ arg[%d] = \"%s\"\n", pt->i - 1, pt->tok->value);
		}
		else if (pt->tok->type == REDIR_IN || pt->tok->type == REDIR_OUT
			|| pt->tok->type == REDIR_APPEND || pt->tok->type == HEREDOC)
		{
			pt->cmd->redir_type = pt->tok->type;
			pt->tok = pt->tok->next;
			if (pt->tok && pt->tok->type == WORD)
			{
				add_redir(pt->cmd, pt->cmd->redir_type, pt->tok->value);
				printf("   🔁 redir: %d -> \"%s\"\n", pt->cmd->redir_type, pt->tok->value);
			}
		}
		pt->tok = pt->tok->next;
	}
	printf("✅ [PARSER] Command finished.\n\n");
	pt->cmd->args[pt->i] = NULL;
}

t_cmd	*parser_tokens(t_token *tokens)
{
	t_parse_token	pt;

	pt.cmd_list = NULL;
	pt.tok = tokens;
	while (pt.tok && pt.tok->type != END_OF_INPUT)
	{
		parser_tokens2(&pt);
		if (pt.tok && (pt.tok->type == AND || pt.tok->type == OR))
		{
			pt.cmd->cond_type = pt.tok->type;
			printf("⚙️  [PARSER] Logical operator: %s\n",
				(pt.tok->type == AND) ? "&&" : "||");
			pt.tok = pt.tok->next;
		}
		else if (pt.tok && pt.tok->type == PIPE)
		{
			printf("🚇 [PARSER] PIPE detected, moving to next command...\n");
			pt.tok = pt.tok->next;
		}
		if (!pt.cmd_list)
			pt.cmd_list = pt.cmd;
		else
		{
			pt.tmp = pt.cmd_list;
			while (pt.tmp->next)
				pt.tmp = pt.tmp->next;
			pt.tmp->next = pt.cmd;
		}
	}
	printf("🏁 [PARSER] All tokens parsed.\n\n");
	return (pt.cmd_list);
}
