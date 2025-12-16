#include "minishell.h"

int execute_command(t_cmd *cmd, t_mini *mini)
{
    return 1;
}

void    executor(t_cmd *cmd_list, t_mini *mini)
{
    t_cmd   *cmd;

    cmd = cmd_list;
    while (cmd)
    {
        mini->exit_code = execute_command(cmd, mini);
    }

}