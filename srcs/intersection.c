/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikrkharb <ikrkharb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 23:00:09 by ikrkharb          #+#    #+#             */
/*   Updated: 2020/01/23 19:12:27 by ikrkharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

float		intersect_ray_sphere(t_ray *ray, t_vec center, float radius) // object 
{
	t_vec oc;
	float a;
	float b;
	float c;
	float t1; 
	float t2;

	oc = vec_sub(ray->origin, center); // Origin - center of sphere
	a = vec_dot(ray->dir, ray->dir);
	b = 2.0 * vec_dot(oc, ray->dir);
	c = vec_dot(oc, oc) - (radius * radius);
	if ((b * b) - (4 * a * c) < 0)
		return (FALSE);
	t1 = (- b + sqrt((b * b) - (4 * a * c))) / (2 * a);
	t2 = (- b - sqrt((b * b) - (4 * a * c))) / (2 * a);
	if (t1 > 0.2 && t1 < 100000)
		return (t1);
	if (t2 < 0.2 && t2 < 100000)
		return (t2);
	return(FALSE);
}

float	intersect_ray_cylinder(t_ray *ray, float radius)
{
	t_vec	va = (t_vec){0,0,0};
	t_point	pa =(t_point){0,1,1};
	float a;
	float b;
	float c;
	float t1, t2;
	t_vec	delta_p;

	delta_p = vec_sub(ray->origin, pa);
	a = vec_dot(vec_sub(va, vec_kscale(vec_dot(ray->dir, va), va)),vec_sub(va, vec_kscale(vec_dot(ray->dir, va), va)));
	b = 2 * vec_dot(vec_sub(va, vec_kscale(vec_dot(ray->dir, va), va)),(vec_sub(delta_p, vec_kscale(vec_dot(delta_p, va), va))));
	c = vec_dot(vec_sub(delta_p, vec_kscale(vec_dot(delta_p, va), va)), vec_sub(delta_p, vec_kscale(vec_dot(delta_p, va), va))) - (radius * radius);
	if ((b * b - 4 * a * c) < 0)
		return (FALSE);
	t1 = (- b + sqrt(b * b - 4 * a * c)) / (2 * a);
	t2 = (- b - sqrt(b * b - 4 * a * c)) / (2 * a);
	if (t1 > 0.1 && t1 < 10000)
		return (t1);
	else if (t2 > 0.1 && t2 < 10000)
		return (t2);
	return (FALSE);
}

float	intersect_ray_plane(t_ray *ray, t_point	p0, t_vec normal)
{
	t_vec p0l0;
	float	t;
	float	denom;
	
	denom = vec_dot(normal, ray->dir);
	if (fabs(denom) > 1e-6)
	{
		p0l0 = vec_sub(p0 , ray->origin);
		t = vec_dot(p0l0, normal) / denom;
		if (t >= 0)
			return (t);
	}
	return (FALSE); // false
}

float 		intersect_ray_cone(t_ray *ray, t_vec center)
{
	t_vec 	va = (t_vec){0,-1,0};
	float alpha = DEG_TO_RAD(30);
	float a;
	float b;
	float c;
	float v_va = vec_dot(ray->dir,va);
	t_vec delta_p = vec_sub(ray->origin, center);
	float t1;
	float t2;
	
	a = pow(cos(alpha), 2) * vec_dot(vec_sub(ray->dir, vec_kscale(v_va, va)), vec_sub( ray->dir, vec_kscale(v_va, va))) - pow(sin(alpha),2) * v_va * v_va;
	b = 2 * pow(cos(alpha), 2) * vec_dot(vec_sub(ray->dir, vec_kscale(v_va, va)), vec_sub(delta_p, vec_kscale(vec_dot(delta_p, va), va))) - 2 * pow(sin(alpha),2) * v_va * vec_dot(delta_p, va);
	c = pow(cos(alpha), 2) * vec_dot(vec_sub(delta_p, vec_kscale(vec_dot(delta_p, va),va)), vec_sub(delta_p, vec_kscale(vec_dot(delta_p, va),va))) - pow(sin(alpha),2) * pow(vec_dot(delta_p, va), 2);
	if (b * b - (4 * a * c) < 0)
		return (FALSE);
	t1 = (-b - sqrt(b * b - (4 * a * c))) / 2 * a; 
	t2 = (-b + sqrt(b * b - (4 * a * c))) / 2 * a; 
	if (t1 > 1 && t1 < 2000)
		return(t1);
	if (t2 >1 && t2 < 2000)
		return(t2);
	return (FALSE);
}