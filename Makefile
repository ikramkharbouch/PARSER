# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikrkharb <ikrkharb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/02 20:53:05 by ikrkharb          #+#    #+#              #
#    Updated: 2020/01/20 01:49:34 by ikrkharb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

FLAGS = -Wall -Werror -Wextra

SRCS = 	srcs/camera.c\
		srcs/fill_data.c\
		srcs/hooks.c\
		srcs/parser.c\
		srcs/rtv1.c\
		srcs/vectors_ops.c\
		srcs/debug.c\
		srcs/objects.c\
		srcs/intersection.c\
		srcs/utils.c

LIBFT = libft/libft.a

LIBPS = Dynamic_parser/libparser.a

INC = includes/rtv1.h

all: $(NAME)

$(NAME): $(SRCS) $(INC)
	@make -C libft > /dev/null
	@make -C Dynamic_parser > /dev/null
	@gcc $(FLAGS) -I usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit $(SRCS) $(LIBFT) $(LIBPS) -o $(NAME)
	@echo "\033[92mDone\033[0m"

clean:
	@make clean -C libft
	@make clean -C Dynamic_parser
	@echo "\033[92mCleaning done\033[0m"

fclean:
	@make fclean -C libft
	@make fclean -C Dynamic_parser
	@/bin/rm -rf $(NAME)
	@echo "\033[92mExecution and cleaning were done\033[0m"

re: fclean all