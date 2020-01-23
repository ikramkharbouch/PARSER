/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikrkharb <ikrkharb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:29:55 by ikrkharb          #+#    #+#             */
/*   Updated: 2020/01/20 01:55:01 by ikrkharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_list	*Fill_camera_data(t_object *object)
{
	t_object_list 	*list;
	t_list			*cam;
	t_camera 		camera;
	int i;

	cam = NULL;
	list = object->list;
	i = 0;
	init_cam(&camera);
	while (i < object->n)
	{
		if (!ft_strcmp(list[i].key, "eye"))
			camera.eye = char_to_vec(list[i].value);
		if (!ft_strcmp(list[i].key, "look_at"))
			camera.look_at = char_to_vec(list[i].value);
		if (!ft_strcmp(list[i].key, "fov"))
			camera.fov = ft_atof(list[i].value);
		if (!ft_strcmp(list[i].key, "dist"))
			camera.dist = ft_atof(list[i].value);
		i++;
	}
	ft_lstadd(&cam, ft_lstnew(&camera, sizeof(t_camera)));
	return (cam);
}

t_list	*Fill_light_data(t_object *object)
{
	t_object_list	*list;
	t_list			*lights;
	t_light			light;
	int				i;

	lights = NULL;
	list = object->list;
	init_light(&light);
	i = 0;
	while (i < object->n)
	{
		if (!ft_strcmp(list[i].key, "origin"))
			light.origin = char_to_vec(list[i].value);
		if (!ft_strcmp(list[i].key, "intensity"))
			light.intensity = ft_atof(list[i].value);
		i++;
	}
	ft_lstadd(&lights, ft_lstnew(&light, sizeof(t_light)));
	return (lights);
}

t_list	*Fill_object_data(t_object *object)
{
	t_object_list 	*list;
	t_list			*objects;
	t_obj_type		obj;
	int				i;

	objects = NULL;
	list = object->list;
	init_obj(&obj);
	i = 0;
	while (i < object->n)
	{
		if (!ft_strcmp(list[i].key, "name"))
			obj.name = list[i].value;
		if (!ft_strcmp(list[i].key, "color"))
			obj.color = ft_atoi(list[i].value);
		if (!ft_strcmp(list[i].key, "center"))
			obj.center = char_to_vec(list[i].value);
		if (!ft_strcmp(list[i].key, "radius"))
			obj.radius = ft_atof(list[i].value);
		if (!ft_strcmp(list[i].key, "ks"))
			obj.ks = ft_atof(list[i].value);
		if (!ft_strcmp(list[i].key, "kd"))
			obj.kd = ft_atof(list[i].value);
		if (!ft_strcmp(list[i].key, "n"))
			obj.n = ft_atof(list[i].value);
		i++;
	}
	return (ft_lstnew(&obj, sizeof(t_obj_type)));
	// return (objects);
}

int Fill(t_parser *p, t_mlx *mlx)
{
	t_object 	*object;
	t_list		*camera;
	t_list		*lights;
	t_list		*objects;
	int i;

	i = 0;
	objects = NULL;
	while (i < p->n)
	{
		object = &(p->objects[i]);
		if (!strcmp(object->name, "camera"))
		{
			if (!(camera = Fill_camera_data(object)))
				return (0);
		}
		if (!strcmp(object->name, "light"))
		{
			if (!(lights = Fill_light_data(object)))
				return (0);
		}
		if (!strcmp(object->name, "object"))
		{
			ft_lstadd(&objects, Fill_object_data(object));
		}
		i++;
	}
	create_actual_objs(mlx, camera, lights, objects);
	return (1);
}
