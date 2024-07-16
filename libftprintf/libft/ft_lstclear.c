/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:02:19 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/09 15:58:49 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current_elem;
	t_list	*next_elem;

	current_elem = *lst;
	while (current_elem)
	{
		next_elem = current_elem->next;
		ft_lstdelone(current_elem, del);
		current_elem = next_elem;
	}
	*lst = NULL;
}
