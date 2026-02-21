#include "minishell.h"

char	*join_free(char *s1, char *s2, char *s3)
{
	char	*joined;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	joined = malloc(len);
	if (!joined)
		return (NULL);
	ft_strcpy(joined, s1);
	ft_strcat(joined, s2);
	ft_strcat(joined, s3);
	return (joined);
}