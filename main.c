/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-troc <hho-troc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:38:53 by hho-troc          #+#    #+#             */
/*   Updated: 2024/12/09 09:52:45 by hho-troc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#include <time.h>


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <file_name>\n", argv[0]);
        return (1);
    }
	clock_t start = clock();
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("can't open");
        return (1);
    }

    char *line;
	int i = 1;
    while ((line = get_next_line(fd)))
    {
        //printf("%s", line);
		printf("line [%02d]: %s", i, line);
        free(line);
		i++;
    }

    if (close(fd) < 0)
    {
        perror("can't close");
        return (1);
    }
	clock_t end = clock();
    printf("Time taken: %.9f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return (0);
}
/* int	main(int argc, char **argv)
{
	int	fd;
	char	*line;

	(void)argc;
	fd = open(argv[1], O_RDONLY);
	line = "";
	while (line != NULL)
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
	fd = close(fd);
	return (0);
}
 */