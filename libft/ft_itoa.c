/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:21:00 by dpiedra           #+#    #+#             */
/*   Updated: 2021/05/26 15:14:32 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	getitoalen(long n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	n /= 10;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static int	itoa_divpow(long n)
{
	int	div;

	div = 1;
	if (n < 0)
		n = -n;
	n /= 10;
	while (n)
	{
		div *= 10;
		n /= 10;
	}
	return (div);
}

static void	itoa_assign(char *str, size_t len, int div, long n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		str[i++] = '-';
		n = -n;
	}
	while (i < len)
	{
		str[i] = ((n / div) % 10) + '0';
		i++;
		div /= 10;
	}
	str[i] = '\0';
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*str;
	int		div;
	long	ln;

	ln = (long)n;
	len = getitoalen(ln);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	div = itoa_divpow(ln);
	itoa_assign(str, len, div, ln);
	return (str);
}
