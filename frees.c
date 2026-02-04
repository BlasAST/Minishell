#include "minishell.h"

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list->next;
		free(env_list->key);
		if (env_list->value)
			free (env_list->value);
		free(env_list);
		env_list = tmp;
	}
}

void	free_token_list(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->value);
		free(list);
		list = tmp;
	}
}

void	free_redir_list(t_redir *list)
{
	t_redir	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->target);
		free(list);
		list = tmp;
	}
}

// void	free_cmd_list(t_cmd *list)
// {
// 	t_cmd	*tmp;
// 	int 	i;

// 	i = 0;
// 	while (list)
// 	{
// 		tmp = list->next;
// 		if (list->args)
// 		{
// 			while (list->args[i])
// 			{
// 				free(list->args[i]);
// 				i++;
// 			}
// 		}
// 		free(list->args);
// 		if (list->cmd_path)
// 			free(list->cmd_path);
// 		free_redir_list(list->redir_list);
// 		free(list);
// 		list = tmp;
// 		i = 0;
// 	}
// }

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->target)
			free(redir->target);
		free(redir);
		redir = tmp;
	}
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		// 1. Liberar los argumentos (char **)
		if (cmd->args)
			free_array(cmd->args);
		// 2. Liberar el path calculado
		if (cmd->cmd_path)
			free(cmd->cmd_path);
		// 3. Liberar la lista de redirecciones
		if (cmd->redir_list)
			free_redirs(cmd->redir_list);
		// 4. Cerrar FDs si se quedaron abiertos (opcional pero recomendado)
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		// 5. Liberar el nodo actual y saltar al siguiente
		free(cmd);
		cmd = tmp;
	}
}

