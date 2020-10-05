
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
char	*ft_strlcpy(char *dst, char *src, size_t len);
char	*ft_strdup(char *s1);
int		find_next_line(char *s);
size_t	line_len(char *str);
size_t	buffsize(char *str);

#endif
