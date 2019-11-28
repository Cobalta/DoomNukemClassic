/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: brey-gal <brey-gal@student.42.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 14:28:41 by brey-gal     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/28 22:01:46 by brey-gal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dest;

	i = 0;
	while (s[i])
		i++;
	if (!(dest = (char *)malloc(sizeof(char) * i + 1)))
		return (dest);
	dest[i] = '\0';
	i--;
	while (i >= 0)
	{
		dest[i] = s[i];
		i--;
	}
	return (dest);
}
