/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 10:48:58 by dpiedra           #+#    #+#             */
/*   Updated: 2020/02/06 10:49:37 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_neg_nbr(int neg, int base, int nbr)
{
	if (base == 10 && nbr < 0)
		neg = 1;
	else
		neg = 0;
	return (neg);
}

int		ft_count_space(int base, int i)
{
	if (i == 0)
		return (1);
	else
		return (base * ft_count_space(base, i - 1));
}

char	*ft_itoa_base(int nbr, int base)
{
	int		i;
	char	*str;
	int		neg;

	i = 1;
	neg = 0;
	neg = ft_neg_nbr(neg, base, nbr);
	if (nbr < 0)
		nbr *= -1;
	while (ft_count_space(base, i) - 1 < nbr)
		i++;
	str = (char*)malloc(sizeof(str) * i);
	str[i] = '\0';
	while (i-- > 0)
	{
		if (nbr % base > 9)
			str[i + neg] = (nbr % base) + 'a' - 10;
		else
			str[i + neg] = (nbr % base) + '0';
		nbr = nbr / base;
	}
	if (neg == 1)
		str[0] = '-';
	return (str);
}
