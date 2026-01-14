/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiturria <aiturria@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:59:46 by aiturria          #+#    #+#             */
/*   Updated: 2023/12/10 11:43:33 by aiturria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> 
#include <stdlib.h>

int	ft_atoi(const char *str)
{
	int	minus;
	int	result;

	result = 0;
	minus = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus *= -1;
		str++;
	}
	if (*str < '0' || *str > '9')
	{
		return (0);
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * minus);
}

/*int	main(void)
{
	char a[17] = " -965ab567";
	
	printf("%d\n", ft_atoi(a));
	printf("%d", atoi(a));
	return (0);
}*/
