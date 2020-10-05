#include "get_next_line.h"

static char		*buff_free(char *leftover)
{
	size_t	i;
	size_t	left_len;
	size_t	buff_len;
	char	*tmp;

	left_len = line_len(leftover);
	buff_len = buffsize(leftover) - left_len;
	if (buff_len > 0)
	{
		if (!(tmp = (char *)malloc((buff_len + 1) * sizeof(char))))
			return (NULL);
		i = 0;
		while (leftover[left_len++] != '\0')
			tmp[i++] = leftover[left_len];
		tmp[i] = '\0';
		free(leftover);
		return (tmp);
	}
	free(leftover);
	leftover = NULL;
	return (leftover);
}

static int		linemaker(char **line, char *leftover)
{
	size_t i;

	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	i = line_len(leftover);
	if (!(*line = (char *)malloc((i + 1) * sizeof(char))))
		return (-1);
	(*line)[i] = '\0';
	if (leftover)
	{
		ft_strlcpy(*line, leftover, i);
		if (leftover[i] == '\n')
			return (1);
	}
	return (0);
}

static char		*add_buffline(char *tmp, char *buffline)
{
	size_t	i;
	size_t	tmp_len;
	size_t	buff_len;
	char	*left;

	tmp_len = buffsize(tmp);
	buff_len = buffsize(buffline);
	if (!(left = (char *)malloc((tmp_len + buff_len + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < tmp_len)
	{
		left[i] = tmp[i];
		i++;
	}
	i = 0;
	while (i < buff_len)
	{
		left[tmp_len] = buffline[i];
		i++;
		tmp_len++;
	}
	left[tmp_len] = '\0';
	return (left);
}

static char		*read_append(int fd, char *leftover, char *buffline)
{
	ssize_t	chars;
	char	*tmp;

	while ((chars = read(fd, buffline, BUFFER_SIZE)) > 0)
	{
		buffline[chars] = '\0';
		tmp = leftover;
		leftover = add_buffline(tmp, buffline);
		free(tmp);
		if (find_next_line(buffline))
			break ;
	}
	return (leftover);
}

int				get_next_line(int fd, char **line)
{
	int			chars;
	char		buffline[BUFFER_SIZE + 1];
	static char	*leftover;

	if (!line || fd < 0 || BUFFER_SIZE < 1 ||
		(read(fd, buffline, 0) < 0) || !(*line = ft_strdup("")))
		return (-1);
	leftover = read_append(fd, leftover, buffline);
	if (leftover == NULL)
		return (0);
	chars = linemaker(line, leftover);
	leftover = buff_free(leftover);
	return (chars);
}
