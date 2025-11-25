#include <minishell.h>

int ispecial(char c)
{
    if ()
}

void    tokenize_imput(char *input, t_env *env)
{
    t_token *list;
    int     i;

    while (input[i])
    {
        while (input[i] && (input[i] == ' ' || input[i] == '\t'))
            i++;
        if (!input[i])
            break ;
        if (ispecial(input[i]))
        
    }
    
}