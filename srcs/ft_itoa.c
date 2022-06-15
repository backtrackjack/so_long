/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:04:05 by jsellars          #+#    #+#             */
/*   Updated: 2022/06/15 13:04:08 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_numlen(int n)
{
	int	numlen;

	numlen = 0;
	while (n != 0)
	{
		n = n / 10;
		numlen++;
	}
	return (numlen);
}

static char	*itoa_neg(int n, int i, char *s)
{
	s[i++] = '-';
	while (n / 10 != 0)
	{
		s[i] = -(n % -10) + 48;
		n /= 10;
		i++;
	}
	s[i] = -(n) + 48;
	return (s);
}

static char	*itoa_pos(int n, int i, char *s)
{
	while (n / 10 != 0)
	{
		s[i] = n % 10 + 48;
		n /= 10;
		i++;
	}
	s[i] = n + 48;
	return (s);
}

static char	*reverse_arr(char *arr, int start)
{
	int		last;
	char	temp_value;

	last = ft_strlen(arr) - 1;
	while (last >= start)
	{
		temp_value = arr[start];
		arr[start] = arr[last];
		arr[last] = temp_value;
		start++;
		last--;
	}
	return (arr);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * ft_numlen(n) + 2);
	if (str == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		str = itoa_neg(n, i, str);
		str = reverse_arr(str, 1);
	}
	else
	{
		str = itoa_pos(n, i, str);
		str = reverse_arr(str, 0);
	}
	return (str);
}
