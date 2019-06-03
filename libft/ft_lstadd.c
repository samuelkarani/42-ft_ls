/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:51:25 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/17 23:38:40 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new_elem)
{
	t_list	**ptr;

	ptr = alst;
	new_elem->next = *alst;
	*ptr = new_elem;
}
