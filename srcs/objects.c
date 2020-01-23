/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikrkharb <ikrkharb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 20:28:39 by ikrkharb          #+#    #+#             */
/*   Updated: 2020/01/23 19:20:05 by ikrkharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_obj_type *find_inter(t_mlx *mlx, t_camera camera, t_list *objects, int i, int j)
{
	(void)mlx;
	t_ray ray;
	t_obj_type *objec = (t_obj_type *)malloc(sizeof(t_obj_type));
	t_obj_type *obj1;
	t_list 		*tmp;

	camera = ft_create_cam(camera.eye, camera.look_at, camera.fov);
	ray = generate_ray(&camera, i, j);
	tmp = objects;
	while (tmp)
	{
		obj1 = (t_obj_type *)tmp->content;
		if (!(ft_strcmp(obj1->name, "sphere")))
			obj1->t = intersect_ray_sphere(&ray, obj1->center, obj1->radius);
		if (!(ft_strcmp(obj1->name, "plane")))
			obj1->t = intersect_ray_plane(&ray, obj1->center, (t_vec){0, 1, 0});
		if (!(ft_strcmp(obj1->name, "cone")))
			obj1->t = intersect_ray_cone(&ray, obj1->center);
		if (!(ft_strcmp(obj1->name, "cylinder")))
			obj1->t = intersect_ray_cylinder(&ray, obj1->radius);
		tmp->content = (t_obj_type *)obj1;
		tmp = tmp->next;
	}
	while (objects && objects->next)
	{
		if (((t_obj_type *)objects->content)->t < ((t_obj_type *)objects->next->content)->t)
			objec = (t_obj_type *)objects->content;
		objects = objects->next;
	}
	if (objec->t - FALSE == 0)
		return (NULL);
	return(objec);
}

void create_actual_objs(t_mlx *mlx, t_list *camera, t_list *lights, t_list *objects)
{
	t_camera *cam;
	(void)lights;

	cam = camera->content;
	ft_draw_objects(mlx, *cam, objects);
}

void		ft_draw_objects(t_mlx *mlx, t_camera camera, t_list *objects)
{
	//t_ray 		ray;
	t_obj_type	*obj;
	int			i;
	int			j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			obj = find_inter(mlx, camera, objects, i, j);
			if (obj == NULL)
			{	printf("i am here\n");
				ft_mlx_pixel_put(mlx, i, j, 0);
			}
				
			ft_mlx_pixel_put(mlx, i, j, obj->color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}

