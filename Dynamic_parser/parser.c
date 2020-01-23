/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikrkharb <ikrkharb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 21:33:14 by ikrkharb          #+#    #+#             */
/*   Updated: 2020/01/21 16:18:30 by ikrkharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser	*new_parser()
{
	t_parser	*p;

	p = (t_parser *)malloc(sizeof(t_parser));
	if (!p)
		return (NULL);
	p->n = 0;
	return (p);
}

void		free_parser(t_parser **p)
{
	ft_memdel((void **)p);
}

int			parse_object(t_object *object, int fd)
{
	char	*line;
	int		type;
	int		list;

	list = 0;
	object->n = 0;
	while (get_next_line(fd, &line) == 1)
	{
		type = get_type(line);
		if (type == NEW_LINE)
		{
			ft_memdel((void **)&line);
			return (1);
		}
		else if (type == COMMENT)
		{
			ft_memdel((void **)&line);
			continue ;
		}
		else if (type == KEY)
		{
			object->list[list].key = pretty_name(line);
		}
		else if (type == VALUE)
		{
			object->list[list].value = ft_strtrim(line);
			object->n += 1;
			list++;
		}
		ft_memdel((void **)&line);
	}
	return (1);
}

t_parser 	*parse(char *filename)
{
	t_parser	*p;
	char		*line;
	int			fd;
	int			type;
	int			object;

	p = new_parser();
	if (!p)
		return (NULL);
	fd = open(filename, O_RDONLY);
	object = 0;
	while (get_next_line(fd, &line) == 1)
	{
		type = get_type(line);
		if (type == COMMENT)
		{
			ft_memdel((void **)&line);
			continue ;
		}
		else if (type == OBJECT)
		{
			p->objects[object].name = pretty_name(line);
			parse_object(&(p->objects[object]), fd);
			object++;
			p->n += 1;
		}
		ft_memdel((void **)&line);
	}
	close(fd);
	if (!check(p))
		return (NULL);
	return (p);
}

void		pretty_parser(t_parser *p)
{
	t_object		*object;
	t_object_list	*list;
	int				i;
	int				j;

	printf("Objects: %d\n", p->n);
	i = 0;
	while (i < p->n)
		{
			object = &(p->objects[i]);
			list = object->list;
			printf("Object: %s\n", object->name);
			j = 0;
			while (j < object->n)
			{
				printf("\tList:\n\t\tKey:\t%s\n\t\tValue:\t%s\n",
					list[j].key, list[j].value);
				j++;
			}
			i++;
		}
}
