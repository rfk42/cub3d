/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:56:50 by ahamini           #+#    #+#             */
/*   Updated: 2024/05/30 15:03:45 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src [i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[j])
		j++;
	return (j);
}

/*int	main(void)
{
	char	dst[10];
	char	*src;
	int	size;

	size = 10;
	src = "akim";
	printf("%zu\n", ft_strlcpy(dst, src, size));
	printf("%s\n", dst);
	return (0);
}*/
