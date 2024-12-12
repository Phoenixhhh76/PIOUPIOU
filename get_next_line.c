/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-troc <hho-troc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:15:50 by hho-troc          #+#    #+#             */
/*   Updated: 2024/12/12 15:38:13 by hho-troc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *save)
{
	int		i;
	char	*str;

	i = 0;
	if (!save || !save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		str[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		str[i] = save[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*skip_get_line(char *save)
{
	int	i = 0;
	int	j = 0;
	char	*str;
	int	count = 0;

	if (!save || !save[i])
		return (NULL);
	while (save[i] && save[i] != '\n' && count < 8)
	{
		if (save[i] == ';')
			count++;
		i++;
	}
	int len = 0;
    int start = i;
    while (save[start] && save[start] != '\n') {
        start++;
        len++;
    }
	 str = (char *)malloc(sizeof(char) * (len + 2));
	 if (!str)
	 	return (NULL);
	j = 0;
	while (save[i] && save[i] != '\n')
	{
		str[j++] = save[i++];
	}
	if (save[i] == '\n')
	{
		str[j++] = '\n';
	}
	str[j] = '\0';
	return (str);
}

char	*get_read_save(int fd, char *save)
{
	char	*buff;
	int		n_bytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	n_bytes = 1;
	while (!save || (!ft_strchr(save, '\n') && n_bytes))
	{
		n_bytes = read(fd, buff, BUFFER_SIZE);
		if (n_bytes == -1)
		{
			free(buff);
			free(save);
			return (NULL);
		}
		buff[n_bytes] = '\0';
		save = ft_strjoin(save, buff);
	}
	free(buff);
	return (save);
}

char	*get_save(char *save)
{
	int		i;
	int		pos;
	char	*str;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	i++;
	pos = 0;
	while (save[i])
		str[pos++] = save[i++];
	str[pos] = '\0';
	free(save);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = get_read_save(fd, save);
	if (!save)
		return (NULL);
	line = skip_get_line(save);
	save = get_save(save);
	return (line);
}
