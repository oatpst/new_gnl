/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwanakit <pwanakit@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:10:07 by pwanakit          #+#    #+#             */
/*   Updated: 2024/02/20 01:24:52 by pwanakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_clear(char **buffer)
{
	if (buffer)
		free(*buffer);
	*buffer = NULL;
	return (NULL);
}

char	*ft_read(int fd, char *buf, char **buffer)
{
	int		count;
	char	*temp;

	count = 1;
	while (count)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count == -1)
			if (buffer)
				return (ft_clear(&*buffer));
		if (count < 1)
			break ;
		buf[count] = '\0';
		if (!(*buffer))
			*buffer = ft_strdup("");
		temp = *buffer;
		*buffer = ft_strjoin(temp, buf);
		if (temp)
			ft_clear(&temp);
		if (!(*buffer))
			return (ft_clear(&*buffer));
		if (ft_strchr(*buffer, '\n'))
			break ;
	}
	return (*buffer);
}

char	*ft_get_line(char *line)
{
	int		i;
	char	*temp;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	temp = ft_substr(line, i + 1, -1);
	if (!temp)
		return (NULL);
	if (temp[0] == '\0')
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	return (temp);
}

char	*ft_cut_line(char *line)
{
	int		i;
	char	*new;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	new = ft_strdup(line);
	free(line);
	if (!new)
		return (NULL);
	line = ft_substr(new, 0, i + 1);
	if (new)
		free(new);
	if (!line)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		if (buffer)
			return (ft_clear(&buffer));
		return (NULL);
	}
	line = ft_read(fd, buf, &buffer);
	free(buf);
	buffer = ft_get_line(line);
	line = ft_cut_line(line);
	if (!line)
	{
		if (buffer)
			return (ft_clear(&buffer));
		return (NULL);
	}
	return (line);
}
