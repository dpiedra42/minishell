/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:40:55 by dpiedra           #+#    #+#             */
/*   Updated: 2021/05/26 15:08:19 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*new;
	void	*tmp;

	if (!lst || !f)
		return (NULL);
	tmp = (*f)(lst->content);
	new = ft_lstnew(tmp);
	if (!(new))
		return (NULL);
	result = new;
	lst = lst->next;
	while (lst)
	{
		tmp = (*f)(lst->content);
		new->next = ft_lstnew(tmp);
		if (!(new->next))
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	return (result);
}
