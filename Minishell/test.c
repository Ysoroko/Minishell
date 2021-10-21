/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:55:22 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/21 16:56:12 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int ft_strcmp(const char *s1, const char *s2)
{
    int i;
    i = 0;
    int result;

    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] < s2[i])
            return (-1);
        else if (s1[i] > s2[i])
            return (1);
        i++;
    }
	if (s1[i] < s2[i])
        return (-1);
	else if (s1[i] > s2[i])
        return (1);
    return (0);
}

int main()
{
    printf("%d\n", ft_strcmp("hello", "hello"));
    printf("%d\n", ft_strcmp("hell", "hello"));
    printf("%d\n", ft_strcmp("hello", "hell"));
    return (0);
}