/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikrkharb <ikrkharb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 21:05:55 by ikrkharb          #+#    #+#             */
/*   Updated: 2020/01/21 16:29:12 by ikrkharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <fcntl.h>
#include <stdio.h>
#include "../libft/libft.h"

# define NEW_LINE	1
# define COMMENT	2
# define OBJECT		3
# define KEY		4
# define VALUE		5

# define CAMERA		6
# define LIGHT		7
# define SHAPE		8 

typedef struct		s_object_list
{
	char			*key;
	char			*value;
}					t_object_list;

typedef struct		s_object
{
	int				n;
	char			*name;
	t_object_list	list[10];
}					t_object;

typedef struct		s_parser
{
	int				n;
	t_object		objects[10];
}					t_parser;

t_parser			*parse(char *filename);
void				free_parser(t_parser **p);
void				pretty_parser(t_parser *p);

int					is_comment(char *str);
int					is_object(char *str);
int					is_list(char *str);
char				*pretty_name(char *str);
int					get_type(char *str);
int					get_name(char *str);

int					check(t_parser *p);
int					check_cam_keys(t_object_list *list);
int					check_light_keys(t_object_list *list);
int					check_shape_keys(t_object_list *list);

#endif
