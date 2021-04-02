/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:18:48 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/02 17:09:56 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*alst;
	t_list	*newlst;
	void	*tmp;

	if (!lst || !f)
		return (NULL);
	tmp = (*f)(lst->content);
	if (!(newlst = ft_lstnew(tmp)))
		return (NULL);
	alst = newlst;
	lst = lst->next;
	while (lst)
	{
		tmp = (*f)(lst->content);
		if (!(newlst->next = ft_lstnew(tmp)))
		{
			ft_lstclear(&alst, del);
			return (NULL);
		}
		newlst = newlst->next;
		lst = lst->next;
	}
	return (alst);
}
