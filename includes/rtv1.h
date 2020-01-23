/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikrkharb <ikrkharb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 17:17:06 by ikrkharb          #+#    #+#             */
/*   Updated: 2020/01/23 19:09:17 by ikrkharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
#define RTV1_H

#include "mlx.h"
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"
#include "../Dynamic_parser/parser.h"
#define HEIGHT 800
#define WIDTH 800
#define DEG_TO_RAD(X) (X * (M_PI / 180.0));
#define FALSE 1e+30

typedef struct s_point
{
	float x;
	float y;
	float z;
} t_point;

typedef t_point t_vec;

typedef struct s_camera
{
	t_point eye;
	t_point look_at;
	t_vec up;
	t_vec u;
	t_vec v;
	t_vec view_dir;
	t_vec bottom_left;
	t_vec x_incv;
	t_vec y_incv;
	float aspect_ratio;
	float fov;
	float h_width;
	float h_height;
	float dist;
} t_camera;

typedef struct s_mlx
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	char *img_data;
	int bpp;
	int s_l;
	int en;
	int x;
	int y;
} t_mlx;

typedef struct 	s_obj_type
{
	char 	*name;
	int		color;
	t_vec 	center;
	t_vec	vec_dir; // For rotation
	float 	radius;
	float	alpha;
	float 	ks;
	float 	kd;
	float 	n;
	float	t;
} 				t_obj_type;

typedef struct s_light
{
	t_point 	origin;
	t_vec 		dir;
	float 		intensity;
	struct s_light *next;
} t_light;

typedef struct 	s_ray
{
	t_point origin;
	t_vec 	dir;
	float 	dist;
} 				t_ray;

typedef	struct s_scene
{
	t_camera	camera;
	t_light		light;
	t_obj_type	obj_type;
}				t_scene;

typedef struct s_closest
{
	char 	*name;
	float 	t;
}				t_closest;

void 	ft_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int 	mouse_press(int button, int x, int y, void *param);
int 	key_press(int keycode, void *param);
int 	close_win(void *param);
void	ft_mlx_window(t_mlx *mlx);

void 	camera_setup(t_camera *camera);
t_ray 	generate_ray(t_camera *camera, int i, int j);
void	debug_camera(t_list *camera);

float 	vec_dot(t_vec v1, t_vec v2);
float 	vec_dot_x_z(t_vec v1, t_vec v2);
t_vec 	vec_sub(t_vec v1, t_vec v2);
t_vec 	vec_sum(t_vec v1, t_vec v2);
t_vec 	vec_scale(t_vec v1, t_vec v2);
t_vec 	vec_kscale(float k, t_vec v2);
t_vec 	vec_cross(t_vec v1, t_vec v2);
t_vec 	vec_normalize(t_vec v);
t_vec 	vec_kdiv(t_vec v, float k);

/* TO DELETE */
void 	print_obj_props(t_object *object);
void 	print_light_props(t_light *light);
void 	read_object_values(int fd, t_object *object);
void 	read_light_values(int fd, t_light *light);
void 	print_cam_props(t_camera *camera);

void print_cam_props(t_camera *camera);
void print_light_props(t_light *light);
/**/

void 		init_cam(t_camera *camera);
void 		init_light(t_light *light);
void 		init_obj(t_obj_type *obj);
int 		get_data(char *filename, t_mlx *mlx);
t_vec 		char_to_vec(char *str);

t_list		*Fill_object_data(t_object *object);
t_list		*Fill_camera_data(t_object *object);
t_list		*Fill_light_data(t_object *object);
int 		Fill(t_parser *p, t_mlx *mlx);

t_camera	ft_create_cam(t_vec eye, t_vec look_at, float fov);
float 		intersect_ray_sphere(t_ray *ray, t_vec center, float radius);
float 		intersect_ray_cone(t_ray *ray, t_vec center);
float 		intersect_ray_plane(t_ray *ray, t_point p0, t_vec normal);
float 		intersect_ray_cylinder(t_ray *ray, float radius);
void		ft_draw_objects(t_mlx *mlx, t_camera camera, t_list *objects);

void		create_actual_objs(t_mlx *mlx, t_list *camera, t_list *lights,t_list *objects);
t_obj_type 	*find_inter(t_mlx *mlx, t_camera camera, t_list *objects, int i, int j);

#endif