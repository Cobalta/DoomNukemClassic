/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: brey-gal <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/09 14:33:34 by brey-gal     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/17 18:15:46 by brey-gal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fillstr(int n, int len, char *dst)
{
	while (len--)
	{
		dst[len] = n % 10 + '0';
		n /= 10;
	}
	return (dst);
}

char		*ft_itoa(int n)
{
	int		len;
	int		nb;
	int		isnegat;
	char	*dst;

	isnegat = 0;
	len = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n *= -1;
		len++;
		isnegat = 1;
	}
	nb = n;
	while (nb /= 10)
		len++;
	if (!(dst = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	dst[len] = '\0';
	dst = ft_fillstr(n, len, dst);
	if (isnegat)
		dst[0] = '-';
	return (dst);
}
