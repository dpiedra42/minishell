/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:21:00 by dpiedra           #+#    #+#             */
/*   Updated: 2019/11/18 14:22:42 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nlength(long n)
{
	size_t len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char		*ft_makestr(long int n, char *str, int neg, char nlength)
{
	if (neg == 1)
		str[0] = '-';
	while (n > 0)
	{
		str[nlength - 1] = n % 10 + '0';
		n = n / 10;
		nlength--;
	}
	return (str);
}

char			*ft_itoa(int n)
{
	char		*str;
	size_t		nlen;
	int			neg;
	long		num;

	neg = 0;
	num = (long)n;
	nlen = ft_nlength(num);
	if (num == 0)
	{
		return (str = ft_strdup("0"));
	}
	if (num < 0)
	{
		num = num * -1;
		neg = 1;
	}
	if (!(str = malloc(sizeof(char) * (nlen + 1))))
		return (NULL);
	str = ft_makestr(num, str, neg, nlen);
	str[nlen] = '\0';
	return (str);
}
