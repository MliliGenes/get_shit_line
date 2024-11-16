#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct t_item
{
	char			*str;
	struct t_item	*next;
	struct t_item	*prev;
}					t_item;

#define BUFFER_SIZE 5

t_item	*new_node(char *str)
{
	t_item	*node;

	node = malloc(sizeof(t_item));
	if (!node)
		return (NULL);
	node->str = str;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_back(t_item **head, t_item *new_item)
{
	t_item	*current;

	if (!head || !new_item)
		return ;
	if (*head == NULL)
	{
		*head = new_item;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_item;
		new_item->prev = current;
	}
	new_item->next = NULL;
}

int	has_newline(const char *buffer)
{
	size_t	i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*str_join(const char *str1, const char *str2)
{
	char	*result;

	size_t len1, len2, i, j;
	if (!str1 && !str2)
		return (NULL);
	len1 = 0;
	while (str1[len1])
		len1++;
	len2 = 0;
	while (str2[len2])
		len2++;
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len1)
		result[i++] = str1[i];
	j = 0;
	while (j < len2)
		result[i + j++] = str2[j];
	result[i + j] = '\0';
	return (result);
}

void	*stashing(t_item *node)
{
	static t_item	*head;
	char			*buff;
	char			*total;
	int				i;
	t_item			*tmp;

	head = NULL;
	add_back(&head, node);
	if (has_newline(node->str) > -1)
	{
		buff = malloc(has_newline(node->str) + 1);
		buff[has_newline(node->str)] = '\0';
		i = 0;
		while (buff[i])
			buff[i++] = (node->str)[i];
		tmp = head;
		while (tmp->prev)
			tmp = tmp->prev;
		total = NULL;
		while (tmp)
		{
			str_join(total,tmp->str)
			tmp = tmp->next;
		}
	}
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = 0;
	while (s[len])
		len++;
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

char	*get_next_line(int fd)
{
	char	*buff;
	int		bytes_read;
	char	*str;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	bytes_read = read(fd, buff, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buff);
		return (NULL);
	}
	buff[bytes_read] = '\0';
	if (!tmp)
		return (NULL);
	str = stashing(new_node(ft_strdup(buff)));



	// return (buff);
}

int	main(void)
{
	int fd = open("test.txt", O_RDONLY, 0777);
	if (fd < 0)
		return (1);
	printf("%s", get_next_line(fd));
	close(fd);
	return (0);
}