/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:56:50 by ahamini           #+#    #+#             */
/*   Updated: 2024/05/30 15:03:38 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (dst == 0 && src == 0)
		return (0);
	while (dst[j] && j < size)
		j++;
	while (src[i] && j + i < size - 1 && size)
	{
		dst[j + i] = src[i];
		i++;
	}
	if (j < size)
		dst[j + i] = '\0';
	while (src[i])
		i++;
	return (j + i);
}

/*int	main(void)
{
	char	dst[20] = "je suis";
	char	*src;
	int	size;

	size = 20;
	src = " akim";
	printf("%zu\n", ft_strlcat(dst, src, size));
	printf("%s\n", dst);
	return (0);
}*/
