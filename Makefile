# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsibiet <rsibiet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/28 12:44:44 by rsibiet           #+#    #+#              #
#    Updated: 2017/05/04 13:32:44 by ksoulard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FTC = main.c init.c threads.c graphic.c rest.c think.c eat.c

SRC_FTC = $(addprefix srcs/, $(FTC))

FTO = $(SRC_FTC:%.c=%.o)

EXEC = libft.a
.PHONY: all re clean fclean

all: $(EXEC) $(NAME)

$(EXEC):
		@echo "\033[34;1m___________________________ Loading libft ______________________________\033[0m\n"
		@make -C ./libft

$(NAME): $(FTO)
	@echo ""
	@echo "\033[32m• $(NAME) created!\033[0m"
	@echo "\n"
	@gcc -Wall -Wextra -Werror -o $(NAME) $(FTO) -I ./includes/ -L./libft/ -lft -lmlx -framework OpenGL -framework Appkit

%.o: %.c
	@tput civis
	@gcc -Wall -Wextra -Werror -I./libft/ -I./includes/ -o $@ -c $<
	@tput cnorm

clean:
	@rm -rf $(FTO)
	@echo "\033[33m• $(NAME) object deleted!\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[31;1m• \033[31m$(NAME) deleted!\033[0m"

re: fclean all
