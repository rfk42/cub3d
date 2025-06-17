/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:56:50 by ahamini           #+#    #+#             */
/*   Updated: 2024/05/30 15:04:04 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s1, unsigned int start, size_t len)
{
	unsigned int	strlen;
	unsigned int	i;
	char			*s2;

	i = 0;
	if (!s1)
		return (NULL);
	strlen = ft_strlen((char *)s1);
	if (start > strlen)
		return (ft_strdup(""));
	s1 = s1 + start;
	while (s1[i] && len--)
		i++;
	s2 = malloc(sizeof(char) * (i + 1));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, i + 1);
	return (s2);
}

/*int main(void)
{
  printf("%s\n", ft_substr("abcdakimdcba", 20, 2));
  printf("%s\n", ft_substr("abcdakimdcba", 5, 4));
}*/
