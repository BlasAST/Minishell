#include "libft.h"

char	*ft_strndup(const char *strin, size_t n)
{
	char	*s;
	size_t	i;

	if (!strin)
		return (NULL);
	s = malloc((n + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (i < n && strin[i] != '\0')
	{
		s[i] = strin[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}