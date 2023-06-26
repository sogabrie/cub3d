/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:12:18 by sogabrie          #+#    #+#             */
/*   Updated: 2023/06/26 16:12:19 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_STRUCT_H
# define DEF_STRUCT_H

//  Error and Warning messages
# define E_MALLOC "Error\n! Failed to allocate dynamic memory !\n"
# define E_ARGC_1 "Error\n! Please specify the .cub file !\n"
# define W_ARGC_2 "Warning\n! Only the first argument is considered !\n"
# define E_OPEN_FILE "Error\n! It was not possible to open the file !\n"
# define E_FILE_EMPTY "Error\n! .cub file is empty !\n"
# define E_CONFIGURATION "Error\n! Wrong file configuration !\n"
# define E_MAP_CONF "Error\n! Incorrect map configuration !\n"

typedef struct s_colors {
	int	red;
	int	green;
	int	blue;
}	t_colors;

typedef struct s_options {
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	t_colors	floor;
	t_colors	ceiling;

}	t_options;

typedef struct s_data_segment {
	char		**map;
	t_options	options;
	int			y_axis;
	int			x_axis;
}	t_data_segment;

#endif