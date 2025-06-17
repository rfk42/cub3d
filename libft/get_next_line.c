/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:48:24 by alexa             #+#    #+#             */
/*   Updated: 2025/05/22 12:33:55 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *s, size_t n)
{
    size_t i;
    char *dup;

    i = 0;
    while (s[i] && i < n)
        i++;
    dup = malloc(i + 1);
    if (!dup)
        return NULL;
    i = 0;
    while (s[i] && i < n)
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}

static int read_into_buffer(int fd, char *buffer)
{
    int bytes_read;

    if (!buffer[0])
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
            return bytes_read;
        buffer[bytes_read] = '\0';
    }
    return 1;
}

static int process_buffer(char *buffer, char **line)
{
    int newline_pos = find_newline(buffer);

    if (newline_pos >= 0)
    {
        char *tmp = ft_strndup(buffer, newline_pos + 1);
        if (!tmp)
            return -1;
        *line = join_line(*line, tmp);
        free(tmp);
        if (!*line)
            return -1;
        shift_buffer(buffer, newline_pos);
        return 1;
    }
    else
    {
        *line = join_line(*line, buffer);
        if (!*line)
            return -1;
        buffer[0] = '\0';
    }
    return 0;
}

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    char *line = NULL;
    int ret;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    while (1)
    {
        ret = read_into_buffer(fd, buffer);
        if (ret <= 0)
            break;
        ret = process_buffer(buffer, &line);
        if (ret != 0)
            break;
    }

    if (ret == -1 || (ret == 0 && (!line || !*line)))
    {
        free(line);
        return NULL;
    }
    return line;
}
