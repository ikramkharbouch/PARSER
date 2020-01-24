/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikrkharb <ikrkharb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 18:09:32 by ikrkharb          #+#    #+#             */
/*   Updated: 2020/01/24 14:56:50 by ikrkharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		light_exists(t_parser *p)
{
	t_object		*object;
	int				name;
	int				i;

	i = 0;
	while (i < p->n)
	{
		object = &(p->objects[i]);
		name = get_name(object->name);
		if (i == 1 && !(name == LIGHT))
			return (0);
		if (name == LIGHT)
			return (1);
		i++;
	}
	return (0);
}

int		order_exists(t_object *object)
{
	t_object_list	*list;
	int				name;

	name = get_name(object->name);
	list = object->list;
	if (name == CAMERA)
	{
		if (!(object->n == 3))
			return (0);
		if (!(check_cam_keys(list)))
			return (0);
	}
	if (name == LIGHT)
	{
		if (!(object->n == 2))
			return (0);
		if (!(check_light_keys(list)))
			return (0);
	}
	if (name == SHAPE)
	{
		// if (!(object->n == 4))
		// 	return (0);
		if (!(check_shape_keys(list)))
			return (0);
	}
	return (1);
}

int		camera_exists(t_parser *p)
{
	t_object	*object;
	int			counter;
	int			name;
	int			i;
	
	
	counter = 0;
	i = 0;
	while (i < p->n)
	{
		object = &(p->objects[i]);
		name = get_name(object->name);
		if (i == 0 && !(name == CAMERA))
			return (0);
		if (name == CAMERA)
			counter++;
		i++;
	}
	if (counter == 1)
		return (1);
	return (0);
}

int		check(t_parser *p)
{
	t_object		*object;
	int				i;

	if (!(camera_exists(p)) || !(light_exists(p)))
		return (0);
	i = 0;
	while (i < p->n)
	{
		object = &(p->objects[i]);
		if (!order_exists(object))
			return (0);
		i++;
	}
	return (1);
}