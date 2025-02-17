/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:46:09 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/14 10:50:03 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int	i;
	int	nbr;
	int	sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr * sign);
}

int	ft_is_uint(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] == '0')
		i++;
	j = i;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	return (!str[i] && (i - j) < 11 && ft_atoi(str) > 0);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
