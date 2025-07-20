/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galauren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:26:32 by galauren          #+#    #+#             */
/*   Updated: 2025/07/12 20:28:29 by galauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	is_sign_at_valid_pos(const char *s, int i)
{
	if (i == 0)
		return (1);
	return (0);
}

static int	is_valid_double_char_extended(const char *s, int i)
{
	if (s[i] == '+')
	{
		if (!is_sign_at_valid_pos(s, i))
			return (0);
	}
	else if (!ft_isdigit(s[i]))
		return (0);
	return (1);
}

int	is_valid_double_str(const char *s)
{
	int			i;

	i = 0;
	while (s[i])
	{
		if (!is_valid_double_char_extended(s, i))
			return (0);
		i++;
	}
	return (1);
}

double	ft_strtod(const char *s)
{
	int		i;
	int		sign;
	double	val;

	i = 0;
	sign = 1;
	val = 0.0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\v' || s[i] == '\f' || s[i] == '\r')
		i++;
	if (!is_valid_double_str(s))
		return (printf("Error: malformed number input.\n"), NAN);
	if (s[i] == '+')
		i++;
	while (ft_isdigit(s[i]))
		val = val * 10.0 + (s[i++] - '0');
	if (s[i] != '\0')
		return (printf(
				"Error: unexpected characters after number.\n"), NAN);
	return (sign * val);
}
