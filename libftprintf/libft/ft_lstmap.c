/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:20:17 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/10 09:56:39 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*new;
	void	*new_content;

	if (!lst)
		return (NULL);
	new_content = f(lst->content);
	map = ft_lstnew(new_content);
	if (!map)
		del(new_content);
	while (map && lst->next)
	{
		lst = lst->next;
		new_content = f(lst->content);
		new = ft_lstnew(new_content);
		if (!new)
		{
			del(new_content);
			ft_lstclear(&map, del);
			return (NULL);
		}
		ft_lstadd_back(&map, new);
	}
	return (map);
}
