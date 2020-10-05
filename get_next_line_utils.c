#include "get_next_line.h"

char	*ft_strlcpy(char *dst, char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!len || dst == src)
		return (dst);
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	size_t	j;
	char	*s2;

	if (!s1)
		return (NULL);
	i = 0;
	j = buffsize(s1);
	if (!(s2 = (char *)malloc((j + 1) * sizeof(char))))
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int		find_next_line(char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

size_t	line_len(char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	return (i);
}

size_t	buffsize(char *buff)
{
	size_t i;

	if (!buff)
		return (0);
	i = 0;
	while (buff[i] != '\0')
		i++;
	return (i);
}
