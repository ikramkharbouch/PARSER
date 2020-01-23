/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikrkharb <ikrkharb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 20:54:36 by ikrkharb          #+#    #+#             */
/*   Updated: 2020/01/14 21:57:44 by ikrkharb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vec		char_to_vec(char *str)
{
	char	**values;
	t_vec	tmp;
	
	ft_strtrim(str);
	values 	= ft_strsplit(str, ' ');
	tmp.x 	= ft_atof(values[0]);
	tmp.y 	= ft_atof(values[1]);
	tmp.z 	= ft_atof(values[2]);
	return (tmp);
}