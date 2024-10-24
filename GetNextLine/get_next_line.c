/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:21:10 by rmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/24 16:49:55 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join_stash(char *stash, char *buffer)
{
	char	*temp;

	if (!stash)
		return (ft_strdup(buffer));
	temp = ft_strjoin(stash, buffer);
	if (!temp)
	{
		free (stash);
		return (NULL);
	}
	free (stash);
	return (temp);
}

static char	*read_n_store(int fd, char *stash, ssize_t *nbytes)
{
	char	*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	*nbytes = read(fd, buffer, BUFFER_SIZE);
	while (*nbytes > 0)
	{
		buffer[*nbytes] = '\0';
		stash = join_stash(stash, buffer);
		if (ft_strchr(stash, '\n'))
			break ;
		*nbytes = read(fd, buffer, BUFFER_SIZE);
	}
	if (*nbytes < 0)
	{
		free (stash);
		free(buffer);
		return (NULL);
	}
	free (buffer);
	return (stash);
}

static char	*get_line(char *stash)
{
	char	*ptr;
	char	*substr;
	size_t	len;

	if (!stash)
		return (NULL);
	ptr = ft_strchr(stash, '\n');
	if (ptr)
	{
		len = (ptr + 1) - stash;
		substr = ft_substr(stash, 0, len);
	}
	else
	{
		len = ft_strlen(stash) + 1;
		substr = ft_substr(stash, 0, len);
	}
	return (substr);
}

static char	*update_stash(char *stash)
{
	char	*ptr;
	char	*new_stash;
	size_t	len;

	if (!stash)
		return (NULL);
	ptr = ft_strchr(stash, '\n');
	if (ptr)
	{
		len = ft_strlen(ptr + 1);
		new_stash = ft_substr(ptr + 1, 0, len);
	}
	else
		new_stash = NULL;
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	ssize_t		nbytes;

	stash = read_n_store(fd, stash, &nbytes);
	if (fd < 0 || BUFFER_SIZE <= 0 || nbytes < 0)
	{
		free (stash);
		stash = NULL;
		return (NULL);
	}
	if (!stash)
		return (NULL);
	line = get_line(stash);
	if (!line)
		return (NULL);
	stash = update_stash(stash);
	return (line);
}

/*int main() {
    int fd = open("hola.txt", O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}*/