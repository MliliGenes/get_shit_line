/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 08:02:17 by sel-mlil          #+#    #+#             */
/*   Updated: 2024/11/17 14:08:27 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strchr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		sizetotal;
	char	*res;
	int		i;
	int		j;

	i = 0;
	sizetotal = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (sizetotal + 1));
	if (!res || !s1 || !s2)
		return (NULL);
	while (s1[i] != 0)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[sizetotal] = '\0';
	free(s1);
	return (res);
}

char	*get_next(char *stash)
{
	char	*next;
	char	*tmp;

	if (!stash)
		return (NULL);
	tmp = ft_strchr(stash, '\n');
	if (!tmp)
		return (NULL);
	next = ft_strdup(tmp);
	free(tmp);
	free(stash);
	return (next);
}

char	*get_line(char *stash)
{
	char	*line;
	int		i;

	if (!stash)
		return (NULL);
	if (!stash[i])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(i + 1);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] && stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	free(stash);
	return (line);
}

char	*get_chunk(char *stash, int fd)
{
	int		read_bytes;
	char	*tmp;

	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(tmp), tmp = NULL, NULL);
		stash = ft_strjoin(stash, tmp);
		if (ft_strchr(tmp, '\n'))
			break ;
	}
	free(tmp);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (free(stash), stash = NULL, NULL);
	stash = get_chunk(stash, fd);
	if (!stash)
		return (NULL);
	printf("%s", stash);
	line = get_line(stash);
	stash = get_next(stash);
	return (line);
}

int	main(void)
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	// line = get_next_line(fd);
	// printf("==>%s\n", line);
	// free(line);
	// line = get_next_line(fd);
	// printf("==>%s\n", line);
	// free(line);
	// line = get_next_line(fd);
	// printf("==>%s\n", line);
	// free(line);
	// 	// line = get_next_line(fd);
	// 	// printf("==>%s\n", line);
	// 	// free(line);
	// 	// line = get_next_line(fd);
	// 	// printf("==>%s\n", line);
	// 	// free(line);
	while ((line = get_next_line(fd)))
	{
		printf("=>%s\n", line);
		free(line);
	}
	close(fd);

	return (0);
}