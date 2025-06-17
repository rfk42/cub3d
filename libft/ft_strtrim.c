/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:56:50 by ahamini           #+#    #+#             */
/*   Updated: 2024/05/30 15:00:16 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (s1 == 0 || set == 0)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1 + i) - 1;
	while (j >= 0 && ft_strchr(set, s1[i + j]))
		j--;
	str = malloc(sizeof(char) * (j + 2));
	if (!str)
		return (NULL);
	while (k <= j)
	{
		str[k++] = s1[i++];
	}
	str[k] = '\0';
	return (str);
}

/*int main(void)
{
  printf("%s", ft_strtrim("llllakimllll", "l"));
}*/