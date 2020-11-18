# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/10 14:45:40 by mkivipur          #+#    #+#              #
#    Updated: 2020/07/02 09:38:34 by mkivipur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

SRCS = ./sources/main.c ./sources/read.c ./sources/get_next_line.c ./sources/draw.c ./sources/color.c ./sources/vector_calc.c ./sources/vector_calc2.c ./sources/rotate_vec.c ./sources/init.c ./sources/intersect_sphere.c ./sources/intersect_plane.c ./sources/intersect_cylinder.c ./sources/intersect_cone.c ./sources/shadow.c ./sources/error.c ./sources/memory.c ./sources/cylinder.c ./sources/camera.c ./sources/plane.c ./sources/cone.c ./sources/sphere.c ./sources/spot.c ./sources/utils.c ./sources/light.c

OBJS = ./*.o

HDR = ./sources/

MLX		= ./miniLibX/

LIBS	= -L libft/ -lft -L ./miniLibX -l mlx -framework OpenGL -framework AppKit

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS) 
	gcc $(OBJS) $(LIBS) -o $(NAME)

$(OBJS): $(SRCS) 
	$(CC) $(FLAGS) -c $(SRCS)
	make re -C ./libft/

clean:
	/bin/rm -f $(OBJS)
	make clean -C ./libft/
fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C ./libft/
re: fclean all
