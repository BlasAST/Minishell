#include "libft.h"

char	*ft_strndup(const char *string, size_t n)
{
	char	*s;
	size_t	i;

	if (!string)
		return (NULL);
	s = malloc((n + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (i < n && string[i] != '\0')
	{
		s[i] = string[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}