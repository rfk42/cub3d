/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:56:50 by ahamini           #+#    #+#             */
/*   Updated: 2024/05/30 15:02:26 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n-- > 1 && (*(unsigned char *)s1 == *(unsigned char *)s2))
	{
		s1 = (unsigned char *)s1 + 1;
		s2 = (unsigned char *)s2 + 1;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/*int	main(void)
{
	char	s1[] = {-127, 0, 127, 0};
	char	s2[] = {-128, 0, 127, 0};
	printf("%d\n", ft_memcmp(s1, s2, 4));
}*/
