#include "minishell.h"

char	*join_path(char *dir, char *sep, char *cmd)
{
	char	*joined;
	size_t	len;

	if (!dir || !sep || !cmd)
		return (NULL);
	len = ft_strlen(dir) + ft_strlen(sep) + ft_strlen(cmd) + 1;
	joined = malloc(len);
	if (!joined)
		return (NULL);
	ft_strcpy(joined, dir);
	ft_strcat(joined, sep);
	ft_strcat(joined, cmd);
	return (joined);
}
