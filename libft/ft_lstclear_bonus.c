/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:41:23 by aafrikya          #+#    #+#             */
/*   Updated: 2023/06/26 16:41:24 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*de;

	if (!del || !lst || !*lst)
		return ;
	while (*lst)
	{
		de = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = de;
	}
}
