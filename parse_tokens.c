#include "minishell.h"

int	count_args(t_token *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type != PIPE && tok->type != END_OF_INPUT)
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
	cmd->redir_target = NULL;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->pid = -1;
	cmd->redir_type = END_OF_INPUT;
	cmd->next = NULL;
	return (cmd);
}

t_cmd   *parser_tokens(t_token *tokens)
{
	t_parse_token	pt;

	pt.cmd_list = NULL;
	pt.tok = tokens;
	while (pt.tok && pt.tok->type != END_OF_INPUT)
	{
		pt.cmd = new_cmd();
		pt.arg_count = count_args(pt.tok);
		pt.cmd->args = malloc(sizeof(char *) * (pt.arg_count + 1));
		if (!pt.cmd->args)
			return (NULL);
		pt.i = 0;
		while ()
	}

}