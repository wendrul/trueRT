/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indexof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:51:09 by agoodwin          #+#    #+#             */
/*   Updated: 2019/11/10 19:30:51 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_indexof(char needle, const char *hay)
{
	int i;

	i = -1;
	while (hay[++i])
		if (hay[i] == needle)
			return (i);
	return (-1);
}
