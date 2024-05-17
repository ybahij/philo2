/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_f3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:57:36 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/01 15:14:24 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int ft_space(char c)
{
    if ((c >= 9 && c <= 13) || c == 32)
        return (1);
    else
        return (0);
}

int if_is_digit(const char *str)
{
    while (*str)
    {
        if (*str < '0' || *str > '9')
            return (0);
        str++;
    }
    return (1);
}

long ft_atol(const char *s)
{
    const char *str;
    long n;

    n = 0;
    str = valid_str(s);
    while (*str >= '0' && *str <= '9')
        n = (n * 10) + (*str++ - '0');
    if (n > INT_MAX)
        ft_error("the value is to big, INTMAX is the limit\n");
    return (n);
}