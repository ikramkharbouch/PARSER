/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikrkharb <ikrkharb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 19:07:50 by ikrkharb          #+#    #+#             */
/*   Updated: 2020/01/20 01:52:14 by ikrkharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		check_cam_keys(t_object_list *list)
{
	if (ft_strcmp(list[0].key, "eye"))
		return (0);
	if (ft_strcmp(list[1].key, "look_at"))
		return (0);
	if (ft_strcmp(list[2].key, "fov"))
		return (0);
	return (1);
}

int		check_light_keys(t_object_list *list)
{
	if (ft_strcmp(list[0].key, "origin"))
		return (0);
	if (ft_strcmp(list[1].key, "intensity"))
		return (0);
	if (ft_strcmp(list[2].key, "ks"))
		return (0);
	if (ft_strcmp(list[3].key, "kd"))
		return (0);
	if (ft_strcmp(list[4].key, "n"))
		return (0);
	// check if ks and kd are > 0 && < 1
	if (ft_atof(list[2].value) < 0 || ft_atof(list[2].value) > 1)
		return (0);
	if (ft_atof(list[3].value) < 0 || ft_atof(list[3].value) > 1)
		return (0);
	return (1);
}

int		check_shape_keys(t_object_list *list)
{
	if (ft_strcmp(list[0].key, "name"))
		return (0);
	if (ft_strcmp(list[1].key, "center"))
		return (0);
	if (ft_strcmp(list[2].key, "radius"))
		return (0);
	if (ft_strcmp(list[3].key, "color"))
		return (0);
	return (1);
}