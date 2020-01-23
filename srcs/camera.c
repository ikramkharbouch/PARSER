/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera->c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikrkharb <ikrkharb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 20:15:26 by ikrkharb          #+#    #+#             */
/*   Updated: 2020/01/02 23:07:34 by ikrkharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

/*
** U = left, V = right
** Direction = viewPlanePoint - eye
*/
float		get_dist(t_vec eye, t_vec look_at)
{
	float 	result;
	float	a;
	float	b;
	float	c;

	a = pow((look_at.x - eye.x), 2);
	b = pow((look_at.y - eye.y), 2);
	c = pow((look_at.z - eye.z), 2);
	result = sqrtf(a + b + c);
	return (result);
}

t_camera	ft_create_cam(t_vec eye, t_vec look_at, float fov)
{
	t_camera 	camera;
	t_vec		up;
	float		dist;

	dist 					= get_dist(eye, look_at);
	up 						= (t_vec){0.0, 1.0, 0.0};
	camera.fov 				= DEG_TO_RAD(fov);
	camera.eye 				= eye;
	camera.look_at			= look_at;
	camera.view_dir 		= vec_normalize(vec_sub(look_at, eye));
	camera.u 				= vec_normalize(vec_cross(up, camera.view_dir));
	camera.v 				= vec_cross(camera.view_dir, camera.u);
	camera.h_width 			= tan(camera.fov / 2.0) * 2.0 * dist;
	camera.aspect_ratio 	= (float)HEIGHT / (float)WIDTH;
	camera.h_height 		= camera.aspect_ratio * camera.h_width;
	camera.bottom_left 		= vec_sub(camera.look_at, vec_sum(vec_kscale(camera.h_height, camera.v), vec_kscale(camera.h_width, camera.u)));

	/*
    ** They give our viewplane coordinates for each pixel.
    */

   	camera.x_incv = vec_kscale(2.0 * camera.h_width, camera.u);
	camera.y_incv = vec_kscale(2.0 * camera.h_height, camera.v);
	return (camera);
}

/*
** ray.dir = (t_vec3){0, 0, 1};
** ray.dir = vec3_normalize(ray.dir);
*/

/*
** returning a ray that passes from the eye point.
*/

t_ray	generate_ray(t_camera *camera, int x, int y)
{
	t_ray ray;
	t_vec plane_point;

	ray.origin = camera->eye;
	ray.dist   = 100;
	/*
    ** x and y are the viewplane coordinates for each pixel
    */
   	plane_point = vec_sum(camera->bottom_left, vec_sum(vec_kscale((float)x / (float)WIDTH, camera->x_incv), vec_kscale((float)y / (float)HEIGHT, camera->y_incv)));
   	ray.dir = vec_sub(plane_point, camera->eye);
   	return (ray);
}

