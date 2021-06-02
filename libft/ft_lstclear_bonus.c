/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:02:58 by dpiedra           #+#    #+#             */
/*   Updated: 2021/05/26 15:08:39 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*element;
	t_list	*successor;

	if (!lst || !*lst || !del)
		return ;
	element = *lst;
	while (element)
	{
		successor = element->next;
		(*del)((void *)element->content);
		free(element);
		element = successor;
	}
	*lst = NULL;
}
