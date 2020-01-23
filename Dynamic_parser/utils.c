/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikrkharb <ikrkharb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 22:53:57 by ikrkharb          #+#    #+#             */
/*   Updated: 2020/01/19 18:29:23 by ikrkharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			is_comment(char *str)
{
	while (ft_is_whitespace(*str))
		str++;
	return (*str == '#');
}

int		is_object(char *str)
{
	return (strchr(str, ':') && !strchr(str, '-'));
}

int		is_list(char *str)
{
	return (strchr(str, ':') && strchr(str, '-'));
}

char		*pretty_name(char *str)
{
	int	i;

	i = 0;
	while (!ft_isalnum(str[i]))
	{
		str[i] = ' ';
		i++;
	}
	i = ft_strlen(str) - 1;
	while (!ft_isalnum(str[i]))
	{
		str[i] = ' ';
		i--;
	}
	return (ft_strtrim(str));
}

int			get_type(char *str)
{
	if (!*str)
		return (NEW_LINE);
	else if (is_comment(str))
		return (COMMENT);
	else if (is_object(str))
		return (OBJECT);
	else if (is_list(str))
		return (KEY);
	return (VALUE);
}

int			get_name(char *str)
{
	if (!ft_strcmp(str, "camera"))
		return (CAMERA);
	else if (!(ft_strcmp(str, "light")))
		return (LIGHT);
	else if (!(ft_strcmp(str, "object")))
		return (SHAPE);
	return (-1);
}