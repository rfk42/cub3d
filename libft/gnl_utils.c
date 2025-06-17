/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:49:32 by alexa             #+#    #+#             */
/*   Updated: 2025/05/22 12:25:37 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strcpy(char *dst, const char *src)
{
    size_t i = 0;
    while (src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return dst;
}

char *ft_strcat(char *dst, const char *src)
{
    size_t i = 0;
    size_t dst_len = ft_strlen(dst);

    while (src[i] != '\0')
    {
        dst[dst_len + i] = src[i];
        i++;
    }
    dst[dst_len + i] = '\0';
    return dst;
}

int find_newline(const char *str)
{
    int i = 0;
    if (!str)
        return -1;
    while (str[i])
    {
        if (str[i] == '\n')
            return i;
        i++;
    }
    return -1;
}

void shift_buffer(char *buffer, int newline_pos)
{
    int i = 0;
    while (buffer[newline_pos + 1 + i])
    {
        buffer[i] = buffer[newline_pos + 1 + i];
        i++;
    }
    buffer[i] = '\0';
}

char *join_line(char *line, const char *buffer)
{
    size_t len_line;
    size_t len_buf;
    char *new_line;

    if (line)
        len_line = ft_strlen(line);
    else
        len_line = 0;

    len_buf = ft_strlen(buffer);
    new_line = malloc(len_line + len_buf + 1);
    if (!new_line)
        return NULL;

    if (line)
    {
        ft_strcpy(new_line, line);
        free(line);
    }
    else
        new_line[0] = '\0';

    ft_strcat(new_line, buffer);
    return new_line;
}
