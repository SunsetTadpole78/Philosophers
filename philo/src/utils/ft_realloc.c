/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:20:04 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/17 09:22:02 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*t;
	unsigned char	*r;

	i = 0;
	t = (unsigned char *)dest;
	r = (unsigned char *)src;
	if (n == 0)
		return (t);
	if (!t && !r)
		return (NULL);
	while (i < n)
	{
		t[i] = r[i];
		i++;
	}
	return (t);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*temp;

	if (!new_size)
		new_size = 1;
	temp = malloc(new_size);
	if (!temp)
		return (NULL);
	if (ptr)
	{
		if (old_size < new_size)
			new_size = old_size;
		ft_memcpy(temp, ptr, new_size);
		free(ptr);
	}
	return (temp);
}
